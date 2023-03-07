#ifndef CHOIXPROFIL_H
#define CHOIXPROFIL_H

#include <QDialog>

namespace Ui {
class ChoixProfil;
}

class ChoixProfil : public QDialog
{
    Q_OBJECT

public:
    explicit ChoixProfil(QWidget *parent = nullptr);
    ~ChoixProfil();

private:
    Ui::ChoixProfil *ui;
};

#endif // CHOIXPROFIL_H
