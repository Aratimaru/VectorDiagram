#ifndef PHASEVECTOR_H
#define PHASEVECTOR_H

#include "../calculations/complexnumberadapter.h"
#include <iostream>
#include <utility>

#include <QDebug>
#include <QLineF>
#include <QPointF>
#include <QString>

enum class PhaseVectorType { CURRENT = 0, VOLTAGE, RESISTENCE, NOT_DEFINED };
enum class PhaseVectorPhase { PHASE_A = 0, PHASE_B, PHASE_C, NOT_DEFINED };
enum class PhaseVectorMetricPrefics {
  NANO = -9,
  MICRO = -6,
  MILLI = -3,
  STANDARD = 1,
  KILO = 3,
  MEGA = 6,
  GIGA = 9
};
struct VectorLabel {
  PhaseVectorType type{PhaseVectorType::NOT_DEFINED};
  PhaseVectorPhase phase{PhaseVectorPhase::NOT_DEFINED};
  PhaseVectorMetricPrefics metricPrefics{PhaseVectorMetricPrefics::STANDARD};
  QString customName{};
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
              const QString customName = "");
  PhaseVector(const ComplexNumberAdapter &end,
              const PhaseVectorType type = PhaseVectorType::NOT_DEFINED,
              const PhaseVectorPhase phase = PhaseVectorPhase::NOT_DEFINED,
              const QString customName = "");

  PhaseVector(const PhaseVector &other);

  void setCoodinates(const ComplexNumberAdapter begin,
                     const ComplexNumberAdapter end); // in general form
  void
  setCoodinates(const ComplexNumberAdapter end); // if vector begins at {0;0}

  ComplexNumberLine getCoordinates() const;

  QString PhaseVectorTypeToString();
  QString PhaseVectorPhaseToString(bool upperCase = false);

  void setLabel(const VectorLabel label);
  void setLabelType(const PhaseVectorType type);
  void setLabelPhase(const PhaseVectorPhase phase);
  void setLabelName(const QString customName);
  void setLabelNameFromTypeAndPhase();

  VectorLabel getLabel() const;
  PhaseVectorType getLabelType() const;
  PhaseVectorPhase getLabelPhase() const;
  QString getLabelName() const;

  bool isEmpty();
  int length() const;

  friend std::ostream &operator<<(std::ostream &os, const PhaseVector &c);
  friend std::istream &operator>>(std::istream &is, PhaseVector &c);

private:
  ComplexNumberAdapter _begin;
  ComplexNumberAdapter _end;
  VectorLabel _label;
};

// Q_DECLARE_METATYPE(PhaseVector);

#endif // PHASEVECTOR_H
