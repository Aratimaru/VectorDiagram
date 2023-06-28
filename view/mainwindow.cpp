#include "mainwindow.h"

#include "calculations/phasevectorcalculator.h"
#include "data_structure/phasevector.h"
#include "model/vectordiagrammodel.h"
#include "ui_mainwindow.h"

#include <QBrush>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      _model(std::make_shared<VectorDiagramModel>()) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_ConfirmButton_clicked() // choose 1 from and convert to
                                            // another automatically
{
  ComplexNumberAdapter complexCurrent;
  ComplexNumberAdapter complexrVoltage;

  if (!ui->I1CurrentGenReal->text().isNull() &&
      !ui->I1CurrentGenImag->text().isNull()) {
    complexCurrent = {ui->I1CurrentGenReal->text().toFloat(),
                      ui->I1CurrentGenImag->text().toFloat()};
    complexrVoltage = {ui->V1VoltageGenReal->text().toFloat(),
                       ui->V1VoltageGenImag->text().toFloat()};
  } else {

    complexCurrent = {ui->I1CurrentExpReal->text().toFloat(),
                      ui->I1CurrentExpImag->text().toFloat()};
    complexrVoltage = {ui->V1VoltageExpReal->text().toFloat(),
                       ui->V1VoltageExpImag->text().toFloat()};
  }

  complexCurrent.setForm(ComplexNumberForm::EXPONENTIAL);
  complexrVoltage.setForm(ComplexNumberForm::EXPONENTIAL);

  PhaseVector currentVector(complexCurrent, PhaseVectorType::CURRENT,
                            PhaseVectorPhase::PHASE_A);
  PhaseVector voltageVector(complexrVoltage, PhaseVectorType::VOLTAGE,
                            PhaseVectorPhase::PHASE_A);
  PhaseVector resistenceVector = *PhaseVectorCalculator::findResistenceVector(
      currentVector, voltageVector);

  std::vector<PhaseVector> phaseA;
  phaseA.push_back(currentVector);
  phaseA.push_back(voltageVector);

  _model->fillModel(phaseA);

  ui->graphicsView->drawLines(_model.get());
}

void MainWindow::on_ClearButton_clicked() {
  ui->graphicsView->scene()->clear();
}
