#ifndef SQLBRIDGEMODEL_H
#define SQLBRIDGEMODEL_H

#include "sqlquerymodel.h"

class SqlBridgeModel : public SqlQueryModel
{
public:
    virtual QList<ColumnDescription> columnDescriptions() const;
    virtual QString tableName() const;
    virtual void initialise();
};

#endif // SQLBRIDGEMODEL_H
