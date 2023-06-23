#include "VectorParametersCalculator.h"

VectorParametersCalculator::VectorParametersCalculator() {}

std::vector<PhaseVector> VectorParametersCalculator::calculate(
    PhaseParametersStorage &phaseParametersStorage) {
  std::vector<PhaseVector> phaseVectors;

  calculateVoltageVector(phaseParametersStorage);
  calculateCurrentVector(phaseParametersStorage);

  // transform to general form because PhaseVector stores data in general form
  if (phaseParametersStorage.getCurrent().value != UNDEFINED_COMPLEX_NUMBER &&
      phaseParametersStorage.getVoltage().value != UNDEFINED_COMPLEX_NUMBER) {

    if (phaseParametersStorage.getVoltage().value.getForm() ==
        ComplexNumberForm::EXPONENTIAL) {
      Parameter voltage;
      voltage.value = phaseParametersStorage.getVoltage().value.toGeneralForm();
      phaseParametersStorage.setVoltage(voltage);
    }

    if (phaseParametersStorage.getCurrent().value.getForm() ==
        ComplexNumberForm::EXPONENTIAL) {
      Parameter current;
      current.value = phaseParametersStorage.getCurrent().value.toGeneralForm();
      phaseParametersStorage.setCurrent(current);
    }
  } else {
    return phaseVectors;
  }

  PhaseVector currentVector;
  currentVector.setCoodinates(
      QPointF{phaseParametersStorage.getCurrent().value.real(),
              phaseParametersStorage.getCurrent().value.imag()});
  currentVector.setLabelType(PhaseVectorType::CURRENT);
  PhaseVector voltageVector;
  voltageVector.setCoodinates(
      QPointF{phaseParametersStorage.getVoltage().value.real(),
              phaseParametersStorage.getVoltage().value.imag()});
  voltageVector.setLabelType(PhaseVectorType::VOLTAGE);

  phaseVectors.push_back(voltageVector);
  phaseVectors.push_back(currentVector);
  return phaseVectors;
}

void VectorParametersCalculator::calculateCurrentVector(
    PhaseParametersStorage &phaseParametersStorage) {
  //  if (phaseParametersStorage.getCurrent().value == UNDEFINED_COMPLEX_NUMBER)
  //  {
  //    if (!necessaryParametersFound(phaseParametersStorage,
  //                                  PhaseVectorType::CURRENT)) {
  //      return;
  //    }

  //    // transform to exp form
  //    if (phaseParametersStorage.getVoltage().value.getForm() ==
  //        ComplexNumberForm::GENERAL) {
  //      Parameter voltage;
  //      voltage.value =
  //          phaseParametersStorage.getVoltage().value.toExponentialForm();
  //      phaseParametersStorage.setVoltage(voltage);
  //    }

  //    // transform to exp form
  //    if (phaseParametersStorage.getResistence().value.getForm() ==
  //        ComplexNumberForm::GENERAL) {
  //      Parameter resistence;
  //      resistence.value =
  //          phaseParametersStorage.getResistence().value.toExponentialForm();
  //      phaseParametersStorage.setResistence(resistence);
  //    }

  //    Parameter current;
  //    current.value = divideExp(phaseParametersStorage.getVoltage().value,
  //                              phaseParametersStorage.getResistence().value);
  //    current.value.setForm(ComplexNumberForm::EXPONENTIAL);
  //    phaseParametersStorage.setCurrent(current);
  //  }
}

void VectorParametersCalculator::calculateVoltageVector(
    PhaseParametersStorage &phaseParametersStorage) {

  if (phaseParametersStorage.getVoltage().value == UNDEFINED_COMPLEX_NUMBER) {
    if (!necessaryParametersFound(phaseParametersStorage,
                                  PhaseVectorType::VOLTAGE)) {
      return;
    }

    // transform to exp form
    if (phaseParametersStorage.getCurrent().value.getForm() ==
        ComplexNumberForm::GENERAL) {
      Parameter current;
      current.value =
          phaseParametersStorage.getCurrent().value.toExponentialForm();
      phaseParametersStorage.setCurrent(current);
    }

    // transform to exp form
    if (phaseParametersStorage.getResistence().value.getForm() ==
        ComplexNumberForm::GENERAL) {
      Parameter resistence;
      resistence.value =
          phaseParametersStorage.getResistence().value.toExponentialForm();
      phaseParametersStorage.setResistence(resistence);
    }

    Parameter voltage;
    voltage.value = multExp(phaseParametersStorage.getCurrent().value,
                            phaseParametersStorage.getResistence().value);
    voltage.value.setForm(ComplexNumberForm::EXPONENTIAL);
    phaseParametersStorage.setVoltage(voltage);
  }
}

void VectorParametersCalculator::calculateResistenceVector(
    PhaseParametersStorage &phaseParametersStorage) {
  //! \todo
}

bool VectorParametersCalculator::necessaryParametersFound(
    PhaseParametersStorage &phaseParametersStorage, PhaseVectorType type) {
  switch (type) {
  case PhaseVectorType::VOLTAGE: {
    return (phaseParametersStorage.getCurrent().value !=
                UNDEFINED_COMPLEX_NUMBER &&
            phaseParametersStorage.getResistence().value !=
                UNDEFINED_COMPLEX_NUMBER);
    break;
  }
  case PhaseVectorType::CURRENT: {
    return (
        phaseParametersStorage.getVoltage().value != UNDEFINED_COMPLEX_NUMBER &&
        phaseParametersStorage.getResistence().value !=
            UNDEFINED_COMPLEX_NUMBER &&
        phaseParametersStorage.getResistence().value != NULL_COMPLEX_NUMBER);
    break;
  }
  case PhaseVectorType::RESISTENCE: {
    return (
        phaseParametersStorage.getCurrent().value != UNDEFINED_COMPLEX_NUMBER &&
        phaseParametersStorage.getVoltage().value != UNDEFINED_COMPLEX_NUMBER);
    break;
  }
  default: {
    return false;
  }
  }
}

// void VectorParametersCalculator::convertToUnit(Parameters p, const UnitPrefix
// u)
//{
//     switch (p) {
//     case CURRENT:
//     {
//         if(_Current.value.getForm() == false){     //only for exp form
//             return;
//         }
//         _Current.value.real(_Current.value.real() * pow(10,
//         (int)_Current.prefix - (int)u)); _Current.prefix = u; break;
//     }
//     case VOLTAGE:
//     {
//         if(_Voltage.value.getForm() == false){     //only for exp form
//             return;
//         }
//         _Voltage.value.real(_Voltage.value.real() * pow(10,
//         (int)_Voltage.prefix - (int)u)); _Voltage.prefix = u; break;
//     }
//     case RESISTENCE:
//     {
//         if(_Resistence.value.getForm() == false){     //only for exp form
//             return;
//         }
//         _Resistence.value.real(_Resistence.value.real() * pow(10,
//         (int)_Resistence.prefix - (int)u)); _Resistence.prefix = u; break;
//     }
//     default:
//         break;
//     }
// }

// void VectorParametersCalculator::convertToUnit(Parameter &p, const UnitPrefix
// u)
//{
//     if(p.value.getForm() == false){     //only for exp form
//         return;
//     }
//     p.value.real(p.value.real() * pow(10, ((int)p.prefix - (int)u)));
//     p.prefix = u;
// }

// void VectorParametersCalculator::convertToSmallerUnit(Parameter &p1,
// Parameter &p2)
//{

//}
