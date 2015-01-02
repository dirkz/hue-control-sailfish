#include <QSqlQuery>
#include <QSqlRecord>

#include "sqlquerymodel.h"

ColumnDescription::ColumnDescription(QString name, QString type) :
    m_columnName(name), m_columnType(type)
{
}

QString ColumnDescription::columnName()
{
    return m_columnName;
}

QString ColumnDescription::columnType()
{
    return m_columnType;
}

SqlQueryModel::SqlQueryModel() :
    QSqlQueryModel()
{
}

void SqlQueryModel::initialise()
{
    createConnection();
    refresh();
}

QString SqlQueryModel::createStandardQuery() const
{
    QString queryString("select ");
    bool columnAdded = false;
    foreach (ColumnDescription c, columnDescriptions()) {
        if (columnAdded) {
            queryString.append(", ");
        }
        queryString.append(c.columnName());
        columnAdded = true;
    }
    queryString.append(" from " + tableName());
    return queryString;
}

void SqlQueryModel::refresh()
{
    setQuery(createStandardQuery());
}

void SqlQueryModel::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        qFatal("Cannot open database");
        return;
    }

    QSqlQuery query;
    QString queryString("create table " + tableName() + " (");
    bool columnAdded = false;
    foreach (ColumnDescription c, columnDescriptions()) {
        if (columnAdded) {
            queryString.append(", ");
        }
        queryString.append(c.columnName() + " " + c.columnType());
        columnAdded = true;
    }
    queryString.append(")");
    bool success = query.exec(queryString);
    if (!success) {
        qFatal("error creating database");
    }
    return;
}

QHash<int,QByteArray> SqlQueryModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    int roleIndex = Qt::UserRole + 1;
    foreach (ColumnDescription c, columnDescriptions()) {
        roles[roleIndex++] = c.columnName().toUtf8();
    }
    return roles;
}

QVariant SqlQueryModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole) {
        return QSqlQueryModel::data(item, role);
    } else {
        int columnIdx = role - Qt::UserRole - 1;
        QSqlRecord r = record(item.row());
        QVariant v = r.value(columnIdx);
        return v;
    }
}
