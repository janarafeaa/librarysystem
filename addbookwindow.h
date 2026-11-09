#ifndef ADDBOOKWINDOW_H
#define ADDBOOKWINDOW_H

#include <QDialog>

namespace Ui {
class AddBookWindow;
}

class AddBookWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookWindow(QWidget *parent = nullptr);
    ~AddBookWindow();

private:
    Ui::AddBookWindow *ui;
};

#endif // ADDBOOKWINDOW_H
