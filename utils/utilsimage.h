#ifndef UTILSIMAGE_H
#define UTILSIMAGE_H

#include <QStringList>

class UtilsImage {
public:
  UtilsImage();
  static QStringList recognizeComponentsFromPythonOutput(const QString &output);
};

#endif // UTILSIMAGE_H
