#include "addprescription.h"
#include "ui_addprescription.h"

extern QString gd_pnum;
extern QString gs_dnum;

QString prnum;

QString AddPrescription::get_time(){
    QString  curTime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    return curTime;
}

QString AddPrescription::getPrNum(){
    int temp=1;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1 ="select PRNUM from prescri order by cast(PRNUM as  decimal )";
    query.exec(str1);
    if(query.numRowsAffected()){
        query.last();
        temp=query.value(0).toInt();
        qDebug()<<temp;
        temp++;
    }
    qDebug()<<temp;
    return QString::number(temp);
}

QString AddPrescription::getPreNum(){
    int temp=1;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1 ="select * from presctiption";
    query.exec(str1);
    if(query.numRowsAffected()){
        query.last();
        temp=query.value(0).toInt();
        qDebug()<<temp;
        temp++;
    }
    qDebug()<<temp;
    return QString::number(temp);
}

QString AddPrescription::getConNum(){
    int temp=1;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1 ="select * from consrecord";
    query.exec(str1);
    if(query.numRowsAffected()){
        query.last();
        temp=query.value(0).toInt();
        qDebug()<<temp;
        temp++;
    }
    qDebug()<<temp;
    return QString::number(temp);
}

QString  AddPrescription::getDrNum(QString str){
    QString res;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1 ="select DRNUM from DRUG where DENAME='"+str+"'";
    qDebug()<<str1;
    if(query.exec(str1)){
        query.first();
        res=query.value(0).toString();
    }else{
         QMessageBox::information(this,"提示","药品编号查找失败!");
    }
    return res;
}


void AddPrescription::ChangeStatus(QString str){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="update res_p_d set STAUS = '已开处方' where PNUM = '"+str+"'";
    qDebug()<<str1;
    if(!query.exec(str1)){
        QMessageBox::information(this,"提示","状态更新失败!");
    }
}

void AddPrescription::init_AddPR(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    prnum = getPrNum();
    QString curtime=get_time();
    QString str1="insert into prescri value ('"+prnum+"','"+gs_dnum+"','"+gd_pnum+"','"+curtime+"')";
    qDebug()<<str1;
    if(!query.exec(str1)){
        QMessageBox::information(this,"提示","添加失败!");
    }
}
void AddPrescription::init_APT(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select PRENUM,DENAME,WAY,COUNT,DEFEES from pres_drug where PNUM='"+gd_pnum+"' and PRNUM='"+prnum+"'";
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
        model->setHeaderData(2,Qt::Horizontal,("用药方法"));
        model->setHeaderData(3,Qt::Horizontal,("总量"));
        model->setHeaderData(4,Qt::Horizontal,("单价"));
        model->setRowCount(rows);
        int i=0;
        while (query.seek(i)) {
                model->setItem(i,0,new QStandardItem(query.value(0).toString()));
                model->setItem(i,1,new QStandardItem(query.value(1).toString()));
                model->setItem(i,2,new QStandardItem(query.value(2).toString()));
                model->setItem(i,3,new QStandardItem(query.value(3).toString()));
                model->setItem(i,4,new QStandardItem(query.value(4).toString()));
                i++;
        }
        ui->tableView->setModel(model);
    }
}

void AddPrescription::init_APW(){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DENAME from DRUG";
    if(query.exec(str1)){
        while (query.next()) {
            ui->comboBox->addItem(query.value(0).toString());
        }
    }else{
        QMessageBox::information(this,"提示","初始化失败!");
    }
    QString str2="select PNAME,EMED from rec_m_r where PNUM ='"+gd_pnum+"'";
    qDebug()<<str2;
    if(query.exec(str2)){
        query.first();
        ui->label_3->setText(query.value(0).toString());
        ui->textBrowser->setText(query.value(1).toString());
    }
    else{
        QMessageBox::information(this,"提示","初始化失败!");
    }
}

AddPrescription::AddPrescription(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddPrescription)
{
    ui->setupUi(this);
    init_APW();
    init_AddPR();
}

AddPrescription::~AddPrescription()
{
    delete ui;
}

void AddPrescription::on_pushButton_clicked()
{
    bool flag1=false;
    if(ui->lineEdit_2->text()=="") flag1=true;
    if(ui->textEdit->toPlainText()=="") flag1=true;
    if(flag1){
        QMessageBox::information(this,"提示","请输入完整的信息!");
    }else{
        QString prenum=getPreNum();
        QString drnum=getDrNum(ui->comboBox->currentText());
        QString way=ui->textEdit->toPlainText();
        QString count=ui->lineEdit_2->text();
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QSqlQuery query(db);
        QString str1="insert into presctiption value ('"+prenum+"','"+prnum+"','"+drnum+"','"+way+"',"+count+")";
        qDebug()<<str1;
        if(!query.exec(str1)){
            QMessageBox::information(this,"提示","添加失败!");
        }
    }
    init_APT();

}

void AddPrescription::on_pushButton_3_clicked()
{
    init_APT();
}

void AddPrescription::on_pushButton_2_clicked()
{
    bool flag1=false;
    if(ui->lineEdit->text()=="") flag1=true;
    if(flag1){
        QMessageBox::information(this,"提示","请输入要删除的药品编号!");
    }else{
        QString del_num=ui->lineEdit->text();
        QSqlDatabase db=QSqlDatabase::database();
        if(!db.open()){
             QMessageBox::information(this,"错误","数据库连接失败!");
        }
        QSqlQuery query(db);
        QString str1="delete from presctiption where PRENUM='"+del_num+"'";
        qDebug()<<str1;
        if(!query.exec(str1)){
            QMessageBox::information(this,"提示","删除失败!");
        }
        init_APT();
    }
}

void AddPrescription::on_pushButton_4_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1 ="select * from presctiption";
    query.exec(str1);
    if(!query.numRowsAffected()){
        query.first();
        QString str2="delete from prescri where PRNUM = '"+prnum+"'";
        if(!query.exec(str2)){
            query.first();
            QMessageBox::information(this,"提示","删除失败!");
        }
    }else{
        QString consnum=getConNum();
        QString str2="select DFEES,sum(DEFEES*COUNT) from pres_drug where PRNUM='"+prnum+"'";
        //qDebug()<<str2;
        query.exec(str2);
        query.first();
        //qDebug()<<query.value(0);
        //qDebug()<<query.value(1);
        QString dfees=query.value(0).toString();
        QString drfees=query.value(1).toString();
        QString afees=QString::number(dfees.toDouble()+drfees.toDouble());
        QString str3="insert into consrecord value ('"+consnum+"','"+gd_pnum+"','"+prnum+"',"+dfees+","+drfees+","+afees+",'未支付')";
        //qDebug()<<str3;
        if(query.exec(str3)){
            ChangeStatus(gd_pnum);
            close();
        }else{
            QMessageBox::information(this,"提示","插入失败!");
        }
    }
}

void AddPrescription::on_pushButton_5_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1 ="select * from presctiption";
    query.exec(str1);
    if(!query.numRowsAffected()){
        query.first();
        QString str2="delete from prescri where PRNUM = '"+prnum+"'";
        if(!query.exec(str2)){
            QMessageBox::information(this,"提示","删除失败!");
        }
    }
    this->close();
}
