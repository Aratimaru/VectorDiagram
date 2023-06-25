#include "phasevectorcalculator.h"

PhaseVectorCalculator::PhaseVectorCalculator() {}

bool PhaseVectorCalculator::calculate(VectorDiagramModel &model) {

  return true;
}

PhaseVector PhaseVectorCalculator::findMissingVectorForOnePhase(
    VectorDiagramModel &model, const PhaseVectorPhase &phase) {
  PhaseVector vectorToBeFound;

  // phase = column in model

  for (int i = 0; i < model.rowCount(); i++) {
    QModelIndex index = model.index(i, static_cast<int>(phase));
    QLineF coordinates = model.data(index).value<QLineF>();
    vectorToBeFound.setCoodinates(coordinates.p1(), coordinates.p2());
  }
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
