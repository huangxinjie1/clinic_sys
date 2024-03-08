#ifndef RESERVATION_H
#define RESERVATION_H

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
#include<QDateTime>

namespace Ui {
class Reservation;
}

class Reservation : public QMainWindow
{
    Q_OBJECT

public:
    explicit Reservation(QWidget *parent = nullptr);
    ~Reservation();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    QString getTime();
    QString getRoomNum(QString str);
    QString getPrnum();
    void init_WIN();
    Ui::Reservation *ui;
};

#endif // RESERVATION_H
