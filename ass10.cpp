#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Book {
private:
    int id;
    string title, author, genre, availability;

public:

    void input() {
        cout << "Enter Book ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        cout << "Enter Genre: ";
        getline(cin, genre);

        cout << "Enter Availability (Available/Issued): ";
        getline(cin, availability);
    }

    void display() const {
        cout << "\nBook ID: " << id
             << "\nTitle: " << title
             << "\nAuthor: " << author
             << "\nGenre: " << genre
             << "\nAvailability: " << availability
             << endl;
    }

    int getId() const {
        return id;
    }

    string serialize() const {
        return to_string(id) + "|" + title + "|" + author + "|" + genre + "|" + availability;
    }

    void deserialize(string line) {

        int pos = 0;

        pos = line.find('|');
        id = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find('|');
        title = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        author = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        genre = line.substr(0, pos);
        line.erase(0, pos + 1);

        availability = line;
    }
};

class Library {

private:
    string filename = "library.txt";

public:

    void addBook() {

        Book b;

        b.input();

        ofstream file(filename, ios::app);

        file << b.serialize() << endl;

        file.close();

        cout << "Book added successfully.\n";
    }

    void displayAll() {

        ifstream file(filename);

        string line;

        Book b;

        while (getline(file, line)) {

            b.deserialize(line);

            b.display();
        }

        file.close();
    }

    void searchBook(int searchId) {

        ifstream file(filename);

        string line;

        Book b;

        bool found = false;

        while (getline(file, line)) {

            b.deserialize(line);

            if (b.getId() == searchId) {

                cout << "\nBook Found:\n";

                b.display();

                found = true;

                break;
            }
        }

        if (!found) {
            cout << "Book record not found.\n";
        }

        file.close();
    }

    void deleteBook(int deleteId) {

        ifstream file(filename);

        ofstream temp("temp.txt");

        string line;

        Book b;

        bool found = false;

        while (getline(file, line)) {

            b.deserialize(line);

            if (b.getId() != deleteId) {

                temp << line << endl;

            } else {

                found = true;
            }
        }

        file.close();

        temp.close();

        remove(filename.c_str());

        rename("temp.txt", filename.c_str());

        if (found)
            cout << "Book deleted successfully.\n";
        else
            cout << "Book not found.\n";
    }

    void updateBook(int updateId) {

        ifstream file(filename);

        ofstream temp("temp.txt");

        string line;

        Book b;

        bool found = false;

        while (getline(file, line)) {

            b.deserialize(line);

            if (b.getId() == updateId) {

                cout << "Enter new details:\n";

                b.input();

                temp << b.serialize() << endl;

                found = true;

            } else {

                temp << line << endl;
            }
        }

        file.close();

        temp.close();

        remove(filename.c_str());

        rename("temp.txt", filename.c_str());

        if (found)
            cout << "Book updated successfully.\n";
        else
            cout << "Book not found.\n";
    }
};

int main() {

    Library lib;

    int choice, id;

    do {

        cout << "\n===== Library Menu =====\n";

        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Update Book\n";
        cout << "5. Delete Book\n";
        cout << "6. Exit\n";

        cout << "Enter choice: ";

        cin >> choice;

        switch (choice) {

            case 1:
                lib.addBook();
                break;

            case 2:
                lib.displayAll();
                break;

            case 3:
                cout << "Enter Book ID to search: ";
                cin >> id;
                lib.searchBook(id);
                break;

            case 4:
                cout << "Enter Book ID to update: ";
                cin >> id;
                lib.updateBook(id);
                break;

            case 5:
                cout << "Enter Book ID to delete: ";
                cin >> id;
                lib.deleteBook(id);
                break;

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}
