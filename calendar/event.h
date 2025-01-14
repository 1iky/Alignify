/**
 * @file event.h
 * @brief Defines the Event class.
 * 
 * Represents an event with a title, description, date&time, location, and organizer.
 */
#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDateTime>
#include <QSet>
#include "user.h"

/**
 * @class Event
 * @brief Represents an event with a title, description, date&time, location, and organizer.
 * 
 * The Event class represents an event with a title, description, date&time, location, and organizer.
 */
class Event {
private:
    int eventID;
    QString title;
    QString description;
    QDateTime date;
    QString location;
    User* organizer;
    QSet<User*> participants;

public:
    Event(int id, const QString& title, const QString& desc, const QDateTime& date, const QString& location, User* org);

    void updateEvent(const QString& newTitle, const QString& newDesc, QDateTime& newDate, const QString& newLocation);

    QSet<User*> getAvaiableUsers() const;
    QString getTitle() const;
    QDateTime getDate() const;
    QString getDescription() const;
    User* getUser() const;
    QString getOrganizerName() const;

    QString getLocation() const;
    int getEventID() const;
    User* getOrganizer() const;

};


#endif // EVENT_H
