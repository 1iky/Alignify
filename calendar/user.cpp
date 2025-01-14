/**
 * @file user.cpp
 * @brief Implementation of the User class
 *
 * This class represents an individual user with unique ID, first name, last name.
 */
#include "user.h"

/**
 * @brief Constructs a User object.
 *
 * @param id The unique identifier for the user.
 * @param firstName The first name of the user.
 * @param lastName The last name of the user.
 */
User::User(int id, const QString& firstName, const QString& lastName)
    : Person(id, firstName, lastName) {}


