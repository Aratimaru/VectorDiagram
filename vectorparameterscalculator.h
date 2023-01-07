#ifndef VectorParametersCalculator_H
#define VectorParametersCalculator_H
#include "calculator.h"
#include <cstddef>
#include <limits>
#include "complexnumberadapter.h"

class VectorParametersCalculator : public Calculator
{
public:
    enum Parameters{
        VOLTAGE = 0,
        CURRENT,
        RESISTENCE
    };
private:
    bool necessaryParametersFound(Parameters value);
public:
    VectorParametersCalculator();
    VectorParametersCalculator(ComplexNumberAdapter v, ComplexNumberAdapter c, ComplexNumberAdapter r);
    VectorParametersCalculator(ComplexNumberAdapter v, ComplexNumberAdapter c);
    bool evaluateCircuit() override;
    void setVoltage(ComplexNumberAdapter v);
    void setCurrent(ComplexNumberAdapter c);
    void setResistence(ComplexNumberAdapter r);
    ComplexNumberAdapter getVoltage();
    ComplexNumberAdapter getCurrent();
    ComplexNumberAdapter getResistence();
private:
    ComplexNumberAdapter m_Voltage{UNDEFINED_COMPLEX_NUMBER};
    ComplexNumberAdapter m_Current{UNDEFINED_COMPLEX_NUMBER};
    ComplexNumberAdapter m_Resistence{UNDEFINED_COMPLEX_NUMBER};
};

#endif // VectorParametersCalculator_H
