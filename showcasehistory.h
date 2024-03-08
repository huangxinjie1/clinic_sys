#ifndef SHOWCASEHISTORY_H
#define SHOWCASEHISTORY_H

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

namespace Ui {
class ShowCaseHistory;
}

class ShowCaseHistory : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowCaseHistory(QWidget *parent = nullptr);
    ~ShowCaseHistory();

private slots:
    void on_pushButton_clicked();

private:
    void show_info();
    Ui::ShowCaseHistory *ui;
};

#endif // SHOWCASEHISTORY_H
