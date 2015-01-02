#include <QSqlQuery>

#include "sqlbridgemodel.h"

QString SqlBridgeModel::tableName() const
{
    return "bridges";
}

QList<ColumnDescription> SqlBridgeModel::columnDescriptions() const
{
    QList<ColumnDescription> columns;
    columns.append(ColumnDescription("name", "text"));
    columns.append(ColumnDescription("id", "text unique"));
    columns.append(ColumnDescription("macaddress", "text unique"));
    columns.append(ColumnDescription("internalipaddress", "text unique"));
    return columns;
}

void SqlBridgeModel::initialise()
{
    SqlQueryModel::initialise();
    QSqlQuery query;
    bool success = query.exec("insert into bridges values('hue', 'id', 'mac', '192.168.178.33')");
    if (!success) {
        qFatal("error inserting sample bridge");
    }
    refresh();
}

