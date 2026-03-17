#include "QtWidgetsApplication4.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

QtWidgetsApplication4::QtWidgetsApplication4(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("172.29.16.55");
    db.setDatabaseName("QTBDD");
    db.setUserName("testBDD");
    db.setPassword("testBDD");

    if (db.open())
    {
        ui.DBStatusLabel->setText("Status BDD : Connecté");
        updateUserList();
    }
    else
    {
        ui.DBStatusLabel->setText("Status BDD : Erreur de connexion");
        qDebug() << "Erreur connexion :" << db.lastError().text();
    }

    connect(ui.pushButton, &QPushButton::clicked,
        this, &QtWidgetsApplication4::onCreateUserButtonClicked);
    connect(ui.ConnectUserButton, &QPushButton::clicked,
        this, &QtWidgetsApplication4::onLoginButtonClicked);
}

void QtWidgetsApplication4::onCreateUserButtonClicked()
{
    QString username = ui.lineedit2->text();
    QString password = ui.lineEdit->text();

    QSqlQuery query;
    query.prepare("INSERT INTO Users (Login, Password) VALUES (:user, SHA2(:pass, 512));");
    query.bindValue(":user", username);
    query.bindValue(":pass", password);

    if (query.exec())
    {
        qDebug() << "Utilisateur ajouté.";
        
        QMessageBox msgBox;
        msgBox.setText("Utilisateur créé avec succès !");
        msgBox.exec();
        updateUserList();
    }
    else
    {
        qDebug() << "Erreur ajout :" << query.lastError().text();
        QMessageBox::warning(this, "Erreur",
            "Impossible d'ajouter l'utilisateur :\n" + query.lastError().text());
    }
}

void QtWidgetsApplication4::onLoginButtonClicked()
{
    QString username = ui.UsernameLineEdit_2->text();
    QString password = ui.PasswordLineEdit_2->text();

    QSqlQuery query;
    query.prepare("SELECT id FROM Users WHERE Login = :user AND Password = SHA2(:pass, 512);");
    query.bindValue(":user", username);
    query.bindValue(":pass", password);

    
    if (!query.exec())
    {
        QMessageBox::warning(this, "Erreur SQL",
            "Erreur lors de la connexion :\n" + query.lastError().text());
        return;
    }

    QMessageBox msgBox;
    msgBox.setText(query.next() ? "Connexion réussie !" : "Connexion échouée !");
    msgBox.exec();
}

void QtWidgetsApplication4::updateUserList()
{
    QSqlQuery query("SELECT id, Login, Password FROM Users;");

    if (model != nullptr)
    {
        model->deleteLater();
        model = nullptr;
    }

    model = new QStandardItemModel(0, 3, this);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Login");
    model->setHeaderData(2, Qt::Horizontal, "Password hash");

    while (query.next())
    {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::number(query.value("id").toInt()))
            << new QStandardItem(query.value("Login").toString())
            << new QStandardItem(query.value("Password").toString());
        model->appendRow(row);
    }

    ui.RequestResultTableViev->setModel(model);
}

QtWidgetsApplication4::~QtWidgetsApplication4() {}
		ui.DBStatusLabel->setText("Failed to connect to database");
	}
}
QtWidgetsApplication4::~QtWidgetsApplication4()
{}
