#include "modelupdater.h"

ModelUpdater::ModelUpdater() : _model(std::make_unique<VectorDiagramModel>()) {}

void ModelUpdater::fillModel(const std::vector<PhaseVector> &allPhases) {
  auto converter = [this](const PhaseVector &item, int row, int column) {
    const QLineF coord = item.getCoordinates();

    // Create index

    //! \todo get row and column
    const auto idx = _model->index(row, column);
    const auto data = QVariant::fromValue<QLineF>(coord);

    _model->setData(idx, data);
  };

  _model->reserve(allPhases.size());

  for (int i = 0; i < allPhases.size(); i++) {
    converter(allPhases.at(i), i % allPhases.size(), i / allPhases.size());
  }
}

bool ModelUpdater::hasNext() { return _model->hasNext(); }

QLineF ModelUpdater::getNextVector() { return _model->getNextVector(); }

int ModelUpdater::getRowCount(const std::vector<PhaseVector> &allPhases) const {
  int count{};
  for (const auto &e : allPhases) {
    if (e.getLabelPhase() == PhaseVectorPhase::PHASE_A) {
      count++;
    }
  }
  return count;
}

int ModelUpdater::getColumnCount(
    const std::vector<PhaseVector> &allPhases) const {
  int count{};
  PhaseVectorPhase previousPhase = PhaseVectorPhase::NOT_DEFINED;
  for (const auto &e : allPhases) {
    if (previousPhase != e.getLabelPhase()) {
      count++;
    }
    previousPhase = e.getLabelPhase();
  }
  return count;
}
