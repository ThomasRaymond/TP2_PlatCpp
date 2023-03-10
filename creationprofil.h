#ifndef CREATIONPROFIL_H
#define CREATIONPROFIL_H

#include <QDialog>
#include <QMessageBox>
#include "choixprofil.h"

namespace Ui {
class CreationProfil;
}

class CreationProfil : public QDialog
{
    Q_OBJECT

public:
    explicit CreationProfil(QWidget *parent = nullptr);
    ~CreationProfil();

private slots:
    void clickAnnuler();
    void clickValider();

private:
    Ui::CreationProfil *ui;
};

#endif // CREATIONPROFIL_H
