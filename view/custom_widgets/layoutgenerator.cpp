#include "layoutgenerator.h"
#include "qlabel.h"
#include "qlineedit.h"

LayoutGenerator::LayoutGenerator() {}

QHBoxLayout *LayoutGenerator::createParameterLayout(const QString &name) {
  QHBoxLayout *parameterLayout = new QHBoxLayout;

  // QLabel
  QLabel *labelV1 = createLabel(name, name, 15);
  parameterLayout->addWidget(labelV1);

  QVBoxLayout *oneEndLayout = createOneEndLayout(true);
  QVBoxLayout *endLayout = createOneEndLayout(false);

  QFrame *leftLine = createLine("TopLine", QFrame::VLine);
  QFrame *centralLine = createLine("CentralLine", QFrame::VLine);
  QFrame *rightLine = createLine("BottomLine", QFrame::VLine);

  parameterLayout->addWidget(leftLine);
  parameterLayout->addLayout(oneEndLayout);
  parameterLayout->addWidget(centralLine);
  parameterLayout->addLayout(endLayout);
  parameterLayout->addWidget(rightLine);

  return parameterLayout;
}

QVBoxLayout *LayoutGenerator::createOneEndLayout(bool start) {
  QVBoxLayout *oneEndLayout = new QVBoxLayout;
  oneEndLayout->setObjectName("V1StartLayout");

  // QLabel для "Start coordinates"
  QString labelCoordinate;
  if (start) {
    labelCoordinate = "Start";
  } else {
    labelCoordinate = "End";
  }
  QLabel *oneEndLabel = createLabel(labelCoordinate + " coordinates",
                                    labelCoordinate + " coordinates", 13);
  oneEndLabel->setFrameShape(QFrame::StyledPanel);
  oneEndLayout->addWidget(oneEndLabel);

  // Gen Layout
  QHBoxLayout *oneEndGenLayout = new QHBoxLayout;

  // X Layout
  QHBoxLayout *oneEndGenXLayout = new QHBoxLayout;
  QLabel *oneEndGenXLabel = createLabel("x", labelCoordinate + "GenXLabel", 11);
  oneEndGenXLayout->addWidget(oneEndGenXLabel);
  QLineEdit *oneEndGenXEdit = new QLineEdit;
  oneEndGenXEdit->setObjectName(labelCoordinate + "GenXEdit");
  oneEndGenXLayout->addWidget(oneEndGenXEdit);

  // Y Layout
  QHBoxLayout *oneEndGenYLayout = new QHBoxLayout;
  QLabel *oneEndGenYLabel =
      createLabel("+iy", labelCoordinate + "GenYLabel", 11);
  oneEndGenYLayout->addWidget(oneEndGenYLabel);
  QLineEdit *oneEndGenYEdit = new QLineEdit;
  oneEndGenYEdit->setObjectName(labelCoordinate + "GenYEdit");
  oneEndGenYLayout->addWidget(oneEndGenYEdit);

  // Imag Layout
  QVBoxLayout *oneEndImagLayout = new QVBoxLayout;
  QHBoxLayout *oneEndImagLayoutAbove = new QHBoxLayout;
  QHBoxLayout *oneEndImagLayoutBelow = new QHBoxLayout;

  // ia
  QHBoxLayout *oneEndImagALayout = new QHBoxLayout;
  QLabel *oneEndImagALabel =
      createLabel("ia", labelCoordinate + "ImagALabel", 11);
  oneEndImagALabel->setMinimumSize(170, 5);
  oneEndImagALabel->setAlignment(Qt::AlignRight);
  oneEndImagALayout->addWidget(oneEndImagALabel, 8,
                               Qt::AlignRight | Qt::AlignVCenter);
  QLineEdit *oneEndImagAEdit = new QLineEdit;
  oneEndImagAEdit->setObjectName(labelCoordinate + "ImagAEdit");
  oneEndImagALayout->addWidget(oneEndImagAEdit, 3,
                               Qt::AlignLeft | Qt::AlignVCenter);
  oneEndImagALabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
  oneEndImagAEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

  // U Layout
  QHBoxLayout *oneEndImagULayout = new QHBoxLayout;
  QLabel *oneEndImagULabel =
      createLabel("U", labelCoordinate + "ImagULabel", 11);
  oneEndImagULayout->addWidget(oneEndImagULabel);
  QLineEdit *oneEndImagUEdit = new QLineEdit;
  oneEndImagUEdit->setObjectName(labelCoordinate + "ImagUEdit");
  oneEndImagULayout->addWidget(oneEndImagUEdit);

  // e
  QHBoxLayout *oneEndImagELayout = new QHBoxLayout;
  QLabel *oneEndImagELabel =
      createLabel("e", labelCoordinate + "ImagELabel", 11);
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

QLabel *LayoutGenerator::createLabel(const QString &name,
                                     const QString &objectName, int font) {
  QLabel *oneEndLabel = new QLabel(name);
  oneEndLabel->setObjectName(name);
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
