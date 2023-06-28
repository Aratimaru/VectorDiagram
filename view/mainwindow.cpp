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
  ComplexNumberAdapter begin{0.f, 0.f};
  ComplexNumberAdapter complexCurrent{ui->I1CurrentExpReal->text().toFloat(),
                                      ui->I1CurrentExpImag->text().toFloat()};
  ComplexNumberAdapter complexrVoltage{ui->V1VoltageExpReal->text().toFloat(),
                                       ui->V1VoltageExpImag->text().toFloat()};
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
  phaseA.push_back(resistenceVector);

  _model->fillModel(phaseA);

  ui->graphicsView->drawLines(_model.get());
}
