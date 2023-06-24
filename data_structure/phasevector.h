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
  PhaseVector(QPointF &begin, QPointF &end);
  PhaseVector(ComplexNumberAdapter &begin, ComplexNumberAdapter &end);

  PhaseVector(QPointF &begin, QPointF &end, VectorLabel label);
  PhaseVector(QPointF &begin, QPointF &end, const PhaseVectorType type,
              const PhaseVectorPhase phase);
  PhaseVector(QPointF &begin, QPointF &end, const PhaseVectorType type,
              const PhaseVectorPhase phase, const std::string customName);
  PhaseVector(QPointF &end, const PhaseVectorType type,
              const PhaseVectorPhase phase);
  PhaseVector(ComplexNumberAdapter &end, const PhaseVectorType type,
              const PhaseVectorPhase phase);
  PhaseVector(QPointF &end, const PhaseVectorType type,
              const PhaseVectorPhase phase, const std::string customName);

  //  std::pair<QPointF, QPointF> getCoordinates() const;
  void setCoodinates(const QPointF begin,
                     const QPointF end); // in general form
  void setCoodinates(const QPointF end); // if vector begins at {0;0}
  void setCoodinates(ComplexNumberAdapter end);
  void setCoodinates(ComplexNumberAdapter begin, ComplexNumberAdapter end);

  QLineF getCoordinates() const;

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
  QPointF _begin;
  QPointF _end;
  VectorLabel _label;
};

// Q_DECLARE_METATYPE(PhaseVector);

#endif // PHASEVECTOR_H
