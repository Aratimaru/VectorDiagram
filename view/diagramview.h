#ifndef DIAGRAMVIEW_H
#define DIAGRAMVIEW_H

#include "model/vectordiagrammodel.h"
#include "qgraphicsview.h"
class DiagramView : public QGraphicsView {
public:
  DiagramView();
  DiagramView(QWidget *widget);

  ~DiagramView();
  void drawLines(VectorDiagramModel *model) const;

private:
  QGraphicsScene *_scene;

  void setupView();
};

#endif // DIAGRAMVIEW_H
