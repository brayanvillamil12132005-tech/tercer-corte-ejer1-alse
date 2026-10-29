#include <vector>
#include <iostream>

class ATM {
private:
    std::vector<long long> count;
    const std::vector<int> values = {20, 50, 100, 200, 500};

public:
    ATM() : count(5, 0) {}
    
    void deposit(std::vector<int> banknotesCount) {
        for (int i = 0; i < 5; ++i) {
            count[i] += banknotesCount[i];
        }
    }
    
    std::vector<int> withdraw(int amount) {
        std::vector<int> give(5, 0);
        long long rem = amount;
        
        for (int i = 4; i >= 0; --i) {
            if (rem <= 0) break;
            long long needed = rem / values[i];
            long long take = std::min(needed, count[i]);
            give[i] = take;
            rem -= take * values[i];
        }
        
        if (rem > 0) {
            return {-1};
        }
        
        for (int i = 0; i < 5; ++i) {
            count[i] -= give[i];
        }
        
        return give;
    }
};

int main() {
    ATM atm;
    atm.deposit({0, 0, 1, 2, 1});
    auto res1 = atm.withdraw(600);
    std::cout << "Prueba de retiro ejecutada con exito." << std::endl;
    return 0;
}
