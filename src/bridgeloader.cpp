#include <QNetworkConfigurationManager>
#include <QNetworkConfiguration>
#include <QNetworkSession>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QByteArray>

#include "bridgeloader.h"

static const QString HUE_GET_BRIDGES_URL = "https://www.meethue.com/api/nupnp";

BridgeLoader::BridgeLoader(QObject *parent) :
    QObject(parent), m_networkSession(NULL)
{
}

bool BridgeLoader::openNetworkConnection()
{
    if (m_networkSession == NULL) {
        QNetworkConfigurationManager manager;
        const bool canStartIAP = (manager.capabilities() & QNetworkConfigurationManager::CanStartAndStopInterfaces);
        QNetworkConfiguration cfg = manager.defaultConfiguration();
        if (!cfg.isValid() || (!canStartIAP && cfg.state() != QNetworkConfiguration::Active)) {
            emit loadBridgesError("no access point found");
            qDebug("no access point found");
            return false;
        }
        m_networkSession = new QNetworkSession(cfg, this);
        m_networkSession->open();
        return m_networkSession->waitForOpened(-1);
    } else {
        return true;
    }
}

QNetworkAccessManager *BridgeLoader::getNetworkAccessManager()
{
    if (m_networkAccessManager == NULL) {
        m_networkAccessManager = new QNetworkAccessManager(this);
        connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(loadBridgesRequestFinished(QNetworkReply *)));
    }
    return m_networkAccessManager;
}

void BridgeLoader::loadBridges()
{
    qDebug("loadBridges()");
    openNetworkConnection();
    getNetworkAccessManager()->get(QNetworkRequest(QUrl(HUE_GET_BRIDGES_URL)));
}

void BridgeLoader::loadBridgesRequestFinished(QNetworkReply *reply)
{
    qDebug("loadBridgesFinished()");
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        QString result = QString(bytes);
        qDebug("bridges: %s", qPrintable(result));
        emit loadBridgesFinished(result);
    } else {
        qDebug("error: %s", qPrintable(reply->errorString()));
        QString errorString = reply->errorString();
        if (errorString != "") {
            emit loadBridgesError(reply->errorString());
        } else {
            emit loadBridgesError("unknown error");
        }
    }
}
