#ifndef PERSISTENTATTRIBUTE_H
#define PERSISTENTATTRIBUTE_H

#include <QVariant>

class PersistentAttribute
{
    private:

        /**
         * @brief Return the SQL type corresponding to the QVariant type
         * @return TYPE
         */
        QString Qtype2SQLType();


    public:
        QString name; // name and ID of the attribute in the class to store and in the database
        QVariant::Type type; /* type of data to store
         Qvariant : enumerata all existing type
         we manage :
          - string,
          - list<string>
          - int
          - float
        */
        void *data; // pointer to read and write data when storing and getting class
        PersistentAttribute(QString * name, QVariant::Type type, void * data);

        /**
         * @brief Create a part of a SQL CREATE statement to declare a field
         * @line
         * @return "name TYPE"
         */
        QString createSQLField();

        /**
         * @brief Cast void pointer `data` depending on QVariant::type `type`
         * @return QVariant data
         */
        QString voidPointer2QString();
};

#endif // PERSISTENTATTRIBUTE_H
