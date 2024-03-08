#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include<QProcess>
#include<QString>
#include<QButtonGroup>
#include<QCryptographicHash>
#include<QByteArray>
#include<QDebug>
#include "doctorwindow.h"
#include "patientwindow.h"
#include "adaminwindow.h"
#include "addpatient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    AddPatient *apw;
    DoctorWindow *dw;
    PatientWindow *pw;
    AdaminWindow *aw;
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
    bool creatMySqlConn();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    void init_PNUM(QString str);
    void init_DNUM(QString str);
    Ui::StartWindow *ui;
    QString strToMd5(QString str);
};
#endif // STARTWINDOW_H
