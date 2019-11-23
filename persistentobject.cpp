#include <iostream>
#include <QList>
#include <QtSql>
#include <QDebug>

#include "persistentobject.h"
#include "persistentattribute.h"



using namespace std;

PersistentObject::PersistentObject(QString className) :
    table(className),
    attributes(new QList<PersistentAttribute *>)
{
    static int persistantObjectCounter = 0;
    persistantObjectCounter ++;
    this->id = persistantObjectCounter;
}

void PersistentObject::addAttribute(PersistentAttribute *persistantAttribute){
    attributes->append(persistantAttribute);
}

void PersistentObject::print()
{
    cout << "Persistent ID: " << this->id << endl;
    cout << "table: " << this->table.toStdString() << endl;
}


int PersistentObject::save()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // loading driver
    db.setDatabaseName("HARDCODED.db"); // name db
    if (! db.open()){
        cout << "Unable to open the database." << endl;
    }

    QString queryStr = QString("CREATE TABLE IF NOT EXISTS %1 (%2)").arg(this->table, this->generateFieldsTable());
    qDebug() << queryStr;
    QSqlQuery query(db);
    query.prepare(queryStr);
    if (! query.exec())
    {
        cout << "Error executing query" << endl;
        qDebug() << query.lastError();
    }
    db.close ();
    return this->id;
}

QString PersistentObject::generateFieldsTable()
{
    QString fields = QString("id INTEGER UNIQUE PRIMARY KEY, ");
    for (int index=0; index < this->attributes->size() -1; index++)
    {
        fields += this->attributes->at(index)->createSQLField() + QString(", ");
    }
    // no comma after the last element
    fields += this->attributes->at(
                this->attributes->size()-1
              )->createSQLField();
    return fields;
}
