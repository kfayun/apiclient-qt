/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>

class HttpRequest : public QObject
{

    Q_OBJECT

public:
    HttpRequest() {}

    QByteArray get(const QString& url);

    QByteArray post(const QString& url, const QByteArray& postData);

    /* member */
public:
    int statusCode;
    int errorCode;
    QString errorMessage;
};

#endif // HTTPREQUEST_H
