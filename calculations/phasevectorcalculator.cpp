#include "phasevectorcalculator.h"

PhaseVectorCalculator::PhaseVectorCalculator() {}

bool PhaseVectorCalculator::calculate(VectorDiagramModel &model) {

  return true;
}

PhaseVector *PhaseVectorCalculator::findMissingVectorForOnePhase(
    VectorDiagramModel &model, const PhaseVectorPhase &phase) {
  PhaseVector *vectorToBeFound = new PhaseVector();

  // phase = column in model

  for (int i = 0; i < model.rowCount(); i++) {
    QModelIndex index = model.index(i, static_cast<int>(phase));
    *vectorToBeFound = model.data(index).value<PhaseVector>();
    if (vectorToBeFound->getLabelType() == PhaseVectorType::NOT_DEFINED) {

      // all vectors are stored in known order
      //! \todo
      vectorToBeFound->setLabelType(static_cast<PhaseVectorType>(i));
      switch (vectorToBeFound->getLabelType()) {
      case PhaseVectorType::CURRENT:
        vectorToBeFound = findCurrentVector(
            model.data(model.index(1, static_cast<int>(phase)))
                .value<PhaseVector>(),
            model.data(model.index(2, static_cast<int>(phase)))
                .value<PhaseVector>());
        break;
      case PhaseVectorType::VOLTAGE:
        vectorToBeFound = findCurrentVector(
            model.data(model.index(0, static_cast<int>(phase)))
                .value<PhaseVector>(),
            model.data(model.index(2, static_cast<int>(phase)))
                .value<PhaseVector>());
        break;
      case PhaseVectorType::RESISTENCE:
        vectorToBeFound = findCurrentVector(
            model.data(model.index(0, static_cast<int>(phase)))
                .value<PhaseVector>(),
            model.data(model.index(1, static_cast<int>(phase)))
                .value<PhaseVector>());
        break;
      default:
        break;
      }
      return vectorToBeFound;
    }
  }
  delete vectorToBeFound;
  return nullptr;
}

bool PhaseVectorCalculator::nessesaryVectorsKnown(
    const VectorDiagramModel &model, const PhaseVectorPhase &phase) const {
  return true;
}

PhaseVector *
PhaseVectorCalculator::findCurrentVector(const PhaseVector &voltageVector,
                                         const PhaseVector &resistenceVector) {
  return nullptr;
}

PhaseVector *
PhaseVectorCalculator::findVoltageVector(const PhaseVector &currentVector,
                                         const PhaseVector &resistenceVector) {
  return nullptr;
}

PhaseVector *
PhaseVectorCalculator::findResistenceVector(const PhaseVector &currentVector,
                                            const PhaseVector &voltageVector) {
  return nullptr;
}
