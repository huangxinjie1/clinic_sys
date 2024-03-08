#include "updatedoctor.h"
#include "ui_updatedoctor.h"

extern QString gd_num;

QString duname;
QString dname;
QString dsex;
QString dage;
QString rname;
QString dpre;
QString dspc;
QString dfees;
QString dinfo;
QString rnum;

QString UpdateDoctor::strToMD5(QString str){
    QString strMd5;
    QByteArray qba;
    qba = QCryptographicHash::hash(str.toLatin1(),QCryptographicHash::Md5);
    strMd5.append(qba.toHex());
    return strMd5;
}

QString UpdateDoctor::FormatRegu(QString str){
    QString res=str;
    QChar h0('\0'); // 使用构造函数创建空字符;
    res.replace(h0,"");
    return res;
}

void UpdateDoctor::Updcom_init(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select RNAME from room";
    if(query.exec(str1)){
        while (query.next()) {
            ui->comboBox_2->addItem(query.value(0).toString());
        }

    }
    else{
        QMessageBox::information(this,"提示","初始化失败!");
    }
}

void UpdateDoctor::UpDW_init(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
          QMessageBox::information(this,"错误","数据库连接失败!");
     }
   QSqlQuery query(db);
   QString str1="select U_NAME,DNAME,DSEX,DAGE,RNAME,DPROF,DSPC,DFEES,DINFO,RNUM from r_doc_acc where DNUM='"+gd_num+"'";
   qDebug()<<str1<<"初始化";
   if(query.exec(str1)){
        query.first();
        duname=query.value(0).toString();
        dname=query.value(1).toString();
        dsex=query.value(2).toString();
        dage=query.value(3).toString();
        rname=query.value(4).toString();
        dpre=query.value(5).toString();
        dspc=query.value(6).toString();
        dfees=query.value(7).toString();
        dinfo=FormatRegu(query.value(8).toString());
        rnum=query.value(9).toString();
        qDebug()<<dinfo<<"简介";
   }
   ui->lineEdit->setText(duname);
   ui->lineEdit_3->setText(dname);
   ui->comboBox->setCurrentText(dsex);
   ui->lineEdit_4->setText(dage);
   ui->lineEdit_5->setText(dpre);
   ui->lineEdit_6->setText(dspc);
   ui->lineEdit_7->setText(dfees);
   ui->textEdit->setText(dinfo);
   Updcom_init();
}

QString UpdateDoctor::getRNum(QString str){
   QString res="0";
   QSqlDatabase db=QSqlDatabase::database();
   if(!db.open()){
        QMessageBox::information(this,"错误","数据库连接失败!");
     }
   QSqlQuery query(db);
    QString str1="select RNUM from room where RNAME='"+str+"'";
    if(query.exec(str1)){
        query.first();
        res=query.value(0).toString();
    }
    return res;
}

void UpdateDoctor::AddPepleNum(QString str){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
      }
    QSqlQuery query(db);
    QString str1="update room set PEUPLE =PEUPLE+1 where RNUM='"+str+"'";
    if(!query.exec(str1)){
        QMessageBox::information(this,"提示","更新失败");
    }
}

void UpdateDoctor::SubPepleNUm(QString str){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
      }
    QSqlQuery query(db);
    QString str1="update room set PEUPLE =PEUPLE-1 where RNUM='"+str+"'";
    if(!query.exec(str1)){
        QMessageBox::information(this,"提示","更新失败");
    }
}

bool UpdateDoctor::IsInfoNull(){
    bool flag1=false;
    if(ui->lineEdit_3->text()=="")flag1=true;
    if(ui->lineEdit_4->text()=="")flag1=true;
    if(ui->lineEdit_5->text()=="")flag1=true;
    if(ui->lineEdit_6->text()=="")flag1=true;
    if(ui->lineEdit_7->text()=="")flag1=true;
    if(ui->textEdit->toPlainText()=="")flag1=true;
    if(flag1){
         QMessageBox::information(this,"提示","请输入完整的信息!");
    }
    return flag1;

}

UpdateDoctor::UpdateDoctor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UpdateDoctor)
{
    ui->setupUi(this);
    UpDW_init();
    //qDebug()<<d_num;
}

UpdateDoctor::~UpdateDoctor()
{
    delete ui;

}


void UpdateDoctor::on_pushButton_clicked()
{
    bool flag1=false;
    if(!IsInfoNull()){

    }
    QString d_name=ui->lineEdit_3->text();
    QString d_sex=ui->comboBox->currentText();
    QString d_age=ui->lineEdit_4->text();
    QString d_rname=ui->comboBox_2->currentText();
    QString d_pre=ui->lineEdit_5->text();
    QString d_spc=ui->lineEdit_6->text();
    QString d_fees=ui->lineEdit_7->text();
    QString d_info=ui->textEdit->toPlainText();
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    if(d_name!=dname){
        QString str1="update doctor set DNAME ='"+dname+"' where DNUM='"+gd_num+"'";
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","姓名已更新!");
        }

    }
    if(d_sex!=dsex){
        QString str1="update doctor set DSEX ='"+d_sex+"' where DNUM='"+gd_num+"'";
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","姓名已更新!");
        }

    }
    if(d_age!=dage){
        QString str1="update doctor set DAGE ='"+dage+"' where DNUM='"+gd_num+"'";
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","年龄已更新!");
        }
    }
    if(d_pre!=dpre){
        QString str1="update doctor set DPROF ='"+d_pre+"' where DNUM='"+gd_num+"'";
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","职称已更新!");
        }
    }
    if(d_spc!=dspc){
        QString str1="update doctor set DSPC ='"+d_spc+"' where DNUM='"+gd_num+"'";
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","方向已更新!");
        }
    }
    if(d_fees!=dfees){
        QString str1="update doctor set DFEES ='"+d_fees+"' where DNUM='"+gd_num+"'";
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","诊费已更新!");
        }
    }
    if(d_info!=dinfo){
        QString str1="update doctor set DINFO ='"+d_info+"' where DNUM='"+gd_num+"'";
        qDebug()<<str1;
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","简介已更新!");
        }
    }
    if(d_rname!=rname){
        QString d_newrnum=getRNum(d_rname);
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QSqlQuery query(db);
        QString str1="update doctor set RNUM ='"+d_newrnum+"' where DNUM='"+gd_num+"'";
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","简介已更新!");
            AddPepleNum(d_newrnum);
            SubPepleNUm(rnum);
        }

    }

    if(flag1){
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->textEdit->clear();
        this->close();
    }else{
       QMessageBox::information(this,"提示","信息未更改!");
    }

}

void UpdateDoctor::on_pushButton_3_clicked()
{
    close();
}

void UpdateDoctor::on_pushButton_2_clicked()
{
    bool flag1=true;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    if(ui->lineEdit_2->text()==""){
        flag1=false;
        QMessageBox::information(this,"提示","密码为空!");
    }
    if(duname!=ui->lineEdit->text()){
        flag1=false;
        QMessageBox::information(this,"提示","用户名不可更改!");
    }
    if(flag1){
        QString new_pass=strToMD5(ui->lineEdit_2->text());
        QString str1="update d_account set U_PASS='"+new_pass+"' where U_NAME='"+duname+"'";
        if(query.exec(str1)){
            query.first();
            QMessageBox::information(this,"提示","密码已经更新!");
        }
    }else{
        QMessageBox::information(this,"提示","密码未更新!");
    }
}
