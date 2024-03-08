#include "updatedrug.h"
#include "ui_updatedrug.h"

extern QString drnum;
QString drname;
QString drcate;
QString drfees;
QString drsum;


void UpdateDrug::init_udWin(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DENAME, DECATE, DEFEES from  drug where DRNUM = '"+drnum+"'";
    if(query.exec(str1)){
        query.first();
        //qDebug()<<query.value(0).toString();
        //qDebug()<<query.value(1).toString();
        //qDebug()<<query.value(2).toString();
        drname=query.value(0).toString();
        drcate=query.value(1).toString();
        drfees=query.value(2).toString();
        ui->lineEdit->setText(drname);
        ui->lineEdit_2->setText(drfees);
        ui->comboBox->setCurrentText(drcate);
    }
}


UpdateDrug::UpdateDrug(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UpdateDrug)
{
    ui->setupUi(this);
    init_udWin();
}

UpdateDrug::~UpdateDrug()
{
    delete ui;
}

void UpdateDrug::on_pushButton_2_clicked()
{
    close();
}

void UpdateDrug::on_pushButton_clicked()
{
    bool flag1=false;
    QString dr_name=ui->lineEdit->text();
    QString dr_cate=ui->comboBox->currentText();
    QString dr_fees=ui->lineEdit_2->text();
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    if(dr_name!=drname){
        QString str1="update DRUG set DENAME ='"+dr_name+"' where DRNUM='"+drnum+"'";
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","药品名已更新!");
        }
    }
    if(dr_cate!=drcate){
        QString str1="update DRUG set DECATE ='"+dr_cate+"' where DRNUM='"+drnum+"'";
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","药品类别已更新!");
        }
    }
    if(dr_fees!=drfees){
        QString str1="update DRUG set DEFEES ='"+dr_fees+"' where DRNUM='"+drnum+"'";
        if(query.exec(str1)){
            query.first();
            flag1=true;
            QMessageBox::information(this,"提示","药品单价已更新!");
        }
    }
    if(flag1){
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        this->close();
    }else{
       QMessageBox::information(this,"提示","信息未更改!");
    }

}
