#include "doctorwindow.h"
#include "ui_doctorwindow.h"

extern QString gs_dnum;
extern QString gd_pnum;


void DoctorWindow::init_DWT(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select RENUM,PNAME,PAGE,PSEX,PDISC,PTEL,PETEL,PTIME,STAUS from res_p_d where DNUM='"+gs_dnum+"'";
    query.exec(str1);
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
    model->setHeaderData(2,Qt::Horizontal,("年龄"));
    model->setHeaderData(3,Qt::Horizontal,("性别"));
    model->setHeaderData(4,Qt::Horizontal,("症状"));
    model->setHeaderData(5,Qt::Horizontal,("电话"));
    model->setHeaderData(6,Qt::Horizontal,("紧急联系人"));
    model->setHeaderData(7,Qt::Horizontal,("时间"));
    model->setHeaderData(8,Qt::Horizontal,("状态"));
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

QString DoctorWindow::getPnum(QString str){
    QString res;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select PNUM from res_p_d where RENUM = '"+str+"'";
    if(query.exec(str1)){
        query.first();
        res=query.value(0).toString();
    }
    return res;
}

bool DoctorWindow::isDia(QString str){  //判断医生是否诊断
    bool flag=false;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select STAUS from res_p_d where RENUM = '"+str+"'";
    if(query.exec(str1)){
        query.first();
        if(query.value(0)=="已就诊"){
           flag=true;
        }
    }
    return flag;
}

bool DoctorWindow::isPres(QString str){ //判断医生是否开处方
    bool flag=false;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select STAUS from res_p_d where RENUM = '"+str+"'";
    qDebug()<<str1;
    if(query.exec(str1)){
        query.first();
        if(query.value(0)=="已开处方"){
           flag=true;
        }
    }
    return flag;
}

DoctorWindow::DoctorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DoctorWindow)
{
    ui->setupUi(this);
    init_DWT();

}

DoctorWindow::~DoctorWindow()
{
    delete ui;
}

void DoctorWindow::on_pushButton_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select PNUM,PNAME,PAGE,PSEX,PDISC,PTEL,PETEL,PTIME,STAUS from res_p_d where STAUS='已挂号' and DNUM='"+gs_dnum+"'";
    query.exec(str1);
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
    model->setHeaderData(2,Qt::Horizontal,("年龄"));
    model->setHeaderData(3,Qt::Horizontal,("性别"));
    model->setHeaderData(4,Qt::Horizontal,("症状"));
    model->setHeaderData(5,Qt::Horizontal,("电话"));
    model->setHeaderData(6,Qt::Horizontal,("紧急联系人"));
    model->setHeaderData(7,Qt::Horizontal,("时间"));
    model->setHeaderData(8,Qt::Horizontal,("状态"));
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


void DoctorWindow::on_pushButton_2_clicked()
{
    bool flag1=false; bool flag2=true;
    if(ui->lineEdit->text()=="") flag1 = true;
    if(flag1){
        QMessageBox::information(this,"提示","请输入关键词!");
    }
    else{
        QString recnum=ui->lineEdit->text();
        gd_pnum=getPnum(recnum);
        if(isDia(recnum)){
            flag2=false;
            QMessageBox::information(this,"提示","该患者已经就诊!");
        }
        if(isPres(recnum)){
            flag2=false;
            QMessageBox::information(this,"提示","该患者已开处方!");
        }

    }

    if(flag2&&!flag1){
        dgw=new Diagnose(nullptr);
        dgw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
        dgw->show();
    }

}

void DoctorWindow::on_pushButton_3_clicked()
{
    bool flag1=false;
    bool flag2=true;
    if(ui->lineEdit->text()=="") flag1 = true;
    if(flag1){
        QMessageBox::information(this,"提示","请输入关键词!");
    }
    else{
        QString recnum=ui->lineEdit->text();
        gd_pnum=getPnum(recnum);
        qDebug()<<gd_pnum;
        if(!isDia(recnum)){
            flag2=false;
            QMessageBox::information(this,"提示","该患者还未诊断!");
        }
        if(isPres(recnum)){
            flag2=false;
            QMessageBox::information(this,"提示","该患者已经开过处方!");
        }

    }
    if(flag2){
        apw=new AddPrescription(nullptr);
        apw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
        apw->show();
    }
}

void DoctorWindow::on_pushButton_4_clicked()
{
    bool flag1=false;
    if(ui->lineEdit->text()=="") flag1 = true;
    if(flag1){
        QMessageBox::information(this,"提示","请输入关键词!");
    }else {
        gd_pnum=ui->lineEdit->text();
        schw = new ShowCaseHistory(nullptr);
        schw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
        schw->show();
    }

}

void DoctorWindow::on_pushButton_5_clicked()
{
    init_DWT();
}

void DoctorWindow::on_pushButton_6_clicked()
{
    close();
}
