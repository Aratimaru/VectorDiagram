#include "phaseparametersstorage.h"

PhaseParametersStorage::PhaseParametersStorage() {}

PhaseParametersStorage::PhaseParametersStorage(Parameter v, Parameter c)
    : _voltage(v), _current(c) {}

PhaseParametersStorage::PhaseParametersStorage(Parameter v, Parameter c,
                                               Parameter r)
    : _voltage(v), _current(c), _resistence(r) {}

void PhaseParametersStorage::setVoltage(const Parameter &v) { _voltage = v; }

void PhaseParametersStorage::setCurrent(const Parameter &c) { _current = c; }

void PhaseParametersStorage::setResistence(const Parameter &r) {
  _resistence = r;
}

Parameter PhaseParametersStorage::getVoltage() const { return _voltage; }

Parameter PhaseParametersStorage::getCurrent() const { return _current; }

Parameter PhaseParametersStorage::getResistence() const { return _resistence; }

std::ostream &operator<<(std::ostream &os, const Parameter &p) {
  os << "(" << p.value << "; " << p.prefix << ")";
  return os;
}
std::istream &operator>>(std::istream &is, Parameter &p) {
  is >> p.value;
  // TODO: input for unit
  return is;
}
