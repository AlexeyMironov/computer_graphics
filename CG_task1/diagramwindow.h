#ifndef DIAGRAMWINDOW_H
#define DIAGRAMWINDOW_H

#include "editedtablemodel.h"
#include <QDialog>
//#include <QPoint>

namespace Ui {
class DiagramWindow;
}

class DiagramWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DiagramWindow(QWidget *parent, EditedTableModel *model);
    ~DiagramWindow();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::DiagramWindow *ui;
    EditedTableModel *m_model;
    QPointF GetPoint(double angle, double R1 = 0, double R2 = 0);
    int GetQuater(double angle);
    double Angle360(double angle);
    void mouseMoveEvent(QMouseEvent *event);
    double cX,cY,cW,cH,pW,lX,lY;
    QPoint coords;
};

#endif // DIAGRAMWINDOW_H
