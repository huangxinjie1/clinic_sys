#include "doctormanager.h"
#include "ui_doctormanager.h"

QString gd_num;


QString DoctorManager::FindRoom(QString str){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select RNAME from room where RNUM ='"+str+"'";
    query.exec(str1);
    query.first();
    return query.value(0).toString();
}

QString DoctorManager::getRnum(QString str){
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

void DoctorManager::DMT_init(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DNUM,DNAME,DSEX,DAGE,RNAME,DPROF,DSPC,DFEES from r_doc_acc";
    qDebug()<<str1;
    query.exec(str1);
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
    model->setHeaderData(4,Qt::Horizontal,("科室"));
    model->setHeaderData(5,Qt::Horizontal,("职称"));
    model->setHeaderData(6,Qt::Horizontal,("方向"));
    model->setHeaderData(7,Qt::Horizontal,("诊费"));
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
            i++;
    }
    ui->tableView->setModel(model);
}

void DoctorManager::DMC_init(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select RNAME from room";
    if(query.exec(str1)){
        while (query.next()) {
            ui->comboBox->addItem(query.value(0).toString());
        }

    }
    else{
        QMessageBox::information(this,"提示","初始化失败!");
    }
}

void DoctorManager::subPepleNum(QString str){
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

DoctorManager::DoctorManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DoctorManager)
{
    ui->setupUi(this);
    DMT_init();
    DMC_init();
}

DoctorManager::~DoctorManager()
{
    delete ui;
}

void DoctorManager::on_pushButton_2_clicked()
{
    adw=new AddDoctor(nullptr);
    adw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    adw->show();
}

void DoctorManager::on_pushButton_5_clicked()
{
    DMT_init();
    DMC_init();
}

void DoctorManager::on_pushButton_3_clicked()
{
    if(ui->lineEdit->text()==""){
        QMessageBox::information(this,"提示","请输入关键词!");
    }else{
         gd_num=ui->lineEdit->text();
         udw=new  UpdateDoctor(nullptr);
         udw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
         udw->show();
       }


}

void DoctorManager::on_pushButton_4_clicked()
{
    bool flag1=false;
    if(ui->lineEdit->text()=="") flag1 = true;
    QString str1=ui->lineEdit->text();
    if(flag1){
        QMessageBox::information(this,"提示","请输入关键词!");
    }
    else{
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QSqlQuery query(db);
        QString str2="delete from doctor where DNUM = '"+str1+"'";
        if(query.exec(str2)){
            query.finish();

            QMessageBox::information(this,"提示","删除成功!");
            ui->lineEdit->clear();
            DMT_init();
        }
    }
}

void DoctorManager::on_pushButton_clicked()
{
    if(ui->lineEdit->text()==""){
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QString d_room=ui->comboBox->currentText();
        QSqlQuery query(db);
        QString str1="select DNUM,DNAME,DSEX,DAGE,RNAME,DPROF,DSPC,DFEES from r_doc_acc where RNAME='"+d_room+"'";
        qDebug()<<str1;
        if(query.exec(str1)){
            int rows=query.numRowsAffected();
            QSqlRecord res = query.record();
            int cols=res.count();
            QStandardItemModel *model=new QStandardItemModel();
            model->setColumnCount(cols);
            model->setHeaderData(0,Qt::Horizontal,("编号"));
            model->setHeaderData(1,Qt::Horizontal,("姓名"));
            model->setHeaderData(2,Qt::Horizontal,("性别"));
            model->setHeaderData(3,Qt::Horizontal,("年龄"));
            model->setHeaderData(4,Qt::Horizontal,("科室"));
            model->setHeaderData(5,Qt::Horizontal,("职称"));
            model->setHeaderData(6,Qt::Horizontal,("方向"));
            model->setHeaderData(7,Qt::Horizontal,("诊费"));
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
                    i++;
            }
            ui->tableView->setModel(model);
        }else{
            QMessageBox::information(this,"提示","查询失败!");
        }
    }else{
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QString d_num=ui->lineEdit->text();
        QSqlQuery query(db);
        QString str1="select DNUM,DNAME,DSEX,DAGE,RNAME,DPROF,DSPC,DFEES from r_doc_acc where DNUM='"+d_num+"'";
        if(query.exec(str1)){
            int rows=query.numRowsAffected();
            QSqlRecord res = query.record();
            int cols=res.count();
            QStandardItemModel *model=new QStandardItemModel();
            model->setColumnCount(cols);
            model->setHeaderData(0,Qt::Horizontal,("编号"));
            model->setHeaderData(1,Qt::Horizontal,("姓名"));
            model->setHeaderData(2,Qt::Horizontal,("性别"));
            model->setHeaderData(3,Qt::Horizontal,("年龄"));
            model->setHeaderData(4,Qt::Horizontal,("科室"));
            model->setHeaderData(5,Qt::Horizontal,("职称"));
            model->setHeaderData(6,Qt::Horizontal,("方向"));
            model->setHeaderData(7,Qt::Horizontal,("诊费"));
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
                    i++;
            }
            ui->tableView->setModel(model);
        }
    }
}

void DoctorManager::on_pushButton_6_clicked()
{
    close();
}
