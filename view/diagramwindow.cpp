#include "diagramwindow.h"
#include "dynamic_layouts/layoutgenerator.h"
#include "ui_diagramwindow.h"
#include "utils/utilsimage.h"

DiagramWindow::DiagramWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::DiagramWindow),
      _model(std::make_shared<VectorDiagramModel>()) {
  setupWindow(this);

  _mainDynamicLayout = new QVBoxLayout();

  // initial layouts
  DynamicLayoutsPerElement *initialLayouts = new DynamicLayoutsPerElement;
  QString currentPhase = ui->ChoosePhaseComboBox->currentText().toLower();
  initialLayouts->U =
      (LayoutGenerator::createParameterLayout("U", currentPhase));
  initialLayouts->I =
      (LayoutGenerator::createParameterLayout("I", currentPhase));
  initialLayouts->R = nullptr;
  initialLayouts->elementName = currentPhase;
  _dynamicLayoutsHolder.push_back(*initialLayouts);

  QFrame *topLine = LayoutGenerator::createLine("TopLine", QFrame::HLine);
  _mainDynamicLayout->addWidget(topLine);
  createDynamicLayouts();
  connectDynamicSlots();

  // keep initial layouts in the same window as dynamic
  _dynamicLayoutWidget = std::make_unique<QWidget>();
  _dynamicLayoutWidget->setLayout(_mainDynamicLayout);

  // Add scroll option to parameters' section
  _scrollArea = new QScrollArea();
  _scrollArea->setWidgetResizable(true);
  _scrollArea->setWidget(_dynamicLayoutWidget.get());
  _scrollArea->setMinimumSize(this->width() / 2, this->height() / 4);

  ui->DataLayout->insertWidget(2, _scrollArea);
}

DiagramWindow::~DiagramWindow() { delete ui; }

QString DiagramWindow::createCircuitElementsRecognizerProcess(
    const QString &imagePath) {
  QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
  QString program = "python.exe";

  QStringList arguments;
  arguments << "main.py" << imagePath;

  QProcess *imageRecognizerProcess = new QProcess();
  imageRecognizerProcess->setProcessEnvironment(env);
  imageRecognizerProcess->setWorkingDirectory(
      "D:\\Studing\\Diploma\\Hand-Drawn-Electrical-Circuit-"
      "Recognition-using-YOLOv5");
  imageRecognizerProcess->start(program, arguments);
  if (!imageRecognizerProcess->waitForStarted(100))
    qDebug() << Q_FUNC_INFO
             << " Unable to start process ::" << imageRecognizerProcess->error()
             << " Error msg" << imageRecognizerProcess->errorString();

  imageRecognizerProcess->waitForFinished();
  QString output(imageRecognizerProcess->readAllStandardOutput());
  qDebug() << Q_FUNC_INFO << "output: " << output << '\n';

  return output;
}

void DiagramWindow::createDynamicLayouts() {
  for (int i = 0; i < _dynamicLayoutsHolder.size(); i++) {
    if (_dynamicLayoutsHolder[i].I != nullptr)
      _mainDynamicLayout->addLayout(_dynamicLayoutsHolder[i].I);
    if (_dynamicLayoutsHolder[i].U != nullptr)
      _mainDynamicLayout->addLayout(_dynamicLayoutsHolder[i].U);
    if (_dynamicLayoutsHolder[i].R != nullptr)
      _mainDynamicLayout->addLayout(_dynamicLayoutsHolder[i].R);
    _mainDynamicLayout->addWidget(LayoutGenerator::createLine(
        "DynamicLine" + QString::number(i), QFrame::HLine));
  }
}

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
  if (phase == PhaseVectorPhase::NOT_DEFINED) {
    QMessageBox::critical(this, "Error", "Please specify phase for the vector");
    return result;
  }
  if (!validateInputParameters()) {
    return result;
  }

  float I1StartGenXEdit =
      _fieldsAddress.lineEdits["IaStartGenXEdit"]->text().toFloat();
  float I1StartGenYEdit =
      _fieldsAddress.lineEdits["IaStartGenYEdit"]->text().toFloat();
  float I1EndGenXEdit =
      _fieldsAddress.lineEdits["IaEndGenXEdit"]->text().toFloat();
  float I1EndGenYEdit =
      _fieldsAddress.lineEdits["IaEndGenYEdit"]->text().toFloat();

  ComplexNumberAdapter currentStart = {I1StartGenXEdit, I1StartGenYEdit,
                                       ComplexNumberForm::GENERAL};
  ComplexNumberAdapter currentEnd = {I1EndGenXEdit, I1EndGenYEdit,
                                     ComplexNumberForm::GENERAL};

  result[{phase, PhaseVectorType::CURRENT}] =
      PhaseVector{currentStart, currentEnd, PhaseVectorType::CURRENT, phase};
  result[{phase, PhaseVectorType::CURRENT}].setLabelNameFromTypeAndPhase();

  float V1StartGenXEdit =
      _fieldsAddress.lineEdits["UaStartGenXEdit"]->text().toFloat();
  float V1StartGenYEdit =
      _fieldsAddress.lineEdits["UaStartGenYEdit"]->text().toFloat();
  float V1EndGenXEdit =
      _fieldsAddress.lineEdits["UaEndGenXEdit"]->text().toFloat();
  float V1EndGenYEdit =
      _fieldsAddress.lineEdits["UaEndGenYEdit"]->text().toFloat();

  ComplexNumberAdapter voltageStart = {V1StartGenXEdit, V1StartGenYEdit,
                                       ComplexNumberForm::GENERAL};
  ComplexNumberAdapter voltageEnd = {V1EndGenXEdit, V1EndGenYEdit,
                                     ComplexNumberForm::GENERAL};

  result[{phase, PhaseVectorType::VOLTAGE}] =
      PhaseVector{voltageStart, voltageEnd, PhaseVectorType::VOLTAGE, phase};
  result[{phase, PhaseVectorType::VOLTAGE}].setLabelNameFromTypeAndPhase();
  return result;
}

void DiagramWindow::setupWindow(QMainWindow *DiagramWindow) {
  ui->setupUi(this);

  ui->PlotDiagram->xAxis->setLabel("X");
  ui->PlotDiagram->yAxis->setLabel("Y");
  ui->PlotDiagram->xAxis->setRange(-300, 300);
  ui->PlotDiagram->yAxis->setRange(-300, 300);
  ui->PlotDiagram->setInteractions(
      {QCP::iRangeDrag, QCP::iRangeZoom, QCP::iSelectPlottables});

  ui->ChoosePhaseComboBox->addItem("A");
  ui->ChoosePhaseComboBox->addItem("B");
  ui->ChoosePhaseComboBox->addItem("C");

  connect(ui->ClearBtn, &QPushButton::clicked, this,
          &DiagramWindow::onClearBtnClicked);
  connect(ui->DrawBtn, &QPushButton::clicked, this,
          &DiagramWindow::onDrawBtnClicked);

  connect(ui->ChooseImageButton, &QPushButton::clicked, this,
          &DiagramWindow::onChooseImageButtonClicked);
}

void DiagramWindow::connectDynamicSlots() {
  qDebug() << Q_FUNC_INFO;
  _fieldsAddress = LayoutGenerator::getFieldsAddresses();
  QStringList parameterName{};

  // we should have all LineEdit components already created with similar
  // objectName.
  for (int i = 0; i < _dynamicLayoutsHolder.size(); i++) {
    if (_dynamicLayoutsHolder[i].U != nullptr) {
      parameterName.append("U");
    }
    if (_dynamicLayoutsHolder[i].I != nullptr) {
      parameterName.append("I");
    }
    if (_dynamicLayoutsHolder[i].R != nullptr) {
      parameterName.append("R");
    }

    for (const auto &pName : parameterName) {
      QString lineEditPrefix = pName + _dynamicLayoutsHolder[i].elementName;

      connect(_fieldsAddress.lineEdits[lineEditPrefix + "StartGenXEdit"],
              &QLineEdit::textEdited, this,
              &DiagramWindow::onStartGenXEditTextEdited);
      connect(_fieldsAddress.lineEdits[lineEditPrefix + "StartGenYEdit"],
              &QLineEdit::textEdited, this,
              &DiagramWindow::onStartGenYEditTextEdited);
      connect(_fieldsAddress.lineEdits[lineEditPrefix + "StartExpAEdit"],
              &QLineEdit::textEdited, this,
              &DiagramWindow::onStartExpAEditTextEdited);
      connect(_fieldsAddress.lineEdits[lineEditPrefix + "StartExpUEdit"],
              &QLineEdit::textEdited, this,
              &DiagramWindow::onStartExpUEditTextEdited);

      connect(_fieldsAddress.lineEdits[lineEditPrefix + "EndGenXEdit"],
              &QLineEdit::textEdited, this,
              &DiagramWindow::onEndGenXEditTextEdited);
      connect(_fieldsAddress.lineEdits[lineEditPrefix + "EndGenYEdit"],
              &QLineEdit::textEdited, this,
              &DiagramWindow::onEndGenYEditTextEdited);
      connect(_fieldsAddress.lineEdits[lineEditPrefix + "EndExpAEdit"],
              &QLineEdit::textEdited, this,
              &DiagramWindow::onEndExpAEditTextEdited);
      connect(_fieldsAddress.lineEdits[lineEditPrefix + "EndExpUEdit"],
              &QLineEdit::textEdited, this,
              &DiagramWindow::onEndExpUEditTextEdited);
    }
    parameterName.clear();
  }
}

void DiagramWindow::onClearBtnClicked() {
  ui->PlotDiagram->clear();
  _model->clear();
}

void DiagramWindow::onDrawBtnClicked() {
  // get parameters from UI
  // create PhaseVectors
  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector> phaseVectors =
      getParametersFromUi();

  // update model and draw the vectors
  _model->fillModel(phaseVectors);
  ui->PlotDiagram->clear();
  ui->PlotDiagram->drawDataFromModel(_model.get());
}

void DiagramWindow::onChooseImageButtonClicked() {
  QString originalImagePath = QFileDialog::getOpenFileName(
      this, tr("Open image"),
      "D://Studing//Diploma//"
      "Hand-Drawn-Electrical-Circuit-Recognition-using-YOLOv5//Test_set",
      "Image (*.png)");

  qDebug() << "Original image path: " << originalImagePath;
  ui->ChooseImageLabel->setText(originalImagePath);
  QPixmap originalImage{originalImagePath};
  ui->OriginalImageLabel->setPixmap(originalImage.scaled(
      ui->OriginalImageLabel->maximumSize(), Qt::KeepAspectRatio));
  ui->RecognizedImageLabel->setText("Please wait, your image is being ond...");

  // image recognition process is started here
  QString output = createCircuitElementsRecognizerProcess(originalImagePath);

  QPixmap recognizedImage{"D://Studing//Diploma//"
                          "Hand-Drawn-Electrical-Circuit-Recognition-using-"
                          "YOLOv5//lastRecognizedImage.png"};
  ui->RecognizedImageLabel->setPixmap(recognizedImage.scaled(
      ui->RecognizedImageLabel->maximumSize(), Qt::KeepAspectRatio));

  QStringList elementsList =
      UtilsImage::recognizeComponentsFromPythonOutput(output);

  //!\todo
  UtilsImage::recognizeConnectionFromPythonOutput(output);

  // clear previous layouts
  _scrollArea->takeWidget()->deleteLater();
  _mainDynamicLayout = new QVBoxLayout();
  _dynamicLayoutsHolder.clear();

  // add new layouts
  for (const auto &e : elementsList) {
    _dynamicLayoutsHolder.addLayoutForElement(e);
  }
  _dynamicLayoutWidget = std::make_unique<QWidget>();
  _dynamicLayoutWidget->setLayout(_mainDynamicLayout);
  _scrollArea->setWidget(_dynamicLayoutWidget.get());

  createDynamicLayouts();
  connectDynamicSlots();
}

void DiagramWindow::onStartGenXEditTextEdited() {
  QString startGenXEditObjectName = QObject::sender()->objectName();

  QString startGenYEditObjectName = QObject::sender()->objectName();
  startGenYEditObjectName.replace("StartGenXEdit", "StartGenYEdit");

  QString startExpUEditObjectName = QObject::sender()->objectName();
  startExpUEditObjectName.replace("StartGenXEdit", "StartExpUEdit");

  QString startExpAEditObjectName = QObject::sender()->objectName();
  startExpAEditObjectName.replace("StartGenXEdit", "StartExpAEdit");

  ComplexNumberAdapter genForm{
      _fieldsAddress.lineEdits[startGenXEditObjectName]->text().toFloat(),
      _fieldsAddress.lineEdits[startGenYEditObjectName]->text().toFloat(),
      ComplexNumberForm::GENERAL};
  ComplexNumberAdapter expForm{genForm.toExponentialForm().real(),
                               genForm.toExponentialForm().imag(),
                               ComplexNumberForm::EXPONENTIAL};
  _fieldsAddress.lineEdits[startExpUEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", expForm.real())));
  _fieldsAddress.lineEdits[startExpAEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", expForm.imag())));
}

void DiagramWindow::onStartGenYEditTextEdited() {
  QString startGenYEditObjectName = QObject::sender()->objectName();

  QString startGenXEditObjectName = QObject::sender()->objectName();
  startGenYEditObjectName.replace("StartGenYEdit", "StartGenXEdit");

  QString startExpUEditObjectName = QObject::sender()->objectName();
  startExpUEditObjectName.replace("StartGenYEdit", "StartExpUEdit");

  QString startExpAEditObjectName = QObject::sender()->objectName();
  startExpAEditObjectName.replace("StartGenYEdit", "StartExpAEdit");

  ComplexNumberAdapter genForm{
      _fieldsAddress.lineEdits[startGenXEditObjectName]->text().toFloat(),
      _fieldsAddress.lineEdits[startGenYEditObjectName]->text().toFloat(),
      ComplexNumberForm::GENERAL};
  ComplexNumberAdapter expForm{genForm.toExponentialForm().real(),
                               genForm.toExponentialForm().imag(),
                               ComplexNumberForm::EXPONENTIAL};
  _fieldsAddress.lineEdits[startExpUEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", expForm.real())));
  _fieldsAddress.lineEdits[startExpAEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", expForm.imag())));
}

void DiagramWindow::onStartExpAEditTextEdited() {
  QString startExpAEditObjectName = QObject::sender()->objectName();

  QString startGenXEditObjectName = QObject::sender()->objectName();
  startGenXEditObjectName.replace("StartExpAEdit", "StartGenXEdit");

  QString startGenYEditObjectName = QObject::sender()->objectName();
  startGenYEditObjectName.replace("StartExpAEdit", "StartGenYEdit");

  QString startExpUEditObjectName = QObject::sender()->objectName();
  startExpUEditObjectName.replace("StartExpAEdit", "StartExpUEdit");

  ComplexNumberAdapter expForm{
      _fieldsAddress.lineEdits[startExpUEditObjectName]->text().toFloat(),
      _fieldsAddress.lineEdits[startExpAEditObjectName]->text().toFloat(),
      ComplexNumberForm::GENERAL};
  ComplexNumberAdapter genForm{expForm.toExponentialForm().real(),
                               expForm.toExponentialForm().imag(),
                               ComplexNumberForm::GENERAL};
  _fieldsAddress.lineEdits[startGenXEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", genForm.real())));
  _fieldsAddress.lineEdits[startGenYEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", genForm.imag())));
}

void DiagramWindow::onStartExpUEditTextEdited() {
  QString startExpUEditObjectName = QObject::sender()->objectName();

  QString startGenXEditObjectName = QObject::sender()->objectName();
  startGenXEditObjectName.replace("StartExpUEdit", "StartGenXEdit");

  QString startGenYEditObjectName = QObject::sender()->objectName();
  startGenYEditObjectName.replace("StartExpUEdit", "StartGenYEdit");

  QString startExpAEditObjectName = QObject::sender()->objectName();
  startExpAEditObjectName.replace("StartExpUEdit", "StartExpAEdit");

  ComplexNumberAdapter expForm{
      _fieldsAddress.lineEdits[startExpUEditObjectName]->text().toFloat(),
      _fieldsAddress.lineEdits[startExpAEditObjectName]->text().toFloat(),
      ComplexNumberForm::GENERAL};
  ComplexNumberAdapter genForm{expForm.toExponentialForm().real(),
                               expForm.toExponentialForm().imag(),
                               ComplexNumberForm::GENERAL};
  _fieldsAddress.lineEdits[startGenXEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", genForm.real())));
  _fieldsAddress.lineEdits[startGenYEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", genForm.imag())));
}

void DiagramWindow::onEndGenXEditTextEdited() {
  QString endGenXEditObjectName = QObject::sender()->objectName();

  QString endGenYEditObjectName = QObject::sender()->objectName();
  endGenYEditObjectName.replace("EndGenXEdit", "EndGenYEdit");

  QString endExpUEditObjectName = QObject::sender()->objectName();
  endExpUEditObjectName.replace("EndGenXEdit", "EndExpUEdit");

  QString endExpAEditObjectName = QObject::sender()->objectName();
  endExpAEditObjectName.replace("EndGenXEdit", "EndExpAEdit");

  ComplexNumberAdapter genForm{
      _fieldsAddress.lineEdits[endGenXEditObjectName]->text().toFloat(),
      _fieldsAddress.lineEdits[endGenYEditObjectName]->text().toFloat(),
      ComplexNumberForm::GENERAL};
  ComplexNumberAdapter expForm{genForm.toExponentialForm().real(),
                               genForm.toExponentialForm().imag(),
                               ComplexNumberForm::EXPONENTIAL};
  _fieldsAddress.lineEdits[endExpUEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", expForm.real())));
  _fieldsAddress.lineEdits[endExpAEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", expForm.imag())));
}

void DiagramWindow::onEndGenYEditTextEdited() {
  QString endGenYEditObjectName = QObject::sender()->objectName();

  QString endGenXEditObjectName = QObject::sender()->objectName();
  endGenYEditObjectName.replace("EndGenYEdit", "EndGenXEdit");

  QString endExpUEditObjectName = QObject::sender()->objectName();
  endExpUEditObjectName.replace("EndGenYEdit", "EndExpUEdit");

  QString endExpAEditObjectName = QObject::sender()->objectName();
  endExpAEditObjectName.replace("EndGenYEdit", "EndExpAEdit");

  ComplexNumberAdapter genForm{
      _fieldsAddress.lineEdits[endGenXEditObjectName]->text().toFloat(),
      _fieldsAddress.lineEdits[endGenYEditObjectName]->text().toFloat(),
      ComplexNumberForm::GENERAL};
  ComplexNumberAdapter expForm{genForm.toExponentialForm().real(),
                               genForm.toExponentialForm().imag(),
                               ComplexNumberForm::EXPONENTIAL};
  _fieldsAddress.lineEdits[endExpUEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", expForm.real())));
  _fieldsAddress.lineEdits[endExpAEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", expForm.imag())));
}

void DiagramWindow::onEndExpAEditTextEdited() {
  QString endExpAEditObjectName = QObject::sender()->objectName();

  QString endGenXEditObjectName = QObject::sender()->objectName();
  endGenXEditObjectName.replace("EndExpAEdit", "EndGenXEdit");

  QString endGenYEditObjectName = QObject::sender()->objectName();
  endGenYEditObjectName.replace("EndExpAEdit", "EndGenYEdit");

  QString endExpUEditObjectName = QObject::sender()->objectName();
  endExpUEditObjectName.replace("EndExpAEdit", "EndExpUEdit");

  ComplexNumberAdapter expForm{
      _fieldsAddress.lineEdits[endExpUEditObjectName]->text().toFloat(),
      _fieldsAddress.lineEdits[endExpAEditObjectName]->text().toFloat(),
      ComplexNumberForm::GENERAL};
  ComplexNumberAdapter genForm{expForm.toExponentialForm().real(),
                               expForm.toExponentialForm().imag(),
                               ComplexNumberForm::GENERAL};
  _fieldsAddress.lineEdits[endGenXEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", genForm.real())));
  _fieldsAddress.lineEdits[endGenYEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", genForm.imag())));
}

void DiagramWindow::onEndExpUEditTextEdited() {
  QString endExpUEditObjectName = QObject::sender()->objectName();

  QString endGenXEditObjectName = QObject::sender()->objectName();
  endGenXEditObjectName.replace("EndExpUEdit", "EndGenXEdit");

  QString endGenYEditObjectName = QObject::sender()->objectName();
  endGenYEditObjectName.replace("EndExpUEdit", "EndGenYEdit");

  QString endExpAEditObjectName = QObject::sender()->objectName();
  endExpAEditObjectName.replace("EndExpUEdit", "EndExpAEdit");

  ComplexNumberAdapter expForm{
      _fieldsAddress.lineEdits[endExpUEditObjectName]->text().toFloat(),
      _fieldsAddress.lineEdits[endExpAEditObjectName]->text().toFloat(),
      ComplexNumberForm::GENERAL};
  ComplexNumberAdapter genForm{expForm.toExponentialForm().real(),
                               expForm.toExponentialForm().imag(),
                               ComplexNumberForm::GENERAL};
  _fieldsAddress.lineEdits[endGenXEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", genForm.real())));
  _fieldsAddress.lineEdits[endGenYEditObjectName]->setText(
      QString::fromStdString(std::format("{:.2f}", genForm.imag())));
}

bool DiagramWindow::validateInputParameters() {
  auto isNumber = [](const QString &s) {
    for (const auto c : s) {
      if (!(c.isNumber() || c.isSymbol('-') || c.isPunct('.'))) {
        return false;
      }
    }
    return true;
  };

  QStringList parameters;
  //  parameters.append(ui->I1StartGenXEdit->text());
  //  parameters.append(ui->I1StartGenYEdit->text());
  //  parameters.append(ui->I1EndGenXEdit->text());
  //  parameters.append(ui->I1EndGenYEdit->text());
  //  parameters.append(ui->V1StartGenXEdit->text());
  //  parameters.append(ui->V1StartGenYEdit->text());
  //  parameters.append(ui->V1EndGenXEdit->text());
  //  parameters.append(ui->V1EndGenYEdit->text());

  for (const QString &s : parameters) {
    if (!isNumber(s)) {
      QMessageBox::critical(this, "Error", "All parameters should be numbers!");
      qDebug() << __FUNCTION__ << "Not all parameters are numbers!\n";
      return false;
    }
  }

  return true;
}
