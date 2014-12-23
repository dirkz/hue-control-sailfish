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

SOURCES += src/hue-control-sailfish.cpp \
    src/bridgeloader.cpp

OTHER_FILES += qml/hue-control-sailfish.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    rpm/hue-control-sailfish.changes.in \
    rpm/hue-control-sailfish.spec \
    rpm/hue-control-sailfish.yaml \
    translations/*.ts \
    hue-control-sailfish.desktop \
    qml/pages/ShowBridges.qml

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/hue-control-sailfish-de.ts

HEADERS += \
    src/bridgeloader.h

