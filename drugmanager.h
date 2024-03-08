#ifndef DRUGMANAGER_H
#define DRUGMANAGER_H

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
#include "adddrug.h"
#include "updatedrug.h"
#include "adddrugsum.h"

namespace Ui {
class DrugManager;
}

class DrugManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrugManager(QWidget *parent = nullptr);
    ~DrugManager();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    AddDrug *adw;
    UpdateDrug *udw;
    AddDrugSum *adsw;
    void init_DrugWin();
    Ui::DrugManager *ui;
};

#endif // DRUGMANAGER_H
