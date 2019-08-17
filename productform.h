/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#ifndef PRODUCTFORM_H
#define PRODUCTFORM_H

#include <QDialog>
#include <QCloseEvent>
#include <QListWidget>
#include <QTableWidget>
#include <QSplitter>
#include "product.h"
#include "apiclient.h"

namespace Ui {
class ProductForm;
}

class ProductForm : public QDialog
{
    Q_OBJECT

public:
    explicit ProductForm(const Product& product, QWidget *parent = nullptr);
    ~ProductForm();

private:

    void onProductResponse( const QSharedPointer<TaskResponse<Product>>& response);
    void onRequestError(const QException* exception);

private:
    Ui::ProductForm *ui;

    ApiClient *client;

    Product product;
};

#endif // PRODUCTFORM_H
