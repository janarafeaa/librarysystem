#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "librarydata.h"
#include <QMessageBox>

Loginwindow::Loginwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Loginwindow)
{
    ui->setupUi(this);
    ui->labelError->hide();
}
void Loginwindow::on_pushButtonLogin_clicked()
{
    ui->labelError->hide();
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();
    bool isLibrarian = ui->radioButtonLibrarian->isChecked();
    bool isMember = ui->radioButtonMember->isChecked();

    if (username.isEmpty() || password.isEmpty() || (!isLibrarian && !isMember))
    {
        QMessageBox::critical(this, "Login Error", "Please enter username, password and select a role.");
        return;
    }

    for (const User &user : users)
    {
        if (user.username == username &&
            user.password == password &&
            user.isLibrarian == isLibrarian)
        {
            ui->labelError->hide();
            ui->lineEditUsername->clear();
            ui->lineEditPassword->clear();
            return;
        }
    }

    ui->labelError->setText("Invalid username, password or role");
    ui->labelError->show();
}


void Loginwindow::on_checkBoxShowPassword_toggled(bool checked)
{
    if (checked)
        ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
    else
        ui->lineEditPassword->setEchoMode(QLineEdit::Password);
}

Loginwindow::~Loginwindow()
{
    delete ui;
}
