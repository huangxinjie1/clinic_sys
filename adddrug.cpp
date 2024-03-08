#include "adddrug.h"
#include "ui_adddrug.h"

QString AddDrug::FindNum(){
    int temp=1;
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DRNUM from drug order by cast(DRNUM as decimal )";
    query.exec(str1);
    query.first();
    qDebug()<<query.numRowsAffected();
    if(query.numRowsAffected()){
        query.last();
        temp=query.value(0).toInt();
        qDebug()<<temp;
        temp++;
    }
    return QString::number(temp);
}

QString AddDrug::FindPhnum(QString str){
    if(str=="处方药"){
        return "1";
    }
    else if(str=="非处方药"){
        return "2";
    }
    else return 0;
}

AddDrug::AddDrug(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddDrug)
{
    ui->setupUi(this);
}

AddDrug::~AddDrug()
{
    delete ui;
}

void AddDrug::on_pushButton_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    bool flag1=false;
    if(ui->lineEdit->text()=="")flag1=true;
    if(ui->lineEdit_2->text()=="")flag1=true;
    if(ui->lineEdit_3->text()=="")flag1=true;
    if(flag1){
        QMessageBox::about(NULL,"提示","请输入信息!");
        return;
    }
    else{

        QString d_num=FindNum();
        QString d_name=ui->lineEdit->text();
        QString d_cate=ui->comboBox->currentText();
        QString d_fees=ui->lineEdit_2->text();
        QString d_phnum=FindPhnum(ui->comboBox->currentText());
        QString d_inum=ui->lineEdit_3->text();
        QString str1="insert into drug value ('"+d_num+"','"+d_name+"','"+d_cate+"',"+d_fees+",'"+d_phnum+"',"+d_inum+")";
        qDebug()<<str1;
        if(query.exec(str1)){
            QMessageBox::information(this,"提示","添加成功!");
        }
        else{
            QMessageBox::information(this,"提示","添加失败,请检查!");
        }

    }

}

void AddDrug::on_pushButton_2_clicked()
{
    close();
}
