#ifndef PERSISTENTOBJECT_H
#define PERSISTENTOBJECT_H

#include <QList>
#include "persistentattribute.h"

class PersistentObject
{
    private:
        int id; // id of the object in database. It's UNIQUE
        QString table; // name of the SQL table where it's stored
        QList<PersistentAttribute *> *attributes; // attributes to store

        /**
            @brief Generate a QString to be inserted in a CREATE SQL statement
            @line
            @return name_1 TYPE_1 name_2 TYPE_2 ... name_n TYPE_n
        */
        QString generateFieldsTable();

    public:
        PersistentObject(QString className);
        void addAttribute(PersistentAttribute *);
        /**
         * @brief Save the object in a database
         * @return
         */
        int save();
        void print();

};

#endif // PERSISTENTOBJECT_H
