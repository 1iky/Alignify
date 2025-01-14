/**
 * @file event.cpp
 * @brief Implementation of the Event class.
 *
 * Represents an event with ID, title, description, date&time, location, and organizer.
 * Provides methods to access and modify attributes.
 * Designed to encapsulate event data.
 */
#include "event.h"

/**
 * @brief Constructs an Event object.
 * @param id The unique ID of the event.
 * @param title The description of the event.
 * @param desc The date and time of the event.
 * @param date The date and time of the event.
 * @param location The location of the event.
 * @param org A pointer to the User object representing event's organizer.
 */
Event::Event(int id, const QString& title, const QString& desc, const QDateTime& date, const QString& location, User* org)
    : eventID(id), title(title), description(desc), date(date), location(location), organizer(org) {}

/**
 * @brief Updates the details of the event.
 * @param newTitle The new title for the event.
 * @param newDesc The new description for the event.
 * @param newDate The new date and time for the event.
 * @param newLocation The new location for the event.
 */
void Event::updateEvent(const QString& newTitle, const QString& newDesc, QDateTime& newDate, const QString& newLocation){
    title = newTitle;
    description = newDesc;
    date = newDate;
    location = newLocation;
}

/**
 * @brief Gets the title of the event.
 * @return The title of the event.
 */
QString Event::getTitle() const{
    return title;
}

/**
 * @brief Gets the date and time of the event.
 * @return A QDateTime object representing the event's date and time.
 */
QDateTime Event::getDate() const{
    return date;
}

/**
 * @brief Gets the description of the event.
 * @return The description of the event.
 */
QString Event::getDescription() const {
    return description;
}

/**
 * @brief Gets the organizer of the event.
 * @return A pointer to the User object representing the event's organizer.
 */
User* Event::getUser() const {
    return organizer;
}

/**
 * @brief Gets the full name of event organizer.
 * @return The full name of the organizer.
 */
QString Event::getOrganizerName() const {
    if (organizer) {
        return organizer->getFirstName() + " " + organizer->getLastName();
    }
    return "No Organizer";
}

/**
 * @brief Gets the full name of the event's organizer.
 * @return The full name of the organizer.
 */
QString Event::getLocation() const {
    return location;
}

/**
 * @brief Gets the ID of the event.
 * @return The ID of the event.
 */
int Event::getEventID() const {
    return eventID;

}

/**
 * @brief Gets the organizer of the event.
 * @return A pointer to the User object representing the event's organizer.
 */
User* Event::getOrganizer() const {
    return organizer;
}
