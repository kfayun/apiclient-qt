/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include "taskrequest.h"
#include "apiclient.h"
#include <QTableWidgetItem>
#include "product.h"
#include "productform.h"
#include "pagercontrol.h"
#include "myrequests.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void paperPageChanged(int newPage);

    void setPaperList(const PageList<Product>& data)
    {
        if (paperlist != nullptr) {
            paperlist.clear();
            paperlist = nullptr;
        }
        PageList<Product> *list = new PageList<Product>(data);
        paperlist = QSharedPointer<PageList<Product>>(list);
    }

    void on_actionSearch_triggered();

private:
    void onProductListResponse(const QSharedPointer<TaskResponse<PageList<Product>>>& response);
    void onRequestError(const QException* exception);

    void loadTestPapers(int pageNo);

private:
    Ui::MainWindow* ui;
    QLabel *keywordLabel;
    QTextEdit *keywordEdit;
    PagerControl *pagerCtl;

private:
    ApiClient* client;

    QSharedPointer<PageList<Product>> paperlist = nullptr;
};

#endif // MAINWINDOW_H
