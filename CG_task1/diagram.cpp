#include "diagram.h"
#include "ui_diagram.h"
#include <QPainter>


diagram::diagram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::diagram)
{
    ui->setupUi(this);
    timer = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()), this, SLOT(timer_tick()));
    timer->start(1000);
}

diagram::~diagram()
{
    delete ui;
    delete timer;
}

void diagram::timer_tick()
{
    /*openGLWidget.setRenderHints(QPainter::Antialiasing, true);
    openGLWidget.setBrush(QBrush(Qt::red));
    openGLWidget.drawPie(QRect(10,10,100,50), 90 * 16, 270 * 16);*/
}

void diagram::paintEvent(QPaintEvent *event)
{
    //create a QPainter and pass a pointer to the device.
    //A paint device can be a QWidget, a QPixmap or a QImage
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(Qt::red));
    painter.drawPie(QRect(10,10,100,50), 90 * 16, 270 * 16);
}
