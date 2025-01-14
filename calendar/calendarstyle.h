/**
 * @file calendarstyle.h
 * @brief Defines the CalendarStyle class.
 * 
 * Provides methods to apply custom styles to a QCalendarWidget.
 */
#ifndef CALENDARSTYLE_H
#define CALENDARSTYLE_H

#include <QCalendarWidget>
#include <QColor>
#include <QString>

/**
 * @class CalendarStyle
 * @brief Provides methods to apply custom styles to a QCalendarWidget.
 */
class CalendarStyle {
private:
    static QString getBaseStyleSheet();

public:
    CalendarStyle() = default;
    static void applyStyle(QCalendarWidget* calendar);
    static void applyCustomStyle(QCalendarWidget* calendar);

};


#endif // CALENDARSTYLE_H
