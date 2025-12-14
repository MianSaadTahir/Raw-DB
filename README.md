# Raw DB
A lightweight, modular, and extensible **Relational Database Management System (RDBMS)** built from scratch in C++. It supports SQL-like operations, B+ tree indexing, transaction control, role-based authentication, and a simple console interface. It demonstrates core principles of modern DBMS design.

## Table of Contents
- [Features](#features)
- [Architecture](#architecture)
- [Dataflow Diagram](#dataflow-diagram)
- [Screenshots](#screenshots)
- [Documentation](#documentation)
- [Technologies Used](#technologies-used)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)
## Features
- Admin & Guest login with secure credentials
- Create tables, insert data, SELECT queries, JOINs
- Efficient persistent data storage using pages
- Fast access through indexed keys
- Locking via a LockManager for consistency
- Backup and restore databases
- Converts and runs commands through a structured interface for parsing

## Architecture
The system is divided into two major parts:
### 1. **User-Facing Components**
- `main.cpp`: Command-line interface for interacting with the DB
- `AccessControl`: Handles login and role verification
- `Parser`: Parses user commands into structured data
- `Executor`: Maps parsed commands to database operations

### 2. **Backend Components**
- `Database`: Manages schema, tables, and data
- `StorageEngine`: Handles page I/O, buffer pool, and indexing
- `TransactionManager` & `LockManager`: Ensures data consistency
- `RecoveryManager`: Backs up and restores the database

## Dataflow Diagram
<img src="diagram/architecture.png" alt="Screenshot" width="50%">

## Screenshots
<img src="assets/1.png" alt="Screenshot" width="75%">
<img src="assets/2.png" alt="Screenshot" width="75%">

## Documentation
For a detailed overview of the project, refer to the [Documentation](./documentation) in the repository.

## Technologies Used
- C++
- STL

## Usage
1. Clone the repository
   `git clone https://github.com/miansaadtahir/Raw-DB.git`
2. Run the program
   `main.exe`
3. Login credentials
   - Admin <br>
   Username: `admin`
   Password: `admin123`<br>
   - Guest <br>
   Username: `guest`
   Password: `guest123`
4. Use `HELP` to see available commands

## Contributing
Contributions, issues, and feature requests are welcome!  
Feel free to check out the [issues page](https://github.com/miansaadtahir/Raw-DB/issues).

## License

This project is open source and available under the MIT [License](https://github.com/MianSaadTahir/Raw-DB/blob/main/LICENSE).


