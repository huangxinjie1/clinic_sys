#ifndef ADDDOCTOR_H
#define ADDDOCTOR_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>
#include<QCryptographicHash>
#include<QString>
#include<QList>

namespace Ui {
class AddDoctor;
}

class AddDoctor : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddDoctor(QWidget *parent = nullptr);
    ~AddDoctor();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void init_doc();
    void AddToRoom(QString str);
    QString FindNUM();
    QString FindRNUM(QString str);
    bool IsAccExsis(QString str);
    bool IsAccRep(QString str);
    bool IsAccNull();
    bool IsInfoNull();
    QString strToMd5(QString str);
    Ui::AddDoctor *ui;
};

#endif // ADDDOCTOR_H
