#ifndef DBCOLUMN_H
#define DBCOLUMN_H

#include <QString>

class DBColumn
{
public:
    QString name();
    QString type();
    void setName(const QString & name);
    void setType(const QString & type);

private:
    QString m_name;
    QString m_type;
};

#endif // DBCOLUMN_H
