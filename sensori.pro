QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += charts
QT += core gui widgets charts

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aggiungi_sensore.cpp \
  contenuto.cpp \
    energiabutton.cpp \
    main.cpp \
    mainwindow.cpp \
    Sensore_Astratto.cpp  \
    S_Umidita.cpp  \
    S_Temperatura.cpp  \
    S_Radiazione.cpp  \
    modifica_sensore.cpp \
    sensore_item.cpp \
    sensore_lista_widget.cpp \
    simulatore.cpp  \
    modello.cpp  \
    controller.cpp  \
    parser.cpp  \
    smistatore.cpp \
    utilities.cpp

HEADERS += \
    aggiungi_sensore.h \
    cercaWidget.h \
    contenuto.h \
    energiabutton.h \
    mainwindow.h \
    Sensore_Astratto.h \
    S_Umidita.h \
    S_Temperatura.h \
    S_Radiazione.h \
    modifica_sensore.h \
    sensore_i_const_visitor.h \
    sensore_i_visitor.h \
    sensore_item.h \
    sensori_lista_widget.h \
    simulatore.h \
    modello.h \
    controller.h \
    parser.h \
    smistatore.h \
    utilities.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

FORMS += \
    form.ui
