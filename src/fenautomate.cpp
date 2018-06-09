#include "headers/fenautomate.h"

fenAutomate::fenAutomate(Simulateur* s):monSimu(s), probability(60)
{
    setWindowTitle("Automate anonyme");
    UImaker();
}


fenAutomate::fenAutomate(QString nom, Simulateur* s): monSimu(s), probability(60)
{
    setWindowTitle(nom);
    UImaker();
}


void fenAutomate::UImaker(){

    setWindowIcon(QIcon(":/img/virus.png"));
    playPause = true;
    setMinimumSize(500,500);
    myCentralWidget = new QWidget;

    BTavancer = new QPushButton("Avancer", myCentralWidget);
    BTreculer = new QPushButton("Reculer",myCentralWidget);
    BTplay = new QPushButton(QIcon(":/img/play-button.png"),"", myCentralWidget);
    BTplay->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    BTplay->setFlat(true);
    BTinit = new QPushButton("Initialiser", myCentralWidget);

    myTimer = new QTimer(this);
    mySlider = new QSlider(Qt::Horizontal);
    mySlider->setMinimum(1);mySlider->setMaximum(10000);
    mySlider->setValue(1000);
    myTimer->setInterval(mySlider->value());

    connect(myTimer,SIGNAL(timeout()),this,SLOT(slotAvancer()));
    connect(BTplay, SIGNAL(clicked()),this,SLOT(slotBtPlayStop()));
    connect(mySlider,SIGNAL(sliderMoved(int)),this,SLOT(slotTimerIntervalChange(int)));
    connect(BTavancer,SIGNAL(clicked()),this,SLOT(slotAvancer()));
    connect(BTreculer,SIGNAL(clicked()),this,SLOT(slotReculer()));
    connect(BTinit, SIGNAL(clicked()),this,SLOT(slotInit()));

    QHBoxLayout* BTLayout = new QHBoxLayout;
    BTLayout->addWidget(BTreculer);
    BTLayout->addWidget(BTplay);
    BTLayout->addWidget(BTavancer);
    BTLayout->addWidget(BTinit);

    monLayout = new QGridLayout;
    monLayout->addLayout(BTLayout,90,0,5,100);
    monLayout->addWidget(mySlider,95,0,5,100);
    setCentralWidget(myCentralWidget);
    myCentralWidget->setLayout(monLayout);
}


void fenAutomate::slotBtPlayStop(){
    if(playPause){
        BTplay->setIcon(QIcon(":/pause.png"));
        myTimer->start(mySlider->value());
        playPause = false;
    }else{
        myTimer->stop();
        BTplay->setIcon(QIcon(":/play-button.png"));
        playPause = true;
    }
    BTplay->repaint();
}


void fenAutomate::slotTimerIntervalChange(int i){
    if(myTimer==nullptr) return;
    myTimer->setInterval(i);
}


void fenAutomate::slotAvancer(){
    avancer();
}


void fenAutomate::slotReculer(){
    reculer();
}

void fenAutomate::slotInit(){
    initialize();
}
