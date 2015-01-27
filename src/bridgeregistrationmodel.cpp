#include <QDebug>
#include <QNetworkInterface>
#include <QCryptographicHash>
#include <QIODevice>

#include "bridgeregistrationmodel.h"

#include "hueerror.h"

static const QString DEVICE_TYPE = "hue-control";

BridgeRegistrationModel::BridgeRegistrationModel(QObject *parent) :
    QObject(parent),
    m_registrationStatus(tr("Unknown")),
    m_userName(tr("Unknown")),
    m_userNameGenerated(false)
{
    QObject::connect(&m_jsonObjectFetcher, &JsonObjectFetcher::jsonObjectsReceived,
                     this, &BridgeRegistrationModel::jsonObjectsReceived);
    QObject::connect(&m_jsonObjectFetcher, &JsonObjectFetcher::lastErrorChanged,
                     this, &BridgeRegistrationModel::setLastError);
}

BridgeRegistrationModel::~BridgeRegistrationModel()
{
    m_jsonObjectFetcher.disconnect();
}

QString BridgeRegistrationModel::lastError()
{
    return m_lastError;
}

void BridgeRegistrationModel::setLastError(const QString & errorString)
{
    m_lastError = errorString;
    emit lastErrorChanged(errorString);
    qDebug() << errorString;
}

QString BridgeRegistrationModel::registrationStatus()
{
    return m_registrationStatus;
}

QString BridgeRegistrationModel::userName()
{
    return m_userName;
}

QUrl BridgeRegistrationModel::bridgeApiUrl()
{
    return QUrl("http://" + bridgeIpAddress() + "/api/" + userName() + "/");
}

QUrl BridgeRegistrationModel::bridgeRegistrationUrl()
{
    return QUrl("http://" + bridgeIpAddress() + "/api/");
}

void BridgeRegistrationModel::updateRegistrationStatus()
{
    if (!m_userNameGenerated) {
        generateUserName();
    }
    m_jsonObjectFetcher.get(bridgeApiUrl());
}

void BridgeRegistrationModel::registerBridge()
{
    if (!m_userNameGenerated) {
        generateUserName();
    }
    QString data = QString("{\"devicetype\":\"%1\",\"username\":\"%2\"}").arg(DEVICE_TYPE).arg(userName());
    m_jsonObjectFetcher.post(bridgeRegistrationUrl(), data.toUtf8());
}

void BridgeRegistrationModel::jsonObjectsReceived(const QUrl & url, const QList<QJsonObject> & objects)
{
    if (url == bridgeApiUrl()) {
        if (objects.count() >= 1) {
            HueError error(this, objects.at(0));
            if (error.isError()) {
                setLastError(error.description());
                setRegistrationStatus(tr("Unregistered"));
            } else {
                setRegistrationStatus(tr("Registered"));
                setLastError("");
            }
        } else {
            setLastError(tr("No JSON objects fetched"));
            setRegistrationStatus(tr("Unknown"));
        }
    } else {
        if (objects.count() > 0) {
            if (objects.count() == 1) {
                HueError error(this, objects.at(0));
                if (error.isError()) {
                    setLastError(error.description());
                } else {
                    setRegistrationStatus(tr("Registered"));
                }
            }
        } else {
            setLastError(tr("no json objects fetched"));
            setRegistrationStatus(tr("Unknown"));
        }
    }
}

void BridgeRegistrationModel::generateUserName()
{
    QCryptographicHash crypto(QCryptographicHash::Md5);
    foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
        qDebug() << "interface" << interface.name() << interface.humanReadableName() << interface.hardwareAddress();
        crypto.addData(interface.name().toUtf8());
    }
    qDebug() << m_userName;
    setUserName(crypto.result().toHex());
    m_userNameGenerated = true;
}

QString BridgeRegistrationModel::bridgeIpAddress()
{
    return m_bridgeIpAddress;
}

void BridgeRegistrationModel::setBridgeIpAddress(const QString & ipAddress)
{
    m_bridgeIpAddress = ipAddress;
    emit bridgeIpAddressChanged(m_bridgeIpAddress);
}

void BridgeRegistrationModel::setUserName(const QString & name)
{
    if (name != m_userName) {
        m_userName = name;
        emit userNameChanged(m_userName);
        emit bridgeApiUrlChanged(bridgeApiUrl());
    }
}

void BridgeRegistrationModel::setRegistrationStatus(const QString & status)
{
    m_registrationStatus = status;
    emit registrationStatusChanged(m_registrationStatus);
}
