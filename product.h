/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#ifndef TESTPAPER_H
#define TESTPAPER_H

#include <QJsonObject>
#include <QDateTime>

class Product
{
public:
    int id;
    QString name;
    QString summary;
    QDateTime addTime;

public:
    static Product fromJson(const QJsonObject& jsonObj) {

        Product prod;
        prod.id = jsonObj.value("id").toInt();
        prod.name = jsonObj.value("name").toString();
        prod.summary = jsonObj.value("summary").toString();
        prod.addTime = QDateTime::fromString(jsonObj.value("addTime").toString(), "yyyy-MM-dd hh:mm:ss");

        return prod;
    }

};

#endif // TESTPAPER_H
