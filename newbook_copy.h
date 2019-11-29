#ifndef NEWBOOK_H
#define NEWBOOK_H

#include <QDialog>
#include "book.h"

namespace Ui {
class NewBook;
}

class NewBook : public QDialog
{
    Q_OBJECT

public:
    explicit NewBook(QWidget *parent = nullptr);
    ~NewBook();

private slots:
    Book on_buttonBox_accepted();

private:
    Ui::NewBook *ui;
};

#endif // NEWBOOK_H
