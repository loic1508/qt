#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication4.h"
#include <qsqldatabase.h>
#include <qstandarditemmodel.h>

class QtWidgetsApplication4 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication4(QWidget *parent = nullptr);
    ~QtWidgetsApplication4();

private:
    Ui::QtWidgetsApplication4Class ui;

	QSqlDatabase db;
	QStandardItemModel* model;
};