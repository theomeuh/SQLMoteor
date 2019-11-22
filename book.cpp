#include "book.h"
#include <iostream>
using namespace std;



Book::Book(QStringList authors, QString title, int ISBN, int year) : PersistentObject("Book"),
    authors(authors),
    title(title),
    ISBN(ISBN),
    year(year)
{
    this->addAttribute(new PersistentAttribute(new QString("authors"), QVariant::StringList, &authors));
    this->addAttribute(new PersistentAttribute(new QString("title"), QVariant::String, &title));
    this->addAttribute(new PersistentAttribute(new QString("ISBN"), QVariant::Int, &ISBN));
    this->addAttribute(new PersistentAttribute(new QString("year"), QVariant::Int, &year));
}


void Book::print(){
    cout << "title: " << this->title.toStdString() << endl;
    for ( const auto& author : this->authors )
    {
        cout << "author: " << author.toStdString() << endl;
    }
    cout << "year: " << this->year << endl;
    cout << "ISBN: " << this->ISBN << endl;
}