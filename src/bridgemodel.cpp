#include <QByteArray>

#include "bridgemodel.h"

Bridge::Bridge(const QString &bridgeId, const QString &ip, const QString &mac, const QString &name) :
    m_bridgeId(bridgeId), m_ip(ip), m_mac(mac), m_name(name)
{
}

QString Bridge::bridgeId() const
{
    return m_bridgeId;
}

QString Bridge::ip() const
{
    return m_ip;
}

QString Bridge::mac() const
{
    return m_mac;
}

QString Bridge::name() const
{
    return m_name;
}

BridgeModel::BridgeModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QHash<int, QByteArray> BridgeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "bridgeId";
    roles[IpRole] = "ip";
    roles[MacRole] = "mac";
    roles[NameRole] = "name";
    return roles;
}


void BridgeModel::addBridge(const Bridge &bridge)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_bridges << bridge;
    endInsertRows();
}

int BridgeModel::rowCount(const QModelIndex & parent) const {
    return m_bridges.count();
}

QVariant BridgeModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() > m_bridges.count())
        return QVariant();

    const Bridge &bridge = m_bridges[index.row()];
    switch (role) {
    case IdRole:
        return bridge.bridgeId();
    case IpRole:
        return bridge.ip();
    case MacRole:
        return bridge.mac();
    case NameRole:
        return bridge.name();
    default:
        return QVariant();
    }
}

int BridgeModel::rowCount() const
{
    return m_bridges.count();
}
