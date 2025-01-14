/**
 * @file mainwindow.cpp
 * @brief Implementation of the MainWindow class
 * 
 * This class represents the main window of the application.
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eventdialog.h"
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include "calendarstyle.h"
#include "calendarmanager.h"
#include "usermanager.h"
/**
 * @brief Constructs the main window.
 * @param parent The parent widget.
 * 
 * Initializes the main window and sets up the user interface.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , createStrategy(std::make_unique<CreateEventStrategy>())
    , deleteStrategy(std::make_unique<DeleteEventStrategy>())
    , editStrategy(std::make_unique<EditEventStrategy>())
    , ui(new Ui::MainWindow)
{

    // light mode
    QApplication::setStyle("fusion");
    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::PlaceholderText, Qt::darkGray);
    lightPalette.setColor(QPalette::AlternateBase, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::ToolTipBase, Qt::white);
    lightPalette.setColor(QPalette::ToolTipText, Qt::black);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::ButtonText, Qt::black);
    lightPalette.setColor(QPalette::BrightText, Qt::white);
    lightPalette.setColor(QPalette::Highlight, QColor(75, 123, 245));
    lightPalette.setColor(QPalette::HighlightedText, Qt::white);
    QApplication::setPalette(lightPalette);


    //setup user interface
    setupUI();
    createConnections();

    currentUser = (new User(1, "", ""));
    userCalendar = new Calendar(1, currentUser);
}

/**
 * @brief Sets up the user interface.
 */
void MainWindow::setupUI()
{
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    // Calendar section
    QVBoxLayout* calendarLayout = new QVBoxLayout();
    calendarWidget = new QCalendarWidget();
    CalendarStyle::applyStyle(calendarWidget); // Apply style to calendar
    calendarLayout->addWidget(calendarWidget);

    // User + Event list section
    QVBoxLayout* rightLayout = new QVBoxLayout();

    // "Users" Section
    QFrame* userFrame = new QFrame();
    userFrame->setStyleSheet("QFrame { background-color: #F5F5F5; border: 1px solid #C0C0C0; border-radius: 10px; padding: 5px; }");
    QVBoxLayout* userFrameLayout = new QVBoxLayout(userFrame);

    QLabel* userLabel = new QLabel("Users");
    // Set font to bold
    QFont font = userLabel->font();
    font.setBold(true);
    font.setPointSize(16);
    userLabel->setFont(font);
    // Align center
    userLabel->setAlignment(Qt::AlignCenter);

    userList = new QListWidget();
    userList->setStyleSheet("QListWidget::item { margin: 2px 0;}");

    createUserButton = new QPushButton("Create User");

    QFont fontButton = userLabel->font();
    fontButton.setPointSize(12);
    createUserButton->setFont(fontButton);
    createUserButton->setStyleSheet("background-color: #DBEBEB;");

    //list widget
    QFont listFont = userList->font();
    listFont.setPointSize(12);
    userList->setFont(listFont);

    userFrameLayout->addWidget(userLabel);
    userFrameLayout->addWidget(userList);
    userFrameLayout->addWidget(createUserButton);

    rightLayout->addWidget(userFrame);

    // "User Events" Section
    QFrame* userEventsFrame = new QFrame();
    userEventsFrame->setStyleSheet("QFrame { background-color: #F5F5F5; border: 1px solid #C0C0C0; border-radius: 10px; padding: 5px; }");
    QVBoxLayout* userEventsFrameLayout = new QVBoxLayout(userEventsFrame);

    QLabel* eventLabel = new QLabel("User Events");
    eventLabel->setFont(font);
    eventLabel->setAlignment(Qt::AlignCenter);

    eventList = new QListWidget();
    eventList->setStyleSheet("QListWidget::item { margin: 2px 0;}");

    userEventsFrameLayout->addWidget(eventLabel);
    userEventsFrameLayout->addWidget(eventList);
    eventList->setFont(listFont);

    rightLayout->addWidget(userEventsFrame);

    // "Created Events" Section
    QFrame* createdEventsFrame = new QFrame();
    createdEventsFrame->setStyleSheet("QFrame { background-color: #F5F5F5; border: 1px solid #C0C0C0; border-radius: 10px; padding: 5px; }");
    QVBoxLayout* createdEventsFrameLayout = new QVBoxLayout(createdEventsFrame);

    QLabel* createdEventLabel = new QLabel("Created Events");
    createdEventLabel->setFont(font);
    createdEventLabel->setAlignment(Qt::AlignCenter);

    createdEventList = new QListWidget();
    createdEventList->setStyleSheet("QListWidget::item { margin: 2px 0;}");

    createEventButton = new QPushButton("Create Event");
    createEventButton->setFont(fontButton);
    createEventButton->setStyleSheet("background-color: #DBEBEB;");
    createdEventList->setFont(listFont);

    createdEventsFrameLayout->addWidget(createdEventLabel);
    createdEventsFrameLayout->addWidget(createdEventList);
    createdEventsFrameLayout->addWidget(createEventButton);

    rightLayout->addWidget(createdEventsFrame);

    mainLayout->addLayout(calendarLayout, 2);
    mainLayout->addLayout(rightLayout, 1);

    setCentralWidget(centralWidget);
    setWindowTitle("Alignify");
    resize(1240, 750);
}

/**
 * @brief Connects widget buttons to methods.
 */
void MainWindow::createConnections() {
    connect(calendarWidget, &QCalendarWidget::clicked,
            this, &MainWindow::onDateSelected); // on date selected
    connect(createEventButton, &QPushButton::clicked,
            this, &MainWindow::onCreateEventClicked); //on create event
    connect(createUserButton, &QPushButton::clicked,
            this, &MainWindow::onCreateUserClicked); // on create user
    connect(eventList, &QListWidget::itemClicked,
            this, &MainWindow::onEventItemClicked); // on USER event clicked
    connect(userList, &QListWidget::itemClicked,
            this, &MainWindow::onUserItemClicked); // on user clicked
    connect(createdEventList, &QListWidget::itemClicked,
            this, &MainWindow::onEventItemClicked); // on CREATED event clicked
}

/**
 * @brief on "Create User" button clicked, display dialog to create user
 */
void MainWindow::onCreateUserClicked() {
    QDialog dialog(this);
    dialog.setWindowTitle("Create User");

    // create user dialog ui
    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    QLineEdit* firstNameEdit = new QLineEdit();
    QLineEdit* lastNameEdit = new QLineEdit();
    QPushButton* browseButton = new QPushButton("Browse ICS File");
    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");

    //indicate required fields *
    firstNameEdit->setPlaceholderText("First Name *");
    lastNameEdit->setPlaceholderText("Last Name *");
    browseButton->setText("Browse ICS File *");
    layout->addWidget(firstNameEdit);
    layout->addWidget(lastNameEdit);
    layout->addWidget(browseButton);

    // ok and cancel button
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    // import button clicked
    QString selectedFile;
    connect(browseButton, &QPushButton::clicked, [&]() {
        selectedFile = QFileDialog::getOpenFileName(this,
            "Select ICS File", "", "ICS Files (*.ics)");
        if (!selectedFile.isEmpty()) {
            browseButton->setText("Selected: " + QFileInfo(selectedFile).fileName()); //set button text as selected file name
        }
    });

    QString firstName;
    QString lastName;

    //make sure user enters all required fields
    connect(okButton, &QPushButton::clicked, [&](){
        firstName = firstNameEdit->text().trimmed();
        lastName = lastNameEdit->text().trimmed();

        if (firstName.isEmpty() || lastName.isEmpty() || selectedFile.isEmpty()) {
            QString errorMessage = "Please fill out all required fields:\n";
            if (firstName.isEmpty()){
                errorMessage += "- First Name\n";
            }
            if (lastName.isEmpty()){
                errorMessage += "- Last Name\n";
            }
            if (selectedFile.isEmpty()){
                errorMessage += "- ICS File\n";
            }

            QMessageBox::warning(&dialog, "Required Fields", errorMessage);
            return;
        }

        dialog.accept();
    });

    // reject on cancel button clicked
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    // OK button clicked
    if (dialog.exec() == QDialog::Accepted) {
        // create user using usermanager singleton
        User* newUser = UserManager::getInstance()->createUser(firstName,  lastName);
        // create user using calendarmanager singleton
        Calendar* newCalendar = CalendarManager::getInstance()->createUserCalendar(newUser);

        users[newUser->getPersonID()] = newUser;
        userCalendars[newUser->getPersonID()] = newCalendar;

        // display user on user list
        QString displayName = QString("%1 %2").arg(firstName, lastName);
        QListWidgetItem* item = new QListWidgetItem(displayName, userList);
        item->setData(Qt::UserRole, newUser->getPersonID());

        // assign unique colour
        QColor userColor = UserManager::getInstance()->getUserColor(newUser->getPersonID());
        item->setBackground(userColor);

        // text color change depending on background
        if (userColor.lightness() < 128) {
            item->setForeground(Qt::white);
        }


        loadICSFile(selectedFile, newUser);
        //nextUserID++;
        updateUserEventsList();

    }
}


/**
 * @brief on import ICS file, load events into user calendar.
 * @param filePath The path to the ICS file.
 * @param user The user to assign the events to.
 * 
 * Loads user events from an ICS file into the user's calendar.
 */
void MainWindow::loadICSFile(const QString& filePath, User* user) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    // split the file into events
    QStringList events = content.split("BEGIN:VEVENT");
    static int nextEventID = 1;

    Calendar* userCalendar = CalendarManager::getInstance()->getUserCalendar(user->getPersonID());

    for (int i = 1; i < events.size(); i++) { // Start from 1 to skip header
        QStringList eventLines = events[i].split('\n');
        Event* newEvent = parseICSEvent(eventLines, user, nextEventID);

        if (newEvent) {
            userCalendar->addEvent(newEvent);

            // mark the date on calendar
            QTextCharFormat format;
            format.setBackground(QColor(200,230,255));
            calendarWidget->setDateTextFormat(newEvent->getDate().date(), format);
        }
    }

    updateUserEventsList();
}

/**
 * @brief Parses an ICS event from a list of lines.
 * @param eventLines The list of lines representing the event.
 * @param user The user to assign the event to.
 * @param nextEventID The ID of the next event.
 * 
 * @return A pointer to the parsed event, or nullptr if parsing failed.
 */
Event* MainWindow::parseICSEvent(const QStringList& eventLines, User* user, int& nextEventID) {
    QString summary;
    QString description;
    QString location;
    QDateTime startDate;

    for (const QString& line : eventLines) {
        if (line.startsWith("SUMMARY:")) {
            summary = line.mid(8).trimmed();
        }
        else if (line.startsWith("DESCRIPTION:")) {
            description = line.mid(12).trimmed();
        }
        else if (line.startsWith("LOCATION:")) {
            location = line.mid(9).trimmed();
        }
        else if (line.startsWith("DTSTART:")) {
            startDate = parseICSDateTime(line.mid(8).trimmed());
        }
    }

    if (!summary.isEmpty() && startDate.isValid()) {
        Event* event = new Event(nextEventID++, summary, description, startDate, location, user);
        return event;
    }

    return nullptr;
}

/**
 * @brief Parses an ICS date-time string.
 * @param dateTimeStr The date-time string to parse.
 * @return A QDateTime object representing the parsed date-time.
 * 
 * Parses an ICS date-time string into a QDateTime object.
 */
QDateTime MainWindow::parseICSDateTime(const QString& dateTimeStr) {
    // handle different date-time formats
    QRegularExpression pattern("(\\d{8})(T\\d{6}Z?)?");
    QRegularExpressionMatch match = pattern.match(dateTimeStr);

    if (match.hasMatch()) {
        QString dateStr = match.captured(1);
        QString timeStr = match.captured(2);

        QDate date = QDate::fromString(dateStr, "yyyyMMdd");
        QTime time;

        if (!timeStr.isEmpty()) {
            timeStr = timeStr.mid(1, 6); // Remove 'T' and 'Z'
            time = QTime::fromString(timeStr, "HHmmss");
        } else {
            time = QTime(0, 0); // Default to midnight
        }

        return QDateTime(date, time);
    }

    return QDateTime();
}

/**
 * @brief Shows all events for the selected date.
 * @param date The selected date.
 * 
 * Displays all events for the selected date in the event list.
 * 
 */
void MainWindow::onDateSelected(const QDate& date) {
    eventList->clear();
    createdEventList->clear();

    // Populate events for created events
    for (Event* event : userCalendar->getEvents()) {
        if (event->getDate().date() == date) {
            QListWidgetItem* item = new QListWidgetItem(event->getTitle(), createdEventList);
            item->setData(Qt::UserRole, QVariant::fromValue(event));
        }
   }

   // get all calendars
    QList<Calendar*> calendars = CalendarManager::getInstance()->getAllCalendars();

    // Add events from user ics calendar
    for (Calendar* calendar : calendars) {
        User* user = calendar->getOwner();
        QColor userColor = UserManager::getInstance()->getUserColor(user->getPersonID());
        // get user events
        for (Event* event : calendar->getEvents()) {
            if (event->getDate().date() == date) {
                // create display text in events list that shows title of event and organizer
                QString displayText = QString("%1: %2")
                    .arg(event->getOrganizerName())
                    .arg(event->getTitle());

                // create list item with display text into the events list
                QListWidgetItem* item = new QListWidgetItem(displayText, eventList);

                item->setData(Qt::UserRole, QVariant::fromValue(event));

                // Set the item's background color to match the user's color
                item->setBackground(userColor);
            }
        }
    }
}

/**
 * @brief Creates a new event.
 * 
 * Displays a dialog to create a new event and adds it to the calendar.
 */
void MainWindow::onCreateEventClicked() {
    EventDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        static int nextEventID = 1;

        //create builder
        EventBuilder builder;

        // populate builder from dialog
        dialog.getEventData(builder, nextEventID++, currentUser);

        // build event
        Event* newEvent = builder.build();

        if (newEvent) {
            createStrategy->execute(userCalendar, newEvent);

            QDate selectedDate = calendarWidget->selectedDate();
            if (newEvent->getDate().date() == selectedDate){
                onDateSelected(selectedDate);
            }

            QTextCharFormat format;
            format.setBackground(Qt::lightGray); // set background of calendar for dates with events
            calendarWidget->setDateTextFormat(newEvent->getDate().date(), format);
        }
    }
}

/**
 * @brief Shows event dialog when an event is clicked.
 */
void MainWindow::onEventItemClicked(QListWidgetItem* item) {
    Event* event = item->data(Qt::UserRole).value<Event*>();
    if (event) {
        bool isCreatedEvent = (item->listWidget() == createdEventList);
        showEventDetailsDialog(event, isCreatedEvent);
    }
}

/**
 * @brief Shows the event details dialog.
 * @param event The event to display.
 * @param isCreatedEvent Indicates if the event was created by the user.
 * 
 * Displays a dialog with the details of the event.
 */
void MainWindow:: showEventDetailsDialog(Event* event, bool isCreatedEvent) {
    QDialog dialog(this);
    dialog.setWindowTitle("Event Details");
    dialog.setModal(true);

    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    QLabel* titleLabel = new QLabel(QString("Title: %1").arg(event->getTitle()));
    QLabel* dateLabel = new QLabel(QString("Date: %1").arg(event->getDate().toString("MMM d, yyyy h:mm AP")));
    QLabel* descLabel = new QLabel(QString("Description: %1").arg(event->getDescription()));
    QLabel* locationLabel = new QLabel(QString("Location: %1").arg(event->getLocation()));

    layout->addWidget(titleLabel);
    layout->addWidget(dateLabel);
    layout->addWidget(descLabel);
    layout->addWidget(locationLabel);

    if (isCreatedEvent) {
        // Users that are available for event
        QLabel* availableUsersLabel = new QLabel("Available Users:");
        QListWidget* availableUsersList = new QListWidget();

        // find available users
        QList<Calendar*> allCalendars = CalendarManager::getInstance()->getAllCalendars();
        for (Calendar* calendar : allCalendars) {
            User* user = calendar->getOwner();
            bool isAvailable = true;

            // Check if user has any conflicting events
            for (Event* existingEvent : calendar->getEvents()) {
                if (existingEvent->getDate().toString("yyyy-MM-dd hh:mm") == event->getDate().toString("yyyy-MM-dd hh:mm")) {
                    isAvailable = false;
                    break;
                }
            }

            // If user is available, add to list
            if (isAvailable) {
                QString displayName = QString("%1 %2").arg(user->getFirstName(), user->getLastName());
                QListWidgetItem* userItem = new QListWidgetItem(displayName, availableUsersList);

                // Set background color to user's color
                QColor userColor = UserManager::getInstance()->getUserColor(user->getPersonID());
                userItem->setBackground(userColor);

                // Adjust text color for readability
                if (userColor.lightness() < 128) {
                    userItem->setForeground(Qt::white);
                }
            }
        }

        layout->addWidget(availableUsersLabel);
        layout->addWidget(availableUsersList);
    }

    if (isCreatedEvent) {
        QHBoxLayout* buttonLayout = new QHBoxLayout();

        QPushButton* editButton = new QPushButton("Edit");
        QPushButton* deleteButton = new QPushButton("Delete");
        QPushButton* closeButton = new QPushButton("Close");

        buttonLayout->addWidget(editButton);
        buttonLayout->addWidget(deleteButton);
        buttonLayout->addWidget(closeButton);

        layout->addLayout(buttonLayout);

        // connect edit and delete buttons
        connect(editButton, &QPushButton::clicked, [&]() {
            dialog.accept();
            editEvent(event);
        });

        connect(deleteButton, &QPushButton::clicked, [&]() {
            dialog.accept();
            deleteEvent(event);
        });

        connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    } else {
        // close button
        QPushButton* closeButton = new QPushButton("Close");
        layout->addWidget(closeButton);
        connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    }

    dialog.exec();

}



/**
 * @brief Updates User Events List
 * 
 * Updates the list of events for the selected user.
 */
void MainWindow::updateUserEventsList() {
    if (calendarWidget->selectedDate().isValid()) {
        onDateSelected(calendarWidget->selectedDate());
    }
}


/** 
 * @brief Shows user details dialog when a user is clicked.
 * @param item The list item representing the user.
 * 
 * Displays a dialog with the details of the selected user.
 */
void MainWindow::onUserItemClicked(QListWidgetItem* item) {
    int userID = item->data(Qt::UserRole).toInt();
    User* user = users[userID];
    Calendar* calendar = userCalendars[userID];

    if (user && calendar) {
        showUserDetailsDialog(user, calendar);
    }
}

/**
 * @brief Shows the user details dialog.
 * @param user The user to display.
 * @param calendar The user's calendar.
 * 
 * Displays a dialog with the details of the user and their calendar.
 */
void MainWindow::showUserDetailsDialog(User* user, Calendar* calendar) {
    QDialog dialog(this);
    dialog.setWindowTitle("User Details");
    dialog.setModal(true);

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    // on click, user details
    QString info = QString("User: %1 %2\nTotal Events: %3")
                       .arg(user->getFirstName())
                       .arg(user->getLastName())
                       .arg(calendar->getEvents().size());

    QLabel* infoLabel = new QLabel(info);
    layout->addWidget(infoLabel);

    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QPushButton* deleteButton = new QPushButton("Delete User");
    QPushButton* closeButton = new QPushButton("Close");

    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(closeButton);

    layout->addLayout(buttonLayout);

    // Connect buttons
    connect(deleteButton, &QPushButton::clicked, [&]() {
        dialog.accept();
        deleteUser(user);
    });

    connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.exec();
}

/**
 * @brief Displays a confirmation dialog to delete an event.
 * @param event The event to delete.
 * 
 * Displays a confirmation dialog to delete the selected event.
 */
void MainWindow::deleteEvent(Event* event) {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Deletion",
                                                              "Are you sure you want to delete this event?\nThis action cannot be undone.",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        deleteStrategy->execute(userCalendar, event);
        updateCalendarDisplay();
    }
}

/**
 * @brief Updates the calendar display.
 * 
 * Updates the calendar display to reflect changes in the user's calendar.
 */
void MainWindow::updateDateFormat(const QDate& date) {
    // clear the format
    QTextCharFormat defaultFormat;
    calendarWidget->setDateTextFormat(date, defaultFormat);

    // check all calendars for events on this date
    bool hasEvents = false;

    // check user calendar
    for (const Event* event : userCalendar->getEvents()) {
        if (event->getDate().date() == date) {
            QTextCharFormat format;
            // set background to user for event that belongs to user
            format.setBackground(Qt::lightGray);
            calendarWidget->setDateTextFormat(date, format);
            hasEvents = true;
            break;
        }
    }

    // no events found in user calendar, check other calendars
    if (!hasEvents) {
        QList<Calendar*> calendars = CalendarManager::getInstance()->getAllCalendars();
        for (Calendar* calendar : calendars) {
            for (const Event* event : calendar->getEvents()) {
                if (event->getDate().date() == date) {
                    QTextCharFormat format;
                    format.setBackground(QColor(200, 230, 255));
                    calendarWidget->setDateTextFormat(date, format);
                    hasEvents = true;
                    break;
                }
            }
            if (hasEvents) break;
        }
    }
}


/**
 * @brief Edits an event.
 * @param event The event to edit.
 * 
 * Displays a dialog to edit the selected event.
 */
void MainWindow::editEvent(Event* event) {
    EventDialog dialog(this);
    dialog.setEventData(event);

    if (dialog.exec() == QDialog::Accepted) {
        // update event with new data

        //create event builder
        EventBuilder builder;

        //populate builder from dialog
        dialog.getEventData(builder, event->getEventID(), event->getOrganizer());

        //build updated event
        Event* updatedEvent = builder.build();

        if (updatedEvent) {
            // update the event in the calendar
            editStrategy->execute(userCalendar, updatedEvent);
            // update interface
            updateCalendarDisplay();
        }
    }
}

/**
 * @brief Deletes a user and their calendar.
 * @param user The user to delete.
 * 
 * Displays a confirmation dialog to delete the selected user and their calendar.
 */
void MainWindow::deleteUser(User* user) {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Deletion",
                                                              "Are you sure you want to delete this user and their calendar?\nThis action cannot be undone.",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        int userID = user->getPersonID();

        // store user info
        QString firstName = user->getFirstName();
        QString lastName = user->getLastName();


        // clear events from the calendar first
        Calendar* calendar = userCalendars.value(userID);

        if (calendar) {
            for (const Event* event : calendar->getEvents()) {
                // reset format if NO OTHER calendars have events on this date
                QDate eventDate = event->getDate().date();

                //check for any created events on date
                bool hasCreatedEvent = false;
                for (const Event* createdEvent : userCalendar->getEvents()) {
                    if (createdEvent->getDate().date() == eventDate) {
                        hasCreatedEvent = true;
                        break;
                    }
                }

                // check if other calendars have events on this date
                bool hasOtherUserEvents = false;
                QList<Calendar*> allCalendars = CalendarManager::getInstance()->getAllCalendars();
                for (Calendar* otherCalendar : allCalendars) {
                    if (otherCalendar->getOwner()->getPersonID() != userID) {
                        for (const Event* otherEvent : otherCalendar->getEvents()) {
                            if (otherEvent->getDate().date() == eventDate) {
                                hasOtherUserEvents = true;
                                break;
                            }
                        }
                    }
                    if (hasOtherUserEvents) break;
                }

                // reset format if no created events or user events
                if (!hasCreatedEvent && !hasOtherUserEvents) {
                    QTextCharFormat defaultFormat;
                    calendarWidget->setDateTextFormat(eventDate, defaultFormat);
                }
                // if there are created events on the date, keep the gray color
                else if (hasCreatedEvent) {
                    QTextCharFormat createdEventFormat;
                    createdEventFormat.setBackground(Qt::lightGray);
                    calendarWidget->setDateTextFormat(eventDate, createdEventFormat);
                }
                // if other user events exist, mark with light blue
                else if (hasOtherUserEvents) {
                    QTextCharFormat userEventFormat;
                    userEventFormat.setBackground(QColor(200, 230, 255));
                    calendarWidget->setDateTextFormat(eventDate, userEventFormat);
                }
            }
        }

        // remove user from UI
        QList<QListWidgetItem*> items = userList->findItems(
            QString("%1 %2").arg(firstName, lastName),
            Qt::MatchExactly
            );
        for (QListWidgetItem* item : items) {
            delete item;
        }

        // remove user events that belong to user
        for (int i = eventList->count() - 1; i >= 0; --i) {
            QListWidgetItem* item = eventList->item(i);
            Event* event = item->data(Qt::UserRole).value<Event*>();
            if (event && event->getOrganizer()->getPersonID() == userID) {
                delete eventList->takeItem(i);
            }
        }
        // remove events created BY the user
        for (int i = createdEventList->count() - 1; i >= 0; --i) {
            QListWidgetItem* item = createdEventList->item(i);
            Event* event = item->data(Qt::UserRole).value<Event*>();
            if (event && event->getOrganizer()->getPersonID() == userID) {
                delete createdEventList->takeItem(i);
            }
        }


        // removing mapping of userID from Calendar and User
        userCalendars.remove(userID);
        users.remove(userID);

        // handle memory cleanup
        CalendarManager::getInstance()->deleteCalendar(userID);
        UserManager::getInstance()->deleteUser(userID);

        QMessageBox::information(this, "Success", "User and calendar deleted successfully.");
    }
}

/**
 * @brief Updates the calendar display.
 * 
 * Updates the calendar display to reflect changes in the user's calendar.
 */
void MainWindow::updateCalendarDisplay() {
    // clear all date formats
    QTextCharFormat defaultFormat;

    // get the current month's first and last dates
    QDate currentDate = calendarWidget->selectedDate();
    QDate firstDate(currentDate.year(), currentDate.month(), 1);
    QDate lastDate(currentDate.year(), currentDate.month(), currentDate.daysInMonth());

    // clear formats for all dates in the current month
    for (QDate date = firstDate; date <= lastDate; date = date.addDays(1)) {
        calendarWidget->setDateTextFormat(date, defaultFormat);
    }

    //create colours for user event
    QTextCharFormat userEventBackground;
    userEventBackground.setBackground(QColor(200,230,255));
    //create colours for created events
    QTextCharFormat createdEventBackground;
    createdEventBackground.setBackground(QColor(Qt::lightGray));

    // mark dates with created events first, so gray will always be on top even if a new user is added
    for (const Event* event : userCalendar->getEvents()) {
        calendarWidget->setDateTextFormat(event->getDate().date(), createdEventBackground);
    }

    // mark all user events with blue to keep it consistent
    QList<Calendar*> calendars = CalendarManager::getInstance()->getAllCalendars();
    for (const Calendar* calendar : calendars) {
        if (calendar) {
            for (const Event* event : calendar->getEvents()) {
                QDate eventDate = event->getDate().date();
                // set to light blue if not already marked by a created event
                if (calendarWidget->dateTextFormat(eventDate) == defaultFormat) {
                    calendarWidget->setDateTextFormat(eventDate, userEventBackground);
                }
            }
        }
    }

    // update event lists for date selected
    if (calendarWidget->selectedDate().isValid()) {
        onDateSelected(calendarWidget->selectedDate());
    }
}

/**
 * @brief Destroys the main window.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

