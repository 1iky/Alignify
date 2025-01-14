/**
 * @file eventbuilder.cpp
 * @brief Implementation of the EventBuilder class.
 *        Use of the Builder design pattern.
 */
#include "eventbuilder.h"
#include <QDebug>

/**
 * @brief Initializes the builder with default values for all event properties.
 */
EventBuilder::EventBuilder() : eventID(-1), title(""), description(""), location(""), dateTime(QDateTime()), organizer(nullptr) {}

/**
 * @brief Sets the Event ID
 * @param id Unique ID for event
 * @return A reference to current EventBuilder instance for method chaining.
 */
EventBuilder& EventBuilder::setEventID(int id) {
    eventID = id;
    return *this;
}

/**
 * @brief Sets the title of the event.
 * @param t The title of the event
 * @return A reference to the current EventBuilder instance for method chaining.
 */
EventBuilder& EventBuilder::setTitle(const QString& t) {
    title = t;
    return *this;
}

/**
 * @brief Sets the description of the event.
 * @param desc The description of the event.
 * @return A reference to the current EventBuilder instance for method chaining.
 */
EventBuilder& EventBuilder::setDescription(const QString& desc) {
    description = desc;
    return *this;
}

/**
 * @brief Sets the location of the event.
 * @param loc The location of the event.
 * @return A reference to the current EventBuilder instance for method chaining.
 */
EventBuilder& EventBuilder::setLocation(const QString& loc) {
    location = loc;
    return *this;
}

/**
 * @brief Sets the date and time of the event.
 * @param dt A QDateTime object representing the event's date and time.
 * @return A reference to current EventBuilder instance for method chaining.
 */
EventBuilder& EventBuilder::setDateTime(const QDateTime& dt) {
    dateTime = dt;
    return *this;
}

/**
 * @brief Sets the organizer of the event.
 * @param org A pointer to the User object representing the organizer of the event.
 * @return A reference to the current EventBuilder instance for method chaining.
 */
EventBuilder& EventBuilder::setOrganizer(User* org) {
    organizer = org;
    return *this;
}

/**
 * @brief Validates that all required fields have been set for the event.
 * @return True if builder contains valid data for creating an Event
 */
bool EventBuilder::isValid() const {
    return !title.isEmpty() &&
           dateTime.isValid() &&
           organizer != nullptr &&
           eventID != -1;
}

/**
 * @brief Builds and returns a new Event object.
 * @return A pointer to the newly created Event object, or nullptr if validation fails.
 */
Event* EventBuilder::build() {
    if (!isValid()) {
        qDebug() << "Cannot build event: Invalid parameters";
        return nullptr;
    }
    return new Event(eventID, title, description, dateTime, location, organizer);
}
