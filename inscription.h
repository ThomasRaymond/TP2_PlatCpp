#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QWidget>
#include <QMessageBox>
#include <QRegularExpression>

#include "ui_inscription.h"
#include "utilisateur.h"
#include "controleurxml.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Inscription; }
QT_END_NAMESPACE

// Classe permettant de gérer la fenêtre d'inscription
class Inscription : public QDialog
{
    Q_OBJECT

public:
    Inscription(QWidget *parent = nullptr);
    ~Inscription();
    void clearfields();

private slots:
    void clickBoutonValider();
    void clickBoutonConnexion();

private:
    Ui::Inscription *ui;

};
#endif // INSCRIPTION_H
