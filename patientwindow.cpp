#include "patientwindow.h"
#include "ui_patientwindow.h"

extern QString gp_dnum;
extern QString gd_pnum;
extern QString gs_pnum;
extern QString prnum;

void PatientWindow::init_PWT(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DNUM,DNAME,DSEX,DAGE,RNAME,DPROF,DSPC,DFEES from r_doc_acc";
    query.exec(str1);
    int rows=query.numRowsAffected();
    //qDebug()<<rows;
    QSqlRecord res = query.record();
    int cols=res.count();
    //qDebug()<<cols;
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

void PatientWindow::init_PWC(){
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
PatientWindow::PatientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PatientWindow)
{
    ui->setupUi(this);
    init_PWT();
    init_PWC();
}

PatientWindow::~PatientWindow()
{
    delete ui;
}


void PatientWindow::on_pushButton_4_clicked()
{

    if(ui->lineEdit->text()==""){
        QMessageBox::information(this,"提示","请输入医生编号进行挂号!");
    }else{
        gp_dnum=ui->lineEdit->text();
        rw=new Reservation(nullptr);
        rw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
        rw->show();
    }
    ui->lineEdit->clear();
}

void PatientWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text()==""){
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QString d_room=ui->comboBox->currentText();
        QSqlQuery query(db);
        QString str1="select DNUM,DNAME,DSEX,DAGE,RNAME,DPROF,DSPC,DFEES from r_doc_acc where RNAME='"+d_room+"'";
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

void PatientWindow::on_pushButton_3_clicked()
{
    gd_pnum=gs_pnum;
    schw=new ShowCaseHistory(nullptr);
    schw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    schw->show();

}

void PatientWindow::on_pushButton_6_clicked()
{
    sdw=new ShowDrug(nullptr);
    sdw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    sdw->show();
}

void PatientWindow::on_pushButton_7_clicked()
{
    bw=new Bill(nullptr);
    bw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    bw->show();
}

void PatientWindow::on_pushButton_2_clicked()
{
    upw=new UpdatePatient(nullptr);
    upw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    upw->show();
}

void PatientWindow::on_pushButton_5_clicked()
{
    close();
}
