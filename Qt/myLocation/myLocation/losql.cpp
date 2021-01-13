#include "losql.h"
#include <QDir>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
#include <QSqlRecord>
#include <QTextStream>
QSqlDatabase db;
#define QT_DB_NAME QString("location.sqlite")

bool loSql::initDateBase()
{
    QString dllDir = QDir::currentPath();
    db = QSqlDatabase::addDatabase("QSQLITE");
//    QString typeos=QSysInfo::productType();
//    int oosType=0;
//    if (typeos=="android")          oosType=1;
//    if (typeos=="windows")          oosType=10;
    QDir *temp = new QDir;
    bool exist = temp->exists(dllDir+"/f9");
    if(!exist)
        temp->mkdir(dllDir+"/f9");

    db.setDatabaseName(dllDir+"/f9/" + QT_DB_NAME);
    qDebug()<<dllDir+"/f9/" + QT_DB_NAME;
    db.setConnectOptions("QSQLITE_ENABLE_SHARED_CACHE = 1 ;QSQLITE_BUSY_TIMEOUT = 10");

    if(!db.open())
    {
        return false;
    }
    db.open();
    queryy=new QSqlQuery(db);
    queryy->exec("CREATE TABLE IF NOT EXISTS loMark (l_location VARCHAR NOT NULL,l_mark VARCHAR )");
    queryy->exec("CREATE TABLE IF NOT EXISTS duTime (s_time DATETIME NOT NULL,s_lono INTEGER NOT NULL )");
    queryy->exec("CREATE TABLE IF NOT EXISTS mark (m_mark nvarchar(50) )");

    return true;
}

bool loSql::addNewLo(QString lo, QString mark)
{
    db.open();
    query_getLoca=0;
    if(query_getLoca == 0)
    {
        query_getLoca = new QSqlQuery(db);
    }
    query_getLoca->clear();
    QString insrtSql="";
    QSqlError err;
    if(isLoExist(lo)){
        insrtSql="update loMark set l_mark='"+mark+"' where l_location='"+lo+"'";
    }else{
        insrtSql="insert into loMark VALUES ( '"+lo+"','"+mark+"')";
    }
    query_getLoca->exec(insrtSql);
    err = query_getLoca->lastError();
    QTextStream(stdout)<<err.text()<<"addNewLo";
    if(err.isValid())
        return false;
    return true;

}

bool loSql::isLoExist(QString lo)
{
    db.open();
    query_getLoca=0;
    if(query_getLoca == 0)
    {
        query_getLoca = new QSqlQuery(db);
    }
    query_getLoca->clear();


    QString queryId;
    queryId="select  * from loMark where l_location='"+lo+"'";
    query_getLoca->exec(queryId);
    while(query_getLoca->next()){
        return true;
    }
    return false;
}

int loSql::addRecord(QString lo)
{
//    s_time DATETIME NOT NULL,s_lono INTEGER NOT NULL
    db.open();
    if(query_getTime == 0)
    {
        query_getTime = new QSqlQuery(db);
    }
    query_getTime->clear();

    QString queryId;
    queryId="select * from duTime order by s_time desc limit 1";
    query_getTime->exec(queryId);
    int maxIndex=query_getTime->record().indexOf("s_time");
    QDateTime time;
    QDateTime now=QDateTime::currentDateTime();
    bool hasTime=false;
    while(query_getTime->next()){
        hasTime=true;
        time=  QDateTime::fromString(query_getTime->value(maxIndex).toString(),"yyyyMMddHHmmss");
    }
    if(hasTime&&(time.addSecs(3600)>now))
        return 1000;//1000:打卡时间间隔太短（不足1小时）

    QSqlQuery queryInsert;
    QSqlError err;
    qDebug()<<now.toString("yyyyMMddHHmmss");
    queryId="insert into duTime VALUES ('"+now.toString("yyyyMMddHHmmss")+"' , '"+lo+"')";
    queryInsert.exec(queryId);
    err=queryInsert.lastError();
    QTextStream(stdout)<<err.text()<<"11111";
//    qDebug()<<err;
    if(err.isValid())
        return 1001;//插入数据库失败
    return 0;

}

bool loSql::addMark(QString mark)
{
//    CREATE TABLE IF NOT EXISTS mark (m_mark VARCHAR NOT NULL
    query_getMark=0;
    if(query_getMark == 0)
    {
        query_getMark = new QSqlQuery(db);
    }
    query_getMark->clear();
    QString insrtSql="";
    QSqlError err;
    bool isex=isMarkEx(mark);
    if(isex)
        return false;
    else{
        insrtSql="insert into mark  VALUES ('"+mark+"')";
    }
    query_getMark->exec(insrtSql);
    err = query_getMark->lastError();
    QTextStream(stdout)<<err.text()<<insrtSql;
    if(err.isValid())
        return false;
    return true;
}

bool loSql::delMark(QString mark)
{
    query_getMark=0;
    if(query_getMark == 0)
    {
        query_getMark = new QSqlQuery(db);
    }
    query_getMark->clear();
    QString delSql="";
    QSqlError err;
    bool isex=isMarkEx(mark);
    if(isex)
        return false;
    else{
        delSql="DELETE FROM mark where m_mark='"+mark+"'";
    }
    query_getMark->exec(delSql);
    err = query_getMark->lastError();
    QTextStream(stdout)<<err.text()<<delSql;
    if(err.isValid())
        return false;
    return true;
}

bool loSql::isMarkEx(QString mark)
{
    db.open();
    query_getMark=0;
    if(query_getMark == 0)
    {
        query_getMark = new QSqlQuery(db);
    }
    query_getMark->clear();


    QString queryId;
    queryId="select  * from mark where m_mark='"+mark+"'";
    query_getMark->exec(queryId);
    while(query_getMark->next()){
        return true;
    }
    return false;
}

QString loSql::serchAllMark()
{
    db.open();
    query_getMark=0;
    if(query_getMark == 0)
    {
        query_getMark = new QSqlQuery(db);
    }
    query_getMark->clear();


    QString queryId;
    queryId="select  * from mark ";
    query_getMark->exec(queryId);
    QString re="";
    int index=query_getMark->record().indexOf("m_mark");
    while(query_getMark->next()){
        re+= (query_getMark->value(index).toString())+"***";
    }

    return re;
}

QString loSql::searchLoMark(QString lo)
{
    db.open();
    query_getLoca=0;
    if(query_getLoca == 0)
    {
        query_getLoca = new QSqlQuery(db);
    }
    query_getLoca->clear();
    QString queryId;
    QString re="";
    queryId="select  * from loMark where l_location='"+lo+"'";
    query_getLoca->exec(queryId);
    int index=query_getLoca->record().indexOf("l_mark");
    while(query_getLoca->next()){
        re= (query_getLoca->value(index).toString());
    }
    return re;
}

bool loSql::delTable()
{
    db.open();
    query_getLoca=0;
    if(query_getLoca == 0)
    {
        query_getLoca = new QSqlQuery(db);
    }
    query_getLoca->clear();
    bool re=true;
    re=re&query_getLoca->exec("Delete loMark");
    re=re&query_getLoca->exec("Delete duTime");
    re=re&query_getLoca->exec("Delete mark");

    return re;

}
