#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "benevole.h"
#include "connection.h"
#include "excelexport.h"
#include <QMessageBox>
#include <QDebug>
#include<QDesktopServices>
#include<QPdfWriter>
#include<QPixmap>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include <QPainter>
#include<QtSvg/QSvgRenderer>
#include <QAbstractSocket>
#include <QRegExpValidator>
//#include <QSqlQuery>
//#include <QSqlQueryModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtWidgets/QApplication>
#include <QTextDocument>
#include <QButtonGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

      QStringList items = {"Argent", "Aliment", "Vetement","Accomodation","Medicament"};

     comboBox_dono = new QComboBox(this);
     comboBox_dono->addItems(items);

      ajouterargent = new QLineEdit(this);
      ajouterargent->setPlaceholderText("Enter la somme d'argent");
      ajouterargent->hide();

      connect(comboBox_dono, QOverload<int>::of(&QComboBox::currentIndexChanged),
              this, &MainWindow::showLineEdit);

   ui->verticalLayout->addWidget(comboBox_dono);
   ui->verticalLayout->addWidget(ajouterargent);




   //Set up empty display panel
   ui->displayPanel->clear();

   //Set operator and store number flags to false
   operatorClicked = false;
   hasStoredNumber = false;

   //Set number button group listener
   ui->numberGroup->connect(ui->numberGroup,SIGNAL(buttonClicked(QAbstractButton*)),
                            this, SLOT(numberGroup_clicked(QAbstractButton*)));
   //Set operator button group listener
   ui->actionGroup->connect(ui->actionGroup,SIGNAL(buttonClicked(QAbstractButton*)),
                            this, SLOT(actionGroup_clicked(QAbstractButton*)));
   QMetaObject::connectSlotsByName(this);



}

MainWindow::~MainWindow()
{
    delete ui;
    delete comboBox_dono;
       delete ajouterargent;
}


void MainWindow::on_BouttonAjouter_clicked()
{

    bool verif=true;
    int id_b=ui->Ajouterid_b->text().toInt();
    QString nom=ui->AjouterNom->text();
    QString prenom=ui->AjouterPrenom->text();
    QString rib=ui->AjouterRib->text();
    QString date_b=ui->datebar->text();
    QString numero=ui->AjouterNumero->text();
    QString email=ui->AjouterEmail->text();
    QString type_donation=ui->comboBox_dono->currentText();
    QString argent=ui->ajouterargent->text();

    //qDebug() << "rib length" << rib.length();
    QRegExp emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    if(rib.length()!=10)
        {QMessageBox::critical(nullptr, QObject::tr("Erreur! "),
                               QObject::tr("Rib invalide [10] !.\n"
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
    Benevole b(id_b,nom,prenom,rib,date_b,numero,email,type_donation,argent);

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

void MainWindow::on_QTabBar_tabBarClicked()
{
     ui->affichageDon->setModel(benev.afficher());
}




void MainWindow::on_supprimerClient_7_clicked()
{
    bool verif=true;
    int id_b=ui->modif_id_b->text().toInt();


  //  benev.setID(ui->modif_id_b->text().toInt());
       if(benev.rechercheid(id_b)==0)
       {
           qDebug() << id_b ;

        verif=false;
        QMessageBox::critical(nullptr, QObject::tr("Erreur! "),
                                       QObject::tr("id invalide !.\n"
                                                   "Click Cancel to try again"), QMessageBox::Cancel);

       }

       if (verif)
       {

       bool test=benev.supprimer(id_b);
       if (test)
       {
           qDebug() << "Query:" ;

           //refresh
           ui->affichageDon->setModel(benev.afficher());

                   QMessageBox::information(nullptr,QObject::tr("ok"),
                                            QObject::tr("SUPPRESSION effectué\n""Click Cancel to exit."),
                                            QMessageBox::Cancel);
               }
               else
                   QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                         QObject::tr("SUPPRESSION non effectué\n""Click Cancel to exit."),
                                         QMessageBox::Cancel);
       }
}

void MainWindow::on_modifierClient_7_clicked()
{
bool verif=true;
    int id_b=ui->modif_id_b->text().toInt();
    QString nom=ui->modif_nom->text();
    QString prenom=ui->modif_prenom->text();
    QString rib=ui->modif_rib->text();
    QString date_b=ui->datebar->text();
    QString numero=ui->modif_num->text();
    QString email=ui->modif_mail->text();
    QString type_donation=ui->comboBox_modif_donation->currentText();
    QString argent=ui->ajouterargent->text();

    Benevole b(id_b,nom,prenom,rib,date_b,numero,email,type_donation,argent);

    b.setID(ui->modif_id_b->text().toInt());
       if(b.rechercheid(b.getID_b())==0)
       {
        verif=false;
        QMessageBox::critical(nullptr, QObject::tr("Erreur! "),
                                       QObject::tr("id invalide !.\n"
                                                   "Click Cancel to try again"), QMessageBox::Cancel);
       }
    QRegExp emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");

    if(rib.length()!=10)
        {QMessageBox::critical(nullptr, QObject::tr("Erreur! "),
                               QObject::tr("Rib invalide [10] !.\n"
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
//
void MainWindow::on_tri_5_clicked()
{
    ui->affichageDon->setModel(benev.affichage_tri2());

}



void MainWindow::on_pdf_9_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         "/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
             qDebug()<<dir;
             QPdfWriter pdf(dir+"/PdfList.pdf");
                                    QPainter painter(&pdf);
                                   int i = 4000;

                                   painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/Admin/Desktop/msi.png"));
                                       //painter.drawText(900,650,"Tiny hues");

                                        //painter.drawPixmap(QRect(7600,100,2100,2700),QPixmap("C:/Users/Admin/Desktop/msi.png"));

                                        painter.setPen(Qt::red);
                                        painter.setFont(QFont("Time New Roman", 20));
                                        painter.drawText(3000,1450,"Liste Des Benevoles");
                                        painter.setPen(Qt::black);
                                        painter.setFont(QFont("Time New Roman", 9));
                                        painter.drawRect(100,100,9000,2500);
                                        painter.drawRect(100,3000,9000,500);
                                        painter.setFont(QFont("Time New Roman",6));
                                        painter.drawText(300,3300,"id_b");
                                        painter.drawText(1000,3300,"Nom");
                                        painter.drawText(2000,3300,"Prenom");
                                        painter.drawText(3500,3300,"RIB");
                                        painter.drawText(4600,3300,"Date");
                                        painter.drawText(5900,3300,"Numero");
                                        painter.drawText(7100,3300,"Email");
                                        painter.drawText(8500,3300,"Type");
                                        painter.drawText(9500,3300,"Type");

                                        painter.drawRect(100,3000,11000,10700);


                                        QTextDocument previewDoc;
                                        QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");


                                        QTextCursor cursor(&previewDoc);



                                        QSqlQuery query;
                                        query.prepare("select * from Benevole");
                                        query.exec();
                                        while (query.next())
                                        {
                                            painter.drawText(300,i,query.value(0).toString());
                                            painter.drawText(1000,i,query.value(1).toString());
                                            painter.drawText(2000,i,query.value(2).toString());
                                            painter.drawText(3500,i,query.value(3).toString());
                                            painter.drawText(4600,i,query.value(4).toString());
                                            painter.drawText(5900,i,query.value(5).toString());
                                            painter.drawText(7100,i,query.value(6).toString());
                                            painter.drawText(8500,i,query.value(7).toString());
                                            painter.drawText(9500,i,query.value(8).toString());




                                           i = i +500;
                                        }
                                        int reponse = QMessageBox::question(this, "Générer PDF", " PDF Enregistré ! Voulez Vous Affichez Le PDF ?",
                                                                            QMessageBox::Yes|QMessageBox::No);
                                            if (reponse == QMessageBox::Yes)
                                            {
                                                QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                                painter.end();
                                            }
                                            else
                                            {
                                                 painter.end();
   }
}


int MainWindow::stat_medicament()
{
    int result = 0;
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM Benevole WHERE type_donation = 'Medicament' ");
      //  qDebug() << "Query:" << query.lastQuery();
        if (query.exec() && query.next()) {
            result = query.value(0).toInt();
        } else {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
        return result;
}
int MainWindow::stat_accomodation()
{
    int result = 0;
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM Benevole WHERE type_donation = 'Accomodation' ");
      //  qDebug() << "Query:" << query.lastQuery();
        if (query.exec() && query.next()) {
            result = query.value(0).toInt();
        } else {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
        return result;
}
int MainWindow::stat_aliment()
{
    int result = 0;
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM Benevole WHERE type_donation = 'Aliment' ");
      //  qDebug() << "Query:" << query.lastQuery();
        if (query.exec() && query.next()) {
            result = query.value(0).toInt();
        } else {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
        return result;
}
int MainWindow::stat_vetement()
{
    int result = 0;
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM Benevole WHERE type_donation = 'Vetement' ");
      //  qDebug() << "Query:" << query.lastQuery();
        if (query.exec() && query.next()) {
            result = query.value(0).toInt();
        } else {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
        return result;
}


int MainWindow::stat_argent()
{
    int result = 0;
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM Benevole WHERE type_donation = 'Argent' ");
      //  qDebug() << "Query:" << query.lastQuery();
        if (query.exec() && query.next()) {
            result = query.value(0).toInt();
        } else {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
        return result;
}

bool chartShown = false;



void MainWindow::on_QTabBar_tabBarClicked(int index)
{
    int b=stat_argent(); //count occurences param1
    int c=stat_medicament();//count occurences param2
    int d=stat_accomodation(); //count occurences param1
    int e=stat_aliment();//count occurences param2
    int f=stat_vetement(); //count occurences param1


    float s2= b*100 ;
    float s3=c*100;
    float s4= d*100 ;
    float s5=e*100;
    float s6= f*100 ;

    float nb = b+c+d+e+f ; //number of all occurences

    float q2;
        q2 = s2/nb ; //param1 %
        float y  ;
        y = (q2*360)/100 ; //param1 on pie

        float q3;
        q3=s3/nb; //param2 %
        float m; //param2 on pie
        m= (q3*360)/100;

        float q4;
        q4=s4/nb; //param2 %
        float m4; //param2 on pie
        m4= (q4*360)/100;

        float q5;
        q5=s5/nb; //param2 %
        float m5; //param2 on pie
        m5= (q5*360)/100;

        float q6;
        q6=s6/nb; //param2 %
        float m6; //param2 on pie
        m6= (q6*360)/100;



    ui->argent->setText("argent");
    ui->medicament->setText("medication");
    ui->accomodation->setText("accomodation");
    ui->vetement->setText("vetement");
    ui->aliment->setText("aliment");

    ui->prargent->setNum(q2);
    ui->prmedicament->setNum(q3);
    ui->praccomodation->setNum(q4);
    ui->prvetement->setNum(q5);
    ui->praliment->setNum(q6);




}


void MainWindow::on_showstat_clicked()
{
    int b=stat_argent(); //count occurences param1
    int c=stat_medicament();//count occurences param2
    int d=stat_accomodation(); //count occurences param1
    int e=stat_aliment();//count occurences param2
    int f=stat_vetement(); //count occurences param1

    // Create and show the chart only if it has not already been shown
   // if (!chartShown) {


    // Create a pie series
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
        series->append("Argent", b);
        series->append("Medicament", c);
        series->append("Accomodation", d);
        series->append("Aliment", e);
        series->append("Vetement", f);

        // Create a chart and add the series
         QtCharts::QChart *chart = new QtCharts::QChart();
        chart->addSeries(series);
        chart->setTitle("Statistics");

        // Create a chart view and set the chart
        QtCharts:: QChartView *chartView = new QtCharts::QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

            // Show the chart view
            chartView->show();
            chartShown = true;
         //   }
}

void MainWindow::showLineEdit(int index)
{
    qDebug() << "showLineEdit() called with index: " << index;
       if (index == 0) {
           ajouterargent->show();
       } else {
           ajouterargent->hide();
       }
}

//export excel
void MainWindow::on_pb_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "Tableau Des Dons", ui->affichageDon);

    //colums to export
    obj.addField(0, "id_b", "char(30)");
    obj.addField(1, "nom", "char(30)");
    obj.addField(2, "prenom", "char(30)");
    obj.addField(3, "date_b", "char(30)");
    obj.addField(4, "RIB", "char(30)");
    obj.addField(5, "numero", "char(30)");
    obj.addField(6, "email", "char(30)");
    obj.addField(7, "type_donation", "char(30)");
    obj.addField(8, "argent", "char(30)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}


void MainWindow::numberGroup_clicked(QAbstractButton* button)
{
    //Get string from display
    QString displayLabel = ui->displayPanel->text();

    /* Check if the previous button that was clicked was an operator button.
     * If so, clear the display and set the flag to false. Then proceed to
     * add the digit requested. */
    if (operatorClicked) {
        displayLabel.clear();
        operatorClicked = false;
    }

    //Append the digit only if we are not exceeding the digit limit
    if (displayLabel.length() >= DIGIT_LIMIT) {
        return;
    }

    //Append requested digit
    displayLabel.append(button->text());

    //Set number back to display
    ui->displayPanel->setText(displayLabel);
}

// Called whenever an action button is clicked
void MainWindow::actionGroup_clicked(QAbstractButton* button)
{
    /* If the previous button that was clicked was not an operator, then we just need to save the operator
     * that was requested and exit.
     * If it was though, we need to see whether we just need to save the number that is
     * displayed or if there is already a number stored in memory, perform the calculation and
     * store the result.
     * Example for this case: 5 + 7 + -> We need to save 12 in memory and then save operator. */

    if (operatorClicked) {
        storedOperator = button->text().at(0);
    }
    else {
        if (hasStoredNumber) {
            calculate_result();
        }
        else {
            //Set the flag to indicate that we now have a number stored in memory
            hasStoredNumber = true;
            //Get string from display
            QString displayLabel = ui->displayPanel->text();
            //Convert string to double and save
            storedNumber = displayLabel.toDouble();
        }
        //Set the flag that the last button that was clicked was an operator
        operatorClicked = true;
        //Store operator in memory
        storedOperator = button->text().at(0);
    }
}

void MainWindow::on_actionDel_2_clicked()
{
    //Get string from display
    QString displayLabel = ui->displayPanel->text();

    //Check if label is empty
    if (displayLabel.length() == 0) {
        return;
    }

    //Delete last digit from string
    displayLabel.QString::chop(1);
    //Set number back to display
    ui->displayPanel->setText(displayLabel);
}

void MainWindow::on_actionCalc_2_clicked()
{
    //Get string from display
    QString displayLabel = ui->displayPanel->text();
    /* A number must be saved in memory to be able calculate a result.
     * In addition, a number with at least one digit should be present in the display and
     * The last button that was clicked should not be an operator */

    if (!hasStoredNumber || displayLabel.length() < 1 || operatorClicked) {
        return;
    }

    //Calculate result and set in on display
    calculate_result();

    //Set stored number flag to false (we have it on screen now)
    hasStoredNumber = false;

}

void MainWindow::on_comma_2_clicked()
{
    //Get string from display
    QString displayLabel = ui->displayPanel->text();

    /* Append the digit only if we are not exceeding the digit limit.
     * More specifically in this case, we need 2 digits to be available.
     * One for the comma and at least another one for a remaining digit.
     * Also check if whether there is another comma already present. */
    if (displayLabel.length() >= (DIGIT_LIMIT - 1) ||
        displayLabel.contains('.', Qt::CaseSensitive)) {
        return;
    }

    //If label is empty, add zero and then append comma
    if (displayLabel.length() == 0) {
        displayLabel = "0";
    }

    //Append comma
    displayLabel.append('.');
    //Set number back to display
    ui->displayPanel->setText(displayLabel);
}

void MainWindow::on_actionClear_2_clicked()
{
    //Clear display label (for now)
    ui->displayPanel->clear();
    //Set operator and store number flags to false
    operatorClicked = false;
    hasStoredNumber = false;
}

void MainWindow::on_actionPercent_2_clicked()
{
    //Get string from display
    QString displayLabel = ui->displayPanel->text();
    //Convert to double
    double percentage = displayLabel.toDouble();
    //Just multiply with 0.01 to make it a percentage
    percentage *= 0.01;
    //Since there might be an overflow, its best to convert the number carefully
    displayLabel = QString::number(percentage,'g', DIGIT_LIMIT);
    //Set number back to display
    ui->displayPanel->setText(displayLabel);
}

void MainWindow::on_actionSign_2_clicked()
{
    //Get string from display
    QString displayLabel = ui->displayPanel->text();
    //Convert to double
    double percentage = displayLabel.toDouble();
    //Just multiply with -1 to change its sign
    percentage *= -1;
    //Convert the number carefully
    displayLabel = QString::number(percentage,'g', DIGIT_LIMIT);
    //Set number back to display
    ui->displayPanel->setText(displayLabel);
}

//==================================================================================
//Helper functions
//==================================================================================
void MainWindow::calculate_result() {
    //Get string from display
    QString displayLabel = ui->displayPanel->text();

    //If the displayed number ends with a comma, drop the comma.
     if (displayLabel.endsWith('.',Qt::CaseSensitive)) {
         displayLabel.QString::chop(1);
     }

     //Decide what to do according to operation
     if (storedOperator == '+') {
         storedNumber += displayLabel.toDouble();
     }
     else if (storedOperator == '-') {
         storedNumber -= displayLabel.toDouble();
     }
     else if (storedOperator == 'x') {
         storedNumber *= displayLabel.toDouble();
     }
     else if (storedOperator == '/') {
         storedNumber /= displayLabel.toDouble();
     }

     //Since there might be an overflow, its best to convert the number carefully
     displayLabel = QString::number(storedNumber,'g', DIGIT_LIMIT);

     //Set number back to display
     ui->displayPanel->setText(displayLabel);
}

//Keyboard buttons should call the corresponding functions
void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
        //Numbers
        case Qt::Key_1:
            numberGroup_clicked(ui->num1_2);
            break;
        case Qt::Key_2:
            numberGroup_clicked(ui->num2_2);
            break;
        case Qt::Key_3:
            numberGroup_clicked(ui->num3_2);
            break;
        case Qt::Key_4:
            numberGroup_clicked(ui->num4_2);
            break;
        case Qt::Key_5:
            numberGroup_clicked(ui->num5_2);
            break;
        case Qt::Key_6:
            numberGroup_clicked(ui->num6_2);
            break;
        case Qt::Key_7:
            numberGroup_clicked(ui->num7_2);
            break;
        case Qt::Key_8:
            numberGroup_clicked(ui->num8_2);
            break;
        case Qt::Key_9:
            numberGroup_clicked(ui->num9_2);
            break;
        case Qt::Key_0:
            numberGroup_clicked(ui->num0_2);
            break;
        //Operators
        case Qt::Key_Plus:
            actionGroup_clicked(ui->actionPlus_2);
            break;
        case Qt::Key_Minus:
            actionGroup_clicked(ui->actionMinus_2);
            break;
        case Qt::Key_Asterisk:
            actionGroup_clicked(ui->actionMul_2);
            break;
        case Qt::Key_Slash:
            actionGroup_clicked(ui->actionDiv_2);
            break;
        //Comma
        case Qt::Key_Period:
            on_comma_2_clicked();
            break;
        //Return (enter)
        case Qt::Key_Enter:
        case Qt::Key_Return:
            on_actionCalc_2_clicked();
            break;
        //Backspace and delete
        case Qt::Key_Backspace:
            on_actionDel_2_clicked();
            break;
        case Qt::Key_Delete:
            on_actionClear_2_clicked();
            break;
        //Percentage
        case Qt::Key_Percent:
            on_actionPercent_2_clicked();
            break;
    }
}

