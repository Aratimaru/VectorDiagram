#include "diagramplot.h"
#include "view/cparrow.h"

DiagramPlot::DiagramPlot() {}
DiagramPlot::DiagramPlot(QWidget *widget) : DiagramPlot() {
  this->setParent(widget);
}

void DiagramPlot::drawDataFromModel(const VectorDiagramModel *model) {
  QPen *pen = new QPen{Qt::black};
  pen->setWidth(3);

  // will be changed in findBoundingRect() method
  QRectF newBoundingRect;

  for (int i = 0; i < model->rowCount(); i++) {
    for (int j = 0; j < model->columnCount(); j++) {
      PhaseVector vector = model->data(model->index(i, j)).value<PhaseVector>();
      if (vector.length() == 0) {
        continue;
      }

      CPArrow *arrow = new CPArrow(this);
      arrow->start->setCoords(vector.getCoordinates().first);
      arrow->end->setCoords(vector.getCoordinates().second);
      arrow->setHead(QCPLineEnding::esLineArrow);

      QCPItemText *label = new QCPItemText(this);
      label->setText(vector.getLabelName());
      label->setPadding(QMargins(5, 0, 5, 0));
      label->setPositionAlignment(Qt::AlignLeft | Qt::AlignVCenter);
      label->position->setParentAnchor(arrow->end);

      // find diagram size to show all arrows
      findBoundingRect(arrow->boundingRect(), newBoundingRect);
    }
  }
  this->rescaleAxis(newBoundingRect);
  this->replot();
}

void DiagramPlot::clear() {
  int count = this->itemCount();
  for (int i = 0; i < count; i++) {
    this->removeItem(count - i - 1);
  }
  this->replot();
}

void DiagramPlot::resizeEvent(QResizeEvent *e) {
  QCustomPlot::resizeEvent(e);
  int maxRangeAxis = std::max(xAxis->range().size(), yAxis->range().size());
  if (maxRangeAxis == xAxis->range().size()) {
    this->yAxis->setScaleRatio(xAxis, 1.0);
  } else {
    this->xAxis->setScaleRatio(yAxis, 1.0);
  }
}

void DiagramPlot::wheelEvent(QWheelEvent *e) {
  QCustomPlot::wheelEvent(e);
  int maxRangeAxis = std::max(xAxis->range().size(), yAxis->range().size());
  if (maxRangeAxis == xAxis->range().size()) {
    this->yAxis->setScaleRatio(xAxis, 1.0);
  } else {
    this->xAxis->setScaleRatio(yAxis, 1.0);
  }
}

// QPair<QVector<double>, QVector<double>>
// DiagramPlot::turnArrowToVectorOfCoordinates(const Arrow *arrow) {
//   QVector<double> x;
//   QVector<double> y;

//  x.push_back(arrow->getP1().real());
//  x.push_back(arrow->getP2().real());
//  x.push_back(arrow->getLeftSideP2().x());
//  x.push_back(arrow->getP2().real());
//  x.push_back(arrow->getRightSideP2().x());

//  y.push_back(arrow->getP1().imag());
//  y.push_back(arrow->getP2().imag());
//  y.push_back(arrow->getLeftSideP2().y());
//  y.push_back(arrow->getP2().imag());
//  y.push_back(arrow->getRightSideP2().y());

//  return {x, y};
//}

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
  xAxis->scaleRange(2);
  yAxis->setRange(boundingRect.bottomRight().y(), boundingRect.topLeft().y());
  yAxis->scaleRange(2);

  int maxRangeAxis = std::max(xAxis->range().size(), yAxis->range().size());
  if (maxRangeAxis == xAxis->range().size()) {
    this->yAxis->setScaleRatio(xAxis, 1.0);
  } else {
    this->xAxis->setScaleRatio(yAxis, 1.0);
  }
}
