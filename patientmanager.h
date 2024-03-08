#ifndef PATIENTMANAGER_H
#define PATIENTMANAGER_H

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

#include "addpatient.h"
#include "updatepatient.h"

namespace Ui {
class patientmanager;
}

class patientmanager : public QMainWindow
{
    Q_OBJECT

public:
    AddPatient *apw;
    explicit patientmanager(QWidget *parent = nullptr);
    ~patientmanager();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

private:
    void init_WIN();
    UpdatePatient *udw;
    Ui::patientmanager *ui;
};

#endif // PATIENTMANAGER_H
