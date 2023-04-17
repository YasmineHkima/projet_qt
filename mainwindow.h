#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "benevole.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QAbstractButton>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_BouttonAjouter_clicked();

    void on_QTabBar_tabBarClicked();

    void on_supprimerClient_7_clicked();

    void on_modifierClient_7_clicked();

    void on_RechercherDon_clicked();

    void on_tri_4_clicked();

    void on_pdf_9_clicked();
    int stat_accomodation();
    int stat_aliment();
    int stat_medicament();
    int stat_vetement();
    int stat_argent();
    // void paintEvent(QPaintEvent *) ;


     void on_QTabBar_tabBarClicked(int index);

     //void on_pushButton_clicked();

     void on_showstat_clicked();
     void showLineEdit(int index);
     //void on_comboBox_dono_currentIndexChanged(const QString &x);
     void on_pb_excel_clicked();

     void numberGroup_clicked(QAbstractButton*);
     void actionGroup_clicked(QAbstractButton*);

     void on_actionDel_2_clicked();
     void on_actionCalc_2_clicked();
     void on_comma_2_clicked();
     void on_actionClear_2_clicked();
     void on_actionPercent_2_clicked();
     void on_actionSign_2_clicked();


     void on_tri_5_clicked();

private:
    Ui::MainWindow *ui;
    Benevole benev;
    QComboBox *comboBox_dono;
       QLineEdit *ajouterargent;

       //Digit limit
       const int DIGIT_LIMIT = 16;
       //Flag to check whether the previous button that was clicked was an operator
       bool operatorClicked;
       //Last operator requested
       QChar storedOperator;
       //Flag to check whether a number is stored in memory
       bool hasStoredNumber;
       //Stored number
       double storedNumber;
       //Calculate result based on stored number and displayed number
       void calculate_result();


protected:
    void keyPressEvent(QKeyEvent *e);
};
#endif // MAINWINDOW_H
