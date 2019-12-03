#include <iostream>
#include <QList>
#include <QtSql>
#include <QDebug>

#include "persistentobject.h"
#include "persistentattribute.h"
#include "sqlcontroller.h"


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

QList<QStringList> PersistentObject::get(QString tableName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // loading driver
    db.setDatabaseName("HARDCODED.db"); // name db
    if (! db.open()){
        cout << "Unable to open the database." << endl;
    }

    QString queryStr = QString("select * from %1").arg(tableName);
    qDebug() << queryStr;
    QSqlQuery query(db);
    query.prepare(queryStr);
    if (! query.exec())
    {
        cout << "Error executing Get query" << endl;
        qDebug() << query.lastError();
    }
    QList<QStringList> data;
    while(query.next()){
        QStringList row;
        int index = 0;
        while(query.value(index).toString()!="")
        {
            QString value = query.value(index).toString();
            row.append(value);
            index++;
        }
        data.append(row);
    }
    return data;
}

int PersistentObject::save()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // loading driver
    this->SQLDbInit(&db);
    this->insert(&db);
    db.close ();
    return this->id;
}

void PersistentObject::drop()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // loading driver
    db.setDatabaseName("HARDCODED.db"); // name db
    if (! db.open()){
        cout << "Unable to open the database." << endl;
    }

    QString queryStr = QString("DROP table Book");
    qDebug() << queryStr;
    QSqlQuery query(db);
    query.prepare(queryStr);
    if (! query.exec())
    {
        cout << "Error executing query" << endl;
        qDebug() << query.lastError();
    }    db.close ();
}


void PersistentObject::insert(QSqlDatabase *db)
{
    QString queryStr = QString("INSERT INTO %1 VALUES (%2)").arg(this->table, this->insertFieldsTable());
    qDebug() << queryStr;
    QSqlQuery query(*db);

    SqlController::Instance()->addRequest(queryStr);
    SqlController::Instance()->showRequestList();
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

QString PersistentObject::insertFieldsTable()
{
    QString values = QString::number(this->id) + QString(", ");
    this->print();
    for (int index=0; index < this->attributes->size() -1; index++)
    {
        // pre and append single quote to handle comma seperated list
        QString value = QString("'") + this->attributes->at(index)->voidPointer2QString() + QString("'");
        values += value + QString(", ");
    }
    // no comma after the last element
    values += QString("'") + this->attributes->at(
                this->attributes->size() -1
              )->voidPointer2QString() + QString("'");
    return values;
}

void PersistentObject::SQLDbInit(QSqlDatabase *db)
{
    db->setDatabaseName("HARDCODED.db"); // name db
    if (! db->open()){
        cout << "Unable to open the database." << endl;
    }

    QString queryStr = QString("CREATE TABLE IF NOT EXISTS %1 (%2)").arg(this->table, this->generateFieldsTable());
    qDebug() << queryStr;
    QSqlQuery query(*db);
    query.prepare(queryStr);
    if (! query.exec())
    {
        cout << "Error executing query" << endl;
        qDebug() << query.lastError();
    }
}
