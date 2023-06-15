#include "phasevector.h"

PhaseVector::PhaseVector() {
  _begin = INCORRECT_NUMBER;
  _end = INCORRECT_NUMBER;
  _Label = NOT_DEFINED;
}
PhaseVector::PhaseVector(Coordinates &begin, Coordinates &end) {
  _begin = begin;
  _end = end;
  _Label = NOT_DEFINED;
}
PhaseVector::PhaseVector(Coordinates &begin, Coordinates &end,
                         VectorLabel label) {
  _begin = begin;
  _end = end;
  _Label = label;
}
// std::pair<Coordinates, Coordinates> PhaseVector::getCoordinates() const {
//   return {_Begin, _End};
// }

void PhaseVector::setCoodinates(const Coordinates begin,
                                const Coordinates end) {
  _begin = begin;
  _end = end;
}

void PhaseVector::setCoodinates(const Coordinates end) {
  _begin = {0, 0};
  _end = end;
}

QLineF PhaseVector::getCoordinates() const {
  return {{_begin.x, _begin.y}, {_end.x, _end.y}};
}

void PhaseVector::setLabel(VectorLabel label) { _Label = label; }

VectorLabel PhaseVector::getLabel() const { return _Label; }

std::ostream &operator<<(std::ostream &os, const Coordinates &c) {
  os << "(" << c.x << "; " << c.y << ")";
  return os;
}
std::istream &operator>>(std::istream &is, Coordinates &c) {
  is >> c.x;
  is >> c.y;
  return is;
}

std::ostream &operator<<(std::ostream &os, const PhaseVector &c) {
  if (c._Label == CURRENT) {
    os << "Current" << std::endl;
  } else {
    if (c._Label == VOLTAGE) {
      os << "Voltage" << std::endl;
    } else {
      if (c._Label == RESISTENCE) {
        os << "Resistence" << std::endl;
      }
    }
  }
  os << "\tBegin\t" << c._begin << std::endl << "\tEnd\t" << c._end;
  return os;
}

std::istream &operator>>(std::istream &is, PhaseVector &c) {
  is >> c._begin;
  is >> c._end;
  return is;
}
