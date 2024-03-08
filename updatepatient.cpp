#include "updatepatient.h"
#include "ui_updatepatient.h"

extern QString gs_pnum;

QString puname;
QString p_pass;
QString pname;
QString psex;
QString page;
QStringList pbirthlist;
QString pbirth;
QString ptel;
QString petel;
QString pid;
QString psid;

QString UpdatePatient::strToMd5(QString str){
    QString strMd5;
    QByteArray qba;
    qba = QCryptographicHash::hash(str.toLatin1(),QCryptographicHash::Md5);
    strMd5.append(qba.toHex());
    return strMd5;
}

void UpdatePatient::init_UpPWin(){  
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select U_NAME from p_account where PNUM='"+gs_pnum+"'";
    if(query.exec(str1)){
        query.first();
        puname=query.value(0).toString();
        ui->lineEdit->setText(puname);
    }else{
        QMessageBox::information(this,"提示","用户名初始化失败!");
    }
    QString str2="select PNAME,PSEX,PAGE,PBIRTH,PTEL,PETEL,PID,PSID from PAT where PNUM='"+gs_pnum+"'";
    if(query.exec(str2)){
        query.first();
        pname=query.value(0).toString();
        psex=query.value(1).toString();
        page=query.value(2).toString();
        pbirthlist=query.value(3).toString().split('-');
        ptel=query.value(4).toString();
        petel=query.value(5).toString();
        pid=query.value(6).toString();
        psid=query.value(7).toString();
        ui->lineEdit_3->setText(pname);
        ui->comboBox->setCurrentText(psex);
        ui->lineEdit_4->setText(page);
        //qDebug()<<pbirthlist;
        ui->lineEdit_5->setText(ptel);
        ui->lineEdit_6->setText(petel);
        ui->lineEdit_7->setText(pid);
        ui->lineEdit_8->setText(psid);
        ui->lineEdit_9->setText(pbirthlist[0]);
        ui->lineEdit_10->setText(pbirthlist[1]);
        ui->lineEdit_11->setText((pbirthlist[2]));
        pbirth=pbirthlist[0]+"-"+pbirthlist[1]+"-"+pbirthlist[2];
    }
}

UpdatePatient::UpdatePatient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UpdatePatient)
{
    ui->setupUi(this);
    init_UpPWin();
}

UpdatePatient::~UpdatePatient()
{
    delete ui;
}

void UpdatePatient::on_pushButton_clicked()
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
    if(puname!=ui->lineEdit->text()){
        flag1=false;
        QMessageBox::information(this,"提示","用户名不可更改!");
    }
    if(flag1){
        QString new_pass=strToMd5(ui->lineEdit_2->text());
        QString str1="update p_account set U_PASS='"+new_pass+"' where U_NAME='"+puname+"'";
        if(query.exec(str1)){
            query.first();
            QMessageBox::information(this,"提示","密码已经更新!");
        }
    }


}

void UpdatePatient::on_pushButton_2_clicked()
{
    bool flag1=false;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString p_pname=ui->lineEdit_3->text();
    QString p_psex=ui->comboBox->currentText();
    QString p_page=ui->lineEdit_4->text();
    QString p_ptel=ui->lineEdit_5->text();
    QString p_petel=ui->lineEdit_6->text();
    QString p_pid=ui->lineEdit_7->text();
    QString p_psid=ui->lineEdit_8->text();
    QString p_pbirth=pbirthlist[0]+"-"+pbirthlist[1]+"-"+pbirthlist[2];
    if(p_pname!=pname){
        QString str1="update PAT set PNAME ='"+p_pname+"' where PNUM='"+gs_pnum+"'";
        qDebug()<<str1;
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","姓名已更新!");
        }
    }
    if(p_psex!=psex){
        QString str1="update pat set PSEX ='"+p_psex+"' where PNUM='"+gs_pnum+"'";
        qDebug()<<str1;
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","性别已更新!");
        }
    }
    if(p_page!=page){
        QString str1="update pat set PAGE ='"+p_page+"' where PNUM='"+gs_pnum+"'";
        qDebug()<<str1;
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","年龄已更新!");
        }
    }
    if(p_pbirth!=pbirth){
        QString str1="update pat set PBIRTH ='"+p_pbirth+"' where PNUM='"+gs_pnum+"'";
        qDebug()<<str1;
        qDebug()<<str1;
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","出生日期已更新!");
        }
    }
    if(p_ptel!=ptel){
        QString str1="update pat set PTEl ='"+p_ptel+"' where PNUM='"+gs_pnum+"'";
        qDebug()<<str1;
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","电话已更新!");
        }
    }
    if(p_petel!=petel){
        QString str1="update pat set PETEL ='"+p_petel+"' where PNUM='"+gs_pnum+"'";
        qDebug()<<str1;
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","紧急联系人已更新!");
        }
    }
    if(p_pid!=pid){
        QString str1="update pat set PID ='"+p_pid+"' where PNUM='"+gs_pnum+"'";
        qDebug()<<str1;
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","身份证号已更新!");
        }
    }
    if(p_psid!=psid){
        QString str1="update pat set PSID ='"+p_psid+"' where PNUM='"+gs_pnum+"'";
        qDebug()<<str1;
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","社保卡号已更新!");
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
        ui->lineEdit_9->clear();
        ui->lineEdit_8->clear();
        ui->lineEdit_10->clear();
        ui->lineEdit_11->clear();
        this->close();
    }else{
       QMessageBox::information(this,"提示","信息未更改!");
    }

}

void UpdatePatient::on_pushButton_3_clicked()
{
    close();
}
