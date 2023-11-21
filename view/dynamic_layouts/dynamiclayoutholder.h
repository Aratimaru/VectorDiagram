#ifndef DYNAMICLAYOUTHOLDER_H
#define DYNAMICLAYOUTHOLDER_H
#include "layoutgenerator.h"

// contains layouts for current, voltage and resistance per element in circuit
struct DynamicLayoutsPerElement {
  QHBoxLayout *I;
  QHBoxLayout *U;
  QHBoxLayout *R;

  QString elementName;
};

class DynamicLayoutsHolder {
public:
  DynamicLayoutsHolder() = default;
  void addLayoutForElement(const QString &elementName);
  void push_back(DynamicLayoutsPerElement &el);
  void pop_back();
  int size();
  const DynamicLayoutsPerElement &operator[](int) const;
  DynamicLayoutsPerElement &operator[](int);

private:
  QVector<DynamicLayoutsPerElement *> _dynamicLayouts;
};

#endif // DYNAMICLAYOUTHOLDER_H
