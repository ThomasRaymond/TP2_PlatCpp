#ifndef CONNEXION_H
#define CONNEXION_H

#include <QWidget>

namespace Ui {
class Connexion;
}

class Connexion : public QWidget
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = nullptr);
    ~Connexion();

private:
    Ui::Connexion *ui;
};

#endif // CONNEXION_H
