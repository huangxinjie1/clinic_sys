#ifndef ADDROOM_H
#define ADDROOM_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>
#include<QCryptographicHash>
#include<QString>

namespace Ui {
class AddRoom;
}

class AddRoom : public QMainWindow
{
    Q_OBJECT

public:    
    explicit AddRoom(QWidget *parent = nullptr);
    ~AddRoom();

private slots:
    QString sum_doc();
    QString sum_room();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddRoom *ui;
};

#endif // ADDROOM_H
