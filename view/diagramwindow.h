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

  void handleV1StartGenTextEdited();
  void handleV1EndGenTextEdited();
  void handleV1StartExpTextEdited();
  void handleV1EndExpTextEdited();

  void handleI1StartGenTextEdited();
  void handleI1EndGenTextEdited();
  void handleI1StartExpTextEdited();
  void handleI1EndExpTextEdited();

  void handleChooseImageButtonClicked();

private:
  bool validateInputParameters();
  PhaseVectorPhase getCurrentPhase();
  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector>
  getParametersFromUi();
  void setupWindow(QMainWindow *DiagramWindow);
  QVector<QString> getElementsFromImage();

public:
  explicit DiagramWindow(QWidget *parent = nullptr);
  ~DiagramWindow();
  void createCircuitElementsRecognizerProcess(const QString &imagePath);

private:
  Ui::DiagramWindow *ui;
  std::shared_ptr<VectorDiagramModel> _model;
};

#endif // DIAGRAMWINDOW_H
