#include <bits/stdc++.h>
using namespace std;

class Manager {
private:
    string password;
public:
    string name;
    Manager(string n, string p) : name(n), password(p) {}

    bool validatePassword(const string& pw) const {
        return password == pw;
    }
};

class Customer {
protected:
    string password;
    double account_balance = 0.0;
    vector<pair<int, double>> bookedTickets; 

public:
    static int idCounter;
    int id;
    string username;
    Customer() : id(idCounter++), username(""), password("") {}
    Customer(string un, string pw) : username(un), password(pw) {
        id = idCounter++;
    }

    bool validatePassword(const string& pw) const {
        return password == pw;
    }

    double getBalance() const {
        return account_balance;
    }

    void deductBalance(double amount) {
        account_balance -= amount;
    }

    void addBalance(double amount) {
        account_balance += amount;
    }

    void bookTicket(int movieID, double ticketPrice) {
        bookedTickets.push_back({movieID, ticketPrice});
    }

    bool hasBookedTicket(int movieID) const {
        return any_of(bookedTickets.begin(), bookedTickets.end(), 
                      [movieID](const pair<int, double>& ticket) {
                          return ticket.first == movieID;
                      });
    }

    double getTicketPrice(int movieID) const {
        auto it = find_if(bookedTickets.begin(), bookedTickets.end(),
                          [movieID](const pair<int, double>& ticket) {
                              return ticket.first == movieID;
                          });
        return (it != bookedTickets.end()) ? it->second : 0.0;
    }

    void removeTicket(int movieID) {
        bookedTickets.erase(
            remove_if(bookedTickets.begin(), bookedTickets.end(),
                      [movieID](const pair<int, double>& ticket) {
                          return ticket.first == movieID;
                      }),
            bookedTickets.end()
        );
    }

    void displayBookedTickets() const {
        if (bookedTickets.empty()) {
            cout << "No tickets booked." << endl;
            return;
        }
        cout << "Booked Tickets:" << endl;
        for (const auto& ticket : bookedTickets) {
            cout << "Movie ID: " << ticket.first << ", Price: Rs" << ticket.second << endl;
        }
    }
};

int Customer::idCounter = 1;

class Movie {
public:
    int id;
    string title;
    string start_time;
    int duration;
    double price;
    int availableSeats = 50; 

    Movie(int i = 0, string t = "", string st = "", int d = 0, double p = 0.0)
        : id(i), title(t), start_time(st), duration(d), price(p) {}

    void viewDetails() const {
        cout << "ID: " << id << ", Title: " << title
             << ", Start Time: " << start_time
             << ", Duration: " << duration << " hrs"
             << ", Price: Rs." << price 
             << ", Available Seats: " << availableSeats << endl;
    }

    bool hasAvailableSeats() const {
        return availableSeats > 0;
    }

    void reduceSeats() {
        if (availableSeats > 0) {
            availableSeats--;
        }
    }

    void addSeat() {
        if (availableSeats < 50) {
            availableSeats++;
        }
    }
};


void viewAllMovies(const map<int, Movie>& movieMap) {
    if (movieMap.empty()) {
        cout << "No movies available!" << endl;
        return;
    }

    for (const auto& moviePair : movieMap) {
        moviePair.second.viewDetails();
    }
}


void addMovie(map<int, Movie>& movieMap, map<int, pair<int, int>>& movieTimes, int id, const string& title, const string& start_time, int duration, double price) {
   
    int startHour;
    startHour  = stoi(start_time.substr(0, 2)); 
    startHour +=( (start_time.substr(5, 2) == "PM" )? 12 : 0);

    
    if (movieMap.find(id) != movieMap.end()) {
        cout << "Movie with this ID already exists, manager!" << endl;
        return;
    }

    
    
    if(!movieTimes.empty()) {
        for (const auto& movieTime : movieTimes) {
            int ID = movieTime.first;
            auto times = movieTime.second;
            int existingStart = times.first;
            int existingEnd = times.first + times.second;
    
            if (startHour == existingStart) {
                cout << "A movie already starts at this time. Cannot add this movie!" << endl;
                return;
            }
    
            if (startHour < existingEnd && startHour + duration > existingStart) {
                cout << "This movie overlaps with another movie. Cannot add this movie!" << endl;
                return;
            }
        }
    }

    
    movieMap[id] = Movie(id, title, start_time, duration, price);
    movieTimes[id] = {startHour, startHour + duration}; 
    cout << "Movie added successfully!" << endl;
}


void removeMovie(map<int, Movie>& movieMap, map<int, pair<int, int>>& movieTimes, int id) {
    if (movieMap.erase(id)) {
        cout << "Movie removed successfully!" << endl;
        movieTimes.erase(id);
    } else {
        cout << "Movie with this ID does not exist!" << endl;
    }
}


void bookTicket(map<int, Movie>& movieMap, Customer& customer, int movieID) {
    auto it = movieMap.find(movieID);
    if (it == movieMap.end()) {
        cout << "Movie with this ID does not exist!" << endl;
        return;
    }

    Movie& movie = it->second;
    if (!movie.hasAvailableSeats()) {
        cout << "Sorry, no seats available for this movie!" << endl;
        return;
    }

    if (customer.hasBookedTicket(movieID)) {
        cout << "You have already booked a ticket for this movie!" << endl;
        return;
    }

    if (customer.getBalance() < movie.price) {
        cout << "Insufficient balance to book this ticket!" << endl;
        return;
    }

    customer.deductBalance(movie.price);
    customer.bookTicket(movieID, movie.price);
    movie.reduceSeats();

    cout << "Ticket booked successfully for " << movie.title << "!" << endl;
    cout << "Remaining Balance: Rs." << customer.getBalance() << endl;
}


void cancelTicket(map<int, Movie>& movieMap, Customer& customer, int movieID) {
    if (!customer.hasBookedTicket(movieID)) {
        cout << "No ticket found for this movie!" << endl;
        return;
    }

    auto it = movieMap.find(movieID);
    if (it == movieMap.end()) {
        cout << "Movie no longer exists!" << endl;
        return;
    }

    Movie& movie = it->second;
    double ticketPrice = customer.getTicketPrice(movieID);

    customer.addBalance(ticketPrice);
    customer.removeTicket(movieID);
    movie.addSeat();

    cout << "Ticket canceled successfully!" << endl;
    cout << "Refunded: Rs." << ticketPrice << ", Current Balance: Rs." << customer.getBalance() << endl;
}


bool check(string un, string pw, unordered_map<string, Customer>& customerMap) {
    if (customerMap.find(un) != customerMap.end()) {
        if (customerMap[un].validatePassword(pw)) {
            cout << "Login successful!" << endl;
            cout << "Task 1: customer profile\nTask 2: View all Movies\nTask 3: Top up\nTask 4: Book a Ticket\nTask 5: Cancel a Ticket\nTask 6: Log Out\n";
            return true;
        } else {
            cout << "Incorrect password!" << endl;
            return false;
        }
    }

    
    customerMap[un] = Customer(un, pw);
    cout << "Welcome, " << un << "!" << endl;
    cout << "Task 1: customer profile\nTask 2: View all Movies\nTask 3: Top up\nTask 4: Book a Ticket\nTask 5: Cancel a Ticket\nTask 6: Log Out\n";
    return true;
}

int main() {
    

    unordered_map<string, Customer> customerMap;
    map<int, Movie> movieMap;
    map<int, pair<int, int>> movieTimes; 
    Manager manager("hrushikesh_roop", "qwerty");

    while (1) {
        cout<<"1: Manager\n2: User\n";
        int ch;
        cout << "Choice.ID: ";
        cin >> ch;
        string un, ps;
        cout << "Username: ";
        cin >> un;
        cout << "Password: ";
        cin >> ps;
        bool auth = false;

        if (ch == 1) { 
            if (manager.name == un && manager.validatePassword(ps)) {
                cout << "LogIn successful, Manager!" << endl;
                cout << "Task 1: View all Movies\nTask 2: Add a Movie\nTask 3: Remove a Movie\nTask 4: LogOut\n";
                auth = true;
            } else {
                cout << "Invalid manager credentials!" << endl;
            }
        } else if (ch == 2) { 
            auth = check(un, ps, customerMap);
        }

        if (auth) {
            if (ch == 1) { 
                
                while (1) {
                    cout << "Task.no: ";
                    int p;
                    cin >> p;
                    if (p == 1) {
                        viewAllMovies(movieMap);
                    } else if (p == 2) {
                        int id;
                        string title, start_time;
                        int duration;
                        double price;
                        cout << "ID: ";
                        cin >> id;
                        cout << "Title: ";
                        cin >> title;
                        cout << "Start Time(HH:00(AM/PM)): ";
                        cin >> start_time;
                        cout << "Duration: ";
                        cin >> duration;
                        cout << "Price: ";
                        cin >> price;
                        addMovie(movieMap, movieTimes, id, title, start_time, duration, price);
                    } else if (p == 3) {
                        int id;
                        cout << "ID: ";
                        cin >> id;
                        removeMovie(movieMap, movieTimes, id);
                    }else if(p==4)break;
                }
            } else if (ch == 2) {
                Customer& customer = customerMap[un];
                
                while (1) {
                    cout << "Task.no :";
                    int p;
                    cin >> p;
                    if (p == 1) {
                        cout<<un<<endl;
                        cout << "Current Balance: Rs." << customer.getBalance() << endl;
                        customer.displayBookedTickets();  
                    } else if (p == 2) {
                        viewAllMovies(movieMap);
                    } else if (p == 3) {
                        double amount;
                        cout << "Amount: ";
                        cin >> amount;
                        customer.addBalance(amount);
                        cout << "Balance added successfully!" << endl;
                        cout << "Current Balance: Rs." << customer.getBalance() << endl;
                    } else if (p == 4) {
                        int id;
                        cout << "ID: ";
                        cin >> id;
                        bookTicket(movieMap, customer, id);
                    } else if (p == 5) {
                        int id;
                        cout << "ID: ";
                        cin >> id;
                        cancelTicket(movieMap, customer, id);
                    }else if(p==6)break;
                }
            }
        }
    }

    return 0;
}
