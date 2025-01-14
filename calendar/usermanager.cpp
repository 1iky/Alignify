/**
 * @file usermanager.cpp
 * @brief Implementation of the UserManager class
 * Implements Singleton pattern for managing users and their unique IDs and colours.
 */
#include "usermanager.h"

// initialization
UserManager* UserManager::instance = nullptr;

/**
 * @brief Initializes the user ID counter to 1.
 */
UserManager::UserManager() : nextUserID(1) {}

/**
 * @brief Gets Singleton instance of UserManager
 *
 * @return A pointer to the singleton UserManager instance.
 */
UserManager* UserManager:: getInstance() {
    if (instance == nullptr) {
        instance = new UserManager();
    }
    return instance;
}

/**
 * @brief Creates new user with unique ID and assigns a colour.
 *
 * @param firstName The first name of the user.
 * @param lastName The last name of the user.
 * @return A pointer to newly created User object.
 */
User* UserManager::createUser(const QString& firstName, const QString& lastName) {
    User* newUser = new User(nextUserID, firstName, lastName);
    users[nextUserID] = newUser;
    assignUserColor(nextUserID);
    nextUserID++;
    return newUser;
}
/**
 * @brief Gets user by unique ID
 * @param id The unique ID of user.
 * @return A pointer to the User object if found, or nullptr if not.
 */
User* UserManager::getUser(int id) {
    return users.value(id, nullptr);
}
/**
 * @brief Gets the colour associated with a user.
 *
 * @param id The unique ID of the user.
 * @return The colour assigned to the user.
 */
QColor UserManager::getUserColor(int id) {
    return userColors.value(id);
}

/**
 * @brief Gets all the users managed by UserManager
 *
 * @return A Map containing all users, indexed by their unique IDs.
 */
QMap<int, User*> UserManager::getAllUsers() const {
    return users;
}

/**
 * @brief Assigns unique colour to user.
 *
 * @param userID The unique ID of the user
 */
void UserManager::assignUserColor(int userID) {
    static const QVector<QColor> colors = {
        QColor(251, 248, 204), // Yellow
        QColor(253, 228, 207), // beige pink
        QColor(255, 207, 210), // pink
        QColor(241, 192, 232), // magenta
        QColor(207, 186, 240), // purple
        QColor(163, 196, 243), // periwinkle
        QColor(144, 219, 244), // blue
        QColor(142, 236, 245), // light blue
        QColor(152, 245, 225), // sea green
        QColor(185, 251, 192)  // green
    };
    static int colorIndex = 0;
    userColors[userID] = colors[colorIndex % colors.size()];
    colorIndex++;
}

/**
 * @brief Deletes a user by their unique ID.
 *
 * @param userID The unique ID of the user to be deleted.
 */
void UserManager::deleteUser(int userID){
    if (users.contains(userID)) {
        User* user = users[userID];
        users.remove(userID);
        delete user;
    }
}
