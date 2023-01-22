#ifndef VECTORDIAGRAMMODEL_H
#define VECTORDIAGRAMMODEL_H

#include "phasevector.h"

#include <QAbstractTableModel>

#define ROWS 2
#define COLUMNS 3

struct TableOfPhases{
    QPair<double, double> phaseA{};
    QPair<double, double> phaseB{};
    QPair<double, double> phaseC{};
};

class VectorDiagramModel : public QAbstractTableModel
{
public:
    explicit VectorDiagramModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

signals:
    void editCompleted(const QString &);

private:
    QString m_gridData[COLUMNS][ROWS];  //holds text entered into QTableView

    QVector<TableOfPhases> _instances;
};

#endif // VECTORDIAGRAMMODEL_H
