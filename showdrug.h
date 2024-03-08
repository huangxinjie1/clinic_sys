#ifndef SHOWDRUG_H
#define SHOWDRUG_H

#include <QMainWindow>
#include <QMainWindow>
#include<QStandardItemModel>
#include<QStandardItem>
#include<QTableView>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlRecord>
#include<QMessageBox>
#include<QDebug>
#include<QCryptographicHash>
#include<QString>

namespace Ui {
class ShowDrug;
}

class ShowDrug : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowDrug(QWidget *parent = nullptr);
    ~ShowDrug();

private slots:
    void on_pushButton_clicked();

private:
    void show_info();
    Ui::ShowDrug *ui;
};

#endif // SHOWDRUG_H
