#ifndef DIAGNOSE_H
#define DIAGNOSE_H

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

namespace Ui {
class Diagnose;
}

class Diagnose : public QMainWindow
{
    Q_OBJECT

public:
    explicit Diagnose(QWidget *parent = nullptr);
    ~Diagnose();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    QString getDate();
    QString getMNum();
    void ChangeStatus(QString str);
    void init_DWIN();
    Ui::Diagnose *ui;
};

#endif // DIAGNOSE_H
