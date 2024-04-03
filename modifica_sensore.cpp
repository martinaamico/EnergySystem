#include "modifica_sensore.h"
#include <QPushButton>
#include <QDialog>
#include "S_Radiazione.h"
#include "S_Umidita.h"
#include "S_Temperatura.h"
#include <QMessageBox>
#include <QCheckBox>
#include "utilities.h"

ModificaSensore::ModificaSensore(Sensore_Astratto& s,Controller *c, QWidget *parent)
    : QDialog(parent),controller(c) {

    mainlayout = new QVBoxLayout;
    layoutcomune = new QVBoxLayout;
    layoutspecifico = new QVBoxLayout;
    title = new QLabel("Modifica: " + QString::fromStdString(s.getNome()), this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: rgb(67, 108, 108); font-size: 16pt;");  // Imposta il colore del testo e la dimensione del carattere
    QHBoxLayout* campiDatiLayout = new QHBoxLayout;
    QVBoxLayout* campiDati[2] = {new QVBoxLayout, new QVBoxLayout};


    QHBoxLayout* nomeLayout = new QHBoxLayout;
    QLabel* nomeLabel = new QLabel("Nome",this);
    nome = new QLineEdit(QString::fromStdString(s.getNome()));
    nome->setMaxLength(15);
    nomeLayout->addWidget(nomeLabel);
    nomeLayout->addWidget(nome);

   QHBoxLayout* costoLayout = new QHBoxLayout;
    QLabel* costoLabel = new QLabel("Costo", this);
    double costoValue = s.getCosto(); // Assicurati che getCosto() restituisca un valore double
    QString costoString = QString::fromStdString(std::to_string(costoValue));
    costo = new QLineEdit(costoString);
    costo->setReadOnly(true);
    costo->setMaxLength(7);
    costoLayout->addWidget(costoLabel);
    costoLayout->addWidget(costo);


    QHBoxLayout* impiantoLayout = new QHBoxLayout;
    QLabel* impiantoLabel = new QLabel("Impianto", this);
    impiantoBox = new QComboBox(this);
    impiantoBox->addItems({"eolico", "solare"});

    impiantoLayout->addWidget(impiantoLabel);
    impiantoLayout->addWidget(impiantoBox);


    QHBoxLayout* descrizioneLayout = new QHBoxLayout;
    QLabel* descLabel = new QLabel("Descrizione", this);
    descrizione = new QTextEdit(QString::fromStdString(s.getDescrizionecon_()));
    connect(descrizione, &QTextEdit::textChanged, [=](){ if (descrizione->toPlainText().length() > 200) descrizione->setPlainText(descrizione->toPlainText().left(200)); });
    descrizione->setFixedHeight(100);  // Altezza fissa per l'area di testo
    descrizioneLayout->addWidget(descLabel);
    descrizioneLayout->addWidget(descrizione);



    QHBoxLayout* codiceLayout = new QHBoxLayout;
    QLabel* codLabel = new QLabel("Codice", this);
    int codiceValue = s.getCodice();
    codice = new QLineEdit(QString::number(codiceValue));
    codice->setReadOnly(true);  // Imposta il QLineEdit come non modificabile
    codiceLayout->addWidget(codLabel);
    codiceLayout->addWidget(codice);
    cod=s.getCodice();


    QHBoxLayout* funzionanteLayout = new QHBoxLayout;
    QLabel* funzionanteLabel = new QLabel("Funzionante", this);
    funzionanteCheckBox = new QCheckBox(this);
    funzionanteCheckBox->setChecked(s.getFunzionante());
    funzionanteLayout->addWidget(funzionanteLabel);
    funzionanteLayout->addWidget(funzionanteCheckBox);


    //controllo che sia un intero

    //campiDati[0]->addLayout(tipoLayout);
    campiDati[0]->addLayout(nomeLayout);
    campiDati[0]->addLayout(costoLayout);
    campiDati[0]->addLayout(codiceLayout);
    campiDati[0]->addLayout(funzionanteLayout);

    campiDati[1]->addLayout(impiantoLayout);
    campiDati[1]->addLayout(descrizioneLayout);

    campiDatiLayout->addLayout(campiDati[0]);
    campiDatiLayout->addLayout(campiDati[1]);


    img=s.getPercorso_Immagine();

    layoutcomune->addLayout(campiDatiLayout);
    QPushButton* modifica = new QPushButton("Modifica",this);
    modifica->setStyleSheet("background-color: rgb(67, 108, 108); color: white;");
    connect(modifica, SIGNAL(clicked()), this, SLOT(modificaSensore()));

    mainlayout->addWidget(title);

    if(dynamic_cast<S_Temperatura*>(&s)){

        S_Temperatura p=static_cast<S_Temperatura&>(s);
        scalaLayout = new QHBoxLayout;
        QLabel* scalaLabel = new QLabel("Scala misurazione", this);
        scalaBox = new QComboBox(this);
        scalaBox->addItems({"Kelvin", "Fahrenheit", "Celsius"});
        scalaLayout->addWidget(scalaLabel);
        scalaLayout->addWidget(scalaBox);

        precisioneLayout = new QHBoxLayout;
        QLabel* precLabel = new QLabel("Precisione", this);
        double precValue = p.getPrecisione();
        QString precString = QString::fromStdString(std::to_string(precValue));
        precisione = new QLineEdit(precString);
        precisione->setMaxLength(7);
        precisione->setReadOnly(true);
        precisioneLayout->addWidget(precLabel);
        precisioneLayout->addWidget(precisione);
        precisione->setValidator(new QDoubleValidator(0, 100, 2, this));

        massimoLayout = new QHBoxLayout;
        QLabel* massimoLabel = new QLabel("Livello massimo", this);
        double maxValue = p.getLivello_Massimo();
        QString maxString = QString::fromStdString(std::to_string(maxValue));
        livello_massimo = new QLineEdit(maxString);
        livello_massimo->setMaxLength(7);
        massimoLayout->addWidget(massimoLabel);
        massimoLayout->addWidget(livello_massimo);
        livello_massimo->setValidator(new QDoubleValidator(0, 100, 2, this));

        minimoLayout = new QHBoxLayout;
        QLabel* minimoLabel = new QLabel("Livello minimo", this);
        double minValue = p.getLivello_Minimo();
        QString minString = QString::fromStdString(std::to_string(minValue));
        livello_minimo = new QLineEdit(minString);
        livello_minimo->setMaxLength(7);
        minimoLayout->addWidget(minimoLabel);
        minimoLayout->addWidget(livello_minimo);
        livello_minimo->setValidator(new QDoubleValidator(0, 100, 2, this));

        layoutspecifico->addLayout(scalaLayout);
        layoutspecifico->addLayout(precisioneLayout);
        layoutspecifico->addLayout(massimoLayout);
        layoutspecifico->addLayout(minimoLayout);
        tipo="temperatura";

    }
    else if(dynamic_cast<S_Radiazione*>(&s)){
        S_Radiazione p=static_cast<S_Radiazione&>(s);
        angoloLayout = new QHBoxLayout;
        QLabel* angoloLabel = new QLabel("Angolo radiazione", this);
        double angoloValue = p.getAngolo_Radiazione();
        QString angoloString = QString::fromStdString(std::to_string(angoloValue));
        angolo_radiazione = new QLineEdit(angoloString);
        angolo_radiazione->setMaxLength(7);
        angoloLayout->addWidget(angoloLabel);
        angoloLayout->addWidget(angolo_radiazione);
        angolo_radiazione->setValidator(new QDoubleValidator(0, 100, 2, this));

        fusioneLayout = new QHBoxLayout;
        QLabel* fusioneLabel = new QLabel("Livello fusione", this);
        double fusioneValue = p.getLivello_Fusione();
        QString fusioneString = QString::fromStdString(std::to_string(fusioneValue));
        livello_fusione = new QLineEdit(fusioneString);
        livello_fusione->setMaxLength(7);
        fusioneLayout->addWidget(fusioneLabel);
        fusioneLayout->addWidget(livello_fusione);
        livello_fusione->setValidator(new QDoubleValidator(0, 100, 2, this));

        minimoLayout = new QHBoxLayout;
        QLabel* minimoLabel = new QLabel("Livello minimo", this);
        double minValue = p.getLivello_Minimo();
        QString minString = QString::fromStdString(std::to_string(minValue));
        livello_minimo = new QLineEdit(minString);
        livello_minimo->setMaxLength(7);
        minimoLayout->addWidget(minimoLabel);
        minimoLayout->addWidget(livello_minimo);
        livello_minimo->setValidator(new QDoubleValidator(0, 100, 2, this));

        layoutspecifico->addLayout(angoloLayout);
        layoutspecifico->addLayout(fusioneLayout);
        layoutspecifico->addLayout(minimoLayout);
        tipo="radiazione";
    }
    else {
        S_Umidita p=static_cast<S_Umidita&>(s);
        massimoLayout = new QHBoxLayout;
        QLabel* massimoLabel = new QLabel("Livello massimo", this);
        double maxValue = p.getLivello_Massimo();
        QString maxString = QString::fromStdString(std::to_string(maxValue));
        livello_massimo = new QLineEdit(maxString);
        livello_massimo->setMaxLength(7);
        massimoLayout->addWidget(massimoLabel);
        massimoLayout->addWidget(livello_massimo);
        livello_massimo->setValidator(new QDoubleValidator(0, 100, 2, this));

        muffaLayout = new QHBoxLayout;
        QLabel* muffaLabel = new QLabel("Livello creazione muffa", this);
        double muffaValue = p.getLivello_Massimo();
        QString muffaString = QString::fromStdString(std::to_string(muffaValue));
        livello_muffa = new QLineEdit(muffaString);
        livello_muffa->setMaxLength(7);
        muffaLayout->addWidget(muffaLabel);
        muffaLayout->addWidget(livello_muffa);

        layoutspecifico->addLayout(massimoLayout);
        layoutspecifico->addLayout(muffaLayout);
        tipo="umidita";
    }

    mainlayout->addLayout(layoutcomune);
    mainlayout->addLayout(layoutspecifico);
    mainlayout->addWidget(modifica);
    setLayout(mainlayout);
    setMinimumSize(500,500);
}

void ModificaSensore::modificaSensore(){
    if (descrizione->toPlainText().contains(';')) {
        QMessageBox::critical(this, "Errore", "La descrizione contiene un ';' non ammesso nell'inserimento.");
        return;
    }

    if (nome->text().contains(';')) {
        QMessageBox::critical(this, "Errore", "Il nome contiene un ';' non ammesso nell'inserimento.");
        return;
    }
    if (tipo =="temperatura") {
        double livelloMassimo = livello_massimo->text().toDouble();
        double livelloMinimo = livello_minimo->text().toDouble();
        if (livelloMinimo >= livelloMassimo) {
            QMessageBox::critical(this, "Errore", "Inserire un valore di Livello minimo inferiore al Livello massimo.");
            return;
        }
    }
    if (tipo =="radiazione") {
        double livelloFusione = livello_fusione->text().toDouble();
        double livelloMinimo = livello_minimo->text().toDouble();

        if (livelloMinimo <= livelloFusione) {
            QMessageBox::critical(this, "Errore", "Il Livello minimo deve essere maggiore del Livello di fusione.");
            return;
        }
    }
    Sensore_Astratto* s=nullptr;
    if(tipo =="radiazione")
    {
        s = new S_Radiazione(
        cod,
        nome->text().toStdString(),
        descrizione->toPlainText().toStdString(),
        img,
        costo->text().toDouble(),
        convertItoE(impiantoBox->currentIndex()),
        funzionanteCheckBox->isChecked(),
        angolo_radiazione->text().toDouble(),
        livello_fusione->text().toDouble(),
        livello_minimo->text().toDouble()
            );
    }
    else if(tipo =="umidita")
    {
        s = new S_Umidita(
            cod,
            nome->text().toStdString(),
            descrizione->toPlainText().toStdString(),
            img,
            costo->text().toDouble(),
            convertItoE(impiantoBox->currentIndex()),
            funzionanteCheckBox->isChecked(),
            livello_massimo->text().toDouble(),
            livello_muffa->text().toDouble()
            );
    }
    else {s = new S_Temperatura(
        cod,
        nome->text().toStdString(),
        descrizione->toPlainText().toStdString(),
        img,
        costo->text().toDouble(),
        convertItoE(impiantoBox->currentIndex()),
        funzionanteCheckBox->isChecked(),
        convertItoM(scalaBox->currentIndex()),
        precisione->text().toDouble(),
        livello_massimo->text().toDouble(),
        livello_minimo->text().toDouble()
        );
    }

   try{

       controller->modifica_sensore(*s);
       delete s;
    }
    catch(std::invalid_argument e){
        QMessageBox::critical(this, "Errore", QString::fromStdString(e.what()));
        delete s;
    }
    //emit sensoreModificato();

    close();
}

