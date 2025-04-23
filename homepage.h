#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QTimer>
#include "restaurant.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HomePage; }
QT_END_NAMESPACE

/**
 * @class HomePage
 * @brief Dashboard showing daily stats, active tables, top product,
 *    recent activities, and a decorative photo.
 **/
class HomePage : public QWidget {

    Q_OBJECT

public:
    /**
     * @brief Constructer.
     */
    explicit HomePage(QWidget *parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~HomePage() override;

    /**
     * @brief Refreshes all widgets from the Restaurant singleton.
     */
    void refreshHome();

private slots:
    /**
     * @brief Updates the clock display once per second.
     * Called by the internal QTimer timeout() to keep the header clock live.
     */
    void updateDateTime();

private:
    Ui::HomePage* ui;
    QTimer* clockTimer; /// @brief Timer triggering updateDateTime() every second.

    /**
     * @brief Fetches and displays the three summary cards.
     */
    void updateSummaries();

    /**
     * @brief Populates the “Recent Activities” list.
     */
    void updateRecentActivities();
};

#endif
