#ifndef PERSISTENTOBJECT_H
#define PERSISTENTOBJECT_H

#include <QList>
#include "persistentattribute.h"

class PersistentObject
{
    private:
        int id; // id of the object in database. It's UNIQUE
        QString *table; // name of the SQL table where it's stored
        QList<PersistentAttribute *> *attributes; // attributes to store

    public:
        PersistentObject(QString className);
        void addAttribute(PersistentAttribute *);
        int save(); // save() goes through attributes and each attribute must be able to store itself in the table of the class

};

#endif // PERSISTENTOBJECT_H
