#include "qboxlayout.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qprocess.h"
#include "view/diagramwindow.h"
#include <QApplication>
#include <iostream>

using namespace std::complex_literals;

int main(int argc, char *argv[]) // TODO: add units MV, MA, kA, kV...
{
  QApplication a(argc, argv);
  DiagramWindow w;
  w.setWindowState(Qt::WindowMaximized);
  w.show();
  return a.exec();

  //  return 0;
}
