# Library Management System

This project is a console-based Library Management System written in C++. It is organized in a simple academic submission format and demonstrates core Object-Oriented Programming concepts with STL-based data handling.

## Technologies Used

- C++
- STL
- Object-Oriented Programming
- File handling using text files

## Features

- Add and delete books
- Register library members
- Search books by title and author
- Search members by name
- Issue and return books
- Track borrow history
- Show basic library statistics
- Store records using text files

## Project Structure

```text
Library_Management_System_CPP/
├── src/
│   ├── main.cpp
│   ├── Library.cpp
│   ├── Library.h
│   ├── Book.cpp
│   ├── Book.h
│   ├── Member.cpp
│   ├── Member.h
│   ├── BorrowRecord.cpp
│   ├── BorrowRecord.h
│   ├── UI.cpp
│   └── UI.h
├── data/
│   ├── books.txt
│   ├── members.txt
│   └── borrow_records.txt
├── README.md
└── instructions.txt
```

## Compile

```bash
g++ -std=c++17 src/main.cpp src/Library.cpp src/Book.cpp src/Member.cpp src/BorrowRecord.cpp src/UI.cpp -o lms
```

## Run

```bash
./lms
```
