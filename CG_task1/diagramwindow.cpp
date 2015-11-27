#include "diagramwindow.h"
#include "ui_diagramwindow.h"
#include <QPainter>
#include <QVector>
#include <QColor>
#include <QMouseEvent>



DiagramWindow::DiagramWindow(QWidget *parent, EditedTableModel *model) :
    QDialog(parent),
    ui(new Ui::DiagramWindow)
{
    ui->setupUi(this);
    m_model = model;

    cW = 150;
    cH = 100;
    cX = (this->width() - cW) / 2;
    cY = (this->height() - cH) / 2;
    lX = cX+cW+20;
    lY = cY;
}

DiagramWindow::~DiagramWindow()
{
    delete ui;
}

QPointF DiagramWindow::GetPoint(double angle, double R1, double R2)
{
    if (R1 == 0 && R2 == 0)
    {
        R1 = cW;
        R2 = cH;
    }
    QPointF point;
    double x = R1 / 2 * cos(angle * M_PI / 180);
    x += cW / 2 + cX;
    double y = -R2 / 2 * sin(angle * M_PI / 180);
    y += cH / 2 + cY;
    point.setX(x);
    point.setY(y);
    return point;
}

DiagramWindow::GetQuater(double angle)
{
    angle = Angle360(angle);

    if(angle >= 0 && angle < 90)
    {
        return 1;
    }
    if(angle >= 90 && angle < 180)
    {
        return 2;
    }
    if(angle >= 180 && angle < 270)
    {
        return 3;
    }
    return 4;
}

double DiagramWindow::Angle360(double angle)
{
    int i = (int)angle;
    double delta = angle - i;
    return (i % 360 + delta);
}

void DiagramWindow::mouseMoveEvent(QMouseEvent *event)
{
    coords = event->pos();
    this->update();
}

void DiagramWindow::paintEvent(QPaintEvent *event)
{
    (void)event;
    QPainter painter(this);  
    painter.setRenderHints(QPainter::Antialiasing, true);

    pW = 50 - float(coords.y()) / this->height() * 50;
    cH = float(coords.y()) / this->height() * 150;

    if (cH > 150 / 3 + 30)   //  /3 == *60/180
    {
        cH = 150 / 3 + 30;
        pW = 50 - cH / 150 * 50;
    }
    else if (cH < 150 / 6 + 30)    //  /6 == *30/180
    {
        cH = 150 / 6 + 30;
        pW = 50 - cH / 150 * 50;
    }

    QLinearGradient gradient(cX - 0.5 * cW, cY + cH / 2, cX + 1.5 * cW, cY + cH / 2);
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);
    QLinearGradient gradientSide(cX, cY + cH, cX + cW ,cY + cH);
    gradientSide.setColorAt(0, Qt::black);

    double pAlpha = float(coords.x()) / this->width() * 360;
    if (pAlpha > 360)
    {
        pAlpha = 360;
    }
    else if (pAlpha < 0)
    {
        pAlpha = 0;
    }

    auto data = m_model->getData();
    float allPopulation = 0;
    for (int i = 0; i < data.size(); i++)
    {
        allPopulation += data[i].population;
    }

    double pDegree = 0;
    QPointF p;
    QVector<QColor> colors = {Qt::red, Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow, Qt::gray};

    for (int i = 0; i <  data.size(); i++)
    {
        gradient.setColorAt(0.5, colors[i % 7]);
        painter.setBrush(gradient);
        pDegree = (data[i].population / allPopulation) * 360;
        painter.drawPie(cX, cY, cW, cH, pAlpha * 16, pDegree * 16);

        double alphaPrev = Angle360(pAlpha);
        int quatPrev = GetQuater(pAlpha);

        pAlpha += pDegree;

        double alphaNext = Angle360(pAlpha);
        int quatNext = GetQuater(pAlpha);

        QPainterPath path;
        p = GetPoint(pAlpha);

        if((quatNext == 3 || quatNext == 4) && (quatPrev == 3 || quatPrev == 4))
        {
            if (alphaNext > alphaPrev)
            {
                QPointF pOld = GetPoint(pAlpha - pDegree);
                path.moveTo(pOld.x() - 1, pOld.y());
                path.arcTo(cX, cY, cW, cH, pAlpha - pDegree, pDegree);
                path.lineTo(p.x(), p.y() + pW);
                path.arcTo(cX, cY + pW, cW, cH, pAlpha, -pDegree);
            }
            else
            {
                path.moveTo(cX,cY + cH / 2);
                path.arcTo(cX, cY, cW, cH, 180, Angle360(pAlpha) - 180);
                path.lineTo(p.x(), p.y() + pW);
                path.arcTo(cX, cY + pW,cW,cH, Angle360(pAlpha), -Angle360(pAlpha) + 180);
                path.lineTo(cX, cY + cH / 2);

                path.moveTo(p.x(), p.y());
                path.arcTo(cX, cY, cW, cH, pAlpha - pDegree, 360 - Angle360(pAlpha - pDegree));
                path.lineTo(cX + cW, cY + cH/2 + pW);
                path.arcTo(cX, cY + pW, cW, cH, 0, -360 + Angle360(pAlpha - pDegree));
             }
        }
        else if((quatNext == 3 || quatNext == 4) && (quatPrev == 1 || quatPrev == 2) && alphaNext > alphaPrev )
        {
            path.moveTo(cX, cY + cH / 2);
            path.arcTo(cX, cY, cW, cH, 180, Angle360(pAlpha) - 180);
            path.lineTo(p.x(), p.y() + pW);
            path.arcTo(cX, cY + pW, cW, cH, Angle360(pAlpha), -Angle360(pAlpha) + 180);
            path.lineTo(cX, cY + cH / 2);
        }
        else if((quatNext == 1 || quatNext == 2) && (quatPrev == 3 || quatPrev == 4) && alphaNext < alphaPrev)
        {
            p = GetPoint(pAlpha - pDegree);
            path.moveTo(p.x(), p.y());
            path.arcTo(cX, cY, cW, cH, pAlpha - pDegree, 360 - Angle360(pAlpha - pDegree));
            path.lineTo(cX + cW, cY + cH / 2 + pW);
            path.arcTo(cX, cY + pW, cW, cH, 0, -360 + Angle360(pAlpha - pDegree));
        }
        if (!path.isEmpty())
        {
            gradientSide.setColorAt(1, colors[i]);
            painter.setBrush(gradientSide);
            painter.drawPath(path);
        }
    }
}
