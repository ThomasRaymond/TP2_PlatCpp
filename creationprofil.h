#ifndef CREATIONPROFIL_H
#define CREATIONPROFIL_H

#include <QDialog>

namespace Ui {
class CreationProfil;
}

class CreationProfil : public QDialog
{
    Q_OBJECT

public:
    explicit CreationProfil(QWidget *parent = nullptr);
    ~CreationProfil();

private:
    Ui::CreationProfil *ui;
};

#endif // CREATIONPROFIL_H
