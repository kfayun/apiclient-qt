/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#ifndef MYREQUESTS_H
#define MYREQUESTS_H

#include "taskrequest.h"
#include "taskresponse.h"
#include "product.h"

class GetProductListRequest : public TaskRequest<PageList<Product>>
{
public:
    GetProductListRequest(const QString& keyword) :
          keyword(keyword), pageNo(1),  pageSize(20) { }

    QString getQueryString() override;

public:
    QString keyword;
    int pageNo;
    int pageSize;

};

class GetProductRequest : public TaskRequest<Product>
{
public:
    GetProductRequest(int productId) :
        productId(productId) { }

    QString getQueryString() override;

public:
    int productId;

};

#endif // MYREQUESTS_H
