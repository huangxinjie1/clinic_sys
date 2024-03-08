#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

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
#include "addroom.h"

namespace Ui {
class RoomManager;
}

class RoomManager : public QMainWindow
{
    Q_OBJECT

public:
    AddRoom *arw;
    explicit RoomManager(QWidget *parent = nullptr);
    ~RoomManager();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

private:
    void init_room();
    Ui::RoomManager *ui;
};

#endif // ROOMMANAGER_H
