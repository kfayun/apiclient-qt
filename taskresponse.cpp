/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#include "taskresponse.h"

void BaseResponse::handleResult(const QByteArray& data)
{
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data, &json_error));

    if(json_error.error != QJsonParseError::NoError)
    {
        errCode = -1;
        errMsg = "json error!";
        qDebug() << QString(data);
        return;
    }

    QJsonObject jsonData = jsonDoc.object();

    errCode = jsonData.value("errCode").toInt();
    errMsg = jsonData.value("errMsg").toString();

    if (errCode == 0)
    {
        handleData( jsonData );
    }
}

void BaseResponse::handleData(const QJsonObject& jsonData)
{
    Q_UNUSED(jsonData); /* do nothing; */
}
