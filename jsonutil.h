/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#ifndef JSONUTIL_H
#define JSONUTIL_H

#include <QJsonArray>
#include <QJsonObject>
#include "pagelist.h"

class JsonUtil
{
public:
    template <typename TModel>
    static PageList<TModel> ConvertToPageList(const QJsonObject& jsonData) {
        QJsonObject jsonObj = jsonData.value("data").toObject();

        PageList<TModel> pglist = PageList<TModel>();
        pglist.pageNo = jsonObj.value("pageNo").toInt();
        pglist.pageSize = jsonObj.value("pageSize").toInt();
        pglist.totalCount = jsonObj.value("total").toInt();

        QJsonArray jsonArr = jsonObj.value("list").toArray();
        for (int i=0; i<jsonArr.size(); i++) {
            pglist.add(TModel::fromJson(jsonArr[i].toObject()));
        }

        return pglist;
    }

    template <typename TModel>
    static QList<TModel> ConvertToList(const QJsonObject& jsonData) {
        QList<TModel> list = QList<TModel>();
        QJsonArray jsonArr = jsonData.value("data").toArray();
        for (int i=0; i<jsonArr.size(); i++) {
            list.append(TModel::fromJson(jsonArr[i].toObject()));
        }
        return list;
    }
};

#endif // JSONUTIL_H
