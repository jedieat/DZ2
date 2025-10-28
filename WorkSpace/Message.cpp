#include "Message.h"

void MessageManager::sendMessage(int senderId, int receiverId, const std::string& content) {
    messages_.emplace_back(senderId, receiverId, content);
}

void MessageManager::broadcastMessage(int senderId, const std::string& content) {
    // -1 означает групповое сообщение
    messages_.emplace_back(senderId, -1, content);
}

std::vector<Message> MessageManager::getMessagesForUser(int userId) const {
    std::vector<Message> userMessages;

    for (const auto& msg : messages_) {
        if (msg.receiverId == userId || msg.receiverId == -1) {
            userMessages.push_back(msg);
        }
    }

    return userMessages;
}

const std::vector<Message>& MessageManager::getAllMessages() const {
    return messages_;
}