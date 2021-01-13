#include "getlocation.h"
#include <QDebug>

getLocation::getLocation(QObject *parent) : QObject(parent)
{
    source = QGeoPositionInfoSource::createDefaultSource(this);

    connect(source,SIGNAL(positionUpdated(QGeoPositionInfo)),
                         this, SLOT(positionUpdated1(QGeoPositionInfo)));
    connect(source,SIGNAL(updateTimeout()),this, SLOT(timeout()));
    connect(source,SIGNAL(error(QGeoPositionInfoSource::Error)),this, SLOT(getError(QGeoPositionInfoSource::Error)));
    source->setUpdateInterval(3000);
    source->setPreferredPositioningMethods(QGeoPositionInfoSource::AllPositioningMethods);


    result="";
}

getLocation::~getLocation()
{
    source->deleteLater();
    result="";
}

void getLocation::setErrorFlag(int error)
{
    erInfo=error;
}

void getLocation::positionUpdated1(const QGeoPositionInfo &info)
{
    if(info.isValid()){
        QDateTime time=info.timestamp();
//        double longitude=info.coordinate().longitude();
//        double latitude=info.coordinate().latitude();
        QString strinfo=info.coordinate().toString(QGeoCoordinate::Degrees);

        qDebug()<<time.toString("yyyy-MM-dd-hh-mm-ss")<<"___"<<info.coordinate().toString(QGeoCoordinate::Degrees);
//        strinfo.split(",").length()
                QString latitude=strinfo.split(",")[0].replace(QString("°"), QString(""));
                QString longitude=strinfo.split(",")[1].replace(QString("°"), QString(""));

//        QNetworkRequest request;
//        QString url=(netUrl+"location="+QString::number(latitude,10,3)+","+QString::number(longitude,10,3)+"&output=json&pois=1&ak="+myAK);

        QString re=latitude+","+longitude;
        qDebug()<<"rere"<<re;
        setLo(re);
        emit loChanged(re);


    }else{
        ////错误代码：1005：无效地址信息
        qDebug()<<"无效值";
        setErrorFlag(1005);
        emit errorSignal(1005);
    }
}

void getLocation::startGet()
{
    source->requestUpdate(10000);
}

void getLocation::timeout()
{/////超时：错误代码1004
    qDebug()<<"超时！！";
    setErrorFlag(1004);
    emit errorSignal(1004);
}

void getLocation::getError(QGeoPositionInfoSource::Error error)
{
    /////错误代码：1000：无权限
    /// 1001：定位服务关闭
    /// 1002：未知错误
    /// 1003：无错误
    if(error!=3){
        setErrorFlag(error+1000);
        emit errorSignal(error+1000);
    }
}

int getLocation::getErrorInfo()
{
    return erInfo;
}

QString getLocation::getLo()
{
    return result;
}

void getLocation::setLo(QString re)
{
    result=re;
}

