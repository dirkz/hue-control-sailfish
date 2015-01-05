#ifndef JSONLISTMODEL_H
#define JSONLISTMODEL_H

#include <QAbstractListModel>
#include <QModelIndex>
#include <QUrl>
#include <QHash>
#include <QList>
#include <QJsonObject>

class QNetworkReply;
class QNetworkAccessManager;

class JsonListModel : public QAbstractListModel
{
    Q_OBJECT

static const QString ID_REPLACEMENT;

public:
    explicit JsonListModel(QObject *parent = 0);
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void fetchJson();

    Q_PROPERTY(QUrl fetchUrl READ fetchUrl WRITE setFetchUrl)
    void setFetchUrl(const QUrl & url);
    QUrl fetchUrl();

    Q_PROPERTY(QString lastError READ lastError WRITE setLastError NOTIFY lastErrorChanged)
    QString lastError();
    void setLastError(const QString & errorString);

signals:
    void lastErrorChanged(const QString & errorMessage);

public slots:

private slots:
    void fetchJsonFinished(QNetworkReply *);

private:
    QUrl m_fetchUrl;
    QNetworkAccessManager *m_networkAccessManager;
    QString m_lastError;
    QList<QByteArray> m_roleNames;
    QList<QJsonObject> m_jsonObjects;

    QNetworkAccessManager *networkAccessManager();
    void generateRoleNamesFromJson();
};

#endif // JSONLISTMODEL_H
