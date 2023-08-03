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
  void resizeEvent(QResizeEvent *e);
  void wheelEvent(QWheelEvent *e);

private:
  void setupView();
  QPair<QVector<double>, QVector<double>>
  turnArrowToVectorOfCoordinates(const Arrow *arrow);
  void findBoundingRect(const QRectF &current, QRectF &newBoundingRect);
  void rescaleAxis(const QRectF &boundingRect);
};

#endif // DIAGRAMPLOT_H
