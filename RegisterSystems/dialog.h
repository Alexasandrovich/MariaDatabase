#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    QString current_table;
    QString log;

public:
    explicit Dialog(QWidget *parent = 0);
    void getDB(QSqlDatabase& database_open, QString& privilege_)
    {
        database = database_open;
        privilege = privilege_;

    }
    bool ask_privilege()
    {
        if(privilege == "1")
        {
            return 1;
        }
        else return 0;
    }
    ~Dialog();

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_reselected_table_clicked();

    void on_add_row_clicked();

    void on_detele_row_clicked();

    void on_comboBox_activated(const QString &which_table);

    void on_show_tables_clicked();

    void on_export_csv_clicked();

    void on_textEdit_objectNameChanged(const QString &objectName);

    void on_log_objectNameChanged(const QString &objectName);

private:
    Ui::Dialog *ui;
    QSqlDatabase database;
    QSqlQueryModel *querymodel;
    QSqlTableModel* model;
    QString privilege;
};

#endif // DIALOG_H
