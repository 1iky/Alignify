/**
 * @file person.cpp
 * @brief Implements the Person class.
 *        Base class representing individuals with a unique ID, first name, last name.
 */
#include "person.h"

/**
 * @brief Construct a Person object.
 *
 * @param id The unique ID for person.
 * @param firstName The first name of person.
 * @param lastName The last name of the person.
 */
Person::Person(int id, const QString& firstName, const QString& lastName)
    : personID(id), firstName(firstName), lastName(lastName) {}

/**
 * @brief Gets unique ID of the person.
 *
 * @return The person's unique ID as integer.
 */
int Person::getPersonID() const {
    return personID;
}

/**
 * @brief Gets the first name of the person.
 *
 * @return The first name as a string.
 */
QString Person::getFirstName() const {
    return firstName;
}

/**
 * @brief Gets the last name of the person.
 *
 * @return The last name as a string.
 */
QString Person::getLastName() const{
    return lastName;
}

/**
 * @brief Gets the full name of the person with space between.
 *
 * @return The full name as a string.
 */
QString Person::getFullName() const {
    return firstName + " " + lastName;
}

/**
 * @brief Sets first name of the person.
 *
 * @param first The updated first name as string.
 */
void Person::setFirstName(const QString& first){
    firstName = first;
}

/**
 * @brief Sets the last name of the person.
 *
 * @param last The new last name as a string.
 */
void Person::setLastName(const QString& last){
    lastName = last;
}
