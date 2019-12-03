#include "persistentattribute.h"
#include "QDebug"

using namespace std;

PersistentAttribute::PersistentAttribute(
        QString * attributeName, QVariant::Type attributeType, void * attribute) :
    name(*attributeName),
    type(attributeType),
    data(attribute)
{
    qDebug() << "name: " << this->name;
    qDebug() << "type: " << this->type;
    qDebug() << "data: " << this->voidPointer2QString() << endl;
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

QString PersistentAttribute::voidPointer2QString()
{
    QVariant variant = this->type;
             //enumeration on QMetaType instead on QVariant because float type is not in QVariant
            switch (static_cast<QMetaType::Type>(variant.type())) {
                case QMetaType::Int:
                    return QString::number(*static_cast<int*>(this->data));
                case QMetaType::Float:
                    return QString::number(*static_cast<float*>(this->data));
                case QMetaType::QString:
                    return *static_cast<QString*>(this->data);
                case QMetaType::QStringList:
                    return static_cast<QStringList*>(this->data)->join(",");
                default:;
                    throw std::invalid_argument("type of attribute not in Int, Float, QString, QStringList");
            }
}
