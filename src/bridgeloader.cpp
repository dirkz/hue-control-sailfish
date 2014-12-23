#include "bridgeloader.h"

BridgeLoader::BridgeLoader(QObject *parent) :
    QObject(parent)
{
}

void BridgeLoader::loadBridges()
{
    qDebug("loadBridges()");
}
