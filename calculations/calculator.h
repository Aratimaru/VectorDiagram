#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "model/vectordiagrammodel.h"
class Calculator {
public:
  virtual bool calculate(VectorDiagramModel &model) = 0;
};

#endif // CALCULATOR_H
