/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#ifndef TASKREQUEST_H
#define TASKREQUEST_H

#include <QObject>
#include <QCryptographicHash>
#include <QDateTime>
#include "taskresponse.h"
#include "constants.h"

class ApiClient;

class BaseRequest
{
public:
    explicit BaseRequest() { }
    virtual ~BaseRequest() { qDebug()<< "request destoryed."; }

    QString buildUrl();

    virtual QByteArray getPostData();

protected:
    virtual QString getQueryString() = 0;

private:
    QString getSign(QString str) {
        return QCryptographicHash::hash(str.toUtf8(), QCryptographicHash::Md5).toHex();
    }

/* members */
private:

};

template<typename TModel>
class TaskRequest : public BaseRequest
{
};

#endif // TASKREQUEST_H
