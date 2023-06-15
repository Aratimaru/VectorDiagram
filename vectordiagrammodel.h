#ifndef VECTORDIAGRAMMODEL_H
#define VECTORDIAGRAMMODEL_H

#include <QAbstractTableModel>
#include <QLineF>
#include <QPointF>

#define ROWS 2
#define COLUMNS 3

struct TableOfPhases {
  QLineF phaseA{};
  QLineF phaseB{};
  QLineF phaseC{};
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
  bool hasNext();
  bool isEmpty();
  void resetIter();
  QLineF getNextVector();

signals:
  void editCompleted(const QString &);

private:
  QString _gridData[COLUMNS][ROWS]; // holds text entered into QTableView

  QVector<TableOfPhases> _instances{};
  QPair<int, int> _iter{0, 0};
  bool _hasNext{false};
};

#endif // VECTORDIAGRAMMODEL_H
