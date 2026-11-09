
#include "addbookwindow.h"
#include "ui_addbookwindow.h"
#include "librarydata.h"

#include <QMessageBox>

AddBookWindow::AddBookWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddBookWindow)
{
    ui->setupUi(this);

    // Populate category dropdown
    ui->comboBoxCategory->addItems({
        "Programming",
        "Science",
        "Fiction",
        "History",
        "Other"
    });

    // Add button
    connect(ui->pushButtonAdd, &QPushButton::clicked, this, [this]()
            {
                QString title = ui->lineEditTitle->text().trimmed();
                QString author = ui->lineEditAuthor->text().trimmed();
                QString isbn = ui->lineEditISBN->text().trimmed();
                QString yearText = ui->lineEditYear->text().trimmed();
                QString category = ui->comboBoxCategory->currentText();
                bool referenceOnly = ui->checkBoxReferenceOnly->isChecked();

                bool yearValid;
                int year = yearText.toInt(&yearValid);

                if (title.isEmpty() || author.isEmpty() ||
                    isbn.isEmpty() || yearText.isEmpty())
                {
                    QMessageBox::warning(this, "Missing Information",
                                         "Please fill in all book details.");
                    return;
                }

                if (!yearValid)
                {
                    QMessageBox::warning(this, "Invalid Year",
                                         "Please enter a valid year.");
                    return;
                }

                Book newBook = {
                    title,
                    author,
                    isbn,
                    category,
                    "",
                    year,
                    referenceOnly,
                    false
                };

                books.push_back(newBook);

                QMessageBox::information(this, "Book Added",
                                         "Book added successfully!\n\n"
                                         "Title: " + title + "\n"
                                                       "Author: " + author + "\n"
                                                        "ISBN: " + isbn + "\n"
                                                      "Year: " + yearText + "\n"
                                                          "Category: " + category);

                // Clear the form after adding
                ui->lineEditTitle->clear();
                ui->lineEditAuthor->clear();
                ui->lineEditISBN->clear();
                ui->lineEditYear->clear();
                ui->comboBoxCategory->setCurrentIndex(0);
                ui->checkBoxReferenceOnly->setChecked(false);
            });

    // Clear button
    connect(ui->pushButtonClear, &QPushButton::clicked, this, [this]()
            {
                ui->lineEditTitle->clear();
                ui->lineEditAuthor->clear();
                ui->lineEditISBN->clear();
                ui->lineEditYear->clear();
                ui->comboBoxCategory->setCurrentIndex(0);
                ui->checkBoxReferenceOnly->setChecked(false);
            });

    // Back button
    connect(ui->pushButtonBack, &QPushButton::clicked, this, [this]()
            {
                this->hide();

                if (parentWidget())
                {
                    parentWidget()->show();
                }
            });
}

AddBookWindow::~AddBookWindow()
{
    delete ui;
}
