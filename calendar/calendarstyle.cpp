/**
 * @file calendarstyle.cpp
 * @brief Implementation of the CalendarStyle class
 */
#include "calendarstyle.h"
#include <QTextCharFormat>

void CalendarStyle::applyStyle(QCalendarWidget* calendar) {
    applyCustomStyle(calendar);
}

void CalendarStyle::applyCustomStyle(QCalendarWidget* calendar) {
    if (!calendar) return;

    // apply the stylesheet
    calendar->setStyleSheet(getBaseStyleSheet());

    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendar->setGridVisible(true);
}

QString CalendarStyle::getBaseStyleSheet() {
    return QString(
        // Calendar header
        "QCalendarWidget QToolButton {"
        "   color:black !important;"
        "   font-size:24px;"
        "   icon-size: 50px 50px;"
        "   background-color: #dbebeb !important;"
        "}"

        // Navigation bar
        "QCalendarWidget QWidget#qt_calendar_navigationbar {"
        "    background-color: #dbebeb !important;"
        "    padding: 10px;"
        "}"

        // Prev/Next buttons
        "QCalendarWidget QToolButton {"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 4px;"
        "    margin: 2px;"
        "}"

        "QCalendarWidget QMenu {"
        "    width: 150px;"
        "    left:20px;"
        "    color:black !important;"
        "    font-size: 20px;"
        "    background-color: white !important;"
        "}"

        "QCalendarWidget QSpinBox {"
        "    width: 100px;"
        "    height: 60px;"
        "    font-size: 20px;"
        "    color: black !important;"
        "    background-color: white !important;"
        "}"

        "QCalendarWidget QSpinBox::up-button {"
        "    subcontrol-origin: border;"
        "    subcontrol-position: left;"
        "    width: 30px;"
        "    height: 60px;"
        "}"


        "QCalendarWidget QSpinBox::down-button {"
        "    subcontrol-origin: border;"
        "    subcontrol-position: right;"
        "    width: 30px;"
        "    height: 60px;"
        "}"


        "QCalendarWidget QToolButton:hover {"
        "    background-color: #d3d3d3 !important;"
        "}"


        "QCalendarWidget QTableView::section {"
        "    background-color: #f4acb7 !important;"
        "    color: black !important;"
        "    font-weight: bold;"
        "    border: none;"
        "}"


        "QCalendarWidget QAbstractItemView:enabled {"
        "    font-size: 15px;"
        "    color: black;"
        "    font-weight: bold !important;"
        "    selection-background-color: #d9d9d9;"
        "    selection-color: black !important;"
        "}"


        "QCalendarWidget QAbstractItemView:disabled {"
        "    color: #91bad6 !important;"
        "}"


        "QCalendarWidget QAbstractItemView:enabled:selected {"
        "    background-color: #dbebeb !important;"
        "}"


        );
}


