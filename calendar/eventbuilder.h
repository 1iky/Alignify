/**
 * @file eventbuilder.h
 * @brief Defines the EventBuilder class.
 * 
 * The EventBuilder class is responsible for creating Event objects.
 */
#ifndef EVENTBUILDER_H
#define EVENTBUILDER_H

#include <QString>
#include <QDateTime>
#include "event.h"
#include "user.h"

/**
 * @class EventBuilder
 * @brief Builds Event objects.
 * 
 * The EventBuilder class is responsible for building Event objects.
 */
class EventBuilder {
    int eventID;
    QString title;
    QString description;
    QString location;
    QDateTime dateTime;
    User* organizer;

public:
    EventBuilder();

    //interface methods
    EventBuilder& setEventID(int id);
    EventBuilder& setTitle(const QString& t);
    EventBuilder& setDescription(const QString& desc);
    EventBuilder& setLocation(const QString& loc);
    EventBuilder& setDateTime(const QDateTime& dt);
    EventBuilder& setOrganizer(User* org);

    // validation check to make sure all required fields are set
    bool isValid() const;

    //build method to create event
    Event* build();

};


#endif // EVENTBUILDER_H
