#ifndef LOSQL_H
#define LOSQL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
class loSql : public QObject
{
    Q_OBJECT
public:
    loSql(){
        query_getTime=0;
        query_getLoca=0;
        query_getMark=0;
    }
    QSqlQuery *queryy;
    QSqlQuery *query_getTime;
    QSqlQuery *query_getLoca;
    QSqlQuery *query_getMark;

    bool initDateBase();

signals:

public slots:
    bool addNewLo(QString lo,QString mark);
    bool isLoExist(QString lo);
    int addRecord(QString lo);
    bool addMark(QString mark);
    bool delMark(QString mark);
    bool isMarkEx(QString mark);
    QString serchAllMark();
    QString searchLoMark(QString lo);
    bool delTable();
};

#endif // LOSQL_H
