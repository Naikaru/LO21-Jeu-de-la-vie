QT += widgets

SOURCES += \
    src/main.cpp \
    src/fenprincipale.cpp \
    src/fenautomate.cpp \
    src/etat.cpp \
    src/simulateur.cpp \
    src/automatemaker.cpp \
    src/gestionnaireautomatefactory.cpp \
    src/automate1d.cpp \
    src/gameoflife.cpp \
    src/forestfire.cpp \
    src/fenautomate1d.cpp \
    src/fenautomate2d.cpp

HEADERS += \
    headers/fenprincipale.h \
    headers/fenautomate.h \
    headers/automate.h \
    headers/etat.h \
    headers/simulateur.h \
    headers/automatemaker.h \
    headers/abstractautomatefactory.h \
    headers/gestionnaireautomatefactory.h \
    headers/automate1d.h \
    headers/gameoflife.h \
    headers/forestfire.h \
    headers/fenautomate1d.h \
    headers/fenautomate2d.h

DISTFILES +=

RESOURCES += \
    ressources.qrc
