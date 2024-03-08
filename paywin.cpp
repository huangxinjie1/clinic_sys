#include "paywin.h"
#include "ui_paywin.h"

extern QString gb_recnum;

void PayWin::init_WIN(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DISTINCT PNAME,AFEES,DFEES,DRAFEES from bill where PNUM='"+gb_recnum+"'";
    qDebug()<<str1;
    if(query.exec(str1)){
        query.first();
        ui->label_3->setText(query.value(0).toString());
        ui->label_5->setText(query.value(1).toString());
        ui->label_7->setText(query.value(2).toString());
        ui->label_9->setText(query.value(3).toString());
    }else{
        QMessageBox::information(this,"提示","初始化失败!");
    }


}

void PayWin::sub_invent(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="update bill set INVENT=INVENT-COUNT where RECNUM='"+gb_recnum+"'";
    if(!query.exec(str1)){
        QMessageBox::information(this,"提示","药品不足!");
    }
}

void PayWin::change_stat(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="update consrecord set STATUS = '已支付' where RECNUM= '"+gb_recnum+"'";

    if(!query.exec(str1)){
        QMessageBox::information(this,"提示","支付失败!");
    }
}

PayWin::PayWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PayWin)
{
    ui->setupUi(this);
    init_WIN();
}

PayWin::~PayWin()
{
    delete ui;
}

void PayWin::on_pushButton_2_clicked()
{
    close();
}

void PayWin::on_pushButton_clicked()
{
    sub_invent();
    change_stat();
    close();
}
