#ifndef ADDPATIENT_H
#define ADDPATIENT_H

#include<QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>
#include<QCryptographicHash>
#include<QString>

namespace Ui {
class AddPatient;
}

class AddPatient : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddPatient(QWidget *parent = nullptr);
    ~AddPatient();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::AddPatient *ui;
    bool flag1,flag2;
    bool IsAccExsis(QString str);
    QString FindPNUM();
    QString strToMd5(QString str);
};

#endif // ADDPATIENT_H
