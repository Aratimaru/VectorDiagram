#include "phasevector.h"

PhaseVector::PhaseVector()
    : PhaseVector({0, 0}, {0, 0}, PhaseVectorType::NOT_DEFINED,
                  PhaseVectorPhase::NOT_DEFINED, "") {}

PhaseVector::PhaseVector(const ComplexNumberAdapter &begin,
                         const ComplexNumberAdapter &end, VectorLabel label)
    : PhaseVector(begin, end, label.type, label.phase, label.customName) {}

PhaseVector::PhaseVector(const ComplexNumberAdapter &begin,
                         const ComplexNumberAdapter &end,
                         const PhaseVectorType type,
                         const PhaseVectorPhase phase,
                         const QString customName) {
  _begin = begin;
  _end = end;
  setLabelType(type);
  setLabelPhase(phase);
  setLabelName(customName);

  _begin = _begin.toGeneralForm();
  _end = _end.toGeneralForm();
}

PhaseVector::PhaseVector(const ComplexNumberAdapter &end,
                         const PhaseVectorType type,
                         const PhaseVectorPhase phase, const QString customName)
    : PhaseVector({0, 0}, end, type, phase, customName) {}

PhaseVector::PhaseVector(const PhaseVector &other) {
  this->_begin = other._begin;
  this->_end = other._end;
  this->_label = other._label;

  _begin = _begin.toGeneralForm();
  _end = _end.toGeneralForm();
}

void PhaseVector::setCoodinates(const ComplexNumberAdapter begin,
                                const ComplexNumberAdapter end) {
  _begin = begin;
  _end = end;

  _begin.toGeneralForm();
  _end.toGeneralForm();
}

void PhaseVector::setCoodinates(const ComplexNumberAdapter end) {
  _begin = QPointF{0, 0};
  _end = end;

  _begin.toGeneralForm();
  _end.toGeneralForm();
}

ComplexNumberLine PhaseVector::getCoordinates() const { return {_begin, _end}; }

void PhaseVector::setLabel(const VectorLabel label) { _label = label; }

void PhaseVector::setLabelType(const PhaseVectorType type) {
  _label.type = type;
}

void PhaseVector::setLabelPhase(const PhaseVectorPhase phase) {
  _label.phase = phase;
}

void PhaseVector::setLabelName(const QString customName) {
  _label.customName = customName;
}

void PhaseVector::setLabelNameFromTypeAndPhase() {
  QString name = PhaseVectorTypeToString() + PhaseVectorPhaseToString();
  this->setLabelName(name);
}

VectorLabel PhaseVector::getLabel() const { return _label; }

PhaseVectorType PhaseVector::getLabelType() const { return _label.type; }

PhaseVectorPhase PhaseVector::getLabelPhase() const { return _label.phase; }

QString PhaseVector::getLabelName() const { return _label.customName; }

QString PhaseVector::PhaseVectorTypeToString() {
  QString result{};

  switch (this->getLabelType()) {
  case PhaseVectorType::CURRENT:
    result = "I";
    break;
  case PhaseVectorType::VOLTAGE:
    result = "U";
    break;
  case PhaseVectorType::RESISTENCE:
    result = "R";
    break;
  default:
    qDebug() << Q_FUNC_INFO << "Type is invalid" << '\n';
    break;
  }

  return result;
}

QString PhaseVector::PhaseVectorPhaseToString(bool upperCase) {
  QString result{};

  switch (this->getLabelPhase()) {
  case PhaseVectorPhase::PHASE_A:
    result = "a";
    break;
  case PhaseVectorPhase::PHASE_B:
    result = "b";
    break;
  case PhaseVectorPhase::PHASE_C:
    result = "c";
    break;
  default:
    qDebug() << Q_FUNC_INFO << "Phase is invalid" << '\n';
    break;
  }

  if (upperCase) {
    result = result.toUpper();
  }
  return result;
}

bool PhaseVector::isEmpty() { return (_begin.isNull()); }

int PhaseVector::length() const { return QLineF(_begin, _end).length(); }

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
  os << c._label.customName.toStdString() << '\n';
  os << "\tBegin:\t" << &c._begin << "\t\t"
     << "\tEnd:\t" << &c._end << '\n';
  return os;
}
