#include "electricalvaluescalculator.h"

bool ElectricalValuesCalculator::calculate(VectorDiagramModel &model) {
  (void)model;
  return true;
}

ComplexNumberAdapter ElectricalValuesCalculator::findCircuitGeneralCurrent(
    const QMap<QString, QPair<int, int>> &connection,
    const QMap<QString, ComplexNumberAdapter> &values) {

  // need to choose root voltage element
  QStringList rootElements;
  for (const auto &v : connection.keys()) {
    if (v.startsWith("v")) {
      rootElements.append(v);
    }
  }
  if (rootElements.size() == 0) {
    throw(std::runtime_error("No voltage source found!"));
    return ComplexNumberAdapter{};
  }

  QMap<int, QString> sequenceConnectionsMap =
      findSequenceConnections(connection, values, rootElements);

  QVector<QVector<int>> parallelConnectionsVector =
      findParallelConnections(sequenceConnectionsMap);

  ComplexNumberAdapter result;
  for (int i = 0; i < parallelConnectionsVector.size(); i++) {
    for (int j = 0; i < parallelConnectionsVector[i].size(); i++) {
      QString elementNameInParallelOrder =
          sequenceConnectionsMap[parallelConnectionsVector[i][j]];

      ComplexNumberAdapter value = values[elementNameInParallelOrder];
      result += value;
    }
  }

  return result;
}

QMap<int, QString> ElectricalValuesCalculator::findSequenceConnections(
    const QMap<QString, QPair<int, int>> &connection,
    const QMap<QString, ComplexNumberAdapter> &values,
    QStringList &rootElements) {
  QMap<int, QString> sequenceConnections;

  // Having only one voltage source.
  //! \todo
  QString rootElement = rootElements.at(0);
  int startNode = connection[rootElement].first;
  int endNode = connection[rootElement].second;

  QString currentElementName = rootElement;
  int n1 = connection[currentElementName].first;
  int n2 = connection[currentElementName].second;

  QStringList nextElementsList = findNextElementsInSequence(connection, n2);
  switch (nextElementsList.size()) {
  case 0:
    if (n2 == startNode) {
      qDebug() << Q_FUNC_INFO
               << "Circuit end reached. Finally:) God bless the King";
    } else {
      qDebug()
          << Q_FUNC_INFO
          << "Error: no circuit end found and element sequence breaks here";
      throw(std::runtime_error("No circuit end found!!!"));
    }
    break;
  case 1:
    qDebug() << Q_FUNC_INFO
             << "New sequential element found: " << nextElementsList;
    break;
  default:
    qDebug() << Q_FUNC_INFO
             << "Several sequential elements found: " << nextElementsList;
    break;
  }

  return sequenceConnections;
}

QVector<QVector<int>> ElectricalValuesCalculator::findParallelConnections(
    const QMap<int, QString> &sequenceConnections) {
  QVector<QVector<int>> parallelConnections;

  return parallelConnections;
}

QStringList ElectricalValuesCalculator::findNextElementsInSequence(
    const QMap<QString, QPair<int, int>> &connection, int connectionNode) {
  QStringList nextElements;

  for (const auto &el : connection.keys()) {
    if (connectionNode == connection[el].first ||
        connectionNode == connection[el].second) {
      nextElements.push_back(el);
    }
  }
  return nextElements;
}

bool ElectricalValuesCalculator::areElementsConnected(
    const QPair<int, int> &e1, const QPair<int, int> &e2) {
  return e1.first == e2.first || e1.first == e2.second ||
         e1.second == e2.first || e1.second == e2.second;
}

ElectricalValuesCalculator::ElectricalValuesCalculator() {}
