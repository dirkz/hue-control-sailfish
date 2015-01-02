# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = hue-control-sailfish

CONFIG += sailfishapp

QT += sql

SOURCES +=

OTHER_FILES += qml/hue-control-sailfish.qml \
    qml/cover/CoverPage.qml \
    rpm/hue-control-sailfish.changes.in \
    rpm/hue-control-sailfish.spec \
    rpm/hue-control-sailfish.yaml \
    translations/*.ts \
    hue-control-sailfish.desktop \
    qml/pages/ShowBridges.qml \
    qml/pages/bridgemodel.py \
    qml/pages/BridgeInfo.qml \
    qml/pages/TextAreaLog.qml

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/hue-control-sailfish-de.ts

HEADERS +=

