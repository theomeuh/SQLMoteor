#include "newbook.h"
#include "ui_newbook.h"

NewBook::NewBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewBook)
{
    ui->setupUi(this);
}

NewBook::~NewBook()
{
    delete ui;
}

QStringList NewBook::on_authorsEdit_textChanged(const QString &authorsString)
{
    // parse authorsString on comma and return QStringList
    return QStringList();
}
