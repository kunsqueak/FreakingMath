#include "FreakingMath.h"
#include <QPainter>
#include <QPixmap>
#include <QSize>
#include <time.h>
#include <QTime>
#include <QApplication>
#include <QMouseEvent>
#include <QPoint>

FreakingMath::FreakingMath(QWidget *parent) : QWidget(parent)
{
    srand(time(NULL));
    diemso=0;
    timeleft=TIME_LEFT;
    trangthaipheptoan=0;
    timerId=startTimer(DELAY);
};

void FreakingMath::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if(mode==0) Khung1(painter);
    if(mode==1&&trangthaipheptoan==0)
    {
        createMath();
        trangthaipheptoan=1;
    }
    if(mode==1&&trangthaipheptoan==1)
    {
        drawMath(painter);
    }

    if(mode==1)
    {
        Khung2(painter);
    }

    if(mode==-1) Khung3(painter);
}
void FreakingMath::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);
    if(mode==1)
    {
        timeleft-=6;
        if(timeleft==0)
        {
            mode=-1;
        }
        repaint();
    }


}


void FreakingMath::Khung1(QPainter& painter)
{
    QString filename = ":/image/icon.png";
    painter.drawPixmap(115,50,150,150,QPixmap(filename));
}

void FreakingMath::Khung2(QPainter& painter)
{
    buttonclick(painter);
    diem(painter);
    drawtimebar(painter);
}

void FreakingMath::Khung3(QPainter& painter)
{
    EndGame(painter);
}

void FreakingMath::EndGame(QPainter &painter)
{
    QString message="Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);

    int textWidth = fm.width(message);
    painter.setFont(font);
    int h = height();
    int w = width();

    painter.setPen(QPen(QBrush("black"), 1));
    painter.translate(QPoint(w/2, h/2));
    painter.drawText(-textWidth/2, 0, message);
}

void FreakingMath::diem(QPainter &painter)
{
    //painter.drawText(width()-100,30,"Điểm: ");
    painter.drawText(width()-50,30,QString::number(diemso));

}

int FreakingMath::random(int n)
{
    return (rand()%n);
}

int FreakingMath::toanhang1()
{
    return 1+rand()%10;
}

int FreakingMath::toanhang2()
{
    return 1+rand()%10;
}

QString FreakingMath::toantu()
{
    QString cong="+";
    QString tru="-";
    int toantu1=random(2);
    switch (toantu1) {
    case 0:
        return cong;
        break;
    case 1:
        return tru;
        break;
    }
}

int FreakingMath::fakeresult(int kq)
{
    int a=kq-3;
    int b=kq+3;
    while(kqgia==kq || kqgia<0)
    {
        kqgia=(a+rand()%(b-a+1));
    }
    return kqgia;
}

void FreakingMath::createMath()
{
   sosanh=random(2);
   th1=toanhang1();
   th2=toanhang2();
   tt=toantu();
    if(tt=="+")
    {
        kqthuc=th1+th2;
    }
    else if(tt=="-")
    {
        while(th2>th1)
        {
            int temp;
            temp=th2;
            th1=temp;
            th2=th1;
        }
        kqthuc=th1-th2;
    }
    kqgia=fakeresult(kqthuc);

}
void FreakingMath::drawMath(QPainter &painter)
{
    painter.drawText(100,100,QString::number(th1));
    painter.drawText(125,100,tt);
    painter.drawText(150,100,QString::number(th2));
    if(sosanh == 0)
    {
        painter.drawText(100,150,QString::number(kqthuc));
        mathIsTrue=true;
    }
    else
    {
        painter.drawText(100,150,QString::number(kqgia));
        mathIsTrue=false;
    }
}
void FreakingMath::buttonclick(QPainter &painter)
{
    QString truebtn = ":/image/btntrue.png";
    painter.drawPixmap(20,height()-170,150,150,QPixmap(truebtn));
    QString falsebtn = ":/image/btnfalse.png";
    painter.drawPixmap(width()-170,height()-170,150,150,QPixmap(falsebtn));
}

void FreakingMath::mousePressEvent(QMouseEvent *event)
{
    if(((event->x() >= 20) && (event->x() <= 20+150)) && ((event->y() >= height()-170) && (event->y() <= height()-20)))
    {
        if(mathIsTrue)
        {
            diemso++;
            trangthaipheptoan=0;
            timeleft=TIME_LEFT;
         }
        else mode=-1;
        repaint();
    }
    if((event->x() >= width()-170) && (event->x() <= width()-20) && (event->y() >= height()-170) && (event->y()<= height()-20))
    {
        if(!mathIsTrue)
        {
            diemso++;
            trangthaipheptoan=0;
            timeleft=TIME_LEFT;
        }
        else mode=-1;
        repaint();
    }
   return QWidget::mousePressEvent(event);
}

void FreakingMath::drawtimebar(QPainter &painter)
{
    painter.setBrush(Qt::green);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0,0,timeleft,10);
}
