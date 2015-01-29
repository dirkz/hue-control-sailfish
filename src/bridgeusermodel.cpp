#include <QDebug>
#include <QNetworkInterface>
#include <QCryptographicHash>

#include "bridgeusermodel.h"

BridgeUserModel::BridgeUserModel(QObject *parent) :
    QObject(parent)
{
}

void BridgeUserModel::setUserName(const QString & name)
{
    if (name != m_userName) {
        m_userName = name;
    }
}

QString BridgeUserModel::userName()
{
    if (m_userName.isEmpty()) {
        generateUserName();
    }
    return m_userName;
}

void BridgeUserModel::generateUserName()
{
    QCryptographicHash crypto(QCryptographicHash::Md5);
    foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
        qDebug() << "interface" << interface.name() << interface.humanReadableName() << interface.hardwareAddress();
        crypto.addData(interface.name().toUtf8());
    }
    setUserName("as" + crypto.result().toHex());
    qDebug() << m_userName;
}

