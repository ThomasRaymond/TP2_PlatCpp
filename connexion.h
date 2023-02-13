#ifndef CONNEXION_H
#define CONNEXION_H

#include <QWidget>
#include <QMessageBox>

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
    void clickBoutonAnnuler();
    //void clickBoutonValider();

private:
    Ui::Connexion *ui;
};

#endif // CONNEXION_H
