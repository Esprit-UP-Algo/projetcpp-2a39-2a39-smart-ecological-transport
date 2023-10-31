#include "connection.h"

#include<QtDebug>
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("Ghofrane");
db.setPassword("esprit18");

if (db.open())
test=true;





    return  test;
}
