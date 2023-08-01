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
  ui->PlotDiagram->xAxis->setLabel("X");
  ui->PlotDiagram->yAxis->setLabel("Y");
  ui->PlotDiagram->xAxis->setRange(-300, 300);
  ui->PlotDiagram->yAxis->setRange(-300, 300);
  ui->PlotDiagram->setInteractions(
      {QCP::iRangeDrag, QCP::iRangeZoom, QCP::iSelectPlottables});
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_ConfirmButton_clicked() // choose 1 form and convert to
                                            // another automatically
{
  ComplexNumberAdapter complexCurrent;
  ComplexNumberAdapter complexrVoltage;

  if (!ui->I1CurrentGenReal->text().isNull() &&
      !ui->I1CurrentGenImag->text().isNull()) {
    complexCurrent =
        ComplexNumberAdapter{ui->I1CurrentGenReal->text().toFloat(),
                             ui->I1CurrentGenImag->text().toFloat()};
    complexrVoltage =
        ComplexNumberAdapter{ui->V1VoltageGenReal->text().toFloat(),
                             ui->V1VoltageGenImag->text().toFloat()};
  } else {

    complexCurrent =
        ComplexNumberAdapter{ui->I1CurrentExpReal->text().toFloat(),
                             ui->I1CurrentExpImag->text().toFloat()};
    complexrVoltage =
        ComplexNumberAdapter{ui->V1VoltageExpReal->text().toFloat(),
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
  ui->PlotDiagram->drawDataFromModel(_model.get());
}

void MainWindow::on_ClearButton_clicked() { ui->PlotDiagram->clear(); }
