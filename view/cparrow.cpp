#include "cparrow.h"

CPArrow::CPArrow(QCustomPlot *parent) : QCPItemLine(parent) {}

QRectF CPArrow::boundingRect() const {
  // find top left corner
  const float topLeftX = std::min(start->coords().x(), end->coords().x());
  const float topLeftY = std::max(start->coords().y(), end->coords().y());

  // find bottom right corner
  const float bottomRightX = std::max(start->coords().x(), end->coords().x());
  const float bottomRightY = std::min(start->coords().y(), end->coords().y());

  return QRectF(QPointF(topLeftX, topLeftY),
                QPointF(bottomRightX, bottomRightY));
}

int CPArrow::length() const {
  return QLineF(start->coords(), end->coords()).length();
}
