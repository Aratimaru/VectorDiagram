#include "layoutgenerator.h"
FieldsAddresses LayoutGenerator::_fieldsAddresses;

QHBoxLayout *
LayoutGenerator::createParameterLayout(const QString &parameterName,
                                       const QString &elementName) {
  QHBoxLayout *parameterLayout = new QHBoxLayout;

  // QLabel
  QLabel *parameterLabel = createLabel(elementName + "ParameterLabel",
                                       parameterName + elementName, 15);
  parameterLabel->setMinimumWidth(70);
  qDebug() << Q_FUNC_INFO << "ParameterLabel created with name"
           << parameterLabel->objectName();
  parameterLayout->addWidget(parameterLabel);
  LayoutGenerator::_fieldsAddresses.labels[parameterLabel->objectName()] =
      parameterLabel;

  QVBoxLayout *startLayout = createOneEndLayout(elementName, true);
  QVBoxLayout *endLayout = createOneEndLayout(elementName, false);

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

  // Exp Layout
  QVBoxLayout *oneEndExpLayout = new QVBoxLayout;
  QHBoxLayout *oneEndExpLayoutAbove = new QHBoxLayout;
  QHBoxLayout *oneEndExpLayoutBelow = new QHBoxLayout;

  // ia
  QHBoxLayout *oneEndExpALayout = new QHBoxLayout;
  QLabel *oneEndExpALabel =
      createLabel(elementName + labelCoordinate + "ExpALabel", "ia", 11);
  oneEndExpALabel->setMinimumSize(170, 5);
  oneEndExpALabel->setAlignment(Qt::AlignRight);
  oneEndExpALayout->addWidget(oneEndExpALabel, 8,
                              Qt::AlignRight | Qt::AlignVCenter);
  QLineEdit *oneEndExpAEdit = new QLineEdit;
  oneEndExpAEdit->setObjectName(elementName + labelCoordinate + "ExpAEdit");
  oneEndExpALayout->addWidget(oneEndExpAEdit, 3,
                              Qt::AlignLeft | Qt::AlignVCenter);
  oneEndExpALabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
  oneEndExpAEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
  qDebug() << Q_FUNC_INFO << "oneEndExpAEdit created with name"
           << oneEndExpAEdit->objectName();
  LayoutGenerator::_fieldsAddresses.lineEdits[oneEndExpAEdit->objectName()] =
      oneEndExpAEdit;

  // U Layout
  QHBoxLayout *oneEndExpULayout = new QHBoxLayout;
  QLabel *oneEndExpULabel =
      createLabel(elementName + labelCoordinate + "ExpULabel", "U", 11);
  oneEndExpULayout->addWidget(oneEndExpULabel);
  QLineEdit *oneEndExpUEdit = new QLineEdit;
  oneEndExpUEdit->setObjectName(elementName + labelCoordinate + "ExpUEdit");
  oneEndExpULayout->addWidget(oneEndExpUEdit);
  qDebug() << Q_FUNC_INFO << "oneEndExpUEdit created with name"
           << oneEndExpUEdit->objectName();
  LayoutGenerator::_fieldsAddresses.lineEdits[oneEndExpUEdit->objectName()] =
      oneEndExpUEdit;

  // e
  QHBoxLayout *oneEndExpELayout = new QHBoxLayout;
  QLabel *oneEndExpELabel =
      createLabel(elementName + labelCoordinate + "ExpELabel", "e", 11);
  oneEndExpELayout->addWidget(oneEndExpELabel, 0,
                              Qt::AlignLeft | Qt::AlignVCenter);

  oneEndExpLayoutAbove->addLayout(oneEndExpALayout);
  oneEndExpLayoutBelow->addLayout(oneEndExpULayout, 4);
  oneEndExpLayoutBelow->addLayout(oneEndExpELayout, 5);

  oneEndExpLayout->addLayout(oneEndExpLayoutAbove);
  oneEndExpLayout->addLayout(oneEndExpLayoutBelow);

  oneEndGenLayout->addLayout(oneEndGenXLayout);
  oneEndGenLayout->addLayout(oneEndGenYLayout);

  oneEndLayout->addLayout(oneEndGenLayout);
  oneEndLayout->addLayout(oneEndExpLayout);

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
