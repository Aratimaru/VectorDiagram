#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomLabel : public QLabel {
public:
  CustomLabel(QWidget *parent = nullptr);

  void constructEndGenYlabel(const QString &parameterName,
                             QWidget *parent = nullptr);

private:
};

#endif // CUSTOMLABEL_H
