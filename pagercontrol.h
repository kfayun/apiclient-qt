/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#ifndef PAGERCONTROL_H
#define PAGERCONTROL_H

#include <QWidget>

namespace Ui {
class PagerControl;
}

class PagerControl : public QWidget
{
    Q_OBJECT

public:
    explicit PagerControl(QWidget *parent = nullptr);
    ~PagerControl();

public:
    void setPagerInfo(int pageNo, int pageSize, int totalCount);

signals:
    void currentPageChanged(int newPage);

private:
    void gotoPage(int page);

private:
    Ui::PagerControl *ui;

    int pageNo;
    int pageSize;
    int totalCount;
    int totalPages;
};

#endif // PAGERCONTROL_H
