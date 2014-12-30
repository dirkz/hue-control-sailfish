#include "dbdescription.h"

DBDescription::DBDescription(QObject *parent) :
    QObject(parent), m_columns()
{
}

QString DBDescription::name()
{
    return m_name;
}

void DBDescription::setName(const QString & name)
{
    m_name = name;
}

void DBDescription::addColumn(const DBColumn & column)
{
    m_columns.append(column);
}
