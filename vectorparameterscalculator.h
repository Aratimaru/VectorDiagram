#ifndef VectorParametersCalculator_H
#define VectorParametersCalculator_H
#include "calculator.h"
#include "complexnumberadapter.h"
#include "phasevector.h"

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
    bool calculate() override;
    void setVoltage(const ComplexNumberAdapter& v);
    void setCurrent(const ComplexNumberAdapter& c);
    void setResistence(const ComplexNumberAdapter& r);
    ComplexNumberAdapter getVoltage() const;        //in exp form
    ComplexNumberAdapter getCurrent() const;        //in exp form
    ComplexNumberAdapter getResistence() const;     //in exp form

    void sentResults(PhaseVector& currentVector, PhaseVector& voltageVector);           //TODO: maybe need to send data to Model
private:
    ComplexNumberAdapter m_Voltage{UNDEFINED_COMPLEX_NUMBER};
    ComplexNumberAdapter m_Current{UNDEFINED_COMPLEX_NUMBER};
    ComplexNumberAdapter m_Resistence{UNDEFINED_COMPLEX_NUMBER};
};

#endif // VectorParametersCalculator_H
