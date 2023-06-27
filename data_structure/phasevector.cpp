#include "phasevector.h"

PhaseVector::PhaseVector() {
  _begin = INCORRECT_NUMBER;
  _end = INCORRECT_NUMBER;
  setLabelType(PhaseVectorType::NOT_DEFINED);
  setLabelPhase(PhaseVectorPhase::NOT_DEFINED);

  _begin.toGeneralForm();
  _end.toGeneralForm();
}
PhaseVector::PhaseVector(const ComplexNumberAdapter &begin,
                         const ComplexNumberAdapter &end) {
  _begin = begin;
  _end = end;
  setLabelType(PhaseVectorType::NOT_DEFINED);
  setLabelPhase(PhaseVectorPhase::NOT_DEFINED);

  _begin.toGeneralForm();
  _end.toGeneralForm();
}

PhaseVector::PhaseVector(const ComplexNumberAdapter &begin,
                         const ComplexNumberAdapter &end, VectorLabel label) {
  _begin = begin;
  _end = end;
  _label = label;

  _begin.toGeneralForm();
  _end.toGeneralForm();
}

PhaseVector::PhaseVector(const ComplexNumberAdapter &begin,
                         const ComplexNumberAdapter &end,
                         const PhaseVectorType type,
                         const PhaseVectorPhase phase) {
  PhaseVector(begin, end);
  setLabelType(type);
  setLabelPhase(phase);

  _begin.toGeneralForm();
  _end.toGeneralForm();
}

PhaseVector::PhaseVector(const ComplexNumberAdapter &begin,
                         const ComplexNumberAdapter &end,
                         const PhaseVectorType type,
                         const PhaseVectorPhase phase,
                         const std::string customName) {
  PhaseVector(begin, end);
  setLabelType(type);
  setLabelPhase(phase);
  setLabelName(customName);

  _begin.toGeneralForm();
  _end.toGeneralForm();
}

PhaseVector::PhaseVector(const ComplexNumberAdapter &end,
                         const PhaseVectorType type,
                         const PhaseVectorPhase phase) {
  setCoodinates(end);
  setLabelType(type);
  setLabelPhase(phase);

  _begin.toGeneralForm();
  _end.toGeneralForm();
}

PhaseVector::PhaseVector(const ComplexNumberAdapter &end,
                         const PhaseVectorType type,
                         const PhaseVectorPhase phase,
                         const std::string customName) {
  setCoodinates(end);
  setLabelType(type);
  setLabelPhase(phase);
  setLabelName(customName);

  _begin.toGeneralForm();
  _end.toGeneralForm();
}
// std::pair<QPointF, QPointF> PhaseVector::getCoordinates() const {
//   return {_Begin, _End};
// }

void PhaseVector::setCoodinates(const ComplexNumberAdapter begin,
                                const ComplexNumberAdapter end) {
  _begin = begin;
  _end = end;

  _begin.toGeneralForm();
  _end.toGeneralForm();
}

void PhaseVector::setCoodinates(const ComplexNumberAdapter end) {
  _begin = {0, 0};
  _end = end;

  _begin.toGeneralForm();
  _end.toGeneralForm();
}

QLineF PhaseVector::getCoordinates() const {
  return {{_begin.real(), _begin.imag()}, {_end.real(), _end.imag()}};
}

void PhaseVector::setLabel(const VectorLabel label) { _label = label; }

void PhaseVector::setLabelType(const PhaseVectorType type) {
  _label.type = type;
}

void PhaseVector::setLabelPhase(const PhaseVectorPhase phase) {
  _label.phase = phase;
}

void PhaseVector::setLabelName(const std::string customName) {
  _label.customName = customName;
}

VectorLabel PhaseVector::getLabel() const { return _label; }

PhaseVectorType PhaseVector::getLabelType() const { return _label.type; }

PhaseVectorPhase PhaseVector::getLabelPhase() const { return _label.phase; }

std::string PhaseVector::getLabelName() const { return _label.customName; }

bool PhaseVector::isEmpty() { return (_begin.isNull()); }

std::ostream &operator<<(std::ostream &os, const PhaseVector &c) {
  if (c._label.type == PhaseVectorType::CURRENT) {
    os << "Current\t";
  } else {
    if (c._label.type == PhaseVectorType::VOLTAGE) {
      os << "Voltage\t";
    } else {
      if (c._label.type == PhaseVectorType::RESISTENCE) {
        os << "Resistence\t";
      }
    }
  }
  os << c._label.customName << '\n';
  os << "\tBegin:\t" << &c._begin << "\t\t"
     << "\tEnd:\t" << &c._end << '\n';
  return os;
}
