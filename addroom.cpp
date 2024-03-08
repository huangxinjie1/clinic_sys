#include "addroom.h"
#include "ui_addroom.h"



QString AddRoom::sum_room(){
    int temp=1;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select RNUM from room order by cast(RNUM as decimal )";
    query.exec(str1);
    if(query.numRowsAffected()){
        query.last();
        temp=query.value(0).toInt();
        qDebug()<<temp;
        temp++;
    }
    return QString::number(temp);
}

QString AddRoom::sum_doc(){ //计算医生人数,考虑到新建科室后再加入医生,所以科室人数初始为0,此函数弃用
    int temp=0;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select * from doctor";
    if(query.exec(str1)){
        temp=query.numRowsAffected();
        temp++;
    }
    return QString::number(temp);
}

AddRoom::AddRoom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddRoom)
{
    ui->setupUi(this);
}

AddRoom::~AddRoom()
{
    delete ui;
}

void AddRoom::on_pushButton_clicked()
{
    bool flag1=false;
    if(ui->lineEdit->text()=="")flag1=true;
    if(ui->lineEdit_2->text()=="")flag1=true;
    if(flag1){
        QMessageBox::about(NULL,"提示","请输入信息!");
        return;
    }
    else{
        QString r_num=sum_room();
        QString r_name=ui->lineEdit->text();
        QString r_tel=ui->lineEdit_2->text();
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QSqlQuery query(db);
        QString str1="insert into room value ('"+r_num+"','"+r_name+"','0','"+r_tel+"')";
        if(query.exec(str1)){
            QMessageBox::information(this,"提示","插入成功!");
        }
        else{
            QMessageBox::information(this,"提示","插入失败!");
        }
    }
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    this->close();
}

void AddRoom::on_pushButton_2_clicked()
{
    close();
}
