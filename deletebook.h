#ifndef DELETEBOOK_H
#define DELETEBOOK_H

#include <QWidget>
#include "book.h"

namespace Ui {
class DeleteBook;
}

class DeleteBook : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteBook(QWidget *parent = nullptr);
    ~DeleteBook();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DeleteBook *ui;
};

#endif // DELETEBOOK_H
