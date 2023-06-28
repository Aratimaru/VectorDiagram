#include "arrow.h"
#include "qpainter.h"

Arrow::Arrow(QAbstractGraphicsShapeItem *parent)
    : QAbstractGraphicsShapeItem(parent) {}

Arrow::Arrow(const ComplexNumberPair &base, QLineF &leftSide,
             QLineF &rightSide) {
  _base = base;
  _leftSide = leftSide;
  _rightSide = rightSide;
}

Arrow::Arrow(const ComplexNumberPair &base, const float &angle,
             const float &sideLenght) {
  _base = base;
  _angle = angle;
  _sideLenght = sideLenght;
  calculateSidesByAngle();
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
  (void)widget;
  (void)option;
  QList<QLineF> list;
  list.append(QLineF(_base.first, _base.second));
  list.append(_leftSide);
  list.append(_rightSide);
  painter->setPen(this->pen());
  painter->setBrush(this->brush());
  painter->drawLines(list);
}

//! \todo change implementation
QRectF Arrow::boundingRect() const {
  // find top left corner
  float topLeftX = _base.first.real() < _base.second.real()
                       ? _base.first.real()
                       : _base.second.real();
  float topLeftY = _base.first.imag() < _base.second.imag()
                       ? _base.first.imag()
                       : _base.second.imag();

  // find bottom right corner
  float bottomRightX = _base.first.real() > _base.second.real()
                           ? _base.first.real()
                           : _base.second.real();
  float bottomRightY = _base.first.imag() > _base.second.imag()
                           ? _base.first.imag()
                           : _base.second.imag();

  return QRectF(QPointF(topLeftX, topLeftY),
                QPointF(bottomRightX, bottomRightY));
}

void Arrow::setArrowParameters(ComplexNumberPair &base, QLineF &leftSide,
                               QLineF &rightSide) {
  _base = base;
  _leftSide = leftSide;
  _rightSide = rightSide;
}

void Arrow::setArrowParameters(
    std::pair<ComplexNumberAdapter, ComplexNumberAdapter> &base,
    const float &angle, const float &sideLenght) {
  _base = base;
  _angle = angle;
  _sideLenght = sideLenght;
  calculateSidesByAngle();
}

ComplexNumberAdapter Arrow::getP1() { return _base.first; }

ComplexNumberAdapter Arrow::getP2() { return _base.second; }

float Arrow::length() const {
  return QLineF(_base.first, _base.second).length();
}

void Arrow::calculateSidesByAngle() {

  /*
   *           C
   *          /|\
   *         / | \
   *        /  |  \
   *       /   |   \
   *      /    |    \
   *     /    B|_____\A
   *           |
   *           |
   */

  const QPointF arrowHead = _base.second;
  _leftSide.setP1(QPointF{arrowHead.x(), arrowHead.y()});
  _rightSide.setP1(QPointF{arrowHead.x(), arrowHead.y()});

  const float BA_lenght = sin(_angle / 2 * M_PI / 180) * _sideLenght;
  const float BC_lenght = cos(_angle / 2 * M_PI / 180) * _sideLenght;

  float coefficient = 1 - BC_lenght / length();
  const float Bx = arrowHead.x() * coefficient;
  const float By = arrowHead.y() * coefficient;

  const float CBx = arrowHead.x() - Bx;
  const float CBy = arrowHead.y() - By;

  const QPointF normalLeft = {CBy, -CBx};
  const QPointF normalRight = {-CBy, CBx};

  float xCoefLeft = normalLeft.x() / BC_lenght;
  float yCoefLeft = normalLeft.y() / BC_lenght;

  float xCoefRight = normalRight.x() / BC_lenght;
  float yCoefRight = normalRight.y() / BC_lenght;

  _leftSide.setP2(
      QPointF{BA_lenght * xCoefLeft + Bx, BA_lenght * yCoefLeft + By});
  _rightSide.setP2(
      QPointF{BA_lenght * xCoefRight + Bx, BA_lenght * yCoefRight + By});
}
