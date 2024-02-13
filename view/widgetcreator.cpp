#include "widgetcreator.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include "qtextedit.h"

QWidget *WidgetCreator::create(WidgetType widgetType, QWidget *parent) {
  switch (widgetType) {
  case WidgetType::Q_LABEL:
    return new QLabel(parent);
    break;
  case WidgetType::Q_TEXT_EDIT:
    return new QTextEdit(parent);
    break;
  case WidgetType::Q_PUSH_BUTTON:
    return new QPushButton(parent);
    break;
  case WidgetType::Q_LINE_EDIT:
    return new QLineEdit(parent);
    break;
  default:
    qDebug() << "Widget type isn't implemented";
    Q_ASSERT(false);
    break;
  }
}
