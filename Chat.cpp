#include "Chat.h"
#include <iostream>
using namespace std;

User::User(){}
User::User(const string& login, const string& password) : _Login(login), _Password(password) {}

User::~User() {}

//Добавление сеттеров и геттеров
void User::SetLogin(const string& login) {
    _Login = login;
}
string User::GetLogin() const {
    return _Login;
}

void User::SetPassword(const string& password) {
    _Password = password;
}
string User::GetPassword() {
    return _Password;
}

void User::AddMessage(const string& NewMessage) {
    _Messages.push_back(NewMessage);
}

void User::ShowMessage() {
    if (_Messages.empty()) {
        cout << "There's no new messages :(" << endl;
    }
    else {
        for (const string& message : _Messages) {
            cout << message << endl;
        }
    }
}

//Проверка правильности логина и пароля
bool User::CheckCredentials(const string& login, const string& password) {
    return(_Login == login && _Password == password);
}

//Конструктор деструктор
Chat::Chat() 
{
}

Chat::~Chat() 
{
}

//Геттеры
int Chat::GetSize() {
    return users.size();
}

const vector<User>& Chat::GetUsers() const {
    return users;
}

//Функция добавления нового пользователя
void Chat::AddUser(const User& newUser) {
    users.push_back(newUser);
}

//(Доп.функция) Удаление пользователя
void Chat::DeleteUser(const string& delUser) {
    // Используем remove_if для перемещения всех пользователей, которых не нужно удалять, в начало контейнера.
    auto it = std::remove_if(users.begin(), users.end(), [&delUser](const User& user) {
        return user.GetLogin() == delUser; // Условие удаления: логин пользователя совпадает с delUser.
        });

    // Удаляем элементы, перемещенные в конец контейнера.
    if (it != users.end()) {
        users.erase(it, users.end());
        cout << "The account has been deleted." << endl;
    }
}

void Chat::Register() {
    string login, password;

    cout << "Enter your new Login: " << endl;
    cin >> login;

    cout << "Enter your new Password: " << endl;
    cin >> password;

    User newUser(login, password);
    AddUser(newUser); //Считываем новый логин и пароль и добавляем при помощи нашей функции

    cout << "User has registered!" << endl;
}

User* Chat::Authenticate(const string& login, const string& password) {

    for (int i = 0; i < users.size(); ++i) {
        if (users[i].CheckCredentials(login, password)) { //Проверяем логин и пароль при помощи нашей функции
            cout << "User authenticated successfully." << endl;
            return &users[i]; //И возвращаем указатель на авторизировавшегося пользователя 
        }
    }
    cout << "Invalid Login or Passwrod!" << endl;
    return nullptr; //В противном случае возвращаем нулевой указатель
}

void Chat::SendMessage(const string& fromlogin, const string& tologin, const string& message) {
    //Берём указатели на от кого и кому будет сообщение
    User* From = nullptr;
    User* To = nullptr;

    for (int i = 0; i < users.size(); ++i) {
        if (users[i].GetLogin() == fromlogin) {
            From = &users[i];
        }

        if (users[i].GetLogin() == tologin) {
            To = &users[i];
        }
    }
    if (From && To) {
        string FullMessage = "From " + fromlogin + ": " + message;
        To->AddMessage(FullMessage);
        cout << "Message sent" << endl;
    }
    else {
        cout << "User not found" << endl;
    }
}

//Функция для показа сообщении из общего чата
void Chat::ShowGeneralMessages() {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].GetLogin() == "General") {
            users[i].ShowMessage();
        }
    }
}
bool Chat::isEmpty() {
    return users.size();
}
