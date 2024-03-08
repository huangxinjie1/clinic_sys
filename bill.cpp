#include "bill.h"
#include "ui_bill.h"
extern QString gs_pnum;
QString gb_recnum;

void Bill::init_BT1()
{
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DISTINCT RECNUM,AFEES,DRAFEES,DFEES,DNAME,PRTIME,STATUS from bill where PNUM='"+gs_pnum+"'";
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
    model->setHeaderData(1,Qt::Horizontal,("总费用"));
    model->setHeaderData(2,Qt::Horizontal,("药品费"));
    model->setHeaderData(3,Qt::Horizontal,("诊费"));
    model->setHeaderData(4,Qt::Horizontal,("开药医生"));
    model->setHeaderData(5,Qt::Horizontal,("时间"));
    model->setHeaderData(6,Qt::Horizontal,("状态"));
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
            i++;
    }
    ui->tableView->setModel(model);
}

void Bill::init_BT2(QString str){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DISTINCT RECNUM,DENAME,DEFEES,COUNT,DNAME,PRTIME from bill where RECNUM='"+str+"'";
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
    model->setHeaderData(1,Qt::Horizontal,("药品名"));
    model->setHeaderData(2,Qt::Horizontal,("药品单价"));
    model->setHeaderData(3,Qt::Horizontal,("数量"));
    model->setHeaderData(4,Qt::Horizontal,("开药医生"));
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
    ui->tableView_2->setModel(model);
}

bool Bill::isPay(){
    bool flag=false;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select STATUS from consrecord where PNUM = '"+gs_pnum+"'";
    if(query.exec(str1)){
        query.first();
        if(query.value(0)=="已支付"){
           flag=true;
        }
    }
    return flag;
}

Bill::Bill(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Bill)
{
    ui->setupUi(this);
    init_BT1();
}

Bill::~Bill()
{
    delete ui;
}



void Bill::on_pushButton_2_clicked()
{
    bool flag1=false;
    if(ui->lineEdit->text()=="")flag1=true;
    if(flag1){
        QMessageBox::information(this,"提示","请输入完整的信息!");
    }
    else{
        init_BT2(ui->lineEdit->text());
    }
}

void Bill::on_pushButton_4_clicked()
{
    close();
}

void Bill::on_pushButton_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    if(ui->lineEdit->text()==""){
        QString sta=ui->comboBox->currentText();
        QString str1="select DISTINCT RECNUM,AFEES,DRAFEES,DFEES,DNAME,PRTIME,STATUS from bill where PNUM='"+gs_pnum+"' and STATUS = '"+sta+"'";
        query.exec(str1);
        int rows=query.numRowsAffected();
        qDebug()<<rows;
        QSqlRecord res = query.record();
        int cols=res.count();
        qDebug()<<cols;
        QStandardItemModel *model=new QStandardItemModel();
        model->setColumnCount(cols);
        model->setHeaderData(0,Qt::Horizontal,("编号"));
        model->setHeaderData(1,Qt::Horizontal,("总费用"));
        model->setHeaderData(2,Qt::Horizontal,("药品费"));
        model->setHeaderData(3,Qt::Horizontal,("诊费"));
        model->setHeaderData(4,Qt::Horizontal,("开药医生"));
        model->setHeaderData(5,Qt::Horizontal,("时间"));
        model->setHeaderData(6,Qt::Horizontal,("状态"));
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
                i++;
        }
        ui->tableView->setModel(model);
    }else{
         QString rec_num=ui->lineEdit->text();
         QString str1="select DISTINCT RECNUM,AFEES,DRAFEES,DFEES,DNAME,PRTIME,STATUS from bill where RECNUM = '"+rec_num+"'";
         query.exec(str1);
         int rows=query.numRowsAffected();
         qDebug()<<rows;
         QSqlRecord res = query.record();
         int cols=res.count();
         qDebug()<<cols;
         QStandardItemModel *model=new QStandardItemModel();
         model->setColumnCount(cols);
         model->setHeaderData(0,Qt::Horizontal,("编号"));
         model->setHeaderData(1,Qt::Horizontal,("总费用"));
         model->setHeaderData(2,Qt::Horizontal,("药品费"));
         model->setHeaderData(3,Qt::Horizontal,("诊费"));
         model->setHeaderData(4,Qt::Horizontal,("开药医生"));
         model->setHeaderData(5,Qt::Horizontal,("时间"));
         model->setHeaderData(6,Qt::Horizontal,("状态"));
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
                 i++;
         }
         ui->tableView->setModel(model);
    }
}

void Bill::on_pushButton_3_clicked()
{
    bool flag1=false;bool flag2=true;
    if(ui->lineEdit->text()=="")flag1=true;
    if(flag1){
        QMessageBox::information(this,"提示","请输入完整的信息!");
    }else{
        if(isPay()){
            flag2=false;
            QMessageBox::information(this,"提示","该账单已支付!");
        }

    }
    if(flag2&&!flag1){
        gb_recnum=ui->lineEdit->text();
        payw=new PayWin(nullptr);
        payw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
        payw->show();
    }
}
