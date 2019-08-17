/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#include "productform.h"
#include "myrequests.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QMessageBox>
#include "ui_productform.h"

ProductForm::ProductForm(const Product& product, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductForm),
    client(new ApiClient(this)),
    product(product)
{
    ui->setupUi(this);

    ui->nameEdit->setPlainText(product.name);
    ui->summaryEdit->setPlainText(product.summary);

    // load data.
    connect(client, static_cast<void (ApiClient::*)(const QSharedPointer<TaskResponse<Product>>&)>(&ApiClient::onResponse),
            this, &ProductForm::onProductResponse);

    GetProductRequest *request = new GetProductRequest(product.id);
    QSharedPointer<TaskRequest<Product>> ptr(request);
    client->asyncExecute(ptr);
}

ProductForm::~ProductForm()
{
    delete ui;
}

void ProductForm::onProductResponse(const QSharedPointer<TaskResponse<Product>>& response)
{
    if (response->errCode==0) {

        product = response.data()->data;

        ui->nameEdit->setPlainText(product.name);
        ui->summaryEdit->setPlainText(product.summary);
    } else {
        QMessageBox::information(this, "错误提示", response->errMsg);
    }
}

void ProductForm::onRequestError(const QException* exception)
{
    Q_UNUSED(exception);
}
