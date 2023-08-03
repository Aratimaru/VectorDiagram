#include "diagramplot.h"

DiagramPlot::DiagramPlot() {}
DiagramPlot::DiagramPlot(QWidget *widget) : DiagramPlot() {
  this->setParent(widget);
}

void DiagramPlot::drawDataFromModel(const VectorDiagramModel *model) {
  QPen *pen = new QPen{Qt::black};
  pen->setWidth(3);

  // will be changed in the method
  QRectF newBoundingRect;

  for (int i = 0; i < model->rowCount(); i++) {
    for (int j = 0; j < model->columnCount(); j++) {
      PhaseVector vector = model->data(model->index(i, j)).value<PhaseVector>();
      Arrow *arrow = new Arrow{vector.getCoordinates(), 30};
      const auto arrowCoordinates = turnArrowToVectorOfCoordinates(arrow);
      if (arrow->length() == 0) {
        continue;
      }
      this->addGraph();
      this->graph(graphCount() - 1)
          ->setData(arrowCoordinates.first, arrowCoordinates.second, true);
      this->graph(graphCount() - 1)->setPen(*pen);

      findBoundingRect(arrow->boundingRect(), newBoundingRect);
    }
  }
  this->rescaleAxis(newBoundingRect);
  this->replot();
}

void DiagramPlot::clear() {
  int count = this->graphCount();
  for (int i = 0; i < count; i++) {
    this->removeGraph(count - i - 1);
  }
  this->replot();
}

void DiagramPlot::resizeEvent(QResizeEvent *e) {
  QCustomPlot::resizeEvent(e);
  this->yAxis->setScaleRatio(xAxis, 1.0);
}

void DiagramPlot::wheelEvent(QWheelEvent *e) {
  QCustomPlot::wheelEvent(e);
  this->yAxis->setScaleRatio(xAxis, 1.0);
}

QPair<QVector<double>, QVector<double>>
DiagramPlot::turnArrowToVectorOfCoordinates(const Arrow *arrow) {
  QVector<double> x;
  QVector<double> y;

  x.push_back(arrow->getP1().real());
  x.push_back(arrow->getP2().real());
  x.push_back(arrow->getLeftSideP2().x());
  x.push_back(arrow->getP2().real());
  x.push_back(arrow->getRightSideP2().x());

  y.push_back(arrow->getP1().imag());
  y.push_back(arrow->getP2().imag());
  y.push_back(arrow->getLeftSideP2().y());
  y.push_back(arrow->getP2().imag());
  y.push_back(arrow->getRightSideP2().y());

  return {x, y};
}

void DiagramPlot::findBoundingRect(const QRectF &current,
                                   QRectF &newBoundingRect) {

  float topLeftX =
      std::min(current.topLeft().x(), newBoundingRect.topLeft().x());
  float topLeftY =
      std::max(current.topLeft().y(), newBoundingRect.topLeft().y());

  float bottomRightX =
      std::max(current.bottomRight().x(), newBoundingRect.bottomRight().x());
  float bottomRightY =
      std::min(current.bottomRight().y(), newBoundingRect.bottomRight().y());

  newBoundingRect =
      QRectF(QPointF(topLeftX, topLeftY), QPointF(bottomRightX, bottomRightY));
}

void DiagramPlot::rescaleAxis(const QRectF &boundingRect) {
  xAxis->setRange(boundingRect.topLeft().x(), boundingRect.bottomRight().x());
  xAxis->scaleRange(3);
  yAxis->setRange(boundingRect.bottomRight().y(), boundingRect.topLeft().y());
  yAxis->scaleRange(3);
  this->yAxis->setScaleRatio(xAxis, 1.0);
}
