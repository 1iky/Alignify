/**
 * @file person.h
 * @brief Defines the Person class.
 * 
 * The Person class represents an individual with a unique ID, first name, and last name.
 */
#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDateTime>

/**
 * @class Person
 * @brief Represents an individual with a unique ID, first name, and last name.
 * 
 * The Person class represents an individual with a unique ID, first name, and last name.
 */
class Person {
protected:
    int personID;
    QString firstName;
    QString lastName;

public:
    Person(int id, const QString& firstName, const QString& lastName);

    virtual ~Person() = default;

    int getPersonID() const;
    QString getFirstName() const;\
    QString getLastName() const;
    QString getFullName() const;

    void setFirstName(const QString& first);
    void setLastName(const QString& last);


};





#endif // PERSON_H
