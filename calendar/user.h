/**
 * @file user.h
 * @brief Defines the User class.
 * 
 * The User class represents an individual user with a unique ID, first name, and last name.
 */
#ifndef USER_H
#define USER_H

#include "person.h"
#include <QMap>
#include <QDateTime>

/**
 * @class User
 * @brief Represents an individual user with a unique ID, first name, and last name.
 * 
 * The User class represents an individual user with a unique ID, first name, and last name.
 */
class User : public Person {
private:


public:
    User(int id, const QString& firstName, const QString& lastName);

};




#endif // USER_H
