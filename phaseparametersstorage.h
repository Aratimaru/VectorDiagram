#ifndef PHASEPARAMETERSSTORAGE_H
#define PHASEPARAMETERSSTORAGE_H
#include "complexnumberadapter.h"

// enum ParameterLabel{
//     VOLTAGE = 0,
//     CURRENT,
//     RESISTENCE,
//     NOT_DEFINED
// };

enum UnitPrefix {
  PICO = -12,
  NANO = -9,
  MICRO = -6,
  MILLI = -3,
  STANDART = 1,
  KILO = 3,
  MEGA = 6,
  GIGA = 9,
  TERA = 12
};

struct Parameter {
  ComplexNumberAdapter parameter =
      ComplexNumberAdapter(UNDEFINED_COMPLEX_NUMBER);
  UnitPrefix prefix = STANDART;
  //    ParameterLabel name = NOT_DEFINED;
  friend std::ostream &operator<<(std::ostream &os, const Parameter &c);
  friend std::istream &operator>>(std::istream &is, Parameter &c);
};

class PhaseParametersStorage {
public:
  PhaseParametersStorage();
  PhaseParametersStorage(Parameter v, Parameter c);
  PhaseParametersStorage(Parameter v, Parameter c, Parameter r);

  void setVoltage(const Parameter &v);
  void setCurrent(const Parameter &c);
  void setResistence(const Parameter &r);
  Parameter getVoltage() const;    // in exp form
  Parameter getCurrent() const;    // in exp form
  Parameter getResistence() const; // in exp form
private:
  Parameter _voltage;
  Parameter _current;
  Parameter _resistence;
};

#endif // PHASEPARAMETERSSTORAGE_H
