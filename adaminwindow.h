#ifndef ADAMINWINDOW_H
#define ADAMINWINDOW_H

#include <QMainWindow>
#include "patientmanager.h"
#include "doctormanager.h"
#include "roommanager.h"
#include "drugmanager.h"

namespace Ui {
class AdaminWindow;
}

class AdaminWindow : public QMainWindow
{
    Q_OBJECT

public:
    DrugManager *drmw;
    RoomManager *rmw;
    DoctorManager  *dmw;
    patientmanager *pmw;
    explicit AdaminWindow(QWidget *parent = nullptr);
    ~AdaminWindow();

private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::AdaminWindow *ui;
};

#endif // ADAMINWINDOW_H
