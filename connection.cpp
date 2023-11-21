#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection()
{



db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("Source_Projet2A");
db.setUserName("ROUAA");//inserer nom de l'utilisateur
db.setPassword("esprit23");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;
return test;
}
void Connection::closeConnection(){db.close();}




