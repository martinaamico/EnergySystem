#include "mainwindow.h"
#include <QTextEdit>
#include <QDialog>
#include <QFileDialog>
#include "contenuto.h"
#include <QMessageBox>

#include "controller.h"

void MainWindow::addButtons() {
    auto button1 = new EnergiaButton(Energia::eolico, this);
    button1->setStyleSheet("background-color: rgb(67, 108, 108); color: white;");
    button1->setIcon(QIcon(":/icone/vento.png"));
    button1->setIconSize(QSize(50, 50));
    button1->setMaximumWidth(150);

    auto button2 = new EnergiaButton(Energia::solare, this);
    button2->setStyleSheet("background-color: rgb(67, 108, 108); color: white;");
    button2->setIcon(QIcon(":/icone/sole.png"));
    button2->setIconSize(QSize(50, 50));
    button2->setMaximumWidth(150);


    button1->setMaximumWidth(150);
    button2->setMaximumWidth(150);

    connect(button1,SIGNAL(change(Energia)),this,SLOT(switchWidget(Energia)));
    connect(button2,SIGNAL(change(Energia)),this,SLOT(switchWidget(Energia)));
    sideMenuLayout->addWidget(button1);
    sideMenuLayout->addWidget(button2);
    //sideMenuLayout->setAlignment(Qt::AlignHCenter);

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    auto placeholderWidget = new QWidget(this);


    auto mainLayout = new QHBoxLayout;
    placeholderWidget->setLayout(mainLayout);

    // add menu
    auto menu = new QMenuBar;
    auto fileMenu = menu->addMenu("File");

    QAction *salvaAction = fileMenu->addAction("Salva");
    salvaAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    connect(salvaAction, &QAction::triggered, this, &MainWindow::salva);
    salvaAction->setIcon(QIcon(":/icone/salva.png"));

    QAction *caricaAction = fileMenu->addAction("Carica");
    caricaAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_C));
    connect(caricaAction, &QAction::triggered, this, &MainWindow::carica);
    caricaAction->setIcon(QIcon(":/icone/carica.png"));

    setMenuBar(menu);

    sideMenuLayout = new QVBoxLayout;
    auto titleLabel = new QLabel("EnergySystem");
    titleLabel->setStyleSheet("color: #FDE910	; background-color:;");
    titleLabel->setAlignment(Qt::AlignHCenter);
    titleLabel->setFont(QFont("Arial", 20, QFont::Bold));
    titleLabel->setMaximumHeight(40);
    sideMenuLayout->addWidget(titleLabel);


    QWidget* sideMenuWidget = new QWidget();
    sideMenuWidget->setLayout(sideMenuLayout);
    sideMenuWidget->setStyleSheet("background-color: rgb(204,204,204);");
    mainLayout->addWidget(sideMenuWidget);

    // add buttons
    addButtons();

    screenLayout = new QVBoxLayout;
    screenLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    QWidget* screenWidget = new QWidget();
    screenWidget ->setLayout(screenLayout);
    screenWidget ->setStyleSheet("background-color:#C8D0D0;");

    imageLabel = new QLabel;
    imageLabel->setPixmap(QPixmap(":/icone/schematainizio.jpg"));
    imageLabel->setAlignment(Qt::AlignCenter);
    screenLayout->addWidget(imageLabel);
    mainLayout->addWidget( screenWidget);
    sideWidget = new QWidget(placeholderWidget);
    screenLayout->addWidget(sideWidget);

    mainLayout->setContentsMargins(20,5,20,5);
    mainLayout->setSpacing(10);

    setMinimumSize(720,480);
    setCentralWidget(placeholderWidget);
    setWindowTitle("Sensori");

}

void MainWindow::switchWidget(Energia k) {
    if (sideWidget) {
        delete sideWidget;
        sideWidget = nullptr; // Imposta a nullptr dopo la cancellazione
    }

    // Cancella solo l'oggetto widget se esiste
    if (imageLabel) {
        delete imageLabel;
        imageLabel = nullptr; // Imposta a nullptr dopo la cancellazione
    }

    // Crea e aggiungi nuovi oggetti widget
    sideWidget = new Contenuto(QString::fromStdString(convertEtoS(k)), controller, this);
    screenLayout->addWidget(sideWidget);

    // Rimuovi eventuali stili CSS
    sideWidget->setStyleSheet("");
    QString defaultStyleSheet = "background-color: rgb(67,108,108); color: white;";
    QString selectedStyle = "background-color: white; color: black;";

    // Imposta gli stili per i pulsanti del menu laterale
    sideMenuLayout->itemAt(1)->widget()->setStyleSheet(defaultStyleSheet);
    sideMenuLayout->itemAt(2)->widget()->setStyleSheet(defaultStyleSheet);
    sideMenuLayout->itemAt(int(k+1))->widget()->setStyleSheet(selectedStyle);
}



MainWindow::~MainWindow(){}

void MainWindow::carica() {
    QString filePath = QFileDialog::getOpenFileName(this, "Seleziona il file da caricare", "", "File di testo (*.txt);;Tutti i file (*)");
    if (!filePath.isEmpty()) {
        try{
            controller->carica_file(filePath);
        }
        catch (std::invalid_argument e) {
            QMessageBox::critical(this, "Errore", "Caricamento non avvenuto, dati non sono salvati nel modo corretto");
        }
    }
}

void MainWindow::salva() {
    QString filePath = QFileDialog::getSaveFileName(this, "Seleziona il percorso per salvare il file", "", "File di testo (*.txt);;Tutti i file (*)");
    if (!filePath.isEmpty()) {
        controller->salva_file(filePath);
    }
}

void MainWindow::setController(Controller * c){ controller = c; }
