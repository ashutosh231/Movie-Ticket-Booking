/*
====================================================
 🎬 Movie Ticket Booking System 🎬
----------------------------------------------------
 📌 Project by: Ashutosh Kumar
 🎓 Course    : B.Tech CSE, Lovely Professional University
 🆔 Reg. No   : 12311842
====================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_SEATS = 25;

// Booking details
string names[MAX_SEATS];
int ages[MAX_SEATS];
string emails[MAX_SEATS];
bool booked[MAX_SEATS] = {false};
int seatPrices[MAX_SEATS];

// ---------------- UI DECORATION ----------------
void header(string title) {
    cout << "\n====================================================\n";
    cout << " 🎬  " << title << "  🎬\n";
    cout << "====================================================\n";
}

void projectCredits() {
    cout << "\n====================================================\n";
    cout << " 📌 Project by: Ashutosh Kumar\n";
    cout << " 🎓 B.Tech CSE, Lovely Professional University\n";
    cout << " 🆔 Reg. No: 12311842\n";
    cout << "====================================================\n";
}

void line() {
    cout << "----------------------------------------------------\n";
}

void pause() {
    cout << "\n🍿 Press ENTER to continue...";
    cin.ignore();
    cin.get();
}

// ---------------- SEAT PRICE STRUCTURE ----------------
void setSeatPrices() {
    for (int i = 0; i < MAX_SEATS; i++) {
        if (i < 5) seatPrices[i] = 300;       // Seats 1-5 (Premium)
        else if (i < 15) seatPrices[i] = 200; // Seats 6-15 (Standard)
        else seatPrices[i] = 150;             // Seats 16-25 (Economy)
    }
}

void showSeatPrices() {
    header("🎟️ Ticket Price Structure");
    cout << " 💎 Premium   (Seats 1-5)   : ₹300\n";
    cout << " ⭐ Standard  (Seats 6-15)  : ₹200\n";
    cout << " 🎫 Economy   (Seats 16-25) : ₹150\n";
    line();
}

// ---------------- SAVE & LOAD ----------------
void saveToFile() {
    ofstream file("booked_tickets.txt");
    if (!file) {
        cout << "❌ Error saving file.\n";
        return;
    }

    for (int i = 0; i < MAX_SEATS; i++) {
        if (booked[i]) {
            file << "Seat " << i + 1 
                 << ": " << names[i] 
                 << ", Age: " << ages[i]
                 << ", Email: " << emails[i]
                 << ", Price: " << seatPrices[i]
                 << "\n";
        }
    }

    file.close();
    cout << "💾 All bookings saved in 'booked_tickets.txt' 🎟️\n";
}

void loadFromFile() {
    ifstream file("booked_tickets.txt");
    if (!file) {
        cout << "⚠️ No previous bookings found. Starting fresh.\n";
        return;
    }

    for (int i = 0; i < MAX_SEATS; i++) {
        names[i] = "";
        ages[i] = 0;
        emails[i] = "";
        booked[i] = false;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("Seat") != string::npos) {
            int seatNo, age, price;
            string name, email;

            // Seat number
            size_t pos1 = line.find("Seat ") + 5;
            size_t pos2 = line.find(":");
            seatNo = stoi(line.substr(pos1, pos2 - pos1));

            // Name
            size_t posName = pos2 + 2;
            size_t posAge = line.find(", Age:");
            name = line.substr(posName, posAge - posName);

            // Age
            size_t posAgeVal = line.find("Age:") + 5;
            size_t posEmail = line.find(", Email:");
            age = stoi(line.substr(posAgeVal, posEmail - posAgeVal));

            // Email
            size_t posEmailVal = posEmail + 8;
            size_t posPrice = line.find(", Price:");
            email = line.substr(posEmailVal, posPrice - posEmailVal);

            // Price
            size_t posPriceVal = posPrice + 8;
            price = stoi(line.substr(posPriceVal));

            names[seatNo - 1] = name;
            ages[seatNo - 1] = age;
            emails[seatNo - 1] = email;
            seatPrices[seatNo - 1] = price;
            booked[seatNo - 1] = true;
        }
    }
    file.close();
    cout << "✅ Previous bookings loaded!\n";
}

// ---------------- BOOKING FUNCTIONS ----------------
void bookTicket() {
    showSeatPrices();

    int seatNo;
    header("🎟️ Book a Ticket");
    cout << "Enter seat number (1-" << MAX_SEATS << "): ";
    cin >> seatNo;

    if (seatNo < 1 || seatNo > MAX_SEATS) {
        cout << "❌ Invalid seat number.\n";
        return;
    }
    if (booked[seatNo - 1]) {
        cout << "❌ Seat already booked.\n";
        return;
    }

    cin.ignore();
    cout << "👤 Enter name: ";
    getline(cin, names[seatNo - 1]);
    cout << "🎂 Enter age: ";
    cin >> ages[seatNo - 1];
    cin.ignore();
    cout << "📧 Enter email: ";
    getline(cin, emails[seatNo - 1]);

    booked[seatNo - 1] = true;

    cout << "\n✅ Ticket booked successfully!\n";
    cout << "🎟️ Seat No: " << seatNo
         << " | Price: ₹" << seatPrices[seatNo - 1] << endl;

    saveToFile();
    pause();
}

void cancelTicket() {
    header("❌ Cancel a Ticket");
    int seatNo;
    cout << "Enter seat number (1-" << MAX_SEATS << "): ";
    cin >> seatNo;

    if (seatNo < 1 || seatNo > MAX_SEATS || !booked[seatNo - 1]) {
        cout << "❌ No booking found for that seat.\n";
        return;
    }

    names[seatNo - 1] = "";
    ages[seatNo - 1] = 0;
    emails[seatNo - 1] = "";
    booked[seatNo - 1] = false;

    cout << "✅ Ticket for Seat " << seatNo << " cancelled.\n";
    saveToFile();
    pause();
}

void showBookedTickets() {
    header("🎬  🎟️ Booked Tickets  🎬");

    bool any = false;
    for (int i = 0; i < MAX_SEATS; i++) {
        if (booked[i]) {
            any = true;
            cout << "\n🎟️ Seat " << (i + 1);

            // Category
            if (seatPrices[i] == 300)
                cout << "  | 💺 Premium (₹300)";
            else if (seatPrices[i] == 200)
                cout << "  | ⭐ Standard (₹200)";
            else
                cout << "  | 🎫 Economy (₹150)";

            cout << "\n------------------------------------\n";
            cout << "👤 Name : " << names[i] << "\n";
            cout << "🎂 Age  : " << ages[i] << "\n";
            cout << "📧 Email: " << emails[i] << "\n";
            cout << "💰 Price: ₹" << seatPrices[i] << "\n";
            cout << "------------------------------------\n";
        }
    }

    if (!any) {
        cout << "\n🚫 No tickets booked yet.\n";
    }

    line();
    pause();
}

void showSeatStatus() {
    header("🎬  CINEMA HALL SEAT STATUS  🎬");
    cout << "                  📽️  [SCREEN]  📽️\n";
    line();

    string rowLabels[5] = {"A", "B", "C", "D", "E"};

    for (int row = 0; row < 5; row++) {
        cout << "Row " << rowLabels[row] << ":   ";
        for (int col = 0; col < 5; col++) {
            int seatNo = row * 5 + col + 1;
            if (booked[seatNo - 1])
                cout << "[" << seatNo << "❌] ";
            else
                cout << "[" << seatNo << "✅] ";
        }

        // Show category at end of row
        if (row == 0)
            cout << " 💎 (₹300)";
        else if (row == 1 || row == 2)
            cout << " ⭐ (₹200)";
        else
            cout << " 🎫 (₹150)";

        cout << endl;
    }

    line();
    cout << "✅ = Available   ❌ = Booked\n";
    pause();
}
void viewTicket() {
    header("🎟️ View Ticket");
    int seatNo;
    cout << "Enter seat number (1-" << MAX_SEATS << "): ";
    cin >> seatNo;

    if (seatNo < 1 || seatNo > MAX_SEATS) {
        cout << "❌ Invalid seat number.\n";
        pause();
        return;
    }

    if (!booked[seatNo - 1]) {
        cout << "🚫 No booking found for Seat " << seatNo << ".\n";
        pause();
        return;
    }

    // Determine row (A-E)
    string rowLabels[5] = {"A", "B", "C", "D", "E"};
    string row = rowLabels[(seatNo - 1) / 5];

    cout << "\n=========================================\n";
    cout << "          🎬 MOVIE TICKET 🎬\n";
    cout << "=========================================\n";
    cout << " Seat No   : " << seatNo << "\n";
    cout << " Row       : " << row << "\n";

    if (seatPrices[seatNo - 1] == 300)
        cout << " Category  : 💎 Premium (₹300)\n";
    else if (seatPrices[seatNo - 1] == 200)
        cout << " Category  : ⭐ Standard (₹200)\n";
    else
        cout << " Category  : 🎫 Economy (₹150)\n";

    cout << " Name      : " << names[seatNo - 1] << "\n";
    cout << " Age       : " << ages[seatNo - 1] << "\n";
    cout << " Email     : " << emails[seatNo - 1] << "\n";
    cout << " Price     : ₹" << seatPrices[seatNo - 1] << "\n";
    cout << "=========================================\n";
    cout << " 🎥 Enjoy your show! 🍿\n";
    cout << " 📽️ Thank you for booking with us 🎬\n";
    cout << "=========================================\n";

    pause();
}
// ---------------- MAIN ----------------
int main() {
    setSeatPrices();
    loadFromFile();

    projectCredits(); // Show project credits once at the start

    int choice;
    do {
        header("🍿 Movie Ticket Booking System 🍿");
        cout << "1️⃣  Book Ticket\n";
        cout << "2️⃣  Cancel Ticket\n";
        cout << "3️⃣  Show Booked Tickets\n";
        cout << "4️⃣  Show Seat Status\n";
        cout << "5️⃣  View Ticket\n";   // New Option
        cout << "6️⃣  Save Data\n";
        cout << "7️⃣  Exit\n";
        line();
        cout << "👉 Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bookTicket(); break;
            case 2: cancelTicket(); break;
            case 3: showBookedTickets(); break;
            case 4: showSeatStatus(); break;
            case 5: viewTicket(); break;   // New Function Call
            case 6: saveToFile(); 
                    cout << "💾 Data saved!\n"; 
                    pause(); 
                    break;
            case 7: saveToFile(); 
                    cout << "👋 Thank you! Enjoy your movie 🎥\n"; 
                    break;
            default: cout << "❌ Invalid choice.\n"; pause();
        }

    } while (choice != 7);

    return 0;
}