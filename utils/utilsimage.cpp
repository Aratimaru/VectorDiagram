#include "utilsimage.h"
#include <QDebug>

UtilsImage::UtilsImage() {}

QStringList
UtilsImage::recognizeComponentsFromPythonOutput(const QString &output) {
  QStringList result;
  QString outputCopy = output;

  QString toBeDeletedBefore{"Components in the circuit are: "};
  QString toBeDeletedAfter{"Junctions in the circuit are"};

  outputCopy.remove(QString(toBeDeletedBefore));
  if (outputCopy == output) {
    qDebug() << Q_FUNC_INFO << "Output string can't be parsed";
    return result;
  }

  outputCopy.remove("\r");
  outputCopy.remove("\n");

  int position = outputCopy.indexOf(toBeDeletedAfter);
  outputCopy.remove(position, outputCopy.size() - position);

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
