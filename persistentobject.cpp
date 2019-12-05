#include <iostream>
#include <QList>
#include <QtSql>
#include <QDebug>

#include "persistentobject.h"
#include "persistentattribute.h"
#include "sqlcontroller.h"
#include "dbmanager.h"


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
    QSqlDatabase db = dbManager::Instance()->db;

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
    QSqlDatabase db = dbManager::Instance()->db;
    this->createTable(&db);
    this->insert(&db);
    return this->id;
}

void PersistentObject::drop()
{
    QSqlDatabase db = dbManager::Instance()->db;

    QString queryStr = QString("DROP table %1").arg(this->table);
    qDebug() << queryStr;
    QSqlQuery query(db);
    query.prepare(queryStr);
    if (! query.exec())
    {
        cout << "Error executing query" << endl;
        qDebug() << query.lastError();
    }
}


void PersistentObject::insert(QSqlDatabase *db)
{
    QString queryStr = QString("INSERT INTO %1 VALUES (%2)").arg(this->table, this->insertFieldsTable());
    qDebug() << queryStr;
    QSqlQuery query(*db);

    SqlController::Instance()->addRequest(queryStr);
    SqlController::Instance()->showRequestList();
}

void PersistentObject::deleteBook(QString tableName, int id)
{
    QSqlDatabase db = dbManager::Instance()->db;
    QString queryStr = QString("DELETE FROM %1 WHERE id = %2 ").arg(tableName, id);
    qDebug() << queryStr;
    QSqlQuery query(db);
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

void PersistentObject::createTable(QSqlDatabase *db)
{
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
