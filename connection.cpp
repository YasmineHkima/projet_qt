#include "connection.h"


connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Benevole");
db.setUserName("yasmina");//inserer nom de l'utilisateur
db.setPassword("yasmine12");//inserer mot de passe de cet utilisateur

if (db.open())
{test=true;
}
    return  test;
}
void connection::closeconnect(){db.close();}
