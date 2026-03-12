#include "QtWidgetsApplication4.h"
#include <QDebug.h>
#include <QSqlQuery.h>

QtWidgetsApplication4::QtWidgetsApplication4(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	db = QSqlDatabase::addDatabase("QSQLITE");

	db.setHostName("172.29.16.255");
	db.setUserName("test");
	db.setPassword("test");
	db.setDatabaseName("QTBDD");

	if (db.open())
	{
		ui.DBStatusLabel->setText("Connected to database");

		QSqlQuery query("SELECT id, usernam, password * FROM users");

		model = new QStandardItemModel(query.size(), 3, this);
		model->setHeaderData(0, Qt::Horizontal, "Id");
		model->setHeaderData(0, Qt::Horizontal, "Username");
		model->setHeaderData(0, Qt::Horizontal, "Password hash");

		int lineCounter = 0;
		while (query.next())
		{
			//QString username = query.value(0).toString();
			//qDebug() << "Username: " << username;

			int id = query.value("id").toInt();
			QString username = query.value("username").toString();
			QString password = query.value("password").toString();

			model->setItem(lineCounter, 0, new QStandardItem(QString::number(id)));
			model->setItem(lineCounter, 1, new QStandardItem(username));
			model->setItem(lineCounter, 2, new QStandardItem(password));

			lineCounter++;
		}

		ui.RequestResultTableViev->setModel(model);

	}
	else
	{
		ui.DBStatusLabel->setText("Failed to connect to database");
	}
}
QtWidgetsApplication4::~QtWidgetsApplication4()
{}