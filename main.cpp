#include "mainwindow.h"
#include "controller.h"
#include "modello.h"
#include <QApplication>

#include "S_Temperatura.h"
#include "S_Umidita.h"
#include "S_Radiazione.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Controller c;
    Modello m;

    S_Temperatura sensore1= S_Temperatura(1,"Temperatura1","Questo sensore è posizionato nel'ala sud vicino al serbatoio",4,1,Energia::eolico,true,Misura::Celsius,2,200,0);
    S_Temperatura sensore2= S_Temperatura(2,"Temperatura2","Questo sensore è dotato di una batteria",5,1,Energia::solare,true,Misura::Celsius,2,100,50);
    S_Temperatura sensore3= S_Temperatura(3,"Temperatura3","Questo sensore è il più grande dell'impianto",6,1,Energia::eolico,true,Misura::Celsius,2,400,200);
    S_Temperatura sensore4= S_Temperatura(4,"Temperatura4","Questo sensore è dotato di illuminazione",4,1,Energia::solare,true,Misura::Celsius,2,200,-150);
    S_Temperatura sensore5= S_Temperatura(5,"Temperatura5","Sensore per ala nord",5,1,Energia::eolico,true,Misura::Celsius,2.2,500,400);
    S_Temperatura sensore6= S_Temperatura(6,"Temperatura6","Sensore per temperatura dei liquidi ",6,1,Energia::solare,true,Misura::Celsius,5,250,200);
    S_Temperatura sensore7= S_Temperatura(7,"Temperatura7","Questo sensore non è dotato di una batteria",4,1,Energia::eolico,true,Misura::Celsius,2,100,-8);
    S_Temperatura sensore8= S_Temperatura(8,"Temperatura8","Temperatura8 è fondamentale per il controllo",5,1,Energia::solare,true,Misura::Celsius,3,8484,-30);
    S_Temperatura sensore9= S_Temperatura(9,"Temperatura9","Sensore per ala nord",6,1,Energia::solare,true,Misura::Celsius,5,6988,-10);
    S_Temperatura sensore10= S_Temperatura(10,"Temperatura10","Questo sensore è posizionato vicino alle pale",4,1,Energia::eolico,true,Misura::Fahrenheit,2,800,8);
    S_Temperatura sensore11= S_Temperatura(11,"Temperatura11","Questo sensore viene spostato spesso",5,1,Energia::solare,true,Misura::Celsius,3,1000,9);
    S_Temperatura sensore12= S_Temperatura(12,"Temperatura12","Questo sensore si trova fuori dall'impianto",6,1,Energia::solare,true,Misura::Fahrenheit,5,989,0);

    S_Umidita s13=S_Umidita(13,"Umidita1","Questo sensore è posizionato nel'ala sud vicino al serbatoio",7,12,Energia::eolico,true,100,20);
    S_Umidita s14=S_Umidita(14,"Umidita2","Questo sensore è dotato di una batteri",8,12,Energia::eolico,true,90,1);
    S_Umidita s15=S_Umidita(15,"Umidita3","Questo sensore si trova fuori dall'impianto",9,12,Energia::eolico,true,80,3);
    S_Umidita s16=S_Umidita(16,"Umidita4","Sensore per ala nord",7,12,Energia::solare,true,50,5);
    S_Umidita s17=S_Umidita(17,"Umidita5","Questo sensore non è dotato di una batteria",8,12,Energia::solare,true,70,20);
    S_Umidita s18=S_Umidita(18,"Umidita6","Sensore per ala sud",9,12,Energia::eolico,true,99,15);
    S_Umidita s19=S_Umidita(19,"Umidita7","Questo sensore viene spostato spesso",7,12,Energia::solare,true,89,2);
    S_Umidita s21=S_Umidita(131,"Umidita8","Questo sensore è costituito da 3 sensori distinti uniti",8,12,Energia::eolico,true,80,0.4);
    S_Umidita s22=S_Umidita(132,"Umidita9","Questo sensore è il più piccolo dell'impianto",9,12,Energia::solare,true,98,0.6);
    S_Umidita s23=S_Umidita(133,"Umidita10","Questo sensore si trova fuori dall'impianto",7,12,Energia::eolico,true,87,20);
    S_Umidita s24=S_Umidita(134,"Umidita11","Questo sensore è stato comprato usato",8,12,Energia::solare,true,95,0.3);
    S_Umidita s25=S_Umidita(135,"Umidita12","Questo sensore è di colore rosso",9,12,Energia::eolico,false,30,99);

    S_Radiazione s26=S_Radiazione(91,"Radiazione1","desc",1,24.30,Energia::eolico,true,20,80,260);
    S_Radiazione s27=S_Radiazione(92,"Radiazione2","Questo sensore è stato comprato usato",2,24.30,Energia::eolico,true,23,100,2660);
    S_Radiazione s28=S_Radiazione(93,"Radiazione3","Sensore per ala est",3,24.30,Energia::eolico,true,23,200,2660);
    S_Radiazione s29=S_Radiazione(94,"Radiazione4","Questo sensore non è dotato di una batteria",1,24.30,Energia::eolico,true,23,400,2660);
    S_Radiazione s30=S_Radiazione(95,"Radiazione5","Questo sensore si trova fuori dall'impianto",2,24.30,Energia::eolico,true,23,485,240);
    S_Radiazione s31=S_Radiazione(96,"Radiazione6","Questo sensore viene spostato spesso",3,24.30,Energia::eolico,true,23,451,2440);
    S_Radiazione s32=S_Radiazione(97,"Radiazione7","Questo sensore si trova fuori dall'impianto",1,24.30,Energia::eolico,true,23,145,2440);
    S_Radiazione s33=S_Radiazione(98,"Radiazione8","Questo sensore è stato comprato usato",2,24.30,Energia::eolico,true,23,45,2440);
    S_Radiazione s34=S_Radiazione(99,"Radiazione9","Sensore per ala nord",3,24.30,Energia::eolico,true,23,95,2660);
    S_Radiazione s35=S_Radiazione(999,"Radiazione10","Sensore per ala nord",1,24.30,Energia::eolico,true,23,45,2660);

    try{

    m.aggiungiSensore(sensore1);
    m.aggiungiSensore(sensore2);
    m.aggiungiSensore(sensore3);
    m.aggiungiSensore(sensore4);
    m.aggiungiSensore(sensore5);
    m.aggiungiSensore(sensore6);
    m.aggiungiSensore(sensore7);
    m.aggiungiSensore(sensore8);
    m.aggiungiSensore(sensore9);
    m.aggiungiSensore(sensore10);
    m.aggiungiSensore(sensore11);
    m.aggiungiSensore(sensore12);
    m.aggiungiSensore(s14);

    m.aggiungiSensore(s15);
    m.aggiungiSensore(s16);
    m.aggiungiSensore(s17);
    m.aggiungiSensore(s18);
    m.aggiungiSensore(s19);
    m.aggiungiSensore(s21);
    m.aggiungiSensore(s22);
    m.aggiungiSensore(s23);
    m.aggiungiSensore(s24);
    m.aggiungiSensore(s25);

    m.aggiungiSensore(s26);
    m.aggiungiSensore(s27);
    m.aggiungiSensore(s28);
    m.aggiungiSensore(s29);
    m.aggiungiSensore(s30);
    m.aggiungiSensore(s31);
    m.aggiungiSensore(s32);
    m.aggiungiSensore(s33);
    m.aggiungiSensore(s34);
    m.aggiungiSensore(s35);
    }
    catch (std::invalid_argument e){
    }

    c.setModel(&m);
    c.setView(&w);
    w.setController(&c);


    w.show();
    return a.exec();
}
