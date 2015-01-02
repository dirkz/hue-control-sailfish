#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H

#include <QSqlQueryModel>

#include <QSqlQueryModel>
#include <QList>

class ColumnDescription
{
public:
    ColumnDescription(QString name, QString type);

    QString columnName();
    QString columnType();

private:
    QString m_columnName;
    QString m_columnType;
};

class SqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    SqlQueryModel();

    virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;
    virtual QHash<int,QByteArray> roleNames() const;
    Q_INVOKABLE virtual void initialise();
    virtual QList<ColumnDescription> columnDescriptions() const = 0;
    virtual QString tableName() const = 0;
    virtual QString createStandardQuery() const;
    virtual void refresh();

private:
    void createConnection();
};

#endif // SQLQUERYMODEL_H
