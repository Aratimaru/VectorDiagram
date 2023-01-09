#ifndef VectorParametersCalculator_H
#define VectorParametersCalculator_H
#include "calculator.h"
#include "complexnumberadapter.h"
#include "phasevector.h"
enum Parameters{
    VOLTAGE = 0,
    CURRENT,
    RESISTENCE
};

enum UnitPrefix {
    PICO  = -12,
    NANO = -9,
    MICRO = -6,
    MILLI = -3,
    STANDART = 1,
    KILO = 3,
    MEGA = 6,
    GIGA = 9,
    TERA = 12
};

struct Parameter{
    ComplexNumberAdapter parameter = ComplexNumberAdapter(UNDEFINED_COMPLEX_NUMBER);
    UnitPrefix prefix = STANDART;
    friend std::ostream& operator<<(std::ostream& os, const Parameter& c);        //need to find the right place for it
    friend std::istream & operator >> (std::istream &is,  Parameter &c);
};

class VectorParametersCalculator : public Calculator
{
private:
    bool necessaryParametersFound(Parameters value);


public:
    VectorParametersCalculator();
    VectorParametersCalculator(Parameter v, Parameter c, Parameter r);
    VectorParametersCalculator(Parameter v, Parameter c);
    bool calculate() override;
    void setVoltage(const Parameter& v);
    void setCurrent(const Parameter& c);
    void setResistence(const Parameter& r);
    Parameter getVoltage() const;        //in exp form
    Parameter getCurrent() const;        //in exp form
    Parameter getResistence() const;     //in exp form

    void convertToUnit (Parameters p, const UnitPrefix u);
    void convertToUnit (Parameter& p, const UnitPrefix u);     //TODO: change to private
    void convertToSmallerUnit(Parameter& p1, Parameter& p2);
    void convertToBiggerUnit(Parameter& p1, Parameter& p2);

    void sentResults(PhaseVector& currentVector, PhaseVector& voltageVector);           //TODO: maybe need to send data to Model
private:
    Parameter m_Voltage;
    Parameter m_Current;
    Parameter m_Resistence;
};

#endif // VectorParametersCalculator_H
