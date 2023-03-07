#include "choixprofil.h"
#include "ui_choixprofil.h"

ChoixProfil::ChoixProfil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoixProfil)
{
    ui->setupUi(this);
}

ChoixProfil::~ChoixProfil()
{
    delete ui;
}
