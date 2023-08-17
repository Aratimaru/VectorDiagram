#include "mainwindow.h"

#include "calculations/phasevectorcalculator.h"
#include "data_structure/phasevector.h"
#include "model/vectordiagrammodel.h"
#include "ui_mainwindow.h"

#include <QBrush>
#include <QPen>
#include <format>

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
  ComplexNumberAdapter result{parameterFields[realPart]->text().toFloat(),
                              parameterFields[imagPart]->text().toFloat()};
  result.setForm(std::get<2>(key));
  return result;
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
  //  // Ib
  //    result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //            ComplexNumberForm::GENERAL}] =
  //        constructPoint({PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //                        ComplexNumberForm::GENERAL});
  //    result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //            ComplexNumberForm::EXPONENTIAL}] =
  //        constructPoint({PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT,
  //                        ComplexNumberForm::EXPONENTIAL});
  //  // Ic
  //    result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //            ComplexNumberForm::GENERAL}] =
  //        constructPoint({PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //                        ComplexNumberForm::GENERAL});
  //    result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //            ComplexNumberForm::EXPONENTIAL}] =
  //        constructPoint({PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT,
  //                        ComplexNumberForm::EXPONENTIAL});
  // Ua
  result[{PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE,
          ComplexNumberForm::GENERAL}] =
      constructPoint({PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE,
                      ComplexNumberForm::GENERAL});
  result[{PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE,
          ComplexNumberForm::EXPONENTIAL}] =
      constructPoint({PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE,
                      ComplexNumberForm::EXPONENTIAL});
  //  // Ub
  //    result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE,
  //            ComplexNumberForm::GENERAL}] =
  //        constructPoint({PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE,
  //                        ComplexNumberForm::GENERAL});
  //    result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE,
  //            ComplexNumberForm::EXPONENTIAL}] =
  //        constructPoint({PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE,
  //                        ComplexNumberForm::EXPONENTIAL});
  //  //   Uc
  //    result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE,
  //            ComplexNumberForm::GENERAL}] =
  //        constructPoint({PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE,
  //                        ComplexNumberForm::GENERAL});
  //    result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE,
  //            ComplexNumberForm::EXPONENTIAL}] =
  //        constructPoint({PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE,
  //                        ComplexNumberForm::EXPONENTIAL});
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

QMap<std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>,
     ComplexNumberAdapter>
MainWindow::determineChangedFields() {
  QMap<std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>,
       ComplexNumberAdapter>
      changedFields;

  for (const auto &e : currentParameters.keys()) {
    if (currentParameters[e] != previousParameters[e]) {
      changedFields[e] = currentParameters[e];

      // debug
      qDebug() << "changedFields: \ncurrent" << changedFields[e].real()
               << changedFields[e].imag()
               << "\nprevious:" << previousParameters[e].real()
               << previousParameters[e].imag() << '\n';
      qDebug() << "PhaseVectorPhase " << (int)std::get<0>(e)
               << "PhaseVectorType " << (int)std::get<1>(e)
               << "ComplexNumberForm " << (int)std::get<2>(e) << '\n';
    }
  }
  qDebug() << "---------------------------------------------------" << '\n';

  return changedFields;
}

void MainWindow::calculateOtherFormFieldBasedOnChangedInput(
    const QMap<std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>,
               ComplexNumberAdapter> &difference) {
  for (const auto &e : difference.keys()) {

    std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm,
               ComplexNumberPart>
        genRealKey =
            std::make_tuple(get<0>(e), get<1>(e), ComplexNumberForm::GENERAL,
                            ComplexNumberPart::Re);
    std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm,
               ComplexNumberPart>
        genImagKey =
            std::make_tuple(get<0>(e), get<1>(e), ComplexNumberForm::GENERAL,
                            ComplexNumberPart::Im);
    std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm,
               ComplexNumberPart>
        expRealKey = std::make_tuple(get<0>(e), get<1>(e),
                                     ComplexNumberForm::EXPONENTIAL,
                                     ComplexNumberPart::Re);
    std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm,
               ComplexNumberPart>
        expImagKey = std::make_tuple(get<0>(e), get<1>(e),
                                     ComplexNumberForm::EXPONENTIAL,
                                     ComplexNumberPart::Im);

    // lets calculate both forms
    float genReal = currentParameters[e].toGeneralForm().real();
    float genImag = currentParameters[e].toGeneralForm().imag();

    float expReal = currentParameters[e].toExponentialForm().real();
    float expImag = currentParameters[e].toExponentialForm().imag();

    genReal = std::round(std::round(genReal * 1000.f) / 10.f) / 100.f;
    genImag = std::round(std::round(genImag * 1000.f) / 10.f) / 100.f;
    expReal = std::round(std::round(expReal * 1000.f) / 10.f) / 100.f;
    expImag = std::round(std::round(expImag * 1000.f) / 10.f) / 100.f;

    std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>
        genParamKey =
            std::make_tuple(get<0>(e), get<1>(e), ComplexNumberForm::GENERAL);
    std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>
        expParamKey = std::make_tuple(get<0>(e), get<1>(e),
                                      ComplexNumberForm::EXPONENTIAL);

    // need to update current info
    qDebug() << "currentParameters[genParamKey]"
             << currentParameters[genParamKey].real()
             << currentParameters[genParamKey].imag() << '\n';
    qDebug() << "currentParameters[expParamKey]"
             << currentParameters[expParamKey].real()
             << currentParameters[expParamKey].imag() << '\n';

    currentParameters[genParamKey] = ComplexNumberAdapter{genReal, genImag};
    currentParameters[expParamKey] = ComplexNumberAdapter{expReal, expImag};

    qDebug() << "After update" << '\n';
    qDebug() << "currentParameters[genParamKey]"
             << currentParameters[genParamKey].real()
             << currentParameters[genParamKey].imag() << '\n';
    qDebug() << "currentParameters[expParamKey]"
             << currentParameters[expParamKey].real()
             << currentParameters[expParamKey].imag() << '\n';

    // update QLineEdit
    QString genTextReal =
        QString::fromStdString(std::format("{:.2f}", genReal));
    QString genTextImag =
        QString::fromStdString(std::format("{:.2f}", genImag));
    QString expTextReal =
        QString::fromStdString(std::format("{:.2f}", expReal));
    QString expTextImag =
        QString::fromStdString(std::format("{:.2f}", expImag));

    parameterFields[genRealKey]->setText(genTextReal);
    parameterFields[genImagKey]->setText(genTextImag);
    parameterFields[expRealKey]->setText(expTextReal);
    parameterFields[expImagKey]->setText(expTextImag);
  }
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

void MainWindow::on_ConfirmButton_clicked() {
  currentParameters = getParametersFromUI();

  QMap<std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>,
       ComplexNumberAdapter>
      difference = determineChangedFields();

  // choose 1 form and convert to
  // another automatically, display
  // found info
  calculateOtherFormFieldBasedOnChangedInput(difference);
  previousParameters = currentParameters;

  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector> phaseVectors =
      constructVectorsFromParameters(currentParameters);

  _model->fillModel(phaseVectors);
  ui->PlotDiagram->drawDataFromModel(_model.get());
}

void MainWindow::on_ClearButton_clicked() { ui->PlotDiagram->clear(); }
