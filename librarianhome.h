
#ifndef LIBRARIANHOME_H
#define LIBRARIANHOME_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class LibrarianHome : public QMainWindow
{
    Q_OBJECT

public:
    explicit LibrarianHome(QWidget *parent = nullptr);
    ~LibrarianHome();

    void setValues(const QString &username);

private slots:
    void on_pushButtonLogout_clicked();
    void on_actionLogout_triggered(bool checked);
    void on_actionAdd_New_Book_triggered(bool checked);
    void on_actionSearch_Books_triggered(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // LIBRARIANHOME_H
