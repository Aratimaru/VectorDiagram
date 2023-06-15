#include "complexnumberadapter.h"

ComplexNumberAdapter::ComplexNumberAdapter() : std::complex<float>() {
  setForm(false);
}

ComplexNumberAdapter::ComplexNumberAdapter(std::complex<float> a)
    : std::complex<float>(a) {
  setForm(false);
}

ComplexNumberAdapter::ComplexNumberAdapter(float r, float i)
    : std::complex<float>(r, i) {
  setForm(true);
}

ComplexNumberAdapter ComplexNumberAdapter::toGeneralForm() {
  ComplexNumberAdapter result;
  result._form = ComplexNumberForm::GENERAL;

  result.real(this->real() *
              (std::cos(this->imag() * (std::atan(1.0f) * 4 / 180.f))));
  result.imag(this->real() *
              (std::sin(this->imag() * (std::atan(1.0f) * 4 / 180.f))));
  return result;
}

ComplexNumberAdapter ComplexNumberAdapter::toExponentialForm() {
  ComplexNumberAdapter result;
  result._form = ComplexNumberForm::EXPONENTIAL;

  result.real(std::sqrt(std::pow(this->real(), 2) + std::pow(this->imag(), 2)));
  result.imag(std::atan(this->imag() / this->real()) * 180.f /
              (std::atan(1.0f) * 4.f)); // std::atan(1.0)*4 = PI
  return result;
}

ComplexNumberForm ComplexNumberAdapter::getForm() { return _form; }

void ComplexNumberAdapter::setForm(ComplexNumberForm f) { _form = f; }

void ComplexNumberAdapter::setForm(bool f) { _form = ComplexNumberForm(f); }

bool ComplexNumberAdapter::isDigit(const char &c) {
  return ((c > 47 && c < 58) || c == '.' || c == '-');
}

ComplexNumberAdapter multExp(ComplexNumberAdapter c1,
                             const ComplexNumberAdapter &c2) {
  ComplexNumberAdapter result;

  float real = c1.real() * c2.real();
  float imag = c1.imag() + c2.imag();

  result.real(real);
  result.imag(imag);
  return result;
}

ComplexNumberAdapter divideExp(ComplexNumberAdapter c1,
                               const ComplexNumberAdapter &c2) {
  ComplexNumberAdapter result;

  if (c2.real() == NULL_COMPLEX_NUMBER)
    return ComplexNumberAdapter(NULL_COMPLEX_NUMBER);

  float real = c1.real() / c2.real();
  float imag = c1.imag() - c2.imag();

  result.real(real);
  result.imag(imag);
  return result;
}
