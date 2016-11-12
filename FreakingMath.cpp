#include "FreakingMath.h"
#include <QPainter>
#include <QPixmap>
#include <QSize>
#include <time.h>
#include <QTime>
#include <QApplication>
#include <QMouseEvent>
#include <QPoint>
#include <QFont>
#include <QPainterPath>

FreakingMath::FreakingMath(QWidget *parent) : QWidget(parent)
{
    srand(time(NULL));
    diemso=0;
    RAND_INC=1;
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
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush("#3180B0"));
    painter.drawRect(0,0,600,800);
    QString filename = ":/image/logo.png";
    painter.drawPixmap(75,100,250,125,QPixmap(filename));
    QString play = ":/image/buttonplay.png";
    painter.drawPixmap(150,310,100,100,QPixmap(play));
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
    /*QString message="Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);

    int textWidth = fm.width(message);
    painter.setFont(font);
    int h = height();
    int w = width();

    painter.setPen(QPen(QBrush("black"), 1));
    painter.translate(QPoint(w/2, h/2));
    painter.drawText(-textWidth/2, 0, message);*/
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawRect(50,100,275,200);
    QString playagain = ":/image/buttonplay.png";
    painter.drawPixmap(120,310,50,50,QPixmap(playagain));
    QString header = ":/image/header.png";
    painter.drawPixmap(220,310,50,50,QPixmap(header));


}

void FreakingMath::diem(QPainter &painter)
{
    QFont f;
    f.setPointSize(30);
    f.setFamily("Impact");
    painter.setFont(f);
    painter.drawText(width()-50,50,QString::number(diemso));

}

int FreakingMath::random(int n)
{
    return (rand()%n);
}

int FreakingMath::toanhang1()
{
    return 1+rand()%RAND_INC;
}

int FreakingMath::toanhang2()
{
    return 1+rand()%RAND_INC;
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

int FreakingMath::createkqgia(int kq)
{
    int a=kq-3;
    int b=kq+3;
    while(kqgia==kq || kqgia<=0)
    {
        kqgia=(a+rand()%(b-a+1));
    }
    return kqgia;
}

void FreakingMath::createMath()
{
   background=QColor(random(255),random(255),random(255));
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
    kqgia=createkqgia(kqthuc);

}

void FreakingMath::drawMath(QPainter &painter)
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(background);
    painter.drawRect(0,0,600,800);
    QFont f;
    f.setPointSize(50);
    f.setFamily("Impact");
    painter.setFont(f);
    painter.setPen(Qt::white);
    painter.drawText(55,125,QString::number(th1));
    painter.drawText(130,125,tt);
    painter.drawText(185,125,QString::number(th2));
    painter.drawText(260,125,"=");
    if(sosanh == 0)
    {
        painter.drawText(100,225,QString::number(kqthuc));
        mathIsTrue=true;
    }
    else
    {
        painter.drawText(100,225,QString::number(kqgia));
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
    //Sự kiện nhấn nút bắt đầu
    if(mode==0 && event->x() >= 150 && event->x() <= 250 && event->y() >= 310 && event->y() <= 410)
    {
        mode=1;
        diemso=0;
        RAND_INC=1;
        trangthaipheptoan=0;
        timeleft=TIME_LEFT;
        repaint();
    }
    //Sự kiện nhấn nút True
    if((mode==1 && (event->x() >= 20) && (event->x() <= 20+150)) && ((event->y() >= height()-170) && (event->y() <= height()-20)))
    {
        if(mathIsTrue)
        {
            diemso++;
            RAND_INC++;
            trangthaipheptoan=0;
            timeleft=TIME_LEFT;
         }
        else mode=-1;
        repaint();
    }
    //Sự kiện nhấn nút False
    if(mode==1 && (event->x() >= width()-170) && (event->x() <= width()-20) && (event->y() >= height()-170) && (event->y()<= height()-20))
    {
        if(!mathIsTrue)
        {
            diemso++;
            RAND_INC++;
            trangthaipheptoan=0;
            timeleft=TIME_LEFT;
        }
        else mode=-1;
        repaint();
    }
    //Sự kiện nhấn nút chơi lại
    if(mode==-1 && (event->x() >= 120) && (event->x() <= 170) && (event->y() >= 310) && (event->y() <=360))
    {
        mode=1;
        diemso=0;
        RAND_INC=1;
        trangthaipheptoan=0;
        timeleft=TIME_LEFT;
        repaint();
    }
    //Sự kiện nhấn nút trở lại trang chính
    if(mode==-1 && event->x() >= 220 && event->x() <= 270 && event->y() >= 310 && event->y() <=360)
    {
        mode=0;
        repaint();
    }
   QWidget::mousePressEvent(event);
}

void FreakingMath::drawtimebar(QPainter &painter)
{
    painter.setBrush(Qt::green);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0,0,timeleft,10);
}
