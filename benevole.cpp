#include "benevole.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
Benevole::Benevole(int id_b,QString nom ,QString prenom,QString rib,QString date_b,QString numero,QString email,QString type_donation,QString argent)
{
       this->id_b=id_b;
       this->nom=nom;
       this->prenom=prenom;
       this->rib=rib;
    this->date_b=date_b;
    this->numero=numero;
    this->email=email;
    this->type_donation=type_donation;
    this->argent=argent;
}

bool Benevole::ajouter()
{
    //TODO

    QSqlQuery query;
          QString res=QString::number(id_b);
          query.prepare("INSERT INTO Benevole (id_b, nom, prenom,rib,date_b,numero,email,type_donation, argent) ""VALUES (:id_b, :nom, :prenom,:rib,:date_b,:numero,:email,:type_donation,:argent)");
          query.bindValue(":id_b",res);//INSERT INTO equipement VALUES (val code, nom,type)meme ordre que le table
          query.bindValue(":nom",nom);
          query.bindValue(":prenom",prenom);
          query.bindValue(":rib",rib);
          query.bindValue(":date_b",date_b);
          query.bindValue(":numero",numero);
          query.bindValue(":email",email);
          query.bindValue(":type_donation",type_donation);
          query.bindValue(":argent", argent);

       //   qDebug() << "Type de don: " << type_donation;
         // qDebug() << "Argent: " << argent;
    return query.exec();
}

QSqlQueryModel * Benevole::afficher()
{
    QSqlQueryModel  * model=new QSqlQueryModel();
    model->setQuery("select * from Benevole");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_b"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("rib"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_b"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("numero"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("type_donation"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("argent"));


    return model;
}

bool Benevole::supprimer(int id_b)
{


    QSqlQuery query;
    QString res=QString::number(id_b);

    query.prepare("DELETE from Benevole where id_b=:id_b");
    query.bindValue(":id_b",res);

    return query.exec();
}

bool Benevole::modifier()
{
    QSqlQuery query;
    QString res = QString::number(id_b);

    query.prepare("UPDATE Benevole SET nom=:nom, prenom=:prenom, email=:email , rib=:rib ,date_b=:date_b, numero=:numero, type_donation=:type_donation WHERE id_b=:id_b" );

    query.bindValue(":id_b",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":rib",rib);
    query.bindValue(":date_b",date_b);
    query.bindValue(":numero",numero);
    query.bindValue(":email",email);
    query.bindValue(":type_donation",type_donation);
    query.bindValue(":argent", argent);


    return query.exec();
}
QSqlQueryModel * Benevole::rechercherNom(QString nom)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from benevole where regexp_like (nom,'" +nom+"')");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_b"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("rib"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_b"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("numero"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("type_donation"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("argent"));

    return model;
}

QSqlQueryModel * Benevole::affichage_tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from Benevole order by nom");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_b"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("rib"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_b"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("numero"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("type_donation"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("argent"));

    return model;
}

QSqlQueryModel * Benevole::affichage_tri2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from Benevole order by id_b");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_b"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("rib"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_b"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("numero"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("type_donation"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("argent"));

    return model;
}
int Benevole::rechercheid(int id_b)
{
    int result = 0;
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM Benevole WHERE id_b = ?");
        query.addBindValue(id_b);
      //  qDebug() << "Query:" << query.lastQuery();
        if (query.exec() && query.next()) {
            result = query.value(0).toInt();
        } else {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
        return result;

}

