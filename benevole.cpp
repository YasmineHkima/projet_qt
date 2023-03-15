#include "benevole.h"
#include <QDebug>
Benevole::Benevole(int id_b,QString nom ,QString prenom,QString rib,QString numero,QString email,QString type_donation)
{
       this->id_b=id_b;
       this->nom=nom;
       this->prenom=prenom;
       this->rib=rib;
   // this->date_b=date_b;
    this->numero=numero;
    this->email=email;
    this->type_donation=type_donation;
}

bool Benevole::ajouter()
{
    //TODO

    QSqlQuery query;
          QString res=QString::number(id_b);
          query.prepare("INSERT INTO Benevole (id_b, nom, prenom,rib,numero,email,type_donation) ""VALUES (:id_b, :nom, :prenom,:rib,:numero,:email,:type_donation)");
          query.bindValue(":id_b",res);//INSERT INTO equipement VALUES (val code, nom,type)meme ordre que le table
          query.bindValue(":nom",nom);
          query.bindValue(":prenom",prenom);
          query.bindValue(":rib",rib);
          //query.bindValue(":date",date_b);
          query.bindValue(":numero",numero);
          query.bindValue(":email",email);
          query.bindValue(":type_donation",type_donation);


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


    return model;
}

bool Benevole::supprimer(int id_b)
{
    //TODO

    QSqlQuery query;
    QString res=QString::number(id_b);

    query.prepare("delete from Benevole where id_b= :id_b");
    query.bindValue(":id_b",res);

    return query.exec();
}

bool Benevole::modifier()
{
    QSqlQuery query;
    QString res = QString::number(id_b);

    query.prepare("UPDATE Benevole SET nom=:nom, prenom=:prenom, email=:email , rib=:rib , numero=:numero  WHERE id_b=:id_b" );

    query.bindValue(":id_b",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":rib",rib);
    //query.bindValue(":date",date_b);
    query.bindValue(":numero",numero);
    query.bindValue(":email",email);
    query.bindValue(":type_donation",type_donation);
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
    return model;
}
