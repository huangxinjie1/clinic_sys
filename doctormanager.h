#ifndef DOCTORMANAGER_H
#define DOCTORMANAGER_H

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
#include<QList>
#include "adddoctor.h"
#include "updatedoctor.h"

namespace Ui {
class DoctorManager;
}

class DoctorManager : public QMainWindow
{
    Q_OBJECT

public:
    UpdateDoctor *udw;
    AddDoctor *adw;
    explicit DoctorManager(QWidget *parent = nullptr);
    ~DoctorManager();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

private:
    void DMT_init();
    void DMC_init();
    void subPepleNum(QString str);
    QString getRnum(QString str);
    QString FindRoom(QString str);
    Ui::DoctorManager *ui;
};

#endif // DOCTORMANAGER_H
