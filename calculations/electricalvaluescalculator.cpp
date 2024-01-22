#include "electricalvaluescalculator.h"

bool ElectricalValuesCalculator::calculate(VectorDiagramModel &model) {
  (void)model;
  return true;
}

QPair<ComplexNumberAdapter, ComplexNumberAdapter>
ElectricalValuesCalculator::findCircuitGeneralCurrent(
    const QMap<QString, QPair<int, int>> &connection,
    const QMap<QString, ComplexNumberAdapter> &values) {

  QPair<ComplexNumberAdapter, ComplexNumberAdapter> result;
  // don't need to calculate current parameter if it's already set by user
  if (values.keys().contains("IaStart") && values.keys().contains("IaEnd")) {
    result.first = values["IaStart"];
    result.second = values["IaEnd"];
    return result;
  }

  // need to choose root voltage element
  QStringList rootElements;
  for (const auto &v : connection.keys()) {
    if (v.startsWith("v")) {
      rootElements.append(v);
    }
  }
  if (rootElements.size() == 0) {
    throw(std::runtime_error("No voltage source found!"));
    return result;
  }

  QMap<int, QStringList> sequenceConnectionsMap =
      findSequenceConnections(connection, rootElements);

  // e.g. parallel elements amount: 3, 2, 1, 3
  QVector<QVector<int>> parallelConnectionsVector =
      findParallelConnections(sequenceConnectionsMap);

  // WA for only 1 sequencial connection
  // only End parameter is needed
  result.first = ComplexNumberAdapter{};
  result.second =
      calculateCurrentInSequencialConnection(values, sequenceConnectionsMap[0]);

  return result;
}

QPair<ComplexNumberAdapter, ComplexNumberAdapter>
ElectricalValuesCalculator::findCircuitGeneralVoltage(
    const QMap<QString, QPair<int, int>> &connection,
    const QMap<QString, ComplexNumberAdapter> &values) {

  QPair<ComplexNumberAdapter, ComplexNumberAdapter> result;
  // don't need to calculate current parameter if it's already set by user
  if (values.keys().contains("UaStart") && values.keys().contains("UaEnd")) {
    result.first = values["UaStart"];
    result.second = values["UaEnd"];
    return result;
  }

  // need to choose root voltage element
  QStringList rootElements;
  for (const auto &v : connection.keys()) {
    if (v.startsWith("v")) {
      rootElements.append(v);
    }
  }
  if (rootElements.size() == 0) {
    throw(std::runtime_error("No voltage source found!"));
    return result;
  }

  //! \todo
  if (rootElements.size() > 1) {
    throw(std::runtime_error(
        "More than 1 voltage source found! No support implemented yet"));
    return result;
  }

  QString strNameFromValuesMap = "U" + rootElements.at(0) + "End";

  // WA for only 1 sequencial connection
  // only End parameter is needed
  result.first = ComplexNumberAdapter{};
  result.second = values[strNameFromValuesMap];

  return result;
}

QMap<int, QStringList> ElectricalValuesCalculator::findSequenceConnections(
    const QMap<QString, QPair<int, int>> &connection, QStringList &rootElements,
    int sequenceConnectionsCounter) {
  QMap<int, QStringList> sequenceConnections;

  // Having only one voltage source.
  //! \todo
  QString rootElement = rootElements.at(0);
  int startNode = connection[rootElement].first;
  int endNode = connection[rootElement].second;

  QString currentElementName = rootElement;
  int n1 = connection[currentElementName].first;
  int n2 = connection[currentElementName].second;

  bool isCircuitEndFound = false;

  qDebug() << Q_FUNC_INFO << "Starting from root element: " << rootElement;
  sequenceConnections[sequenceConnectionsCounter].append(rootElement);

  QStringList nextElementsList =
      findNextElementsInSequence(connection, n2, currentElementName);

  while (!isCircuitEndFound) {
    switch (nextElementsList.size()) {
    case 0:
      if (n2 == startNode) {
        qDebug() << Q_FUNC_INFO << "Why 0???";
        isCircuitEndFound = true;
      } else {
        qDebug()
            << Q_FUNC_INFO
            << "Error: no circuit end found and element sequence breaks here";
        throw(std::runtime_error("No circuit end found!!!"));
      }
      break;
    case 1:
      if (n2 == startNode) {
        qDebug() << Q_FUNC_INFO
                 << "Circuit end reached. Finally:) God bless the King";
        isCircuitEndFound = true;
        sequenceConnectionsCounter += 10;
        break;
      }
      qDebug() << Q_FUNC_INFO
               << "New sequential element found: " << nextElementsList;
      sequenceConnections[sequenceConnectionsCounter].append(
          nextElementsList.last());

      currentElementName = nextElementsList.last();
      // choose node number different from current one
      if (n2 == connection[currentElementName].second) {
        n2 = connection[currentElementName].first;
      } else {
        n2 = connection[currentElementName].second;
      }
      nextElementsList =
          findNextElementsInSequence(connection, n2, currentElementName);
      break;
    default:

      //! \todo reserve 10 numbers to mark 1 parallel connection
      qDebug() << Q_FUNC_INFO
               << "Several sequential elements found: " << nextElementsList;
      nextElementsList.clear();
      sequenceConnectionsCounter++;
      break;
    }
  }

  return sequenceConnections;
}

//! \todo reserve 10 numbers to mark 1 parallel connection
QVector<QVector<int>> ElectricalValuesCalculator::findParallelConnections(
    const QMap<int, QStringList> &sequenceConnections) {
  QVector<QVector<int>> parallelConnections;
  if (sequenceConnections.size() == 1) {
    QVector<int> parallelChain;
    parallelChain.append(sequenceConnections.keys().at(0));
    parallelConnections.append(parallelChain);
  }

  return parallelConnections;
}

QStringList ElectricalValuesCalculator::findNextElementsInSequence(
    const QMap<QString, QPair<int, int>> &connection, int connectionNode,
    const QString &currentElementName) {
  QStringList nextElements;

  for (const auto &el : connection.keys()) {
    if (el != currentElementName && (connectionNode == connection[el].first ||
                                     connectionNode == connection[el].second)) {
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

//! \todo Add support for multiple voltage sources
QMap<QString, ComplexNumberAdapter>
ElectricalValuesCalculator::findCurrentForResistanceElements(
    const QMap<QString, ComplexNumberAdapter> &allElementValues) {
  QMap<QString, ComplexNumberAdapter> currentCalculatedfromResistance;

  ComplexNumberAdapter voltageValue = allElementValues["v1"];
  for (auto it = allElementValues.begin(); it != allElementValues.end(); it++) {
    if (!it.key().contains("v") && !it.key().contains("E")) {
      ComplexNumberAdapter resistance =
          ComplexNumberAdapter::divExp(it.value(), voltageValue);
      currentCalculatedfromResistance[it.key()] = resistance;
    }
  }

  return currentCalculatedfromResistance;
}

//! \todo
ComplexNumberAdapter
ElectricalValuesCalculator::calculateCurrentInParallelConnection(
    const QMap<QString, ComplexNumberAdapter> &values,
    QMap<int, QStringList> sequenceConnections,
    QVector<QVector<int>> parallelConnections) {
  ComplexNumberAdapter result;
  return result;
}

ComplexNumberAdapter
ElectricalValuesCalculator::calculateCurrentInSequencialConnection(
    const QMap<QString, ComplexNumberAdapter> &values,
    QStringList &sequenceConnections) {
  // current is the same for all elements in sequence
  ComplexNumberAdapter result;
  ComplexNumberAdapter voltageValue;
  ComplexNumberAdapter resistanceValue;

  for (const auto &e : sequenceConnections) {
    // not voltage element
    if (e.contains("E")) {
      continue;
    }
    if (!e.contains("v")) {
      QString strNameFromValuesMap = "R" + e + "End";
      resistanceValue += values[strNameFromValuesMap];
    } else {
      QString strNameFromValuesMap = "U" + e + "End";
      voltageValue += values[strNameFromValuesMap];
    }
  }
  if (resistanceValue == ComplexNumberAdapter()) {
    throw std::runtime_error("Division by 0 is not allowed!");
  }
  result = voltageValue / resistanceValue;
  return result;
}
