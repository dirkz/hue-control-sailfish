#include <QNetworkConfigurationManager>
#include <QNetworkConfiguration>
#include <QNetworkSession>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

#include "bridgeloader.h"

static const QString HUE_GET_BRIDGES_URL = "https://www.meethue.com/api/nupnp";

BridgeLoader::BridgeLoader(QObject *parent) :
    QObject(parent), m_networkSession(NULL)
{
}

BridgeModel *BridgeLoader::bridgeModel() const
{
    return m_bridgeModel;
}

void BridgeLoader::setBridgeModel(BridgeModel *model)
{
    m_bridgeModel = model;
}

bool BridgeLoader::openNetworkConnection()
{
    if (m_networkSession == NULL) {
        QNetworkConfigurationManager manager;
        const bool canStartIAP = (manager.capabilities() & QNetworkConfigurationManager::CanStartAndStopInterfaces);
        QNetworkConfiguration cfg = manager.defaultConfiguration();
        if (!cfg.isValid() || (!canStartIAP && cfg.state() != QNetworkConfiguration::Active)) {
            emit loadBridgesError(tr("no access point found"));
            return false;
        }
        m_networkSession = new QNetworkSession(cfg, this);
        m_networkSession->open();
        return m_networkSession->waitForOpened(-1);
    } else {
        return true;
    }
}

QNetworkAccessManager *BridgeLoader::networkAccessManager()
{
    if (m_networkAccessManager == NULL) {
        m_networkAccessManager = new QNetworkAccessManager(this);
        connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(loadBridgesRequestFinished(QNetworkReply *)));
    }
    return m_networkAccessManager;
}

void BridgeLoader::loadBridges()
{
    openNetworkConnection();
    networkAccessManager()->get(QNetworkRequest(QUrl(HUE_GET_BRIDGES_URL)));
}

void BridgeLoader::loadBridgesRequestFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        QJsonParseError *parseError = NULL;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(bytes, parseError);
        if (parseError != NULL) {
            emit loadBridgesError(parseError->errorString());
        } else {
            if (jsonDocument.isArray()) {
                QJsonArray jsonArray = jsonDocument.array();
                foreach (const QJsonValue& jsonBridge, jsonArray) {
                    if (jsonBridge.isObject()) {
                        Bridge bridge(jsonBridge.toObject());
                        bridgeModel()->addBridge(bridge);
                    } else {
                        emit loadBridgesError(tr("invalid bridge format received"));
                    }
                }
            } else {
                emit loadBridgesError(tr("no bridge array found"));
            }
        }
    } else {
        qDebug("error: %s", qPrintable(reply->errorString()));
        QString errorString = reply->errorString();
        if (!errorString.isEmpty()) {
            emit loadBridgesError(reply->errorString());
        } else {
            emit loadBridgesError(tr("unknown error when loading bridges"));
        }
    }
}
