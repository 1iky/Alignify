/**
 * @file calendarmanager.cpp
 * @brief Implementation of the CalendarManager class
 */
#include "calendarmanager.h"

/**
 * @brief Initializes the CalendarManager instance.
 */
CalendarManager* CalendarManager::instance = nullptr;

/**
 * @brief Constructs a CalendarManager object.
 */
CalendarManager::CalendarManager() {}

/**
 * @brief Gets the singleton instance of CalendarManager.
 * @return A pointer to the CalendarManager instance.
 */
CalendarManager* CalendarManager::getInstance() {
    if (instance == nullptr) {
        instance = new CalendarManager();
    }
    return instance;
}

/**
 * @brief Creates a new calendar for a user.
 * @param user The user to create the calendar.
 * @return A pointer to the new calendar.
 */
Calendar* CalendarManager::createUserCalendar(User* user) {
    int userID = user->getPersonID();
    Calendar* newCalendar = new Calendar(userID, user);
    userCalendars[userID] = newCalendar;

    return newCalendar;
}

/**
 * @brief Gets the calendar for a user.
 * @param userID The ID of the user.
 * @return A pointer to the user's calendar, or nullptr if not found.
 */
Calendar* CalendarManager::getUserCalendar(int userID) {
    return userCalendars.value(userID, nullptr);
}

/**
 * @brief Gets all calendars.
 * @return A list of all calendars.
 */
QList<Calendar*> CalendarManager::getAllCalendars() {
    return userCalendars.values();
}

/**
 * @brief Deletes the calendar for a user.
 * @param userID The ID of the user.
 * @return A pointer to the deleted calendar, or nullptr if not found.
 */
void CalendarManager::deleteCalendar(int userID) {
    if (userCalendars.contains(userID)) {
        Calendar* calendar = userCalendars[userID];
        userCalendars.remove(userID);
        delete calendar;
    }
}
