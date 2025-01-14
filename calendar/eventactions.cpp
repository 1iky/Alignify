/**
 * @file eventactions.cpp
 * @brief Implementation of event action strategies for creating, deleting, and editing events.
 */

#include "eventactions.h"
#include "usermanager.h"
#include <QMessageBox>
#include <QTextCharFormat>

/**
 * @brief Executes the event creation logic.
 *
 * Adds event to calendar and sets background colour based on organizers unique colour.
 *
 * @param calendar A pointer to Calendar object where event is to be added.
 * @param event A pointer to the Event object to be created.
 */
void CreateEventStrategy::execute(Calendar* calendar, Event* event) {
    if (!calendar || !event) return;

    calendar->addEvent(event);

    QTextCharFormat format;
    format.setBackground(UserManager::getInstance()->getUserColor(event->getOrganizer()->getPersonID()));

    QMessageBox::information(nullptr, "Success!",
                             "Event '" + event->getTitle() + "' has been created successfully.");

}

/**
 * @brief Executes the event deletion logic.
 *
 * Removes specified event from the calendar.
 *
 * @param calendar A pointer to the Calendar object where the event is stored.
 * @param event A pointer to the Event object to be deleted.
 */
void DeleteEventStrategy::execute(Calendar* calendar, Event* event) {
    if (!calendar || !event) return;

    calendar->removeEvent(event);

    QMessageBox::information(nullptr, "Success", "Event deleted successfully.");
}

/**
 * @brief Executes the event editing logic.
 *
 * Updates the details of the specified event in the calendar.
 *
 * @param calendar A pointer to the Calendar object where the event is stored.
 * @param event A pointer to the Event object to be updated.
 */
void EditEventStrategy::execute(Calendar* calendar, Event* event) {
    if (!calendar || !event) return;

    calendar->updateEvent(event);

    QMessageBox::information(nullptr, "Success", "Event updated successfully.");
}
