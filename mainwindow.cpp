#include "mainwindow.h"

#include "complexnumberadapter.h"
#include "phaseparametersstorage.h"
#include "ui_mainwindow.h"
#include "vectordiagrammodel.h"
#include "vectorparameterscalculator.h"

#include <QBrush>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      _model(std::make_shared<VectorDiagramModel>()) {
  ui->setupUi(this);

  ui->graphicsView->setScene(new QGraphicsScene(this));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_ConfirmButton_clicked() // choose 1 from and convert to
                                            // another automatically
{
  //  ComplexNumberAdapter
  //  complexCurrent{ui->I1CurrentExpReal->text().toFloat(),
  //                                      ui->I1CurrentExpImag->text().toFloat()};
  //  ComplexNumberAdapter
  //  complexrVoltage{ui->V1VoltageExpReal->text().toFloat(),
  //                                       ui->V1VoltageExpImag->text().toFloat()};

  //  Parameter currentParameter;
  //  currentParameter.parameter = complexCurrent;
  //  Parameter voltageParameter;
  //  voltageParameter.parameter = complexrVoltage;

  //  PhaseParametersStorage phaseParametersStorage;
  //  phaseParametersStorage.setCurrent(currentParameter);
  //  phaseParametersStorage.setVoltage(voltageParameter);

  //  VectorParametersCalculator calculator;
  //  std::vector<PhaseVector> phaseVectorsA{
  //      calculator.calculate(phaseParametersStorage)};
  std::vector<PhaseVector> phaseVectorsA;
  PhaseVector currentVector{};
  currentVector.setCoodinates({0, 0}, {90, 139});
  PhaseVector voltageVector{};
  voltageVector.setCoodinates({0, 0}, {-80, 69});

  phaseVectorsA.push_back(currentVector);
  phaseVectorsA.push_back(voltageVector);

  fillModel(phaseVectorsA);
  drawLines();
}

void MainWindow::fillModel(const std::vector<PhaseVector> &allPhases) {
  auto converter = [this](const PhaseVector &item, int row, int column) {
    const QLineF coord = item.getCoordinates();

    // Create index

    //! \todo get row and column
    const auto idx = _model->index(row, column);
    const auto data = QVariant::fromValue<QLineF>(coord);

    _model->setData(idx, data);
  };

  _model->reserve(allPhases.size());

  for (int i = 0; i < allPhases.size(); i++) {
    converter(allPhases.at(i), i % ROWS, i / COLUMNS);
  }
}

void MainWindow::drawLines() {
  auto pen =
      new QPen{QBrush{Qt::BrushStyle::SolidPattern}, 3}; // -> field /shared_ptr
  QGraphicsScene *scene = ui->graphicsView->scene();

  while (_model->hasNext()) {
    const QLineF nextLine{_model->getNextVector()};
    if (!nextLine.p1().isNull() || !nextLine.p2().isNull())
      scene->addLine({nextLine.p1(), nextLine.p2()}, *pen);
  }
}
