#ifndef ARROW_H
#define ARROW_H

#include "calculations/complexnumberadapter.h"
#include <QAbstractGraphicsShapeItem>
#include <QLineF>
#include <QObject>

class Arrow : public QAbstractGraphicsShapeItem {
public:
  explicit Arrow(QAbstractGraphicsShapeItem *parent = nullptr);
  Arrow(const ComplexNumberPair &base, QLineF &leftSide, QLineF &rightSide);
  Arrow(const ComplexNumberPair &base, const float &angle = 90,
        const float &sideLenght = 10);
  //  Arrow(ComplexNumberAdapter base, const float &angle = 90,
  //        const float &sideLenght = 10);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QRectF boundingRect() const override;

  void setArrowParameters(ComplexNumberPair &base, QLineF &leftSide,
                          QLineF &rightSide);
  void setArrowParameters(ComplexNumberPair &base, const float &angle = 60,
                          const float &sideLenght = 20);

  ComplexNumberAdapter getP1();
  ComplexNumberAdapter getP2();
  float length() const;

private:
  void calculateSidesByAngle();

  ComplexNumberPair _base{};
  QLineF _leftSide{};
  QLineF _rightSide{};
  float _angle{};
  float _sideLenght{};
};

#endif // ARROW_H
