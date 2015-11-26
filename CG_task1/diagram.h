#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QWidget>
#include <QTimer>

class MainWindow;
namespace Ui {
class diagram;
}

class diagram : public QWidget
{
    Q_OBJECT

public:
    explicit diagram(QWidget *parent = 0);
    ~diagram();

protected:
    void paintEvent(QPaintEvent *event);

public slots:
  //Слот, который срабатывает при переполнении таймера
  void timer_tick();

private:
    Ui::diagram *ui;
    MainWindow *m_window;
    QTimer *timer;
};

#endif // DIAGRAM_H
