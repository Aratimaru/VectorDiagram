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

ComplexNumberAdapter MainWindow::chooseCorrectField(
    const QPair<PhaseVectorPhase, PhaseVectorType> &key) {
  //! \todo complene other phases

  ComplexNumberAdapter result;
  switch (key.first) {
  case PhaseVectorPhase::PHASE_A:
    if (key.second == PhaseVectorType::CURRENT) {
      if (!ui->I1CurrentGenReal->text().isEmpty()) {
        result = ComplexNumberAdapter{ui->I1CurrentGenReal->text().toFloat(),
                                      ui->I1CurrentGenImag->text().toFloat()};
        result.setForm(ComplexNumberForm::GENERAL);

        ui->I1CurrentExpReal->setText(QString::fromStdString(
            std::to_string(result.toExponentialForm().real())));
        ui->I1CurrentExpImag->setText(QString::fromStdString(
            std::to_string(result.toExponentialForm().imag())));
      } else if (!ui->I1CurrentExpReal->text().isEmpty()) {
        result = ComplexNumberAdapter{ui->I1CurrentExpReal->text().toFloat(),
                                      ui->I1CurrentExpImag->text().toFloat()};
        result.setForm(ComplexNumberForm::EXPONENTIAL);

        ui->I1CurrentGenReal->setText(QString::fromStdString(
            std::to_string(result.toGeneralForm().real())));
        ui->I1CurrentGenImag->setText(QString::fromStdString(
            std::to_string(result.toGeneralForm().imag())));
      }
    }
    if (key.second == PhaseVectorType::VOLTAGE) {
      if (!ui->V1VoltageGenReal->text().isEmpty()) {
        result = ComplexNumberAdapter{ui->V1VoltageGenReal->text().toFloat(),
                                      ui->V1VoltageGenImag->text().toFloat()};
        result.setForm(ComplexNumberForm::GENERAL);

        ui->V1VoltageExpReal->setText(QString::fromStdString(
            std::to_string(result.toExponentialForm().real())));
        ui->V1VoltageExpImag->setText(QString::fromStdString(
            std::to_string(result.toExponentialForm().imag())));
      } else if (!ui->V1VoltageExpReal->text().isEmpty()) {
        result = ComplexNumberAdapter{ui->V1VoltageExpReal->text().toFloat(),
                                      ui->V1VoltageExpImag->text().toFloat()};
        result.setForm(ComplexNumberForm::EXPONENTIAL);

        ui->V1VoltageGenReal->setText(QString::fromStdString(
            std::to_string(result.toGeneralForm().real())));
        ui->V1VoltageGenImag->setText(QString::fromStdString(
            std::to_string(result.toGeneralForm().imag())));
      }
    }

    break;
  case PhaseVectorPhase::PHASE_B:
    if (key.second == PhaseVectorType::CURRENT) {
      if (!ui->I1CurrentGenReal->text().isEmpty()) {
        result = ComplexNumberAdapter{ui->I2CurrentGenReal->text().toFloat(),
                                      ui->I2CurrentGenImag->text().toFloat()};
        result.setForm(ComplexNumberForm::GENERAL);
      } else {
        result = ComplexNumberAdapter{ui->I2CurrentExpReal->text().toFloat(),
                                      ui->I2CurrentExpImag->text().toFloat()};
        result.setForm(ComplexNumberForm::EXPONENTIAL);
      }
    }
    if (key.second == PhaseVectorType::VOLTAGE) {
      if (!ui->V1VoltageGenReal->text().isEmpty()) {
        result = ComplexNumberAdapter{ui->V2VoltageGenReal->text().toFloat(),
                                      ui->V2VoltageGenImag->text().toFloat()};
        result.setForm(ComplexNumberForm::GENERAL);
      } else {
        result = ComplexNumberAdapter{ui->V2VoltageExpReal->text().toFloat(),
                                      ui->V2VoltageExpImag->text().toFloat()};
        result.setForm(ComplexNumberForm::EXPONENTIAL);
      }
    }

    break;
  case PhaseVectorPhase::PHASE_C:
    if (key.second == PhaseVectorType::CURRENT) {
      if (!ui->I1CurrentGenReal->text().isEmpty()) {
        result = ComplexNumberAdapter{ui->I3CurrentGenReal->text().toFloat(),
                                      ui->I3CurrentGenImag->text().toFloat()};
        result.setForm(ComplexNumberForm::GENERAL);
      } else {
        result = ComplexNumberAdapter{ui->I3CurrentExpReal->text().toFloat(),
                                      ui->I3CurrentExpImag->text().toFloat()};
        result.setForm(ComplexNumberForm::EXPONENTIAL);
      }
    }
    if (key.second == PhaseVectorType::VOLTAGE) {
      if (!ui->V1VoltageGenReal->text().isEmpty()) {
        result = ComplexNumberAdapter{ui->V3VoltageGenReal->text().toFloat(),
                                      ui->V3VoltageGenImag->text().toFloat()};
        result.setForm(ComplexNumberForm::GENERAL);
      } else {
        result = ComplexNumberAdapter{ui->V3VoltageExpReal->text().toFloat(),
                                      ui->V3VoltageExpImag->text().toFloat()};
        result.setForm(ComplexNumberForm::EXPONENTIAL);
      }
    }

    break;
  default:
    break;
  }
  return result;
}

QMap<QPair<PhaseVectorPhase, PhaseVectorType>, ComplexNumberAdapter>
MainWindow::getParametersFromUI() {
  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, ComplexNumberAdapter> result;
  result[{PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT}] =
      chooseCorrectField({PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT});
  result[{PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE}] =
      chooseCorrectField({PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE});

  result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT}] =
      chooseCorrectField({PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT});
  result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE}] =
      chooseCorrectField({PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE});

  result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT}] =
      chooseCorrectField({PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT});
  result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE}] =
      chooseCorrectField({PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE});

  return result;
}

QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector>
MainWindow::constructVectorsFromParameters(
    const QMap<QPair<PhaseVectorPhase, PhaseVectorType>, ComplexNumberAdapter>
        &parameters) {
  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector> result;

  result[{PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT}] = PhaseVector(
      parameters[{PhaseVectorPhase::PHASE_A, PhaseVectorType::CURRENT}],
      PhaseVectorType::CURRENT, PhaseVectorPhase::PHASE_A, "Ia");
  result[{PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE}] = PhaseVector(
      parameters[{PhaseVectorPhase::PHASE_A, PhaseVectorType::VOLTAGE}],
      PhaseVectorType::VOLTAGE, PhaseVectorPhase::PHASE_A, "Va");

  result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT}] = PhaseVector(
      parameters[{PhaseVectorPhase::PHASE_B, PhaseVectorType::CURRENT}],
      PhaseVectorType::CURRENT, PhaseVectorPhase::PHASE_B, "Ib");
  result[{PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE}] = PhaseVector(
      parameters[{PhaseVectorPhase::PHASE_B, PhaseVectorType::VOLTAGE}],
      PhaseVectorType::VOLTAGE, PhaseVectorPhase::PHASE_B, "Vb");

  result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT}] = PhaseVector(
      parameters[{PhaseVectorPhase::PHASE_C, PhaseVectorType::CURRENT}],
      PhaseVectorType::CURRENT, PhaseVectorPhase::PHASE_C, "Ic");
  result[{PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE}] = PhaseVector(
      parameters[{PhaseVectorPhase::PHASE_C, PhaseVectorType::VOLTAGE}],
      PhaseVectorType::VOLTAGE, PhaseVectorPhase::PHASE_C, "Vc");

  return result;
}

void MainWindow::on_ConfirmButton_clicked() // choose 1 form and convert to
                                            // another automatically, display
                                            // found info
{
  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, ComplexNumberAdapter>
      parameters = getParametersFromUI();

  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector> phaseVectors =
      constructVectorsFromParameters(parameters);

  _model->fillModel(phaseVectors);
  ui->PlotDiagram->drawDataFromModel(_model.get());
}

void MainWindow::on_ClearButton_clicked() { ui->PlotDiagram->clear(); }
