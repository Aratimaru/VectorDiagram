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

  auto pen = new QPen{QBrush{Qt::BrushStyle::Dense1Pattern}, 1};
  {
    auto myScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(myScene);
  }

  auto scene = ui->graphicsView->scene();

  auto l = new QLineF(0, 50, 50, 200);
  scene->addLine(*l, *pen);
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

  _model->reserve(allPhases.size());

  for (int i = 0; i < allPhases.size(); i++) {
    converter(allPhases.at(i), i % ROWS, i / COLUMNS);
  }
}
