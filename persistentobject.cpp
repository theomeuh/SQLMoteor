#include <iostream>
#include <QList>
#include <QtSql>
#include <QDebug>

#include "persistentobject.h"
#include "persistentattribute.h"

int persistantObjectCounter = 0;

using namespace std;

PersistentObject::PersistentObject(QString className) :
    id(persistantObjectCounter++),
    table(&className),
    attributes(new QList<PersistentAttribute *>)
{

}

void PersistentObject::addAttribute(PersistentAttribute *persistantAttribute){
    attributes->append(persistantAttribute);
}


int PersistentObject::save(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // loading driver
    db.setDatabaseName("HARDCODED.db"); // name db

    if (! db.open()){
        cout << "Unable to open the database." << endl;
    }


    // Ensure inputs are sanitized to prevent sql injection
    for(int i=0; i < this->attributes->count(); i++){
        PersistentAttribute *attribute = this->attributes->at(i);
        QSqlQuery query(db);
        QString queryStr = "";

        QVariant variant = attribute->type;
        // enumeration on QMetaType instead on QVariant because float type is not in QVariant
        switch (static_cast<QMetaType::Type>(variant.type())) {
            case QMetaType::Int:
                cout << "This is a int" << endl;
                break;
            case QMetaType::Float:
                cout << "This is a float" << endl;
                break;
            case QMetaType::QString:
                cout << "This is a QString" << endl;
                break;
            case QMetaType::QStringList:
                cout << "This is a QStringList" << endl;
                break;
            default:;
        }


        query.prepare(queryStr);
        query.bindValue(":id", attribute->name);
        if (! query.exec())
        {
            cout << "Error executing query" << endl;
            qDebug() << query.lastError();
        }
    }

    db.close ();
    return this->id;
}
