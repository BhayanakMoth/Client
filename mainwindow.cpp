#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
    void WriteToServerArea();
}
void MainWindow::writeToServerArea(QString qstr)
{
   ui->serverArea->setText(qstr);
}
