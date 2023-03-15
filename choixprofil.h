#ifndef CHOIXPROFIL_H
#define CHOIXPROFIL_H

#include <QDialog>
#include "profil.h"
#include <filesystem>

#define CONTEXT_FIRST_ACCESS 100
#define CONTEXT_CHANGE_PROFILE 200



namespace Ui {
class ChoixProfil;
}

class ChoixProfil : public QDialog
{
    Q_OBJECT

public:
    explicit ChoixProfil(QWidget *parent = nullptr);
    ~ChoixProfil();

    void addListProfiles(std::vector<Profil> list);
    void clearfields();
    void enregistrerProfil(QString nomProfil);

    int getContexte();
    void setContexte(int contexte);
private slots:
    void clickValider();
    void clickAnnuler();
    void creerProfil();


private:
    Ui::ChoixProfil *ui;
    int contexte;
};

#endif // CHOIXPROFIL_H
