#include "about.h"
#include "ui_about.h"
#include <QPainter>
#include <QLayout>

about::about(QWidget* parent) : QDialog(parent), ui(new Ui::about)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    this->setStyleSheet("background-color: rgba(39, 245, 230, 200);");
    ui->label->setStyleSheet("background-color: rgba(255, 255, 255, 0); color: rgba(39, 69, 230, 255); ");
}

about::~about()
{
    delete ui;
}

void about::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen({QColorConstants::Svg::black, 5.0});
    painter.translate(width() / 2, height() / 2);
    painter.drawLine(-140, -40, -140, 20);
    painter.drawLine(0, 100, 0, 160);
    painter.drawLine(0, 160, -140, 20);
    painter.drawLine(0, 100, -140, -40);

    painter.drawLine(0, 160, 120, 100);
    painter.drawLine(120, 100, 120, 40);
    painter.drawLine(0, 100, 120, 40);
    painter.drawLine(-140, -40, -20, -100);
    painter.drawLine(-20, -100, 120, 40);

    painter.drawLine(0, 115, 120, 55);
    painter.drawLine(0, 130, 120, 70);
    painter.drawLine(0, 145, 120, 85);

}

