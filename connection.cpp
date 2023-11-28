#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection()
{



db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("Projects");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("system");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;
return test;
}
void Connection::closeConnection(){db.close();}




