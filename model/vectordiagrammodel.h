#ifndef VECTORDIAGRAMMODEL_H
#define VECTORDIAGRAMMODEL_H

#include "data_structure/phasevector.h"
#include <QAbstractTableModel>
#include <QLineF>
#include <QPointF>

struct TableOfPhases {
  PhaseVector phaseA{};
  PhaseVector phaseB{};
  PhaseVector phaseC{};
};

class VectorDiagramModel : public QAbstractTableModel {
public:
  explicit VectorDiagramModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  void reserve(int size);
  bool isEmpty() const;
  int getColumnCount(const QVector<PhaseVector> &allPhases) const;
  int getRowCount(const QVector<PhaseVector> &allPhases) const;
  void fillModel(QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector> &phaseVectors);

signals:
  void editCompleted(const QString &);

private:
  QVector<TableOfPhases> _instances{};
};

#endif // VECTORDIAGRAMMODEL_H
