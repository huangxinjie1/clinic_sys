#ifndef UPDATEDRUG_H
#define UPDATEDRUG_H

#include <QMainWindow>
#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>
#include<QCryptographicHash>
#include<QString>

namespace Ui {
class UpdateDrug;
}

class UpdateDrug : public QMainWindow
{
    Q_OBJECT

public:
    explicit UpdateDrug(QWidget *parent = nullptr);
    ~UpdateDrug();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    void init_udWin();
    Ui::UpdateDrug *ui;
};

#endif // UPDATEDRUG_H
