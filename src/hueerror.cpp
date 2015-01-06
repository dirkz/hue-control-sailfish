#include "hueerror.h"

#include <QJsonValue>

HueError::HueError(QObject *parent, const QJsonObject & jsonObject) :
    QObject(parent), m_type(TYPE_NO_ERROR), m_address(""), m_description("")
{
    extractError(jsonObject);
}

void HueError::extractError(const QJsonObject & jsonObject)
{
    QJsonValue value = jsonObject.value("error");
    if (!value.isUndefined()) {
        QJsonObject obj = value.toObject();
        value = obj.value("type");
        if (!value.isUndefined()) {
            m_type = value.toInt();
        }
        value = obj.value("description");
        if (!value.isUndefined()) {
            m_description = value.toString();
        }
        value = obj.value("address");
        if (!value.isUndefined()) {
            m_address = value.toString();
        }
    }
}

bool HueError::isError() const
{
    return m_type != TYPE_NO_ERROR;
}

int HueError::type()
{
    return m_type;
}

QString HueError::address()
{
    return m_address;
}

QString HueError::description()
{
    return m_description;
}
