
#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include <cctype>

using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Linked list node for Users (used in linked list of users)
struct UserNode
{
    string username;
    string password;
    string role;
    UserNode *next;
};

// Linked list node for Emergencies (used in both queue and stack)
struct Emergency
{
    string id, name, type, level, location, description;
    int priority;
    time_t addedTime;
    Emergency *next;
};

// Helper functions to calculate priority for queue
int getTypeScore(string type)
{
    if (type == "Medical")
        return 1;
    if (type == "Accident")
        return 2;
    if (type == "Fire")
        return 3;
    if (type == "Crime")
        return 4;
    if (type == "Natural Disaster")
        return 5;
    return 0;
}

int getLevelScore(string level)
{
    if (level == "Very Low")
        return 1;
    if (level == "Low")
        return 2;
    if (level == "Mid")
        return 3;
    if (level == "High")
        return 4;
    if (level == "Critical")
        return 5;
    return 0;
}

int calculatePriority(string level, string type)
{
    return getLevelScore(level) + getTypeScore(type);
}

// This class uses a Priority Queue implemented using Linked List
class PendingEmergency
{
    Emergency *head; // Head of linked list
    int emergencyCounter;

public:
    PendingEmergency()
    {
        head = NULL;
        emergencyCounter = 1;
    }

    void push(string name, string type, string level, string location, string description, int priority)
    {
        // New emergency node (linked list node)
        Emergency *newEmergency = new Emergency;
        newEmergency->id = "E" + to_string(emergencyCounter++);
        newEmergency->name = name;
        newEmergency->type = type;
        newEmergency->level = level;
        newEmergency->location = location;
        newEmergency->description = description;
        newEmergency->priority = priority;
        newEmergency->addedTime = time(NULL);
        newEmergency->next = NULL;

        // Insert into queue (priority order, higher priority at top)
        if (head == NULL || newEmergency->priority > head->priority)
        {
            newEmergency->next = head;
            head = newEmergency;
        }
        else
        {
            Emergency *current = head;
            while (current->next != NULL && current->next->priority >= newEmergency->priority)
            {
                current = current->next;
            }
            newEmergency->next = current->next;
            current->next = newEmergency;
        }
    }

    Emergency *GetHead() const
    {
        if (head == NULL)
        {
            cout << "Queue is empty";
        }
        return head; // Return top of queue
    }

    void pop()
    {
        if (head == NULL)
        {
            throw runtime_error("Queue is empty");
        }
        // Remove from queue (FIFO logic with priority)
        Emergency *temp = head;
        head = head->next;
        delete temp;
    }

    bool empty() const
    {
        return head == NULL;
    }

    void display() const
    {
        Emergency *current = head;
        while (current != NULL)
        {
            cout << "Emergencies are: " << endl;
            cout << "ID: " << current->id << ", Name: " << current->name
                 << ", Type: " << current->type << ", Level: " << current->level
                 << ", Location: " << current->location << ", Desc: " << current->description
                 << ", Priority: " << current->priority << endl;
            current = current->next;
        }
    }

    void filterByType(string filterType) const
    {
        Emergency *current = head;
        bool found = false;

        while (current != NULL)
        {
            if (current->type == filterType)
            {
                cout << "ID: " << current->id << ", Name: " << current->name
                     << ", Type: " << current->type << ", Level: " << current->level
                     << ", Location: " << current->location << ", Desc: " << current->description
                     << ", Priority: " << current->priority << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found)
        {
            cout << "No emergencies found for type: " << filterType << endl;
        }
    }

    void sortQueueByPriority()
    {
        if (!head || !head->next)
            return; // 0 or 1 node, already sorted

        Emergency *sorted = NULL; // New sorted list

        Emergency *current = head;
        while (current != NULL)
        {
            Emergency *next = current->next;

            // Insert current in sorted list
            if (!sorted || current->priority > sorted->priority)
            {
                current->next = sorted;
                sorted = current;
            }
            else
            {
                Emergency *temp = sorted;
                while (temp->next && temp->next->priority >= current->priority)
                {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }

        head = sorted; // Reset head to sorted list
    }

    ~PendingEmergency()
    {
        while (head != NULL)
        {
            Emergency *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// This class uses a Stack implemented using Linked List
class HistoryStack
{
    Emergency *top; // Top of the stack

public:
    HistoryStack()
    {
        top = NULL;
    }

    void push(Emergency *emergency)
    {
        // Create new node (linked list node)
        Emergency *newEmergency = new Emergency;
        *newEmergency = *emergency;
        newEmergency->next = top;
        top = newEmergency;
    }

    void display() const
    {
        Emergency *current = top;
        while (current != NULL)
        {
            cout << "Emergency Processed! " << endl;
            cout << "Name: " << current->name << ", Type: " << current->type
                 << ", Level: " << current->level << ", Location: " << current->location
                 << ", Desc: " << current->description
                 << ", Priority: " << current->priority << endl;
            current = current->next;
        }
    }

    bool empty() const
    {
        return top == NULL;
    }

    Emergency *getTop() const
    {
        if (top == NULL)
        {
            cout << "No history is Found";
        }
        return top;
    }
    ~HistoryStack()
    {
        while (top != NULL)
        {
            Emergency *temp = top;
            top = top->next;
            delete temp;
        }
    }
};

// This class uses a Linked List to manage users
class UserList
{
private:
    UserNode *head; // Head of user linked list

public:
    UserList()
    {
        head = NULL;
    }

    ~UserList()
    {
        while (head != NULL)
        {
            UserNode *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addUser(string username, string password, string role)
    {
        UserNode *newUser = new UserNode;
        newUser->username = username;
        newUser->password = password;
        newUser->role = role;
        newUser->next = head;
        head = newUser;
    }

    void deleteUser(string username)
    {
        UserNode *current = head;
        UserNode *previous = NULL;

        while (current != NULL)
        {
            if (current->username == username)
            {
                if (previous == NULL)
                {
                    head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }
                delete current;
                cout << "User deleted: " << username << endl;
                return;
            }
            previous = current;
            current = current->next;
        }

        cout << "User not found: " << username << endl;
    }

    UserNode *searchUser(string username)
    {
        UserNode *current = head;

        while (current != NULL)
        {
            if (current->username == username)
            {
                return current;
            }
            current = current->next;
        }

        return NULL;
    }

    void displayUsers()
    {
        clearScreen();
        if (head == NULL)
        {
            cout << "No users in the list." << endl;
            return;
        }

        UserNode *current = head;
        cout << "Users in the list:" << endl;
        while (current != NULL)
        {
            cout << "Username: " << current->username << ", Role: " << current->role << endl;
            current = current->next;
        }
    }
};

// Global Objects
PendingEmergency queue; // Queue (priority) of emergencies
HistoryStack stack;     // Stack of resolved emergencies
UserList Users;         // Linked list of users
UserNode *currentUser = NULL;

// Functions related to  emergency

void addEmergency()
{
    clearScreen();

    cout << "State Your Emergency! " << endl;

    string name, type, level, location, description;
    cout << "\nEnter Emergency Details:\n";
    cout << "Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Type (Medical, Accident, Fire, Crime, Natural Disaster): ";
    getline(cin, type);

    cout << "Level (Very Low, Low, Mid, High, Critical): ";
    getline(cin, level);

    cout << "Location: ";
    getline(cin, location);

    cout << "Description: ";
    getline(cin, description);

    int priority = calculatePriority(level, type);
    queue.push(name, type, level, location, description, priority);

    cout << "Emergency added successfully!\n";
    pauseScreen();
    clearScreen();
}

void deleteEmergency()
{
    clearScreen();
    if (queue.empty())
    {
        cout << "No emergency to delete." << endl;
    }
    else
    {
        Emergency *topEmergency = queue.GetHead();
        stack.push(topEmergency); // Push to stack
        queue.pop();              // Remove from queue
        cout << "Emergency Process." << endl;
    }
    pauseScreen();
    clearScreen();
}

void searchByFilter()
{
    clearScreen();
    string type;
    cout << "Enter type of filter: ";
    cin.ignore();
    getline(cin, type);
    queue.filterByType(type);
    pauseScreen();
    clearScreen();
}

void escalateEmergencies(int thresholdSeconds)
{
    time_t now = time(NULL);
    Emergency *current = queue.GetHead();

    while (current != NULL)
    {
        double elapsed = difftime(now, current->addedTime);
        if (elapsed > thresholdSeconds)
        {
            current->priority += 1;
            current->addedTime = now; // reset timer
        }
        current = current->next;
    }

    queue.sortQueueByPriority();
}

void showSummary()
{
    clearScreen();

    // Counters for each emergency type
    int medicalCount = 0, accidentCount = 0, fireCount = 0, crimeCount = 0, disasterCount = 0;
    Emergency *current = queue.GetHead();
while (current != NULL)
{
    string type = current->type;
    
    // Convert to lowercase
    transform(type.begin(), type.end(), type.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    // Now compare with lowercase versions
    if (type == "medical")
        medicalCount++;
    else if (type == "accident")
        accidentCount++;
    else if (type == "fire")
        fireCount++;
    else if (type == "crime")
        crimeCount++;
    else if (type == "natural disaster")
        disasterCount++;

    current = current->next;
}

    cout << "===== Pending Emergency Summary =====\n";
    cout << "Medical: " << medicalCount << endl;
    cout << "Accident: " << accidentCount << endl;
    cout << "Fire: " << fireCount << endl;
    cout << "Crime: " << crimeCount << endl;
    cout << "Natural Disaster: " << disasterCount << endl;

    pauseScreen();
}

// Functions related to processed history
void viewHistory()
{
    clearScreen();
    if (stack.empty())
    {
        cout << "No history available." << endl;
    }
    else
    {
        stack.display();
    }
    pauseScreen();
    clearScreen();
}

void searchEmergency()
{
    clearScreen();
    string keyword;
    cin.ignore();
    cout << "Enter keyword to search (ID / Type / Location / Description): ";
    getline(cin, keyword);

    Emergency *current = stack.getTop();
    bool found = false;

    while (current != NULL)
    {
        if (current->id == keyword || current->type == keyword ||
            current->location == keyword ||
            current->description == keyword)
        {

            cout << "ID: " << current->id << ", Name: " << current->name
                 << ", Type: " << current->type << ", Level: " << current->level
                 << ", Location: " << current->location << ", Desc: " << current->description
                 << ", Priority: " << current->priority << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found)
    {
        cout << endl;
        cout << "No emergency found with the given keyword: " << keyword << endl;
    }

    pauseScreen();
    clearScreen();
}

// Functions related to user management
void addStaff()
{
    clearScreen();

    string username, password;
    cout << "Enter username for the new staff: ";
    cin >> username;

    if (Users.searchUser(username) != NULL)
    {
        cout << "Username already exists. Please try again with a different username." << endl;
        pauseScreen();
        clearScreen();
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    string role = "Staff";
    Users.addUser(username, password, role);
    cout << "Staff added successfully." << endl;
}

void deleteStaff()
{
    clearScreen();
    string username;
    cout << "Enter username to delete: ";
    cin >> username;
    Users.deleteUser(username);
}

bool login(string username, string password)
{
    currentUser = Users.searchUser(username);
    if (currentUser == NULL || currentUser->password != password)
    {
        currentUser = NULL;
        return false;
    }
    return true;
}

void dashboard(UserNode *user)
{
    int choice;

    do
    {
        escalateEmergencies(600);
        clearScreen();
        cout << "\n====== DASHBOARD ======" << endl;
        cout << "Logged in as: " << user->username << " (" << user->role << ")\n";

        if (user->role == "Admin")
        {
            cout << "1. Add Emergency\n";
            cout << "2. View Emergencies\n";
            cout << "3. Process Emergency\n";
            cout << "4. View Processed History\n";
            cout << "5. Add Staff\n";
            cout << "6. Delete Staff\n";
            cout << "7. Search Processed Emergency by Keyword\n";
            cout << "8. Filter Emergency by Type\n";
            cout << "9. View Users\n";
            cout << "10. View Summary of Pending Emergencies\n";
            cout << "0. Logout\n";
        }
        else if (user->role == "Staff")
        {
            cout << "1. Add Emergency\n";
            cout << "2. View Emergencies\n";
            cout << "3. Process Emergency\n";
            cout << "4. View Processed History\n";
            cout << "0. Logout\n";
        }
        else
        {
            cout << "Invalid Role.\n";
            break;
        }

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addEmergency();
            break;
        case 2:
            clearScreen();
            if (queue.empty())
            {
                cout << "No emergencies in the queue." << endl;
            }
            else
            {
                queue.display();
            }
            pauseScreen();
            clearScreen();
            break;
        case 3:
            deleteEmergency();
            break;
        case 4:
            viewHistory();
            break;
        case 5:
            if (user->role == "Admin")
                addStaff();
            else
                cout << "Invalid option.\n";
            pauseScreen();
            break;
        case 6:
            if (user->role == "Admin")
                deleteStaff();
            else
                cout << "Invalid option.\n";
            pauseScreen();
            break;
        case 7:
            if (user->role == "Admin")
            {
                searchEmergency();
            }
            else
            {
                cout << "Invalid option.\n";
                pauseScreen();
            }
            break;
        case 8:
            if (user->role == "Admin")
            {
                searchByFilter();
            }
            else
            {
                cout << "Invalid option.\n";
                pauseScreen();
            }
            break;
        case 9:
            if (user->role == "Admin")
            {
                Users.displayUsers();
                pauseScreen();
            }
            else
            {
                cout << "Invalid option.\n";
                pauseScreen();
            }
            break;
        case 10:
            if (user->role == "Admin")
            {
                showSummary();
            }
            else
            {
                cout << "Invalid option.\n";
                pauseScreen();
            }
            break;

        case 0:
            cout << "Logging out...\n";
            pauseScreen();
            return;

        default:
            cout << "Invalid choice. Try again.\n";
            pauseScreen();
            break;
        }
    } while (true);
}

int main()
{
    Users.addUser("admin", "admin123", "Admin");
    // Change as needed
    int choice;
    bool isLoggedIn = false;

    do
    {
        escalateEmergencies(600);
        clearScreen();
        cout << "\n===== Emergency Response System =====\n";
        cout << "1. Login\n";
        cout << "2. Add Emergency\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            clearScreen();
            cout << "\nEnter the Username and Password: " << endl;
            cout << "\n";
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            isLoggedIn = login(username, password);
            if (isLoggedIn)

            {
                cout << endl;
                cout << "Login successful! Welcome, " << currentUser->username << " (" << currentUser->role << ")\n";
                pauseScreen();
                dashboard(currentUser);
            }
            else
            {
                cout << endl;

                cout << "Invalid username or password.\n";
                pauseScreen();
                clearScreen();
            }
            break;
        }

        case 2:

            addEmergency();
            break;

        case 0:
            cout << "EXITING PROGRAM.....\n";

            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
