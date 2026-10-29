#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

class clock_class {
private:
    int minutes;

    void normalize() {
        int total_mins = minutes % (24 * 60);
        if (total_mins < 0) {
            total_mins += 24 * 60;
        }
        minutes = total_mins;
    }

public:
    clock_class(int hour, int minute) {
        minutes = hour * 60 + minute;
        normalize();
    }

    clock_class add(int minutes_to_add) const {
        clock_class new_clock(0, minutes + minutes_to_add);
        return new_clock;
    }

    clock_class subtract(int minutes_to_subtract) const {
        clock_class new_clock(0, minutes - minutes_to_subtract);
        return new_clock;
    }

    std::string to_string() const {
        int h = minutes / 60;
        int m = minutes % 60;
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << h << ":"
            << std::setfill('0') << std::setw(2) << m;
        return oss.str();
    }

    bool operator==(const clock_class& other) const {
        return minutes == other.minutes;
    }

    bool operator!=(const clock_class& other) const {
        return minutes != other.minutes;
    }
};

int main() {
    clock_class my_clock(10, 30);
    auto updated_clock = my_clock.add(90);
    std::cout << "Reloj inicial (10:30) + 90 mins: " << updated_clock.to_string() << std::endl;
    return 0;
}
