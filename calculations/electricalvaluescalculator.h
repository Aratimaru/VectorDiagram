#ifndef ELECTRICALVALUESCALCULATOR_H
#define ELECTRICALVALUESCALCULATOR_H

#include "calculator.h"

class ElectricalValuesCalculator : public Calculator {
public:
  bool calculate(VectorDiagramModel &model) override;

  static QPair<ComplexNumberAdapter, ComplexNumberAdapter> findCircuitGeneralCurrent(const QMap<QString, QPair<int, int>> &connection,
                            const QMap<QString, ComplexNumberAdapter> &values);
  static QMap<int, QStringList>
  findSequenceConnections(const QMap<QString, QPair<int, int>> &connection,
                          QStringList &rootElements,
                          int sequenceConnectionsCounter = 0);
  static QVector<QVector<int>>
  findParallelConnections(const QMap<int, QStringList> &sequenceConnections);
  static QStringList
  findNextElementsInSequence(const QMap<QString, QPair<int, int>> &connection,
                             int connectionNode,
                             const QString &currentElementName);
  static bool areElementsConnected(const QPair<int, int> &e1,
                                   const QPair<int, int> &e2);
  static QMap<QString, ComplexNumberAdapter> findCurrentForResistanceElements(
      const QMap<QString, ComplexNumberAdapter> &allElementValues);

  static ComplexNumberAdapter calculateCurrentInParallelConnection(
      const QMap<QString, ComplexNumberAdapter> &values,
      QMap<int, QStringList> sequenceConnections,
      QVector<QVector<int>> parallelConnections);
  static ComplexNumberAdapter calculateCurrentInSequencialConnection(
      const QMap<QString, ComplexNumberAdapter> &values,
      QStringList &sequenceConnections);
};

#endif // ELECTRICALVALUESCALCULATOR_H
