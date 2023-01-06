#ifndef PHASEVECTOR_H
#define PHASEVECTOR_H
#include <utility>
#include "complexnumberadapter.h"

class PhaseVector
{
private:
    struct CartesianCoordinates{
        float x;
        float y;
    };
public:
    PhaseVector(float &angle, float &lenght);
    std::pair<float, float> getPolarCoordinates();
    std::pair<CartesianCoordinates, CartesianCoordinates> getCartesianCoordinates() const;
private:
    float m_angle;
    float m_lenght;
    CartesianCoordinates m_begin;
    CartesianCoordinates m_end;
};

#endif // PHASEVECTOR_H
