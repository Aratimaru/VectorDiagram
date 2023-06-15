#include "phaseparametersstorage.h"

PhaseParametersStorage::PhaseParametersStorage() {}

PhaseParametersStorage::PhaseParametersStorage(Parameter v, Parameter c)
    : _voltage(v), _current(c) {
  //    _Voltage.name = VOLTAGE;
  //    _Current.name = CURRENT;
}

PhaseParametersStorage::PhaseParametersStorage(Parameter v, Parameter c,
                                               Parameter r)
    : _voltage(v), _current(c), _resistence(r) {
  //    _Voltage.name = VOLTAGE;
  //    _Current.name = CURRENT;
  //    _Resistence.name = RESISTENCE;
}

void PhaseParametersStorage::setVoltage(const Parameter &v) {
  _voltage = v;
  //    _Voltage.name = VOLTAGE;
}

void PhaseParametersStorage::setCurrent(const Parameter &c) {
  _current = c;
  //    _Current.name = CURRENT;
}

void PhaseParametersStorage::setResistence(const Parameter &r) {
  _resistence = r;
  //    _Resistence.name = RESISTENCE;
}

Parameter PhaseParametersStorage::getVoltage() const { return _voltage; }

Parameter PhaseParametersStorage::getCurrent() const { return _current; }

Parameter PhaseParametersStorage::getResistence() const { return _resistence; }

std::ostream &operator<<(std::ostream &os, const Parameter &p) {
  os << "(" << p.parameter << "; " << p.prefix << ")";
  return os;
}
std::istream &operator>>(std::istream &is, Parameter &p) {
  is >> p.parameter;
  // TODO: input for unit
  return is;
}
