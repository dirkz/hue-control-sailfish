#ifndef LIGHTSTATE_H
#define LIGHTSTATE_H

#include <QObject>
#include <QPointF>

class LightState : public QObject
{
    Q_OBJECT
public:
    explicit LightState(QObject *parent = 0);

    Q_PROPERTY(bool on READ on WRITE setOn NOTIFY onChanged)
    Q_PROPERTY(quint8 bri READ bri WRITE setBri NOTIFY briChanged)
    Q_PROPERTY(quint16 hue READ hue WRITE setHue NOTIFY hueChanged)
    Q_PROPERTY(quint8 sat READ sat WRITE setSat NOTIFY satChanged)
    Q_PROPERTY(QPointF xy READ xy WRITE setXy NOTIFY xyChanged)
    Q_PROPERTY(quint16 ct READ ct WRITE setCt NOTIFY ctChanged)
    Q_PROPERTY(QString alert READ alert WRITE setAlert NOTIFY alertChanged)
    Q_PROPERTY(QString effect READ effect WRITE setEffect NOTIFY effectChanged)
    Q_PROPERTY(QString colormode READ colorMode WRITE setColorMode NOTIFY colorModeChanged)
    Q_PROPERTY(bool reachable READ reachable WRITE setReachable NOTIFY reachableChanged)

    bool on();
    quint8 bri();
    quint16 hue();
    quint8 sat();
    QPointF xy();
    quint16 ct();
    QString alert();
    QString effect();
    QString colorMode();
    bool reachable();

    void setOn(bool on);
    void setBri(quint8 bri);
    void setHue(quint16 hue);
    void setSat(quint8 sat);
    void setXy(QPointF xy);
    void setCt(quint16 ct);
    void setAlert(QString alert);
    void setEffect(QString effect);
    void setColorMode(QString colorMode);
    void setReachable(bool reachable);

signals:
    void onChanged(const bool & on);
    void briChanged(const quint8 & bri);
    void hueChanged(const quint16 & hue);
    void satChanged(const quint8 & sat);
    void xyChanged(const QPointF & xy);
    void ctChanged(const quint16 & ct);
    void alertChanged(const QString & alert);
    void effectChanged(const QString & effect);
    void colorModeChanged(const QString & colorMode);
    void reachableChanged(const bool & reachable);

public slots:

private:
    bool m_on;
    quint8 m_bri;
    quint16 m_hue;
    quint8 m_sat;
    QPointF m_xy;
    quint16 m_ct;
    QString m_alert;
    QString m_effect;
    QString m_colorMode;
    bool m_reachable;

};

#endif // LIGHTSTATE_H
