#ifndef BRIDGEREGISTRATIONMODEL_H
#define BRIDGEREGISTRATIONMODEL_H

#include <QObject>
#include <QUrl>

#include "jsonobjectfetcher.h"

class BridgeRegistrationModel : public QObject
{
    Q_OBJECT
public:
    explicit BridgeRegistrationModel(QObject *parent = 0);
    ~BridgeRegistrationModel();

    Q_PROPERTY(QString lastError READ lastError WRITE setLastError NOTIFY lastErrorChanged)
    QString lastError();
    void setLastError(const QString & errorString);

    Q_PROPERTY(QString registrationStatus READ registrationStatus NOTIFY registrationStatusChanged)
    QString registrationStatus();

    Q_PROPERTY(QString userName READ userName NOTIFY userNameChanged)
    QString userName();

    Q_PROPERTY(QString bridgeIpAddress READ bridgeIpAddress WRITE setBridgeIpAddress NOTIFY bridgeIpAddressChanged)
    QString bridgeIpAddress();
    void setBridgeIpAddress(const QString & ipAddress);

    Q_PROPERTY(QUrl bridgeApiUrl READ bridgeApiUrl NOTIFY bridgeApiUrlChanged)
    QUrl bridgeApiUrl();

    Q_INVOKABLE void updateRegistrationStatus();
    Q_INVOKABLE void registerBridge();

signals:
    void lastErrorChanged(const QString & errorMessage);
    void userNameChanged(const QString & userName);
    void registrationStatusChanged(const QString & bridgeRegisteredInfoString);
    void bridgeIpAddressChanged(const QString & bridgeIpAddress);
    void bridgeApiUrlChanged(const QUrl & url);

public slots:

private:
    QString m_lastError;
    QString m_registrationStatus;
    QString m_userName;
    JsonObjectFetcher m_jsonObjectFetcher;
    bool m_userNameGenerated;
    QString m_bridgeIpAddress;

    void jsonObjectsReceived(const QUrl & url, const QList<QJsonObject> & objects);
    void generateUserName();

    void setUserName(const QString & name);
    void setRegistrationStatus(const QString & status);

    QUrl bridgeRegistrationUrl();
};

#endif // BRIDGEREGISTRATIONMODEL_H
