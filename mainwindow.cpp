#include "mainwindow.h"

#include "complexnumberadapter.h"
#include "phaseparametersstorage.h"
#include "ui_mainwindow.h"
#include "vectordiagrammodel.h"
#include "vectorparameterscalculator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      _model(std::make_shared<VectorDiagramModel>()) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_ConfirmButton_clicked() // choose 1 from and convert to
                                            // another automatically
{
  ComplexNumberAdapter complexCurrent{ui->I1CurrentExpReal->text().toFloat(),
                                      ui->I1CurrentExpImag->text().toFloat()};
  ComplexNumberAdapter complexrVoltage{ui->V1VoltageExpReal->text().toFloat(),
                                       ui->V1VoltageExpImag->text().toFloat()};

  Parameter currentParameter;
  currentParameter.parameter = complexCurrent;
  Parameter voltageParameter;
  voltageParameter.parameter = complexrVoltage;

  PhaseParametersStorage phaseParametersStorage;
  phaseParametersStorage.setCurrent(currentParameter);
  phaseParametersStorage.setVoltage(voltageParameter);

  VectorParametersCalculator calculator;
  std::vector<PhaseVector> phaseVectorsA{
      calculator.calculate(phaseParametersStorage)};

  fillModel(phaseVectorsA);

  const auto idx = _model->index(0, 0);
  std::cout << _model->data(idx).value<PhaseVector>();

  //  std::cout << phaseVectors.at(0) << std::endl;
  //  std::cout << phaseVectors.at(1) << std::endl;
}

void MainWindow::fillModel(const std::vector<PhaseVector> &allPhases) {
  auto converter = [this](const PhaseVector &item, int row, int column) {
    const Line coord = item.getCoordinates();

    // Create index

    //! \todo get row and column
    const auto idx = _model->index(row, column);
    const auto data = QVariant::fromValue<Line>(coord);

    _model->setData(idx, data);
  };

  for (int i = 0; i < allPhases.size(); i++) {
    converter(allPhases.at(i), i % ROWS, i / COLUMNS);
  }
}
