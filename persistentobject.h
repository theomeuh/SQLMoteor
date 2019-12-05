#ifndef PERSISTENTOBJECT_H
#define PERSISTENTOBJECT_H

#include <QList>
#include <QSqlDatabase>
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
            @return name_1 TYPE_1, name_2 TYPE_2, ... name_n TYPE_n
        */
        QString generateFieldsTable();

        /**
         * @brief Generate a QString to be inserted in a INSERT INTO SQL statement
         * @return 'value_1', 'value_2', ... 'value_n'
         */
        QString insertFieldsTable();

        /**
         * @brief Init the table if it does not exist
         * @return QSqlDatabase db
         */
        void createTable(QSqlDatabase *db);

        /**
         * @brief Make the insertion of the PersistentObject in the database `db` in the table `table`
         * @param QSqlDatabase db
         */
        void insert(QSqlDatabase *db);

    public:
        PersistentObject(QString className);
        void addAttribute(PersistentAttribute *);
        /**
         * @brief Save the object in a database
         * @return
         */
        int save();
        void print();
        static QList<QStringList> get(QString tableName);
        static void drop(QString tableName);

};

#endif // PERSISTENTOBJECT_H
