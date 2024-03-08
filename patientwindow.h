#ifndef PATIENTWINDOW_H
#define PATIENTWINDOW_H

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
#include"updatepatient.h"
#include"reservation.h"
#include"showcasehistory.h"
#include"showdrug.h"
#include "bill.h"

namespace Ui {
class PatientWindow;
}

class PatientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PatientWindow(QWidget *parent = nullptr);
    ~PatientWindow();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

private:
    UpdatePatient *upw;
    ShowDrug *sdw;
    Reservation *rw;
    ShowCaseHistory *schw;
    Bill *bw;
    void init_PWT();
    void init_PWC();
    Ui::PatientWindow *ui;
};

#endif // PATIENTWINDOW_H
