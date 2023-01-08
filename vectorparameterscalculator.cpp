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

bool VectorParametersCalculator::calculate(){
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

void VectorParametersCalculator::setVoltage(const ComplexNumberAdapter& v)
{
    m_Voltage = v;
}

void VectorParametersCalculator::setCurrent(const ComplexNumberAdapter& c)
{
    m_Current = c;
}

void VectorParametersCalculator::setResistence(const ComplexNumberAdapter& r)
{
    m_Resistence = r;
}

ComplexNumberAdapter VectorParametersCalculator::getVoltage() const
{
    return m_Voltage;
}

ComplexNumberAdapter VectorParametersCalculator::getCurrent() const
{
    return m_Current;
}

ComplexNumberAdapter VectorParametersCalculator::getResistence() const
{
    return m_Resistence;
}

void VectorParametersCalculator::sentResults(PhaseVector& currentVector, PhaseVector& voltageVector)
{
    ComplexNumberAdapter voltage = m_Voltage.toGeneralForm();
    ComplexNumberAdapter current = m_Current.toGeneralForm();

    currentVector.setCoodinates({current.real(), current.imag()});
    voltageVector.setCoodinates({voltage.real(), voltage.imag()});
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
