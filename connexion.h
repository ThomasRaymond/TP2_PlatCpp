#ifndef CONNEXION_H
#define CONNEXION_H

#include <QWidget>
#include <QMessageBox>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class Connexion; }
QT_END_NAMESPACE


// Classe permettant de gérer la fenêtre de connexion
class Connexion : public QDialog
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = nullptr);
    ~Connexion();
    void clearfields();

private slots:
    void clickBoutonValider();
    void clickBoutonInscription();

private:
    Ui::Connexion *ui;
};

#endif // CONNEXION_H
