#ifndef LAYOUTGENERATOR_H
#define LAYOUTGENERATOR_H

#include "qboxlayout.h"
#include "qlabel.h"
#include "qlineedit.h"

struct FieldsAddresses {
  QMap<QString, QLabel *> labels{};
  QMap<QString, QLineEdit *> lineEdits{};
};

class LayoutGenerator {
public:
  LayoutGenerator() = default;

  static QHBoxLayout *createParameterLayout(const QString &name);
  static QVBoxLayout *createOneEndLayout(const QString &elementName,
                                         bool start);
  static QLabel *createLabel(const QString &objectName, const QString &name,
                             int font);
  static QFrame *createLine(const QString &name, QFrame::Shape shape);
  static FieldsAddresses &getFieldsAddresses();

private:
  static FieldsAddresses _fieldsAddresses;
};

#endif // LAYOUTGENERATOR_H
