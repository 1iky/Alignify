/**
 * @file calendarmanager.h
 * @brief Defines the CalendarManager class.
 * 
 * Manages calendars for users.
 */
#ifndef CALENDARMANAGER_H
#define CALENDARMANAGER_H

#include <QMap>
#include "calendar.h"
#include "user.h"

/**
 * @class Calendar
 * @brief Manages calendars for users.
 * 
 * The CalendarManager class is responsible for creating, storing, and managing calendars for users.
 */
class CalendarManager {
private:
    static CalendarManager* instance;
    QMap<int, Calendar*> userCalendars;

    CalendarManager();

public:
    static CalendarManager* getInstance();
    CalendarManager(const CalendarManager&) = delete;
    CalendarManager& operator=(const CalendarManager&) = delete;
    Calendar* createUserCalendar(User* user);
    Calendar* getUserCalendar(int userID);
    QList<Calendar*> getAllCalendars();
    void deleteCalendar(int userID);

};


#endif // CALENDARMANAGER_H
