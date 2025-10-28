#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>

struct Message {
    int senderId;
    int receiverId; // -1 ��� ��������� ���������
    std::string content;
    int timestamp; // ������� �������� timestamp

    Message(int sender, int receiver, const std::string& msg, int time = 0)
        : senderId(sender), receiverId(receiver), content(msg), timestamp(time) {}
};

class MessageManager {
public:
    // �������� ��������� ������������
    void sendMessage(int senderId, int receiverId, const std::string& content);

    // �������� ���������� ���������
    void broadcastMessage(int senderId, const std::string& content);

    // ��������� ��������� ��� ������������
    std::vector<Message> getMessagesForUser(int userId) const;

    // ��������� ���� ��������� (��� �������)
    const std::vector<Message>& getAllMessages() const;

private:
    std::vector<Message> messages_;
    static int messageCounter_; // ������� ��� ��������� timestamp
};

#endif
