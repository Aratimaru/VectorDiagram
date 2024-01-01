#include "utilsimage.h"
#include "qregularexpression.h"
#include <QDebug>

UtilsImage::UtilsImage() {}

QStringList
UtilsImage::recognizeComponentsFromPythonOutput(const QString &output) {
  QStringList result;
  QString outputCopy = output;

  int toBeDeletedBefore = outputCopy.indexOf("Components in the circuit are:");

  outputCopy.remove(0, toBeDeletedBefore +
                           QString("Components in the circuit are:").size());
  if (outputCopy == output) {
    qDebug() << Q_FUNC_INFO << "Output string can't be parsed";
    return result;
  }

  outputCopy.remove("\r");
  outputCopy.remove("\n");

  int toBeDeletedAfter = outputCopy.indexOf("Junctions in the circuit are:");
  outputCopy.chop(outputCopy.size() - toBeDeletedAfter);

  // parse "R1U1I1R2U2" string to determine elements name
  QString elementName{};
  for (int i = 0; i < outputCopy.size(); i++) {
    if (outputCopy[i].isLetter()) {
      if (elementName.isEmpty()) {
        elementName.append(outputCopy[i].toLower());
      } else {
        result.push_back(elementName);
        elementName.clear();
        elementName.append(outputCopy[i].toLower());
      }
    } else if (outputCopy[i].isDigit()) {
      elementName.append(outputCopy[i]);
    }
  }
  // don't forget about last one
  result.push_back(elementName);
  return result;
}

QMap<QString, QPair<int, int>>
UtilsImage::recognizeConnectionFromPythonOutput(const QString &output) {
  QStringList components = recognizeComponentsFromPythonOutput(output);

  QMap<QString, QPair<int, int>> nodesConnectedToComponent;

  // The input string
  QString inputString = output;
  int startPosition = inputString.indexOf('[');
  int endPosition = inputString.indexOf("\r\nComponents in");
  inputString.remove(0, startPosition);
  inputString.chop(inputString.size() - endPosition);
  qDebug() << Q_FUNC_INFO << "Trimmed inputString:" << inputString;

  // Remove brackets and spaces
  inputString.remove(QRegularExpression("[\\[\\]() ]"));

  // Split the string into a QStringList based on ']' character
  QStringList setsList = inputString.split("]");

  // Iterate through the QStringList and create name-element pairs
  int elementIndex = 0;
  for (const QString &set : setsList) {
    // Split each set of numbers into a QStringList based on commas
    QStringList numbersList = set.split(',');

    // Create pairs for consecutive numbers
    for (int i = 0; i < numbersList.size() - 1; i += 2) {
      bool ok1, ok2;
      int num1 = numbersList[i].toInt(&ok1);
      int num2 = numbersList[i + 1].toInt(&ok2);

      if (ok1 && ok2) {
        QString elementName{};
        if (elementIndex < components.size()) {
          elementName = components[elementIndex];
        } else {
          elementName = QString("E%1").arg(elementIndex);
        }
        QPair<int, int> elementPair(num1, num2);
        nodesConnectedToComponent.insert(elementName, elementPair);
        elementIndex++;
      } else {
        qDebug() << Q_FUNC_INFO << "Error converting to integers";
        break;
      }
    }
  }

  // Print the QMap content
  qDebug() << Q_FUNC_INFO << "Resulting QMap<QString, QPair<int, int>>:";

  for (const QString &key : nodesConnectedToComponent.keys()) {
    const QPair<int, int> &elementPair = nodesConnectedToComponent.value(key);
    qDebug() << key << ": (" << elementPair.first << ", " << elementPair.second
             << ")";
  }

  return nodesConnectedToComponent;
}
