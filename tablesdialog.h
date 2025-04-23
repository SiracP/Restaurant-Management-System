#ifndef TABLESDIALOG_H
#define TABLESDIALOG_H

#include "table.h"
#include "restaurant.h"
#include <QDialog>
#include <QPushButton>
#include <QMap>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TablesDialog; }
QT_END_NAMESPACE

class TablesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TablesDialog(QWidget *parent = nullptr);
    ~TablesDialog();

private slots:
    void handleTableClicked(int);
    void on_buttonAddOrder_clicked();
    void on_buttonCheckout_clicked();
    void on_buttonCloseRightPanel_clicked();

private:
    Ui::TablesDialog *ui;
    QMap<int, QPushButton*> tableButtons;
    Table* currentTable = nullptr;

    void createTableButtons(int count, int columns = 4);
    void updateButtonStyle(int);
    void showTableInfo(int);
    void populateOrderList();
    void setRightPanelVisible(bool);
};

#endif // TABLESDIALOG_H
