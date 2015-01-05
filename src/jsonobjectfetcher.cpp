#include <QDebug>
#include <QNetworkReply>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include "jsonobjectfetcher.h"

JsonObjectFetcher::JsonObjectFetcher(QObject *parent) :
    QObject(parent), m_networkAccessManager(NULL)
{
}

QString JsonObjectFetcher::lastError()
{
    return m_lastError;
}

void JsonObjectFetcher::setLastError(const QString & errorString)
{
    m_lastError = errorString;
    emit lastErrorChanged(errorString);
    qDebug() << errorString;
}

QNetworkAccessManager *JsonObjectFetcher::networkAccessManager()
{
    if (m_networkAccessManager == NULL) {
        m_networkAccessManager = new QNetworkAccessManager(this);
        QObject::connect(m_networkAccessManager, &QNetworkAccessManager::finished,
                this, &JsonObjectFetcher::jsonObjectsFetched);
    }
    return m_networkAccessManager;
}

void JsonObjectFetcher::fetchJsonObjects(QUrl url)
{
    networkAccessManager()->get(QNetworkRequest(url));
}

void JsonObjectFetcher::jsonObjectsFetched(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        QJsonParseError *parseError = NULL;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(bytes, parseError);
        if (parseError != NULL) {
            setLastError(parseError->errorString());
        } else {
            if (jsonDocument.isArray()) {
                QList<QJsonObject> jsonObjects;
                QJsonArray jsonArray = jsonDocument.array();
                foreach (const QJsonValue& jsonValue, jsonArray) {
                    if (jsonValue.isObject()) {
                        QJsonObject jsonObject = jsonValue.toObject();
                        qDebug() << jsonObject;
                        jsonObjects.append(jsonObject);
                    } else {
                        setLastError(tr("json elements are no objects"));
                    }
                }
                emit jsonObjectsReceived(jsonObjects);
            } else {
                setLastError(tr("returned json is not an array"));
            }
        }
    } else {
        qDebug("error: %s", qPrintable(reply->errorString()));
        QString errorString = reply->errorString();
        if (!errorString.isEmpty()) {
            setLastError(reply->errorString());
        } else {
            setLastError(tr("unknown error when fetching json"));
        }
    }
}

