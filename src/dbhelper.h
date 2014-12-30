#ifndef DBHELPER_H
#define DBHELPER_H

#include <QObject>

#include "dbdescription.h"

class DBHelper : public QObject
{
    Q_OBJECT
public:
    explicit DBHelper(QObject *parent = 0);
    Q_INVOKABLE void create();

signals:

public slots:

private:
    DBDescription m_dbDescription;
};

#endif // DBHELPER_H
