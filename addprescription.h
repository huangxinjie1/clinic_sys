#ifndef ADDPRESCRIPTION_H
#define ADDPRESCRIPTION_H
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
#include<QDateTime>

namespace Ui {
class AddPrescription;
}

class AddPrescription : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddPrescription(QWidget *parent = nullptr);
    ~AddPrescription();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    QString getConNum();
    QString get_time();
    QString getDrNum(QString str);
    QString getPrNum();  //获取开处方编号
    QString getPreNum(); //获取处方编号
    void ChangeStatus(QString str);
    void init_APW();
    void init_AddPR();
    void init_APT();
    Ui::AddPrescription *ui;
};

#endif // ADDPRESCRIPTION_H
