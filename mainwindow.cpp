/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrequests.h"
#include "apiclient.h"
#include <QDebug>
#include <QThread>
#include <QWidget>
#include <QComboBox>
#include <QMessageBox>
#include <productform.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    keywordLabel(new QLabel("Keyword:", this)),
    keywordEdit(new QTextEdit(this)),
    pagerCtl(new PagerControl(this)),
    client(new ApiClient(this))
{
    ui->setupUi(this);

    // init layout
    ui->centralWidget->layout()->setContentsMargins(0,0,0,0);
    ui->page->layout()->setContentsMargins(3,3,3,3);
    pagerCtl->setFixedHeight(30);
    ui->page->layout()->addWidget(pagerCtl);

    ui->mainToolBar->insertWidget(ui->actionSearch, keywordLabel);

    keywordEdit->setFixedHeight(30);
    keywordEdit->setFixedWidth(100);
    ui->mainToolBar->insertWidget(ui->actionSearch, keywordEdit);

    // init ui
    QStringList headerList;
    headerList << "ID" << "名称" << "简介" << "添加时间";
    ui->tableWidget->setColumnCount(headerList.size());
    ui->tableWidget->setHorizontalHeaderLabels(headerList);
    ui->tableWidget->setColumnWidth(2, 300);
    ui->tableWidget->setContextMenuPolicy(Qt::DefaultContextMenu);

    connect(pagerCtl, &PagerControl::currentPageChanged, this, &MainWindow::paperPageChanged );

    // load data.
    connect(client, static_cast<void (ApiClient::*)(const QSharedPointer<TaskResponse<PageList<Product>>>& )>(&ApiClient::onResponse),
            this, &MainWindow::onProductListResponse);

    connect(client, &ApiClient::onError, this, &MainWindow::onRequestError);

    loadTestPapers(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::loadTestPapers(int pageNo)
{
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->clearContents();
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("正在读取数据，请稍候..."));

    GetProductListRequest *request = new GetProductListRequest(keywordEdit->toPlainText());
    request->pageNo = pageNo;
    QSharedPointer<TaskRequest<PageList<Product>>> ptr(request);
    client->asyncExecute(ptr);
}

void MainWindow::onProductListResponse(const QSharedPointer<TaskResponse<PageList<Product>>>& response)
{
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();

    if (response->errCode==0) {
        setPaperList(response->data);

        ui->tableWidget->setRowCount(paperlist->list.size());
        int i=0;
        for (Product tp : paperlist->list) {
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(tr("%1").arg(tp.id)));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(tp.name));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(tp.summary));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(tp.addTime.toString("yyyy-MM-dd")));

            ++i;
        }

        pagerCtl->setPagerInfo(paperlist->pageNo, paperlist->pageSize, paperlist->totalCount);
    } else {
        QMessageBox::warning(this, "错误提示", response->errMsg);
    }
}

void MainWindow::onRequestError(const QException* exception)
{
    Q_UNUSED(exception);
}

void MainWindow::paperPageChanged(int newPage)
{
    GetProductListRequest* request = new GetProductListRequest("");
    request->pageNo = newPage;
    QSharedPointer<TaskRequest<PageList<Product>>> ptr(request);
    client->asyncExecute(ptr);
}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    Product tp = paperlist->list.value(item->row());

    ProductForm form(tp);
    form.exec();
}

void MainWindow::on_actionSearch_triggered()
{
    loadTestPapers(1);
}
