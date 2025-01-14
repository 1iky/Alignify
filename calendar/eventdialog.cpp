/**
 * @file eventdialog.cpp
 * @brief Implements the EventDialog class.
 *        Dialog window for creating and editing events.
 *        The dialog allows users to input event details such as title, description, date/time, and location.
 */
#include "eventdialog.h"
#include "eventbuilder.h"
#include <QMessageBox>

/**
 * @brief Initializes dialog window, sets up the layout, and creates input fields for event details.
 *
 *
 * @param parent The parent widget of the dailog.
 */
EventDialog::EventDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Create New Event");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // title
    mainLayout->addWidget(new QLabel("Title *:"));
    titleEdit = new QLineEdit(this);
    mainLayout->addWidget(titleEdit);

    // description
    mainLayout->addWidget(new QLabel("Description:"));
    descriptionEdit = new QTextEdit(this);
    mainLayout->addWidget(descriptionEdit);

    // date and time
    mainLayout->addWidget(new QLabel("Date and Time:"));
    dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    dateTimeEdit->setCalendarPopup(true);
    mainLayout->addWidget(dateTimeEdit);

    // location
    mainLayout->addWidget(new QLabel("Location:"));
    locationEdit = new QLineEdit(this);
    mainLayout->addWidget(locationEdit);

    // buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    createButton = new QPushButton("Create", this);
    cancelButton = new QPushButton("Cancel", this);

    buttonLayout->addWidget(createButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(createButton, &QPushButton::clicked, this, &EventDialog::onCreateClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    setLayout(mainLayout); //set dialog layout
}

/**
 * @brief Handles when Create button is clicked
 */
void EventDialog::onCreateClicked() {
    if (titleEdit->text().isEmpty()) { //check if title is
        QMessageBox::warning(this, "Event title is required!", "Please enter an event title.");
        return;
    }
    accept();
}

/**
 * @brief Creates an Event object using the input fields in the dialog.
 * @param builder Reference to EventBuilder instance used to construct Event object.
 * @param eventId Unique ID for event.
 * @param organizer Event organizer
 * @return A pointer to new created Event object.
 */
Event* EventDialog::getEventData(EventBuilder& builder, int eventId, User* organizer) {

    Event* event = builder
                       .setEventID(eventId)
                       .setTitle(titleEdit->text())
                       .setDescription(descriptionEdit->toPlainText())
                       .setDateTime(dateTimeEdit->dateTime())
                       .setLocation(locationEdit->text())
                       .setOrganizer(organizer)
                       .build();

    return event;
}

/**
 * @brief Populates the dialog fields with data from existing Event object.
 * @param event Pointer to Event object contianing data to populate dialog fields.
 *              Does nothing if event is null.
 */
void EventDialog::setEventData(Event* event) {
    if (!event) return;

    titleEdit->setText(event->getTitle());
    descriptionEdit->setText(event->getDescription());
    locationEdit->setText(event->getLocation());
    dateTimeEdit->setDateTime(event->getDate());
}
