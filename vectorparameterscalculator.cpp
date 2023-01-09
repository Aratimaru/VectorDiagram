#include "VectorParametersCalculator.h"

VectorParametersCalculator::VectorParametersCalculator()
{

}

VectorParametersCalculator::VectorParametersCalculator(Parameter v, Parameter c, Parameter r):
    m_Voltage(v), m_Current(c), m_Resistence(r)
{

}

VectorParametersCalculator::VectorParametersCalculator(Parameter v, Parameter c) :
    m_Voltage(v), m_Current(c)
{

}

bool VectorParametersCalculator::calculate(){
    if(m_Voltage.parameter == UNDEFINED_COMPLEX_NUMBER){
        if(!necessaryParametersFound(VOLTAGE)){
            return false;
        }

        if(m_Current.parameter.getForm() == false){
            m_Current.parameter = m_Current.parameter.toExponentialForm();
        }
        if(m_Resistence.parameter.getForm() == false){
            m_Resistence.parameter = m_Resistence.parameter.toExponentialForm();
        }
        m_Voltage.parameter = multExp(m_Current.parameter, m_Resistence.parameter);
    }

    if(m_Current.parameter == UNDEFINED_COMPLEX_NUMBER){
        if(!necessaryParametersFound(CURRENT)){
            return false;
        }

        if(m_Voltage.parameter.getForm() == false){
            m_Voltage.parameter = m_Voltage.parameter.toExponentialForm();
        }
        if(m_Resistence.parameter.getForm() == false){
            m_Resistence.parameter = m_Resistence.parameter.toExponentialForm();
        }
        m_Current.parameter = divideExp(m_Voltage.parameter, m_Resistence.parameter);
    }
    return true;
}

void VectorParametersCalculator::setVoltage(const Parameter& v)
{
    m_Voltage = v;
}

void VectorParametersCalculator::setCurrent(const Parameter& c)
{
    m_Current = c;
}

void VectorParametersCalculator::setResistence(const Parameter& r)
{
    m_Resistence = r;
}

Parameter VectorParametersCalculator::getVoltage() const
{
    return m_Voltage;
}

Parameter VectorParametersCalculator::getCurrent() const
{
    return m_Current;
}

Parameter VectorParametersCalculator::getResistence() const
{
    return m_Resistence;
}

void VectorParametersCalculator::sentResults(PhaseVector& currentVector, PhaseVector& voltageVector)
{
    ComplexNumberAdapter voltage = m_Voltage.parameter.toGeneralForm();
    ComplexNumberAdapter current = m_Current.parameter.toGeneralForm();

    currentVector.setCoodinates({current.real(), current.imag()});
    voltageVector.setCoodinates({voltage.real(), voltage.imag()});
}

bool VectorParametersCalculator::necessaryParametersFound(Parameters value){
    switch (value){
    case VOLTAGE:
    {
        return (m_Current.parameter!=UNDEFINED_COMPLEX_NUMBER && m_Resistence.parameter!=UNDEFINED_COMPLEX_NUMBER);
        break;
    }
    case CURRENT:
    {
        return (m_Voltage.parameter!=UNDEFINED_COMPLEX_NUMBER && m_Resistence.parameter!=UNDEFINED_COMPLEX_NUMBER && m_Resistence.parameter!=NULL_COMPLEX_NUMBER);
        break;
    }
    case RESISTENCE:
    {
        return (m_Current.parameter!=UNDEFINED_COMPLEX_NUMBER && m_Voltage.parameter!=UNDEFINED_COMPLEX_NUMBER);
        break;
    }
    default:
    {
        return false;
    }
    }
}

void VectorParametersCalculator::convertToUnit(Parameters p, const UnitPrefix u)
{
    switch (p) {
    case CURRENT:
    {
        if(m_Current.parameter.getForm() == false){     //only for exp form
            return;
        }
        m_Current.parameter.real(m_Current.parameter.real() * pow(10, (int)m_Current.prefix - (int)u));
        m_Current.prefix = u;
        break;
    }
    case VOLTAGE:
    {
        if(m_Voltage.parameter.getForm() == false){     //only for exp form
            return;
        }
        m_Voltage.parameter.real(m_Voltage.parameter.real() * pow(10, (int)m_Voltage.prefix - (int)u));
        m_Voltage.prefix = u;
        break;
    }
    case RESISTENCE:
    {
        if(m_Resistence.parameter.getForm() == false){     //only for exp form
            return;
        }
        m_Resistence.parameter.real(m_Resistence.parameter.real() * pow(10, (int)m_Resistence.prefix - (int)u));
        m_Resistence.prefix = u;
        break;
    }
    default:
        break;
    }
}

void VectorParametersCalculator::convertToUnit(Parameter &p, const UnitPrefix u)
{
    if(p.parameter.getForm() == false){     //only for exp form
        return;
    }
    p.parameter.real(p.parameter.real() * pow(10, ((int)p.prefix - (int)u)));
    p.prefix = u;
}

void VectorParametersCalculator::convertToSmallerUnit(Parameter &p1, Parameter &p2)
{

}

std::ostream& operator<<(std::ostream& os, const Parameter& p){
    os << "(" << p.parameter << "; " << p.prefix <<")";
    return os;
}
std::istream & operator >> (std::istream &is,  Parameter &p){
    is >> p.parameter;
    //TODO: input for unit
    return is;
}
