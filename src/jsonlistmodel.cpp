#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>
#include <QStringList>

#include "jsonlistmodel.h"

const QString JsonListModel::ID_REPLACEMENT = "theId";

JsonListModel::JsonListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

void JsonListModel::setFetchUrl(const QUrl & url)
{
    m_fetchUrl = url;
    fetchJson();
}

QUrl JsonListModel::fetchUrl()
{
    return m_fetchUrl;
}

QString JsonListModel::lastError()
{
    return m_lastError;
}

void JsonListModel::setLastError(const QString & errorString)
{
    m_lastError = errorString;
    emit lastErrorChanged(errorString);
    qDebug() << errorString;
}

QNetworkAccessManager *JsonListModel::networkAccessManager()
{
    if (m_networkAccessManager == NULL) {
        m_networkAccessManager = new QNetworkAccessManager(this);
        connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(fetchJsonFinished(QNetworkReply *)));
    }
    return m_networkAccessManager;
}

void JsonListModel::fetchJson()
{
    networkAccessManager()->get(QNetworkRequest(fetchUrl()));
}

void JsonListModel::generateRoleNamesFromJson()
{
    m_roleNames.clear();
    if (m_jsonObjects.count() > 0) {
        QJsonObject jsonObject = m_jsonObjects.at(0);
        foreach (const QString & key, jsonObject.keys()) {
            m_roleNames.append(key.toUtf8());
        }
    }
}

void JsonListModel::fetchJsonFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        QJsonParseError *parseError = NULL;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(bytes, parseError);
        if (parseError != NULL) {
            setLastError(parseError->errorString());
        } else {
            if (jsonDocument.isArray()) {
                beginResetModel();
                m_jsonObjects.clear();
                QJsonArray jsonArray = jsonDocument.array();
                foreach (const QJsonValue& jsonValue, jsonArray) {
                    if (jsonValue.isObject()) {
                        QJsonObject jsonObject = jsonValue.toObject();
                        qDebug() << jsonObject;
                        m_jsonObjects.append(jsonObject);
                    } else {
                        setLastError(tr("json elements are no objects"));
                    }
                }
                generateRoleNamesFromJson();
                endResetModel();
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

QHash<int, QByteArray> JsonListModel::roleNames() const
{
    QHash<int, QByteArray> theRoleNames;
    int index = Qt::UserRole;
    foreach (QByteArray role, m_roleNames) {
        if (role == "id") {
            role = ID_REPLACEMENT.toUtf8();
        }
        theRoleNames.insert(index++, role);
    }
    return theRoleNames;
}

int JsonListModel::rowCount (const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return m_jsonObjects.count();
}

QVariant JsonListModel::data (const QModelIndex & index, int role) const
{
    if (index.row() < m_jsonObjects.count()) {
        QByteArray roleNameBytes = m_roleNames.at(role - Qt::UserRole);
        QJsonObject jsonObject = m_jsonObjects.at(index.row());
        QJsonValue value = jsonObject.value(roleNameBytes);
        return value;
    }
    return QVariant();
}
