#ifndef BOOK_H
#define BOOK_H

#include "persistentattribute.h"
#include "persistentobject.h"
#include <QVariant>


class Book : private PersistentObject
{

public:
    QStringList authors;
    QString title;
    int ISBN;
    int year;

    Book(QStringList authors, QString title, int ISBN, int year);
    int save();
    void print();
};

#endif // BOOK_H
