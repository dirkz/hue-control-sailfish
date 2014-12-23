#ifndef BRIDGELOADER_H
#define BRIDGELOADER_H

#include <QObject>
#include <QNetworkSession>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class BridgeLoader : public QObject
{
    Q_OBJECT
public:
    explicit BridgeLoader(QObject *parent = 0);

signals:
    void loadBridgesError(QString msg);
    void loadBridgesFinished(QString msg);

public slots:
    void loadBridges();

private:
    QNetworkSession *m_networkSession;
    QNetworkAccessManager *m_networkAccessManager;

    bool openNetworkConnection();
    QNetworkAccessManager *getNetworkAccessManager();

private slots:
    void loadBridgesRequestFinished(QNetworkReply *);
};

#endif // BRIDGELOADER_H
