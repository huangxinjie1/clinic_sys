#include "patientmanager.h"
#include "ui_patientmanager.h"
extern QString gs_pnum;

void patientmanager::init_WIN(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select PNUM,PNAME,PAGE,PSEX,PBIRTH,PID,PSID,PTEL,PETEL from pat";
    query.exec(str1);
    query.first();
    qDebug()<<str1;
    int rows=query.numRowsAffected();
    qDebug()<<rows;
    QSqlRecord res = query.record();
    int cols=res.count();
    qDebug()<<cols;
    QStandardItemModel *model=new QStandardItemModel();
    model->setColumnCount(cols);
    model->setHeaderData(0,Qt::Horizontal,("编号"));
    model->setHeaderData(1,Qt::Horizontal,("姓名"));
    model->setHeaderData(2,Qt::Horizontal,("性别"));
    model->setHeaderData(3,Qt::Horizontal,("年龄"));
    model->setHeaderData(4,Qt::Horizontal,("生日"));
    model->setHeaderData(5,Qt::Horizontal,("身份证号"));
    model->setHeaderData(6,Qt::Horizontal,("社保卡号"));
    model->setHeaderData(7,Qt::Horizontal,("电话"));
    model->setHeaderData(8,Qt::Horizontal,("紧急联系人"));
    model->setRowCount(rows);
    int i=0;
    while (query.seek(i)) {
            model->setItem(i,0,new QStandardItem(query.value(0).toString()));
            model->setItem(i,1,new QStandardItem(query.value(1).toString()));
            model->setItem(i,2,new QStandardItem(query.value(2).toString()));
            model->setItem(i,3,new QStandardItem(query.value(3).toString()));
            model->setItem(i,4,new QStandardItem(query.value(4).toString()));
            model->setItem(i,5,new QStandardItem(query.value(5).toString()));
            model->setItem(i,6,new QStandardItem(query.value(6).toString()));
            model->setItem(i,7,new QStandardItem(query.value(7).toString()));
            model->setItem(i,8,new QStandardItem(query.value(8).toString()));
            i++;
    }
    ui->tableView->setModel(model);
}

patientmanager::patientmanager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::patientmanager)
{
    ui->setupUi(this);
    init_WIN();
}

patientmanager::~patientmanager()
{
    delete ui;
}

void patientmanager::on_pushButton_2_clicked()
{
    apw=new AddPatient(nullptr);
    apw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    apw->show();
}

void patientmanager::on_pushButton_3_clicked()
{
    if(ui->lineEdit->text()==""){
        QMessageBox::information(this,"提示","请输入患者编号!");
    }else{
        gs_pnum=ui->lineEdit->text();
        udw=new UpdatePatient(nullptr);
        udw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
        udw->show();
    }
}

void patientmanager::on_pushButton_clicked()
{
    ui->lineEdit->clear();
    close();
}

void patientmanager::on_pushButton_5_clicked()
{
    init_WIN();
}

void patientmanager::on_pushButton_4_clicked()
{
    if(ui->lineEdit->text()==""){
         QMessageBox::information(this,"提示","请输入患者编号!");
    }else{
        QString pnum=ui->lineEdit->text();
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QSqlQuery query(db);
        QString str1="delete from pat where PNUM = '"+pnum+"'";
        if(query.exec(str1)){
            QMessageBox::information(this,"提示","删除成功!");
            ui->lineEdit->clear();
            init_WIN();
        }
    }
}
