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

  int getRowCount(const std::vector<PhaseVector> &allPhases) const;
  int getColumnCount(const std::vector<PhaseVector> &allPhases) const;

private:
  std::unique_ptr<VectorDiagramModel> _model;
};

#endif // MODELUPDATER_H
