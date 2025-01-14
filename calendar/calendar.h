/**
 * @file calendar.h
 * @brief Defines the Calendar class.
 * 
 * Represents a calendar with events and an owner.
 */
#ifndef CALENDAR_H
#define CALENDAR_H

#include <QList>
#include "event.h"
#include "user.h"

/**
 * @class Calendar
 * @brief Represents a calendar with events and an owner.
 * 
 * The Calendar class represents a calendar that contains events and is owned by a user.
 */
class Calendar {
private:
    int calendarID;
    User* owner;
    QList<Event*> events;

public:
    Calendar(int ID, User* owner);

    void addEvent(Event* event);
    bool cancelEvent(Event* event);
    QList<Event*> getEvents() const;

    User* getOwner() const;

    void removeEvent(Event* event);
    void updateEvent(Event* event);
};


#endif // CALENDAR_H
