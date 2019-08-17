/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QThread>
#include <QException>
#include <QDebug>
#include <QCryptographicHash>
#include "httprequest.h"
#include "asynctask.h"
#include "taskrequest.h"
#include "taskresponse.h"
#include "myrequests.h"
#include "product.h"

class ApiClient : public QObject
{
    Q_OBJECT

public:
    explicit ApiClient(QObject *parent) : QObject(parent)
    {
        qRegisterMetaType<QSharedPointer<TaskResponse<PageList<Product>>>>("QSharedPointer<TaskResponse<PageList<Product>>>");

        qRegisterMetaType<QSharedPointer<TaskResponse<Product>>>("QSharedPointer<TaskResponse<Product>>");

        qRegisterMetaType<QSharedPointer<TaskResponse<int>>>("QSharedPointer<TaskResponse<int>>");
    }

    ~ApiClient() { qDebug() << "apiclient destoryed."; }

signals:
    void onResponse(const QSharedPointer<TaskResponse<PageList<Product>>>& );

    void onResponse(const QSharedPointer<TaskResponse<Product>>& );

    void onResponse(const QSharedPointer<TaskResponse<int>>& );

    void onError(const QException* );

public:

    template<class TModel>
    void asyncExecute(const QSharedPointer<TaskRequest<TModel>>& request)
    {
        AsyncTask *task = new AsyncTask(request);
        QThread *bgThread = new QThread();

        // 线程结束时，销毁线程对象
        connect(bgThread, &QThread::finished, bgThread, &QThread::deleteLater);
        // 任务对象销毁后，退出线程
        connect(task, &AsyncTask::destroyed, bgThread, &QThread::quit);
        // 线程启动后，开始执行任务
        connect(bgThread, &QThread::started, task, &AsyncTask::execute );

        // 任务执行完成信号
        connect(task, &AsyncTask::completed, [=](const QSharedPointer<BaseRequest>& request, const QByteArray& data) {
            Q_UNUSED(request);

            TaskResponse<TModel>* response = new TaskResponse<TModel>();
            response->handleResult(data);

            QSharedPointer<TaskResponse<TModel>> ptr(response);
            emit onResponse(ptr);

            // 销毁任务对象
            task->deleteLater();
        });

        // 任务执行出现错误信号
        connect(task, &AsyncTask::error, [=](const QSharedPointer<BaseRequest>& request, const QException* ex){
            Q_UNUSED(request);

            emit onError(ex);

            // 销毁任务对象
            task->deleteLater();
        });

        task->moveToThread(bgThread);
        bgThread->start();
    }

    template<class TModel>
    const QSharedPointer<TaskResponse<TModel>> execute(const QSharedPointer<TaskRequest<TModel>>& request)
    {
        try {
           QString url = request->buildUrl();
           qDebug()<<"request url:" << url;

           QByteArray postData = request->getPostData();

           HttpRequest req;
           QByteArray data = (postData == nullptr ? req.get(url) : req.post(url, postData));

           TaskResponse<TModel> *response = new TaskResponse<TModel>();
           response->handleResult(data);

           QSharedPointer<TaskResponse<TModel>> ptr(response);
           return ptr;

        } catch (QException *err) {
           qDebug() << err;

           throw err;
        }
    }

};

#endif // APICLIENT_H
