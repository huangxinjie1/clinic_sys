#include "diagnose.h"
#include "ui_diagnose.h"

extern QString gd_pnum;
extern QString gs_dnum;



QString Diagnose::getDate(){
    QString  curTime=QDate::currentDate().toString("yyyy-MM-dd");
    return curTime;
}

QString Diagnose::getMNum(){
    int temp=1;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1 ="select * from MEDRECORD";
    query.exec(str1);
    if(query.numRowsAffected()){
        query.last();
        temp=query.value(0).toInt();
        qDebug()<<temp;
        temp++;
    }
    qDebug()<<temp;
    return QString::number(temp);
}

void Diagnose::init_DWIN(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select PNAME,PAGE,PSEX,PTIME,PDISC from res_p_d where PNUM='"+gd_pnum+"'";
    qDebug()<<str1;
    if(query.exec(str1)){
        query.first();
        ui->label_3->setText(query.value(0).toString());
        ui->label_5->setText(query.value(1).toString());
        ui->label_7->setText(query.value(2).toString());
        ui->label_9->setText(query.value(3).toString());
        ui->textBrowser->setText(query.value(4).toString());
    }else{
        QMessageBox::information(this,"提示","初始化失败!");
    }
}

void Diagnose::ChangeStatus(QString str){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="update res_p_d set STAUS = '已就诊' where PNUM = '"+str+"'";
    qDebug()<<str1;
    if(!query.exec(str1)){
        QMessageBox::information(this,"提示","状态更新失败!");
    }
}

Diagnose::Diagnose(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Diagnose)
{
    ui->setupUi(this);
    init_DWIN();
    qDebug()<<"pnum"<<gd_pnum<<"dnum"<<gs_dnum;
}

Diagnose::~Diagnose()
{
    delete ui;
}

void Diagnose::on_pushButton_2_clicked()
{
    this->close();
}

void Diagnose::on_pushButton_clicked()
{
    bool flag1=false;
    if(ui->textEdit->toPlainText()=="") flag1=true;
    if(ui->textEdit_2->toPlainText()=="") flag1=true;
    if(flag1){
        QMessageBox::information(this,"提示","请输入完整的信息!");
    }else{
        QString rec_num=getMNum();
        QString rec_dnum=gs_dnum;
        QString rec_pnum=gd_pnum;
        QString rec_med=ui->textEdit->toPlainText();
        QString rec_date=getDate();
        QString rec_advavice=ui->textEdit_2->toPlainText();
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QSqlQuery query(db);
        QString str1="insert into medrecord value ('"+rec_num+"','"+rec_dnum+"','"+rec_pnum+"','"+rec_med+"','"+rec_advavice+"','"+rec_date+"')";
        qDebug()<<str1;
        if(query.exec(str1)){
            QMessageBox::information(this,"提示","诊断完成!");
            ChangeStatus(gd_pnum);
        }

    }
}
