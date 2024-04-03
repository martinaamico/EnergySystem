#include "sensore_item.h"
#include "modifica_sensore.h"
#include <QDialog>
#include <QMessageBox>



SensoreItem::SensoreItem(Sensore_Astratto *s,bool mostra_pulsanti ,bool mostra_check )
{
    nome = QString::fromStdString(s->getNome());
    codice = QString::fromStdString(std::to_string(s->getCodice()));
    img = QIcon(QString::fromStdString(":/icone/"+ icons_names[s->getPercorso_Immagine()]+".png"));

    // Crea il widget principale
    background = new QFrame;
    background->setFrameShape(QFrame::StyledPanel);

    // Crea il layout orizzontale per SensoreItem
    QHBoxLayout* layout = new QHBoxLayout(background);

    QLabel* label = new QLabel();
    label->setPixmap(img.pixmap(30,30));

    layout->addWidget(label);

    // Aggiungi le etichette al layout
    QHBoxLayout* info = new QHBoxLayout;
    info->addWidget(new QLabel(nome));
    info->addWidget(new QLabel(codice));
    layout->addLayout(info);

    if(mostra_pulsanti){
        modifica = new QPushButton("");
        modifica->setStyleSheet("background-color: white;");
        modifica->setIcon(QIcon(":/icone/modifica.png"));
        connect(modifica, SIGNAL(clicked()), this, SLOT(ModificaSensoreDialog()));

        elimina = new QPushButton("");
        elimina->setStyleSheet("background-color: white;");
        elimina->setIcon(QIcon(":/icone/elimina.png"));
        connect(elimina, SIGNAL(clicked()), this, SLOT(eliminaSensore()));

        if (width() < 600) {
            // Rimuovi lo spazio per il testo e lascia solo l'icona
            modifica->setText("");
            elimina->setText("");
        } else {
            // Mostra il testo insieme all'icona
            modifica->setText("Modifica");
            elimina->setText("Elimina");
        }
        layout->addWidget(modifica);
        layout->addWidget(elimina);

    }
    if(mostra_check){
        selezioneCheckBox = new QCheckBox;
        //connect(selezioneCheckBox, &QCheckBox::stateChanged, this, &SensoreItem::onSelezioneChanged);

        layout->addWidget(selezioneCheckBox);
    }

    // Imposta il layout principale
    setLayout(layout);
}

void SensoreItem::ModificaSensoreDialog() {
    emit modificaSensoreClicked(codice.toInt());
}

void SensoreItem::eliminaSensore()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Conferma eliminazione", "Sei sicuro/a di voler eliminare il sensore?",
    QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        emit eliminaSensoreClicked(codice.toInt());
    }
}

QString SensoreItem::getCodice() const{
    return codice;
}

QString SensoreItem::getNome() const{
    return nome;
}

bool SensoreItem::isChecked() const {
    return selezioneCheckBox->isChecked();
}
