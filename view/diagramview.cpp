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

  for (int i = 0; i < model->rowCount(); i++)
    for (int j = 0; j < model->columnCount(); j++) {
      PhaseVector vector = model->data(model->index(i, j)).value<PhaseVector>();
      Arrow *arrow = new Arrow{vector.getCoordinates(), 60, 15};
      if (arrow->length() == 0) {
        continue;
      }
      arrow->setPen(*pen);
      _scene->addItem(arrow);
    }
  //! \todo add scaling
}

void DiagramView::setupView() {
  QBrush *brush = new QBrush(QColor(211, 211, 211, 100));
  brush->setStyle(Qt::CrossPattern);
  _scene->setBackgroundBrush(*brush);
  if (_scene == nullptr) {
    Q_ASSERT(false);
  }
  _scene->setSceneRect(-180, -180, 360, 360);
  this->setScene(_scene);
  //  this->scale(1, -1);

  QPen gridPen(Qt::lightGray);
  QPen axisPen(Qt::black);
  QFont labelFont("Arial", 8);

  // add mark for x axis
  for (int x = 50; x <= _scene->width(); x += 50) {
    QGraphicsLineItem *gridLinePositive =
        new QGraphicsLineItem(x, -_scene->width() / 2, x, _scene->width() / 2);
    QGraphicsLineItem *gridLineNegative = new QGraphicsLineItem(
        -x, -_scene->width() / 2, -x, _scene->width() / 2);
    gridLinePositive->setPen(gridPen);
    gridLineNegative->setPen(gridPen);

    _scene->addItem(gridLinePositive);
    _scene->addItem(gridLineNegative);

    QGraphicsTextItem *labelPositive =
        new QGraphicsTextItem(QString::number(x));
    labelPositive->setFont(labelFont);
    labelPositive->setPos(x - labelPositive->boundingRect().width() / 2,
                          -labelPositive->boundingRect().height());
    _scene->addItem(labelPositive);

    QGraphicsTextItem *labelNegative =
        new QGraphicsTextItem(QString::number(-x));
    labelNegative->setFont(labelFont);
    labelNegative->setPos(-x - labelNegative->boundingRect().width() / 2,
                          -labelNegative->boundingRect().height());
    _scene->addItem(labelNegative);
  }

  // add mark for y axis
  for (int y = 50; y <= _scene->height(); y += 50) {
    QGraphicsLineItem *gridLinePositive = new QGraphicsLineItem(
        -_scene->height() / 2, y, _scene->height() / 2, y);
    QGraphicsLineItem *gridLineNegative = new QGraphicsLineItem(
        -_scene->height() / 2, -y, _scene->height() / 2, -y);
    gridLinePositive->setPen(gridPen);
    gridLineNegative->setPen(gridPen);

    _scene->addItem(gridLinePositive);
    _scene->addItem(gridLineNegative);

    QGraphicsTextItem *labelPositive =
        new QGraphicsTextItem(QString::number(y));
    labelPositive->setFont(labelFont);
    labelPositive->setPos(-labelPositive->boundingRect().width(),
                          y - labelPositive->boundingRect().height() / 2);
    _scene->addItem(labelPositive);

    QGraphicsTextItem *labelNegative =
        new QGraphicsTextItem(QString::number(-y));
    labelNegative->setFont(labelFont);
    labelNegative->setPos(-labelPositive->boundingRect().width(),
                          -y - labelPositive->boundingRect().height() / 2);
    _scene->addItem(labelNegative);
  }

  // add axis lines
  Arrow *xAxis = new Arrow(
      QLineF{-_scene->width() / 2, 0, _scene->width() / 2, 0}, 60, 20);
  Arrow *yAxis = new Arrow(
      QLineF{0, -_scene->height() / 2, 0, _scene->height() / 2}, 60, 20);
  xAxis->setPen(axisPen);
  yAxis->setPen(axisPen);

  _scene->addItem(xAxis);
  _scene->addItem(yAxis);
}
