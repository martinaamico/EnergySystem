#include "contenuto.h"
#include <QScrollBar>
#include <QScrollArea>
#include <QDialog>
#include "aggiungi_sensore.h"
#include <QMessageBox>
#include "modifica_sensore.h"
#include <QStackedWidget>
#include <QLineEdit>
#include <QtCharts>

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QValueAxis>


#include "controller.h"

void Contenuto::load_lista()
{
    auto listaSensori = controller->getSensoriTipo(convertStoE(title.toStdString()));
    lista->clear();
    for (auto sensore : listaSensori) {
        lista->nuovo(sensore);
    }
    connect(lista, &SensorListWidget::modificaSensoreClicked, this, &Contenuto::apriModificaSensoreDialog);
    connect(lista, &SensorListWidget::eliminaSensoreClicked, this, &Contenuto::eliminaSensore);
}

void Contenuto::load_simulazione()
{
    auto listasensori= controller->getSensoriTipo(convertStoE(title.toStdString()));
    listaSimulazione->clear();
    for (auto sensore : listasensori) {
        listaSimulazione->nuovo(sensore);
    }
}

void Contenuto::addButtons() {
    barra = new QHBoxLayout;

    aggiungi = new QPushButton("Aggiungi");
    aggiungi->setStyleSheet("background-color:rgb(67,108,108) ; color:white ;");
    aggiungi->setIcon(QIcon(":/icone/aggiungi.png"));
    aggiungi->setIconSize(QSize(40, 50));
    connect(aggiungi, &QPushButton::clicked, this, &Contenuto::AggiungiSensoreDialog);

    cerca = new QPushButton("Cerca");
    cerca->setStyleSheet("background-color:rgb(67,108,108) ; color:white ;");
    cerca->setIcon(QIcon(":/icone/cerca.png"));
    cerca->setIconSize(QSize(40, 50));
    connect(cerca, &QPushButton::clicked, this, &Contenuto::onCercaButtonClicked);

    simula = new QPushButton("Simula");
    simula->setStyleSheet("background-color:rgb(67,108,108) ; color:white ;");
    simula->setIcon(QIcon(":/icone/simula.png"));
    simula->setIconSize(QSize(40, 50));
    connect(simula, &QPushButton::clicked, this, &Contenuto::SimulaClicked);

    barra->addWidget(aggiungi);
    barra->addWidget(cerca);
    barra->addWidget(simula);

    layout->addLayout(barra);
}

void Contenuto::addHomePage()
{
    QWidget *scrollAreaPage = new QWidget(stackedWidget);
    QHBoxLayout *scrollAreaLayout = new QHBoxLayout;

    lista = new SensorListWidget(scrollAreaPage);
    load_lista();

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(lista);
    scrollArea->setWidgetResizable(true);
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { background:rgb(67,108,108); }");
    scrollArea->setStyleSheet("QScrollArea { border: 1px solid black; }");

    scrollAreaLayout->addWidget(scrollArea);
    scrollAreaPage->setLayout(scrollAreaLayout);
    stackedWidget->addWidget(scrollAreaPage);
}

void Contenuto::addCercaPage() {
    QWidget *cercaPage = new QWidget(stackedWidget);
    QVBoxLayout *cercaLayout = new QVBoxLayout;

    QHBoxLayout *searchBarLayout = new QHBoxLayout;
    searchLineEdit = new QLineEdit(cercaPage);
    searchLineEdit->setPlaceholderText("Inserisci una ricerca");
    searchLineEdit->setStyleSheet("QLineEdit { height: 30px; }");
    QPushButton *trovaRisultatiButton = new QPushButton("Trova risultati", cercaPage);
    trovaRisultatiButton->setStyleSheet("QPushButton { font-size: 16px; }");

    trovaRisultatiButton->setStyleSheet(
        "QPushButton { font-size: 16px; background-color: #FFECB3; color: rgb(67,108,108); }");

    connect(trovaRisultatiButton, &QPushButton::clicked, this, &Contenuto::trovaRisultatiClicked);


    cercaLayout->addLayout(searchBarLayout);

    risultatiListWidget = new SensorListWidget(cercaPage);
    QScrollArea *resultScrollArea = new QScrollArea;
    resultScrollArea->setWidget(risultatiListWidget);
    resultScrollArea->setWidgetResizable(true);
    resultScrollArea->setStyleSheet("QScrollArea { border: 1px solid black; }");
    resultScrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { background:rgb(67,108,108); }");
    resultScrollArea->setStyleSheet("QScrollArea { border: 1px solid black; }");

    cercaLayout->addWidget(resultScrollArea);

    cercaPage->setLayout(cercaLayout);
    searchBarLayout->addWidget(searchLineEdit);
    searchBarLayout->addWidget(trovaRisultatiButton);
    noResultsLabel = new QLabel("Non ci sono sensori affini alla tua ricerca.", cercaPage);
    noResultsLabel->setAlignment(Qt::AlignCenter);
    noResultsLabel->hide();
    cercaLayout->addWidget(noResultsLabel);
    stackedWidget->addWidget(cercaPage);
}

void Contenuto::addSimulazionePage() {
    QWidget *simulazionePage = new QWidget;
    QVBoxLayout *simulazioneLayout = new QVBoxLayout;

    QHBoxLayout *dateLabelsLayout = new QHBoxLayout;
    QLabel *labelFrom = new QLabel("Dal:", simulazionePage);
    QLabel *labelTo = new QLabel("Al:", simulazionePage);
    dateLabelsLayout->addWidget(labelFrom);
    dateLabelsLayout->addWidget(labelTo);

    QHBoxLayout *dateEditsLayout = new QHBoxLayout;
    dateFromEdit = new QDateEdit(simulazionePage);
    dateToEdit = new QDateEdit(simulazionePage);
    dateEditsLayout->addWidget(dateFromEdit);
    dateEditsLayout->addWidget(dateToEdit);

    simulazioneLayout->addLayout(dateLabelsLayout);
    simulazioneLayout->addLayout(dateEditsLayout);
    listaSimulazione = new SensorListWidget(stackedWidget,false,true);

    QScrollArea *sensorScrollAreaComplete = new QScrollArea(simulazionePage);
    sensorScrollAreaComplete->setWidget(listaSimulazione);
    sensorScrollAreaComplete->setWidgetResizable(true);
    sensorScrollAreaComplete->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { background:rgb(67,108,108); }");
    sensorScrollAreaComplete->setStyleSheet("QScrollArea { border: 1px solid black; }");
    simulazioneLayout->addWidget(sensorScrollAreaComplete);

    QPushButton *avviaSimulazioneButton = new QPushButton("Avvia Simulazione", simulazionePage);
    simulazioneLayout->addWidget(avviaSimulazioneButton);
    connect(avviaSimulazioneButton, &QPushButton::clicked, this, &Contenuto::avviaSimulazione);

    simulazionePage->setLayout(simulazioneLayout);
    stackedWidget->addWidget(simulazionePage);

    load_simulazione();

}

Contenuto::Contenuto(QString t, Controller *c, QWidget *parent)
    : QWidget(parent), controller(c), title(t), cercaButtonClicked(false)
{
    layout = new QVBoxLayout;

    QLabel *titleWidget = new QLabel(title, this);
    layout->addWidget(titleWidget);

    // Barra dei pulsanti
    addButtons();

    stackedWidget = new QStackedWidget(this);

    addHomePage();

    addCercaPage();

    addSimulazionePage();

    // Aggiungi il QStackedWidget al layout principale
    layout->addWidget(stackedWidget);

    // Imposta il layout principale
    setLayout(layout);
}


void Contenuto::onCercaButtonClicked() {
    // Cambia alla pagina "Cerca"
    stackedWidget->setCurrentIndex(1);
}

void Contenuto::trovaRisultatiClicked() {
    // Chiamata alla funzione del controller
    std::string testoRicerca = searchLineEdit->text().toStdString();
    try{

        std::vector<Sensore_Astratto*> risultati = controller->cercaSensori(testoRicerca, title.toStdString());
        risultatiListWidget->clear();

        noResultsLabel->hide();
        for (auto sensore : risultati) {
            risultatiListWidget->nuovo(sensore);
        }
        connect(risultatiListWidget, &SensorListWidget::modificaSensoreClicked, this, &Contenuto::apriModificaSensoreDialog);
        connect(risultatiListWidget, &SensorListWidget::eliminaSensoreClicked, this, &Contenuto::eliminaSensore);
    }
    catch(std::invalid_argument e){
        noResultsLabel->show();
    }

}

void Contenuto::sensoreAggiunto(Sensore_Astratto* s){

    try{
        controller->aggiungi(s);
        load_lista();
        load_simulazione();
        if(stackedWidget->currentIndex() == 1)
            trovaRisultatiClicked();

        stackedWidget->update();
    }
    catch(std::invalid_argument e){
        QMessageBox::critical(this, "Errore", "Il sensore non è stato aggiunto");
    }
    delete s;
}
void Contenuto::eliminaSensore(int codice)
{
    controller->eliminaSensore(codice);
    lista->eliminaSensore(codice);
    if(stackedWidget->currentIndex() == 0)
        load_lista();
    if(stackedWidget->currentIndex() == 1)
        trovaRisultatiClicked();
    if(stackedWidget->currentIndex() == 2)
        load_simulazione();
}

void Contenuto::AggiungiSensoreDialog() {
    auto dialog = new AggiungiSensore(title,controller,this);
    dialog->show();
}
void Contenuto::apriModificaSensoreDialog(int codice) {
    try{
        Sensore_Astratto &sensore = controller->get_sensore(codice);
        auto dialog = new ModificaSensore(sensore,controller, this);
        dialog->show();
        //connect(dialog, &ModificaSensore::sensoreModificato, this, &Contenuto::sensoreModificato);
    }
    catch(std::invalid_argument e){
        QMessageBox::critical(this, "Errore", "Il sensore non modificato");
    }
}

void Contenuto::sensoreModificato() {
    load_lista();  // Aggiorna la lista principale
    if (stackedWidget->currentIndex() == 1)
        trovaRisultatiClicked();  // Aggiorna la lista di ricerca, se necessario

    stackedWidget->update();
}
void Contenuto::SimulaClicked() {
    stackedWidget->setCurrentIndex(2);
}


void Contenuto::avviaSimulazione() {//gb

    // Ottengo i codici dei sensori
    QList<SensoreItem*> items = listaSimulazione->getSensoriSelezionati();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Errore", "Seleziona almeno un sensore prima di avviare la simulazione.");
        return;
    }


    std::vector<QString> codes;

    for (SensoreItem* item : items) {
        codes.push_back(item->getCodice());
    }
    int days = (dateToEdit->date().toJulianDay() - dateFromEdit->date().toJulianDay());


    if (days < 0) {
        QMessageBox::warning(this, "Errore", "La data d'arrivo deve essere uguale o successiva a quella di partenza");
        return;
    }

    std::vector<Simulazione>  results = controller->avviasimulazione(codes, days+1);

    // Per ogni simulazione produco un grafico
    for (unsigned int i = 0; i < results.size(); i++) {
        Simulazione simulazione = results[i];
        unsigned int n_misurazioni = simulazione.size();
        unsigned int n_sensori = simulazione[0].size();

        if (n_sensori <= 0) continue;
        // n_sensori > 0

        // Imposto gli assi delle ascisse del grafico
        QChart *chart = new QChart;

        QDateTime from = dateFromEdit->dateTime();
        from.setTime(QTime(0,0));
        QDateTime to = dateToEdit->dateTime();
        to.setTime(QTime(23,0));

        int from_milliseconds_epoch = from.toMSecsSinceEpoch();

        QDateTimeAxis *axisX = new QDateTimeAxis;
        QDateTimeAxis *axisX2 = new QDateTimeAxis;

        // Limiti degli assi e numero di coordinate da mostrare
        axisX->setRange(from,to);
        axisX2->setRange(from,to);
        axisX->setTickCount(days+2);
        axisX2->setTickCount(n_misurazioni > 48 ? 48 : n_misurazioni);

        // Formato delle etichette e posizionamento
        axisX->setFormat("yyyy-MM-dd");
        axisX2->setFormat("hh:mm");
        axisX2->setLabelsAngle(90);
        axisX->setLineVisible(false);

        QScatterSeries* brokenMarkers = new QScatterSeries;
        brokenMarkers->setMarkerSize(20);
        brokenMarkers->setColor(QColor(255,0,0));

        // Creo una serie per ogni sensore
        for (unsigned int j = 0; j < n_sensori; j++) {
            auto *series = new QLineSeries;

            unsigned int k;
            for (k = 0; k < n_misurazioni; k++) {

                if(k > 1 && simulazione[k-2][j] == simulazione[k-1][j] && simulazione[k-1][j] == simulazione[k][j]){

                    series->remove(k-1);
                    series->remove(k-2);

                    if (k > 2) {
                        brokenMarkers->append(from_milliseconds_epoch + (k-3) * 360000, simulazione[k-3][j]);
                    }
                    break;
                } else {
                    series->append(from_milliseconds_epoch + k * 360000, simulazione[k][j]);
                }
            }

            if (series->count() > 0) {
                chart->addSeries(series);
                series->setName(items[j]->getNome());
            } else {
                // Se la serie è vuota allora il sensore era rotto in partenza
                // Avviso l'utente
                QDialog* alertDialog = new QDialog;
                QVBoxLayout *alertLayout = new QVBoxLayout;
                alertLayout->addWidget(new QLabel("Il sensore \"" + items[j]->getNome() + "\"è non funzionante. Non è stato aggiunto al grafico"));
                alertDialog->setLayout(alertLayout);

                alertDialog->exec();
            }
        }

        if (brokenMarkers->count() > 0) chart->addSeries(brokenMarkers);

        // Aggiungo gli assi al grafico
        chart->createDefaultAxes(); // Necessario perché le serie restino ordinate
        chart->addAxis(axisX2, Qt::AlignBottom);
        chart->addAxis(axisX, Qt::AlignBottom);

        auto axes = chart->axes();
        auto realAxis = axes.first();
        realAxis->hide();

        // titolo specifico dovrebbe prendere anch el'impianto ?
        QString titolo;
        switch (i) {
        case 0:
            titolo = "Grafico sensori temperatura";
            break;
        case 1:
            titolo = "Grafico sensori umidità";
            break;
        case 2:
            titolo = "Grafico sensori radiazione";
            break;
        default:
            titolo = "Grafico simulazione " + QString::number(i + 1);
        }

        // Impostazioni generali del grafico
        chart->setTitle(titolo);

        // Imposta la dimensione predefinita del grafico a 500x500 ma non ci sta tutto dovrebbe prender assi in base ai valori massimi  eminimi?
        chart->setMinimumSize(500, 500);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QDialog* dialog = new QDialog;
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(chartView);
        dialog->setLayout(layout);

        dialog->show();
    }
}


