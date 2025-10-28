#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Users.h"
#include "Message.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");

    cout << "==================================" << endl;
    cout << "Собираем базу пользователей" << endl;
    cout << "Введите количество пользователей:" << endl;

    int user_number;
    cin >> user_number;

    Users users;
    MessageManager messageManager;

    // Регистрация пользователей
    for (int i = 0; i < user_number; i++) {
        string user_name, user_password;

        cout << "Введите имя пользователя " << i + 1 << endl;
        cin >> user_name;
        cout << "Введите пароль " << i + 1 << endl;
        cin >> user_password;

        try {
            users.addUser(user_name, user_password);
            cout << "Пользователь " << user_name << " успешно зарегистрирован" << endl;
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            i--; // Повторяем ввод для этого пользователя
        }
    }

    // Основной цикл чата
    while (true) {
        cout << "==================================" << endl;
        cout << "Верификация пользователя" << endl;
        cout << "Логин (или 'exit' для выхода):" << endl;

        string current_user;
        cin >> current_user;

        if (current_user == "exit") {
            break;
        }

        if (!users.userExists(current_user)) {
            cout << "Пользователь не найден" << endl;
            continue;
        }

        cout << "Пароль:" << endl;
        string current_password;
        cin >> current_password;

        if (!users.checkPassword(current_user, current_password)) {
            cout << "Пароль неверный" << endl;
            continue;
        }

        int currentUserId = users.getUserId(current_user);
        cout << "Добро пожаловать, " << current_user << "!" << endl;

        // Показываем новые сообщения
        auto userMessages = messageManager.getMessagesForUser(currentUserId);
        if (!userMessages.empty()) {
            cout << "--- Новые сообщения ---" << endl;
            for (const auto& msg : userMessages) {
                string senderName = users.getUserName(msg.senderId);
                cout << "От " << senderName << ": " << msg.content << endl;
            }
            cout << "-----------------------" << endl;
        }
        else {
            cout << "Новых сообщений нет" << endl;
        }

        // Отправка сообщений
        cout << "Кому отправить сообщение (введите имя адресата или 'all' для групповой отправки, или 'back' для выхода):" << endl;
        string recipient;
        cin >> recipient;

        if (recipient == "back") {
            continue;
        }

        if (recipient == "all") {
            cout << "Введите сообщение для всех:" << endl;
            string message;
            cin.ignore(); // Очищаем буфер
            getline(cin, message);

            messageManager.broadcastMessage(currentUserId, message);
            cout << "Сообщение отправлено всем пользователям" << endl;
        }
        else {
            if (!users.userExists(recipient)) {
                cout << "Пользователь не найден" << endl;
                continue;
            }

            if (recipient == current_user) {
                cout << "Нельзя отправить сообщение самому себе" << endl;
                continue;
            }

            cout << "Введите сообщение для " << recipient << ":" << endl;
            string message;
            cin.ignore(); // Очищаем буфер
            getline(cin, message);

            int recipientId = users.getUserId(recipient);
            messageManager.sendMessage(currentUserId, recipientId, message);
            cout << "Сообщение отправлено пользователю " << recipient << endl;
        }
    }

    cout << "До свидания!" << endl;
    return 0;
}