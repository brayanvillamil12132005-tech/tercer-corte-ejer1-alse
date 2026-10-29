#include <iostream>
#include <unordered_map>
#include <map>

class AuctionSystem {
private:
    std::unordered_map<int, std::map<int, int>> itemBids;
    std::unordered_map<long long, int> userItemBid;

    long long getKey(int userId, int itemId) {
        return (static_cast<long long>(userId) << 32) | itemId;
    }

public:
    AuctionSystem() {}
    
    void addBid(int userId, int itemId, int bidAmount) {
        long long key = getKey(userId, itemId);
        if (userItemBid.find(key) != userItemBid.end()) {
            int oldAmount = userItemBid[key];
            itemBids[itemId].erase(oldAmount);
        }
        userItemBid[key] = bidAmount;
        itemBids[itemId][bidAmount] = userId;
    }
    
    void updateBid(int userId, int itemId, int newAmount) {
        addBid(userId, itemId, newAmount);
    }
    
    void removeBid(int userId, int itemId) {
        long long key = getKey(userId, itemId);
        if (userItemBid.find(key) != userItemBid.end()) {
            int amount = userItemBid[key];
            userItemBid.erase(key);
            itemBids[itemId].erase(amount);
        }
    }
    
    int getHighestBidder(int itemId) {
        if (itemBids.find(itemId) == itemBids.end() || itemBids[itemId].empty()) {
            return -1;
        }
        return itemBids[itemId].rbegin()->second;
    }
};

int main() {
    AuctionSystem auctionSystem;
    auctionSystem.addBid(1, 7, 5);
    std::cout << "Auction System ejecutado correctamente." << std::endl;
    return 0;
}
