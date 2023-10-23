#ifndef WIDGETCREATOR_H
#define WIDGETCREATOR_H

#include "qwidget.h"
enum class WidgetType { Q_LABEL, Q_TEXT_EDIT, Q_PUSH_BUTTON, Q_LINE_EDIT };

class WidgetCreator {
public:
  WidgetCreator() = default;
  static QWidget *create(WidgetType widgetType, QWidget *parent = nullptr);
};

#endif // WIDGETCREATOR_H
