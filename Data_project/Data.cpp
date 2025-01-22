#include <iostream>
#include<string>

using namespace std;
const int tableSize = 10; // the size of the hash table

struct User { // struct for the user data
    string name;
    int password, id;
    User* next;
};

struct Admin { //struct for the admin data
    string name;
    string password;
};

struct Book {   // struct for the books data
    string title;
    string author;
    bool isBorrowed;
    Book* left;
    Book* right; //Binary tree 
};

struct QueueNode { // (used for waiting users)
    string username;
    string booktitle;
    QueueNode* next;
};

struct bookRecord {// for book records
    string title;
    bookRecord* next;
};

struct userborrow { // for user borrowing details
    userborrow* next;
    bookRecord* top = NULL;
    string name;
};

//Global variables 
User* head = nullptr;
User* hashTable[tableSize] = { NULL };//Hash table for user data
Book* root = NULL; // root of the binary tree for books
QueueNode* front = NULL; //front of the queue
QueueNode* rear = NULL; //rear of the queue
userborrow* top1 = NULL; // top of the user borrow stack
Admin admins[3] = {
    {"Ghazi", "202311259"},
    {"Shahed", "202311068"},
    {"Alia", "202310432"}
};

string ToUpperCase(string str)// coverting all lowercase letters to uppercase
{
    for (int i = 0; i < str.size(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

int hashFunction(int id) //determine the index for storing users in hash table
{
    return id % tableSize;
}

User* searchUser(int id) // search for a user by ID in the hash table
{
    int index = hashFunction(id);
    User* current = hashTable[index];
    while (current)
    {
        if (current->id == id)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void insertUser(int id, string& username, int password) //insert a new user in the hash table and linked list
{
    int index = hashFunction(id);
    User* newNode = new User{ username,password,id,NULL };
    if (!hashTable[index])
    {
        hashTable[index] = newNode;
    }
    else
    {
        User* current = hashTable[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        User* currHead = head;
        while (currHead->next != NULL)
            currHead = currHead->next;
        currHead->next = newNode;
    }
}

User* Check_user() //allow existing users to log in
{
    string user_name;
    int user_password;
    cout << "Enter your name:\n";
    cin >> user_name;
    cout << "Enter your password:\n";
    cin >> user_password;

    for (int i = 0; i < tableSize; ++i)
    {
        User* current = hashTable[i];
        while (current != nullptr)
        {
            if (current->name == user_name && current->password == user_password)
            {
                cout << "Welcome " << current->name << endl;
                return current;
            }
            current = current->next;
        }
    }
    return NULL;
}

void User_dashboard(User* user);
User* add_user() // add a new user to the system
{
    string user_name;
    int user_password, user_id;

    cout << "Enter your name:\n";
    cin >> user_name;
    cout << "Enter your password:\n";
    cin >> user_password;

    while (true)
    {
        cout << "Enter your user ID:\n";
        cin >> user_id;

        if (searchUser(user_id) != NULL)
        {
            cout << "User ID already exists,please choose a different one\n";
        }
        else
        {
            insertUser(user_id, user_name, user_password);
            cout << "Account created successfully\n";
            User* newUser = searchUser(user_id);
            User_dashboard(newUser);
            return newUser;
        }
    }
}

void change_info(User* user, string new_user_name, int new_user_password) //change user details
{
    user->name = new_user_name;
    user->password = new_user_password;
}

void viewORupdate(User* user) //view and update user's personal info
{
    int choice;
    cout << "\nPersonal Info:\n";
    cout << "Username: " << user->name << "\nPassword: " << user->password << "\nID: " << user->id << endl;
    cout << "Do you want to change your name/password? (1 for Yes,0 for No):";
    cin >> choice;

    if (choice == 1)
    {
        string new_user_name;
        int new_user_password, old_password;
        cout << "Enter your current password:";
        cin >> old_password;

        if (old_password == user->password)
        {
            cout << "Enter your new username: ";
            cin >> new_user_name;
            cout << "Enter your new password: ";
            cin >> new_user_password;
            change_info(user, new_user_name, new_user_password);
            cout << "Your info has been updated successfully\n";
        }
        else
        {
            cout << "Incorrect password, Cannot update information.\n";
        }
    }
}

Book* addbooks(string title, string author, Book* currbook) // adding books by the admin , using a binary tree to sort the books
{
    title = ToUpperCase(title);
    author = ToUpperCase(author);

    if (currbook == NULL) {
        Book* newbook = new Book;
        newbook->title = title;
        newbook->author = author;
        newbook->isBorrowed = false;
        newbook->left = newbook->right = NULL;
        return newbook;
    }
    else if (title < currbook->title)
    {
        currbook->left = addbooks(title, author, currbook->left);
    }
    else
    {
        currbook->right = addbooks(title, author, currbook->right);
    }
    return currbook;
}

Book* searchbytitle(Book* currbook, string title)   //searching the books by using binary search tree
{
    title = ToUpperCase(title);

    if (currbook == NULL || currbook->title == title)
    {
        return currbook;
    }
    if (title < currbook->title)
    {
        return searchbytitle(currbook->left, title);
    }
    else
    {
        return searchbytitle(currbook->right, title);
    }
}

void searchForBook() // search for a book and display its details by the user
{
    string title;
    cout << "Enter the title of the book you want to search: ";
    cin.ignore();
    getline(cin, title);
    title = ToUpperCase(title);
    Book* foundBook = searchbytitle(root, title);
    if (foundBook != NULL)
    {
        cout << "Book found: " << foundBook->title << "\n author: " << foundBook->author << endl;
    }
    else
    {
        cout << "Book not found\n";
    }
}

void displaybytitle(Book* currbook) // diplay all the books
{
    if (currbook != NULL)
    {
        displaybytitle(currbook->left);
        cout << "Book Titlel: " << currbook->title << "\n Author : " << currbook->author << endl;
        displaybytitle(currbook->right);
    }
}

void defaultBooks() // books that already in the system 
{
    root = addbooks("The grand design", "Stephen Hawking", root);
    root = addbooks("The picture of Dorian Gray", "Oscar Wilde", root);
    root = addbooks("The black hole war", "Leonard Susskind", root);
    root = addbooks("Crime and punishment", "Fyodor Dostoevsky", root);
    root = addbooks("Harryy Potter", "J.K. Rowling ", root);
    root = addbooks("The lord of the rings", "John Ronald", root);
    root = addbooks("A breif history of time", "Stephen Hawking", root);
    root = addbooks("White nights", "Fyodor Dostoevsky", root);
    root = addbooks("No longer human", "Osamu Dazai", root);
    root = addbooks("Fear", "Osamah Almuslim", root);
}

void addbooksbyAdmin() // adding books by the admin
{
    string title, author;
    cout << "enter the name of the book you want to add: ";
    cin.ignore();
    getline(cin, title);
    cout << "enter the author of the book: ";
    getline(cin, author);
    root = addbooks(title, author, root);
    cout << "book added successfully\n";
}

void enqueue(string username, string booktitle) //add a user and their book title to the waitlist (queue)
{
    QueueNode* curr = new QueueNode;
    curr->username = username;
    curr->booktitle = booktitle;
    curr->next = NULL;

    if (rear == NULL)
    {
        front = rear = curr;
    }
    else
    {
        rear->next = curr;
        rear = curr;
    }
}

bool isEmpty() //checking if the queue is empty
{
    return front == NULL;
}

string dequeue() // remove and return the user at the front of the queue
{
    if (front == NULL)
    {
        return "";
    }
    string user = front->username;
    QueueNode* curr = front;
    front = front->next;
    if (isEmpty())
    {
        rear = NULL;
    }
    delete curr;
    return user;
}

bool isStackEmpty(bookRecord* top) //checking if the stack is empty
{
    return top == NULL;
}

string pop(bookRecord*& top) // remove and return the book title from the top of the stack
{
    if (isStackEmpty(top))
    {
        cout << "stack is empty ";
        return "";
    }
    else {
        bookRecord* p1 = top;
        string title = top->title;
        top = top->next;
        delete p1;
        return title;
    }
}

bookRecord* push(bookRecord* top, string title) // adding a book to the top of the stack
{
    bookRecord* newbook = new bookRecord;
    newbook->title = title;
    newbook->next = top;
    top = newbook;
    return newbook;
}

void borrow(string username, string title) //allow the user to borrow a book
{
    Book* book1 = searchbytitle(root, title);
    if (book1 != NULL) {
        userborrow* user = top1;
        bool userFound = false;
        while (user != NULL) {
            if (user->name == username) {
                userFound = true;
                user->top = push(user->top, title);
                cout << username << " borrowed the book : " << title << endl;
                return;
            }
            user = user->next;
        }
        if (!userFound)
        {
            userborrow* newUser = new userborrow;
            newUser->name = username;
            newUser->top = push(newUser->top, title);
            newUser->next = top1;
            top1 = newUser;
            cout << username << " borrowed the book : " << title << endl;
        }
    }
    else {
        cout << "the following book : " << title << " is not found in the library\n";
    }
}

void borrowBook(string username, string title) // checking if the requested book is available 
{
    title = ToUpperCase(title);
    Book* book = searchbytitle(root, title);
    if (book != NULL)
    {
        if (!book->isBorrowed)
        {
            book->isBorrowed = true;
            borrow(username, title);
            cout << "Book is avaliable, you have borrowed: " << title << endl;
        }
        else
        {
            cout << "the book is already borrowed, you are added to the waitlist\n";
            enqueue(username, title);
        }
    }
    else
    {
        cout << "The book does not exist in the library.\n";
    }
}

void ShowWaitlist() //display all users who have borrowed books and the list of books they borrowed
{
    userborrow* curr = top1;
    bool hasBorrowedBooks = false;
    while (curr != NULL)
    {
        if (curr->top != NULL)
        {
            if (!hasBorrowedBooks)
            {
                cout << "Users with borrowed books:\n";
                hasBorrowedBooks = true;
            }
            cout << "user: " << curr->name << " has borrowed the following books:\n";
            bookRecord* temp = curr->top;
            while (temp != NULL)
            {
                cout << temp->title << endl;
                temp = temp->next;
            }
        }
        curr = curr->next;
    }
    if (!hasBorrowedBooks)
    {
        cout << "No users currently have borrowed books\n";
    }
    if (front != NULL)
    {
        cout << "\nWaitlist for books:\n";
        QueueNode* temp = front;
        while (temp != NULL)
        {
            cout << "User: " << temp->username << " is waiting for book: " << temp->booktitle << endl;
            temp = temp->next;
        }
    }
    else
    {
        cout << "No waitlist currently exists\n";
    }
}

void returnBook(string username) // allowing the user to return a borrowed book
{
    userborrow* user = top1;
    while (user != NULL)
    {
        if (user->name == username)
        {
            if (isStackEmpty(user->top))
            {
                cout << username << " has no books borrowed\n";
                return;
            }
            cout << "Books borrowed by " << username << ":\n";
            bookRecord* temp = user->top;
            string borrowedBooks[100];
            int count = 0;
            int index = 1;
            while (temp != NULL)
            {
                borrowedBooks[count++] = temp->title;
                cout << index++ << ". " << temp->title << endl;
                temp = temp->next;
            }
            int choice;
            cout << "Enter the number of the book you want to return: ";
            cin >> choice;
            if (choice< 1 || choice>count)
            {
                cout << "Invalid choice\n";
                return;
            }
            string returnedBook = ToUpperCase(borrowedBooks[choice - 1]);
            bookRecord* prev = NULL;
            temp = user->top;
            while (temp != NULL)
            {
                if (ToUpperCase(temp->title) == returnedBook)
                {
                    if (prev == NULL)
                    {
                        user->top = temp->next;
                    }
                    else
                    {
                        prev->next = temp->next;
                    }
                    delete temp;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
            cout << username << " returned the book : " << returnedBook << endl;
            Book* book = searchbytitle(root, returnedBook);
            if (book != NULL)
            {
                book->isBorrowed = false;
            }
            if (!isEmpty())
            {
                QueueNode* waitlistNode = front;
                while (waitlistNode != NULL)
                {
                    if (ToUpperCase(waitlistNode->booktitle) == returnedBook)
                    {
                        string nextUser = dequeue();
                        borrow(nextUser, returnedBook);
                        break;
                    }
                    waitlistNode = waitlistNode->next;
                }

            }
            return;
        }
        user = user->next;
    }
    cout << "User: " << username << " not found\n";
}

bool check_admin() //checking if username and password are right
{
    string admin_user, admin_pass;
    cout << "enter your username:";
    cin >> admin_user;
    cout << "enter your password:";
    cin >> admin_pass;
    for (int i = 0; i < 3; i++)
    {
        if (admins[i].name == admin_user && admins[i].password == admin_pass)
            return true;
    }
    cout << "Invalid username or password.\n";
    return false;
}

void displayUsers() // displaying all the system's users and allowing the admin to view thier details
{
    User* curr = head;
    int number = 1;
    if (curr == nullptr) {
        cout << "No users found.\n";
        return;
    }
    cout << "List of users:\n";
    while (curr != NULL)
    {
        cout << number << ".username:" << curr->name << ",User ID: " << curr->id << endl;
        curr = curr->next;
        number++;
    }
    cout << "Enter the user ID to view thier password:";
    int id;
    cin >> id;

    User* user = searchUser(id);
    if (user)
    {
        cout << "User ID: " << user->id << ",Username: " << user->name << ",Password: " << user->password << endl;
    }
    else
    {
        cout << "user not found" << endl;
    }
}

void adminDashboard() //admin options
{
    int choice = 0;
    while (choice != 5)
    {
        cout << "\nAdmin options:\n";
        cout << "1.Add books\n";
        cout << "2.view all books\n";
        cout << "3.view system users\n";
        cout << "4.view borrowed books(waitlist)\n";
        cout << "5.exit\n";
        cout << "enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addbooksbyAdmin();
            break;
        case 2:
            displaybytitle(root);
            break;
        case 3:
            displayUsers();
            break;
        case 4:
            ShowWaitlist();
            break;
        case 5:
            cout << "exiting admin options\n";
            break;
        default:
            cout << "invalid choice,try again\n";
            break;
        }
    }
}

void User_dashboard(User* user) //user options
{
    int choice;
    while (true)
    {
        cout << "Welcome to user dashboard:\n" << endl;
        cout << "1. View/Update personal info\n";
        cout << "2. View all books\n";
        cout << "3. Search for a book\n";
        cout << "4. Borrow/Return a book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            viewORupdate(user);
            break;
        case 2:
            displaybytitle(root);
            break;
        case 3:
            searchForBook();
            break;
        case 4:
        {
            int borrowChoice;
            cout << "1.Borrow a book\n2.Return a book\nEnter your choice:";
            cin >> borrowChoice;
            if (borrowChoice == 1)
            {
                string title;
                cout << "Enter the book title to borrow: ";
                cin.ignore();
                getline(cin, title);
                borrowBook(user->name, title);
            }
            else if (borrowChoice == 2)
            {
                returnBook(user->name);
            }
            else
            {
                cout << "Invalid choice\n";
            }
        }
        break;
        case 5:
            return;
        default:
            cout << "Invalid choice, try again\n";
        }
    }

}

void handleLogin() { // log in dashboard
    int choice_logging = 0;
    while (choice_logging != 3) {
        cout << "1. logging in as an Admin \n2. logging as a User\n3. Exit \n";
        cout << "Enter your choice : ";
        cin >> choice_logging;
        switch (choice_logging) {
        case 1:
            if (check_admin())
            {
                adminDashboard();
            }
            break;
        case 2:
        {
            User* logged_IN_user = Check_user();
            if (logged_IN_user)
            {
                User_dashboard(logged_IN_user);
            }
            else
                cout << "Incorrect name or Password" << endl;
        }
        break;
        case 3:
            cout << "Exiting login menu\n";
            break;
        default:
            cout << "invalid choice , try again ";
            break;
        }
    }
}

int main() // main function
{
    defaultBooks();
    bool exit = false;
    int choice_main_menu;
    while (!exit)
    {
        cout << "Welcome to our library \n";
        cout << "1. Log in\n";
        cout << "2. Sign up\n";
        cout << "3. Exit\n";
        cout << "Enter your choice : ";
        cin >> choice_main_menu;
        switch (choice_main_menu)
        {
        case 1:
            handleLogin();
            break;
        case 2:
            add_user();
            break;
        case 3:
            exit = true;
            break;
        default:
            cout << "\ninvalid choice , try again ";
            break;
        }
    }
    return 0;
}