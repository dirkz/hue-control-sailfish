#include "lightstate.h"

LightState::LightState(QObject *parent) :
    QObject(parent)
{
}

bool LightState::on() {
    return m_on;
}

void LightState::setOn(bool on) {
    m_on = on;
    emit onChanged(on);
}

quint8 LightState::bri() {
    return m_bri;
}

void LightState::setBri(quint8 bri) {
    m_bri  = bri;
    emit briChanged(bri);
}

quint16 LightState::hue() {
    return m_hue;
}

void LightState::setHue(quint16 hue) {
    m_hue = hue;
    emit hueChanged(hue);
}

quint8 LightState::sat() {
    return m_sat;
}

void LightState::setSat(quint8 sat) {
    m_sat = sat;
    emit satChanged(sat);
}

QPointF LightState::xy() {
    return m_xy;
}

void LightState::setXy(QPointF xy) {
    m_xy = xy;
    emit xyChanged(xy);
}

quint16 LightState::ct() {
    return m_ct;
}

void LightState::setCt(quint16 ct) {
    m_ct = ct;
    emit ctChanged(ct);
}

QString LightState::alert() {
    return m_alert;
}

void LightState::setAlert(QString alert) {
    m_alert = alert;
    emit alertChanged(alert);
}

QString LightState::effect() {
    return m_effect;
}

void LightState::setEffect(QString effect) {
    m_effect = effect;
    emit effectChanged(effect);
}

QString LightState::colorMode() {
    return m_colorMode;
}

void LightState::setColorMode(QString colorMode) {
    m_colorMode = colorMode;
    emit colorModeChanged(colorMode);
}

bool LightState::reachable() {
    return m_reachable;
}

void LightState::setReachable(bool reachable) {
    m_reachable = reachable;
    emit reachableChanged(reachable);
}
