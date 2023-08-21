#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this, database);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    querymodel = new QSqlQueryModel();
    // вывод всех таблиц
    querymodel->setQuery("SHOW TABLES");
    ui->comboBox->setModel(querymodel);
    ui->tableView->setModel(querymodel);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    // submitting all changes data
    if(ask_privilege())
    {
        model->submitAll();
        log = " submitting data - true";
        on_log_objectNameChanged(log);
    }else
    {
        log = " submitting data - false (bad privileges)";
        on_log_objectNameChanged(log);
    }
}

void Dialog::on_pushButton_2_clicked()
{
    // revering changed data
    model->revertAll();
    log = " reverting data - true";
    on_log_objectNameChanged(log);
}

void Dialog::on_reselected_table_clicked()
{
    model->select();
}

void Dialog::on_add_row_clicked()
{
    // adding in the end
    if(ask_privilege())
    {
        qDebug() << "Insering row - " << model->insertRow(model->rowCount());
        log = " Inserting row - " + model->insertRow(model->rowCount());
        on_log_objectNameChanged(log);
    }
    else
    {
        log = " Inserting row - false (bad privileges)";
        on_log_objectNameChanged(log);
    }
}

void Dialog::on_detele_row_clicked()
{
    int selectedRow = ui->tableView->currentIndex().row();
    if(ask_privilege())
    {
        if(selectedRow >= 0)
        {
            qDebug() << "deleting row:" << model->removeRow(selectedRow);
            log = " deleting row - true";
            on_log_objectNameChanged(log);
        }else
        {
            qDebug() << "no row selected";
            log = "deleting row - false (no row selected)";
            on_log_objectNameChanged(log);
        }
    }
    else
    {
        log = " deleting row - false (bad privileges)";
        on_log_objectNameChanged(log);
    }
}

void Dialog::on_comboBox_activated(const QString &which_table)
{
    current_table = which_table;
    model->setTable(which_table);
    model->select();

    ui->tableView->setModel(model);
    on_textEdit_objectNameChanged(which_table);

    // допилить, чтобы можно было редактировать конкретую строчку
    // сделать лог-строчку
    // сделать сортировку по значению
}

void Dialog::on_show_tables_clicked()
{
    querymodel = new QSqlQueryModel();
    // вывод всех таблиц
    querymodel->setQuery("SHOW TABLES");
    ui->comboBox->setModel(querymodel);
    ui->comboBox->setModelColumn(0);
    ui->tableView->setModel(querymodel);
}

void Dialog::on_export_csv_clicked()
{
    QSqlQuery query(database);
    {
        query.prepare(QString("SELECT * FROM users"));// INTO OUTFILE '/var/tmp/table.csv'"));
//        query.bindValue(":current_table", current_table);
        if(!query.exec())
        {
            QMessageBox::information(this, "Failed", "Query failed to execute");
        }
        else
        {
            log = "export table - true";
            on_log_objectNameChanged(log);
        }
    }
}

void Dialog::on_textEdit_objectNameChanged(const QString &objectName)
{
    ui->textEdit->setPlainText(objectName);
}

void Dialog::on_log_objectNameChanged(const QString &objectName)
{
    ui->log->setPlainText(objectName);
}
