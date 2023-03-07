#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "utilisateur.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Utilisateur* getUtilisateur();
    void setUtilisateur(Utilisateur* utilisateur);

    void init();
    void lancerApplication();
    void lancerConnexion();
    void lancerInscription();
    void deconnexion();

    void fermerFenetre(QDialog* fenetre);

private:
    Ui::MainWindow *ui;
    Utilisateur* utilisateur;
};
#endif // MAINWINDOW_H
