#include "phasevectorcalculator.h"

PhaseVectorCalculator::PhaseVectorCalculator() {}

bool PhaseVectorCalculator::calculate(VectorDiagramModel &model) {

  return true;
}

PhaseVector PhaseVectorCalculator::findMissingVectorForOnePhase(
    VectorDiagramModel &model, const PhaseVectorPhase &phase) {
  PhaseVector vectorToBeFound;
  return vectorToBeFound;
}

bool PhaseVectorCalculator::nessesaryVectorsKnown(
    const VectorDiagramModel &model, const PhaseVectorPhase &phase) const {
  return true;
}

void PhaseVectorCalculator::findCurrentVector(
    const PhaseVector &voltageVector, const PhaseVector &resistenceVector) {}

void PhaseVectorCalculator::findVoltageVector(
    const PhaseVector &currentVector, const PhaseVector &resistenceVector) {}

void PhaseVectorCalculator::findResistenceVector(
    const PhaseVector &currentVector, const PhaseVector &voltageVector) {}
