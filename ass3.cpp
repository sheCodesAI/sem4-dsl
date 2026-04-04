#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    string name;
    string role;
    Employee* child[5];
    int childcount;

public:
    Employee(string n, string r) {
        name = n;
        role = r;
        childcount = 0;
        for (int i = 0; i < 5; i++)
            child[i] = NULL;
    }

    string getName() {
        return name;
    }

    string getRole() {
        return role;
    }

    void addChild(Employee* e) {
        if (childcount < 5)
            child[childcount++] = e;
        else
            cout << "Cannot add more subordinates\n";
    }

    Employee* search(string key) {
        if (name == key)
            return this;
        for (int i = 0; i < childcount; i++) {
            Employee* found = child[i]->search(key);
            if (found != NULL)
                return found;
        }
        return NULL;
    }

    int height() {
        int maxH = 0;
        for (int i = 0; i < childcount; i++) {
            int h = child[i]->height();
            if (h > maxH)
                maxH = h;
        }
        return maxH + 1;
    }

    void findLeastSenior(int level, int &maxLevel, string &emp) {
        if (level > maxLevel) {
            maxLevel = level;
            emp = name;
        }
        for (int i = 0; i < childcount; i++)
            child[i]->findLeastSenior(level + 1, maxLevel, emp);
    }

    void display(int space = 0) {
        for (int i = 0; i < space; i++)
            cout << " ";
        cout << name << " (" << role << ")" << endl;
        for (int i = 0; i < childcount; i++)
            child[i]->display(space + 1);
    }
};

int main() {
    Employee* CEO = NULL;
    int choice;
    string name, manager;

    do {
        cout << "\n---- MENU ----\n";
        cout << "1. Create CEO\n";
        cout << "2. Add Manager\n";
        cout << "3. Add Employee\n";
        cout << "4. Display Organization\n";
        cout << "5. Longest Reporting Chain\n";
        cout << "6. Least Senior Employee\n";
        cout << "7. Search Employee\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (CEO == NULL) {
                cout << "Enter CEO name: ";
                cin >> name;
                CEO = new Employee(name, "CEO");
                cout << "CEO created\n";
            } else {
                cout << "CEO already exists\n";
            }
            break;

        case 2:
            if (CEO == NULL) {
                cout << "Create CEO first\n";
                break;
            }
            cout << "Enter Manager name: ";
            cin >> name;
            CEO->addChild(new Employee(name, "Manager"));
            cout << "Manager added under CEO\n";
            break;

        case 3:
            if (CEO == NULL) {
                cout << "Create CEO first\n";
                break;
            }
            cout << "Enter Manager name: ";
            cin >> manager;
            cout << "Enter Employee name: ";
            cin >> name;
            {
                Employee* mgr = CEO->search(manager);
                if (mgr && mgr->getRole() == "Manager") {
                    mgr->addChild(new Employee(name, "Employee"));
                    cout << "Employee added\n";
                } else {
                    cout << "Manager not found or invalid role\n";
                }
            }
            break;

        case 4:
            if (CEO)
                CEO->display();
            else
                cout << "Organization empty\n";
            break;

        case 5:
            if (CEO)
                cout << "Longest reporting chain: " << CEO->height() << endl;
            break;

        case 6:
            if (CEO) {
                int maxLevel = 0;
                string leastEmp;
                CEO->findLeastSenior(1, maxLevel, leastEmp);
                cout << "Least senior employee: " << leastEmp << endl;
            }
            break;

        case 7:
            if (CEO) {
                cout << "Enter name to search: ";
                cin >> name;
                if (CEO->search(name))
                    cout << "Found in organization\n";
                else
                    cout << "Not found\n";
            }
            break;

        case 0:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 0);

    return 0;
}
