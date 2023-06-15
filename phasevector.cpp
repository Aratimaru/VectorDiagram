#include "phasevector.h"

PhaseVector::PhaseVector() {
  _begin = INCORRECT_NUMBER;
  _end = INCORRECT_NUMBER;
  setLabelType(PhaseVectorType::NOT_DEFINED);
  setLabelPhase(PhaseVectorPhase::NOT_DEFINED);
}
PhaseVector::PhaseVector(QPointF &begin, QPointF &end) {
  _begin = begin;
  _end = end;
  setLabelType(PhaseVectorType::NOT_DEFINED);
  setLabelPhase(PhaseVectorPhase::NOT_DEFINED);
}
PhaseVector::PhaseVector(QPointF &begin, QPointF &end,
                         VectorLabel label) {
  _begin = begin;
  _end = end;
  _label = label;
}
// std::pair<QPointF, QPointF> PhaseVector::getCoordinates() const {
//   return {_Begin, _End};
// }

void PhaseVector::setCoodinates(const QPointF begin,
                                const QPointF end) {
  _begin = begin;
  _end = end;
}

void PhaseVector::setCoodinates(const QPointF end) {
  _begin = {0, 0};
  _end = end;
}

QLineF PhaseVector::getCoordinates() const {
  return {{_begin.x(), _begin.y()}, {_end.x(), _end.y()}};
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

// std::ostream &operator<<(std::ostream &os, const QPointF &c) {
//   os << "(" << c.x << "; " << c.y << ")";
//   return os;
// }
// std::istream &operator>>(std::istream &is, QPointF &c) {
//   is >> c.x;
//   is >> c.y;
//   return is;
// }

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

// std::istream &operator>>(std::istream &is, PhaseVector &c) {
//   is >> c._begin;
//   is >> c._end;
//   return is;
// }
