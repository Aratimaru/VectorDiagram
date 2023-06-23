#ifndef MODELUPDATER_H
#define MODELUPDATER_H

#include "data_structure/phasevector.h"
#include "model/vectordiagrammodel.h"

class ModelUpdater {
public:
  ModelUpdater();
  void fillModel(const std::vector<PhaseVector> &allPhases);
  bool hasNext();
  QLineF getNextVector();

private:
  std::unique_ptr<VectorDiagramModel> _model;
};

#endif // MODELUPDATER_H
