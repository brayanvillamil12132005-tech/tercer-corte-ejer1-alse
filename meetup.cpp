#include <iostream>
#include <string>
#include <ctime>

class meetup {
private:
    int year;
    int month;

    int getDayOfWeek(int d, int m, int y) const {
        struct tm t = {0};
        t.tm_year = y - 1900;
        t.tm_mon = m - 1;
        t.tm_mday = d;
        mktime(&t);
        return t.tm_wday;
    }

public:
    meetup(int m, int y) : month(m), year(y) {}

    std::string findTeenth(int targetWday) const {
        for (int d = 13; d <= 19; ++d) {
            if (getDayOfWeek(d, month, year) == targetWday) {
                return std::to_string(year) + "-" + 
                       (month < 10 ? "0" : "") + std::to_string(month) + "-" + 
                       (d < 10 ? "0" : "") + std::to_string(d);
            }
        }
        return "";
    }
};

int main() {
    meetup m(8, 1953);
    std::string resultado = m.findTeenth(6);
    std::cout << "Meetup ejecutado correctamente: " << resultado << std::endl;
    return 0;
}
