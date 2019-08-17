/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#ifndef PAGELIST_H
#define PAGELIST_H

#include <QList>

template <typename TModel>
class PageList
{
public:
    int pageNo;
    int pageSize;
    int totalCount;

    QList<TModel> list;

    void add(TModel item) {
        list.append(item);
    }
};

#endif // PAGELIST_H
