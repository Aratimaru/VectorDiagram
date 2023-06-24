#include "mainwindow.h"

#include "calculations/vectorparameterscalculator.h"
#include "data_structure/phaseparametersstorage.h"
#include "data_structure/phasevector.h"
#include "model/vectordiagrammodel.h"
#include "ui_mainwindow.h"
#include "view/arrow.h"

#include <QBrush>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      _modelUpdater(std::make_shared<ModelUpdater>()),
      _viewUpdater(std::make_shared<ViewUpdater>()) {
  ui->setupUi(this);
  _viewUpdater->setView(ui->graphicsView);
  _viewUpdater->setModel(_modelUpdater.get());
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

  //  Parameter currentParameter;
  //  currentParameter.value = complexCurrent;
  //  Parameter voltageParameter;
  //  voltageParameter.value = complexrVoltage;

  //  PhaseParametersStorage phaseParametersStorage;
  //  phaseParametersStorage.setCurrent(currentParameter);
  //  phaseParametersStorage.setVoltage(voltageParameter);

  //  VectorParametersCalculator calculator;
  //  std::vector<PhaseVector> phaseVectorsA{
  //      calculator.calculate(phaseParametersStorage)};

  //-------------------------------------------------------------------
  //  std::vector<PhaseVector> phaseVectorsA;
  //  PhaseVector currentVector{};
  //  currentVector.setCoodinates(QPointF{0, 0}, QPointF{90, 139});
  //  PhaseVector voltageVector{};
  //  voltageVector.setCoodinates(QPointF{0, 0}, QPointF{-80, 69});

  //  phaseVectorsA.push_back(currentVector);
  //  phaseVectorsA.push_back(voltageVector);

  //-------------------------------------------------------------------

  PhaseVector currentVector(complexCurrent, PhaseVectorType::CURRENT,
                            PhaseVectorPhase::PHASE_A);
  PhaseVector voltageVector(complexrVoltage, PhaseVectorType::VOLTAGE,
                            PhaseVectorPhase::PHASE_A);
  std::vector<PhaseVector> phaseA;
  phaseA.push_back(currentVector);
  phaseA.push_back(voltageVector);

  _modelUpdater->fillModel(phaseA);
  _viewUpdater->drawLines();
}
