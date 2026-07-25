# Library Management System

A simple **console-based Library Management System** built in C++. It lets a librarian add, search, update, issue, and return books — while automatically tracking overdue fines and saving all data to disk between runs.

This project was developed using **Embarcadero Dev-C++**, a lightweight IDE for writing and compiling C++ programs, and is written entirely as a single-file console application, making it easy to read, compile, and extend.

---

## Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [Built With](#built-with)
- [Data Structures](#data-structures)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Overdue Fine Calculation](#overdue-fine-calculation)
- [Sample Menu Walkthrough](#sample-menu-walkthrough)
- [Limitations](#limitations)
- [Roadmap Ideas](#roadmap-ideas)
- [Learning Outcomes](#learning-outcomes)
- [License](#license)
- [Author](#author)

---

## About the Project

Many college and school libraries still rely on manual registers or spreadsheets to track which books are available and which have been borrowed. This project was built as a learning exercise to recreate that basic front-desk workflow in C++ — covering everything from adding new stock to issuing books, handling returns, and calculating late fines — without relying on any external database or GUI framework.

Everything runs through a simple numbered menu in the terminal, and all data is written to plain text files so that nothing is lost when the program is closed and reopened.

---

## Features

- **Add Book** — add new books to the library, with duplicate detection based on title, author, and category
- **Display Books** — view every book currently in the library in a clean, aligned tabular format
- **Update Book** — edit a book's title, author, category, or quantity after it has been added
- **Search Book** — look up the full details of a specific book using its unique ID
- **Issue Book** — issue a book to a student, recording their ID, name, email, issue date, and due date
- **Return Book** — process a book return and automatically calculate any overdue fine
- **Delete Book** — remove a book from the system, with safe handling for books that are still on loan
- **Available Books** — list only the books that currently have free copies to issue
- **Issued Books** — list every book that is currently checked out, along with the borrowing student
- **Overdue Books** — list all overdue books together with the number of days late and the fine owed
- **Persistent Storage** — every change is written to disk immediately and reloaded automatically the next time the program starts

---

## Built With

- **Language:** C++
- **IDE:** Embarcadero Dev-C++
- **Concepts used:** structs, arrays, loops, functions, and file input/output
- **Date/Time handling:** the standard `ctime` library, used to record issue dates and calculate overdue days
- **Storage:** plain text files (`books.txt` and `issues.txt`), read and written using `fstream`

---

## Data Structures

The program is organized around two custom `struct` types, each acting as a blueprint for one kind of record.

### `Book`
| Field | Description |
|---|---|
| `id` | Unique book ID, auto-generated starting from 1001 |
| `title` | Title of the book |
| `author` | Name of the author |
| `category` | Genre or subject category |
| `quantity` | Total number of copies owned by the library |
| `available_copies` | Number of copies currently free to be issued |
| `issued_copies` | Number of copies currently on loan |
| `status` | Whether the book is available or fully issued out |

### `Issue`
| Field | Description |
|---|---|
| `book_id` | ID of the book that was issued |
| `book_title` | Title of the issued book, kept for quick reference |
| `student_id` | ID of the student who borrowed the book |
| `student_name` | Name of the student |
| `student_email` | Email address of the student |
| `issue_date` | Date the book was issued (recorded automatically) |
| `return_date` | Date the book is due back |

Both structs are stored in fixed-size arrays (`books[200]` and `issue_books[200]`), which are kept in sync with each other whenever a book is issued, returned, or deleted.

---

## Project Structure

Since this is a single-file console project, the structure is intentionally simple:

```
library-management-system/
│
├── library.cpp      # Main source file — all logic lives here
├── books.txt         # Auto-generated file storing book records
├── issues.txt         # Auto-generated file storing issue/borrowing records
└── README.md          # Project documentation
```

`books.txt` and `issues.txt` are created automatically the first time you add a book or issue one — you don't need to create them manually.

---

## How It Works

When the program starts, it immediately tries to load any existing data from `books.txt` and `issues.txt` so that books and borrowing records from a previous session are available right away.

The main loop then displays a numbered menu and waits for the librarian to choose an option. Based on the choice, the program calls the relevant function — for example, choosing option `5` calls the book-issuing function, which walks the librarian through selecting a book, entering the student's details, and setting a return date.

After almost every action that changes data — adding, updating, issuing, returning, or deleting a book — the program immediately saves the current state of both arrays back to their text files. This means the program never depends on being closed "properly" to keep its data safe.

Overdue fines are calculated by comparing the stored due date against the current system date using functions from `ctime`, converting both to a common time format, and measuring the difference in days.

---

## Getting Started

### Prerequisites
- A C++ compiler, such as the one bundled with **Embarcadero Dev-C++**, or any standard compiler like `g++`

### Compile & Run (Dev-C++)

1. Open **Embarcadero Dev-C++**.
2. Open `library.cpp` from the project folder (`File → Open Project or File`).
3. Compile the program using `Execute → Compile` (or `F9`).
4. Run it using `Execute → Run` (or `F10`).

### Compile & Run (Command Line)

```bash
# Clone the repository
git clone https://github.com/your-username/library-management-system.git
cd library-management-system

# Compile
g++ library.cpp -o library

# Run
./library        # On Windows: library.exe
```

> Make sure the program has permission to create `books.txt` and `issues.txt` in the same folder — this is where all data is saved.

---

## Usage

On launch, you'll see a menu like this:

```
1: Add book
2: Display books
3: Update book
4: Search book
5: Issue book
6: Return book
7: Delete book
8: Available books
9: Issued books
10: Overdue books
0: Exit
```

Type a number and press Enter to perform that action. The menu will keep reappearing after each action until you choose `0` to exit the program.

---

## Overdue Fine Calculation

If a book is returned after its due date, a fine is calculated using the following formula:

```
Fine = Overdue Days × Rs. 50
```

For example, a book returned 4 days late would incur a fine of Rs. 200. Books returned on or before their due date incur no fine at all.

---

## Sample Menu Walkthrough

A typical session might look like this:

1. Choose option `1` to add a new book — enter the title, author, category, and quantity.
2. Choose option `5` to issue that book — enter the book ID, the student's details, and a return date.
3. Choose option `9` to confirm the book now shows up under issued books.
4. Later, choose option `6` to return the book — the program tells you whether a fine is owed.
5. Choose option `0` to exit, knowing all changes have already been saved to disk.

---

## Limitations

- The system supports a maximum of **200 books** and **200 active issue records**, since both are stored in fixed-size arrays.
- There is no login or authentication system, so anyone running the program has full access to every option.
- There is no separate, permanent database of students — student details only exist as part of an issue record.
- Data is stored as **plain, unencrypted text**, so this project is meant for learning rather than for managing a real library's records.
- Return dates are entered manually by the librarian rather than being calculated automatically from a fixed loan period.
- The program does not currently support renewing a loan without first returning the book.

---

## Roadmap Ideas

- [ ] Add librarian login/authentication before granting access to the menu
- [ ] Migrate storage from plain text files to a lightweight database such as SQLite
- [ ] Add automatic due-date calculation based on a configurable loan period
- [ ] Add a book renewal option that extends the due date without a full return
- [ ] Build a simple GUI front end to replace the console interface
- [ ] Add basic reporting, such as most-borrowed books or most-active students

---

## Learning Outcomes

This project was a practical way to strengthen several core C++ concepts, including:

- Designing and using `struct`s to model real-world entities
- Managing collections of records with arrays, including insertion, searching, and deletion
- Reading from and writing to files using `fstream` for basic data persistence
- Working with dates and time using the `ctime` library
- Structuring a menu-driven console application with clear, reusable functions
- Validating user input to prevent invalid or unsafe values from being entered

---

## License

This project is open source and available for learning purposes. Feel free to fork, modify, and use it in your own projects.

---

## Author

Developed as a beginner-friendly project using **Embarcadero Dev-C++**, to practice structs, arrays, file handling, and menu-driven program design in C++.
