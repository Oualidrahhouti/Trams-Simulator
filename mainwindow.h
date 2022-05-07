#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QMessageBox>
#include<QDoubleSpinBox>
#include<QFileDialog>
#include<QFont>
#include<QDesktopServices>
#include<QUrl>
#include<QFile>
#include<QDebug>
#include"simulationwindow.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void LoadFile();
    void OpenFileForEdit();
    void StartSimulation();
    void CreateView();
    void ConnectSlotsToSignals();
private:
    QPushButton* loadBtn;
    QLineEdit* fileDestinationTxt;
    QDoubleSpinBox* durationValueDSB;
    QPushButton* editFileBtn;
    QPushButton* startBtn;
    simulationwindow* simulationWindow;
    Ligne* line;

};
#endif // MAINWINDOW_H
