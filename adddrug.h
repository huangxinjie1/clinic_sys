#ifndef ADDDRUG_H
#define ADDDRUG_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QString>

namespace Ui {
class AddDrug;
}

class AddDrug : public QMainWindow
{
    Q_OBJECT

public:
    QString FindNum();
    QString FindPhnum(QString str);
    explicit AddDrug(QWidget *parent = nullptr);
    ~AddDrug();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddDrug *ui;
};

#endif // ADDDRUG_H
