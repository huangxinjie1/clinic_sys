#ifndef PAYWIN_H
#define PAYWIN_H

#include <QMainWindow>
#include<QStandardItemModel>
#include<QStandardItem>
#include<QTableView>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlRecord>
#include<QMessageBox>
#include<QDebug>

namespace Ui {
class PayWin;
}

class PayWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit PayWin(QWidget *parent = nullptr);
    ~PayWin();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    void sub_invent();
    void init_WIN();
    void change_stat();
    Ui::PayWin *ui;
};

#endif // PAYWIN_H
