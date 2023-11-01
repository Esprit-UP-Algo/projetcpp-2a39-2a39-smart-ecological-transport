#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


class Connection
{

public:
    QSqlDatabase db;
    Connection();
    bool createconnect();
    void closeconnect();

};

#endif // CONNECTION_H
