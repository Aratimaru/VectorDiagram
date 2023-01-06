#include "phasevector.h"

PhaseVector::PhaseVector(float &angle, float &lenght):m_angle(angle), m_lenght(lenght)
{}
std::pair<float, float> PhaseVector::getPolarCoordinates(){
    return std::pair<float, float> {m_angle, m_lenght};
}
std::pair<PhaseVector::CartesianCoordinates, PhaseVector::CartesianCoordinates> PhaseVector::getCartesianCoordinates() const{
    return {m_begin, m_end};
}
