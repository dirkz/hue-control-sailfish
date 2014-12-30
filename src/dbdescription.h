#ifndef DBDESCRIPTION_H
#define DBDESCRIPTION_H

#include <QObject>
#include "dbcolumn.h"

class DBDescription : public QObject
{
    Q_OBJECT
public:
    explicit DBDescription(QObject *parent = 0);
    Q_PROPERTY(QString name READ name WRITE setName)

    QString name();
    void setName(const QString & name);

    Q_INVOKABLE void addColumn(const DBColumn & column);

signals:

public slots:

private:
    QString m_name;
    QList<DBColumn> m_columns;

};

#endif // DBDESCRIPTION_H
