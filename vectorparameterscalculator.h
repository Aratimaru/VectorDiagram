#ifndef VectorParametersCalculator_H
#define VectorParametersCalculator_H
#include "calculator.h"
#include <cstddef>
#include <limits>

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
    VectorParametersCalculator(float v, float c, float r);
    VectorParametersCalculator(float v, float c);
    bool evaluateCircuit() override;
    void setVoltage(float v);
    void setCurrent(float c);
    void setResistence(float r);
    float getVoltage();
    float getCurrent();
    float getResistence();
private:
    float m_Voltage = FLT_MAX;
    float m_Current = FLT_MAX;
    float m_Resistence = FLT_MAX;
};

#endif // VectorParametersCalculator_H
