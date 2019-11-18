#include "persistentattribute.h"

PersistentAttribute::PersistentAttribute(
        QString * attributeName, QVariant::Type attributeType, void * attribute) :
    name(*attributeName),
    type(attributeType),
    data(attribute)
{

}
