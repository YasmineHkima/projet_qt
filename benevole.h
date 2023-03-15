#ifndef BENEVOLE_H
#define BENEVOLE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>

class Benevole
{
    int id_b;

    QString nom,prenom;
    QString rib;
    //QDateTime date_b;
    QString numero;
    QString email;
    QString type_donation;

public:
    //const
    Benevole(){}
Benevole(int,QString,QString,QString,QString,QString,QString);

//getters
QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getRib(){return rib;}
        QString getNumero(){return numero;}
        QString getEmail(){return email;}
            QString getType_donation(){return type_donation;}
            //QDateTime getDate_b(){return date_b;}


    //Setters
    void setNom(QString n){nom=n;}
    void setPrenom(QString p){prenom=p;}
    void setRib(QString r){rib=r;}
    void setNumero(QString num){numero=num;}
    void setEmail(QString e){email=e;}
    void settype_donation(QString t){type_donation=t;}
    void setID(int id_b){this->id_b=id_b;}
   // void setDate_b(QDateTime date_b){this->date_b=date_b;}

    //Fonctionnalités de Base relatives a l'entité Etudiant
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * rechercherNom(QString);
    QSqlQueryModel * affichage_tri();

};

#endif // BENEVOLE_H
