#include "adaminwindow.h"
#include "ui_adaminwindow.h"

AdaminWindow::AdaminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdaminWindow)
{
    ui->setupUi(this);
}

AdaminWindow::~AdaminWindow()
{
    delete ui;
}


void AdaminWindow::on_pushButton_3_clicked()
{
    pmw=new patientmanager(nullptr);
    pmw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    pmw->show();
}

void AdaminWindow::on_pushButton_2_clicked()
{
    dmw = new DoctorManager(nullptr);
    dmw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    dmw->show();
}

void AdaminWindow::on_pushButton_4_clicked()
{
    rmw=new RoomManager(nullptr);
    rmw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    rmw->show();
}

void AdaminWindow::on_pushButton_clicked()
{
    drmw=new DrugManager(nullptr);
    drmw->setStyleSheet("QMainWindow{background-color: rgb(214, 209, 176);}");
    drmw->show();
}

void AdaminWindow::on_pushButton_5_clicked()
{
    close();
}
