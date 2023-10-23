#ifndef LAYOUTGENERATOR_H
#define LAYOUTGENERATOR_H

#include "qboxlayout.h"
#include "qlabel.h"
class LayoutGenerator {
public:
  LayoutGenerator();

  static QHBoxLayout *createParameterLayout(const QString &name);
  static QVBoxLayout *createOneEndLayout(bool start);
  static QLabel *createLabel(const QString &name, const QString &objectName,
                             int font);
  static QFrame *createLine(const QString &name, QFrame::Shape shape);
};

#endif // LAYOUTGENERATOR_H
