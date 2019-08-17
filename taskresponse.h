/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#ifndef TASKRESPONSE_H
#define TASKRESPONSE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "jsonutil.h"
#include "product.h"

class BaseResponse
{
public:
    BaseResponse() { }
    virtual ~BaseResponse() { qDebug()<<"response destoryed."; }

    void handleResult(const QByteArray& data);

protected:
    virtual void handleData(const QJsonObject& jsonData);

public:  /* members */
    int errCode;
    QString errMsg;
};

template <typename TModel>
class TaskResponse : public BaseResponse
{

public:
    explicit TaskResponse() { }

    void handleData(const QJsonObject& jsonData) override {

        if (typeid(int) == typeid (TModel))
            data = jsonData.value("data").toInt();
        else if (typeid(double) == typeid(TModel))
            data = jsonData.value("data").toDouble();
        else if (typeid(QString) == typeid(TModel))
            data = jsonData.value("data").toString();
        else if (typeid(bool) == typeid(TModel))
            data = jsonData.value("data").toBool();
    }

public:
    TModel data;
};

template <>
class TaskResponse<Product> : public BaseResponse
{

public:
    explicit TaskResponse() { }

    void handleData(const QJsonObject& jsonData) override {

        data = Product::fromJson(jsonData.value("data").toObject());
    }

public:
    Product data;
};

template <typename TModel>
class TaskResponse<QList<TModel>> : public BaseResponse
{

public:
    explicit TaskResponse() { }

    void handleData(const QJsonObject& jsonData) override {
        data = JsonUtil::ConvertToList<TModel>(jsonData);
    }

public:
    QList<TModel> data;
};

template <typename TModel>
class TaskResponse<PageList<TModel>> : public BaseResponse
{

public:
    explicit TaskResponse() { }

    void handleData(const QJsonObject& jsonData) override {
        data = JsonUtil::ConvertToPageList<TModel>(jsonData);
    }

    PageList<TModel> data;
};

#endif // TASKRESPONSE_H
