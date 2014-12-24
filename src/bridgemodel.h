#ifndef BRIDGEMODEL_H
#define BRIDGEMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class Bridge
{
public:
    Bridge(const QString &bridgeId, const QString &ip, const QString &mac, const QString &name);

    QString bridgeId() const;
    QString ip() const;
    QString mac() const;
    QString name() const;

private:
    QString m_bridgeId;
    QString m_ip;
    QString m_mac;
    QString m_name;
};

class BridgeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum BridgeRoles {
        IdRole = Qt::UserRole + 1,
        IpRole,
        MacRole,
        NameRole
    };

    explicit BridgeModel(QObject *parent = 0);

    void addBridge(const Bridge &bridge);
    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex & parent) const;
    QVariant data(const QModelIndex & index, int role) const;

signals:

public slots:

private:
    QList<Bridge> m_bridges;

    int rowCount() const;
};

#endif // BRIDGEMODEL_H
