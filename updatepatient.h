#ifndef UPDATEPATIENT_H
#define UPDATEPATIENT_H

#include <QMainWindow>
#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>
#include<QCryptographicHash>
#include<QString>
#include<QStringList>

namespace Ui {
class UpdatePatient;
}

class UpdatePatient : public QMainWindow
{
    Q_OBJECT

public:
    void init_UpPWin();
    explicit UpdatePatient(QWidget *parent = nullptr);
    ~UpdatePatient();

private slots:
    void on_pushButton_clicked();
    QString strToMd5(QString str);
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::UpdatePatient *ui;
};

#endif // UPDATEPATIENT_H
