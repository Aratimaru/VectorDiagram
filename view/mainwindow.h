#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>
#include <tuple>

#include "model/vectordiagrammodel.h"
#include "qlineedit.h"
#include "view/diagramview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void resizeEvent(QResizeEvent *e);

private:
  ComplexNumberAdapter constructPoint(
      const std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>
          &key);

  QMap<std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>,
       ComplexNumberAdapter>
  getParametersFromUI();

  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector>
  constructVectorsFromParameters(
      const QMap<
          std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>,
          ComplexNumberAdapter> &parameters);

  QMap<std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>,
       ComplexNumberAdapter>
  determineChangedFields();

  void calculateOtherFormFieldBasedOnChangedInput(
      const QMap<
          std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>,
          ComplexNumberAdapter> &difference);

  void setupParametrFieldsNames();

private slots:
  void on_ConfirmButton_clicked();

  void on_ClearButton_clicked();

private:
  Ui::MainWindow *ui;
  std::shared_ptr<VectorDiagramModel> _model;

  // need to track prev parameters to choose the last updated field
  QMap<std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>,
       ComplexNumberAdapter>
      previousParameters;
  QMap<std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm>,
       ComplexNumberAdapter>
      currentParameters;

  // store QLineEdit addresses
  QMap<std::tuple<PhaseVectorPhase, PhaseVectorType, ComplexNumberForm,
                  ComplexNumberPart>,
       QLineEdit *>
      parameterFields;
};
#endif // MAINWINDOW_H
