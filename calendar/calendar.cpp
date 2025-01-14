/**
 * @file calendar.cpp
 * @brief Implementation of the Calendar class
 */
#include "calendar.h"

/**
 * @brief Constructs a Calendar object.
 * @param ID The unique identifier for the calendar.
 * @param owner A pointer to the User object representing the calendar's owner.
 */
Calendar::Calendar(int ID, User* owner)
    : calendarID(ID), owner(owner) {}

/**
 * @brief Adds an event to the calendar.
 * @param event A pointer to the Event object to add.
 */
void Calendar::addEvent(Event* event) {
    events.append(event);
}

/**
 * @brief Cancels an event in the calendar.
 * @param event A pointer to the Event object to cancel.
 * @return true if the event was successfully cancelled, false otherwise.
 */
bool Calendar::cancelEvent(Event* event) {
    return events.removeOne(event);
}

/**
 * @brief Gets all events in the calendar.
 * @return A list of all events in the calendar.
 */
QList<Event*> Calendar::getEvents() const {
    return events;
}

/**
 * @brief Gets the owner of the calendar.
 * @return A pointer to the User object representing the calendar's owner.
 */
User* Calendar::getOwner() const{
    return owner;
}

/**
 * @brief Removes an event from the calendar.
 * @param event A pointer to the Event object to remove.
 * @note The event is deleted from memory.
 */
void Calendar::removeEvent(Event* event) {
    if (!event) return;

    events.removeOne(event);
    delete event;
}

/**
 * @brief Updates an event in the calendar.
 * @param event A pointer to the updated Event object.
 * @note The existing event is replaced with the updated event.
 */
void Calendar::updateEvent(Event* event) {
    if (!event) return;

    for(int i = 0; i < events.size(); i++) {
        if (events[i]->getEventID() == event->getEventID()) {
            delete events[i];
            events[i] = event;
            break;
        }
    }
}
