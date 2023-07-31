#ifndef DIAGRAMPLOT_H
#define DIAGRAMPLOT_H

#include <model/vectordiagrammodel.h>
#include <view/qcustomplot.h>

class DiagramPlot : public QCustomPlot {
public:
  DiagramPlot();
  DiagramPlot(QWidget *widget);
  void drawDataFromModel(const VectorDiagramModel *model);
  void clear();

private:
  std::vector<QGraphicsItem *> vectorsHolder;

  void setupView();
};

#endif // DIAGRAMPLOT_H
