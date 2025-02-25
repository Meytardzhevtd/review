#ifndef SOP_HPP_
#define SOP_HPP_

#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <mutex>
#include <cassert>

namespace mtd {
// Структура с тем, что ввел пользователь на какой-то предмет
// Потом добавляется в структуру предмета
struct ResultClass {
    // {оценка 1..5, что нравится, что не равится}
    std::tuple<int, std::string, std::string> lections;

    // {оценка практики, оценка дз, что нравится, что не нравится}
    // групп несколько, поэтому в std::map
    // {name_teacher, tuple}
    std::map<std::string, std::tuple<int, int, std::string, std::string>> practice;

    // доп комментарии
    std::string comments;
};

// Структура отдельного предмета
struct Subject {
    std::string subjectName;
    std::string lecturer;                  // имя лектора
    std::vector<std::string> seminarians;  // имена практиков

    // для каждого прошедшего создается ResultClass и записывается сюда
    std::vector<ResultClass> result;
};

class AllSubjects {
    std::vector<Subject> data;
    std::mutex m;
public:
    inline void add(const Subject &sbj) {
        std::lock_guard<std::mutex> lock(m);
        data.push_back(sbj);
    }
    inline void pop() {
        std::lock_guard<std::mutex> lock(m);
        data.pop_back();
    }
    inline void clear() {
        std::lock_guard<std::mutex> lock(m);
        data.clear();
    }
    inline const Subject &operator[](size_t index) {
        std::lock_guard<std::mutex> lock(m);
        assert(index < data.size());
        return data[index];
    }
    inline size_t size() {
        std::lock_guard<std::mutex> lock(m);
        return data.size();
    }
};

}  // namespace mtd

#endif