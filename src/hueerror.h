#ifndef HUEERROR_H
#define HUEERROR_H

#include <QObject>
#include <QJsonObject>
#include <QString>

class HueError : public QObject
{
    Q_OBJECT
public:
    explicit HueError(QObject *parent, const QJsonObject & jsonObject);

    static const int TYPE_NO_ERROR = 0;
    bool isError() const;

    Q_PROPERTY(int type READ type)
    int type();

    Q_PROPERTY(QString address READ address)
    QString address();

    Q_PROPERTY(QString description READ description)
    QString description();

signals:

public slots:

private:
    int m_type;
    QString m_address;
    QString m_description;

    void extractError(const QJsonObject & jsonObject);
};

#endif // HUEERROR_H
