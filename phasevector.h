#ifndef PHASEVECTOR_H
#define PHASEVECTOR_H
#include <utility>
#include <iostream>

struct Coordinates{
    float x;
    float y;

};

class PhaseVector       //stores data in general form
{
private:
public:
    PhaseVector();
    PhaseVector(Coordinates &begin, Coordinates &end);
    std::pair<Coordinates, Coordinates> getCoordinates() const;
    void setCoodinates(const Coordinates, const Coordinates);
    void setCoodinates(const Coordinates);
    friend std::ostream& operator<<(std::ostream& os, const Coordinates& c);        //need to find the right place for it
    friend std::istream & operator >> (std::istream &is,  Coordinates &c);
private:
    Coordinates m_Begin;
    Coordinates m_End;
};

#endif // PHASEVECTOR_H
