#ifndef COMPLEXNUMBERADAPTER_H
#define COMPLEXNUMBERADAPTER_H
#include "qline.h"
#include "qpoint.h"
#include <complex>
#include <string>

#define UNDEFINED_COMPLEX_NUMBER (FLT_MAX, FLT_MAX)
#define NULL_COMPLEX_NUMBER (0.f, 0.f)
// #define ComplexNumberLine std::pair<ComplexNumberAdapter,
// ComplexNumberAdapter>

enum class ComplexNumberForm { GENERAL = 0, EXPONENTIAL };

class ComplexNumberAdapter : public std::complex<float> {
public:
  ComplexNumberAdapter();
  ComplexNumberAdapter(std::complex<float>);
  ComplexNumberAdapter(float r, float i);
  ComplexNumberAdapter
  toGeneralForm(); // returns pair of real and imaginary values
  ComplexNumberAdapter
  toExponentialForm(); // returns pair of coefficient and exponent power values

  // TODO: add multiplexion and division for exp form

  static ComplexNumberAdapter
  multExp(const ComplexNumberAdapter &c1,
          const ComplexNumberAdapter
              &c2); // operations methods for exponential form
  static ComplexNumberAdapter divExp(const ComplexNumberAdapter &c1,
                                     const ComplexNumberAdapter &c2);
  ComplexNumberForm getForm() const;
  void setForm(ComplexNumberForm f);
  void setForm(bool f);
  static bool isDigit(const char &c);
  bool isNull() const;

  operator QPointF() const;
  ComplexNumberAdapter &operator=(const QPointF &other);

private:
  ComplexNumberForm _form; // 0 - gen, 1 -exp
};

struct ComplexNumberLine {
  int length() const;
  ComplexNumberAdapter first;
  ComplexNumberAdapter second;

  operator QLineF() const;
  ComplexNumberLine &operator=(const QLineF &other);
};

#endif // COMPLEXNUMBERADAPTER_H
