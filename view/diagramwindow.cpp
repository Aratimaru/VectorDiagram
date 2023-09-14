#include "diagramwindow.h"
#include "ui_diagramwindow.h"

DiagramWindow::DiagramWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::DiagramWindow),
      _model(std::make_shared<VectorDiagramModel>()) {
  ui->setupUi(this);

  connect(ui->ClearBtn, &QPushButton::clicked, this,
          &DiagramWindow::handleClearBtnClicked);
  connect(ui->DrawBtn, &QPushButton::clicked, this,
          &DiagramWindow::handleDrawBtnClicked);
  connect(ui->V1StartGenXEdit, &QLineEdit::textChanged, this,
          &DiagramWindow::handleV1StartGenXEditTextChanged);
  connect(ui->V1StartGenYEdit, &QLineEdit::textChanged, this,
          &DiagramWindow::handleV1StartGenYEditTextChanged);
  connect(ui->V1EndGenXEdit, &QLineEdit::textChanged, this,
          &DiagramWindow::handleV1EndGenXEditTextChanged);
  connect(ui->V1EndGenYEdit, &QLineEdit::textChanged, this,
          &DiagramWindow::handleV1EndGenYEditTextChanged);
  connect(ui->V1ImagStartAEdit, &QLineEdit::textChanged, this,
          &DiagramWindow::handleV1ImagStartAEditTextChanged);
  connect(ui->V1ImagEndAEdit, &QLineEdit::textChanged, this,
          &DiagramWindow::handleV1ImagEndAEditTextChanged);
  connect(ui->V1ImagStartUEdit, &QLineEdit::textChanged, this,
          &DiagramWindow::handleV1ImagStartUEditTextChanged);
  connect(ui->V1ImagEndUEdit, &QLineEdit::textChanged, this,
          &DiagramWindow::handleV1ImagEndUEditTextChanged);
}

DiagramWindow::~DiagramWindow() { delete ui; }

PhaseVectorPhase DiagramWindow::getCurrentPhase() {
  QString phase = ui->ChoosePhaseComboBox->currentText();
  PhaseVectorPhase result;

  if (phase == "A") {
    result = PhaseVectorPhase::PHASE_A;
  } else if (phase == "B") {
    result = PhaseVectorPhase::PHASE_B;
  } else if (phase == "C") {
    result = PhaseVectorPhase::PHASE_C;
  } else {
    qDebug() << __FUNCTION__ << "Check your phase!\n";
    result = PhaseVectorPhase::NOT_DEFINED;
  }

  return result;
}

QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector>
DiagramWindow::getParametersFromUi() {
  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector> result;

  PhaseVectorPhase phase = getCurrentPhase();
  float I1StartGenXEdit = ui->I1StartGenXEdit->text().toFloat();
  float I1StartGenYEdit = ui->I1StartGenYEdit->text().toFloat();
  float I1EndGenXEdit = ui->I1EndGenXEdit->text().toFloat();
  float I1EndGenYEdit = ui->I1EndGenYEdit->text().toFloat();

  ComplexNumberAdapter currentStart = {I1StartGenXEdit, I1StartGenYEdit,
                                       ComplexNumberForm::GENERAL};
  ComplexNumberAdapter currentEnd = {I1EndGenXEdit, I1EndGenYEdit,
                                     ComplexNumberForm::GENERAL};

  result[{phase, PhaseVectorType::CURRENT}] =
      PhaseVector{currentStart, currentEnd, PhaseVectorType::CURRENT, phase};

  float V1StartGenXEdit = ui->V1StartGenXEdit->text().toFloat();
  float V1StartGenYEdit = ui->V1StartGenYEdit->text().toFloat();
  float V1EndGenXEdit = ui->V1EndGenXEdit->text().toFloat();
  float V1EndGenYEdit = ui->V1EndGenYEdit->text().toFloat();

  ComplexNumberAdapter voltageStart = {V1StartGenXEdit, V1StartGenYEdit,
                                       ComplexNumberForm::GENERAL};
  ComplexNumberAdapter voltageEnd = {V1EndGenXEdit, V1EndGenYEdit,
                                     ComplexNumberForm::GENERAL};

  result[{phase, PhaseVectorType::VOLTAGE}] =
      PhaseVector{voltageStart, voltageEnd, PhaseVectorType::VOLTAGE, phase};
  return result;
}

void DiagramWindow::handleClearBtnClicked() { ui->PlotDiagram->clear(); }

void DiagramWindow::handleDrawBtnClicked() {
  // get parameters from UI
  // create PhaseVectors
  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector> phaseVectors =
      getParametersFromUi();

  // update model and draw the vectors
  _model->fillModel(phaseVectors);
  ui->PlotDiagram->clear();
  ui->PlotDiagram->drawDataFromModel(_model.get());
}

void DiagramWindow::handleV1StartGenXEditTextChanged(const QString &arg1) {}

void DiagramWindow::handleV1StartGenYEditTextChanged(const QString &arg1) {}

void DiagramWindow::handleV1EndGenXEditTextChanged(const QString &arg1) {}

void DiagramWindow::handleV1EndGenYEditTextChanged(const QString &arg1) {}

void DiagramWindow::handleV1ImagStartAEditTextChanged(const QString &arg1) {}

void DiagramWindow::handleV1ImagEndAEditTextChanged(const QString &arg1) {}

void DiagramWindow::handleV1ImagStartUEditTextChanged(const QString &arg1) {}

void DiagramWindow::handleV1ImagEndUEditTextChanged(const QString &arg1) {}
