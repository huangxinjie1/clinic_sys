#include "roommanager.h"
#include "ui_roommanager.h"

void RoomManager::init_room(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select * from room order by cast(RNUM as decimal )";
    qDebug()<<str1;
    if(query.exec(str1)){
        int rows=query.numRowsAffected();
        qDebug()<<rows;
        QSqlRecord res = query.record();
        int cols=res.count();
        qDebug()<<cols;
        QStandardItemModel *model=new QStandardItemModel();
        model->setColumnCount(cols);
        model->setHeaderData(0,Qt::Horizontal,("编号"));
        model->setHeaderData(1,Qt::Horizontal,("科室名"));
        model->setHeaderData(2,Qt::Horizontal,("科室人数"));
        model->setHeaderData(3,Qt::Horizontal,("科室电话"));
        model->setRowCount(rows);
        int i=0;
        while (query.seek(i)) {
                model->setItem(i,0,new QStandardItem(query.value(0).toString()));
                model->setItem(i,1,new QStandardItem(query.value(1).toString()));
                model->setItem(i,2,new QStandardItem(query.value(2).toString()));
                model->setItem(i,3,new QStandardItem(query.value(3).toString()));
                i++;
        }
        ui->tableView->setModel(model);
    }

}

RoomManager::RoomManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RoomManager)
{
    ui->setupUi(this);
    init_room();
}

RoomManager::~RoomManager()
{
    delete ui;
}

void RoomManager::on_pushButton_5_clicked()
{
    arw=new AddRoom(nullptr);
    arw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    arw->show();
}

void RoomManager::on_pushButton_clicked()
{
    close();
}

void RoomManager::on_pushButton_2_clicked()
{
    init_room();
}

void RoomManager::on_pushButton_6_clicked()
{
    if(ui->lineEdit->text()==""){
        QMessageBox::information(this,"提示","请输入编号以删除!");
    }else{
        QString rnum=ui->lineEdit->text();
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QSqlQuery query(db);
        QString str1="delete from room where RNUM = '"+rnum+"'";
        if(query.exec(str1)){
            QMessageBox::information(this,"提示","删除成功!");
        }

      }
}
