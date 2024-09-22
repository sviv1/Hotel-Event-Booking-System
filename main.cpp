#include <bits/stdc++.h>

using namespace std;



//base class
class client
{
public:
    //base class data members
    static int c_id_count;
    int cost_cnt;
    char c_type;

    Clien(){
        cost_cnt=0;
    }

    //base class member functions
    //using csv file to store & check the user data
    //virtual function for polymorphism
   virtual void check()
{
    // Searching if a client has his/her account
    fstream fin;
    fin.open("client.csv", ios::in);
    string target_phn;
    cout << "Enter the phone number of the client to see details: ";
    cin >> target_phn;

    vector<string> row;
    string line, word;
    int count = 0;

    while (getline(fin, line)) {  // Read the entire line
        row.clear();
        stringstream s(line);

        // Split the line by commas
        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        // Check if the line has at least 5 columns
        if (row.size() >= 5) {
            // Compare phone number as string (safer than converting to int)
            if (row[2] == target_phn) {
                // Printing the client data
                count = 1;
                cout << "Client ID: " << row[0] << "\n";
                cout << "Name: " << row[1] << "\n";
                cout << "Phone No: " << row[2] << "\n";
                cout << "Address: " << row[3] << "\n";
                cout << "NID: " << row[4] << "\n";
                break;
            }
        } else {
            // Handle case where the line is incomplete or corrupted
            cout << "Error: Incomplete or corrupted data in CSV file.\n";
        }
    }

    // If the client isn't registered
    if (count == 0)
        cout << "Record not found\n";

    fin.close();  // Close the file
}

     // Virtual function for updating or adding new clients
    virtual int update()
    {
      fstream fin, fout;
fin.open("client.csv", ios::in);

string target_phn;
int count = 0;

cout << "Enter the phone number of the client: ";
cin >> target_phn;

vector<string> row;
string line, word;

// Checking if the client already exists
while (getline(fin, line)) {
    row.clear();
    stringstream s(line);

    // Splitting the line into comma-separated values
    while (getline(s, word, ',')) {
        row.push_back(word);
    }

    if (row.size() > 2) {  // Ensure there are enough fields
        string phn = row[2];  // Phone number field is at index 2

        if (target_phn == phn) {
            // Client exists, print the existing details
            count = 1;
            cout << "Client already exists. Details:\n";
            cout << "Client ID: " << row[0] << "\n";
            cout << "Name: " << row[1] << "\n";
            cout << "Phone No: " << row[2] << "\n";
            cout << "Address: " << row[3] << "\n";
            cout << "NID: " << row[4] << "\n";
            break;
        }
    }
}

fin.close();

// If the client does not exist, add them to the file
if (count == 0) {
    fout.open("client.csv", ios::out | ios::app);

    int c_id = ++c_id_count;  // Auto-generate a new client ID
    string c_name, c_address, c_nid;

    // Getting the new client's details
    cout << "New client detected. Generating new Client ID: " << c_id << endl;

    cin.ignore();  // Clear the input buffer
    cout << "Enter Client Name: ";
    getline(cin, c_name);  // Use getline to allow spaces in names

    cout << "Enter Client Address: ";
    getline(cin, c_address);  // Use getline for address

    cout << "Enter Client NID: ";
    getline(cin, c_nid);  // Use getline for NID

    // Writing the new client details to the CSV file
    fout << c_id << ","
         << c_name << ","
         << target_phn << ","
         << c_address << ","
         << c_nid << "\n";

    fout.close();

    cout << "Client data saved successfully.Now you can type 3 to Handle your Bookings!\n";
}

    }
    /*
    we can also get the informations using constructor
    client(string c_name,string c_phone_no,string c_address,string c_nid,char c_type)
    {
        c_id_count++; c_id=c_id_count;
        this->c_name=c_name; this->c_phone_no=c_phone_no; this->c_address=c_address; this->c_nid=c_nid; this->c_type=c_type;
    }
    */
};

int client::c_id_count = 0;  // Define and initialize the static member variable


//derived class of the base class client
//virtually inherited client to solve diamond problem

class client_hotelroom:virtual public client
{
public:
    //extended check function to check if a hotel room is vacant

void check() {
    //opening txt file to read
    ifstream inf("hotelroom.txt");

    //if the text file is not available
    if (!inf) {
        cout << "Unable to open Hotel's room file" << endl;
        return;
    }

    int room_id;
    string room_type, room_book;
    bool available_room_found = false;

    cout << "Available Rooms:" << endl;

    //reading the whole file to print available hotel rooms
    while (inf >> room_id >> room_type >> room_book) {
        if (room_book == "NULL") {
            cout << "Room ID: " << room_id << ", Room Type: " << room_type << endl;
            available_room_found = true;
        }
    }

    // If no rooms are available, print a message
    if (!available_room_found) {
        cout << "No available rooms at the moment." << endl;
    }

    //closing the file
    inf.close();
}

    //extented update funtion to book a hotel room
int update()
{
    // Taking the information to book a definite room
    int target_room_id, c_id;
    cout << "Please enter the room id the client wants to book:" << endl;
    cin >> target_room_id;
    cout << "Please enter the client id:" << endl;
    cin >> c_id;

    // Changing the int c_id to string client_id to compare
    string client_id;
    stringstream ss;
    ss << c_id;
    client_id = ss.str();

    // Opening the text file to read and append
    ifstream inf("hotelroom.txt");
    ofstream outf("hotelroom1.txt");
    if (!inf)
    {
        cout << endl << "Unable to open Hotel's room file" << endl;
        return -1;
    }

    int room_id;
    string room_type, room_book;
    bool room_found = false;
    cost_cnt=0;
    // Reading from the file and updating it with the booked room
    while (inf >> room_id >> room_type >> room_book) // Avoid using .eof() as a condition
    {
        if (room_id == target_room_id)
        {
            room_found = true;

            // Calculating the cost based on the room type
            if (room_type == "standard")
                cost_cnt += 2000;
            else if (room_type == "suite")
                cost_cnt += 5000;
            else if (room_type == "deluxe")
                cost_cnt += 10000;

            // Informing the user about the booking
            cout << "Room " << room_id << " (" << room_type << ") is being booked." << endl;

            // Updating the room with client_id to indicate booking
            outf << room_id << " " << room_type << " " << client_id << endl;
        }
        else
        {
            // If not the required room, simply rewrite it as it is
            outf << room_id << " " << room_type << " " << room_book << endl;
        }
    }

    if (!room_found)
    {
        cout << "Room with ID " << target_room_id << " not found." << endl;
    }

    // Closing the files to save the update
    outf.close();
    inf.close();

    // Deleting the previous file and renaming the new file to replace the old one
    remove("hotelroom.txt");
    rename("hotelroom1.txt", "hotelroom.txt");

    // Handling the payment

int payment;
while (true) {
    cout << "Please enter the payment (Total cost: " << cost_cnt << "): ";
    cin >> payment;

    if (payment > cost_cnt) {
        cout << "Payment cannot exceed the total cost. Please enter the correct amount." << endl;
    } else {
        // If the payment is valid, break the loop
        break;
    }
}

// Final message after successful booking
if (payment == cost_cnt) {
    cout << "Payment successful! Your room is booked." << endl;
}


    // Returning the cost of the client
    return cost_cnt;
}



    //checkout a booked room to make it available again
      void checkout() {
        int c_id;
        cout << "Please enter the client id: ";
        cin >> c_id;
        string client_id = to_string(c_id);

        ifstream inf("hotelroom.txt");
        ofstream outf("hotelroom1.txt");
        if (!inf) {
            cout << "Unable to open hotel room file" << endl;
            return;
        }

        int room_id;
        string room_type, room_book;
        bool checked_out = false;

        while (inf >> room_id >> room_type >> room_book) {
            if (room_book == client_id) {
                cout << "Checking out Room: " << room_id << " " << room_type << endl;
                outf << room_id << " " << room_type << " NULL" << endl;
                checked_out = true;
            } else {
                outf << room_id << " " << room_type << " " << room_book << endl;
            }
        }

        outf.close();
        inf.close();

        if (!checked_out) {
            cout << "No room booked under this client ID." << endl;
        } else {
            remove("hotelroom.txt");
            rename("hotelroom1.txt", "hotelroom.txt");
        }
    }





    //virtual function for polymorphism in derived class cost
    virtual void display_cost(){};
};



//client's derived class to book the convention hall

// Derived class for convention hall bookings

class client_conventionhall : virtual public client {
public:
    // Check function to check if the hall is available for the given date range
    void check() {
        // Open the text file and take necessary information
        ifstream inf("conventionhall.txt");
        if (!inf) {
            cout << endl << "Unable to open conventionhall file" << endl;
            return;
        }

        string start_day, end_day, hall_book, target_start_day, target_end_day, res = "Available";
        cout << endl << "Please enter the start date (Ex: 23/05/2019): ";
        cin >> target_start_day;
        cout << endl << "Please enter the end date (Ex: 25/05/2019): ";
        cin >> target_end_day;

        // Check if any existing bookings overlap with the requested range
        while (!inf.eof()) {
            inf >> start_day >> end_day >> hall_book;
            cout << start_day << " " << end_day << " " << hall_book << endl;

            // Check for overlap between the requested range and the existing bookings
            if (!(target_end_day < start_day || target_start_day > end_day)) {
                res = "Booked";
            }
        }

        // Show whether the hall is available or not
        cout << endl << "Hall status: " << res << endl;
        inf.close();
    }

    // Update the booking of the convention hall
    int update() {
        // Taking necessary info to book a time
        string target_start_day, target_end_day;
        int c_id;

        cout << "Please enter the start date of the booking (Ex: 23/05/2019): ";
        cin >> target_start_day;
        cout << "Please enter the end date of the booking (Ex: 25/05/2019): ";
        cin >> target_end_day;
        cout << "Please enter the client ID: ";
        cin >> c_id;

        // Check if the hall is available for the given range
        ifstream inf("conventionhall.txt");
        string start_day, end_day, hall_book, res = "Available";

        while (!inf.eof()) {
            inf >> start_day >> end_day >> hall_book;

            // Check for overlap with existing bookings
            if (!(target_end_day < start_day || target_start_day > end_day)) {
                res = "Booked";
            }
        }
        inf.close();

        if (res == "Booked") {
            cout << "The hall is already booked for the selected date range!" << endl;
            return -1; // Indicating booking failed
        }

        // Calculating the cost
        cost_cnt += 20000;

        // Append the new booking to the text file
        ofstream outf("conventionhall.txt", ios::app);
        outf << endl << target_start_day << " " << target_end_day << " " << c_id;
        outf.close();

        cout << "Hall booked successfully for the selected date range!" << endl;
        return cost_cnt;
    }

    virtual void display_cost() {};
};


// Derived class for restaurant bookings
class client_restaurant : virtual public client {
public:
    // Check if the required number of tables is available for the given date and time slot
    void check() {
        // Input the necessary info
        ifstream inf("restaurant.txt");
        if (!inf) {
            cout << endl << "Unable to open restaurant file" << endl;
            return;
        }

        string day, start_time, end_time;
        int booked_tables, target_tables, available_tables = 50; // Assume restaurant has 50 tables
        string target_day, target_start_time, target_end_time;

        cout << endl << "Please enter the date (Ex: 23/05/2019): ";
        cin >> target_day;
        cout << endl << "Please enter the start time in 24 hrs format (Ex: 07:00): ";
        cin >> target_start_time;
        cout << endl << "Please enter the end time in 24 hrs format (Ex: 09:00): ";
        cin >> target_end_time;
        cout << endl << "Please enter the number of tables needed: ";
        cin >> target_tables;

        // Check the booking data
        while (!inf.eof()) {
            inf >> day >> start_time >> end_time >> booked_tables;

            // If the booking overlaps with the target time and date
            if (day == target_day && !(target_end_time <= start_time || target_start_time >= end_time)) {
                available_tables -= booked_tables; // Reduce available tables based on existing bookings
            }
        }
        inf.close();

        // Check if the required number of tables is available
        if (available_tables >= target_tables) {
            cout << endl << "The restaurant is available for " << target_tables << " table(s)." << endl;
        } else {
            cout << endl << "Not enough tables available. Only " << available_tables << " table(s) left." << endl;
        }
    }

    // Book the restaurant for the given date and time slot with the specified number of tables
    int update() {
        // Take necessary info for the booking
        string target_day, target_start_time, target_end_time;
        int c_id, tables_needed;

        cout << "Please enter the required date (Ex: 23/05/2019): ";
        cin >> target_day;
        cout << "Please enter the start time in 24 hrs format (Ex: 07:00): ";
        cin >> target_start_time;
        cout << "Please enter the end time in 24 hrs format (Ex: 09:00): ";
        cin >> target_end_time;
        cout << "Please enter the number of tables to book: ";
        cin >> tables_needed;
        cout << "Please enter the client ID: ";
        cin >> c_id;

        // Open the file and check the availability first
        ifstream inf("restaurant.txt");
        string day, start_time, end_time;
        int booked_tables, available_tables = 10;

        while (!inf.eof()) {
            inf >> day >> start_time >> end_time >> booked_tables;

            // If the booking overlaps with the requested time
            if (day == target_day && !(target_end_time <= start_time || target_start_time >= end_time)) {
                available_tables -= booked_tables; // Reduce available tables
            }
        }
        inf.close();

        // If there are enough tables available
        if (available_tables >= tables_needed) {
            // Cost calculation (200 per table)
            cost_cnt += tables_needed * 200;

            // Append new booking to the file
            ofstream outf("restaurant.txt", ios::app);
            outf << endl << target_day << " " << target_start_time << " " << target_end_time << " " << tables_needed << " " << c_id;
            outf.close();

            cout << "Booking successful for " << tables_needed << " table(s)." << endl;
        } else {
            cout << "Booking failed. Not enough tables available. Only " << available_tables << " table(s) left." << endl;
        }

        return cost_cnt;
    }

    virtual void display_cost() {};
};


class cost : public client_conventionhall, public client_hotelroom, public client_restaurant {
public:
    // Check and update function for creating polymorphism
    void check() {
        client_conventionhall::check();
        client_hotelroom::check();
        client_restaurant::check();
    }

    int update() {
        int total_cost = 0;
        total_cost += client_conventionhall::update();
        total_cost += client_hotelroom::update();
        total_cost += client_restaurant::update();
        return total_cost;
    }

    // Displaying the total cost of a client
    void display_cost(int cost) {
        cout << endl << "Total cost: " << cost << endl;
        int paid;
        cout << "Paid money: ";
        cin >> paid;
        if (paid >= cost) {
            cout << "Receivable change: " << paid - cost << endl;
        } else {
            cout << "Insufficient payment. Please pay the remaining: " << cost - paid << endl;
        }
    }

    // Operator overloading to compute the cost (addition instead of subtraction)
    cost operator + (cost c) {
        cost c3;
        c3.cost_cnt = this->cost_cnt + c.cost_cnt;
        return c3;
    }
};


void handleBookings(client *bptr, cost &c2, client_hotelroom &h1, client_conventionhall &ch1, client_restaurant &r1) {
    int t;
    while (true) {
        cout << "Type 1 to book a hotel room" << endl
             << "Type 2 to book convention hall" << endl
             << "Type 3 to reserve restaurant meal" << endl
             << "Type 4 to check out hotel room" << endl
             << "Type 0 to end" << endl;
        cin >> t;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        if (t == 1) {
            bptr = &h1;
            bptr->check();
            cout << "Type 1 to check in, Type 0 to not" << endl;
            cin >> t;
            if (t) {
                int rooms;
                cout << "How many rooms?" << endl;
                cin >> rooms;

                int totalCost = 0;  // Reset total cost for this booking
                for (int i = 0; i < rooms; ++i) {
                    totalCost += bptr->update();  // Accumulate cost for each room
                }
                c2.display_cost(totalCost);  // Display total cost after all bookings
            }
        } else if (t == 2) {
            bptr = &ch1;
            bptr->check();
            cout << "Type 1 to book, Type 0 to not" << endl;
            cin >> t;
            if (t) {
                int cost = bptr->update();  // Assuming update() returns the cost for booking
                c2.display_cost(cost);
            }
        } else if (t == 3) {
            bptr = &r1;
            bptr->check();
            cout << "Type 1 to book, Type 0 to not" << endl;
            cin >> t;
            if (t) {
                int cost = bptr->update();  // Assuming update() returns the cost for booking
                c2.display_cost(cost);
            }
        } else if (t == 4) {
            h1.checkout();  // Assuming this handles checkouts correctly
        } else if (t == 0) {
            break;
        } else {
            cout << "Invalid option. Try again." << endl;
        }
    }
}





int main() {
    client *bptr;
    client c1;
    client_conventionhall ch1;
    client_hotelroom h1;
    client_restaurant r1;
    cost c2;
    int t;

    while (true) {
        cout << endl << "Type 1 to search for a client id" << endl
             << "Type 2 to create a client id" << endl
             << "Type 3 to handle bookings" << endl
             << "Type 0 to end" << endl;
        cin >> t;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        if (t == 1) {
            bptr = &c1;
            bptr->check();
        } else if (t == 2) {
            bptr = &c1;
            bptr->update();
        } else if (t == 3) {
            handleBookings(bptr, c2, h1, ch1, r1);
        } else if (t == 0) {
            cout << "Exiting the program..." << endl;
            break;
        } else {
            cout << "Invalid option. Try again." << endl;
        }
    }

    return 0;
}









