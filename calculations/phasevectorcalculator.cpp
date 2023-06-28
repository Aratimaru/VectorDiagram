#include "phasevectorcalculator.h"

PhaseVectorCalculator::PhaseVectorCalculator() {}

bool PhaseVectorCalculator::calculate(VectorDiagramModel &model) {
  (void)model;
  return true;
}

PhaseVector *PhaseVectorCalculator::findMissingVectorForOnePhase(
    const VectorDiagramModel &model, const PhaseVectorPhase &phase) {
  PhaseVector *vectorToBeFound = new PhaseVector();

  // phase = column in model

  for (int i = 0; i < model.rowCount(); i++) {
    QModelIndex index = model.index(i, static_cast<int>(phase));
    *vectorToBeFound = model.data(index).value<PhaseVector>();
    if (vectorToBeFound->getLabelType() == PhaseVectorType::NOT_DEFINED) {

      // all vectors are stored in known order
      switch (static_cast<PhaseVectorType>(i)) {
      case PhaseVectorType::CURRENT:
        vectorToBeFound = findCurrentVector(
            model.data(model.index(1, static_cast<int>(phase)))
                .value<PhaseVector>(),
            model.data(model.index(2, static_cast<int>(phase)))
                .value<PhaseVector>());
        break;
      case PhaseVectorType::VOLTAGE:
        vectorToBeFound = findVoltageVector(
            model.data(model.index(0, static_cast<int>(phase)))
                .value<PhaseVector>(),
            model.data(model.index(2, static_cast<int>(phase)))
                .value<PhaseVector>());
        break;
      case PhaseVectorType::RESISTENCE:
        vectorToBeFound = findResistenceVector(
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

PhaseVector *
PhaseVectorCalculator::findCurrentVector(const PhaseVector &voltageVector,
                                         const PhaseVector &resistenceVector) {
  if (voltageVector.getLabelPhase() != resistenceVector.getLabelPhase()) {
    throw("Vectors must be for the same phase");
    return nullptr;
  }

  PhaseVector *currentVector = new PhaseVector;
  *currentVector =
      PhaseVectorCalculator::divExp(voltageVector, resistenceVector);

  currentVector->setLabelPhase(voltageVector.getLabelPhase());
  currentVector->setLabelType(PhaseVectorType::CURRENT);
  return currentVector;
}

PhaseVector *
PhaseVectorCalculator::findVoltageVector(const PhaseVector &currentVector,
                                         const PhaseVector &resistenceVector) {
  if (currentVector.getLabelPhase() != resistenceVector.getLabelPhase()) {
    throw("Vectors must be for the same phase");
    return nullptr;
  }

  PhaseVector *voltageVector = new PhaseVector;
  *voltageVector =
      PhaseVectorCalculator::multExp(currentVector, resistenceVector);

  voltageVector->setLabelPhase(currentVector.getLabelPhase());
  voltageVector->setLabelType(PhaseVectorType::VOLTAGE);
  return voltageVector;
}

PhaseVector *
PhaseVectorCalculator::findResistenceVector(const PhaseVector &currentVector,
                                            const PhaseVector &voltageVector) {
  if (currentVector.getLabelPhase() != voltageVector.getLabelPhase()) {
    throw("Vectors must be for the same phase");
    return nullptr;
  }

  PhaseVector *resistenceVector = new PhaseVector;
  *resistenceVector =
      PhaseVectorCalculator::divExp(currentVector, voltageVector);

  resistenceVector->setLabelPhase(currentVector.getLabelPhase());
  resistenceVector->setLabelType(PhaseVectorType::RESISTENCE);
  return resistenceVector;
}

PhaseVector PhaseVectorCalculator::multExp(const PhaseVector &v1,
                                           const PhaseVector &v2) {
  PhaseVector v1Exp = v1; // to not lose other parameters
  PhaseVector v2Exp = v2;
  v1Exp.setCoodinates(v1.getCoordinates().first.toExponentialForm(),
                      v1.getCoordinates().second.toExponentialForm());
  v2Exp.setCoodinates(v2.getCoordinates().first.toExponentialForm(),
                      v2.getCoordinates().second.toExponentialForm());

  PhaseVector result;
  result.setCoodinates(
      ComplexNumberAdapter::multExp(v1Exp.getCoordinates().first,
                                    v2Exp.getCoordinates().first),
      ComplexNumberAdapter::multExp(v1Exp.getCoordinates().second,
                                    v2Exp.getCoordinates().second));
  result.getCoordinates().first.toGeneralForm();
  result.getCoordinates().second.toGeneralForm();
  return result;
}

PhaseVector PhaseVectorCalculator::divExp(const PhaseVector &v1,
                                          const PhaseVector &v2) {
  PhaseVector v1Exp = v1; // to not lose other parameters
  PhaseVector v2Exp = v2;
  v1Exp.setCoodinates(v1.getCoordinates().first.toExponentialForm(),
                      v1.getCoordinates().second.toExponentialForm());
  v2Exp.setCoodinates(v2.getCoordinates().first.toExponentialForm(),
                      v2.getCoordinates().second.toExponentialForm());

  PhaseVector result;
  result.setCoodinates(
      ComplexNumberAdapter::divExp(v1Exp.getCoordinates().first,
                                   v2Exp.getCoordinates().first),
      ComplexNumberAdapter::divExp(v1Exp.getCoordinates().second,
                                   v2Exp.getCoordinates().second));
  result.getCoordinates().first.toGeneralForm();
  result.getCoordinates().second.toGeneralForm();
  return result;
}
