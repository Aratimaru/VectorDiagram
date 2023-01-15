#include "phasevector.h"

PhaseVector::PhaseVector(){
    m_Begin = INCORRECT_NUMBER;
    m_End = INCORRECT_NUMBER;
    m_Label = NOT_DEFINED;
}
PhaseVector::PhaseVector(Coordinates &begin, Coordinates &end){
    m_Begin = begin;
    m_End = end;
    m_Label = NOT_DEFINED;
}
PhaseVector::PhaseVector(Coordinates &begin, Coordinates &end, VectorLabel label){
    m_Begin = begin;
    m_End = end;
    m_Label = label;
}
std::pair<Coordinates, Coordinates> PhaseVector::getCoordinates() const{
    return {m_Begin, m_End};
}
void PhaseVector::setCoodinates(const Coordinates begin, const Coordinates end){
    m_Begin = begin;
    m_End = end;
}
void PhaseVector::setCoodinates(const Coordinates end){
    m_Begin = {0, 0};
    m_End = end;
}

void PhaseVector::setLabel(VectorLabel label)
{
    m_Label = label;
}

VectorLabel PhaseVector::getLabel() const
{
    return m_Label;
}

std::ostream& operator<<(std::ostream& os, const Coordinates& c){
    os << "(" << c.x << "; " << c.y <<")";
    return os;
}
std::istream & operator >> (std::istream &is,  Coordinates &c){
    is >> c.x;
    is >> c.y;
    return is;
}

std::ostream& operator<<(std::ostream& os, const PhaseVector& c){
    if(c.m_Label == CURRENT){
        os << "Current" << std::endl;
    }else{
        if (c.m_Label == VOLTAGE){
            os << "Voltage" << std::endl;
        }else{
            if(c.m_Label == RESISTENCE){
                os << "Resistence" << std::endl;
            }
        }
    }
    os << "\tBegin\t" << c.m_Begin << std::endl << "\tEnd\t" << c.m_End;
    return os;
}

std::istream & operator >> (std::istream &is,  PhaseVector &c){
    is >> c.m_Begin;
    is >> c.m_End;
    return is;
}
