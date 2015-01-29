#ifndef BRIDGEUSERMODEL_H
#define BRIDGEUSERMODEL_H

#include <QObject>

class BridgeUserModel : public QObject
{
    Q_OBJECT
public:
    explicit BridgeUserModel(QObject *parent = 0);

    Q_PROPERTY(QString userName READ userName NOTIFY userNameChanged)
    QString userName();

signals:
    void userNameChanged(const QString & userName);

public slots:

private:
    QString m_userName;

    void setUserName(const QString & name);
    void generateUserName();
};

#endif // BRIDGEUSERMODEL_H
