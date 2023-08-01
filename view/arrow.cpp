#include "arrow.h"
#include "qpainter.h"

Arrow::Arrow(QAbstractGraphicsShapeItem *parent)
    : QAbstractGraphicsShapeItem(parent) {}

Arrow::Arrow(const ComplexNumberLine &base, QLineF &leftSide,
             QLineF &rightSide) {
  _base = base;
  _leftSide = leftSide;
  _rightSide = rightSide;
}

Arrow::Arrow(const ComplexNumberLine &base, const float &angle,
             const float &sideLenght) {
  _base = base;
  _angle = angle;
  _sideLenght = sideLenght;
  calculateSidesByAngle();
}

Arrow::Arrow(const QLineF &base, const float &angle, const float &sideLenght) {
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

QRectF Arrow::boundingRect() const {
  // find top left corner
  const float topBaseLeftX = std::min(_base.first.real(), _base.second.real());
  const float topSideLeftX = std::min(_leftSide.p2().x(), _rightSide.p2().x());
  const float topLeftX = std::min(topBaseLeftX, topSideLeftX);

  const float topBaseLeftY = std::min(_base.first.imag(), _base.second.imag());
  const float topSideLeftY = std::min(_leftSide.p2().y(), _rightSide.p2().y());
  const float topLeftY = std::min(topBaseLeftY, topSideLeftY);

  // find bottom right corner
  const float BottomBaseRightX =
      std::max(_base.first.real(), _base.second.real());
  const float BottomSideRightX =
      std::max(_leftSide.p2().x(), _rightSide.p2().x());
  const float bottomRightX = std::max(BottomBaseRightX, BottomSideRightX);

  const float BottomBaseRightY =
      std::max(_base.first.imag(), _base.second.imag());
  const float BottomSideRightY =
      std::max(_leftSide.p2().y(), _rightSide.p2().y());
  const float bottomRightY = std::max(BottomBaseRightY, BottomSideRightY);

  return QRectF(QPointF(topLeftX, topLeftY),
                QPointF(bottomRightX, bottomRightY));
}

void Arrow::setArrowParameters(ComplexNumberLine &base, QLineF &leftSide,
                               QLineF &rightSide) {
  _base = base;
  _leftSide = leftSide;
  _rightSide = rightSide;
}

void Arrow::setArrowParameters(ComplexNumberLine &base, const float &angle,
                               const float &sideLenght) {
  _base = base;
  _angle = angle;
  _sideLenght = sideLenght;
  calculateSidesByAngle();
}

ComplexNumberAdapter Arrow::getP1() const { return _base.first; }

ComplexNumberAdapter Arrow::getP2() const { return _base.second; }

QPointF Arrow::getLeftSideP2() const { return _leftSide.p2(); }

QPointF Arrow::getRightSideP2() const { return _rightSide.p2(); }

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

  if (_sideLenght == 0) {
    _sideLenght = _base.length() * 0.15;
  }
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
