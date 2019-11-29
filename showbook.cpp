#include "newbook.h"
#include "ui_newbook.h"
#include "book.h"

ShowBook::ShowBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewBook)
{
    ui->setupUi(this);
}

ShowBook::~ShowBook()
{
    delete ui;
}

Book NewBook::on_buttonBox_accepted()
{
    QStringList authors = ui->authorsEdit->text().split(",");
    QString title = ui->titleEdit->text();
    int ISBN = ui->ISBNEdit->text().toInt();
    int year = ui->yearEdit->text().toInt();

    Book new_book(authors, title, &ISBN, &year);

    new_book.print();
    new_book.save();

    return new_book;
}
