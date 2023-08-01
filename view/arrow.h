#ifndef ARROW_H
#define ARROW_H

#include "calculations/complexnumberadapter.h"
#include <QAbstractGraphicsShapeItem>
#include <QLineF>
#include <QObject>

class Arrow : public QAbstractGraphicsShapeItem {
public:
  explicit Arrow(QAbstractGraphicsShapeItem *parent = nullptr);
  Arrow(const ComplexNumberLine &base, QLineF &leftSide, QLineF &rightSide);
  Arrow(const ComplexNumberLine &base, const float &angle = 60,
        const float &sideLenght = 0);
  Arrow(const QLineF &base, const float &angle = 60,
        const float &sideLenght = 0);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QRectF boundingRect() const override;

  void setArrowParameters(ComplexNumberLine &base, QLineF &leftSide,
                          QLineF &rightSide);
  void setArrowParameters(ComplexNumberLine &base, const float &angle = 60,
                          const float &sideLenght = 20);

  ComplexNumberAdapter getP1() const;
  ComplexNumberAdapter getP2() const;

  QPointF getLeftSideP2() const;
  QPointF getRightSideP2() const;
  float length() const;

private:
  void calculateSidesByAngle();

  ComplexNumberLine _base{};
  QLineF _leftSide{};
  QLineF _rightSide{};
  float _angle{};
  float _sideLenght{};
};

#endif // ARROW_H
