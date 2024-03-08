#include "showdrug.h"
#include "ui_showdrug.h"
extern QString gs_pnum;

void ShowDrug::show_info(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DENAME,DNAME,WAY,COUNT,DEFEES,PRTIME from pres_drug where PNUM='"+gs_pnum+"'";
    qDebug()<<str1;
    query.exec(str1);
    int rows=query.numRowsAffected();
    qDebug()<<rows;
    QSqlRecord res = query.record();
    int cols=res.count();
    qDebug()<<cols;
    QStandardItemModel *model=new QStandardItemModel();
    model->setColumnCount(cols);
    model->setHeaderData(0,Qt::Horizontal,("药品名"));
    model->setHeaderData(1,Qt::Horizontal,("开药医生"));
    model->setHeaderData(2,Qt::Horizontal,("用药方法"));
    model->setHeaderData(3,Qt::Horizontal,("总量"));
    model->setHeaderData(4,Qt::Horizontal,("单价"));
    model->setHeaderData(5,Qt::Horizontal,("时间"));
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

ShowDrug::ShowDrug(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowDrug)
{
    ui->setupUi(this);
    show_info();
}

ShowDrug::~ShowDrug()
{
    delete ui;
}

void ShowDrug::on_pushButton_clicked()
{
    close();
}
