#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),line(nullptr),simulationWindow(nullptr)
{
   CreateView();
   ConnectSlotsToSignals();
}

MainWindow::~MainWindow()
{
}

void MainWindow::LoadFile()
{
    QString filePath=QFileDialog::getOpenFileName(this,"Veuillez Selectionner le fichier a charger"," ","JSON(*.json)");
    if(!filePath.isEmpty())
    {
        //Show File destination in the text box
        fileDestinationTxt->setText(filePath);
        //retrieve data from the JSON file
        QFile file;
        QString dataAsString;
        file.setFileName(filePath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        dataAsString=file.readAll();
        file.close();
        //check if the required JSON format has been respected then instanciate simulation objects
        try {
            QJsonDocument JSONDocument=QJsonDocument::fromJson(dataAsString.toUtf8());
            QJsonObject dataAsJSON=JSONDocument.object();
            float distanceBetweenStops=dataAsJSON.value("distanceStops").toDouble();
            if(distanceBetweenStops==0 ||
               dataAsJSON.value("stops").toArray().empty() ||
               dataAsJSON.value("tramways").toArray().empty() )
                throw new std::exception();
            //delete unwanted instance of line and simulationWindow
            if(line!=nullptr)
            {
                if(simulationWindow!=nullptr)
                {
                    delete simulationWindow;
                    simulationWindow=nullptr;
                    line=nullptr;
                }else
                {
                    delete line;
                    line=nullptr;
                }
            }
            line=new Ligne(distanceBetweenStops);
            foreach(const QJsonValue &stop,dataAsJSON.value("stops").toArray())
            {
                QString name=stop.toObject().value("name").toString();
                float stopTime=stop.toObject().value("stopTime").toDouble()*1000;
                if(name=="" || stopTime==0)
                    throw new std::exception();
                arret* a=new arret(name,stopTime);
                line->AddStop(a);
            }
            foreach(const QJsonValue &tram,dataAsJSON.value("tramways").toArray())
            {
                float safeDistance=tram.toObject().value("safeDistance").toDouble();
                if(safeDistance==0)
                    throw new std::exception();
                tramway* t=new tramway(line->GetfirstStop(),safeDistance);
                line->AddTramway(t);
            }
        }  catch (std::exception *e ) {
            QMessageBox::critical(this,"Erreur JSON","le format JSON est invalide");
        }
    }
}
void MainWindow::OpenFileForEdit()
{
    //Check if a file is selected
    if(fileDestinationTxt->text()=="Aucun Fichier Selectionné")
    {
        QMessageBox::critical(this,"Erreur","Aucun Fichier Selectionné");
        return;
    }
    //Open The Wanted File
    QDesktopServices::openUrl(QUrl("file:///"+fileDestinationTxt->text(),QUrl::TolerantMode));

}
void MainWindow::StartSimulation()
{
    if(fileDestinationTxt->text()!="Aucun Fichier Selectionné")
    {
        fileDestinationTxt->setText("Aucun Fichier Selectionné");
        simulationWindow=new simulationwindow(line);
        simulationWindow->show();
        simulationWindow->simulationTimer->start(durationValueDSB->value()*1000);   
    }
    else
        QMessageBox::critical(this,"Erreur","Aucun Fichier Selectionné");
}

void MainWindow::CreateView()
{
    //creating layouts
    QVBoxLayout* mainLayout=new QVBoxLayout(this);
    QHBoxLayout* titleLayout=new QHBoxLayout();
    QHBoxLayout* loadingfileLayout=new QHBoxLayout();
    QHBoxLayout* simulationDetailsLayout= new QHBoxLayout();
    //creating unreferenced variables and instatiating referenced variables
    QLabel* titleLbl=new QLabel("Simulation du Tramway");
    QLabel* fileDestinationLbl=new QLabel("Chemin du fichier Selectionné :");
    fileDestinationTxt=new QLineEdit("Aucun Fichier Selectionné");
    loadBtn=new QPushButton("parcourir");
    editFileBtn=new QPushButton("modifier");
    QLabel* durationLabel=new QLabel("Durée en seconde :");
    durationValueDSB=new QDoubleSpinBox();
    startBtn=new QPushButton("Simuler");
    //link widgets to their layouts
    titleLayout->addWidget(titleLbl,1,Qt::AlignCenter);
    loadingfileLayout->addWidget(fileDestinationLbl);
    loadingfileLayout->addWidget(fileDestinationTxt,1,Qt::AlignLeft);
    loadingfileLayout->addWidget(loadBtn,0,Qt::AlignRight);
    loadingfileLayout->addWidget(editFileBtn,0,Qt::AlignRight);
    simulationDetailsLayout->addWidget(durationLabel);
    simulationDetailsLayout->addWidget(durationValueDSB,1,Qt::AlignLeft);
    simulationDetailsLayout->addWidget(startBtn,1,Qt::AlignRight);
    mainLayout->addLayout(titleLayout);
    mainLayout->addLayout(loadingfileLayout);
    mainLayout->addLayout(simulationDetailsLayout,1);
    //Increase Title Font Size
    QFont titleFont=titleLbl->font();
    titleFont.setPointSize(30);
    titleLbl->setFont(titleFont);
    //Assign mainLayout to the main window
    QWidget *placeholderWidget = new QWidget;
    placeholderWidget->setLayout(mainLayout);
    setCentralWidget(placeholderWidget);
    //Fixing Position and Size of Widgets And Fix The Size Of The Main Window
    durationValueDSB->resize(50,durationValueDSB->height());
    durationLabel->setContentsMargins(53,0,0,0);
    fileDestinationTxt->setDisabled(true);
    //Fix Simulation Time conditions
    durationValueDSB->setDecimals(0);
    durationValueDSB->setMinimum(1);
    durationValueDSB->setMaximum(60);
    startBtn->setFixedWidth(157);
    fileDestinationTxt->setFixedWidth(600);
    simulationWindow=nullptr;
    //Fix The Size Of The Main Window
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

void MainWindow::ConnectSlotsToSignals()
{
    //Connect Slots To Buttons
    connect(loadBtn,&QPushButton::clicked,this,&MainWindow::LoadFile);
    connect(editFileBtn,&QPushButton::clicked,this,&MainWindow::OpenFileForEdit);
    connect(startBtn,&QPushButton::clicked,this,&MainWindow::StartSimulation);
}
