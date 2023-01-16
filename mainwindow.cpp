#include "mainwindow.h"
#include "complexnumberadapter.h"
#include "phaseparametersstorage.h"
#include "ui_mainwindow.h"
#include "vectorparameterscalculator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ConfirmButton_clicked()     //choose 1 from and convert to another automatically
{
    ComplexNumberAdapter complexCurrent {ui->I1CurrentExpReal->text().toFloat(), ui->I1CurrentExpImag->text().toFloat()};
    ComplexNumberAdapter complexrVoltage {ui->V1VoltageExpReal->text().toFloat(), ui->V1VoltageExpImag->text().toFloat()};

    Parameter currentParameter; currentParameter.parameter = complexCurrent;
    Parameter voltageParameter; voltageParameter.parameter = complexrVoltage;

    PhaseParametersStorage phaseParametersStorage;
    phaseParametersStorage.setCurrent(currentParameter);
    phaseParametersStorage.setVoltage(voltageParameter);

    VectorParametersCalculator calculator;
    std::vector <PhaseVector> phaseVectors;
    phaseVectors = calculator.calculate(phaseParametersStorage);

    std::cout << phaseVectors.at(0) << std::endl;
    std::cout << phaseVectors.at(1) << std::endl;
}

