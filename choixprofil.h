#ifndef CHOIXPROFIL_H
#define CHOIXPROFIL_H

#include <QDialog>
#include "profil.h"


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

private slots:
    void clickValider();
    void clickAnnuler();

private:
    Ui::ChoixProfil *ui;
};

#endif // CHOIXPROFIL_H
