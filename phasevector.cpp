#include "phasevector.h"

PhaseVector::PhaseVector(){
    m_Begin = INCORRECT_NUMBER;
    m_End = INCORRECT_NUMBER;
}
PhaseVector::PhaseVector(Coordinates &begin, Coordinates &end){
    m_Begin = begin;
    m_End = end;
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
    os << std::endl << "Begin\t" << c.m_Begin << std::endl << "End\t" << c.m_End;
    return os;
}

std::istream & operator >> (std::istream &is,  PhaseVector &c){
    is >> c.m_Begin;
    is >> c.m_End;
    return is;
}
