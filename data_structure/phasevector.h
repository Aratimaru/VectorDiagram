#ifndef PHASEVECTOR_H
#define PHASEVECTOR_H

#include "../calculations/complexnumberadapter.h"
#include <iostream>
#include <utility>

#include <QLineF>
#include <QPointF>

#define INCORRECT_NUMBER                                                       \
  { FLT_MAX, FLT_MAX }

enum class PhaseVectorType { CURRENT = 0, VOLTAGE, RESISTENCE, NOT_DEFINED };
enum class PhaseVectorPhase { PHASE_A = 0, PHASE_B, PHASE_C, NOT_DEFINED };
struct VectorLabel {
  PhaseVectorType type{PhaseVectorType::NOT_DEFINED};
  PhaseVectorPhase phase{PhaseVectorPhase::NOT_DEFINED};
  std::string customName{};
};

class PhaseVector // stores data in general form
{
public:
  PhaseVector();
  PhaseVector(const ComplexNumberAdapter &begin,
              const ComplexNumberAdapter &end,
              const VectorLabel label = VectorLabel());
  PhaseVector(const ComplexNumberAdapter &begin,
              const ComplexNumberAdapter &end,
              const PhaseVectorType type = PhaseVectorType::NOT_DEFINED,
              const PhaseVectorPhase phase = PhaseVectorPhase::NOT_DEFINED,
              const std::string customName = "");
  PhaseVector(const ComplexNumberAdapter &end,
              const PhaseVectorType type = PhaseVectorType::NOT_DEFINED,
              const PhaseVectorPhase phase = PhaseVectorPhase::NOT_DEFINED,
              const std::string customName = "");

  PhaseVector(const PhaseVector &other);

  void setCoodinates(const ComplexNumberAdapter begin,
                     const ComplexNumberAdapter end); // in general form
  void
  setCoodinates(const ComplexNumberAdapter end); // if vector begins at {0;0}

  ComplexNumberPair getCoordinates() const;

  void setLabel(const VectorLabel label);
  void setLabelType(const PhaseVectorType type);
  void setLabelPhase(const PhaseVectorPhase phase);
  void setLabelName(const std::string customName);

  VectorLabel getLabel() const;
  PhaseVectorType getLabelType() const;
  PhaseVectorPhase getLabelPhase() const;
  std::string getLabelName() const;

  bool isEmpty();

  friend std::ostream &operator<<(std::ostream &os, const PhaseVector &c);
  friend std::istream &operator>>(std::istream &is, PhaseVector &c);

private:
  ComplexNumberAdapter _begin;
  ComplexNumberAdapter _end;
  VectorLabel _label;
};

// Q_DECLARE_METATYPE(PhaseVector);

#endif // PHASEVECTOR_H
