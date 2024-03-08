#include "drugmanager.h"
#include "ui_drugmanager.h"

QString drnum;

void DrugManager::init_DrugWin(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DRNUM, DENAME, DECATE, DEFEES, PHNUM, INVENT from  drug order by cast(DRNUM  as decimal )";
    qDebug()<<str1;
    if(query.exec(str1)){
        int rows=query.numRowsAffected();
        qDebug()<<rows;
        QSqlRecord res = query.record();
        int cols=res.count();
        qDebug()<<cols;
        QStandardItemModel *model=new QStandardItemModel();
        model->setColumnCount(cols);
        model->setHeaderData(0,Qt::Horizontal,("编号"));
        model->setHeaderData(1,Qt::Horizontal,("药品名"));
        model->setHeaderData(2,Qt::Horizontal,("药品种类"));
        model->setHeaderData(3,Qt::Horizontal,("单价"));
        model->setHeaderData(4,Qt::Horizontal,("药房编号"));
        model->setHeaderData(5,Qt::Horizontal,("库存"));
        model->setRowCount(rows);
        int i=0;
        while (query.seek(i)) {
                model->setItem(i,0,new QStandardItem(query.value(0).toString()));
                model->setItem(i,1,new QStandardItem(query.value(1).toString()));
                model->setItem(i,2,new QStandardItem(query.value(2).toString()));
                model->setItem(i,3,new QStandardItem(query.value(3).toString()));
                model->setItem(i,4,new QStandardItem(query.value(4).toString()));
                model->setItem(i,5,new QStandardItem(query.value(5).toString()));
                i++;
        }
        ui->tableView->setModel(model);
    }
}

DrugManager::DrugManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrugManager)
{
    ui->setupUi(this);
    init_DrugWin();
}

DrugManager::~DrugManager()
{
    delete ui;
}

void DrugManager::on_pushButton_2_clicked()
{
    adw=new AddDrug(nullptr);
    adw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    adw->show();
}

void DrugManager::on_pushButton_6_clicked()
{
    close();
}

void DrugManager::on_pushButton_clicked()
{
    bool flag1=false;
    if(ui->lineEdit->text()=="") flag1 =true;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    if(flag1){
        QString decate = ui->comboBox->currentText();
        QString str1="select DRNUM, DENAME, DECATE, DEFEES, PHNUM, INVENT from  drug where DECATE = '"+decate+"' order by cast(DRNUM  as decimal )";
        qDebug()<<str1;
        if(query.exec(str1)){
            int rows=query.numRowsAffected();
            qDebug()<<rows;
            QSqlRecord res = query.record();
            int cols=res.count();
            qDebug()<<cols;
            QStandardItemModel *model=new QStandardItemModel();
            model->setColumnCount(cols);
            model->setHeaderData(0,Qt::Horizontal,("编号"));
            model->setHeaderData(1,Qt::Horizontal,("药品名"));
            model->setHeaderData(2,Qt::Horizontal,("药品种类"));
            model->setHeaderData(3,Qt::Horizontal,("单价"));
            model->setHeaderData(4,Qt::Horizontal,("药房编号"));
            model->setHeaderData(5,Qt::Horizontal,("库存"));
            model->setRowCount(rows);
            int i=0;
            while (query.seek(i)) {
                    model->setItem(i,0,new QStandardItem(query.value(0).toString()));
                    model->setItem(i,1,new QStandardItem(query.value(1).toString()));
                    model->setItem(i,2,new QStandardItem(query.value(2).toString()));
                    model->setItem(i,3,new QStandardItem(query.value(3).toString()));
                    model->setItem(i,4,new QStandardItem(query.value(4).toString()));
                    model->setItem(i,5,new QStandardItem(query.value(5).toString()));
                    i++;
            }
            ui->tableView->setModel(model);
        }

    }else{
        QString drnum=ui->lineEdit->text();
        QString str1="select DRNUM, DENAME, DECATE, DEFEES, PHNUM, INVENT from  drug where DRNUM = '"+drnum+"'";
        qDebug()<<str1;
        if(query.exec(str1)){
            int rows=query.numRowsAffected();
            qDebug()<<rows;
            QSqlRecord res = query.record();
            int cols=res.count();
            qDebug()<<cols;
            QStandardItemModel *model=new QStandardItemModel();
            model->setColumnCount(cols);
            model->setHeaderData(0,Qt::Horizontal,("编号"));
            model->setHeaderData(1,Qt::Horizontal,("药品名"));
            model->setHeaderData(2,Qt::Horizontal,("药品种类"));
            model->setHeaderData(3,Qt::Horizontal,("单价"));
            model->setHeaderData(4,Qt::Horizontal,("药房编号"));
            model->setHeaderData(5,Qt::Horizontal,("库存"));
            model->setRowCount(rows);
            int i=0;
            while (query.seek(i)) {
                    model->setItem(i,0,new QStandardItem(query.value(0).toString()));
                    model->setItem(i,1,new QStandardItem(query.value(1).toString()));
                    model->setItem(i,2,new QStandardItem(query.value(2).toString()));
                    model->setItem(i,3,new QStandardItem(query.value(3).toString()));
                    model->setItem(i,4,new QStandardItem(query.value(4).toString()));
                    model->setItem(i,5,new QStandardItem(query.value(5).toString()));
                    i++;
            }
            ui->tableView->setModel(model);
        }
    }
}

void DrugManager::on_pushButton_3_clicked()
{

    if(ui->lineEdit->text()==""){
        QMessageBox::information(this,"提示","请输入要删除的编号!");
    }else{
        QString drnum=ui->lineEdit->text();
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QSqlQuery query(db);
        QString str1="delete from drug where DRNUM = '"+drnum+"'";
        if(query.exec(str1)){
            QMessageBox::information(this,"提示","删除成功!");
            init_DrugWin();
        }
    }
}

void DrugManager::on_pushButton_7_clicked()
{
    init_DrugWin();
}

void DrugManager::on_pushButton_4_clicked()
{
    if(ui->lineEdit->text()==""){
        QMessageBox::information(this,"提示","请输入编号!");
    }else{
       drnum=ui->lineEdit->text();
       udw=new UpdateDrug(nullptr);
       udw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
       udw->show();
    }
}

void DrugManager::on_pushButton_5_clicked()
{
    if(ui->lineEdit->text()==""){
        QMessageBox::information(this,"提示","请输入编号!");
    }else{
       drnum=ui->lineEdit->text();
       adsw=new AddDrugSum(nullptr);
       adsw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
       adsw->show();
    }
}
