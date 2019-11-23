#include "persistentattribute.h"

using namespace std;

PersistentAttribute::PersistentAttribute(
        QString * attributeName, QVariant::Type attributeType, void * attribute) :
    name(*attributeName),
    type(attributeType),
    data(attribute)
{

}

QString PersistentAttribute::createSQLField()
{
    return (QString(this->name) + QString(" ") + this->Qtype2SQLType());
}

QString PersistentAttribute::Qtype2SQLType()
{
    QVariant variant = this->type;
             //enumeration on QMetaType instead on QVariant because float type is not in QVariant
            switch (static_cast<QMetaType::Type>(variant.type())) {
                case QMetaType::Int:
                    return QString("INT");
                case QMetaType::Float:
                    return QString("FLOAT");
                case QMetaType::QString:
                    return QString("VARCHAR(255)");
                case QMetaType::QStringList:
                    return QString("VARCHAR(1023)");
                default:;
                    throw std::invalid_argument("type of attribute not in Int, Float, QString, QStringList");
            }
}
