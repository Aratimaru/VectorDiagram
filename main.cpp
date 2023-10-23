#include "qboxlayout.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qprocess.h"
#include "view/diagramwindow.h"
#include <QApplication>
#include <iostream>

using namespace std::complex_literals;

// class LayoutGenerator {
// public:
//   static QVBoxLayout *createParameterLayout() {
//     QVBoxLayout *infoLayout = new QVBoxLayout;

//    // QLabel для "V1"
//    QLabel *labelV1 = new QLabel("V1");
//    labelV1->setObjectName("V1Label");
//    labelV1->setFont(QFont("Arial", 15));
//    labelV1->setFrameShape(QFrame::NoFrame);
//    labelV1->setFrameShadow(QFrame::Plain);

//    // Додаємо QLabel "V1" до лейауту інформації
//    infoLayout->addWidget(labelV1);

//    // Лейаут для інформації про початкові координати
//    QVBoxLayout *startLayout = new QVBoxLayout;
//    startLayout->setObjectName("V1StartLayout");

//    // QLabel для "Start coordinates"
//    QLabel *startLabel = new QLabel("Start coordinates");
//    startLabel->setObjectName("V1StartLabel");
//    startLabel->setFont(QFont("Arial", 11));
//    startLabel->setFrameShape(QFrame::StyledPanel);
//    startLabel->setFrameShadow(QFrame::Plain);
//    startLabel->setText("Start coordinates");
//    startLabel->setAlignment(Qt::AlignCenter);

//    // Додаємо QLabel "Start coordinates" до лейауту інформації про початкові
//    // координати
//    startLayout->addWidget(startLabel);

//    // Лейаут для X координати початкових координат
//    QHBoxLayout *startGenXLayout = new QHBoxLayout;

//    // QLabel для "x"
//    QLabel *startGenXLabel = new QLabel("x");
//    startGenXLabel->setObjectName("V1StartGenXLabel");
//    startGenXLabel->setFont(QFont("Arial", 13));
//    startGenXLabel->setFrameShape(QFrame::NoFrame);
//    startGenXLabel->setFrameShadow(QFrame::Plain);
//    startGenXLabel->setText("x");

//    // Додаємо QLabel "x" до лейауту X координати початкових координат
//    startGenXLayout->addWidget(startGenXLabel);

//    // QLineEdit для введення X координати
//    QLineEdit *startGenXEdit = new QLineEdit;
//    startGenXEdit->setObjectName("V1StartGenXEdit");

//    // Додаємо QLineEdit до лейауту X координати початкових координат
//    startGenXLayout->addWidget(startGenXEdit);

//    // Лейаут для Y координати початкових координат
//    QHBoxLayout *startGenYLayout = new QHBoxLayout;

//    // QLabel для "+iy"
//    QLabel *startGenYLabel = new QLabel("+iy");
//    startGenYLabel->setObjectName("V1StartGenYLabel");
//    startGenYLabel->setFont(QFont("Arial", 13));
//    startGenYLabel->setFrameShape(QFrame::NoFrame);
//    startGenYLabel->setFrameShadow(QFrame::Plain);
//    startGenYLabel->setText("+iy");

//    // Додаємо QLabel "+iy" до лейауту Y координати початкових координат
//    startGenYLayout->addWidget(startGenYLabel);

//    // QLineEdit для введення Y координати
//    QLineEdit *startGenYEdit = new QLineEdit;
//    startGenYEdit->setObjectName("V1StartGenYEdit");

//    // Додаємо QLineEdit до лейауту Y координати початкових координат
//    startGenYLayout->addWidget(startGenYEdit);

//    // Додаємо лейаут X координати початкових координат до лейауту інформації
//    // про початкові координати
//    startLayout->addLayout(startGenXLayout);
//    startLayout->addLayout(startGenYLayout);

//    // Лейаут для інформації про початкові координати
//    QVBoxLayout *endLayout = new QVBoxLayout;
//    endLayout->setObjectName("V1EndLayout");

//    // QLabel для "End coordinates"
//    QLabel *endLabel = new QLabel("End coordinates");
//    endLabel->setObjectName("V1EndLabel");
//    endLabel->setFont(QFont("Arial", 11));
//    endLabel->setFrameShape(QFrame::StyledPanel);
//    endLabel->setFrameShadow(QFrame::Plain);
//    endLabel->setText("End coordinates");
//    endLabel->setAlignment(Qt::AlignCenter);

//    // Додаємо QLabel "End coordinates" до лейауту інформації про початкові
//    // координати
//    endLayout->addWidget(endLabel);

//    // Лейаут для X координати початкових координат
//    QHBoxLayout *endGenXLayout = new QHBoxLayout;

//    // QLabel для "x"
//    QLabel *endGenXLabel = new QLabel("x");
//    endGenXLabel->setObjectName("V1EndGenXLabel");
//    endGenXLabel->setFont(QFont("Arial", 13));
//    endGenXLabel->setFrameShape(QFrame::NoFrame);
//    endGenXLabel->setFrameShadow(QFrame::Plain);
//    endGenXLabel->setText("x");

//    // Додаємо QLabel "x" до лейауту X координати початкових координат
//    endGenXLayout->addWidget(endGenXLabel);

//    // QLineEdit для введення X координати
//    QLineEdit *endGenXEdit = new QLineEdit;
//    endGenXEdit->setObjectName("V1EndGenXEdit");

//    // Додаємо QLineEdit до лейауту X координати початкових координат
//    endGenXLayout->addWidget(endGenXEdit);

//    // Лейаут для Y координати початкових координат
//    QHBoxLayout *endGenYLayout = new QHBoxLayout;

//    // QLabel для "+iy"
//    QLabel *endGenYLabel = new QLabel("+iy");
//    endGenYLabel->setObjectName("V1EndGenYLabel");
//    endGenYLabel->setFont(QFont("Arial", 13));
//    endGenYLabel->setFrameShape(QFrame::NoFrame);
//    endGenYLabel->setFrameShadow(QFrame::Plain);
//    endGenYLabel->setText("+iy");

//    // Додаємо QLabel "+iy" до лейауту Y координати початкових координат
//    endGenYLayout->addWidget(endGenYLabel);

//    // QLineEdit для введення Y координати
//    QLineEdit *endGenYEdit = new QLineEdit;
//    endGenYEdit->setObjectName("V1EndGenYEdit");

//    // Додаємо QLineEdit до лейауту Y координати початкових координат
//    endGenYLayout->addWidget(endGenYEdit);

//    // Додаємо лейаут X координати початкових координат до лейауту інформації
//    // про початкові координати
//    endLayout->addLayout(endGenXLayout);
//    endLayout->addLayout(endGenYLayout);

//    // Додаємо інші елементи (Y координату, інші лейаути і т. д.) аналогічно

//    // Додаємо лейаут інформації про початкові координати до лейауту
//    інформації infoLayout->addLayout(startLayout);
//    infoLayout->addLayout(endLayout);

//    // Додаємо інші інформаційні лейаути (про кінцеві координати, інші лінії і
//    // т. д.) аналогічно

//    return infoLayout;
//  }
//};

int main(int argc, char *argv[]) // TODO: add units MV, MA, kA, kV...
{
  //  QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
  //  QString program = "python.exe";

  //  QStringList arguments;
  //  arguments << "main.py"
  //            << "Test_set\\19.PNG";

  //  QProcess *imageRecognizerProcess = new QProcess();
  //  imageRecognizerProcess->setProcessEnvironment(env);
  //  imageRecognizerProcess->setWorkingDirectory(
  //      "D:\\Studing\\Diploma\\Hand-Drawn-Electrical-Circuit-"
  //      "Recognition-using-YOLOv5");
  //  imageRecognizerProcess->start(program, arguments);
  //  if (!imageRecognizerProcess->waitForStarted(100))
  //    qDebug() << " Unable to startn process ::"
  //             << imageRecognizerProcess->error() << " Error msg"
  //             << imageRecognizerProcess->errorString();

  //  imageRecognizerProcess->waitForFinished();
  //  QString output(imageRecognizerProcess->readAllStandardOutput());
  //  qDebug() << "output: " << output << '\n';

  QApplication a(argc, argv);
  DiagramWindow w;
  w.show();

  //  QWidget *mainWindow = new QWidget;
  //  mainWindow->setObjectName("V1Layout");

  //  // Головний лейаут для головного вікна
  //  QHBoxLayout *mainLayout = new QHBoxLayout(mainWindow);

  //  // Створюємо кілька лейаутів за допомогою методу createParameterLayout
  //  QVBoxLayout *v1Layout1 = LayoutGenerator::createParameterLayout();
  //  QVBoxLayout *v1Layout2 = LayoutGenerator::createParameterLayout();
  //  QVBoxLayout *v1Layout3 = LayoutGenerator::createParameterLayout();

  //  // Додаємо створені лейаути до головного лейауту
  //  mainLayout->addLayout(v1Layout1);
  //  mainLayout->addLayout(v1Layout2);
  //  mainLayout->addLayout(v1Layout3);

  //  mainWindow->show();

  return a.exec();

  //  return 0;
}
