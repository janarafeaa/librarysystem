#include "librarianhome.h"
#include "ui_LibrarianHome.h"
#include "librarydata.h"
#include "loginwindow.h"
#include <QMessageBox>

LibrarianHome::LibrarianHome(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
        if (parentWidget())
        {
            parentWidget()->show();
        }

        this->close();
    }
}