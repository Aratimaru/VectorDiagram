#ifndef PHASEVECTORCALCULATOR_H
#define PHASEVECTORCALCULATOR_H

#include "calculator.h"

class PhaseVectorCalculator : public Calculator {
public:
  PhaseVectorCalculator();
  bool calculate(VectorDiagramModel &model) override;
  PhaseVector *findMissingVectorForOnePhase(VectorDiagramModel &model,
                                            const PhaseVectorPhase &phase);
  PhaseVector *findCurrentVector(const PhaseVector &voltageVector,
                                 const PhaseVector &resistenceVector);
  PhaseVector *findVoltageVector(const PhaseVector &currentVector,
                                 const PhaseVector &resistenceVector);
  PhaseVector *findResistenceVector(const PhaseVector &currentVector,
                                    const PhaseVector &voltageVector);

private:
  bool nessesaryVectorsKnown(const VectorDiagramModel &model,
                             const PhaseVectorPhase &phase) const;
};

#endif // PHASEVECTORCALCULATOR_H
