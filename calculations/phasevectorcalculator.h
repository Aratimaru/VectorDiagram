#ifndef PHASEVECTORCALCULATOR_H
#define PHASEVECTORCALCULATOR_H

#include "../calculations/complexnumberadapter.h"
#include "calculator.h"

class PhaseVectorCalculator : public Calculator {
public:
  PhaseVectorCalculator();
  bool calculate(VectorDiagramModel &model) override;
  static PhaseVector *
  findMissingVectorForOnePhase(const VectorDiagramModel &model,
                               const PhaseVectorPhase &phase);
  static PhaseVector *findCurrentVector(const PhaseVector &voltageVector,
                                        const PhaseVector &resistenceVector);
  static PhaseVector *findVoltageVector(const PhaseVector &currentVector,
                                        const PhaseVector &resistenceVector);
  static PhaseVector *findResistenceVector(const PhaseVector &currentVector,
                                           const PhaseVector &voltageVector);

  static PhaseVector multExp(const PhaseVector &v1, const PhaseVector &v2);
  static PhaseVector divExp(const PhaseVector &v1, const PhaseVector &v2);
};

#endif // PHASEVECTORCALCULATOR_H
