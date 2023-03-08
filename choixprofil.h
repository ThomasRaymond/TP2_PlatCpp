#ifndef CHOIXPROFIL_H
#define CHOIXPROFIL_H

#include <QDialog>
#include "profil.h"
#include <filesystem>


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
private slots:
    void clickValider();
    void clickAnnuler();
    void creerProfil();


private:
    Ui::ChoixProfil *ui;
};

#endif // CHOIXPROFIL_H
