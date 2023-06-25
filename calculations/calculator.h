#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "data_structure/phaseparametersstorage.h"

class Calculator {
public:
  virtual bool calculate(PhaseParametersStorage &data) = 0;
};

#endif // CALCULATOR_H
