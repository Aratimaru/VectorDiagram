#include "VectorParametersCalculator.h"

VectorParametersCalculator::VectorParametersCalculator()
{

}

VectorParametersCalculator::VectorParametersCalculator(ComplexNumberAdapter v, ComplexNumberAdapter c, ComplexNumberAdapter r):
    m_Voltage(v), m_Current(c), m_Resistence(r)
{

}

VectorParametersCalculator::VectorParametersCalculator(ComplexNumberAdapter v, ComplexNumberAdapter c) :
    m_Voltage(v), m_Current(c)
{

}

bool VectorParametersCalculator::evaluateCircuit(){     //TODO: separate numbers form to do proper calcilations
    if(m_Voltage == UNDEFINED_COMPLEX_NUMBER){
        if(!necessaryParametersFound(VOLTAGE)){
            return false;
        }

        if(m_Current.getForm() == false){
            m_Current = m_Current.toExponentialForm();
        }
        if(m_Resistence.getForm() == false){
            m_Resistence = m_Resistence.toExponentialForm();
        }
        m_Voltage = multExp(m_Current, m_Resistence);
    }

    if(m_Current == UNDEFINED_COMPLEX_NUMBER){
        if(!necessaryParametersFound(CURRENT)){
            return false;
        }

        if(m_Voltage.getForm() == false){
            m_Voltage = m_Voltage.toExponentialForm();
        }
        if(m_Resistence.getForm() == false){
            m_Resistence = m_Resistence.toExponentialForm();
        }
        m_Current = divideExp(m_Voltage, m_Resistence);
    }
    return true;
}

void VectorParametersCalculator::setVoltage(ComplexNumberAdapter v)
{
    m_Voltage = v;
}

void VectorParametersCalculator::setCurrent(ComplexNumberAdapter c)
{
    m_Current = c;
}

void VectorParametersCalculator::setResistence(ComplexNumberAdapter r)
{
    m_Resistence = r;
}

ComplexNumberAdapter VectorParametersCalculator::getVoltage()
{
    return m_Voltage;
}

ComplexNumberAdapter VectorParametersCalculator::getCurrent()
{
    return m_Current;
}

ComplexNumberAdapter VectorParametersCalculator::getResistence()
{
    return m_Resistence;
}

bool VectorParametersCalculator::necessaryParametersFound(Parameters value){
    switch (value){
    case VOLTAGE:
    {
        return (m_Current!=UNDEFINED_COMPLEX_NUMBER && m_Resistence!=UNDEFINED_COMPLEX_NUMBER);
        break;
    }
    case CURRENT:
    {
        return (m_Voltage!=UNDEFINED_COMPLEX_NUMBER && m_Resistence!=UNDEFINED_COMPLEX_NUMBER && m_Resistence!=NULL_COMPLEX_NUMBER);
        break;
    }
    case RESISTENCE:
    {
        return (m_Current!=UNDEFINED_COMPLEX_NUMBER && m_Voltage!=UNDEFINED_COMPLEX_NUMBER);
        break;
    }
    default:
    {
        return false;
    }
    }
}
