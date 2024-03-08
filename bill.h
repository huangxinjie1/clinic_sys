#ifndef BILL_H
#define BILL_H

#include <QMainWindow>
#include<QStandardItemModel>
#include<QStandardItem>
#include<QTableView>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlRecord>
#include<QMessageBox>
#include<QDebug>
#include<QDateTime>
#include<QDate>

#include "paywin.h"
namespace Ui {
class Bill;
}

class Bill : public QMainWindow
{
    Q_OBJECT

public:
    explicit Bill(QWidget *parent = nullptr);
    ~Bill();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    PayWin *payw;
    bool isPay();
    void init_BT1();
    void init_BT2(QString str);
    Ui::Bill *ui;
};

#endif // BILL_H
