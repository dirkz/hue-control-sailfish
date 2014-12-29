#include <QByteArray>

#include "bridgemodel.h"

const static QString KEY_JSON_BRIDGE_ID = "id";
const static QString KEY_JSON_BRIDGE_IP = "internalipaddress";
const static QString KEY_JSON_BRIDGE_MAC = "macaddress";
const static QString KEY_JSON_BRIDGE_NAME = "name";

Bridge::Bridge(const QString& bridgeId, const QString& ip, const QString& mac, const QString& name) :
    m_bridgeId(bridgeId), m_ip(ip), m_mac(mac), m_name(name)
{
}

Bridge::Bridge(const QJsonObject& jsonObject) :
    m_bridgeId(jsonObject.value(KEY_JSON_BRIDGE_ID).toString()),
    m_ip(jsonObject.value(KEY_JSON_BRIDGE_IP).toString()),
    m_mac(jsonObject.value(KEY_JSON_BRIDGE_MAC).toString()),
    m_name(jsonObject.value(KEY_JSON_BRIDGE_NAME).toString())
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
    Q_UNUSED(parent)
    return rowCount();
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

bool BridgeModel::removeRows(int row, int count, const QModelIndex & parent)
{
    if (count > 0) {
        beginRemoveRows(parent, row, row + count - 1);
        for (int i = 0; i < count; ++i) {
            m_bridges.removeAt(row);
        }
        endRemoveRows();
        return true;
    } else {
        return false;
    }
}

bool BridgeModel::remove(int row)
{
    return removeRow(row);
}

bool BridgeModel::clearAll()
{
    return removeRows(0, m_bridges.count());
}
