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
  QVector<QHBoxLayout *> layoutVector;
  layoutVector.push_back(LayoutGenerator::createParameterLayout("V1"));
  layoutVector.push_back(LayoutGenerator::createParameterLayout("I1"));

  QFrame *topLine = LayoutGenerator::createLine("TopLine", QFrame::HLine);
  QFrame *bottomLine = LayoutGenerator::createLine("BottomLine", QFrame::HLine);

  _mainDynamicLayout->addWidget(topLine);
  for (int i = 0; i < layoutVector.size(); i++) {
    _mainDynamicLayout->addLayout(layoutVector[i]);
    layoutVector[i]->setParent(_mainDynamicLayout);
    _mainDynamicLayout->addWidget(LayoutGenerator::createLine(
        "Line" + QString::number(i), QFrame::HLine));
  }
  _mainDynamicLayout->addWidget(bottomLine);

  // keep initial layouts in the same window as dynamic
  QWidget *dynamicLayouts = new QWidget();
  dynamicLayouts->setLayout(_mainDynamicLayout);

  // Add scroll option to parameters' section
  _scrollArea = new QScrollArea();
  _scrollArea->setWidgetResizable(true);
  _scrollArea->setWidget(dynamicLayouts);
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

  //  connect(ui->ClearBtn, &QPushButton::clicked, this,
  //          &DiagramWindow::onClearBtnClicked);
  //  connect(ui->DrawBtn, &QPushButton::clicked, this,
  //          &DiagramWindow::onDrawBtnClicked);

  //  connect(ui->I1EndExpUEdit, &QLineEdit::textEdited, this,
  //          &DiagramWindow::onI1EndExpTextEdited);

  connect(ui->ChooseImageButton, &QPushButton::clicked, this,
          &DiagramWindow::onChooseImageButtonClicked);
}

void DiagramWindow::connectDynamicSlots() {
  auto fieldsAddress = LayoutGenerator::getFieldsAddresses();
  QStringList fieldsNameTemplates;

  fieldsNameTemplates.append("StartGenXEdit");
  fieldsNameTemplates.append("StartGenYEdit");
  fieldsNameTemplates.append("StartImagAEdit");
  fieldsNameTemplates.append("StartImagUEdit");
  fieldsNameTemplates.append("EndGenXEdit");
  fieldsNameTemplates.append("EndGenYEdit");
  fieldsNameTemplates.append("EndImagAEdit");
  fieldsNameTemplates.append("EndImagUEdit");

  // we should have all LineEdit components already created with similar
  // objectName
  for (int i = 0; i < _dynamicLayoutsHolder.size(); i++) {
    for (const auto &fieldName : fieldsNameTemplates) {
      qDebug() << Q_FUNC_INFO
               << fieldsAddress.lineEdits[_dynamicLayoutsHolder[i].elementName +
                                          fieldName];
      connect(fieldsAddress
                  .lineEdits[_dynamicLayoutsHolder[i].elementName + fieldName],
              &QLineEdit::textEdited, this, &DiagramWindow::onGenTextEdited);
    }
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
      this, tr("Open image"), "D://Studing//Diploma", "Image (*.png)");

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

  for (const auto &e : elementsList) {
    _dynamicLayoutsHolder.addLayoutForElement(e);
  }

  createDynamicLayouts();
  connectDynamicSlots();
}

void DiagramWindow::onGenTextEdited() {

  qDebug() << Q_FUNC_INFO;
  //  ComplexNumberAdapter genForm{ui->V1StartGenXEdit->text().toFloat(),
  //                               ui->V1StartGenYEdit->text().toFloat(),
  //                               ComplexNumberForm::GENERAL};
  //  ComplexNumberAdapter expForm{genForm.toExponentialForm().real(),
  //                               genForm.toExponentialForm().imag(),
  //                               ComplexNumberForm::EXPONENTIAL};
  //  ui->V1StartExpUEdit->setText(
  //      QString::fromStdString(std::format("{:.2f}", expForm.real())));
  //  ui->V1StartExpAEdit->setText(
  //      QString::fromStdString(std::format("{:.2f}", expForm.imag())));
}

void DiagramWindow::onExpTextEdited() {}

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
