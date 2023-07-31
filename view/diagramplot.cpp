#include "diagramplot.h"
#include "arrow.h"

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
      Arrow *arrow = new Arrow{vector.getCoordinates(), 60, 15};
      vectorsHolder.push_back(arrow);
      if (arrow->length() == 0) {
        continue;
      }
      arrow->setPen(*pen);
      this->addGraph();
      this->graph(i * model->rowCount() + j)
          ->setData({arrow->getP1().real()}, {arrow->getP1().imag()});
    }
  }
  this->rescaleAxes();
  this->replot();
  this->update();
}

void DiagramPlot::clear() {
  for (int i = 0; i < this->graphCount(); i++) {
    this->removeGraph(i);
  }
  vectorsHolder.clear();
}
