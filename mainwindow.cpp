#include "mainwindow.h"

#include "arrow.h"
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

  QGraphicsScene *scene = new QGraphicsScene(this);
  QBrush *brush = new QBrush(QColor(211, 211, 211, 100));
  QTransform myMatrix;
  brush->setStyle(Qt::CrossPattern);
  scene->setBackgroundBrush(*brush);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->scale(1, -1);
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
  currentParameter.value = complexCurrent;
  Parameter voltageParameter;
  voltageParameter.value = complexrVoltage;

  PhaseParametersStorage phaseParametersStorage;
  phaseParametersStorage.setCurrent(currentParameter);
  phaseParametersStorage.setVoltage(voltageParameter);

  VectorParametersCalculator calculator;
  std::vector<PhaseVector> phaseVectorsA{
      calculator.calculate(phaseParametersStorage)};
  //  std::vector<PhaseVector> phaseVectorsA;
  //  PhaseVector currentVector{};
  //  currentVector.setCoodinates({0, 0}, {90, 139});
  //  PhaseVector voltageVector{};
  //  voltageVector.setCoodinates({0, 0}, {-80, 69});

  //  phaseVectorsA.push_back(currentVector);
  //  phaseVectorsA.push_back(voltageVector);

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
  QPen *pen = new QPen{Qt::black};
  pen->setWidth(3);
  QGraphicsScene *scene = ui->graphicsView->scene();

  while (_model->hasNext()) {
    QLineF nextLine{_model->getNextVector()};
    Arrow *arrow = new Arrow{nextLine, 60, 20};
    if (arrow->lenght() == 0) {
      continue;
    }
    arrow->setPen(*pen);
    scene->addItem(arrow);
    *pen = arrow->pen();

    //    scene->addLine(nextLine, *pen);
  }
  //! \todo add scaling
}
