#ifndef ELECTRICALVALUESCALCULATOR_H
#define ELECTRICALVALUESCALCULATOR_H

#include "calculator.h"

class ElectricalValuesCalculator : public Calculator {
public:
  ElectricalValuesCalculator();
  bool calculate(VectorDiagramModel &model) override;

  ComplexNumberAdapter
  findCircuitGeneralCurrent(const QMap<QString, QPair<int, int>> &connection,
                            const QMap<QString, ComplexNumberAdapter> &values);
  QMap<int, QString>
  findSequenceConnections(const QMap<QString, QPair<int, int>> &connection,
                          const QMap<QString, ComplexNumberAdapter> &values,
                          QStringList &rootElements);
  QVector<QVector<int>>
  findParallelConnections(const QMap<int, QString> &sequenceConnections);
  QStringList
  findNextElementsInSequence(const QMap<QString, QPair<int, int>> &connection,
                             int connectionNode);
  bool areElementsConnected(const QPair<int, int> &e1,
                            const QPair<int, int> &e2);
};

#endif // ELECTRICALVALUESCALCULATOR_H
