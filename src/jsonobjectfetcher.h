#ifndef JSONOBJECTFETCHER_H
#define JSONOBJECTFETCHER_H

#include <QObject>
#include <QList>
#include <QJsonObject>
#include <QUrl>
#include <QByteArray>

class QNetworkReply;
class QNetworkAccessManager;

class JsonObjectFetcher : public QObject
{
    Q_OBJECT
public:
    explicit JsonObjectFetcher(QObject *parent = 0);
    Q_INVOKABLE void get(const QUrl & url);
    Q_INVOKABLE void post(const QUrl & url, const QByteArray & data);
    Q_PROPERTY(QString lastError READ lastError WRITE setLastError NOTIFY lastErrorChanged)
    QString lastError();
    void setLastError(const QString & errorString);

signals:
    void lastErrorChanged(const QString & errorMessage);
    void jsonObjectsReceived(const QUrl &, const QList<QJsonObject> & objects);

public slots:

private slots:
    void jsonObjectsFetched(QNetworkReply *);

private:
    QString m_lastError;
    QNetworkAccessManager *m_networkAccessManager;
    QNetworkAccessManager *networkAccessManager();
};

#endif // JSONOBJECTFETCHER_H
