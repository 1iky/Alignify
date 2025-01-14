/**
 * @file mainwindow.h
 * @brief Defines the MainWindow class.
 * 
 * The MainWindow class is the main window of the application.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCalendarWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include "calendar.h"
#include "user.h"
#include "eventactions.h"
#include <QColor>
#include <QMap>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The main window of the application.
 * 
 * The MainWindow class is the main window of the application.
 * It displays a calendar widget, a list of events, and a list of users.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QCalendarWidget* calendarWidget;
    QListWidget* eventList;
    QListWidget* createdEventList;
    QListWidget* userList;
    QPushButton* createEventButton;
    QPushButton* createUserButton;
    Calendar* userCalendar;
    User * currentUser;
    QMap<int, User*> users;
    QMap<int, Calendar*> userCalendars;

    //create user colours
    QMap<int, QColor> userColors;

    // strategy objects
    std::unique_ptr<EventActions> createStrategy;
    std::unique_ptr<EventActions> deleteStrategy;
    std::unique_ptr<EventActions> editStrategy;


    Event* parseICSEvent(const QStringList& eventLines, User* user, int& nextEventID);
    QDateTime parseICSDateTime(const QString& dateTimeStr);

    void setupUI();
    void createConnections();

    void loadICSFile(const QString& filePath, User* user);
    void updateUserEventsList();

    void showEventDetailsDialog(Event* event, bool isCreatedEvent);
    void showUserDetailsDialog(User* user, Calendar* calendar);
    void deleteEvent(Event* event);
    void editEvent(Event* event);
    void deleteUser(User* user);
    void updateCalendarDisplay();
    void updateDateFormat(const QDate& date);



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDateSelected(const QDate& date);
    void onCreateEventClicked();
    void onCreateUserClicked();
    void onEventItemClicked(QListWidgetItem* item);
    void onUserItemClicked(QListWidgetItem* item);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
