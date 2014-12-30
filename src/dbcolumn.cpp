#include "dbcolumn.h"

QString DBColumn::name()
{
    return m_name;
}

QString DBColumn::type()
{
    return m_type;
}

void DBColumn::setName(const QString & name)
{
    m_name = name;
}

void DBColumn::setType(const QString & type)
{
    m_type = type;
}
