#include "loginwindow.h"
#include "ui_loginwindow.h"

Loginwindow::Loginwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Loginwindow)
{
    ui->setupUi(this);
}

Loginwindow::~Loginwindow()
{
    delete ui;
}
