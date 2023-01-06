#ifndef SINGLEPARAMETERCALCULATOR_H
#define SINGLEPARAMETERCALCULATOR_H
#include "calculator.h"

class SingleParameterCalculator : public Calculator
{
public:
    SingleParameterCalculator();
    SingleParameterCalculator(float v, float c, float r);
    bool evaluateCircuit() override;
    void setVoltage(float v);
    void setCurrent(float c);
    void setResistence(float r);
private:
    float m_Voltage;
    float m_Current;
    float m_Resistence;
};

#endif // SINGLEPARAMETERCALCULATOR_H
