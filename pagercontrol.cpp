/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#include "pagercontrol.h"
#include "ui_pagercontrol.h"
#include <QToolButton>

PagerControl::PagerControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PagerControl),
    pageNo(0),
    pageSize(20),
    totalCount(0),
    totalPages(0)
{
    ui->setupUi(this);
    ui->gridLayout->setContentsMargins(3,3,3,3);
    ui->label->setText("0 / 0");

    connect(ui->tbtnFirst, &QToolButton::clicked, [this]() { gotoPage(1); });
    connect(ui->tbtnPrev, &QToolButton::clicked, [this]() { gotoPage(pageNo - 1); });
    connect(ui->tbtnNext, &QToolButton::clicked, [this]() { gotoPage(pageNo + 1); });
    connect(ui->tbtnLast, &QToolButton::clicked, [this]() { gotoPage(totalPages); });
}

void PagerControl::setPagerInfo(int pageNo, int pageSize, int totalCount)
{
    this->pageNo = pageNo;
    this->pageSize = pageSize;
    this->totalCount = totalCount;
    this->totalPages = (totalCount - 1) / pageSize + 1;

    ui->label->setText(QString("%1 / %2").arg(pageNo).arg(totalPages));
}

void PagerControl::gotoPage(int newPage)
{
    if (totalPages == 0)
        return;

    if (newPage == pageNo)
        return;

    if (newPage>0 && newPage <= totalPages)
        emit currentPageChanged(newPage);
}

PagerControl::~PagerControl()
{
    delete ui;
}
