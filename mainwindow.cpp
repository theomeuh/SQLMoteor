#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "newbook.h"
#include "book.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , bookTable()
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
    QList<QStringList> data = persistentObject->get();
    ui->bookTable->setRowCount(data.size());
    ui->bookTable->setColumnCount(data.value(0).size());
        /*add stuff inside the table view*/
        for(int i=0; i<ui->bookTable->rowCount(); i++)
        {
            for(int j=0; j<ui->bookTable->columnCount(); j++)
            {
                QString valueCell = data.value(i).value(j);
                QTableWidgetItem *pCell = ui->bookTable->item(i, j);
                if(!pCell)
                {
                    pCell = new QTableWidgetItem;
                    ui->bookTable->setItem(i, j, pCell);
                }
                pCell->setText(valueCell);
            }
        }

}

void MainWindow::on_actionErase_Bookcase_triggered()
{
    QString book;
    PersistentObject* persistentObject = new PersistentObject(book);
    persistentObject->drop();
}
