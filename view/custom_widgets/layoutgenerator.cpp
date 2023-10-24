#include "layoutgenerator.h"
#include "qlabel.h"
#include "qlineedit.h"

LayoutGenerator::LayoutGenerator() {}

QHBoxLayout *LayoutGenerator::createParameterLayout(const QString &name) {
  QHBoxLayout *infoLayout = new QHBoxLayout;

  // QLabel
  QLabel *labelV1 = createLabel(name, name, 15);
  infoLayout->addWidget(labelV1);

  QVBoxLayout *startLayout = createOneEndLayout(true);
  QVBoxLayout *endLayout = createOneEndLayout(false);

  QFrame *leftLine = createLine("TopLine", QFrame::VLine);
  QFrame *centralLine = createLine("CentralLine", QFrame::VLine);
  QFrame *rightLine = createLine("BottomLine", QFrame::VLine);

  infoLayout->addWidget(leftLine);
  infoLayout->addLayout(startLayout);
  infoLayout->addWidget(centralLine);
  infoLayout->addLayout(endLayout);
  infoLayout->addWidget(rightLine);

  return infoLayout;
}

QVBoxLayout *LayoutGenerator::createOneEndLayout(bool start) {
  QVBoxLayout *startLayout = new QVBoxLayout;
  startLayout->setObjectName("V1StartLayout");

  // QLabel для "Start coordinates"
  QString labelCoordinate;
  if (start) {
    labelCoordinate = "Start";
  } else {
    labelCoordinate = "End";
  }
  QLabel *startLabel = createLabel(labelCoordinate + " coordinates",
                                   labelCoordinate + " coordinates", 13);
  startLabel->setFrameShape(QFrame::StyledPanel);
  startLayout->addWidget(startLabel);

  // Gen Layout
  QHBoxLayout *startGenLayout = new QHBoxLayout;

  // X Layout
  QHBoxLayout *startGenXLayout = new QHBoxLayout;
  QLabel *startGenXLabel = createLabel("x", labelCoordinate + "GenXLabel", 11);
  startGenXLayout->addWidget(startGenXLabel);
  QLineEdit *startGenXEdit = new QLineEdit;
  startGenXEdit->setObjectName(labelCoordinate + "GenXEdit");
  startGenXLayout->addWidget(startGenXEdit);

  // Y Layout
  QHBoxLayout *startGenYLayout = new QHBoxLayout;
  QLabel *startGenYLabel =
      createLabel("+iy", labelCoordinate + "GenYLabel", 11);
  startGenYLayout->addWidget(startGenYLabel);
  QLineEdit *startGenYEdit = new QLineEdit;
  startGenYEdit->setObjectName(labelCoordinate + "GenYEdit");
  startGenYLayout->addWidget(startGenYEdit);

  // Imag Layout
  QVBoxLayout *startImagLayout = new QVBoxLayout;
  QHBoxLayout *startImagLayoutAbove = new QHBoxLayout;
  QHBoxLayout *startImagLayoutBelow = new QHBoxLayout;

  // ia
  QHBoxLayout *startImagALayout = new QHBoxLayout;
  QLabel *startImagALabel =
      createLabel("ia", labelCoordinate + "ImagALabel", 11);
  startImagALayout->addWidget(startImagALabel, 8,
                              Qt::AlignRight | Qt::AlignVCenter);
  QLineEdit *startImagAEdit = new QLineEdit;
  startImagAEdit->setObjectName(labelCoordinate + "ImagAEdit");
  startImagALayout->addWidget(startImagAEdit, 3,
                              Qt::AlignLeft | Qt::AlignVCenter);
  startImagALabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
  startImagAEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

  // U Layout
  QHBoxLayout *startImagULayout = new QHBoxLayout;
  QLabel *startImagULabel =
      createLabel("U", labelCoordinate + "ImagULabel", 11);
  startImagULayout->addWidget(startImagULabel);
  QLineEdit *startImagUEdit = new QLineEdit;
  startImagUEdit->setObjectName(labelCoordinate + "ImagUEdit");
  startImagULayout->addWidget(startImagUEdit);

  // e
  QHBoxLayout *startImagELayout = new QHBoxLayout;
  QLabel *startImagELabel =
      createLabel("e", labelCoordinate + "ImagELabel", 11);
  startImagELayout->addWidget(startImagELabel, 0,
                              Qt::AlignLeft | Qt::AlignVCenter);

  startImagLayoutAbove->addLayout(startImagALayout);
  startImagLayoutBelow->addLayout(startImagULayout, 4);
  startImagLayoutBelow->addLayout(startImagELayout, 5);

  startImagLayout->addLayout(startImagLayoutAbove);
  startImagLayout->addLayout(startImagLayoutBelow);

  startGenLayout->addLayout(startGenXLayout);
  startGenLayout->addLayout(startGenYLayout);

  startLayout->addLayout(startGenLayout);
  startLayout->addLayout(startImagLayout);

  return startLayout;
}

QLabel *LayoutGenerator::createLabel(const QString &name,
                                     const QString &objectName, int font) {
  QLabel *startLabel = new QLabel(name);
  startLabel->setObjectName(name);
  startLabel->setFont(QFont("Arial", font));
  startLabel->setFrameShape(QFrame::NoFrame);
  startLabel->setFrameShadow(QFrame::Plain);
  startLabel->setText(name);
  startLabel->setAlignment(Qt::AlignCenter);
  return startLabel;
}

QFrame *LayoutGenerator::createLine(const QString &name, QFrame::Shape shape) {
  QFrame *line = new QFrame;
  line->setObjectName(name);
  line->setFrameShape(shape);
  line->setFrameShadow(QFrame::Raised);
  return line;
}
