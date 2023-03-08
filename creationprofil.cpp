#include "creationprofil.h"
#include "ui_creationprofil.h"

CreationProfil::CreationProfil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreationProfil)
{
    ui->setupUi(this);
}

CreationProfil::~CreationProfil()
{
    delete ui;
}
