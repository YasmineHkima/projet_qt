#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "benevole.h"
#include <QMainWindow>

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

    void on_QTabBar_tabBarClicked(int index);

    void on_supprimerClient_7_clicked();

    void on_modifierClient_7_clicked();

    void on_RechercherDon_clicked();

    void on_tri_4_clicked();

private:
    Ui::MainWindow *ui;
    Benevole benev;
};
#endif // MAINWINDOW_H
