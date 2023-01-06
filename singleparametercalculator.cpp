#include "singleparametercalculator.h"

SingleParameterCalculator::SingleParameterCalculator(float v, float c, float r):
    m_Voltage(v), m_Current(c), m_Resistence(r)
{

}

bool SingleParameterCalculator::evaluateCircuit(){
    return true;
}
