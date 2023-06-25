#include "modelupdater.h"

ModelUpdater::ModelUpdater() : _model(std::make_unique<VectorDiagramModel>()) {}

bool ModelUpdater::hasNext() { return _model->hasNext(); }

QLineF ModelUpdater::getNextVector() { return _model->getNextVector(); }
