/**
 * @file eventdialog.h
 * @brief Defines the EventDialog class.
 * 
 * The EventDialog class is a dialog window for creating and editing events.
 */
#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "event.h"
#include "eventbuilder.h"

/**
 * @class EventDialog
 * @brief Dialog window for creating and editing events.
 * 
 * The EventDialog class allows users to input event details such as title, description, date/time, and location.
 */
class EventDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit* titleEdit;
    QTextEdit* descriptionEdit;
    QDateTimeEdit* dateTimeEdit;
    QLineEdit* locationEdit;
    QPushButton* createButton;
    QPushButton* cancelButton;

public:
    EventDialog(QWidget* parent = nullptr);
    Event* getEventData(EventBuilder& builder, int eventId, User* organizer);
    void setEventData(Event* event);

private slots:
    void onCreateClicked();
};

#endif // EVENTDIALOG_H
