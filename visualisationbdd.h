#ifndef VISUALISATIONBDD_H
#define VISUALISATIONBDD_H

#include <QWidget>

namespace Ui {
class VisualisationBDD;
}

class VisualisationBDD : public QWidget
{
    Q_OBJECT

public:
    explicit VisualisationBDD(QWidget *parent = nullptr);
    ~VisualisationBDD();

private:
    Ui::VisualisationBDD *ui;
};

#endif // VISUALISATIONBDD_H
