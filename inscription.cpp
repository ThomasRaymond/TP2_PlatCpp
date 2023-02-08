#include "inscription.h"
#include "ui_inscription.h"

Inscription::Inscription(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Inscription)
{
    ui->setupUi(this);
}

Inscription::~Inscription()
{
    delete ui;
}

