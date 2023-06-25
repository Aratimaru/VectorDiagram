#include "diagramview.h"
#include "view/arrow.h"

DiagramView::DiagramView() {
  _scene = new QGraphicsScene(this);
  setupView();
}

DiagramView::DiagramView(QWidget *widget) : DiagramView() {
  this->setParent(widget);
}

DiagramView::~DiagramView() { delete _scene; }

void DiagramView::drawLines(VectorDiagramModel *model) const {
  QPen *pen = new QPen{Qt::black};
  pen->setWidth(3);
  while (model->hasNext()) {
    QLineF nextLine{model->getNextVector()};
    Arrow *arrow = new Arrow{nextLine, 60, 20};
    if (arrow->lenght() == 0) {
      continue;
    }
    arrow->setPen(*pen);
    _scene->addItem(arrow);
    *pen = arrow->pen();
  }
  //! \todo add scaling
}

void DiagramView::setupView() {
  QBrush *brush = new QBrush(QColor(211, 211, 211, 100));
  brush->setStyle(Qt::CrossPattern);
  _scene->setBackgroundBrush(*brush);
  if (_scene == nullptr) {
    assert(false);
  }
  this->setScene(_scene);
  this->scale(1, -1);
}
