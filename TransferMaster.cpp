#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

#define RESET 7
#define RED 12
#define GREEN 10
#define YELLOW 14
#define BLUE 9
#define CYAN 11

// Player Class
class Player {
private:
    int id;
    string name;
    int age;
    string position;
    char status; // A = Active, I = Inactive, T = Terminated
    int goals;
    int assists;
    int matches;
    int tacklesWon;
    int keyPasses;

public:
    Player(int id = 0, string name = "", int age = 0, string position = "",
           char status = 'A', int goals = 0, int assists = 0, int matches = 0,
           int tacklesWon = 0, int keyPasses = 0)
        : id(id), name(name), age(age), position(position), status(status),
          goals(goals), assists(assists), matches(matches), tacklesWon(tacklesWon), keyPasses(keyPasses) {}

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getPosition() const { return position; }
    char getStatus() const { return status; }
    int getGoals() const { return goals; }
    int getAssists() const { return assists; }
    int getMatches() const { return matches; }
    int getTacklesWon() const { return tacklesWon; }
    int getKeyPasses() const { return keyPasses; }

    // Setters
    void setName(const string &newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setPosition(const string &newPosition) { position = newPosition; }
    void setStatus(char newStatus) { status = newStatus; }
    void setGoals(int newGoals) { goals = newGoals; }
    void setAssists(int newAssists) { assists = newAssists; }
    void setMatches(int newMatches) { matches = newMatches; }
    void setTacklesWon(int newTacklesWon) { tacklesWon = newTacklesWon; }
    void setKeyPasses(int newKeyPasses) { keyPasses = newKeyPasses; }

    // Display player info
    void display() const {
        cout << setw(5) << id << setw(20) << name << setw(10) << age
             << setw(15) << position << setw(10) << status << setw(10) << goals
             << setw(10) << assists << setw(10) << matches << setw(10) << tacklesWon << "\t"
             << setw(20) << keyPasses << endl;
    }
};

vector<Player> players;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void clearScreen() {
    system("cls");
}

void displayLoading() {
    setColor(YELLOW);
    cout << "Loading";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        Sleep(500);
    }
    cout << "\n";
    clearScreen();
}

void savePlayersToFile() {
    ofstream file("players.txt");
    if (!file) {
        cerr << "Error saving players to file.\n";
        return;
    }
    for (const auto &player : players) {
        file << player.getId() << "|" << player.getName() << "|" << player.getAge() << "|"
             << player.getPosition() << "|" << player.getStatus() << "|" << player.getGoals() << "|"
             << player.getAssists() << "|" << player.getMatches() << "|" << player.getTacklesWon()
             << "|" << player.getKeyPasses() << "\n";
    }
    file.close();
}

void loadPlayersFromFile() {
    ifstream file("players.txt");
    if (!file) {
        cerr << "Error loading players from file.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        vector<string> data;
        while ((pos = line.find('|')) != string::npos) {
            data.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        data.push_back(line);

        Player player(stoi(data[0]), data[1], stoi(data[2]), data[3], data[4][0],
                      stoi(data[5]), stoi(data[6]), stoi(data[7]), stoi(data[8]), stoi(data[9]));
        players.push_back(player);
    }
    file.close();
}

void saveAdminPasswordToFile(const string& password) {
    ofstream file("admin_password.txt");
    if (!file) {
        cerr << "Error saving admin password to file.\n";
        return;
    }
    file << password;
    file.close();
}

string loadAdminPasswordFromFile() {
    ifstream file("admin_password.txt");
    if (!file) {
        cerr << "Error loading admin password from file.\n";
        return "admin123"; // Default password
    }

    string password;
    getline(file, password);
    file.close();
    return password;
}

class Club {
private:
    struct Client {
        int id;
        string name;
        string password;
        string agentName;
        string email;
        string phoneNo;
        bool isApproved;
        double balance;

        // Constructor to initialize the Client object
        Client(int id = 0, string name = "", string password = "", string agentName = "", 
               string email = "", string phoneNo = "", bool isApproved = false, double balance = 0.0)
            : id(id), name(name), password(password), agentName(agentName), 
              email(email), phoneNo(phoneNo), isApproved(isApproved), balance(balance) {}
    };

    Client clients[100];  // Fixed array for simplicity (supports up to 100 clients)
    int clientCount;      // Tracks the number of registered clients

    bool isStrongPassword(const string &password) {
        if (password.length() < 8) return false;
        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
        for (char ch : password) {
            if (isupper(ch)) hasUpper = true;
            else if (islower(ch)) hasLower = true;
            else if (isdigit(ch)) hasDigit = true;
            else hasSpecial = true;
        }
        return hasUpper && hasLower && hasDigit && hasSpecial;
    }

public:
    Club() : clientCount(0) {}

    void registerClient() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Client Registration\n====================\n";
        setColor(RESET);

        if (clientCount >= 100) {
            setColor(RED);
            cout << "Client registration limit reached!\n";
            setColor(RESET);
            Sleep(1500);
            return;
        }

        string name, password, agentName, email, phoneNo;
        setColor(YELLOW);
        cout << "Enter Name: ";
        setColor(RESET);
        cin >> name;
        while (true) {
            setColor(YELLOW);
            cout << "Enter Password: ";
            setColor(RESET);
            fflush(stdin);
            cin >> password;

            if (!isStrongPassword(password)) {
                setColor(RED);
                cout << "Password must be at least 8 characters long and include an uppercase letter, a lowercase letter, a digit, and a special character.\n";
                setColor(RESET);
                continue;
            }
            break;
        }

        setColor(YELLOW);
        cout << "Enter Agent Name: ";
        setColor(RESET);
        cin >> agentName;
        setColor(YELLOW);
        fflush(stdin);
        cout << "Enter Email: ";
        setColor(RESET);
        cin >> email;
        setColor(YELLOW);
        fflush(stdin);
        cout << "Enter Phone No: ";
        setColor(RESET);
        cin >> phoneNo;

        int id = clientCount + 1;  // Sequential ID
        clients[clientCount] = Client(id, name, password, agentName, email, phoneNo, false, 0.0);  // Using constructor
        clientCount++;

        setColor(GREEN);
        cout << "Registration successful! Your ID is: " << id << endl;
        setColor(RESET);
        Sleep(1500);
    }

    void loginClient() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Client Login\n====================\n";
        setColor(RESET);

        int id;
        string password;
        setColor(YELLOW);
        cout << "Enter ID: ";
        setColor(RESET);
        cin >> id;
        setColor(YELLOW);
        cout << "Enter Password: ";
        setColor(RESET);
        cin >> password;

        for (int i = 0; i < clientCount; i++) {
            if (clients[i].id == id && clients[i].password == password) {
                setColor(GREEN);
                cout << "Login successful!\n";
                setColor(RESET);
                clients[i].isApproved = true;  // Approve login
                Sleep(1500);
                return;
            }
        }

        setColor(RED);
        cout << "Invalid ID or Password!\n";
        setColor(RESET);
        Sleep(1500);
    }

    void changePassword() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Change Client Password\n====================\n";
        setColor(RESET);

        int id;
        string currentPassword, newPassword;
        setColor(YELLOW);
        cout << "Enter ID: ";
        setColor(RESET);
        cin >> id;

        for (int i = 0; i < clientCount; i++) {
            if (clients[i].id == id) {
                setColor(YELLOW);
                cout << "Enter Current Password: ";
                setColor(RESET);
                cin >> currentPassword;

                if (clients[i].password == currentPassword) {
                    while (true) {
                        setColor(YELLOW);
                        cout << "Enter New Password: ";
                        setColor(RESET);
                        cin >> newPassword;

                        if (!isStrongPassword(newPassword)) {
                            setColor(RED);
                            cout << "Password must be at least 8 characters long and include an uppercase letter, a lowercase letter, a digit, and a special character.\n";
                            setColor(RESET);
                            continue;
                        }
                        break;
                    }
                    clients[i].password = newPassword;
                    setColor(GREEN);
                    cout << "Password changed successfully!\n";
                    setColor(RESET);
                    Sleep(1500);
                    return;
                } else {
                    setColor(RED);
                    cout << "Incorrect Current Password!\n";
                    setColor(RESET);
                    Sleep(1500);
                    return;
                }
            }
        }

        setColor(RED);
        cout << "Client ID not found!\n";
        setColor(RESET);
        Sleep(1500);
    }

    void forgotPassword() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Forgot Password\n====================\n";
        setColor(RESET);

        int id;
        setColor(YELLOW);
        cout << "Enter your ID: ";
        setColor(RESET);
        cin >> id;

        for (int i = 0; i < clientCount; i++) {
            if (clients[i].id == id) {
                setColor(GREEN);
                cout << "Your password is: " << clients[i].password << endl;
                setColor(RESET);
                Sleep(3000);
                return;
            }
        }

        setColor(RED);
        cout << "Client ID not found!\n";
        setColor(RESET);
        Sleep(1500);
    }

    void checkLoginStatus() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Check Login Status\n====================\n";
        setColor(RESET);

        int id;
        setColor(YELLOW);
        cout << "Enter your ID: ";
        setColor(RESET);
        cin >> id;

        for (int i = 0; i < clientCount; i++) {
            if (clients[i].id == id) {
                if (clients[i].isApproved) {
                    setColor(GREEN);
                    cout << "Login status: Approved\n";
                    setColor(RESET);
                } else {
                    setColor(RED);
                    cout << "Login status: Not Approved\n";
                    setColor(RESET);
                }
                Sleep(1500);
                return;
            }
        }

        setColor(RED);
        cout << "Client ID not found!\n";
        setColor(RESET);
        Sleep(1500);
    }

    void approveClient() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Approve Club\n====================\n";
        setColor(RESET);

        if (clientCount == 0) {
            setColor(RED);
            cout << "No client registrations found!\n";
            setColor(RESET);
            Sleep(1500);
            return;
        }

        setColor(GREEN);
        cout << "Pending Club Approvals:\n";
        for (int i = 0; i < clientCount; i++) {
            if (!clients[i].isApproved) {
                cout << "ID: " << clients[i].id << ", Name: " << clients[i].name << ", Agent Name: " << clients[i].agentName << "\n";
            }
        }
        setColor(RESET);

        int id;
        setColor(YELLOW);
        cout << "Enter Client ID to Approve: ";
        setColor(RESET);
        cin >> id;

        for (int i = 0; i < clientCount; i++) {
            if (clients[i].id == id && !clients[i].isApproved) {
                clients[i].isApproved = true;
                setColor(GREEN);
                cout << "Client ID " << id << " approved successfully!\n";
                setColor(RESET);
                Sleep(1500);
                return;
            }
        }

        setColor(RED);
        cout << "Client ID not found or already approved!\n";
        setColor(RESET);
        Sleep(1500);
    }

    void editClient() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Edit Club\n====================\n";
        setColor(RESET);

        int id;
        setColor(YELLOW);
        cout << "Enter Client ID to Edit: ";
        setColor(RESET);
        cin >> id;

        for (int i = 0; i < clientCount; i++) {
            if (clients[i].id == id) {
                while (true) {
                    clearScreen();
                    setColor(CYAN);
                    cout << "TransferMaster - Edit Club Details\n====================\n";
                    setColor(GREEN);
                    cout << "1) Name\n";
                    cout << "2) Agent Name\n";
                    cout << "3) Password\n";
                    cout << "4) Email\n";
                    cout << "5) Phone No\n";
                    cout << "6) Back to Club Management\n";
                    setColor(RESET);
                    setColor(YELLOW);
                    cout << "Enter your choice: ";
                    setColor(RESET);

                    int choice;
                    cin >> choice;
                    displayLoading();
                    clearScreen();

                    switch (choice) {
                        case 1: {
                            setColor(YELLOW);
                            cout << "Enter New Name (Current: " << clients[i].name << "): ";
                            setColor(RESET);
                            cin.ignore();
                            string newName;
                            getline(cin, newName);
                            clients[i].name = newName;
                            break;
                        }
                        case 2: {
                            setColor(YELLOW);
                            cout << "Enter New Agent Name (Current: " << clients[i].agentName << "): ";
                            setColor(RESET);
                            cin.ignore();
                            string newAgentName;
                            getline(cin, newAgentName);
                            clients[i].agentName = newAgentName;
                            break;
                        }
                        case 3: {
                            while (true) {
                                setColor(YELLOW);
                                cout << "Enter New Password: ";
                                setColor(RESET);
                                string newPassword;
                                cin >> newPassword;

                                if (!isStrongPassword(newPassword)) {
                                    setColor(RED);
                                    cout << "Password must be at least 8 characters long and include an uppercase letter, a lowercase letter, a digit, and a special character.\n";
                                    setColor(RESET);
                                    continue;
                                }
                                clients[i].password = newPassword;
                                break;
                            }
                            break;
                        }
                        case 4: {
                            setColor(YELLOW);
                            cout << "Enter New Email (Current: " << clients[i].email << "): ";
                            setColor(RESET);
                            cin.ignore();
                            string newEmail;
                            getline(cin, newEmail);
                            clients[i].email = newEmail;
                            break;
                        }
                        case 5: {
                            setColor(YELLOW);
                            cout << "Enter New Phone No (Current: " << clients[i].phoneNo << "): ";
                            setColor(RESET);
                            cin.ignore();
                            string newPhoneNo;
                            getline(cin, newPhoneNo);
                            clients[i].phoneNo = newPhoneNo;
                            break;
                        }
                        case 6:
                            return;
                        default:
                            setColor(RED);
                            cout << "Invalid choice! Try again.\n";
                            setColor(RESET);
                            Sleep(1500);
                    }
                }
            }
        }

        setColor(RED);
        cout << "Client ID not found!\n";
        setColor(RESET);
        Sleep(1500);
    }

    void deleteClient() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Delete Club\n====================\n";
        setColor(RESET);

        int id;
        setColor(YELLOW);
        cout << "Enter Client ID to Delete: ";
        setColor(RESET);
        cin >> id;
        displayLoading();
        clearScreen();

        auto it = remove_if(clients, clients + clientCount, [id](const Client &c) { return c.id == id; });
        if (it != clients + clientCount) {
            clientCount--;
            setColor(GREEN);
            cout << "Client deleted successfully!\n";
            setColor(RESET);
        } else {
            setColor(RED);
            cout << "Client ID not found!\n";
            setColor(RESET);
        }
        Sleep(1500);
    }

    void searchClient() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Search Club\n====================\n";
        setColor(RESET);

        int id;
        setColor(YELLOW);
        cout << "Enter Client ID to Search: ";
        setColor(RESET);
        cin >> id;
        displayLoading();
        clearScreen();

        for (int i = 0; i < clientCount; i++) {
            if (clients[i].id == id) {
                setColor(GREEN);
                cout << "Client Found!\n";
                cout << "ID: " << clients[i].id << "\n";
                cout << "Name: " << clients[i].name << "\n";
                cout << "Agent Name: " << clients[i].agentName << "\n";
                cout << "Email: " << clients[i].email << "\n";
                cout << "Phone No: " << clients[i].phoneNo << "\n";
                cout << "Balance: $" << fixed << setprecision(2) << clients[i].balance << "\n";
                setColor(RESET);
                Sleep(3000);
                return;
            }
        }

        setColor(RED);
        cout << "Client ID not found!\n";
        setColor(RESET);
        Sleep(1500);
    }

    void updateBalance() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Update Balance\n====================\n";
        setColor(RESET);

        int id;
        double newBalance;
        setColor(YELLOW);
        cout << "Enter Client ID to Update Balance: ";
        setColor(RESET);
        cin >> id;
        displayLoading();
        clearScreen();

        for (int i = 0; i < clientCount; i++) {
            if (clients[i].id == id) {
                setColor(YELLOW);
                cout << "Enter New Balance: ";
                setColor(RESET);
                cin >> newBalance;
                clients[i].balance = newBalance;
                setColor(GREEN);
                cout << "Balance updated successfully!\n";
                setColor(RESET);
                Sleep(1500);
                return;
            }
        }

        setColor(RED);
        cout << "Client ID not found!\n";
        setColor(RESET);
        Sleep(1500);
    }

    void viewAllClients() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - All Clubs\n====================\n";
        setColor(RESET);

        if (clientCount == 0) {
            setColor(RED);
            cout << "No clients found!\n";
            setColor(RESET);
            Sleep(1500);
            return;
        }

        setColor(GREEN);
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(20) << "Agent Name"
             << setw(30) << "Email" << setw(15) << "Phone No" << setw(10) << "Balance\n";
        cout << "----------------------------------------------------------------------------------------------------------------\n";

        for (int i = 0; i < clientCount; i++) {
            cout << setw(5) << clients[i].id << setw(20) << clients[i].name << setw(20) << clients[i].agentName
                 << setw(30) << clients[i].email << setw(15) << clients[i].phoneNo << setw(10) << fixed << setprecision(2) << clients[i].balance << "\n";
        }
        setColor(RESET);

        cout << "\nPress any key to return to Club Management...\n";
        _getch();
    }
};

class Admin {
private:
    string adminPassword;

    bool isStrongPassword(const string &password) {
        if (password.length() < 8) return false;
        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
        for (char ch : password) {
            if (isupper(ch)) hasUpper = true;
            else if (islower(ch)) hasLower = true;
            else if (isdigit(ch)) hasDigit = true;
            else hasSpecial = true;
        }
        return hasUpper && hasLower && hasDigit && hasSpecial;
    }

public:
    Admin() {
        adminPassword = loadAdminPasswordFromFile();
    }

    void changeAdminPassword() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Change Admin Password\n====================\n";
        setColor(RESET);

        setColor(YELLOW);
        cout << "Enter current password: ";
        setColor(RESET);
        string currentPassword;
        cin >> currentPassword;

        if (currentPassword != adminPassword) {
            setColor(RED);
            cout << "Incorrect current password! Returning to main menu.\n";
            setColor(RESET);
            Sleep(1500);
            return;
        }

        string newPassword, confirmPassword;

        while (true) {
            setColor(YELLOW);
            cout << "Enter new admin password: ";
            setColor(RESET);
            cin >> newPassword;

            if (!isStrongPassword(newPassword)) {
                setColor(RED);
                cout << "Password must be at least 8 characters long and include an uppercase letter, a lowercase letter, a digit, and a special character.\n";
                setColor(RESET);
                continue;
            }

            setColor(YELLOW);
            cout << "Confirm new password: ";
            setColor(RESET);
            cin >> confirmPassword;

            if (newPassword == confirmPassword) {
                adminPassword = newPassword;
                saveAdminPasswordToFile(adminPassword);
                setColor(GREEN);
                cout << "Password changed successfully! Returning to main menu.\n";
                setColor(RESET);
                Sleep(1500);
                return;
            } else {
                setColor(RED);
                cout << "Passwords do not match. Try again.\n";
                setColor(RESET);
            }
        }
    }

    bool authenticate() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Admin Login\n====================\n";
        setColor(YELLOW);
        cout << "Enter admin password: ";
        setColor(RESET);
        char enteredPassword[256];
        int i = 0;
        char ch;
        while (true) {
            ch = _getch();
            if (ch == '\r') break;
            if (ch == '\b' && i > 0) {
                i--;
                cout << "\b \b";
            } else if (ch != '\b') {
                enteredPassword[i++] = ch;
                cout << "*";
            }
        }
        enteredPassword[i] = '\0';
        cout << "\n";

        if (adminPassword == enteredPassword) {
            setColor(GREEN);
            cout << "Access granted!\n";
            setColor(RESET);
            displayLoading();
            clearScreen();
            return true;
        } else {
            setColor(RED);
            cout << "Access denied: Incorrect password!\n";
            setColor(RESET);
            Sleep(1500);
            return false;
        }
    }

    void editPlayer() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Edit Player\n====================\n";
        setColor(RESET);

        int id;
        setColor(YELLOW);
        cout << "Enter Player ID to Edit: ";
        setColor(RESET);
        cin >> id;
        displayLoading();
        clearScreen();

        for (auto &player : players) {
            if (player.getId() == id) {
                while (true) {
                    clearScreen();
                    setColor(CYAN);
                    cout << "TransferMaster - Edit Player Details\n====================\n";
                    setColor(GREEN);
                    cout << "1) Name\n";
                    cout << "2) Age\n";
                    cout << "3) Back to Player Management\n";
                    setColor(RESET);
                    setColor(YELLOW);
                    cout << "Enter your choice: ";
                    setColor(RESET);

                    int choice;
                    cin >> choice;
                    displayLoading();
                    clearScreen();

                    switch (choice) {
                        case 1: {
                            setColor(YELLOW);
                            cout << "Enter New Name (Current: " << player.getName() << "): ";
                            setColor(RESET);
                            cin.ignore();
                            string newName;
                            getline(cin, newName);
                            player.setName(newName);
                            break;
                        }
                        case 2: {
                            setColor(YELLOW);
                            cout << "Enter New Age (Current: " << player.getAge() << "): ";
                            setColor(RESET);
                            int newAge;
                            cin >> newAge;
                            player.setAge(newAge);
                            break;
                        }
                        case 3:
                            savePlayersToFile();
                            return;
                        default:
                            setColor(RED);
                            cout << "Invalid choice! Try again.\n";
                            setColor(RESET);
                            Sleep(1500);
                    }
                }
            }
        }

        setColor(RED);
        cout << "Player ID not found!\n";
        setColor(RESET);
        Sleep(1500);
    }

    void deletePlayer() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Delete Player\n====================\n";
        setColor(RESET);

        int id;
        setColor(YELLOW);
        cout << "Enter Player ID to Delete: ";
        setColor(RESET);
        cin >> id;
        displayLoading();
        clearScreen();

        auto it = remove_if(players.begin(), players.end(), [id](const Player &p) { return p.getId() == id; });
        if (it != players.end()) {
            players.erase(it, players.end());
            savePlayersToFile();
            setColor(GREEN);
            cout << "Player deleted successfully!\n";
            setColor(RESET);
        } else {
            setColor(RED);
            cout << "Player ID not found!\n";
            setColor(RESET);
        }
        Sleep(1500);
    }

    void searchPlayer() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Search Player\n====================\n";
        setColor(RESET);

        int id;
        setColor(YELLOW);
        cout << "Enter Player ID to Search: ";
        setColor(RESET);
        cin >> id;
        displayLoading();
        clearScreen();

        for (const auto &player : players) {
            if (player.getId() == id) {
                setColor(GREEN);
                cout << "Player Found!\n";
                player.display();
                setColor(RESET);
                Sleep(3000);
                return;
            }
        }

        setColor(RED);
        cout << "Player ID not found!\n";
        setColor(RESET);
        Sleep(1500);
    }

    void playerManagement() {
        while (true) {
            clearScreen();
            setColor(CYAN);
            cout << "TransferMaster - Player Management\n====================\n";
            setColor(GREEN);
            cout << "1) Add Player\n";
            cout << "2) Edit Player\n";
            cout << "3) Delete Player\n";
            cout << "4) Search Player\n";
            cout << "5) Update Player Stats and Status\n";
            cout << "6) View All Players\n";
            cout << "7) Release Player from Club\n";
            cout << "8) Back to Admin Menu\n";
            setColor(RESET);
            setColor(YELLOW);
            cout << "Enter your choice: ";
            setColor(RESET);

            int choice;
            cin >> choice;
            displayLoading();
            clearScreen();

            switch (choice) {
                case 1:
                    addPlayer();
                    break;
                case 2:
                    editPlayer();
                    break;
                case 3:
                    deletePlayer();
                    break;
                case 4:
                    searchPlayer();
                    break;
                case 5:
                    updatePlayerStats();
                    break;
                case 6:
                    viewAllPlayers();
                    break;
                case 7:
                    releasePlayer();
                    break;
                case 8:
                    return;
                default:
                    setColor(RED);
                    cout << "Invalid choice! Try again.\n";
                    setColor(RESET);
                    Sleep(1500);
            }
        }
    }

    void addPlayer() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Add Player\n====================\n";
        setColor(RESET);

        Player newPlayer(players.empty() ? 1 : players.back().getId() + 1);

        setColor(YELLOW);
        cout << "Enter Player Name: ";
        setColor(RESET);
        cin.ignore();
        string name;
        getline(cin, name);
        newPlayer.setName(name);

        setColor(YELLOW);
        cout << "Enter Player Age: ";
        setColor(RESET);
        int age;
        cin >> age;
        newPlayer.setAge(age);
        
        setColor(GREEN);
        cout << "Player added successfully! Player ID: " << newPlayer.getId() << "\n";
        setColor(RESET);
        Sleep(1500);
        
        displayLoading();
        clearScreen();

        players.push_back(newPlayer);
        savePlayersToFile();
    }

    void updatePlayerStats() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Update Player Stats and Status\n====================\n";
        setColor(RESET);

        int id;
        setColor(YELLOW);
        cout << "Enter Player ID to Update: ";
        setColor(RESET);
        cin >> id;
        displayLoading();
        clearScreen();

        for (auto &player : players) {
            if (player.getId() == id) {
                while (true) {
                    clearScreen();
                    setColor(CYAN);
                    cout << "TransferMaster - Update Player Stats\n====================\n";
                    setColor(GREEN);
                    cout << "1) Goals Scored\n";
                    cout << "2) Assists\n";
                    cout << "3) Matches\n";
                    cout << "4) Tackles Won\n";
                    cout << "5) Key Passes\n";
                    cout << "6) Role\n";
                    cout << "7) Back to Player Management\n";
                    setColor(RESET);
                    setColor(YELLOW);
                    cout << "Enter your choice: ";
                    setColor(RESET);

                    int choice;
                    cin >> choice;
                    displayLoading();
                    clearScreen();

                    switch (choice) {
                        case 1: {
                            setColor(YELLOW);
                            cout << "Enter Goals Scored: ";
                            setColor(RESET);
                            int goals;
                            cin >> goals;
                            player.setGoals(goals);
                            break;
                        }
                        case 2: {
                            setColor(YELLOW);
                            cout << "Enter Assists: ";
                            setColor(RESET);
                            int assists;
                            cin >> assists;
                            player.setAssists(assists);
                            break;
                        }
                        case 3: {
                            setColor(YELLOW);
                            cout << "Enter Matches Played: ";
                            setColor(RESET);
                            int matches;
                            cin >> matches;
                            player.setMatches(matches);
                            break;
                        }
                        case 4: {
                            setColor(YELLOW);
                            cout << "Enter Tackles Won: ";
                            setColor(RESET);
                            int tacklesWon;
                            cin >> tacklesWon;
                            player.setTacklesWon(tacklesWon);
                            break;
                        }
                        case 5: {
                            setColor(YELLOW);
                            cout << "Enter Key Passes: ";
                            setColor(RESET);
                            int keyPasses;
                            cin >> keyPasses;
                            player.setKeyPasses(keyPasses);
                            break;
                        }
                        case 6: {
                            setColor(YELLOW);
                            cout << "Enter Role (Goalkeeper, Defender, Midfielder, Forward): ";
                            setColor(RESET);
                            cin.ignore();
                            string newRole;
                            getline(cin, newRole);
                            player.setPosition(newRole);
                            break;
                        }
                        case 7:
                            savePlayersToFile();
                            return;
                        default:
                            setColor(RED);
                            cout << "Invalid choice! Try again.\n";
                            setColor(RESET);
                            Sleep(1500);
                    }
                }
            }
        }

        setColor(RED);
        cout << "Player ID not found!\n";
        setColor(RESET);
        Sleep(1500);
    }

    void releasePlayer() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Release Player\n====================\n";
        setColor(RESET);

        int id;
        setColor(YELLOW);
        cout << "Enter Player ID to Release: ";
        setColor(RESET);
        cin >> id;
        displayLoading();
        clearScreen();

        auto it = remove_if(players.begin(), players.end(), [id](const Player &p) { return p.getId() == id; });
        if (it != players.end()) {
            players.erase(it, players.end());
            savePlayersToFile();
            setColor(GREEN);
            cout << "Player released successfully!\n";
            setColor(RESET);
        } else {
            setColor(RED);
            cout << "Player ID not found!\n";
            setColor(RESET);
        }
        Sleep(1500);
        clearScreen();
    }

    void viewAllPlayers() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - All Players\n====================\n";
        setColor(RESET);

        if (players.empty()) {
            setColor(RED);
            cout << "No players found!\n";
            setColor(RESET);
            Sleep(1500);
            return;
        }

        setColor(GREEN);
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Age"
             << setw(15) << "Position" << setw(10) << "Status" << setw(10) << "Goals"
             << setw(10) << "Assists" << setw(10) << "Matches" << setw(10) << "Tackles"
             << setw(10) << "\tKeyPasses\n";
        cout << "----------------------------------------------------------------------------------------------------------------\n";

        for (const auto &player : players) {
            player.display();
        }
        setColor(RESET);

        cout << "\nPress any key to return to Player Management...\n";
        _getch();
    }
    
    void clubManagement(Club &club);
};

void Admin::clubManagement(Club &club) {
    while (true) {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Club Management\n====================\n";
        setColor(GREEN);
        cout << "1) Approve Club\n";
        cout << "2) Edit Club\n";
        cout << "3) Delete Club\n";
        cout << "4) Search Club\n";
        cout << "5) Update Balance of Club\n";
        cout << "6) View All Clubs\n";
        cout << "7) Back to Admin Menu\n";
        setColor(RESET);
        setColor(YELLOW);
        cout << "Enter your choice: ";
        setColor(RESET);

        int choice;
        cin >> choice;
        displayLoading();
        clearScreen();

        switch (choice) {
            case 1:
                club.approveClient();
                break;
            case 2:
            	club.editClient();
                break;
            case 3:
                club.deleteClient();
                break;
            case 4:
                club.searchClient();
                break;
            case 5:
                club.updateBalance();
                break;
            case 6:
                club.viewAllClients();
                break;
            case 7:
                return;
            default:
                setColor(RED);
                cout << "Invalid choice! Try again.\n";
                setColor(RESET);
                Sleep(1500);
        }
    }
}

void clientMenu(Club& club) {
    int choice;
    do {
        displayLoading();
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Client Menu\n====================\n";
        setColor(GREEN);
        cout << "1) Register\n";
        cout << "2) Login\n";
        cout << "3) Change Password\n";
        cout << "4) Forgot Password?\n";
        cout << "5) Check Login Status\n";
        cout << "6) Back to Main Menu\n";
        setColor(RESET);
        setColor(YELLOW);
        cout << "Enter your choice: ";
        setColor(RESET);

        cin >> choice;
        displayLoading();
        clearScreen();

        switch (choice) {
        case 1:
            club.registerClient();
            break;
        case 2:
            club.loginClient();
            break;
        case 3:
            club.changePassword();
            break;
        case 4:
            club.forgotPassword();
            break;
        case 5:
            club.checkLoginStatus();
            break;
        case 6:
            cout << "Returning to Main Menu...\n";
            Sleep(1500);
            break;
        default:
            setColor(RED);
            cout << "Invalid choice! Please try again.\n";
            setColor(RESET);
            Sleep(1500);
        }
    } while (choice != 6);
}

int main() {
    Admin admin;
    Club club; // Create an instance of the Club class
    loadPlayersFromFile();

    while (true) {
        displayLoading();
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Main Menu\n====================\n";
        setColor(GREEN);
        cout << "1) Admin\n2) Client (Club)\n3) Privacy Policy\n4) About Us\n5) Exit\n";
        setColor(RESET);
        setColor(YELLOW);
        cout << "Enter your choice: ";
        setColor(RESET);

        int choice;
        cin >> choice;
        displayLoading();
        clearScreen();

        switch (choice) {
            case 1: // Admin Section
                if (admin.authenticate()) {
                    while (true) {
                        clearScreen();
                        setColor(CYAN);
                        cout << "TransferMaster - Admin Menu\n====================\n";
                        setColor(GREEN);
                        cout << "1) Player Management\n";
                        cout << "2) Club Management\n";
                        cout << "3) Change Admin Password\n";
                        cout << "4) Back to Main Menu\n";
                        setColor(RESET);
                        setColor(YELLOW);
                        cout << "Enter your choice: ";
                        setColor(RESET);

                        int adminChoice;
                        cin >> adminChoice;
                        displayLoading();
                        clearScreen();

                        if (adminChoice == 1) {
                            admin.playerManagement();
                        } else if (adminChoice == 2) {
                            admin.clubManagement(club);
                        } else if (adminChoice == 3) {
                            admin.changeAdminPassword();
                        } else if (adminChoice == 4) {
                            break;
                        } else {
                            setColor(RED);
                            cout << "Invalid choice! Try again.\n";
                            setColor(RESET);
                            Sleep(1500);
                        }
                    }
                }
                break;

            case 2: // Client (Club) Section
                clientMenu(club);
                break;

            case 3: // Privacy Policy
                clearScreen();
                setColor(YELLOW);
                cout << "TransferMaster - Privacy Policy\n====================\n";
                setColor(RESET);
                cout << "We value your privacy and securely store all data.\n";
                Sleep(2000);
                break;

            case 4: // About Us
                clearScreen();
                setColor(CYAN);
                cout << "TransferMaster - About Us\n====================\n";
                setColor(YELLOW);
                cout << "TransferMaster is your go-to application for managing football players.\n";
                cout << "Designed for clubs to efficiently manage player data and player transfers.\n";
                setColor(RESET);
                cout << "\nPress any key to return to the main menu...\n";
                _getch();
                break;

            case 5: // Exit
                displayLoading();
                setColor(RED);
                cout << "Thank you for using TransferMaster. Goodbye!\n";
                setColor(RESET);
                exit(0);

            default: // Invalid Input
                setColor(RED);
                cout << "Invalid choice! Try again.\n";
                setColor(RESET);
                Sleep(1500);
        }
    }

    return 0;
}
