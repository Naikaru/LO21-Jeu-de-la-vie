#include "headers/fenautomate.h"

fenAutomate::fenAutomate(Simulateur* s):monSimu(s)
{
    setWindowTitle("Automate anonyme");
    UImaker();
}


fenAutomate::fenAutomate(QString nom, Simulateur* s): monSimu(s)
{
    setWindowTitle(nom);
    UImaker();
}


void fenAutomate::UImaker(){

    setWindowIcon(QIcon(":/img/virus.png"));
    playPause = true;
    setMinimumSize(500,500);
    myCentralWidget = new QWidget;

    BTavancer = new QPushButton(QIcon(":/img/fast-forward-2.png"),"", myCentralWidget);
    BTreculer = new QPushButton(QIcon(":/img/backward.png"),"",myCentralWidget);
    BTplay = new QPushButton(QIcon(":/img/play-button.png"),"", myCentralWidget);
    BTinit = new QPushButton(QIcon(":/img/shuffle.png"),"", myCentralWidget);
    choixInit = new QComboBox();
    choixInit->addItem("Random");
    choixInit->addItem("Symetric");

    BTplay->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    BTplay->setFlat(true);
    BTreculer->setFlat(true);
    BTavancer->setFlat(true);
    BTinit->setFlat(true);

    myTimer = new QTimer(this);
    mySlider = new QSlider(Qt::Horizontal);
    mySlider->setMinimum(1);mySlider->setMaximum(1000);
    mySlider->setValue(750);
    mySlider->setInvertedAppearance(true);
    mySlider->setStyleSheet("""QSlider::groove:horizontal {border: 2px solid #A0A5B2; border-radius: 2px;height: 4px;background: #E8E8E8;}QSlider::handle:horizontal {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFFF, stop: 0.7 #3975D7,stop: 1.0 #C0C0FF);width: 20px;border-top: 1px solid #FFFFFF; border-left: 1px solid #0000FF; border-right: 1px solid #0000FF;border-bottom: 2px solid #0000CC;border-radius: 2px;margin: -3px 0;}""");
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
    BTLayout->addWidget(choixInit);

    monLayout = new QGridLayout;
    monLayout->addLayout(BTLayout,90,0,5,100);
    monLayout->addWidget(mySlider,95,0,5,100);
    setCentralWidget(myCentralWidget);
    myCentralWidget->setLayout(monLayout);
}


void fenAutomate::slotBtPlayStop(){
    if(playPause){
        BTplay->setIcon(QIcon(":/img/pause.png"));
        myTimer->start(mySlider->value());
        playPause = false;
    }else{
        myTimer->stop();
        BTplay->setIcon(QIcon(":/img/play-button.png"));
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
