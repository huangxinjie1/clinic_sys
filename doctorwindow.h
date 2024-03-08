#ifndef DOCTORWINDOW_H
#define DOCTORWINDOW_H

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
#include"showcasehistory.h"
#include"diagnose.h"
#include "addprescription.h"

namespace Ui {
class DoctorWindow;
}

class DoctorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DoctorWindow(QWidget *parent = nullptr);
    ~DoctorWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    bool isDia(QString str);
    bool isPres(QString str);
    void init_DWT();
    QString getPnum(QString str);
    ShowCaseHistory *schw;
    Diagnose *dgw;
    AddPrescription *apw;
    Ui::DoctorWindow *ui;
};

#endif // DOCTORWINDOW_H
