#include "viewupdater.h"

ViewUpdater::ViewUpdater()
    : _view(std::make_shared<QGraphicsView>()),
      _modelUpdater(std::make_shared<ModelUpdater>()),
      _scene(std::make_shared<QGraphicsScene>()) {
  setupView();
}
void ViewUpdater::drawLines() {
  QPen *pen = new QPen{Qt::black};
  pen->setWidth(3);
  while (_modelUpdater->hasNext()) {
    QLineF nextLine{_modelUpdater->getNextVector()};
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

void ViewUpdater::setView(QGraphicsView *view) { _view.reset(view); }

void ViewUpdater::setModel(ModelUpdater *model) { _modelUpdater.reset(model); }

void ViewUpdater::setupView() {
  QBrush *brush = new QBrush(QColor(211, 211, 211, 100));
  brush->setStyle(Qt::CrossPattern);
  _scene->setBackgroundBrush(*brush);
  _view->setScene(_scene.get());
  _view->scale(1, -1);
}
