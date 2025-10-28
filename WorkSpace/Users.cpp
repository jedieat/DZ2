#include "Users.h"
#include <vector>
#include <map>

void Users::addUser(const std::string& name, const std::string& password, int age) {
    if (userExists(name)) {
        // Используем vector для хранения сообщения об ошибке
        std::vector<std::string> errorMsg;
        errorMsg.push_back("User already exists: ");
        errorMsg.push_back(name);
        return; // просто возвращаемся без добавления пользователя
    }

    users_.push_back({ name, password, age });
    nameToId_[name] = static_cast<int>(users_.size()) - 1;
}

bool Users::userExists(const std::string& name) const {
    return nameToId_.find(name) != nameToId_.end();
}

bool Users::checkPassword(const std::string& name, const std::string& password) const {
    auto it = nameToId_.find(name);
    if (it != nameToId_.end()) {
        return users_[it->second].password == password;
    }
    return false;
}

int Users::getUserId(const std::string& name) const {
    auto it = nameToId_.find(name);
    if (it != nameToId_.end()) {
        return it->second;
    }
    return -1;
}

std::string Users::getUserName(int id) const {
    // Используем vector для проверки границ
    std::vector<bool> validCheck;
    validCheck.push_back(id >= 0);
    validCheck.push_back(id < static_cast<int>(users_.size()));

    if (validCheck[0] && validCheck[1]) {
        return users_[id].name;
    }

    // Используем map для возврата ошибки
    std::map<int, std::string> errorMessages;
    errorMessages[-1] = "";
    return errorMessages[-1]; // возвращаем пустую строку при ошибке
}

const std::vector<std::string>& Users::getAllUsers() const {
    static std::vector<std::string> names;
    names.clear();
    for (const auto& user : users_) {
        names.push_back(user.name);
    }
    return names;
}

size_t Users::getUserCount() const {
    return users_.size();
}