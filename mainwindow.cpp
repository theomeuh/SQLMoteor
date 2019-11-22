#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "newbook.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_Book_triggered()
{
    NewBook *newbook = new NewBook();
    newbook->show();
}
