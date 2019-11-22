#ifndef PERSISTENTATTRIBUTE_H
#define PERSISTENTATTRIBUTE_H

#include <QVariant>

class PersistentAttribute
{
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
};

#endif // PERSISTENTATTRIBUTE_H
