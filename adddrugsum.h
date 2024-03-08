#ifndef ADDDRUGSUM_H
#define ADDDRUGSUM_H

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
#include<QList>

namespace Ui {
class AddDrugSum;
}

class AddDrugSum : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddDrugSum(QWidget *parent = nullptr);
    ~AddDrugSum();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    void init_adsWin();
    Ui::AddDrugSum *ui;
};

#endif // ADDDRUGSUM_H
