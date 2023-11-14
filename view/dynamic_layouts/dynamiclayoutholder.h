#ifndef DYNAMICLAYOUTHOLDER_H
#define DYNAMICLAYOUTHOLDER_H
#include "layoutgenerator.h"

// contains layouts for current, voltage and resistance per element in circuit
struct DynamicLayoutsPerElement {
  QVBoxLayout I;
  QVBoxLayout U;
  QVBoxLayout R;

  QString elementName;
};

class DynamicLayoutsHolder {
public:
  DynamicLayoutsHolder();

private:
private:
  QVector<DynamicLayoutsPerElement> _dynamicLayouts;
};

#endif // DYNAMICLAYOUTHOLDER_H
