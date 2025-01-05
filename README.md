# Block Boom Recruitment Task: Movie Management System

This project implements a terminal-based **Movie Management System** using **Object-Oriented Programming (OOP)** concepts in C++. The system allows interaction for two user roles: **Manager** and **Customer**, with distinct features and operations for each role.

## Features

### **User Roles**
1. **Manager**:
   - Only one manager exists: 
     - **Username**: `hrushikesh_roop`
     - **Password**: `qwerty`
   - Capabilities:
     1. **View All Movies**: Display all movies currently available.
     2. **Add a Movie**: Add a new movie to the system by providing details (ID, title, start time, duration, price).
     3. **Remove a Movie**: Remove a movie by providing its unique ID.
     4. **Logout**: Exit the manager session.
     
2. **Customer**:
   - Each customer has a profile with booked tickets and an account balance.
   - Capabilities:
     1. **View Profile**: Displays the customer’s booked tickets and current account balance.
     2. **View All Movies**: Displays a list of available movies.
     3. **Add Money**: Adds money to the customer’s account balance.
     4. **Book a Ticket**: Book a ticket for a movie by providing the movie ID.
     5. **Cancel a Ticket**: Cancel a booked ticket by providing the movie ID.
     6. **Logout**: Exit the customer session.


- **Terminal Interaction**: Designed for seamless interaction through the terminal.



## **How to Use**
1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/movie-management-system.git
   ```
2. Navigate to the project directory:
   ```bash
   cd movie-management-system
   ```
3. Compile the code:
   ```bash
   g++ -o movie_system main.cpp
   ```
4. Run the executable:
   ```bash
   ./movie_system
   ```



## **User Instructions**
### **Login**:
1. Select user role:
   - Press `1` for Manager
   - Press `2` for Customer
2. Enter the required credentials:
   - **Manager**: `username` and `password`
   - **Customer**: Create a profile (username and initial balance).

### **Manager Operations**:
- Follow on-screen prompts to:
  1. View all movies.
  2. Add a movie by entering its ID, title, start time, duration, and price.
  3. Remove a movie by entering its ID.
  4. Logout to exit the session.

### **Customer Operations**:
- Follow on-screen prompts to:
  1. View your profile (tickets and balance).
  2. View available movies.
  3. Add money to your account by entering an amount.
  4. Book a movie ticket by providing the movie ID.
  5. Cancel a booked ticket by providing the movie ID.
  6. Logout to exit the session.


## **Author**
**Hrushikesh Roop Avvari**  



