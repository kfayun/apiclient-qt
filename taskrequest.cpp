/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#include "taskrequest.h"

QString BaseRequest::buildUrl()
{
    QDateTime currTime = QDateTime::currentDateTime();
    uint ticks = currTime.toTime_t();
    QString sign = getSign(QString("yuntik#%1").arg(ticks));

    QString query = getQueryString();
    QString sep = (query.indexOf('?') > 0) ? "&" : "?";

    return API_URL + QString("%1%2ts=%3&sign=%4").arg(query).arg(sep).arg(ticks).arg(sign);
}

QByteArray BaseRequest::getPostData()
{
    return nullptr;
}
