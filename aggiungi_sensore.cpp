#include "aggiungi_sensore.h"
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QMessageBox>
#include <QValidator>


AggiungiSensore::AggiungiSensore(QString t,Controller *c,QWidget *parent) : QDialog(parent),controller(c) {
    mainlayout = new QVBoxLayout;
    layoutcomune = new QVBoxLayout;
    layoutspecifico = new QVBoxLayout;

    QHBoxLayout* campiDatiLayout = new QHBoxLayout;
    QVBoxLayout* campiDati[2] = {new QVBoxLayout, new QVBoxLayout};

    QHBoxLayout* tipoLayout = new QHBoxLayout;
    QLabel* tipoLabel = new QLabel("Tipo * ",this);
    tipoBox = new QComboBox(this);
    tipoBox->addItem("");
    tipoBox->addItems({"Radiazione","Temperatura","Umidità"});
    connect(tipoBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, std::bind(&AggiungiSensore::cambiaWidget, this, std::placeholders::_1));


    tipoLayout->addWidget(tipoLabel);
    tipoLayout->addWidget(tipoBox);

    QHBoxLayout* nomeLayout = new QHBoxLayout;
    QLabel* nomeLabel = new QLabel("Nome * ",this);
    nome = new QLineEdit;
    nome->setMaxLength(15);
    nomeLayout->addWidget(nomeLabel);
    nomeLayout->addWidget(nome);

    QHBoxLayout* costoLayout = new QHBoxLayout;
    QLabel* costoLabel = new QLabel("Costo * ",this);
    costo = new QLineEdit;
    costo->setMaxLength(7);
    costoLayout->addWidget( costoLabel);
    costoLayout->addWidget(costo);
    costo->setValidator(new QDoubleValidator(0, 1000000, 2, this));

    QHBoxLayout* impiantoLayout = new QHBoxLayout;
    QLabel* impiantoLabel = new QLabel("Impianto", this);
    impianto = new QLineEdit(t, this);
    impianto->setReadOnly(true);

    impiantoLayout->addWidget(impiantoLabel);
    impiantoLayout->addWidget(impianto);

    QHBoxLayout* descrizioneLayout = new QHBoxLayout;
    QLabel* descLabel = new QLabel("Descrizione * ", this);
    descrizione = new QTextEdit;
    descrizione->setFixedHeight(100);
    descrizioneLayout->addWidget(descLabel);
    descrizioneLayout->addWidget(descrizione);



    QHBoxLayout* codiceLayout = new QHBoxLayout;
    QLabel* codLabel = new QLabel("Codice *",this);
    codice = new QLineEdit;
    codice->setMaxLength(7);
    codiceLayout->addWidget(codLabel);
    codiceLayout->addWidget(codice);
    codice->setValidator(new QDoubleValidator(0, 10000000, 2, this));

    campiDati[0]->addLayout(tipoLayout);
    campiDati[0]->addLayout(nomeLayout);
    campiDati[0]->addLayout(costoLayout);
    campiDati[0]->addLayout(codiceLayout);

    campiDati[1]->addLayout(impiantoLayout);
    campiDati[1]->addLayout(descrizioneLayout);

    campiDatiLayout->addLayout(campiDati[0]);
    campiDatiLayout->addLayout(campiDati[1]);

    QHBoxLayout* imageLayout = new QHBoxLayout;
    QLabel* imgLabel = new QLabel("Immagine",this);
    img = new QComboBox;
    img->addItem(QIcon(":/icone/radiazione1.png"),"radiattore stilizzato ");
    img->addItem(QIcon(":/icone/radiazione2.png"),"simbolo energia");
    img->addItem(QIcon(":/icone/radiazione3.png"),"radiazione color giallo");
    img->addItem(QIcon(":/icone/temperatura1.png"),"termometro rosso");
    img->addItem(QIcon(":/icone/temperatura2.png"),"termometro nero");
    img->addItem(QIcon(":/icone/temperatura3.png"),"temeratura alta");
    img->addItem(QIcon(":/icone/umidita1.png"),"umidità fitta");
    img->addItem(QIcon(":/icone/umidita2.png"),"nuovoletta");
    img->addItem(QIcon(":/icone/umidita3.png"),"tre goccioline");
    img->setFixedWidth(300);

    imageLayout->addWidget(imgLabel);
    imageLayout->addWidget(img);

    layoutcomune->addLayout(campiDatiLayout);
    layoutcomune->addLayout(imageLayout);

    QPushButton* aggiungi = new QPushButton("Aggiungi",this);
    aggiungi->setStyleSheet("background-color: rgb(67, 108, 108); color: white;");
    connect(aggiungi,SIGNAL(clicked()), this, SLOT(aggiungi()));

    mainlayout->addLayout(layoutcomune);
    mainlayout->addLayout(layoutspecifico);
    mainlayout->addWidget(aggiungi);
    setLayout(mainlayout);
    setMinimumSize(500,500);

    connect(this,SIGNAL(sensoreAggiunto(Sensore_Astratto*)),parent,SLOT(sensoreAggiunto(Sensore_Astratto*)));
}
void AggiungiSensore::aggiungi(){
    int index = tipoBox->currentIndex();



    if (index == 0 || codice->text().isEmpty() || nome->text().isEmpty() || costo->text().isEmpty() || descrizione->toPlainText().isEmpty()
        || ((index == 1) && (angolo_radiazione->text().isEmpty() || livello_fusione->text().isEmpty() || livello_minimo->text().isEmpty()))
        || ((index == 2) && ( precisione->text().isEmpty() || livello_massimo->text().isEmpty() || livello_minimo->text().isEmpty()))
        || ((index == 3) && (livello_massimo->text().isEmpty() || livello_muffa->text().isEmpty()))) {
        QMessageBox::critical(this, "Errore", "Compilare tutti i campi obbligatori (*).");
        return;
    }
    bool isCodiceValido = true;
    unsigned int nuovoCodice = codice->text().toUInt(&isCodiceValido);

    if (!isCodiceValido) {
        QMessageBox::critical(this, "Errore", "Il codice deve contenere solo numeri interi non negativi.");
        return;
    }
    if (codice->text().contains(';')) {
        QMessageBox::critical(this, "Errore", "Il codice contiene un ';' non ammesso nell'inserimento.");
        return;
    }

    if (controller->codiceEsiste(static_cast<int>(nuovoCodice))) {
        QMessageBox::critical(this, "Errore", "Il codice inserito è già stato utilizzato. Inserire un codice univoco.");
        return;
    }

    if (descrizione->toPlainText().contains(';')) {
        QMessageBox::critical(this, "Errore", "La descrizione contiene un ';' non ammesso nell'inserimento.");
        return;
    }

    if (nome->text().contains(';')) {
        QMessageBox::critical(this, "Errore", "Il nome contiene un ';' non ammesso nell'inserimento.");
        return;
    }
    if (index == 2) {
        double livelloMassimo = livello_massimo->text().toDouble();
        double livelloMinimo = livello_minimo->text().toDouble();
        if (livelloMinimo >= livelloMassimo) {
            QMessageBox::critical(this, "Errore", "Inserire un valore di Livello minimo inferiore al Livello massimo.");
            return;
        }
    }
    if (index == 1) {
        double livelloFusione = livello_fusione->text().toDouble();
        double livelloMinimo = livello_minimo->text().toDouble();

        if (livelloMinimo <= livelloFusione) {
            QMessageBox::critical(this, "Errore", "Il Livello minimo deve essere maggiore del Livello di fusione.");
            return;
        }
    }

     Sensore_Astratto* s;

    switch (index) {
    case 1:
    {
        s = new S_Radiazione(
            codice->text().toInt(),
            nome->text().toStdString(),
            descrizione->toPlainText().toStdString(),
            img->currentIndex(),
            costo->text().toDouble(),
            convertStoE(impianto->text().toStdString()),
            true,
            angolo_radiazione->text().toDouble(),
            livello_fusione->text().toDouble(),
            livello_minimo->text().toDouble()
            );

    }
    break;
    case 2:
    {
        s = new S_Temperatura(
            codice->text().toInt(),
            nome->text().toStdString(),
            descrizione->toPlainText().toStdString(),
            img->currentIndex(),
            costo->text().toDouble(),
            convertStoE(impianto->text().toStdString()),
            true,
            convertItoM(scalaBox->currentIndex()),
            precisione->text().toDouble(),
            livello_massimo->text().toDouble(),
            livello_minimo->text().toDouble()
            );
    }
    break;
    default:{
        s = new S_Umidita(
            codice->text().toInt(),
            nome->text().toStdString(),
            descrizione->toPlainText().toStdString(),
            img->currentIndex(),
            costo->text().toDouble(),
            convertStoE(impianto->text().toStdString()),
            true,
            livello_massimo->text().toDouble(),
            livello_muffa->text().toDouble()
            );
        break;
    }
    }

    emit sensoreAggiunto(s);
    close();
}

void AggiungiSensore::pulisciLayoutSpecifichi(QLayout* layout) {
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        if (child->layout()) {
            pulisciLayoutSpecifichi(child->layout());
        } else if (child->widget()) {
            delete child->widget();
        }
        delete child;
    }
}

void AggiungiSensore::cambiaWidget(int index) {
    pulisciLayoutSpecifichi(layoutspecifico);
    switch (index) {
    case 1:
    {
        angoloLayout = new QHBoxLayout;
        QLabel* angoloLabel = new QLabel("Angolo radiazione *", this);
        angolo_radiazione = new QLineEdit;
        angolo_radiazione->setMaxLength(7);
        angoloLayout->addWidget(angoloLabel);
        angoloLayout->addWidget(angolo_radiazione);
        angolo_radiazione->setValidator(new QDoubleValidator(0, 100, 2, this));

        fusioneLayout = new QHBoxLayout;
        QLabel* fusioneLabel = new QLabel("Livello fusione *", this);
        livello_fusione = new QLineEdit;
        livello_fusione->setMaxLength(7);
        fusioneLayout->addWidget(fusioneLabel);
        fusioneLayout->addWidget(livello_fusione);
        livello_fusione->setValidator(new QDoubleValidator(0, 100, 2, this));

        minimoLayout = new QHBoxLayout;
        QLabel* minimoLabel = new QLabel("Livello minimo *", this);
        livello_minimo = new QLineEdit;
        livello_minimo->setMaxLength(7);
        minimoLayout->addWidget(minimoLabel);
        minimoLayout->addWidget(livello_minimo);
        livello_minimo->setValidator(new QDoubleValidator(0, 100, 2, this));

        layoutspecifico->addLayout(angoloLayout);
        layoutspecifico->addLayout(fusioneLayout);
        layoutspecifico->addLayout(minimoLayout);
        mainlayout->addLayout(layoutspecifico);
    }
    break;
    case 2:
    {
        scalaLayout = new QHBoxLayout;
        QLabel* scalaLabel = new QLabel("Scala misurazione ", this);
        scalaBox = new QComboBox(this);
        scalaBox->addItems({"Kelvin", "Fahrenheit", "Celsius"});
        scalaLayout->addWidget(scalaLabel);
        scalaLayout->addWidget(scalaBox);

        precisioneLayout = new QHBoxLayout;
        QLabel* precLabel = new QLabel("Precisione *", this);
        precisione = new QLineEdit;
        precisione->setMaxLength(7);
        precisioneLayout->addWidget(precLabel);
        precisioneLayout->addWidget(precisione);
        precisione->setValidator(new QDoubleValidator(0, 100, 2, this));

        massimoLayout = new QHBoxLayout;
        QLabel* massimoLabel = new QLabel("Livello massimo *", this);
        livello_massimo = new QLineEdit;
        livello_massimo->setMaxLength(7);
        massimoLayout->addWidget(massimoLabel);
        massimoLayout->addWidget(livello_massimo);
        livello_massimo->setValidator(new QDoubleValidator(0, 100, 2, this));

        minimoLayout = new QHBoxLayout;
        QLabel* minimoLabel = new QLabel("Livello minimo", this);
        livello_minimo = new QLineEdit;
        livello_minimo->setMaxLength(7);
        minimoLayout->addWidget(minimoLabel);
        minimoLayout->addWidget(livello_minimo);
        livello_minimo->setValidator(new QDoubleValidator(0, 100, 2, this));

        layoutspecifico->addLayout(scalaLayout);
        layoutspecifico->addLayout(precisioneLayout);
        layoutspecifico->addLayout(massimoLayout);
        layoutspecifico->addLayout(minimoLayout);
        mainlayout->addLayout(layoutspecifico);
    }
    break;
    case 3:
    {
        massimoLayout = new QHBoxLayout;
        QLabel* massimoLabel = new QLabel("Livello massimo *", this);
        livello_massimo = new QLineEdit;
        livello_massimo->setMaxLength(7);
        massimoLayout->addWidget(massimoLabel);
        massimoLayout->addWidget(livello_massimo);
        livello_massimo->setValidator(new QDoubleValidator(0, 100, 2, this));

        muffaLayout = new QHBoxLayout;
        QLabel* muffaLabel = new QLabel("Livello creazione muffa *", this);
        livello_muffa = new QLineEdit;
        livello_muffa->setMaxLength(7);
        muffaLayout->addWidget(muffaLabel);
        muffaLayout->addWidget(livello_muffa);

        layoutspecifico->addLayout(massimoLayout);
        layoutspecifico->addLayout(muffaLayout);
        mainlayout->addLayout(layoutspecifico);
    }
    break;
    default:
        break;
    }
}

