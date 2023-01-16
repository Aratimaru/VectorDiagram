#ifndef VECTORDIAGRAMMODEL_H
#define VECTORDIAGRAMMODEL_H

#include <QAbstractTableModel>
#include "phasevector.h"

class VectorDiagramModel : public QAbstractTableModel
{
public:
    explicit VectorDiagramModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // VECTORDIAGRAMMODEL_H
