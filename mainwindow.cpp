#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "benevole.h"
#include "connection.h"
#include <QMessageBox>
#include <QDebug>

//#include <QSqlQuery>
//#include <QSqlQueryModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    QStringList items = {"Argent", "Aliment", "Vêtements","Accomodation","Medicament"};

    // Add the items to the QComboBox

    ui->setupUi(this);
    ui->comboBox_dono->addItems(items);
    ui->comboBox_modif_donation->addItems(items);
    ui->affichageDon->setModel(benev.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_BouttonAjouter_clicked()
{
    bool verif=true;
    int id_b=ui->Ajouterid_b->text().toInt();
    QString nom=ui->AjouterNom->text();
    QString prenom=ui->AjouterPrenom->text();
    QString rib=ui->AjouterRib->text();
    //QDateTime date_b=ui->dono_date_time->dateTime();
    QString numero=ui->AjouterNumero->text();
    QString email=ui->AjouterEmail->text();
    QString type_donation=ui->comboBox_dono->currentText();
    qDebug() << "rib length" << rib.length();
    QRegExp emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    if(rib.length()!=16)
        {QMessageBox::critical(nullptr, QObject::tr("Erreur! "),
                               QObject::tr("Rib invalide [16] !.\n"
                                           "Click Cancel to try again"), QMessageBox::Cancel);


        verif=false;}

    else if(numero.length()!=8)
        {QMessageBox::critical(nullptr, QObject::tr("Erreur! "),
                               QObject::tr("Numero invalide [8 chiffres] !.\n"
                                           "Click Cancel to try again"), QMessageBox::Cancel);


        verif=false;}


    else if (!emailRegex.exactMatch(email)) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur! "),
                                                          QObject::tr("Email invalide !.\n"
                                                                          "Click Cancel to try again"), QMessageBox::Cancel);


                                       verif=false;}

    if (verif)
    {
    Benevole b(id_b,nom,prenom,rib,numero,email,type_donation);

    bool test=b.ajouter();
    if (test)
    {
        //refresh


        ui->affichageDon->setModel(benev.afficher());



                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("Ajout effectué\n""Click Cancel to exit."),
                                         QMessageBox::Cancel);
            }
            else
                QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                      QObject::tr("Ajouter non effectué\n""Click Cancel to exit."),
                                      QMessageBox::Cancel);
    }

}

void MainWindow::on_QTabBar_tabBarClicked(int index)
{
     ui->affichageDon->setModel(benev.afficher());
}

void MainWindow::on_supprimerClient_7_clicked()
{
    int ref = ui->modif_id_b->text().toInt();
    bool test=benev.supprimer(ref);
    if (test)
    {
        //refresh


        ui->affichageDon->setModel(benev.afficher());



                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("supp effectué\n""Click Cancel to exit."),
                                         QMessageBox::Cancel);
            }
            else
                QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                      QObject::tr("supp non effectué\n""Click Cancel to exit."),
                                      QMessageBox::Cancel);


}

void MainWindow::on_modifierClient_7_clicked()
{
bool verif=true;
    int id_b=ui->modif_id_b->text().toInt();
    QString nom=ui->modif_nom->text();
    QString prenom=ui->modif_prenom->text();
    QString rib=ui->modif_rib->text();
    //QDateTime date_b=ui->dono_date_time->dateTime();
    QString numero=ui->modif_num->text();
    QString email=ui->modif_mail->text();
    QString type_donation=ui->comboBox_modif_donation->currentText();

    Benevole b(id_b,nom,prenom,rib,numero,email,type_donation);

    QRegExp emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");

    if(rib.length()!=16)
        {QMessageBox::critical(nullptr, QObject::tr("Erreur! "),
                               QObject::tr("Rib invalide [16] !.\n"
                                           "Click Cancel to try again"), QMessageBox::Cancel);


        verif=false;}

    else if(numero.length()!=8)
        {QMessageBox::critical(nullptr, QObject::tr("Erreur! "),
                               QObject::tr("Numero invalide [8 chiffres] !.\n"
                                           "Click Cancel to try again"), QMessageBox::Cancel);


        verif=false;}


    else if (!emailRegex.exactMatch(email)) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur! "),
                                                          QObject::tr("Email invalide !.\n"
                                                                          "Click Cancel to try again"), QMessageBox::Cancel);


                                       verif=false;}

    if (verif)
    {


    bool test=b.modifier();
    if (test)
    {
        //refresh


        ui->affichageDon->setModel(benev.afficher());



                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("modification effectué\n""Click Cancel to exit."),
                                         QMessageBox::Cancel);
            }
            else
                QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                      QObject::tr("Modification non effectué\n""Click Cancel to exit."),
                                      QMessageBox::Cancel);
    }
}

void MainWindow::on_RechercherDon_clicked()
{
    QString nom=ui->RechercheDon->text();
     ui->affichageDon->setModel(benev.rechercherNom(nom));
}

void MainWindow::on_tri_4_clicked()
{

    ui->affichageDon->setModel(benev.affichage_tri());
}
