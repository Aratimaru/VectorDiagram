#include "VectorParametersCalculator.h"

VectorParametersCalculator::VectorParametersCalculator()
{

}

VectorParametersCalculator::VectorParametersCalculator(float v, float c, float r):
    m_Voltage(v), m_Current(c), m_Resistence(r)
{

}

VectorParametersCalculator::VectorParametersCalculator(float v, float c) :
    m_Voltage(v), m_Current(c)
{

}

bool VectorParametersCalculator::evaluateCircuit(){
    if(m_Voltage == FLT_MAX){
        if(!necessaryParametersFound(VOLTAGE)){
            return false;
        }

        m_Voltage = m_Current*m_Resistence;
    }

    if(m_Current == FLT_MAX){
        if(!necessaryParametersFound(CURRENT)){
            return false;
        }

        m_Current = m_Voltage/m_Resistence;
    }
    return true;
}

void VectorParametersCalculator::setVoltage(float v)
{
    m_Voltage = v;
}

void VectorParametersCalculator::setCurrent(float c)
{
    m_Current = c;
}

void VectorParametersCalculator::setResistence(float r)
{
    m_Resistence = r;
}

float VectorParametersCalculator::getVoltage()
{
    return m_Voltage;
}

float VectorParametersCalculator::getCurrent()
{
    return m_Current;
}

float VectorParametersCalculator::getResistence()
{
    return m_Resistence;
}

bool VectorParametersCalculator::necessaryParametersFound(Parameters value){
    switch (value){
    case VOLTAGE:
    {
        return (m_Current!=FLT_MAX && m_Resistence!=FLT_MAX);
        break;
    }
    case CURRENT:
    {
        return (m_Voltage!=FLT_MAX && m_Resistence!=FLT_MAX && m_Resistence!=0);
        break;
    }
    case RESISTENCE:
    {
        return (m_Current!=FLT_MAX && m_Voltage!=FLT_MAX);
        break;
    }
    default:
    {
        return false;
    }
    }
}
