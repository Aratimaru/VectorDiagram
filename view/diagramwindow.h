#ifndef DIAGRAMWINDOW_H
#define DIAGRAMWINDOW_H

#include <QMainWindow>

#include "dynamic_layouts/dynamiclayoutholder.h"
#include "qscrollarea.h"
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
  QString createCircuitElementsRecognizerProcess(const QString &imagePath);
  void createDynamicLayouts();

private:
  Ui::DiagramWindow *ui;
  std::shared_ptr<VectorDiagramModel> _model;
  DynamicLayoutsHolder _dynamicLayoutsHolder;
  QVBoxLayout *_mainDynamicLayout;
  QScrollArea *_scrollArea;
};

#endif // DIAGRAMWINDOW_H
