#include "adddrugsum.h"
#include "ui_adddrugsum.h"

extern QString drnum;

void AddDrugSum::init_adsWin(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DENAME, INVENT from  drug where DRNUM = '"+drnum+"'";
    if(query.exec(str1)){
        query.first();
        ui->label_2->setText(query.value(0).toString());
        ui->label_4->setText(query.value(1).toString());
    }
}

AddDrugSum::AddDrugSum(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddDrugSum)
{
    ui->setupUi(this);
    init_adsWin();
}

AddDrugSum::~AddDrugSum()
{
    delete ui;
}

void AddDrugSum::on_pushButton_2_clicked()
{
    close();
}

void AddDrugSum::on_pushButton_clicked()
{
    if(ui->lineEdit->text()==""){
        QMessageBox::information(this,"提示","信息为空!");
    }else{QString temp =ui->lineEdit->text();
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QSqlQuery query(db);
        QString str1="update DRUG set INVENT = INVENT + "+temp+" where DRNUM='"+drnum+"'";
        qDebug()<<str1;
        if(query.exec(str1)){
            QMessageBox::information(this,"提示","添加成功!");
        }}

}
