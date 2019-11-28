#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "newbook.h"
#include "book.h"

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

void MainWindow::on_actionOpen_triggered()
{
    QString book;
    PersistentObject* persistentObject = new PersistentObject(book);
    persistentObject->getBooks();
}

void MainWindow::on_actionErase_Bookcase_triggered()
{
    QString book;
    PersistentObject* persistentObject = new PersistentObject(book);
    persistentObject->drop();
}
