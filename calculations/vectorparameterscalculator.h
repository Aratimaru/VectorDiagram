#ifndef VectorParametersCalculator_H
#define VectorParametersCalculator_H
#include "data_structure/phaseparametersstorage.h"
#include "data_structure/phasevector.h"
#include <vector>

class VectorParametersCalculator {
private:
  bool necessaryParametersFound(PhaseParametersStorage &data,
                                PhaseVectorType value);

public:
  VectorParametersCalculator();
  std::vector<PhaseVector> calculate(
      PhaseParametersStorage &data); // empty if no enough parameters
                                     // returns complex numbers in general form
                                     // sets only vector's end coordinate
                                     // 0 - voltage, 1 - current

  PhaseVector calculate(const PhaseVector &v1, const PhaseVector &v2);

  //    void convertToUnit (Parameters p, const UnitPrefix u);
  //    void convertToUnit (Parameter& p, const UnitPrefix u);     //TODO:
  //    change to private void convertToSmallerUnit(Parameter& p1, Parameter&
  //    p2); void convertToBiggerUnit(Parameter& p1, Parameter& p2);

  //    void sentResults(PhaseVector& currentVector, PhaseVector&
  //    voltageVector);           //TODO: remove

private:
  void calculateCurrentVector(PhaseParametersStorage &phaseParametersStorage);
  void calculateVoltageVector(PhaseParametersStorage &phaseParametersStorage);
  void
  calculateResistenceVector(PhaseParametersStorage &phaseParametersStorage);
};

#endif // VectorParametersCalculator_H
