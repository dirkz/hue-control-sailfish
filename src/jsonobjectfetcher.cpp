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

void JsonObjectFetcher::get(const QUrl & url)
{
    networkAccessManager()->get(QNetworkRequest(url));
}

void JsonObjectFetcher::post(const QUrl & url, const QByteArray & data)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkAccessManager()->post(request, data);
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
                        jsonObjects.append(jsonObject);
                    } else {
                        setLastError(tr("JSON elements are no objects"));
                    }
                }
                emit jsonObjectsReceived(reply->request().url(), jsonObjects);
            } else if (jsonDocument.isObject()) {
                QList<QJsonObject> jsonObjects;
                QJsonObject jsonObject = jsonDocument.object();
                jsonObjects.append(jsonObject);
                emit jsonObjectsReceived(reply->request().url(), jsonObjects);
            } else {
                setLastError(tr("Unsupported JSON response"));
            }
        }
    } else {
        qDebug("error: %s", qPrintable(reply->errorString()));
        QString errorString = reply->errorString();
        if (!errorString.isEmpty()) {
            setLastError(reply->errorString());
        } else {
            setLastError(tr("Unknown error when fetching JSON"));
        }
    }
}

