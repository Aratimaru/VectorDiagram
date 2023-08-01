#ifndef DIAGRAMPLOT_H
#define DIAGRAMPLOT_H

#include "view/arrow.h"
#include <model/vectordiagrammodel.h>
#include <view/qcustomplot.h>

class DiagramPlot : public QCustomPlot {
public:
  DiagramPlot();
  DiagramPlot(QWidget *widget);
  void drawDataFromModel(const VectorDiagramModel *model);
  void clear();

private:
  void setupView();
  QPair<QVector<double>, QVector<double>>
  turnArrowToVectorOfCoordinates(const Arrow *arrow);
};

#endif // DIAGRAMPLOT_H
