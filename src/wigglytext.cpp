/**
 * @file wigglytext.cpp
 *
 * Implementations for an diner-tablet.
 *
 * MOBILE-APP - Project DinerTablet.
 *
 * Copyright (c) 2014 BlueSalute Company Ltda.
 *
 * @author Ederson Moura - <ederson.moura@bluesalute.com.br>
 *
 * $Id: Exp$
 */

#include "wigglytext.h"

#include <QtWidgets>

WigglyText::WigglyText(QWidget *parent)
    : QWidget(parent)
{
    // Delete widget affter close.
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    QFont fontDT("Great Vibes", 20, QFont::Bold);
    this->setFont(fontDT);

    this->m_step = 0;
    this->m_timer.start(60, this);
}

WigglyText::~WigglyText()
{
}

void WigglyText::paintEvent(QPaintEvent * /* event */)
{
    static const int sineTable[16] = {
        0, 38, 71, 92, 100, 92, 71, 38, 0, -38, -71, -92, -100, -92, -71, -38
    };

    QFontMetrics metrics(font());
    int x = (width() - metrics.width(m_text)) / 2;
    int y = (height() + metrics.ascent() - metrics.descent()) / 2;
    QColor color;

    QPainter painter(this);

    for (int i = 0; i < m_text.size(); ++i) {
        int index = (m_step + i) % 16;
        //color.setHsv((15 - index) * 16, 255, 191);
        color.setHsv((15 - index) * 0, 0, 255); // White
        //color.setBlue(1);
        //color.setHsl();
        painter.setPen(color);
        painter.drawText(x, y - ((sineTable[index] * metrics.height()) / 700),
                         QString(m_text[i]));
        x += metrics.width(m_text[i]);
    }
}

void WigglyText::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timer.timerId()) {
        ++m_step;
        update();
    } else {
        QWidget::timerEvent(event);
    }
}
