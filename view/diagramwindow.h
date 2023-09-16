#ifndef DIAGRAMWINDOW_H
#define DIAGRAMWINDOW_H

#include <QMainWindow>

#include <model/vectordiagrammodel.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class DiagramWindow;
}
QT_END_NAMESPACE

class DiagramWindow : public QMainWindow {
  Q_OBJECT

private slots:
  void handleClearBtnClicked();
  void handleDrawBtnClicked();

  void handleV1StartGenXEditTextChanged(const QString &arg1);
  void handleV1StartGenYEditTextChanged(const QString &arg1);
  void handleV1EndGenXEditTextChanged(const QString &arg1);
  void handleV1EndGenYEditTextChanged(const QString &arg1);
  void handleV1ImagStartAEditTextChanged(const QString &arg1);
  void handleV1ImagEndAEditTextChanged(const QString &arg1);
  void handleV1ImagStartUEditTextChanged(const QString &arg1);
  void handleV1ImagEndUEditTextChanged(const QString &arg1);

private:
  bool validateInputParameters();
  PhaseVectorPhase getCurrentPhase();
  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector>
  getParametersFromUi();
  void setupWindow(QMainWindow *DiagramWindow);

public:
  explicit DiagramWindow(QWidget *parent = nullptr);
  ~DiagramWindow();

private:
  Ui::DiagramWindow *ui;
  std::shared_ptr<VectorDiagramModel> _model;
};

#endif // DIAGRAMWINDOW_H
