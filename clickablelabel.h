#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

/**
 * @brief A QLabel subclass that behaves like a clickable button.
 *
 * ClickableLabel emits a clicked() signal when the user presses
 * the label. It also changes the cursor to a pointing hand to
 * indicate interactivity.
 */
class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     */
    explicit ClickableLabel(QWidget* parent = nullptr);

signals:
    /**
     * @brief Emitted when the label is clicked.
     *
     * Clients can connect to this signal to perform an action when
     * the user clicks on the label.
     */
    void clicked();

protected:
    /**
     * @brief Handles mouse press events on the label.
     * @param event The mouse event information.
     *
     * Overrides QLabel::mousePressEvent to first emit the clicked()
     * signal, then invokes the base class implementation.
     */
    void mousePressEvent(QMouseEvent* event) override;
};

#endif
