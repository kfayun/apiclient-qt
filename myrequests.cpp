/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#include "myrequests.h"

QString GetProductListRequest::getQueryString()
{
    return QString("test01/getproducts?keyword=%1&pageno=%2&pagesize=%3")
            .arg(keyword).arg(pageNo).arg(pageSize);
}

QString GetProductRequest::getQueryString()
{
    return QString("test01/getproduct?productid=%1")
            .arg(productId);
}
