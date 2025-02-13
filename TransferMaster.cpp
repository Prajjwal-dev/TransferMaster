#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cmath>

using namespace std;

#define RESET 7
#define RED 12
#define GREEN 10
#define YELLOW 14
#define CYAN 11

// Set color for console output
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Clear console screen
void clearScreen() {
    system("cls");
}

// Display loading animation
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

// Continue prompt for invalid input
bool continuePrompt() {
    char check;
    setColor(CYAN);
    cout << "Do you want to continue (Y/N): ";
    setColor(RESET);
    cin >> check;
    while (check != 'Y' && check != 'y' && check != 'N' && check != 'n') {
        setColor(RED);
        cout << "Error: Invalid input! Please enter Y or N: ";
        setColor(RESET);
        cin >> check;
    }
    if (check == 'N' || check == 'n') {
        setColor(RED);
        cout << "Exiting...\n";
        setColor(RESET);
        exit(0);
    }
    return (check == 'Y' || check == 'y');
}

void gameRules() {
    clearScreen();
    setColor(CYAN);
    cout << "TransferMaster - Game Rules\n====================\n";
    setColor(YELLOW);
    cout << "1. A football match is played by two teams, each consisting of not more than 11 players.\n";
    cout << "2. The match is played on a rectangular field with a goal at each end.\n";
    cout << "3. The objective is to score by getting the ball into the opposing goal.\n";
    cout << "4. The match is won by the team that scores the most goals.\n";
    cout << "5. Players can be assigned to different roles such as Goalkeeper, Defender, Midfielder, Forward, or Striker.\n";
    setColor(RESET);
    cout << "\nPress any key to return...\n";
    _getch();
}

void transferGuidelines() {
    clearScreen();
    setColor(CYAN);
    cout << "TransferMaster - Transfer Guidelines\n====================\n";
    setColor(YELLOW);
    cout << "1. Player should be active.\n";
    cout << "2. If insufficient balance, no transfer.\n";
    cout << "3. Default contract length: 3 years.\n";
    cout << "4. Transfer fee is managed using a regression model based on current transfer value fee trends.\n";
    cout << "5. Ratings are calculated on the basis of stats using a regression model.\n";
    cout << "6. Admin handles releasing player from club.\n";
    cout << "7. Admin handles balance of club.\n";
    cout << "8. Negotiation is usually done by Agent.\n";
    cout << "9. Use of roster to manage player from club.\n";
    cout << "10. The player must be 16 years or above for transfer.\n";
    cout << "11. Overall AI model is used for performing the task.\n";
    cout << "\nRating and Market Value Table:\n";
    cout << "----------------------------------------\n";
    cout << "Level 1 - Minimum: Rating 50, Market Value $10M\n";
    cout << "Level 2 - Average: Rating 75, Market Value $50M\n";
    cout << "Level 3 - Maximum: Rating 100, Market Value $120M\n";
    cout << "----------------------------------------\n";
    setColor(RESET);
    cout << "\nPress any key to return...\n";
    _getch();
}

// Player Class
class Player {
private:
    int id;
    string name;
    int age;
    string nationality;
    string position;
    char status; // A = Active, I = Inactive, T = Terminated
    int goals;
    int assists;
    int matches;
    int tacklesWon;
    int keyPasses;
    int injuries;
    string contractStartDate;
    string contractEndDate;
    string club;

public:
    Player(int id = 0, string name = "", int age = 0, string nationality = "", string position = "",
           char status = 'A', int goals = 0, int assists = 0, int matches = 0,
           int tacklesWon = 0, int keyPasses = 0, int injuries = 0, string contractStartDate = "",
           string contractEndDate = "", string club = "")
        : id(id), name(name), age(age), nationality(nationality), position(position), status(status),
          goals(goals), assists(assists), matches(matches), tacklesWon(tacklesWon), keyPasses(keyPasses),
          injuries(injuries), contractStartDate(contractStartDate), contractEndDate(contractEndDate), club(club) {} // Initialize club

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getNationality() const { return nationality; }
    string getPosition() const { return position; }
    char getStatus() const { return status; }
    int getGoals() const { return goals; }
    int getAssists() const { return assists; }
    int getMatches() const { return matches; }
    int getTacklesWon() const { return tacklesWon; }
    int getKeyPasses() const { return keyPasses; }
    int getInjuries() const { return injuries; }
    string getContractStartDate() const { return contractStartDate; }
    string getContractEndDate() const { return contractEndDate; }
    string getClub() const { return club; } // New getter for club

    // Setters
    void setName(const string &newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setNationality(const string &newNationality) { nationality = newNationality; }
    void setPosition(const string &newPosition) { position = newPosition; }
    void setStatus(char newStatus) { status = newStatus; }
    void setGoals(int newGoals) { goals = newGoals; }
    void setAssists(int newAssists) { assists = newAssists; }
    void setMatches(int newMatches) { matches = newMatches; }
    void setTacklesWon(int newTacklesWon) { tacklesWon = newTacklesWon; }
    void setKeyPasses(int newKeyPasses) { keyPasses = newKeyPasses; }
    void setInjuries(int newInjuries) { injuries = newInjuries; }
    void setContractStartDate(const string &newContractStartDate) { contractStartDate = newContractStartDate; }
    void setContractEndDate(const string &newContractEndDate) { contractEndDate = newContractEndDate; }
    void setClub(const string &newClub) { club = newClub; } // New setter for club

    // Display player info in a tabular format
    void display() const {
        cout << "ID: " << id << "\n"
             << "Name: " << name << "\n"
             << "Age: " << age << "\n"
             << "Nationality: " << nationality << "\n"
             << "Position: " << position << "\n"
             << "Status: " << status << "\n"
             << "Goals Scored: " << goals << "\n"
             << "Assists: " << assists << "\n"
             << "Matches: " << matches << "\n"
             << "Tackles Won: " << tacklesWon << "\n"
             << "Key Passes: " << keyPasses << "\n"
             << "Injuries: " << injuries << "\n"
             << "Contract Start Date: " << contractStartDate << "\n"
             << "Contract End Date: " << contractEndDate << "\n"
             << "Club: " << club << "\n"; // Display club
    }

// Calculate player rating using a regression model
double calculateRating() const {
    double rating = (goals * 0.4 + assists * 0.3 + matches * 0.1 + tacklesWon * 0.1 + keyPasses * 0.1);
    rating -= (injuries * 0.05 + age * 0.02);
    return max(0.0, min(rating, 100.0)); // Ensure rating is between 0 and 100
}

// Calculate transfer fee based on player rating and statistics using AI
double calculateTransferFee() const {
    double rating = calculateRating();
    double transferFee = rating * 1200000 + (goals + assists + matches + tacklesWon + keyPasses) * 60000 - (injuries * 250000 + age * 150000);
    if (transferFee < 0) transferFee = 0;
    return transferFee;
}
};

vector<Player> players;
vector<Player> squad; // List of players in the squad
vector<Player> holdState; // List of players in hold state

void savePlayersToFile() {
    ofstream file("Player.txt");
    if (!file) {
        cerr << "Error saving players to file.\n";
        return;
    }
    for (const auto &player : players) {
        file << player.getId() << "|" << player.getName() << "|" << player.getAge() << "|" << player.getNationality() << "|"
             << player.getPosition() << "|" << player.getStatus() << "|" << player.getGoals() << "|"
             << player.getAssists() << "|" << player.getMatches() << "|" << player.getTacklesWon() << "|"
             << player.getKeyPasses() << "|" << player.getInjuries() << "|" << player.getContractStartDate()
             << "|" << player.getContractEndDate() << "|" << player.getClub() << "\n"; // Save club
    }
    file.close();
}

void loadPlayersFromFile() {
    ifstream file("Player.txt");
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

        if (data.size() == 15) { // Adjusted for the new club parameter
            Player player(stoi(data[0]), data[1], stoi(data[2]), data[3], data[4], data[5][0],
                          stoi(data[6]), stoi(data[7]), stoi(data[8]), stoi(data[9]), stoi(data[10]), stoi(data[11]), data[12], data[13], data[14]);
            players.push_back(player);
        }
    }
    file.close();
}

void saveAdminPasswordToFile(const string& password) {
    ofstream file("adminPassword.txt");
    if (!file) {
        cerr << "Error saving admin password to file.\n";
        return;
    }
    file << password;
    file.close();
}

string loadAdminPasswordFromFile() {
    ifstream file("adminPassword.txt");
    if (!file) {
        saveAdminPasswordToFile("admin123");
        return "admin123"; // Return the initial password if the file did not exist
    }

    string password;
    getline(file, password);
    file.close();
    return password;
}

class Club {
public:
    struct Client {
        int id;
        string name;
        string password;
        string agentName;
        string email;
        string phoneNo;
        bool isApproved;
        long long balance;

        Client(int id = 0, string name = "", string password = "", string agentName = "", 
               string email = "", string phoneNo = "", bool isApproved = false, long long balance = 0)
            : id(id), name(name), password(password), agentName(agentName), 
              email(email), phoneNo(phoneNo), isApproved(isApproved), balance(balance) {}
    };

private:
    vector<Client> clients;

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
    Club() {
        clients = loadClubsFromFile();
    }

    vector<Client> loadClubsFromFile() {
        vector<Client> clients;
        ifstream file("Club.txt");
        if (!file) {
            cerr << "Error loading clubs from file.\n";
            return clients;
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

            clients.emplace_back(stoi(data[0]), data[1], data[2], data[3], data[4], data[5], stoi(data[6]), stoll(data[7]));
        }
        file.close();
        return clients;
    }

    void saveClubsToFile() {
        ofstream file("Club.txt");
        if (!file) {
            cerr << "Error saving clubs to file.\n";
            return;
        }
        for (const auto &client : clients) {
            file << client.id << "|" << client.name << "|" << client.password << "|"
                 << client.agentName << "|" << client.email << "|" << client.phoneNo << "|"
                 << client.isApproved << "|" << client.balance << "\n";
        }
        file.close();
    }

vector<Player> loadRosterFromFile(const string& clubName) {
    vector<Player> roster;
    ifstream file(clubName + "_Roster.txt");
    if (!file) {
//        cerr << "Error loading roster from file.\n";
        return roster;
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

        if (data.size() == 15) { // Adjusted for the new club parameter
            Player player(stoi(data[0]), data[1], stoi(data[2]), data[3], data[4], data[5][0],
                          stoi(data[6]), stoi(data[7]), stoi(data[8]), stoi(data[9]), stoi(data[10]), stoi(data[11]), data[12], data[13], data[14]);
            roster.push_back(player);
        }
    }
    file.close();
    return roster;
}

void saveRosterToFile(const string& clubName, const vector<Player>& roster) {
    ofstream file(clubName + "_Roster.txt");
    if (!file) {
//        cerr << "Error saving roster to file.\n";
        return;
    }
    for (const auto &player : roster) {
        file << player.getId() << "|" << player.getName() << "|" << player.getAge() << "|" << player.getNationality() << "|"
             << player.getPosition() << "|" << player.getStatus() << "|" << player.getGoals() << "|"
             << player.getAssists() << "|" << player.getMatches() << "|" << player.getTacklesWon() << "|"
             << player.getKeyPasses() << "|" << player.getInjuries() << "|" << player.getContractStartDate() << "|"
             << player.getContractEndDate() << "|" << player.getClub() << "\n";
    }
    file.close();
}

    Client* getClientById(int id) {
        for (auto &client : clients) {
            if (client.id == id) {
                return &client;
            }
        }
        return nullptr;
    }

    void registerClient() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Client Registration\n====================\n";
        setColor(RESET);

        if (clients.size() >= 100) {
            setColor(RED);
            cout << "Client registration limit reached!\n";
            setColor(RESET);
            Sleep(1000);
            return;
        }

        string name, password, agentName;
        setColor(YELLOW);
        cout << "Enter Name: ";
        setColor(RESET);
        fflush(stdin);
        getline(cin, name);
        while (true) {
            setColor(YELLOW);
            cout << "Enter Password: ";
            setColor(RESET);
            fflush(stdin);
            getline(cin, password);

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
        fflush(stdin);
        getline(cin, agentName);

        int id = clients.size() + 1;
        clients.emplace_back(id, name, password, agentName, "", "", false, 0);
        saveClubsToFile();

        setColor(GREEN);
        cout << "Registration successful! Your ID is: " << id << " (Needs approval by admin)\n";
        setColor(RESET);
        Sleep(1000);
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
        fflush(stdin);
        cin >> id;
        setColor(YELLOW);
        cout << "Enter Password: ";
        setColor(RESET);
        fflush(stdin);
        char ch;
        string pass = "";
        while ((ch = _getch()) != 13) {
            if (ch == 8 && !pass.empty()) {
                pass.pop_back();
                cout << "\b \b";
            } else if (ch != 8) {
                pass.push_back(ch);
                cout << '*';
            }
        }
        password = pass;
        cout << endl;

        for (auto &client : clients) {
            if (client.id == id && client.password == password) {
                if (!client.isApproved) {
                    setColor(RED);
                    cout << "Your account is not approved yet. Please contact the admin.\n";
                    setColor(RESET);
                    Sleep(1000);
                    return;
                }
                setColor(GREEN);
                cout << "Login successful!\n";
                setColor(RESET);
                Sleep(1000);
                clubLoginMenu(&client);
                return;
            }
        }

        setColor(RED);
        cout << "Invalid ID or Password!\n";
        setColor(RESET);
        Sleep(1000);
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
        fflush(stdin);
        cin >> id;

        for (auto &client : clients) {
            if (client.id == id) {
                setColor(YELLOW);
                cout << "Enter Current Password: ";
                setColor(RESET);
                fflush(stdin);
                cin >> currentPassword;

                if (client.password == currentPassword) {
                    while (true) {
                        setColor(YELLOW);
                        cout << "Enter New Password: ";
                        setColor(RESET);
                        fflush(stdin);
                        cin >> newPassword;

                        if (!isStrongPassword(newPassword)) {
                            setColor(RED);
                            cout << "Password must be at least 8 characters long and include an uppercase letter, a lowercase letter, a digit, and a special character.\n";
                            setColor(RESET);
                            continue;
                        }
                        break;
                    }
                    client.password = newPassword;
                    saveClubsToFile();
                    setColor(GREEN);
                    cout << "Password changed successfully!\n";
                    setColor(RESET);
                    Sleep(1000);
                    return;
                } else {
                    setColor(RED);
                    cout << "Incorrect Current Password!\n";
                    setColor(RESET);
                    Sleep(1000);
                    return;
                }
            }
        }

        setColor(RED);
        cout << "Client ID not found!\n";
        setColor(RESET);
        Sleep(1000);
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
        fflush(stdin);
        cin >> id;

        for (auto &client : clients) {
            if (client.id == id) {
                setColor(GREEN);
                cout << "Your password is: " << client.password << endl;
                setColor(RESET);
                Sleep(3000);
                return;
            }
        }

        setColor(RED);
        cout << "Client ID not found!\n";
        setColor(RESET);
        Sleep(1000);
    }

    void checkLoginStatus() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Check Login Status\n====================\n";
        setColor(RESET);

        int id;
        string password;
        setColor(YELLOW);
        cout << "Enter your ID: ";
        setColor(RESET);
        fflush(stdin);
        cin >> id;
        setColor(YELLOW);
        cout << "Enter your Password: ";
        setColor(RESET);
        fflush(stdin);
        char ch;
        string pass = "";
        while ((ch = _getch()) != 13) {
            if (ch == 8 && !pass.empty()) {
                pass.pop_back();
                cout << "\b \b";
            } else if (ch != 8) {
                pass.push_back(ch);
                cout << '*';
            }
        }
        password = pass;
        cout << endl;

        for (const auto &client : clients) {
            if (client.id == id && client.password == password) {
                if (client.isApproved) {
                    setColor(GREEN);
                    cout << "Login status: Approved\n";
                    setColor(RESET);
                } else {
                    setColor(RED);
                    cout << "Login status: Not Approved\n";
                    setColor(RESET);
                }
                Sleep(1000);
                return;
            }
        }

        setColor(RED);
        cout << "Client ID or Password not found!\n";
        setColor(RESET);
        Sleep(1000);
    }

    void approveClient() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Approve Club\n====================\n";
        setColor(RESET);

        bool foundPending = false;
        setColor(GREEN);
        cout << "Pending Club Approvals:\n";
        for (const auto &client : clients) {
            if (!client.isApproved) {
                foundPending = true;
                cout << "ID: " << client.id << ", Name: " << client.name << ", Agent Name: " << client.agentName << "\n";
            }
        }
        if (!foundPending) {
            setColor(RED);
            cout << "No clients or clubs found!\n";
            setColor(RESET);
            Sleep(1000);
            return;
        }
        setColor(RESET);

        int id;
        setColor(YELLOW);
        cout << "Enter Client ID to Approve: ";
        setColor(RESET);
        fflush(stdin);
        cin >> id;

        for (auto &client : clients) {
            if (client.id == id && !client.isApproved) {
                client.isApproved = true;
                saveClubsToFile();
                setColor(GREEN);
                cout << "Client ID " << id << " approved successfully!\n";
                setColor(RESET);
                Sleep(1000);
                return;
            }
        }

        setColor(RED);
        cout << "Client ID not found or already approved!\n";
        setColor(RESET);
        Sleep(1000);
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
    fflush(stdin);
    cin >> id;

    for (auto &client : clients) {
        if (client.id == id) {
            while (true) {
                clearScreen();
                setColor(CYAN);
                cout << "TransferMaster - Edit Club Details\n====================\n";
                setColor(GREEN);
                cout << "1) Agent Name\n";
                cout << "2) Email\n";
                cout << "3) Phone No\n";
                cout << "4) Back to Club Management\n";
                setColor(RESET);
                setColor(YELLOW);
                cout << "Enter your choice: ";
                setColor(RESET);

                int choice;
                fflush(stdin);
                cin >> choice;
                displayLoading();
                clearScreen();

                switch (choice) {
                    case 1: {
                        setColor(YELLOW);
                        cout << "Enter New Agent Name (Current: " << client.agentName << "): ";
                        setColor(RESET);
                        fflush(stdin);
                        string newAgentName;
                        getline(cin, newAgentName);
                        client.agentName = newAgentName;
                        break;
                    }
                    case 2: {
                        setColor(YELLOW);
                        cout << "Enter New Email (Current: " << client.email << "): ";
                        setColor(RESET);
                        fflush(stdin);
                        string newEmail;
                        getline(cin, newEmail);
                        if (newEmail.size() >= 10 && newEmail.substr(newEmail.size() - 10) == "@gmail.com") {
                            client.email = newEmail;
                        } else {
                            setColor(RED);
                            cout << "Invalid email format! Email should end with '@gmail.com'\n";
                            setColor(RESET);
                            Sleep(1000);
                        }
                        break;
                    }
                    case 3: {
                        setColor(YELLOW);
                        cout << "Enter New Phone No (Current: " << client.phoneNo << "): ";
                        setColor(RESET);
                        fflush(stdin);
                        string newPhoneNo;
                        getline(cin, newPhoneNo);
                        if (newPhoneNo.size() == 10 && all_of(newPhoneNo.begin(), newPhoneNo.end(), ::isdigit)) {
                            client.phoneNo = newPhoneNo;
                        } else {
                            setColor(RED);
                            cout << "Invalid phone number! It should be 10 digits.\n";
                            setColor(RESET);
                            Sleep(1000);
                        }
                        break;
                    }
                    case 4:
                        saveClubsToFile();
                        return;
                    default:
                        setColor(RED);
                        cout << "Invalid choice! Try again.\n";
                        setColor(RESET);
                        Sleep(1000);
                }
            }
        }
    }

    setColor(RED);
    cout << "Client ID not found!\n";
    setColor(RESET);
    Sleep(1000);
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
        fflush(stdin);
        cin >> id;
        displayLoading();
        clearScreen();

        auto it = remove_if(clients.begin(), clients.end(), [id](const Client &c) { return c.id == id; });
        if (it != clients.end()) {
            clients.erase(it, clients.end());
            saveClubsToFile();
            setColor(GREEN);
            cout << "Client deleted successfully!\n";
            setColor(RESET);
        } else {
            setColor(RED);
            cout << "Client ID not found!\n";
            setColor(RESET);
        }
        Sleep(1000);
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
        fflush(stdin);
        cin >> id;
        displayLoading();
        clearScreen();

        for (const auto &client : clients) {
            if (client.id == id) {
                setColor(GREEN);
                cout << "Client Found!\n";
                cout << "ID: " << client.id << "\n";
                cout << "Name: " << client.name << "\n";
                cout << "Agent Name: " << client.agentName << "\n";
                cout << "Email: " << client.email << "\n";
                cout << "Phone No: " << client.phoneNo << "\n";
                cout << "Balance: $" << fixed << setprecision(2) << client.balance << "\n";
                setColor(RESET);
                cout << "Press any key to return to Club Management...." << endl;
                _getch();
                displayLoading();
                return;
            }
        }

        setColor(RED);
        cout << "Client ID not found!\n";
        setColor(RESET);
        Sleep(1000);
    }

    void updateBalance() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Update Balance\n====================\n";
        setColor(RESET);

        int id;
        long long newBalance;
        setColor(YELLOW);
        cout << "Enter Client ID to Update Balance: ";
        setColor(RESET);
        fflush(stdin);
        cin >> id;
        displayLoading();
        clearScreen();

        for (auto &client : clients) {
            if (client.id == id) {
                setColor(YELLOW);
                cout << "Enter New Balance: ";
                setColor(RESET);
                fflush(stdin);
                cin >> newBalance;
                client.balance = newBalance;
                saveClubsToFile();
                setColor(GREEN);
                cout << "Balance updated successfully!\n";
                setColor(RESET);
                Sleep(1000);
                return;
            }
        }

        setColor(RED);
        cout << "Client ID not found!\n";
        setColor(RESET);
        Sleep(1000);
    }

    void viewAllClients() {
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - All Clubs\n====================\n";
        setColor(RESET);

        if (clients.empty()) {
            setColor(RED);
            cout << "No clients found!\n";
            setColor(RESET);
            Sleep(1000);
            return;
        }

        setColor(GREEN);
        for (const auto &client : clients) {
            cout << "ID: " << client.id << "\n"
                 << "Name: " << client.name << "\n"
                 << "Agent Name: " << client.agentName << "\n"
                 << "Email: " << client.email << "\n"
                 << "Phone No: " << client.phoneNo << "\n"
                 << "Balance: $" << fixed << setprecision(2) << client.balance << "\n"
                 << "----------------------------------------\n";
        }
        setColor(RESET);

        cout << "\nPress any key to return to Club Management...\n";
        _getch();
    }

void viewPlayerRatingsAndFees() {
    clearScreen();
    setColor(CYAN);
    cout << "TransferMaster - Player Ratings and Transfer Fees\n====================\n";
    setColor(RESET);

    if (players.empty()) {
        setColor(RED);
        cout << "No players found!\n";
        setColor(RESET);
        Sleep(1000);
        return;
    }

    setColor(GREEN);
    cout << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Rating" << setw(20) << "Transfer Fee\n";
    cout << "------------------------------------------------------------\n";

    for (const auto &player : players) {
        if (player.getStatus() == 'A' && player.getClub().empty()) {
            double rating = player.calculateRating();
            double transferFee = player.calculateTransferFee();
            if (rating >= 50) { // Ensure player meets the minimum rating criteria
                cout << setw(5) << player.getId() << setw(20) << player.getName() << setw(10) << fixed << setprecision(2) << rating << setw(20) << fixed << setprecision(2) << transferFee << "\n";
            }
        }
    }
    setColor(RESET);

    cout << "\nPress any key to return...\n";
    _getch();
}

void initiateTransfer(Client* client) {
    clearScreen();
    setColor(CYAN);
    cout << "TransferMaster - Initiate Transfer\n====================\n";
    setColor(GREEN);
    cout << "Agent name: " << client->agentName << "\tBalance: $" << fixed << setprecision(2) << client->balance << "\n";
    setColor(RESET);

    if (players.empty()) {
        setColor(RED);
        cout << "No players found!\n";
        setColor(RESET);
        Sleep(1000);
        return;
    }

    setColor(GREEN);
    cout << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Rating" << setw(20) << "Transfer Fee\n";
    cout << "------------------------------------------------------------\n";

    for (const auto &player : players) {
        if (player.getStatus() == 'A' && player.getAge() >= 16 && player.getClub().empty()) {
            double rating = player.calculateRating();
            double transferFee = player.calculateTransferFee();
            if (rating >= 50) { // Ensure player meets the minimum rating criteria
                cout << setw(5) << player.getId() << setw(20) << player.getName() << setw(10) << fixed << setprecision(2) << rating << setw(20) << fixed << setprecision(2) << transferFee << "\n";
            }
        }
    }
    setColor(RESET);

    cout << "\nEnter Player ID to initiate transfer: ";
    int playerId;
    fflush(stdin);
    cin >> playerId;

    for (auto &player : players) {
        if (player.getId() == playerId && player.getStatus() == 'A' && player.getAge() >= 16 && player.getClub().empty()) {
            if (client->balance < player.calculateTransferFee()) {
                setColor(RED);
                cout << "Insufficient balance for transfer!\n";
                setColor(RESET);
                Sleep(1000);
                return;
            }

            time_t now = time(0);
            tm *ltm = localtime(&now);
            string startDate = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);
            ltm->tm_year += 3;
            string endDate = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);

            player.setContractStartDate(startDate);
            player.setContractEndDate(endDate);
            player.setClub(client->name); // Assign player to the club
            player.setStatus('A');

            client->balance -= player.calculateTransferFee();
            saveClubsToFile();

            vector<Player> clubRoster = loadRosterFromFile(client->name);
            clubRoster.push_back(player); // Add player to the club's roster
            saveRosterToFile(client->name, clubRoster); // Save to roster file
            savePlayersToFile(); // Save player data to Player.txt

            setColor(GREEN);
            cout << "Transfer initiated successfully! Contract Period: " << startDate << " to " << endDate << "\n";
            setColor(RESET);
            Sleep(1000);
            return;
        }
    }

    setColor(RED);
    cout << "Player ID not found or player is not eligible for transfer!\n";
    setColor(RESET);
    Sleep(1000);
}

void manageRosters(Client* client) {
    clearScreen();
    setColor(CYAN);
    cout << "TransferMaster - Squad Overview\n====================\n";
    setColor(GREEN);
    cout << "1) View Squad\n";
    cout << "2) Back to Client Menu\n";
    setColor(RESET);
    setColor(YELLOW);
    cout << "Enter your choice: ";
    setColor(RESET);

    int choice;
    cin >> choice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (!continuePrompt()) {
            return;
        }
    } else {
        displayLoading();
        clearScreen();

        switch (choice) {
            case 1:
                viewSquad(client); // Pass client
                break;
            case 2:
                return;
            default:
                setColor(RED);
                cout << "Invalid choice! Try again.\n";
                setColor(RESET);
                Sleep(1000);
        }
    }
}

void viewSquad(Client* client) {
    clearScreen();
    setColor(CYAN);
    cout << "TransferMaster - Squad\n====================\n";
    setColor(RESET);

    squad = loadRosterFromFile(client->name); // Load squad from the roster file

    if (squad.empty()) {
        setColor(RED);
        cout << "No players in the squad!\n";
        setColor(RESET);
        Sleep(1000);
        return;
    }

    setColor(GREEN);
    for (const auto &player : squad) {
        cout << "ID: " << player.getId() << "\n"
             << "Name: " << player.getName() << "\n"
             << "Age: " << player.getAge() << "\n"
             << "Nationality: " << player.getNationality() << "\n"
             << "Position: " << player.getPosition() << "\n"
             << "Status: " << player.getStatus() << "\n"
             << "Goals Scored: " << player.getGoals() << "\n"
             << "Assists: " << player.getAssists() << "\n"
             << "Matches: " << player.getMatches() << "\n"
             << "Tackles Won: " << player.getTacklesWon() << "\n"
             << "Key Passes: " << player.getKeyPasses() << "\n"
             << "Injuries: " << player.getInjuries() << "\n"
             << "Contract Start Date: " << player.getContractStartDate() << "\n"
             << "Contract End Date: " << player.getContractEndDate() << "\n"
             << "----------------------------------------\n";
    }
    setColor(RESET);

    cout << "\nPress any key to return...\n";
    _getch();
}

void viewClubInformation(Client* client) {
    clearScreen();
    setColor(CYAN);
    cout << "TransferMaster - Club Information\n====================\n";
    setColor(GREEN);
    cout << "ID: " << client->id << "\n";
    cout << "Name: " << client->name << "\n";
    cout << "Agent Name: " << client->agentName << "\n";
    cout << "Email: " << client->email << "\n";
    cout << "Phone No: " << client->phoneNo << "\n";
    cout << "Balance: $" << fixed << setprecision(2) << client->balance << "\n";
    setColor(RESET);
    cout << "\nPress any key to return...\n";
    _getch();
}

void clubLoginMenu(Client* client) {
    int choice;
    do {
        displayLoading();
        clearScreen();
        setColor(CYAN);
        cout << "TransferMaster - Login Menu\n====================\n";
        setColor(GREEN);
        cout << "Agent name: " << client->agentName << "\tBalance: $" << fixed << setprecision(2) << client->balance << "\n";
        cout << "1) Update Club Information\n";
        cout << "2) Squad Overview\n";
        cout << "3) Initiate Transfer\n";
        cout << "4) View Player's Rating and Transfer Fee\n";
        cout << "5) View Transfer Guidelines\n";
        cout << "6) View Game Rules\n";
        cout << "7) View Club Information\n";
        cout << "8) Back to Main Menu\n";
        setColor(RESET);
        setColor(YELLOW);
        cout << "Enter your choice: ";
        setColor(RESET);

        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!continuePrompt()) {
                return;
            }
            continue;
        }
        displayLoading();
        clearScreen();

        switch (choice) {
            case 1:
                editClient();
                break;
            case 2:
                manageRosters(client); // Pass client
                break;
            case 3:
                initiateTransfer(client);
                break;
            case 4:
                viewPlayerRatingsAndFees();
                break;
            case 5:
                transferGuidelines();
                break;
            case 6:
                gameRules();
                break;
            case 7: // View Club Information
                viewClubInformation(client);
                break;
            case 8:
                cout << "Returning to Main Menu...\n";
                Sleep(1000);
                break;
            default:
                setColor(RED);
                cout << "Invalid choice! Please try again.\n";
                setColor(RESET);
                Sleep(1000);
        }
    } while (choice != 8);
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
        fflush(stdin);
        cin >> currentPassword;

        if (currentPassword != adminPassword) {
            setColor(RED);
            cout << "Incorrect current password! Returning to main menu.\n";
            setColor(RESET);
            Sleep(1000);
            return;
        }

        string newPassword, confirmPassword;

        while (true) {
            setColor(YELLOW);
            cout << "Enter new admin password: ";
            setColor(RESET);
            fflush(stdin);
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
            fflush(stdin);
            cin >> confirmPassword;

            if (newPassword == confirmPassword) {
                adminPassword = newPassword;
                saveAdminPasswordToFile(adminPassword);
                setColor(GREEN);
                cout << "Password changed successfully! Returning to main menu.\n";
                setColor(RESET);
                Sleep(1000);
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
            Sleep(1000);
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
        fflush(stdin);
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
                    cout << "3) Nationality\n";
                    cout << "4) Back to Player Management\n";
                    setColor(RESET);
                    setColor(YELLOW);
                    cout << "Enter your choice: ";
                    setColor(RESET);

                    int choice;
                    cin >> choice;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (!continuePrompt()) {
                            return;
                        }
                        continue;
                    }
                    displayLoading();
                    clearScreen();

                    switch (choice) {
                        case 1: {
                            setColor(YELLOW);
                            cout << "Enter New Name (Current: " << player.getName() << "): ";
                            setColor(RESET);
                            fflush(stdin);
                            string newName;
                            getline(cin, newName);
                            player.setName(newName);
                            break;
                        }
                        case 2: {
                            setColor(YELLOW);
                            cout << "Enter New Age (Current: " << player.getAge() << "): ";
                            setColor(RESET);
                            fflush(stdin);
                            int newAge;
                            cin >> newAge;
                            if (newAge < 16) {
                                setColor(RED);
                                cout << "Player must be 16 years or above.\n";
                                setColor(RESET);
                                Sleep(1000);
                            } else {
                                player.setAge(newAge);
                            }
                            break;
                        }
                        case 3: {
                            setColor(YELLOW);
                            cout << "Enter New Nationality (Current: " << player.getNationality() << "): ";
                            setColor(RESET);
                            fflush(stdin);
                            string newNationality;
                            getline(cin, newNationality);
                            player.setNationality(newNationality);
                            break;
                        }
                        case 4:
                            savePlayersToFile();
                            return;
                        default:
                            setColor(RED);
                            cout << "Invalid choice! Try again.\n";
                            setColor(RESET);
                            Sleep(1000);
                    }
                }
            }
        }

        setColor(RED);
        cout << "Player ID not found!\n";
        setColor(RESET);
        Sleep(1000);
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
        fflush(stdin);
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
        Sleep(1000);
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
        fflush(stdin);
        cin >> id;
        displayLoading();
        clearScreen();

        for (const auto &player : players) {
            if (player.getId() == id) {
                setColor(GREEN);
                cout << "Player Found!\n";
                player.display();
                setColor(RESET);
                cout << "Press any key to return to Player Management...." << endl;
                _getch();
                displayLoading();
                return;
            }
        }

        setColor(RED);
        cout << "Player ID not found!\n";
        setColor(RESET);
        Sleep(1000);
    }

void playerManagement(Club* club, Club::Client* client) {
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
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!continuePrompt()) {
                return;
            }
            continue;
        }
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
                releasePlayer(club, client);
                break;
            case 8:
                return;
            default:
                setColor(RED);
                cout << "Invalid choice! Try again.\n";
                setColor(RESET);
                Sleep(1000);
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
        fflush(stdin);
        string name;
        getline(cin, name);
        newPlayer.setName(name);

        setColor(YELLOW);
        cout << "Enter Player Age: ";
        setColor(RESET);
        fflush(stdin);
        int age;
        cin >> age;
        if (age < 16) {
            setColor(RED);
            cout << "Player must be 16 years or above.\n";
            setColor(RESET);
            Sleep(1000);
            return;
        }
        newPlayer.setAge(age);

        setColor(YELLOW);
        cout << "Enter Player Nationality: ";
        setColor(RESET);
        fflush(stdin);
        string nationality;
        cin >> nationality;
        newPlayer.setNationality(nationality);

        newPlayer.setStatus('A');  // Default status is Active

        players.push_back(newPlayer);
        savePlayersToFile();
        setColor(GREEN);
        cout << "Player added successfully! Player ID: " << newPlayer.getId() << "\n";
        setColor(RESET);
        Sleep(1000);
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
    fflush(stdin);
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
                cout << "6) Position\n";
                cout << "7) Injuries\n";
                cout << "8) Status\n";
                cout << "9) Back to Player Management\n";
                setColor(RESET);
                setColor(YELLOW);
                cout << "Enter your choice: ";
                setColor(RESET);

                int choice;
                cin >> choice;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (!continuePrompt()) {
                        return;
                    }
                    continue;
                }
                displayLoading();
                clearScreen();

                switch (choice) {
                    case 1: {
                        setColor(YELLOW);
                        cout << "Enter Goals Scored: ";
                        setColor(RESET);
                        int goals;
                        fflush(stdin);
                        cin >> goals;
                        player.setGoals(goals);
                        break;
                    }
                    case 2: {
                        setColor(YELLOW);
                        cout << "Enter Assists: ";
                        setColor(RESET);
                        int assists;
                        fflush(stdin);
                        cin >> assists;
                        player.setAssists(assists);
                        break;
                    }
                    case 3: {
                        setColor(YELLOW);
                        cout << "Enter Matches Played: ";
                        setColor(RESET);
                        int matches;
                        fflush(stdin);
                        cin >> matches;
                        player.setMatches(matches);
                        break;
                    }
                    case 4: {
                        setColor(YELLOW);
                        cout << "Enter Tackles Won: ";
                        setColor(RESET);
                        int tacklesWon;
                        fflush(stdin);
                        cin >> tacklesWon;
                        player.setTacklesWon(tacklesWon);
                        break;
                    }
                    case 5: {
                        setColor(YELLOW);
                        cout << "Enter Key Passes: ";
                        setColor(RESET);
                        int keyPasses;
                        fflush(stdin);
                        cin >> keyPasses;
                        player.setKeyPasses(keyPasses);
                        break;
                    }
                    case 6: {
                        setColor(YELLOW);
                        cout << "Enter Position (Goalkeeper, Defender, Midfielder, Forward): ";
                        setColor(RESET);
                        fflush(stdin);
                        string newPosition;
                        getline(cin, newPosition);
                        vector<string> validPositions = {"Goalkeeper", "Defender", "Midfielder", "Forward"};
                        if (find(validPositions.begin(), validPositions.end(), newPosition) != validPositions.end()) {
                            player.setPosition(newPosition);
                        } else {
                            setColor(RED);
                            cout << "Invalid position! Valid positions are Goalkeeper, Defender, Midfielder, Forward.\n";
                            setColor(RESET);
                            Sleep(1000);
                        }
                        break;
                    }
                    case 7: {
                        setColor(YELLOW);
                        cout << "Enter Number of Injuries: ";
                        setColor(RESET);
                        int injuries;
                        fflush(stdin);
                        cin >> injuries;
                        player.setInjuries(injuries);
                        break;
                    }
                    case 8: {
                        setColor(YELLOW);
                        cout << "Enter Status (A=Active, I=Inactive, T=Terminated): ";
                        setColor(RESET);
                        char newStatus;
                        fflush(stdin);
                        cin >> newStatus;
                        if (newStatus == 'A' || newStatus == 'I' || newStatus == 'T') {
                            player.setStatus(newStatus);
                        } else {
                            setColor(RED);
                            cout << "Invalid status! Valid statuses are A=Active, I=Inactive, T=Terminated.\n";
                            setColor(RESET);
                            Sleep(1000);
                        }
                        break;
                    }
                    case 9:
                        savePlayersToFile();
                        return;
                    default:
                        setColor(RED);
                        cout << "Invalid choice! Try again.\n";
                        setColor(RESET);
                        Sleep(1000);
                }
            }
        }
    }

    setColor(RED);
    cout << "Player ID not found!\n";
    setColor(RESET);
    Sleep(1000);
}

void releasePlayer(Club* club, Club::Client* client) {
    clearScreen();
    setColor(CYAN);
    cout << "TransferMaster - Release Player\n====================\n";
    setColor(RESET);

    int id;
    setColor(YELLOW);
    cout << "Enter Player ID to Release: ";
    setColor(RESET);
    fflush(stdin);
    cin >> id;
    displayLoading();
    clearScreen();

    auto it = find_if(players.begin(), players.end(), [id](const Player &p) { return p.getId() == id; });
    if (it != players.end()) {
        string clubName = it->getClub(); // Get the player's club name before clearing it
        it->setClub(""); // Clear the player's club in Player.txt
        it->setContractStartDate(""); // Clear contract start date
        it->setContractEndDate(""); // Clear contract end date
        savePlayersToFile();

        squad = club->loadRosterFromFile(clubName); // Use the club name to load the correct roster
        squad.erase(remove_if(squad.begin(), squad.end(), [id](const Player &p) { return p.getId() == id; }), squad.end());
        club->saveRosterToFile(clubName, squad); // Save the updated roster to the correct file

        setColor(GREEN);
        cout << "Player released successfully!\n";
        setColor(RESET);
    } else {
        setColor(RED);
        cout << "Player ID not found!\n";
        setColor(RESET);
    }
    Sleep(1000);
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
            Sleep(1000);
            return;
        }

        setColor(GREEN);
        for (const auto &player : players) {
            player.display();
            cout << "----------------------------------------\n";
        }
        setColor(RESET);

        cout << "\nPress any key to return to Player Management...\n";
        _getch();
    }

    void clubManagement(Club &club) {
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
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (!continuePrompt()) {
                    return;
                }
                continue;
            }
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
                    Sleep(1000);
            }
        }
    }
};

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
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!continuePrompt()) {
                return;
            }
            continue;
        }
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
            Sleep(1000);
            break;
        default:
            setColor(RED);
            cout << "Invalid choice! Please try again.\n";
            setColor(RESET);
            Sleep(1000);
        }
    } while (choice != 6);
}

void displayPrivacyPolicy() {
    clearScreen();
    setColor(GREEN);
    printf("\n========================= PRIVACY POLICY =========================\n");
    setColor(RESET);
    setColor(CYAN);
    printf("At TransferMaster, we take your privacy seriously. \n");
    printf("We are committed to securely handling your data and ensuring confidentiality.\n\n");
    printf("Your information is protected, and we continuously monitor our security measures\n");
    printf("to safeguard against unauthorized access, disclosure, or misuse.\n");
    printf("====================================================================\n");
    setColor(RESET);
}

// Display about the program and how it facilitates transfer management
void displayAboutUs() {
    clearScreen();
    setColor(GREEN);
    printf("\n=========================== ABOUT US ============================\n");
    setColor(RESET);
    setColor(CYAN);
    printf("Welcome to TransferMaster, your go-to football transfer management system.\n\n");
    
    printf("Our Mission:\n");
    printf("---------------------------------------------------------------------\n");
    printf("Our mission is to revolutionize football transfer management by providing \n");
    printf("an advanced platform that leverages AI and regression models to make \n");
    printf("data-driven decisions, enabling clubs to effectively manage player transfers, \n");
    printf("evaluate player ratings, and set accurate transfer fees.\n\n");
    
    printf("Features:\n");
    printf("---------------------------------------------------------------------\n");
    printf("1. AI-Driven Player Valuation: Use AI models to analyze player performance \n");
    printf("   and predict future market values, ensuring precise transfer fee estimations.\n");
    printf("2. Comprehensive Transfer Management: Efficiently handle player acquisitions,\n");
    printf("   sales, and contracts with real-time updates.\n");
    printf("3. Detailed Player Statistics: Access player stats to make informed decisions on \n");
    printf("   transfers, including performance analysis and injury history.\n");
    printf("4. Transfer Fee Prediction: Use regression models to predict market trends and \n");
    printf("   transfer fees based on player ratings and historical data.\n");
    printf("5. Streamlined User Interface: A clean, user-friendly interface that simplifies \n");
    printf("   the transfer process for administrators.\n\n");
    
    printf("AI and Regression Models:\n");
    printf("---------------------------------------------------------------------\n");
    printf("TransferMaster integrates cutting-edge AI algorithms to evaluate player \n");
    printf("performances and predict market values with high accuracy. Our advanced \n");
    printf("regression models analyze historical data, player stats, and current market \n");
    printf("trends to set realistic transfer fees, enabling clubs to make well-informed, \n");
    printf("strategic decisions.\n\n");
    
    printf("Our Team:\n");
    printf("---------------------------------------------------------------------\n");
    printf("TransferMaster is developed by a team of passionate professionals:\n");
    printf("- Prajjwal Maharjan (Lead Developer)\n");
    printf("- Rabin Pulami Magar\n");
    printf("- Durga Budha\n");
    printf("Prajjwal Maharjan, our lead developer, brings a wealth of expertise in AI, \n");
    printf("data analysis, and software development, ensuring TransferMaster is a cutting-\n");
    printf("edge solution for football transfer management.\n\n");
    
    printf("Thank you for choosing TransferMaster. We are committed to helping clubs \n");
    printf("make data-driven, intelligent decisions in the ever-evolving world of football transfers.\n");
    printf("=====================================================================\n");
    setColor(RESET);
}

int main() {
    Admin admin;
    Club club;
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
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!continuePrompt()) {
                return 0;
            }
            continue;
        }
        displayLoading();
        clearScreen();

        switch (choice) {
            case 1:
                if (admin.authenticate()) {
                    while (true) {
                        clearScreen();
                        setColor(CYAN);
                        cout << "TransferMaster - Admin Menu\n====================\n";
                        setColor(GREEN);
                        cout << "1) Player Management\n";
                        cout << "2) Club Management\n";
                        cout << "3) Change Admin Password\n";
                        cout << "4) View Game Rules\n";
                        cout << "5) View Transfer Guidelines\n";
                        cout << "6) Back to Main Menu\n";
                        setColor(RESET);
                        setColor(YELLOW);
                        cout << "Enter your choice: ";
                        setColor(RESET);

                        int adminChoice;
                        cin >> adminChoice;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            if (!continuePrompt()) {
                                return 0;
                            }
                            continue;
                        }
                        displayLoading();
                        clearScreen();

                        if (adminChoice == 1) {
                            Club::Client* client = club.getClientById(1); 
                            admin.playerManagement(&club, client); 
                        } else if (adminChoice == 2) {
                            admin.clubManagement(club);
                        } else if (adminChoice == 3) {
                            admin.changeAdminPassword();
                            break;
                        } else if (adminChoice == 4) {
                            gameRules();
                        } else if (adminChoice == 5) {
                            transferGuidelines();
                        } else if (adminChoice == 6) {
                            break;
                        } else {
                            setColor(RED);
                            cout << "Invalid choice! Try again.\n";
                            setColor(RESET);
                            Sleep(1000);
                        }
                    }
                }
                break;

            case 2:
                clientMenu(club);
                break;

            case 3:
                displayPrivacyPolicy();
                cout << "Press any key to continue....."<< endl;
                _getch();
                break;

            case 4:
                displayAboutUs();
                cout << "Press any key to continue....." << endl;
                _getch();
                break;

            case 5:
                displayLoading();
                setColor(RED);
                cout << "Thank you for using TransferMaster. Goodbye!\n";
                setColor(RESET);
                exit(0);

            default:
                setColor(RED);
                cout << "Invalid choice! Try again.\n";
                setColor(RESET);
                Sleep(1000);
        }
    }
    return 0;
}
