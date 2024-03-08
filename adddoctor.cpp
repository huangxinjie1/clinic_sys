#include "adddoctor.h"
#include "ui_adddoctor.h"

void AddDoctor::init_doc(){
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

void AddDoctor::AddToRoom(QString str){
    int temp =0;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select PEUPLE from room where RNUM = '"+str+"'";
    qDebug()<<str1;
    if(query.exec(str1)){
        query.first();
        temp=query.value(0).toInt();
        temp++;
        qDebug()<<temp;
        QString str2="update room set PEUPLE="+QString::number(temp)+" where RNUM = '"+str+"'";
        if(query.exec(str2)){

        }else{
            QMessageBox::information(this,"提示","更新失败!");
        }
    }else{
        QMessageBox::information(this,"提示","数据库查询失败!");
    }
}

QString AddDoctor::FindNUM(){
    int temp=1;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DNUM from doctor order by CAST(DNUM AS DECIMAL)";
    query.exec(str1);
    if(query.numRowsAffected()){
        query.last();
        temp=query.value(0).toInt();
        qDebug()<<temp;
        temp++;
    }
    return QString::number(temp);
}

QString AddDoctor::FindRNUM(QString str){
    QString res;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select RNUM from room where RNAME = '"+str+"'";
    if(query.exec(str1)){
        query.first();
        res = query.value(0).toString();
    }
    else{
        QMessageBox::information(this,"提示","数据库查询失败!");
    }
    return res;
}

bool AddDoctor::IsInfoNull(){
    bool flag1=false;
    if(ui->lineEdit->text()=="")flag1=true;
    if(ui->lineEdit_2->text()=="")flag1=true;
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

QString AddDoctor::strToMd5(QString str){
    QString strMd5;
    QByteArray qba;
    qba = QCryptographicHash::hash(str.toLatin1(),QCryptographicHash::Md5);
    strMd5.append(qba.toHex());
    return strMd5;
}

bool AddDoctor::IsAccExsis(QString str){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select * from d_account where U_NAME='"+str+"'and PNUM IS NULL";
    qDebug()<<str1;
    query.exec(str1);
    qDebug()<<query.first();
    if(query.first()){
        return true;
    }
    else return false;

}

bool AddDoctor::IsAccRep(QString str){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select * from d_account where U_NAME='"+str+"'and PNUM IS NOT NULL";
    query.exec(str1);
    if(query.first()){
        QMessageBox::information(this,"提示","用户名重复!");
        return true;
    }
    else return false;
}


AddDoctor::AddDoctor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddDoctor)
{
    ui->setupUi(this);
    init_doc();
}

AddDoctor::~AddDoctor()
{
    delete ui;
}

void AddDoctor::on_pushButton_clicked()
{
    bool flag1=false;
    if(ui->lineEdit->text()=="")flag1=true;
    if(ui->lineEdit_2->text()=="")flag1=true;
    if(IsAccRep(ui->lineEdit->text()));
    if(flag1){
        QMessageBox::information(this,"提示","请输入账户密码!");
    }

}

void AddDoctor::on_pushButton_2_clicked()
{
    QString d_num=FindNUM();
    QString d_uname=ui->lineEdit->text();
    QString d_pass=strToMd5(ui->lineEdit_2->text());
    QString d_name=ui->lineEdit_3->text();
    QString d_sex=ui->comboBox->currentText();
    QString d_age=ui->lineEdit_4->text();
    QString d_rnum=FindRNUM(ui->comboBox_2->currentText());
    QString d_pre=ui->lineEdit_5->text();
    QString d_spc=ui->lineEdit_6->text();
    QString d_fees=ui->lineEdit_7->text();
    QString d_info=ui->textEdit->toPlainText();
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);

    if(IsAccRep(d_uname)){

    }
    else if(!IsInfoNull()){
        QString str1="insert into doctor value ('"+d_num+"',"+d_age+",'"+d_name+"','"+d_sex+"','"+d_rnum+"','"+d_spc+"','"+d_pre+"','"+d_info+"',"+d_fees+")";
        qDebug()<<str1;
        if(query.exec(str1)){
        }
        else{
          QMessageBox::information(this,"提示","数据库插入失败!");
        }
        if(IsAccExsis(d_uname)){
             query.first();
             QString str2="update d_account set PNUM='"+d_num+"' where U_NAME='"+d_uname+"'";
             if(query.exec(str2)){

             }
             else{
                QMessageBox::information(this,"提示","数据库修改失败!");
                return;
             }

         }
         else{
             query.first();
             QString str3="insert into d_account value ('医生','"+d_uname+"','"+d_pass+"','"+d_num+"')";
             if(query.exec(str3)){
                 AddToRoom(d_rnum);
                 QMessageBox::information(this,"提示","添加成功!");
                 ui->lineEdit->clear();
                 ui->lineEdit_2->clear();
                 ui->lineEdit_3->clear();
                 ui->lineEdit_4->clear();
                 ui->lineEdit_5->clear();
                 ui->lineEdit_6->clear();
                 ui->lineEdit_7->clear();
                 ui->textEdit->clear();
                 this->close();
             }
             else{
                 QMessageBox::information(this,"提示","添加失败!");
             }
         }
    }
}

void AddDoctor::on_pushButton_3_clicked()
{
    close();
}
