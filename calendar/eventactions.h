/**
 * @file eventactions.h
 * @brief Defines the EventActions class and its subclasses.
 */
#ifndef EVENTACTIONS_H
#define EVENTACTIONS_H

#include "calendar.h"
#include "event.h"

/**
 * @class EventActions
 * @brief Abstract class for event actions.
 * 
 * The EventActions class is an abstract class that defines the interface for event actions.
 */
class EventActions {
public:
    virtual ~EventActions() = default;
    virtual void execute(Calendar* calendar, Event* event) = 0;

};

/**
 * @class CreateEventStrategy
 * @brief Concrete strategy for creating an event.
 * 
 * The CreateEventStrategy class is a concrete strategy for creating an event.
 */
class CreateEventStrategy : public EventActions {
public:
    void execute(Calendar* calendar, Event* event) override;
};

/**
 * @class DeleteEventStrategy
 * @brief Concrete strategy for deleting an event.
 * 
 * The DeleteEventStrategy class is a concrete strategy for deleting an event.
 */
class DeleteEventStrategy : public EventActions {
public:
    void execute(Calendar* calendar, Event* event) override;
};

/**
 * @class EditEventStrategy
 * @brief Concrete strategy for editing an event.
 * 
 * The EditEventStrategy class is a concrete strategy for editing an event.
 */
class EditEventStrategy : public EventActions {
public:
    void execute(Calendar* calendar, Event* event) override;
};

#endif // EVENTACTIONS_H
