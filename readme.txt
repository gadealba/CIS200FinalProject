#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <ctime>

using namespace std;

// ===== Helper: get current date as YYYY-MM-DD =====
string getCurrentDate() {
    time_t now = time(nullptr);
    tm* lt = localtime(&now);
    char buffer[11]; // "YYYY-MM-DD" + null
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", lt);
    return string(buffer);
}

// ===== Helper: get date after N days as YYYY-MM-DD =====
string getDateAfterDays(int days) {
    time_t now = time(nullptr);
    now += static_cast<time_t>(days) * 24 * 60 * 60;
    tm* lt = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", lt);
    return string(buffer);
}

// ===== Book =====
class Book {
private:
    int id;
    string title;
    string author;
    int totalCopies;
    int availableCopies;

public:
    Book() : id(0), totalCopies(0), availableCopies(0) {}

    Book(int id, const string& title, const string& author, int totalCopies)
        : id(id), title(title), author(author),
          totalCopies(totalCopies), availableCopies(totalCopies) {}

    int getId() const { return id; }
    const string& getTitle() const { return title; }
    const string& getAuthor() const { return author; }
    int getTotalCopies() const { return totalCopies; }
    int getAvailableCopies() const { return availableCopies; }

    bool isAvailable() const {
        return availableCopies > 0;
    }

    bool borrowCopy() {
        if (availableCopies > 0) {
            availableCopies--;
            return true;
        }
        return false;
    }

    void returnCopy() {
        if (availableCopies < totalCopies) {
            availableCopies++;
        }
    }

    void print() const {
        cout << "[" << id << "] " << title
             << " by " << author
             << " (available: " << availableCopies
             << "/" << totalCopies << ")\n";
    }
};

// Forward declaration
class Loan;

// ===== Member =====
class Member {
private:
    int id;
    string name;
    vector<Loan> loans;

public:
    Member() : id(0) {}
    Member(int id, const string& name) : id(id), name(name) {}

    int getId() const { return id; }
    const string& getName() const { return name; }

    vector<Loan>& getLoans() { return loans; }
    const vector<Loan>& getLoans() const { return loans; }

    void addLoan(const Loan& loan);
};

// ===== Loan =====
class Loan {
private:
    Book* book;           // pointer to a Book stored in Library
    string loanDate;
    string dueDate;
    bool returned;

public:
    Loan(Book* b, const string& loanDate, const string& dueDate)
        : book(b), loanDate(loanDate), dueDate(dueDate), returned(false) {}

    Book* getBook() const { return book; }
    const string& getLoanDate() const { return loanDate; }
    const string& getDueDate() const { return dueDate; }
    bool isReturned() const { return returned; }

    void markReturned() { returned = true; }

    void print() const {
        cout << "Book: " << (book ? book->getTitle() : "UNKNOWN")
             << " | Loan date: " << loanDate
             << " | Due date: " << dueDate
             << " | Returned: " << (returned ? "yes" : "no") << "\n";
    }
};

void Member::addLoan(const Loan& loan) {
    loans.push_back(loan);
}

// ===== Library =====
class Library {
private:
    map<int, Book> booksById;
    map<int, Member> membersById;

public:
    void addBook(const Book& book) {
        booksById[book.getId()] = book;
    }

    void addMember(const Member& member) {
        membersById[member.getId()] = member;
    }

    Book* findBookById(int id) {
        auto it = booksById.find(id);
        if (it != booksById.end()) {
            return &it->second;
        }
        return nullptr;
    }

    Member* findMemberById(int id) {
        auto it = membersById.find(id);
        if (it != membersById.end()) {
            return &it->second;
        }
        return nullptr;
    }

    void listAllBooks() const {
        if (booksById.empty()) {
            cout << "No books in the library yet.\n";
            return;
        }
        for (const auto& pair : booksById) {
            pair.second.print();
        }
    }

    vector<Book*> searchBooksByTitle(const string& keyword) {
        vector<Book*> results;
        string lower = keyword;
        // convert keyword to lowercase
        for (char& c : lower) c = static_cast<char>(tolower(c));

        for (auto& pair : booksById) {
            string titleLower = pair.second.getTitle();
            for (char& c : titleLower) c = static_cast<char>(tolower(c));

            if (titleLower.find(lower) != string::npos) {
                results.push_back(&pair.second);
            }
        }
        return results;
    }

    bool borrowBook(int memberId, int bookId) {
        Member* m = findMemberById(memberId);
        if (!m) {
            cout << "Member not found.\n";
            return false;
        }

        Book* b = findBookById(bookId);
        if (!b) {
            cout << "Book not found.\n";
            return false;
        }

        if (!b->isAvailable()) {
            cout << "No available copies.\n";
            return false;
        }

        if (!b->borrowCopy()) {
            cout << "Could not borrow book.\n";
            return false;
        }

        string today = getCurrentDate();
        string due = getDateAfterDays(14); // 2 weeks

        Loan loan(b, today, due);
        m->addLoan(loan);

        cout << "Book borrowed successfully. Due date: " << due << "\n";
        return true;
    }

    bool returnBook(int memberId, int bookId) {
        Member* m = findMemberById(memberId);
        if (!m) {
            cout << "Member not found.\n";
            return false;
        }

        Book* b = findBookById(bookId);
        if (!b) {
            cout << "Book not found.\n";
            return false;
        }

        for (Loan& loan : m->getLoans()) {
            if (loan.getBook() && loan.getBook()->getId() == bookId && !loan.isReturned()) {
                loan.markReturned();
                b->returnCopy();
                cout << "Book returned successfully.\n";
                return true;
            }
        }
        cout << "This member does not have an active loan for that book.\n";
        return false;
    }

    void showMemberLoans(int memberId) const {
        auto it = membersById.find(memberId);
        if (it == membersById.end()) {
            cout << "Member not found.\n";
            return;
        }
        const Member& m = it->second;

        cout << "Loans for member: " << m.getName() << "\n";
        const vector<Loan>& loans = m.getLoans();
        if (loans.empty()) {
            cout << "No loans.\n";
            return;
        }
        for (const Loan& loan : loans) {
            loan.print();
        }
    }
};

// ===== Input helpers =====
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Invalid number. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string readLine(const string& prompt) {
    cout << prompt;
    string line;
    getline(cin, line);
    return line;
}

// ===== Menu actions =====
void seedData(Library& library) {
    library.addBook(Book(1, "The Hobbit", "J.R.R. Tolkien", 3));
    library.addBook(Book(2, "1984", "George Orwell", 2));
    library.addBook(Book(3, "Clean Code", "Robert C. Martin", 1));

    library.addMember(Member(1, "Alice"));
    library.addMember(Member(2, "Bob"));
}

void addNewBook(Library& library) {
    int id = readInt("Enter book id (integer): ");
    string title = readLine("Enter title: ");
    string author = readLine("Enter author: ");
    int copies = readInt("Enter number of copies: ");

    Book book(id, title, author, copies);
    library.addBook(book);
    cout << "Book added.\n";
}

void searchBooks(Library& library) {
    string keyword = readLine("Enter keyword in title: ");
    vector<Book*> results = library.searchBooksByTitle(keyword);
    if (results.empty()) {
        cout << "No books found.\n";
    } else {
        cout << "Found books:\n";
        for (Book* b : results) {
            b->print();
        }
    }
}

void addNewMember(Library& library) {
    int id = readInt("Enter member id (integer): ");
    string name = readLine("Enter member name: ");

    Member member(id, name);
    library.addMember(member);
    cout << "Member added.\n";
}

void borrowBookMenu(Library& library) {
    int memberId = readInt("Enter member id: ");
    int bookId = readInt("Enter book id: ");
    library.borrowBook(memberId, bookId);
}

void returnBookMenu(Library& library) {
    int memberId = readInt("Enter member id: ");
    int bookId = readInt("Enter book id: ");
    library.returnBook(memberId, bookId);
}

void showMemberLoansMenu(const Library& library) {
    int memberId = readInt("Enter member id: ");
    library.showMemberLoans(memberId);
}

// ===== Main menu loop =====
void runMenu(Library& library) {
    while (true) {
        cout << "\n===== Library Management System =====\n";
        cout << "1. List all books\n";
        cout << "2. Add a new book\n";
        cout << "3. Search books by title\n";
        cout << "4. Add a new member\n";
        cout << "5. Borrow a book\n";
        cout << "6. Return a book\n";
        cout << "7. Show member loans\n";
        cout << "0. Exit\n";

        int choice = readInt("Choose an option: ");

        switch (choice) {
            case 1:
                library.listAllBooks();
                break;
            case 2:
                addNewBook(library);
                break;
            case 3:
                searchBooks(library);
                break;
            case 4:
                addNewMember(library);
                break;
            case 5:
                borrowBookMenu(library);
                break;
            case 6:
                returnBookMenu(library);
                break;
            case 7:
                showMemberLoansMenu(library);
                break;
            case 0:
                cout << "Goodbye!\n";
                return;
            default:
                cout << "Unknown option.\n";
        }
    }
}

int main() {
    Library library;
    seedData(library);
    runMenu(library);
    return 0;
}
