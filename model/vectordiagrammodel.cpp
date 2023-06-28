#include "vectordiagrammodel.h"

VectorDiagramModel::VectorDiagramModel(QObject *parent)
    : QAbstractTableModel{parent} {}

int VectorDiagramModel::rowCount(const QModelIndex & /*parent*/) const {
  return _instances.size();
}

int VectorDiagramModel::columnCount(const QModelIndex & /*parent*/) const {
  if (_instances.size() != 0) {
    return 3;
  } else {
    return 0;
  }
}

QVariant VectorDiagramModel::data(const QModelIndex &index, int role) const {
  if (index.column() >= columnCount() || index.row() >= _instances.size())
    return false;

  //! \todo add the sanity check

  (void)role;
  const TableOfPhases *holderStruct{&_instances[index.row()]};
  (void)role;

  switch (index.column()) {
  case 0:
    return QVariant::fromValue(holderStruct->phaseA);
  case 1:
    return QVariant::fromValue(holderStruct->phaseB);
  case 2:
    return QVariant::fromValue(holderStruct->phaseC);
  default:
    Q_ASSERT(false);
    break;
  }
}

bool VectorDiagramModel::setData(const QModelIndex &index,
                                 const QVariant &value, int role) {
  if (index.column() >= columnCount() || index.row() >= _instances.size())
    return false;

  if (!value.canConvert<PhaseVector>())
    return false; // conversion may not succeed

  //! \todo intermediary calculations

  (void)role;
  auto dataPair = value.value<PhaseVector>();
  TableOfPhases *holderStruct;
  holderStruct = &_instances[index.row()];

  switch (index.column()) {
  case 0:
    holderStruct->phaseA = dataPair;
    break;
  case 1:
    holderStruct->phaseB = dataPair;
    break;
  case 2:
    holderStruct->phaseC = dataPair;
    break;
  default:
    Q_ASSERT(false);
    break;
  }

  _hasNext = true;
  return true;
}

void VectorDiagramModel::reserve(int size) {
  _instances = QVector<TableOfPhases>(3);
}

bool VectorDiagramModel::hasNext() const { return _hasNext; }

bool VectorDiagramModel::isEmpty() const {
  return false; // todo
}

void VectorDiagramModel::resetIter() {
  _iter = {0, 0};
  _hasNext = false; // think about the algorithm
}

PhaseVector VectorDiagramModel::getNextVector() {
  int &row = _iter.first;
  int &col = _iter.second;
  const auto idx = index(row, col);
  const PhaseVector info = data(idx).value<PhaseVector>();

  col++;

  if (col >= columnCount()) {
    col = 0;
    row++;
  }

  if (row >= rowCount())
    resetIter();

  return info;
}

int VectorDiagramModel::getRowCount(
    const std::vector<PhaseVector> &allPhases) const {
  int count{};
  for (const auto &e : allPhases) {
    if (e.getLabelPhase() == PhaseVectorPhase::PHASE_A) {
      count++;
    }
  }
  return count;
}

int VectorDiagramModel::getColumnCount(
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

void VectorDiagramModel::fillModel(const std::vector<PhaseVector> &allPhases) {
  auto converter = [this](const PhaseVector &item, int row, int column) {
    // Create index
    //! \todo get row and column
    const auto idx = this->index(row, column);
    const auto data = QVariant::fromValue<PhaseVector>(item);

    this->setData(idx, data);
  };

  this->reserve(allPhases.size());

  for (int i = 0; i < allPhases.size(); i++) {

    // we can be sure all vectors are in the same order all the time
    int row = static_cast<int>(allPhases.at(i).getLabelType());
    int column = static_cast<int>(allPhases.at(i).getLabelPhase());

    converter(allPhases.at(i), row, column);
  }
}
