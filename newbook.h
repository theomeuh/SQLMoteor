#ifndef NEWBOOK_H
#define NEWBOOK_H

#include <QDialog>

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
    QStringList on_authorsEdit_textChanged(const QString &authorsString);

private:
    Ui::NewBook *ui;
};

#endif // NEWBOOK_H
