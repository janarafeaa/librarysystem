#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>
#include <QString>

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();

    void setValues(const QString &username, bool isLibrarian);

private:
    Ui::SearchWindow *ui;

    QString currentUsername;
    bool librarian = false;
    int foundBookIndex = -1;

    void updateBookDetails();
    void clearBookDetails();
};

#endif // SEARCHWINDOW_H
