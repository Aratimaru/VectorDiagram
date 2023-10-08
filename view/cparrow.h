#ifndef CPARROW_H
#define CPARROW_H

#include "qcustomplot.h"

class CPArrow : public QCPItemLine {
public:
  CPArrow(QCustomPlot *parent);
  QRectF boundingRect() const;
  int length() const;
};

#endif // CPARROW_H
