#include "startwindow.h"
#include "ui_startwindow.h"

extern QString gs_dnum;
extern QString gs_pnum;

void StartWindow::init_DNUM(QString str){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select DNUM from d_account where U_NAME='"+str+"'";
    if(query.exec(str1)){
        query.first();
        gs_dnum=query.value(0).toString();
    }
    else{
        QMessageBox::information(this,"提示","当前为游客登录!");
    }
}

void StartWindow::init_PNUM(QString str){
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    QString str1="select PNUM from p_account where U_NAME='"+str+"'";
    if(query.exec(str1)){
        query.first();
        gs_pnum=query.value(0).toString();
        qDebug()<<query.value(0).toString();
    }
    else{
        QMessageBox::information(this,"提示","当前为游客登录!");
    }
}

bool StartWindow::creatMySqlConn(){
    QSqlDatabase db;
       if(QSqlDatabase::contains("mysql_connect")) {
           db = QSqlDatabase::database("mysql_connect");
       } else {
           //连接数据库
           db = QSqlDatabase::addDatabase("QODBC"); //数据库类型
           db.setHostName("127.0.0.1");    //设置为本地主机
           db.setPort(3306);               //设置端口
           db.setDatabaseName("MySQL");   //选择数据库名称
           db.setUserName("root");         //设置用户名
           db.setPassword("Ilovec++1."); //设置密码
           if(!db.open()){
                QMessageBox::information(this,"错误","数据库连接失败!");
                return false;
           }
       }
       return true;
}

QString StartWindow::strToMd5(QString str){
    QString strMd5;
    QByteArray qba;
    qba = QCryptographicHash::hash(str.toLatin1(),QCryptographicHash::Md5);
    strMd5.append(qba.toHex());
    return strMd5;
}

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    creatMySqlConn();
}

StartWindow::~StartWindow()
{
    delete ui;
}


void StartWindow::on_pushButton_2_clicked()
{
    this->close();
}

void StartWindow::on_pushButton_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.open()){
         QMessageBox::information(this,"错误","数据库连接失败!");
    }
    QSqlQuery query(db);
    bool flag1=false;
    if(ui->lineEdit->text()=="") flag1=true;
    if(ui->lineEdit_2->text()=="") flag1=true;
    if(flag1){
        QMessageBox::about(NULL,"提示","请输入账号密码!");
        return;
    }
    QString u_type=ui->buttonGroup->checkedButton()->text();
    QString u_name=ui->lineEdit->text();
    QString u_password=strToMd5(ui->lineEdit_2->text());
    if(u_type=="管理员"){
        if(u_name=="admin"&&u_password==strToMd5("admin")){
            aw=new AdaminWindow(nullptr);
            aw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
            aw->show();
        }
        else{
            QMessageBox::information(this,"提示","账号密码错误!");
        }
    }
    if(u_type=="医生"){
        QString str1="select U_PASS from D_ACCOUNT where U_NAME='"+u_name+"' ";
        query.exec(str1);
        if(query.first()){
            if(query.value(0).toString()==u_password){
                init_DNUM(u_name);
                qDebug()<<gs_pnum;
                dw=new DoctorWindow(nullptr);
                dw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
                dw->show();
            }
            else{
                QMessageBox::information(this,"提示","账号密码错误!");
            }
        }
        else{
            QMessageBox::information(this,"提示","账号密码错误!");
        }
    }
    if(u_type=="患者"){
        QString str1="select U_PASS from P_ACCOUNT where U_NAME='"+u_name+"' and  U_TYPE ='"+u_type+"'";
        query.exec(str1);
        if(query.first()){
            if(query.value(0).toString()==u_password){
                init_PNUM(u_name);
                qDebug()<<gs_pnum;
                pw=new PatientWindow(nullptr);
                pw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
                pw->show();
            }
            else{
                QMessageBox::information(this,"提示","账号密码错误!");
            }
        }
        else{
            QMessageBox::information(this,"提示","账号密码错误!");
        }
    }
}

void StartWindow::on_pushButton_3_clicked()
{
    apw=new AddPatient(nullptr);
    apw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    apw->show();
}
