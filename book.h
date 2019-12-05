#ifndef BOOK_H
#define BOOK_H

#include "persistentattribute.h"
#include "persistentobject.h"
#include <QVariant>


class Book : private PersistentObject
{

public:
    QStringList* authors;
    QString* title;
    int* ISBN;
    int* year;

    Book(QStringList* authors, QString* title, int* ISBN, int* year);
    int save();
    void print();
    static void drop();
    static QList<QStringList> get();
    static void deleteBook(int id);
};

#endif // BOOK_H
