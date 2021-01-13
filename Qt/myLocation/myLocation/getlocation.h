#ifndef GETLOCATION_H
#define GETLOCATION_H

#include <QObject>
#include <QGeoPositionInfoSource>
#include <QNetworkReply>

class getLocation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int erIn READ getErrorInfo WRITE setErrorFlag NOTIFY errorSignal)
    Q_PROPERTY(QString reLocation READ getLo WRITE setLo NOTIFY loChanged)
public:
    explicit getLocation(QObject *parent = 0);
    ~getLocation();
    QGeoPositionInfoSource *source;
    int erInfo;

    void setErrorFlag(int error);
    QString result;
signals:
    void errorSignal(int error);
    void loChanged(QString re);

public slots:
    void positionUpdated1(const QGeoPositionInfo &info);
    void startGet();
    void timeout();
    void getError(QGeoPositionInfoSource::Error error);

    int getErrorInfo();

    QString getLo();
    void setLo(QString re);
};

#endif // GETLOCATION_H
