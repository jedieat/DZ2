#ifndef USERS_H
#define USERS_H

#include <string>
#include <vector>
#include <unordered_map>

class Users {
public:
    Users() = default;

    // ���������� ������������
    void addUser(const std::string& name, const std::string& password, int age = 0);

    // �������� ������������� ������������
    bool userExists(const std::string& name) const;

    // �������� ������
    bool checkPassword(const std::string& name, const std::string& password) const;

    // ��������� ID ������������
    int getUserId(const std::string& name) const;

    // ��������� ����� �� ID
    std::string getUserName(int id) const;

    // ��������� ���� �������������
    const std::vector<std::string>& getAllUsers() const;

    // ���������� �������������
    size_t getUserCount() const;

private:
    struct UserInfo {
        std::string name;
        std::string password;
        int age;
    };

    std::vector<UserInfo> users_;
    std::unordered_map<std::string, int> nameToId_; // ��� -> ������ � �������
};

#endif


