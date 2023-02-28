#ifndef CONNEXION_H
#define CONNEXION_H

#include <QWidget>
#include <QMessageBox>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class Connexion; }
QT_END_NAMESPACE

class Connexion : public QDialog
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
