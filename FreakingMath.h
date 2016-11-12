#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QWidget>
#include <QPushButton>
#include <QPointF>

class FreakingMath : public QWidget
{
    Q_OBJECT
public:
    explicit FreakingMath(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *event);
    int diemso;
    int mode=0;
private:
    static const int DELAY = 10;
    static const int TIME_LEFT = 600;
    int RAND_INC;
    QColor background;
    bool mathIsTrue;
    int timerId;
    double th1;
    double th2;
    double kqthuc;
    double kqgia;
    int random(int );
    int sosanh;
    int timeleft;
    int trangthaipheptoan;
    int toanhang1();
    int toanhang2();
    int createkqgia(int);
    QString tt;
    QString toantu();
    QPointF truebtn;
    QPointF falsebtn;

    void diem(QPainter& );
    void Khung1(QPainter& );
    void Khung2(QPainter& );
    void Khung3(QPainter& );
    void drawtimebar(QPainter &);
    void playgame(QPainter &);
    void buttonclick(QPainter &);
    void createMath();
    void drawMath(QPainter &);
    void EndGame(QPainter &);



signals:

public slots:
};

#endif // GRAPHICS_H
