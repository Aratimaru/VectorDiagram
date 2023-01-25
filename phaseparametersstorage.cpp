#include "phaseparametersstorage.h"

PhaseParametersStorage::PhaseParametersStorage()
{

}

PhaseParametersStorage::PhaseParametersStorage(Parameter v, Parameter c):
    m_Voltage(v), m_Current(c)
{
//    m_Voltage.name = VOLTAGE;
//    m_Current.name = CURRENT;
}

PhaseParametersStorage::PhaseParametersStorage(Parameter v, Parameter c, Parameter r):
    m_Voltage(v), m_Current(c), m_Resistence(r)
{
//    m_Voltage.name = VOLTAGE;
//    m_Current.name = CURRENT;
//    m_Resistence.name = RESISTENCE;
}


void PhaseParametersStorage::setVoltage(const Parameter& v)
{
    m_Voltage = v;
//    m_Voltage.name = VOLTAGE;
}

void PhaseParametersStorage::setCurrent(const Parameter& c)
{
    m_Current = c;
//    m_Current.name = CURRENT;
}

void PhaseParametersStorage::setResistence(const Parameter& r)
{
    m_Resistence = r;
//    m_Resistence.name = RESISTENCE;
}

Parameter PhaseParametersStorage::getVoltage() const
{
    return m_Voltage;
}

Parameter PhaseParametersStorage::getCurrent() const
{
    return m_Current;
}

Parameter PhaseParametersStorage::getResistence() const
{
    return m_Resistence;
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
