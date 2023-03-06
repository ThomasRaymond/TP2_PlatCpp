#include "visualisationbdd.h"
#include "ui_visualisationbdd.h"

VisualisationBDD::VisualisationBDD(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualisationBDD)
{
    ui->setupUi(this);
}

VisualisationBDD::~VisualisationBDD()
{
    delete ui;
}
