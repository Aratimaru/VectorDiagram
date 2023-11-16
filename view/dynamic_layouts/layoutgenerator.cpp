#include "layoutgenerator.h"
FieldsAddresses LayoutGenerator::_fieldsAddresses;

QHBoxLayout *LayoutGenerator::createParameterLayout(const QString &name) {
  QHBoxLayout *parameterLayout = new QHBoxLayout;

  // QLabel
  QLabel *parameterLabel = createLabel(name + "ParameterLabel", name, 15);
  parameterLabel->setMinimumWidth(70);
  qDebug() << Q_FUNC_INFO << "ParameterLabel created with name"
           << parameterLabel->objectName();
  parameterLayout->addWidget(parameterLabel);
  LayoutGenerator::_fieldsAddresses.labels[parameterLabel->objectName()] =
      parameterLabel;

  QVBoxLayout *startLayout = createOneEndLayout(name, true);
  QVBoxLayout *endLayout = createOneEndLayout(name, false);

  QFrame *leftLine = createLine("TopLine", QFrame::VLine);
  QFrame *centralLine = createLine("CentralLine", QFrame::VLine);
  QFrame *rightLine = createLine("BottomLine", QFrame::VLine);

  parameterLayout->addWidget(leftLine);
  parameterLayout->addLayout(startLayout);
  parameterLayout->addWidget(centralLine);
  parameterLayout->addLayout(endLayout);
  parameterLayout->addWidget(rightLine);

  return parameterLayout;
}

QVBoxLayout *LayoutGenerator::createOneEndLayout(const QString &elementName,
                                                 bool start) {
  QString labelCoordinate;
  if (start) {
    labelCoordinate = "Start";
  } else {
    labelCoordinate = "End";
  }

  QVBoxLayout *oneEndLayout = new QVBoxLayout;
  oneEndLayout->setObjectName(elementName + labelCoordinate + "Layout");

  QLabel *oneEndLabel =
      createLabel(elementName + labelCoordinate + "Сoordinates",
                  labelCoordinate + " сoordinates", 13);
  oneEndLabel->setFrameShape(QFrame::StyledPanel);
  oneEndLayout->addWidget(oneEndLabel);

  // Gen Layout
  QHBoxLayout *oneEndGenLayout = new QHBoxLayout;

  // X Layout
  QHBoxLayout *oneEndGenXLayout = new QHBoxLayout;
  QLabel *oneEndGenXLabel =
      createLabel(elementName + labelCoordinate + "GenXLabel", "x", 11);
  oneEndGenXLayout->addWidget(oneEndGenXLabel);
  QLineEdit *oneEndGenXEdit = new QLineEdit;
  oneEndGenXEdit->setObjectName(elementName + labelCoordinate + "GenXEdit");
  oneEndGenXLayout->addWidget(oneEndGenXEdit);
  qDebug() << Q_FUNC_INFO << "oneEndGenXEdit created with name"
           << oneEndGenXEdit->objectName();
  LayoutGenerator::_fieldsAddresses.lineEdits[oneEndGenXEdit->objectName()] =
      oneEndGenXEdit;

  // Y Layout
  QHBoxLayout *oneEndGenYLayout = new QHBoxLayout;
  QLabel *oneEndGenYLabel =
      createLabel(elementName + labelCoordinate + "GenYLabel", "+iy", 11);
  oneEndGenYLayout->addWidget(oneEndGenYLabel);
  QLineEdit *oneEndGenYEdit = new QLineEdit;
  oneEndGenYEdit->setObjectName(elementName + labelCoordinate + "GenYEdit");
  oneEndGenYLayout->addWidget(oneEndGenYEdit);
  qDebug() << Q_FUNC_INFO << "oneEndGenYEdit created with name"
           << oneEndGenYEdit->objectName();
  LayoutGenerator::_fieldsAddresses.lineEdits[oneEndGenYEdit->objectName()] =
      oneEndGenYEdit;

  // Imag Layout
  QVBoxLayout *oneEndImagLayout = new QVBoxLayout;
  QHBoxLayout *oneEndImagLayoutAbove = new QHBoxLayout;
  QHBoxLayout *oneEndImagLayoutBelow = new QHBoxLayout;

  // ia
  QHBoxLayout *oneEndImagALayout = new QHBoxLayout;
  QLabel *oneEndImagALabel =
      createLabel(elementName + labelCoordinate + "ImagALabel", "ia", 11);
  oneEndImagALabel->setMinimumSize(170, 5);
  oneEndImagALabel->setAlignment(Qt::AlignRight);
  oneEndImagALayout->addWidget(oneEndImagALabel, 8,
                               Qt::AlignRight | Qt::AlignVCenter);
  QLineEdit *oneEndImagAEdit = new QLineEdit;
  oneEndImagAEdit->setObjectName(elementName + labelCoordinate + "ImagAEdit");
  oneEndImagALayout->addWidget(oneEndImagAEdit, 3,
                               Qt::AlignLeft | Qt::AlignVCenter);
  oneEndImagALabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
  oneEndImagAEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
  qDebug() << Q_FUNC_INFO << "oneEndImagAEdit created with name"
           << oneEndImagAEdit->objectName();
  LayoutGenerator::_fieldsAddresses.lineEdits[oneEndImagAEdit->objectName()] =
      oneEndImagAEdit;

  // U Layout
  QHBoxLayout *oneEndImagULayout = new QHBoxLayout;
  QLabel *oneEndImagULabel =
      createLabel(elementName + labelCoordinate + "ImagULabel", "U", 11);
  oneEndImagULayout->addWidget(oneEndImagULabel);
  QLineEdit *oneEndImagUEdit = new QLineEdit;
  oneEndImagUEdit->setObjectName(elementName + labelCoordinate + "ImagUEdit");
  oneEndImagULayout->addWidget(oneEndImagUEdit);
  qDebug() << Q_FUNC_INFO << "oneEndImagUEdit created with name"
           << oneEndImagUEdit->objectName();
  LayoutGenerator::_fieldsAddresses.lineEdits[oneEndImagUEdit->objectName()] =
      oneEndImagUEdit;

  // e
  QHBoxLayout *oneEndImagELayout = new QHBoxLayout;
  QLabel *oneEndImagELabel =
      createLabel(elementName + labelCoordinate + "ImagELabel", "e", 11);
  oneEndImagELayout->addWidget(oneEndImagELabel, 0,
                               Qt::AlignLeft | Qt::AlignVCenter);

  oneEndImagLayoutAbove->addLayout(oneEndImagALayout);
  oneEndImagLayoutBelow->addLayout(oneEndImagULayout, 4);
  oneEndImagLayoutBelow->addLayout(oneEndImagELayout, 5);

  oneEndImagLayout->addLayout(oneEndImagLayoutAbove);
  oneEndImagLayout->addLayout(oneEndImagLayoutBelow);

  oneEndGenLayout->addLayout(oneEndGenXLayout);
  oneEndGenLayout->addLayout(oneEndGenYLayout);

  oneEndLayout->addLayout(oneEndGenLayout);
  oneEndLayout->addLayout(oneEndImagLayout);

  return oneEndLayout;
}

QLabel *LayoutGenerator::createLabel(const QString &objectName,
                                     const QString &name, int font) {
  QLabel *oneEndLabel = new QLabel(name);
  oneEndLabel->setObjectName(objectName);
  oneEndLabel->setFont(QFont("Arial", font));
  oneEndLabel->setFrameShape(QFrame::NoFrame);
  oneEndLabel->setFrameShadow(QFrame::Plain);
  oneEndLabel->setText(name);
  oneEndLabel->setAlignment(Qt::AlignCenter);
  return oneEndLabel;
}

QFrame *LayoutGenerator::createLine(const QString &name, QFrame::Shape shape) {
  QFrame *line = new QFrame;
  line->setObjectName(name);
  line->setFrameShape(shape);
  line->setFrameShadow(QFrame::Raised);
  return line;
}

FieldsAddresses &LayoutGenerator::getFieldsAddresses() {
  return LayoutGenerator::_fieldsAddresses;
}
