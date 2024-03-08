#include "reservation.h"
#include "ui_reservation.h"

extern QString gp_dnum;
extern QString gs_pnum;

QString Reservation::getTime(){
    QString  curTime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    return curTime;
}

QString Reservation::getRoomNum(QString str){
    QString res;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select RNUM from doctor where DNUM = '"+str+"'";
    qDebug()<<str1;
    if(query.exec(str1)){
        query.first();
        res = query.value(0).toString();
    }
    else{
        QMessageBox::information(this,"提示","数据库查询失败!");
    }
    return res;
}

void Reservation::init_WIN(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DINFO,DNAME,DAGE,DPROF,DFEES from doctor where DNUM='"+gp_dnum+"'";
    qDebug()<<str1;
    if(query.exec(str1)){
        query.first();
        ui->textBrowser->setText(query.value(0).toString());
        ui->label_5->setText(query.value(1).toString());
        ui->label_7->setText(query.value(2).toString());
        ui->label_9->setText(query.value(3).toString());
        ui->label_11->setText(query.value(4).toString());
    }else{
        QMessageBox::information(this,"提示","界面初始化失败!");
    }
}

QString Reservation::getPrnum(){
    int temp=1;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select RENUM from regis";
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

Reservation::Reservation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Reservation)
{
    ui->setupUi(this);
    init_WIN();
}

Reservation::~Reservation()
{
    delete ui;
}

void Reservation::on_pushButton_2_clicked()
{
    bool flag1=false;
    if(ui->textEdit->toPlainText()=="") flag1=true;
    if(false){
        QMessageBox::information(this,"提示","请输入完整的信息!");
    }else{
        QString prnum=getPrnum();
        QString descri=ui->textEdit->toPlainText();
        QString rnum=getRoomNum(gp_dnum);
        QString ptime=getTime();
        QString staus="已挂号";
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QSqlQuery query(db);
        qDebug()<<"te"<<gs_pnum;
        QString str1="insert into regis value ('"+prnum+"','"+rnum+"','"+gp_dnum+"','"+gs_pnum+"','"+descri+"','"+ptime+"','"+staus+"')";
        qDebug()<<str1;
        if(query.exec(str1)){
            QMessageBox::information(this,"提示","挂号成功!");
        }
    }

}

void Reservation::on_pushButton_clicked()
{
    this->close();
}
