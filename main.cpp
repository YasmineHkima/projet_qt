#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
//#include "calculator.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    connection c;
       bool test=c.createconnect();
        if(test == true)
            {
    w.show();
    QMessageBox::critical(nullptr, QObject::tr("database is open sss"),
                       QObject::tr("connection successful.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

   }
       else
           QMessageBox::critical(nullptr, QObject::tr("database is not open BBB"),
                       QObject::tr("connection failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);





    return a.exec();
}
