#include "phasevector.h"

PhaseVector::PhaseVector(){

}
PhaseVector::PhaseVector(Coordinates &begin, Coordinates &end){
    m_Begin = begin;
    m_End = end;
}
std::pair<PhaseVector::Coordinates, PhaseVector::Coordinates> PhaseVector::getCoordinates() const{
    return {m_Begin, m_End};
}
void PhaseVector::setCoodinates(const Coordinates begin, const Coordinates end){
    m_Begin = begin;
    m_End = end;
}
void PhaseVector::setCoodinates(const Coordinates end){
    m_End = end;
}

std::ostream& operator<<(std::ostream& os, const PhaseVector::Coordinates& c){
    os << "(" << c.x << "; " << c.y <<")";
    return os;
}
std::istream & operator >> (std::istream &is,  PhaseVector::Coordinates &c){
    is >> c.x;
    is >> c.y;
    return is;
}
