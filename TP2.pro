QT += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    choixprofil.cpp \
    connexion.cpp \
    controleurbdd.cpp \
    controleurxml.cpp \
    inscription.cpp \
    main.cpp \
    mainwindow.cpp \
    profil.cpp \
    utilisateur.cpp \
    visualisationbdd.cpp

HEADERS += \
    choixprofil.h \
    connexion.h \
    controleurbdd.h \
    controleurxml.h \
    droitsutilisateurs.h \
    inscription.h \
    mainwindow.h \
    profil.h \
    utilisateur.h \
    visualisationbdd.h

FORMS += \
    choixprofil.ui \
    connexion.ui \
    inscription.ui \
    mainwindow.ui \
    visualisationbdd.ui

TRANSLATIONS += \
    TP2_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT += xml

DISTFILES += \
    users
