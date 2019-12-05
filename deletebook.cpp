#include "deletebook.h"
#include "ui_deletebook.h"
#include "book.h"

DeleteBook::DeleteBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteBook)
{
    ui->setupUi(this);
}

DeleteBook::~DeleteBook()
{
    delete ui;
}

void DeleteBook::on_pushButton_clicked()
{
    int id;
    Book::deleteBook(id);
}
