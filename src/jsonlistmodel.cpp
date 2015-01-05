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

void JsonListModel::fetchJson()
{
    QObject::connect(&m_jsonObjectFetcher, &JsonObjectFetcher::jsonObjectsReceived,
            this, &JsonListModel::jsonObjectsReceived);
    QObject::connect(&m_jsonObjectFetcher, &JsonObjectFetcher::lastErrorChanged,
            this, &JsonListModel::setLastError);
    m_jsonObjectFetcher.fetchJsonObjects(fetchUrl());
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

void JsonListModel::jsonObjectsReceived(const QList<QJsonObject> & objects)
{
    if (objects.count() > 0) {
        beginResetModel();
        m_jsonObjects.clear();
        foreach (const QJsonObject& jsonObject, objects) {
            qDebug() << jsonObject;
            m_jsonObjects.append(jsonObject);
        }
        generateRoleNamesFromJson();
        endResetModel();
    } else {
        setLastError(tr("no json objects fetched"));
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
