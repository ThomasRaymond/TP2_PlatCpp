#ifndef CONNEXION_H
#define CONNEXION_H

#include <QWidget>
#include <QMessageBox>
#include <QRegularExpression>
#include "controleurbdd.h"
#include "inscription.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Connexion; }
QT_END_NAMESPACE

class Connexion : public QWidget
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = nullptr);
    ~Connexion();

private slots:
    void clickBoutonValider();
    void clickBoutonInscription();

private:
    Ui::Connexion *ui;
};

#endif // CONNEXION_H
