#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "librarydata.h"

#include <QMessageBox>
#include <QPushButton>

SearchWindow::SearchWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SearchWindow)
{
    ui->setupUi(this);

    ui->radioButtonTitle->setChecked(true);

    ui->pushButtonBorrow->setEnabled(false);
    ui->pushButtonReturn->setEnabled(false);
    ui->pushButtonDelete->setEnabled(false);

    connect(ui->pushButtonSearch, &QPushButton::clicked, this, [this]()
            {
                foundBookIndex = -1;

                QString searchText = ui->lineEditSearch->text().trimmed();

                if (searchText.isEmpty())
                {
                    QMessageBox::warning(this, "Search",
                                         "Please enter something to search for.");
                    clearBookDetails();
                    return;
                }

                for (int i = 0; i < static_cast<int>(books.size()); i++)
                {
                    bool match = false;

                    if (ui->radioButtonTitle->isChecked())
                        match = books[i].title.contains(searchText, Qt::CaseInsensitive);

                    else if (ui->radioButtonISBN->isChecked())
                        match = books[i].isbn.contains(searchText, Qt::CaseInsensitive);

                    else if (ui->radioButtonAuthor->isChecked())
                        match = books[i].author.contains(searchText, Qt::CaseInsensitive);

                    if (match)
                    {
                        foundBookIndex = i;
                        break;
                    }
                }

                if (foundBookIndex == -1)
                {
                    clearBookDetails();

                    QMessageBox::information(this, "Search",
                                             "No book found.");
                    return;
                }

                updateBookDetails();
            });

    connect(ui->pushButtonBorrow, &QPushButton::clicked, this, [this]()
            {
                if (foundBookIndex == -1)
                    return;

                Book &book = books[foundBookIndex];

                if (book.isBorrowed || book.isReferenceOnly)
                    return;

                book.isBorrowed = true;
                book.borrowedBy = currentUsername;

                QMessageBox::information(this, "Borrow",
                                         "Book borrowed successfully.");

                updateBookDetails();
            });

    connect(ui->pushButtonReturn, &QPushButton::clicked, this, [this]()
            {
                if (foundBookIndex == -1)
                    return;

                Book &book = books[foundBookIndex];

                if (!book.isBorrowed)
                    return;

                if (!librarian && book.borrowedBy != currentUsername)
                {
                    QMessageBox::warning(this, "Return",
                                         "You can only return books borrowed by you.");
                    return;
                }

                book.isBorrowed = false;
                book.borrowedBy = "";

                QMessageBox::information(this, "Return",
                                         "Book returned successfully.");

                updateBookDetails();
            });

    connect(ui->pushButtonDelete, &QPushButton::clicked, this, [this]()
            {
                if (!librarian || foundBookIndex == -1)
                    return;

                Book &book = books[foundBookIndex];

                if (book.isBorrowed)
                {
                    QMessageBox::warning(this, "Delete",
                                         "A borrowed book cannot be deleted.");
                    return;
                }

                QMessageBox::StandardButton reply =
                    QMessageBox::question(this, "Delete Book",
                                          "Are you sure you want to delete this book?",
                                          QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes)
                {
                    books.erase(books.begin() + foundBookIndex);
                    foundBookIndex = -1;

                    clearBookDetails();

                    QMessageBox::information(this, "Delete",
                                             "Book deleted successfully.");
                }
            });

    connect(ui->pushButton, &QPushButton::clicked, this, [this]()
            {
                if (!librarian)
                {
                    QMessageBox::StandardButton reply =
                        QMessageBox::question(this, "Logout",
                                              "Are you sure you want to logout?",
                                              QMessageBox::Yes | QMessageBox::No);

                    if (reply != QMessageBox::Yes)
                        return;
                }

                if (parentWidget())
                    parentWidget()->show();

                this->accept();
            });
}

void SearchWindow::setValues(const QString &username, bool isLibrarian)
{
    currentUsername = username;
    librarian = isLibrarian;

    if (librarian)
    {
        ui->pushButtonDelete->show();
        setWindowTitle("Search - Librarian: " + username);
    }
    else
    {
        ui->pushButtonDelete->hide();
        setWindowTitle("Search - Member: " + username);
    }

    clearBookDetails();
}

void SearchWindow::updateBookDetails()
{
    if (foundBookIndex == -1)
        return;

    const Book &book = books[foundBookIndex];

    ui->labelTitleValue->setText("Title: " + book.title);
    ui->labelAuthorValue->setText("Author: " + book.author);
    ui->labelYearValue->setText("Year: " + QString::number(book.year));
    ui->labelCategoryValue->setText("Category: " + book.category);

    if (book.isReferenceOnly)
        ui->labelStatusValue->setText("Status: Reference only");
    else if (book.isBorrowed)
        ui->labelStatusValue->setText("Status: Borrowed by " + book.borrowedBy);
    else
        ui->labelStatusValue->setText("Status: Available");

    ui->pushButtonBorrow->setEnabled(
        !book.isBorrowed && !book.isReferenceOnly);

    ui->pushButtonReturn->setEnabled(
        book.isBorrowed &&
        (librarian || book.borrowedBy == currentUsername));

    ui->pushButtonDelete->setEnabled(
        librarian && !book.isBorrowed);
}

void SearchWindow::clearBookDetails()
{
    ui->labelTitleValue->setText("Title:");
    ui->labelAuthorValue->setText("Author:");
    ui->labelYearValue->setText("Year:");
    ui->labelCategoryValue->setText("Category:");
    ui->labelStatusValue->setText("Status:");

    ui->pushButtonBorrow->setEnabled(false);
    ui->pushButtonReturn->setEnabled(false);
    ui->pushButtonDelete->setEnabled(false);
}

SearchWindow::~SearchWindow()
{
    delete ui;
}
