#include "addpatient.h"
#include "ui_addpatient.h"

QString AddPatient::FindPNUM(){
    int temp=1;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select PNUM from pat order by cast(PNUM as decimal )";
    query.exec(str1);
    if(query.numRowsAffected()){
        query.last();
        temp=query.value(0).toInt();
        qDebug()<<temp;
        temp++;
    }
    return QString::number(temp);
}

QString AddPatient::strToMd5(QString str){
    QString strMd5;
    QByteArray qba;
    qba = QCryptographicHash::hash(str.toLatin1(),QCryptographicHash::Md5);
    strMd5.append(qba.toHex());
    return strMd5;
}

bool AddPatient::IsAccExsis(QString str){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select * from p_account where U_NAME='"+str+"'and PNUM IS NULL";
    qDebug()<<str1;
    query.exec(str1);
    qDebug()<<query.first();
    if(query.first()){
        return true;
    }
    else return false;

}

AddPatient::AddPatient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddPatient)
{
    ui->setupUi(this);
}

AddPatient::~AddPatient()
{
    delete ui;
}

void AddPatient::on_pushButton_clicked()
{
    flag1=false;
    if(ui->lineEdit->text()=="")flag1=true;
    if(ui->lineEdit_2->text()=="")flag1=true;
    if(flag1){
        QMessageBox::about(NULL,"提示","请输入账号密码!");
        return;
    }
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select * from p_account where U_NAME='"+ui->lineEdit->text()+"'and PNUM IS NOT NULL";
    qDebug()<<str1;
    //qDebug()<<query.first();
    query.exec(str1);
    if(query.first())
    {
        QMessageBox::information(this,"提示","用户名重复");
        return;
    }

}

void AddPatient::on_pushButton_2_clicked()
{
    flag1=false;flag2=false;
    if(ui->lineEdit->text()=="")flag1=true;
    if(ui->lineEdit_2->text()=="")flag1=true;
    if(ui->lineEdit_3->text()=="")flag1=true;
    if(ui->lineEdit_4->text()=="")flag1=true;
    if(ui->lineEdit_5->text()=="")flag1=true;
    if(ui->lineEdit_6->text()=="")flag1=true;
    if(ui->lineEdit_7->text()=="")flag1=true;
    if(ui->lineEdit_8->text()=="")flag1=true;
    if(flag1){
        QMessageBox::about(NULL,"提示","请输入信息!");
        return;
    }
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select * from P_ACCOUNT where U_NAME='"+ui->lineEdit->text()+"' and PNUM IS NOT NULL";
    //qDebug()<<str1;
    //qDebug()<<query.first();
    query.exec(str1);
    if(query.first()){
        flag2=true;
        QMessageBox::information(this,"提示","用户名重复");
        return;
    }
    if(!flag1&&!flag2){
        QString p_accname=ui->lineEdit->text();
        QString p_pass=strToMd5(ui->lineEdit_2->text());
        QString p_name=ui->lineEdit_3->text();
        QString p_sex=ui->comboBox->currentText();
        QString p_age=ui->lineEdit_4->text();
        QString p_birth=ui->lineEdit_9->text()+"-"+ui->lineEdit_10->text()+"-"+ui->lineEdit_11->text();
        QString p_tel=ui->lineEdit_5->text();
        QString p_mtel=ui->lineEdit_6->text();
        QString p_id=ui->lineEdit_7->text();
        QString p_sid=ui->lineEdit_8->text();
        QString p_num=FindPNUM();
        QString str2="insert into pat value('"+p_num+"','"+p_name+"','"+p_sex+"',"+p_age+",'"+p_birth+"','"+p_id+"','"+p_sid+"','"+p_tel+"','"+p_mtel+"')";
        qDebug()<<str2;
        query.first();
        query.exec(str2);
        if(IsAccExsis(p_accname)){
            query.first();
            QString str3="update p_account set PNUM='"+p_num+"' where U_NAME='"+p_accname+"'";
            qDebug()<<str3;
            query.exec(str3);
        }
        else{
            query.first();
            QString str4="insert into p_account value ('患者','"+p_accname+"','"+p_pass+"','"+p_num+"')";
            qDebug()<<str4;
            if(query.exec(str4)){
                QMessageBox::information(this,"提示","添加成功!");
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
                ui->lineEdit_3->clear();
                ui->lineEdit_4->clear();
                ui->lineEdit_5->clear();
                ui->lineEdit_6->clear();
                ui->lineEdit_7->clear();
                ui->lineEdit_8->clear();
                ui->lineEdit_9->clear();
                ui->lineEdit_10->clear();
                ui->lineEdit_11->clear();
            }
            else{
                QMessageBox::information(this,"提示","添加失败!");
            }
        }

    }
    this->close();
}

void AddPatient::on_pushButton_3_clicked()
{
    close();
}
