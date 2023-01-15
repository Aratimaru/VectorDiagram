#ifndef PHASEVECTOR_H
#define PHASEVECTOR_H
#include <utility>
#include <iostream>
#define INCORRECT_NUMBER {FLT_MAX, FLT_MAX}

struct Coordinates{
    float x;
    float y;
    friend std::ostream& operator<<(std::ostream& os, const Coordinates& c);
    friend std::istream & operator >> (std::istream &is,  Coordinates &c);
};

class PhaseVector       //stores data in general form
{
private:
public:
    PhaseVector();
    PhaseVector(Coordinates &begin, Coordinates &end);
    std::pair<Coordinates, Coordinates> getCoordinates() const;
    void setCoodinates(const Coordinates, const Coordinates);       //in general form
    void setCoodinates(const Coordinates);                          //if vector begin point is {0;0}

    friend std::ostream& operator << (std::ostream& os, const PhaseVector& c);
    friend std::istream & operator >> (std::istream &is,  PhaseVector &c);
private:
    Coordinates m_Begin;
    Coordinates m_End;
};

#endif // PHASEVECTOR_H
