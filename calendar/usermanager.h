/**
 * @file usermanager.h
 * @brief Defines the UserManager class.
 * 
 * The UserManager class is responsible for managing users and their unique IDs and colours.
 */
#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QMap>
#include <QColor>
#include <QVector>
#include "user.h"

/**
 * @class UserManager
 * @brief Manages users and their unique IDs and colours.
 * 
 * The UserManager class is responsible for creating, storing, and managing User objects.
 */
class UserManager {
private:
    static UserManager* instance;
    QMap<int, User*> users;
    QMap<int, QColor> userColors;
    int nextUserID;

    UserManager();

public:
    static UserManager* getInstance();
    UserManager(const UserManager&) = delete;
    UserManager& operator=(const UserManager&) = delete;

    User* createUser(const QString& firstName, const QString& lastName);
    User* getUser(int id);
    QColor getUserColor(int id);
    QMap<int, User*> getAllUsers() const;
    void deleteUser(int userID);

private:
    void assignUserColor(int userID);
};

#endif // USERMANAGER_H
