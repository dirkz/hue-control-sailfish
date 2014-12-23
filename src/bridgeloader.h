#ifndef BRIDGELOADER_H
#define BRIDGELOADER_H

#include <QObject>

class BridgeLoader : public QObject
{
    Q_OBJECT
public:
    explicit BridgeLoader(QObject *parent = 0);

signals:

public slots:
    void loadBridges();

};

#endif // BRIDGELOADER_H
