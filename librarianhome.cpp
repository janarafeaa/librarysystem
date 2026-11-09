
#include "librarianhome.h"
#include "ui_LibrarianHome.h"
#include "librarydata.h"
#include "loginwindow.h"
#include "addbookwindow.h"

#include <QMessageBox>

LibrarianHome::LibrarianHome(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("Ready");
}

LibrarianHome::~LibrarianHome()
{
    delete ui;
}

void LibrarianHome::setValues(const QString &username)
{
    ui->labelWelcome->setText("Welcome, " + username + "!");
    ui->labelBookCount->setText("Books in Library: " + QString::number(books.size()));
}

void LibrarianHome::on_pushButtonLogout_clicked()
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Logout",
                                  "Are you sure you want to logout?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        ui->statusbar->clearMessage();

        if (parentWidget())
        {
            parentWidget()->show();
        }

        this->close();
    }
}

void LibrarianHome::on_actionLogout_triggered(bool checked)
{
    on_pushButtonLogout_clicked();
}

void LibrarianHome::on_actionAdd_New_Book_triggered(bool checked)
{
    ui->statusbar->showMessage("Opening Add Book...", 2000);

    int previousBookCount = books.size();

    AddBookWindow dialog(this);
    dialog.exec();

    if (books.size() > previousBookCount)
    {
        ui->labelBookCount->setText(
            "Books in Library: " + QString::number(books.size()));

        ui->statusbar->showMessage("Book added successfully", 3000);
    }
}
