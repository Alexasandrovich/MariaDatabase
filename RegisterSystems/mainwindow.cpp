#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->username->setPlaceholderText("Enter Your Username");
    ui->password->setPlaceholderText("Enter Your Password");
    ui->Phone->setPlaceholderText("Enter Your Phone-number");
    ui->Email->setPlaceholderText("Enter Your Email");

    ui->login_form->setPlaceholderText("Enter Your Login");
    ui->login_password->setPlaceholderText("Enter Your Password");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // conncting to MariaDB database
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("AlexB");
    database.setPassword("3215237");
    database.setDatabaseName("Restaurant_Claude_Monet");
    if(database.open())
    {
        // retrieve data from input fields
        QString username = ui->username->text();
        QString password = ui->password->text();
        QString email = ui->Email->text();
        QString phone = ui->Phone->text();
        QString isAdmin = "";

        if(ui->checkBox->isTristate())
        {
            isAdmin = "1";
        }
        else isAdmin = "0";
        // run our insert query
        QSqlQuery qry;
        qry.prepare("INSERT INTO users_roles (username, password_, email, phone, is_admin)"
                    "VALUES (:username, :password, :email, :phone, :is_Admin)");

        qry.bindValue(":username", username);
        qry.bindValue(":password", password);
        qry.bindValue(":email", email);
        qry.bindValue(":phone", phone);
        qry.bindValue(":is_Admin", isAdmin);

        if(qry.exec())
        {
            QMessageBox::information(this, "Registration", "Registration is successful");
        }else
        {
            QMessageBox::information(this, "Registration", "Registration is NOT successful");
        }
    }else
    {
        QMessageBox::information(this, "Not connected", "DB is Not connected");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    // conncting to MariaDB database
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("AlexB");
    db.setPassword("3215237");
    db.setDatabaseName("Restaurant_Claude_Monet");

    QString username = ui->login_form->text();
    QString password = ui->login_password->text();
    if(db.open())
    {
        // creating My quereis
        QMessageBox::information(this, "Database Connected", "Database connection successfully");
        QSqlQuery query(QSqlDatabase::database("QMYSQL"));
        query.prepare(QString("SELECT * FROM users_roles WHERE username = :username AND password_ = :password"));
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if(!query.exec())
        {
            QMessageBox::information(this, "Failed", "Query failed to execute");
        }
        else{
            while(query.next())
            {
                QString usernameFromDB = query.value(1).toString();
                QString passwordFromDB = query.value(2).toString();
                QString isAdmin = query.value(5).toString();

                if(usernameFromDB == username && passwordFromDB == password)
                {
                    QMessageBox::information(this, "Success", "Login Success");
                    Dialog dialog;
                    dialog.setModal(true);
                    dialog.getDB(db, isAdmin);
                    dialog.exec();
                }else
                {
                    QMessageBox::information(this, "Failed", "Login failed");
                }
            }
        }

    }
    else
    {
        QMessageBox::information(this, "Database Failed", "Database connection failed");
    }
}
