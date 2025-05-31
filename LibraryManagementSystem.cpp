#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Global counter for generating book IDs
int globalBookIDCounter = 1;

// === Book class: Just the basic book info ===
class Book {
protected:
    int bookID;
    string bookTitle;
    string bookAuthor;
    string bookPublisher;
    string bookISBN;

public:
    Book() {
        bookID = globalBookIDCounter++; // Auto ID
    }

    // Input book details from user
    void inputBookDetails() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Book Title: ";
        getline(cin, bookTitle);
        cout << "Enter Author Name: ";
        getline(cin, bookAuthor);
        cout << "Enter Publisher Name: ";
        getline(cin, bookPublisher);
        cout << "Enter ISBN Number: ";
        getline(cin, bookISBN);
    }

    // Just show the book info
    void displayBasicBookInfo() {
        cout << "--- Book Information ---" << endl;
        cout << "Book ID: " << bookID << endl;
        cout << "Title: " << bookTitle << endl;
        cout << "Author: " << bookAuthor << endl;
        cout << "Publisher: " << bookPublisher << endl;
        cout << "ISBN: " << bookISBN << endl;
    }

    // Return the book's ID
    int getBookID() {
        return bookID;
    }
};

// === LibraryBook class: Extends Book with status stuff ===
class LibraryBook : public Book {
private:
    bool bookIsAvailable;
    int overdueDays;

public:
    LibraryBook() {
        bookIsAvailable = true;
        overdueDays = 0;
    }

    // Borrow or return the book
    void updateBookStatus() {
        displayBasicBookInfo();
        cout << "Status: " << (bookIsAvailable ? "Available" : "Borrowed") << endl;
        cout << "1. Borrow Book" << endl;
        cout << "2. Return Book" << endl;
        cout << "Choose option: ";
        int statusOption;
        cin >> statusOption;

        if (statusOption == 1 && bookIsAvailable) {
            bookIsAvailable = false;
            cout << "Book has been borrowed." << endl;
        } else if (statusOption == 2 && !bookIsAvailable) {
            bookIsAvailable = true;
            cout << "Enter days overdue (0 if on time): ";
            cin >> overdueDays;
            if (overdueDays < 0) overdueDays = 0;
            cout << "Book has been returned." << endl;
        } else {
            cout << "Invalid action." << endl;
        }
    }

    // Just get the fine amount
    double getOverdueFine() {
        return overdueDays * 5.0; // R5 per day
    }

    // Show all info including fine (if any)
    void displayCompleteBookInfo() {
        displayBasicBookInfo();
        cout << "Availability: " << (bookIsAvailable ? "Available" : "Borrowed") << endl;
        if (overdueDays > 0)
            cout << "Overdue by " << overdueDays << " days. Fine: R" << getOverdueFine() << endl;
    }
};

// === Main menu loop ===
int main() {
    LibraryBook libraryBooks[10]; // can store 10 books
    int totalBooksInLibrary = 0;
    int userChoice;

    do {
        // show main menu
        cout << "--- Library Menu ---" << endl;
        cout << "1. Add New Book" << endl;
        cout << "2. Borrow or Return Book" << endl;
        cout << "3. View All Books" << endl;
        cout << "4. Calculate Book Fine" << endl;
        cout << "5. Exit Program" << endl;
        cout << "Choose option: ";
        cin >> userChoice;

        // Add new book
        if (userChoice == 1) {
            if (totalBooksInLibrary < 10) {
                libraryBooks[totalBooksInLibrary].inputBookDetails();
                cout << "Book added. Book ID: " << libraryBooks[totalBooksInLibrary].getBookID() << endl;
                totalBooksInLibrary++;
            } else {
                cout << "Library is full. No more books." << endl;
            }
        }

        // Borrow or return
        else if (userChoice == 2) {
            if (totalBooksInLibrary == 0) {
                cout << "No books available yet." << endl;
                continue;
            }
            int searchBookID;
            cout << "Enter Book ID to update: ";
            cin >> searchBookID;
            bool bookFound = false;

            for (int i = 0; i < totalBooksInLibrary; i++) {
                if (libraryBooks[i].getBookID() == searchBookID) {
                    libraryBooks[i].updateBookStatus();
                    bookFound = true;
                    break;
                }
            }

            if (!bookFound) {
                cout << "Book with that ID not found." << endl;
            }
        }

        // View all books
        else if (userChoice == 3) {
            if (totalBooksInLibrary == 0) {
                cout << "No books to show." << endl;
            } else {
                for (int i = 0; i < totalBooksInLibrary; i++) {
                    libraryBooks[i].displayCompleteBookInfo();
                }
            }
        }

        // Calculate fine for a book
        else if (userChoice == 4) {
            int fineBookID;
            cout << "Enter Book ID to check fine: ";
            cin >> fineBookID;
            bool fineBookFound = false;

            for (int i = 0; i < totalBooksInLibrary; i++) {
                if (libraryBooks[i].getBookID() == fineBookID) {
                    double fineAmount = libraryBooks[i].getOverdueFine();
                    if (fineAmount > 0) {
                        cout << "Fine: R" << fineAmount << endl;
                    } else {
                        cout << "No fine due." << endl;
                    }
                    fineBookFound = true;
                    break;
                }
            }

            if (!fineBookFound) {
                cout << "Book ID not found." << endl;
            }
        }

        // Exit the program
        else if (userChoice == 5) {
            cout << "Exiting program. Take care!" << endl;
        }

        // wrong option
        else {
            cout << "Invalid option. Try again." << endl;
        }

    } while (userChoice != 5); // loop until user quits

    return 0;
}
