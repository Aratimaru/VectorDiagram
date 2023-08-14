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

  setupParametrFieldsNames();

  ui->PlotDiagram->xAxis->setLabel("X");
  ui->PlotDiagram->yAxis->setLabel("Y");
  ui->PlotDiagram->xAxis->setRange(-300, 300);
  ui->PlotDiagram->yAxis->setRange(-300, 300);
  ui->PlotDiagram->setInteractions(
      {QCP::iRangeDrag, QCP::iRangeZoom, QCP::iSelectPlottables});
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::resizeEvent(QResizeEvent *e) {
  QMainWindow::resizeEvent(e);
  int maxRangeAxis = std::max(ui->PlotDiagram->xAxis->range().size(),
                              ui->PlotDiagram->yAxis->range().size());
  if (maxRangeAxis == ui->PlotDiagram->xAxis->range().size()) {
    this->ui->PlotDiagram->yAxis->setScaleRatio(ui->PlotDiagram->xAxis, 1.0);
  } else {
    this->ui->PlotDiagram->xAxis->setScaleRatio(ui->PlotDiagram->yAxis, 1.0);
  }
}

ComplexNumberAdapter MainWindow::constructPoint(
    const std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>
        &key) {
  std::tuple realPart =
      std::make_tuple(std::get<0>(key), std::get<1>(key), std::get<2>(key),
                      ComplexNumberPart::Re);
  std::tuple imagPart =
      std::make_tuple(std::get<0>(key), std::get<1>(key), std::get<2>(key),
                      ComplexNumberPart::Im);
  return ComplexNumberAdapter{parameterFields[realPart]->text().toFloat(),
                              parameterFields[imagPart]->text().toFloat()};
}

QMap<std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>,
     ComplexNumberAdapter>
MainWindow::getParametersFromUI() {
  QMap<std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>,
       ComplexNumberAdapter>
      result;
  // Ia
  result[{PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT,
          ComplexNumberForm::GENERAL}] =
      constructPoint({PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT,
                      ComplexNumberForm::GENERAL});
  result[{PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT,
          ComplexNumberForm::EXPONENTIAL}] =
      constructPoint({PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT,
                      ComplexNumberForm::EXPONENTIAL});
  // Ib
  //  result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //          ComplexNumberForm::GENERAL}] =
  //      constructPoint({PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //                      ComplexNumberForm::GENERAL});
  //  result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //          ComplexNumberForm::EXPONENTIAL}] =
  //      constructPoint({PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //                      ComplexNumberForm::EXPONENTIAL});
  // Ic
  //  result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //          ComplexNumberForm::GENERAL}] =
  //      constructPoint({PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //                      ComplexNumberForm::GENERAL});
  //  result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //          ComplexNumberForm::EXPONENTIAL}] =
  //      constructPoint({PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //                      ComplexNumberForm::EXPONENTIAL});
  // Ua
  result[{PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE,
          ComplexNumberForm::GENERAL}] =
      constructPoint({PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE,
                      ComplexNumberForm::GENERAL});
  result[{PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE,
          ComplexNumberForm::EXPONENTIAL}] =
      constructPoint({PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE,
                      ComplexNumberForm::EXPONENTIAL});
  // Ub
  //  result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE,
  //          ComplexNumberForm::GENERAL}] =
  //      constructPoint({PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE,
  //                      ComplexNumberForm::GENERAL});
  //  result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE,
  //          ComplexNumberForm::EXPONENTIAL}] =
  //      constructPoint({PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE,
  //                      ComplexNumberForm::EXPONENTIAL});
  //   Uc
  //  result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE,
  //          ComplexNumberForm::GENERAL}] =
  //      constructPoint({PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE,
  //                      ComplexNumberForm::GENERAL});
  //  result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE,
  //          ComplexNumberForm::EXPONENTIAL}] =
  //      constructPoint({PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE,
  //                      ComplexNumberForm::EXPONENTIAL});
  return result;
}

QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector>
MainWindow::constructVectorsFromParameters(
    const QMap<std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>,
               ComplexNumberAdapter> &parameters) {
  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector> result;

  result[{PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT}] = PhaseVector(
      parameters[{PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT,
                  ComplexNumberForm::GENERAL}],
      PhaseVectorType::CURRENT, PhaseVectorPhase::PHASE_A, "Ia");
  //  result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT}] =
  //  PhaseVector(
  //      parameters[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //                  ComplexNumberForm::GENERAL}],
  //      PhaseVectorType::CURRENT, PhaseVectorPhase::PHASE_B, "Ib");
  //  result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT}] =
  //  PhaseVector(
  //      parameters[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //                  ComplexNumberForm::GENERAL}],
  //      PhaseVectorType::CURRENT, PhaseVectorPhase::PHASE_C, "Ic");

  result[{PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE}] = PhaseVector(
      parameters[{PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE,
                  ComplexNumberForm::GENERAL}],
      PhaseVectorType::VOLTAGE, PhaseVectorPhase::PHASE_A, "Ua");
  //  result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE}] =
  //  PhaseVector(
  //      parameters[{PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE,
  //                  ComplexNumberForm::GENERAL}],
  //      PhaseVectorType::VOLTAGE, PhaseVectorPhase::PHASE_B, "Ub");
  //  result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE}] =
  //  PhaseVector(
  //      parameters[{PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE,
  //                  ComplexNumberForm::GENERAL}],
  //      PhaseVectorType::VOLTAGE, PhaseVectorPhase::PHASE_C, "Uc");

  return result;
}

void MainWindow::setupParametrFieldsNames() {

  parameterFields[{PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT,
                   ComplexNumberForm::GENERAL, ComplexNumberPart::Re}] =
      ui->I1CurrentGenReal;
  parameterFields[{PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT,
                   ComplexNumberForm::GENERAL, ComplexNumberPart::Im}] =
      ui->I1CurrentGenImag;
  //  parameterFields[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, true}] =
  //                   ui->I2CurrentGenReal;
  //  parameterFields[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, false}] =
  //                   ui->I2CurrentGenImag;
  //  parameterFields[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, true}] =
  //                   ui->I3CurrentGenReal;
  //  parameterFields[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, false}] =
  //                   ui->I3CurrentGenImag;

  parameterFields[{PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT,
                   ComplexNumberForm::EXPONENTIAL, ComplexNumberPart::Re}] =
      ui->I1CurrentExpReal;
  parameterFields[{PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT,
                   ComplexNumberForm::EXPONENTIAL, ComplexNumberPart::Im}] =
      ui->I1CurrentExpImag;
  //  parameterFields[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, true}] =
  //                   ui->I2CurrentGenReal;
  //  parameterFields[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, false}] =
  //                   ui->I2CurrentGenImag;
  //  parameterFields[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, true}] =
  //                   ui->I3CurrentGenReal;
  //  parameterFields[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, false}] =
  //                   ui->I3CurrentGenImag;

  parameterFields[{PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE,
                   ComplexNumberForm::GENERAL, ComplexNumberPart::Re}] =
      ui->V1VoltageGenReal;
  parameterFields[{PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE,
                   ComplexNumberForm::GENERAL, ComplexNumberPart::Im}] =
      ui->V1VoltageGenImag;
  //  parameterFields[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, true}] =
  //                   ui->I2CurrentGenReal;
  //  parameterFields[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, false}] =
  //                   ui->I2CurrentGenImag;
  //  parameterFields[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, true}] =
  //                   ui->I3CurrentGenReal;
  //  parameterFields[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, false}] =
  //                   ui->I3CurrentGenImag;

  parameterFields[{PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE,
                   ComplexNumberForm::EXPONENTIAL, ComplexNumberPart::Re}] =
      ui->V1VoltageExpReal;
  parameterFields[{PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE,
                   ComplexNumberForm::EXPONENTIAL, ComplexNumberPart::Im}] =
      ui->V1VoltageExpImag;
  //  parameterFields[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, true}] =
  //                   ui->I2CurrentGenReal;
  //  parameterFields[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, false}] =
  //                   ui->I2CurrentGenImag;
  //  parameterFields[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, true}] =
  //                   ui->I3CurrentGenReal;
  //  parameterFields[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //                   ComplexNumberForm::GENERAL, false}] =
  //                   ui->I3CurrentGenImag;
}

void MainWindow::on_ConfirmButton_clicked() // choose 1 form and convert to
                                            // another automatically, display
                                            // found info
{
  currentParameters = getParametersFromUI();

  // difference = findDifference(previousParameters, currentParameters);
  // applyDifference(currentParameters);

  previousParameters = currentParameters;

  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector> phaseVectors =
      constructVectorsFromParameters(currentParameters);

  _model->fillModel(phaseVectors);
  ui->PlotDiagram->drawDataFromModel(_model.get());
}

void MainWindow::on_ClearButton_clicked() { ui->PlotDiagram->clear(); }
