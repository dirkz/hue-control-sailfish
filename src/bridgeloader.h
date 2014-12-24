#ifndef BRIDGELOADER_H
#define BRIDGELOADER_H

#include <QObject>
#include <QNetworkSession>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>

#include "bridgemodel.h"

class BridgeLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BridgeModel *bridgeModel READ bridgeModel WRITE setBridgeModel)

public:
    explicit BridgeLoader(QObject *parent = 0);
    Q_INVOKABLE void loadBridges();
    BridgeModel *bridgeModel() const;
    void setBridgeModel(BridgeModel *model);

signals:
    void loadBridgesError(const QString& errorMessage);
    void loadBridgesFinished(const QJsonDocument& bridges, const QString& jsonString);

public slots:

private:
    QNetworkSession *m_networkSession;
    QNetworkAccessManager *m_networkAccessManager;
    BridgeModel *m_bridgeModel;

    bool openNetworkConnection();
    QNetworkAccessManager *networkAccessManager();

private slots:
    void loadBridgesRequestFinished(QNetworkReply *);
};

#endif // BRIDGELOADER_H
