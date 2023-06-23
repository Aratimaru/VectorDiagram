#ifndef VIEWUPDATER_H
#define VIEWUPDATER_H

#include "model/modelupdater.h"
#include "qgraphicsview.h"
#include "view/arrow.h"

#include <QBrush>
#include <QPen>

class ViewUpdater {
public:
  ViewUpdater();
  void drawLines();
  void setView(QGraphicsView *view);
  void setModel(ModelUpdater *model);

private:
  std::shared_ptr<QGraphicsView> _view;
  std::shared_ptr<ModelUpdater> _modelUpdater;
  std::shared_ptr<QGraphicsScene> _scene;

  void setupView();
};

#endif // VIEWUPDATER_H
