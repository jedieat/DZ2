#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>

struct Message {
    int senderId;
    int receiverId; // -1 для групповых сообщений
    std::string content;
    int timestamp; // простой числовой timestamp

    Message(int sender, int receiver, const std::string& msg, int time = 0)
        : senderId(sender), receiverId(receiver), content(msg), timestamp(time) {}
};

class MessageManager {
public:
    // Отправка сообщения пользователю
    void sendMessage(int senderId, int receiverId, const std::string& content);

    // Отправка группового сообщения
    void broadcastMessage(int senderId, const std::string& content);

    // Получение сообщений для пользователя
    std::vector<Message> getMessagesForUser(int userId) const;

    // Получение всех сообщений (для отладки)
    const std::vector<Message>& getAllMessages() const;

private:
    std::vector<Message> messages_;
    static int messageCounter_; // счетчик для генерации timestamp
};

#endif
