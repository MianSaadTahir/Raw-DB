# Raw DB
A lightweight, modular, and extensible **Relational Database Management System (RDBMS)** built from scratch in C++. It supports SQL-like operations, B+ tree indexing, transaction control, role-based authentication, and a simple console interface. It demonstrates core principles of modern DBMS design.

## Table of Contents
- [Features](#features)
- [Architecture](#architecture)
- [Circuit Diagram](#circuit-diagram)
- [Screenshots](#screenshots)
- [Usage](#usage)
- [Documentation](#documentation)
- [Technologies Used](#technologies-used)
- [Contributing](#contributing)

## Features
- **Role-Based Access Control**: Admin & Guest login with secure credentials.
- **SQL-like Command Support**: Create tables, insert data, SELECT queries, JOINs.
- **Page-Based Storage Engine**: Efficient persistent data storage using pages.
- **B+ Tree Indexing**: Fast access through indexed keys.
- **Transaction Control**: Basic locking via a `LockManager` for consistency.
- **Recovery System**: Backup and restore databases.
- **Parser + Executor**: Converts and runs commands through a structured interface.
- **Modular Design**: Organized into clearly defined components for extensibility.
- **Testing**: Unit tests for major modules like FileManager, StorageEngine, Transactions, Recovery, etc.


## Architecture
The system is divided into two major parts:
### 1. **User-Facing Components**
- `main.cpp`: Command-line interface for interacting with the DB.
- `AccessControl`: Handles login and role verification.
- `Parser`: Parses user commands into structured data.
- `Executor`: Maps parsed commands to database operations.

### 2. **Backend Components**
- `Database`: Manages schema, tables, and data.
- `StorageEngine`: Handles page I/O, buffer pool, and indexing.
- `TransactionManager` & `LockManager`: Ensures data consistency.
- `RecoveryManager`: Backs up and restores the database.

## Circuit Diagram
<img src="diagram/architecture.PNG" alt="Screenshot" width="75%">
<img src="diagram/dataflowdiagram.PNG" alt="Screenshot" width="75%">

## Screenshots
<img src="assets/1.PNG" alt="Screenshot" width="75%">
<img src="assets/2.PNG" alt="Screenshot" width="75%">
<img src="assets/3.PNG" alt="Screenshot" width="75%">
<img src="assets/4.PNG" alt="Screenshot" width="75%">
<img src="assets/5.PNG" alt="Screenshot" width="75%">
<img src="assets/6.PNG" alt="Screenshot" width="75%">
<img src="assets/7.PNG" alt="Screenshot" width="75%">
<img src="assets/8.PNG" alt="Screenshot" width="75%">
<img src="assets/9.PNG" alt="Screenshot" width="75%">

## Usage
1. Clone the repository
   `git clone https://github.com/miansaadtahir/Raw-DB.git`
2. Navigate to the project directory
   `cd RawDB\`
3. Run the program
   `main.exe`
4. Login credentials
   - Admin
   Username: `admin`
   Password: `admin123`
   - Guest
   Username: `guest`
   Password: `guest123`
6. Use `HELP` to see available commands

## Documentation
For a detailed overview of the project, refer to the [Documentation](./documentation) in the repository.

## Technologies Used
- C++
- C++ STL

## Contributing
Contributions, issues, and feature requests are welcome!  
Feel free to check out the [issues page](https://github.com/miansaadtahir/Raw-DB/issues) for more information.
