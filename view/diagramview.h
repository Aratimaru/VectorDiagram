#ifndef DIAGRAMVIEW_H
#define DIAGRAMVIEW_H

#include "model/vectordiagrammodel.h"
#include "qgraphicsview.h"
#include <QWheelEvent>
#include <vector>

class DiagramView : public QGraphicsView {
public:
  DiagramView();
  DiagramView(QWidget *widget);

  ~DiagramView();
  void drawModel(const VectorDiagramModel *model);
  void clear(const VectorDiagramModel *model);

  void wheelEvent(QWheelEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

private:
  QGraphicsScene *_scene;
  QVector<QGraphicsItem *> vectorsHolder;

  void setupView();
};

#endif // DIAGRAMVIEW_H
