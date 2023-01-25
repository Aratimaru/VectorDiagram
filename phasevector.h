#ifndef PHASEVECTOR_H
#define PHASEVECTOR_H

#include <QPair>

#include <iostream>
#include <utility>

#include <QPointF>

#define INCORRECT_NUMBER                                                       \
  { FLT_MAX, FLT_MAX }

using Line = QPair<QPointF, QPointF>;

enum VectorLabel { VOLTAGE = 0, CURRENT, RESISTENCE, NOT_DEFINED };

struct Coordinates {
  float x;
  float y;
  friend std::ostream &operator<<(std::ostream &os, const Coordinates &c);
  friend std::istream &operator>>(std::istream &is, Coordinates &c);
};

class PhaseVector // stores data in general form
{
public:
  PhaseVector();
  PhaseVector(Coordinates &begin, Coordinates &end);
  PhaseVector(Coordinates &begin, Coordinates &end, VectorLabel label);

  //  std::pair<Coordinates, Coordinates> getCoordinates() const;
  void setCoodinates(const Coordinates, const Coordinates); // in general form
  void setCoodinates(const Coordinates); // if vector begins at {0;0}
  Line getCoordinates() const;
  void setLabel(VectorLabel label);
  VectorLabel getLabel() const;

  friend std::ostream &operator<<(std::ostream &os, const PhaseVector &c);
  friend std::istream &operator>>(std::istream &is, PhaseVector &c);

private:
  Coordinates m_Begin;
  Coordinates m_End;
  VectorLabel m_Label;
};

// Q_DECLARE_METATYPE(PhaseVector);

#endif // PHASEVECTOR_H
