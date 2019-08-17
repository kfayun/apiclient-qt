/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#ifndef ASYNCTASK_H
#define ASYNCTASK_H

#include <QObject>
#include <QException>
#include <QThread>
#include "taskrequest.h"
#include "httprequest.h"

class AsyncTask : public QObject
{
    Q_OBJECT

public:
    explicit AsyncTask(const QSharedPointer<BaseRequest>& request, QObject *parent=nullptr)
        : QObject(parent), request(request) { }
    ~AsyncTask() { qDebug()<<"task destoryed."; }

signals:
    void completed(const QSharedPointer<BaseRequest>& request, const QByteArray& data);
    void error(const QSharedPointer<BaseRequest>& request, const QException* ex);

public slots:
    void execute() {
        try {
           QString url = request->buildUrl();
           qDebug() << "request url:" << url;

           HttpRequest req;
           QByteArray data = req.get(url);

           emit completed(request, data);

        } catch (QException *err) {
           qDebug() << err;

           emit error(request, err);
        }

    }

    /* members */
private:
     QSharedPointer<BaseRequest> request;
};

#endif // ASYNCTASK_H
