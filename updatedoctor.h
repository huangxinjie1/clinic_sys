#ifndef UPDATEDOCTOR_H
#define UPDATEDOCTOR_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>
#include<QCryptographicHash>
#include<QString>
#include<QList>

namespace Ui {
class UpdateDoctor;
}

class UpdateDoctor : public QMainWindow
{
    Q_OBJECT

public:
    explicit UpdateDoctor(QWidget *parent = nullptr);
    ~UpdateDoctor();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    void init_updWin();
    bool IsInfoNull();
    void UpDW_init();
    void Updcom_init();
    void AddPepleNum(QString str);
    void SubPepleNUm(QString str);
    QString FormatRegu(QString str);
    QString getRNum(QString str);
    QString strToMD5(QString str);
    Ui::UpdateDoctor *ui;
};

#endif // UPDATEDOCTOR_H
