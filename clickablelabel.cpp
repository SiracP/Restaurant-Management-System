#include "clickablelabel.h"


ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{
    // Change the mouse cursor to a pointing hand when hovering over this label,
    // giving a visual cue that the label is clickable.
    setCursor(Qt::PointingHandCursor);
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    // Emit the custom clicked() signal so that external code can react
    // when the user clicks on this label.
    emit clicked();

    // Call the base class implementation to ensure any default QLabel
    // behavior (e.g. focus handling) still occurs.
    QLabel::mousePressEvent(event);
}
