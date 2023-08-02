#include "diagramplot.h"

DiagramPlot::DiagramPlot() {}
DiagramPlot::DiagramPlot(QWidget *widget) : DiagramPlot() {
  this->setParent(widget);
}

void DiagramPlot::drawDataFromModel(const VectorDiagramModel *model) {
  QPen *pen = new QPen{Qt::black};
  pen->setWidth(3);

  for (int i = 0; i < model->rowCount(); i++) {
    for (int j = 0; j < model->columnCount(); j++) {
      PhaseVector vector = model->data(model->index(i, j)).value<PhaseVector>();
      Arrow *arrow = new Arrow{vector.getCoordinates(), 60};
      const auto arrowCoordinates = turnArrowToVectorOfCoordinates(arrow);
      //      if (arrow->length() == 0) {
      //        continue;
      //      }
      this->addGraph();
      this->graph(i * model->rowCount() + j)
          ->setData(arrowCoordinates.first, arrowCoordinates.second, true);
      this->graph(i * model->rowCount() + j)->setPen(*pen);
    }
  }
  this->replot();
}

void DiagramPlot::clear() {
  int count = this->graphCount();
  for (int i = 0; i < count; i++) {
    this->removeGraph(count - i - 1);
  }
  this->replot();
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
