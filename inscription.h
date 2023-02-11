#ifndef INSCRIPTION_H
#define INSCRIPTION_H
#include <QWidget>
#include <QMessageBox>
#include "controleurbdd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Inscription; }
QT_END_NAMESPACE

class Inscription : public QWidget
{
    Q_OBJECT

public:
    Inscription(QWidget *parent = nullptr);
    ~Inscription();

private slots:
    void clickBoutonAnnuler();
    void clickBoutonValider();

private:
    Ui::Inscription *ui;

};
#endif // INSCRIPTION_H
