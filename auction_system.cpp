#include <iostream>
#include <unordered_map>
#include <map>

class AuctionSystem {
private:
    // Mapea itemId -> {bidAmount -> userId} para ordenar automáticamente de menor a mayor cantidad y manejar empates por userId
    std::unordered_map<int, std::map<int, int>> itemBids;
    
    // Mapea un par único (userId y itemId) -> bidAmount para consultas, actualizaciones y eliminaciones rápidas
    std::unordered_map<long long, int> userItemBid;

    long long getKey(int userId, int itemId) {
        return (static_cast<long long>(userId) << 32) | itemId;
    }

public:
    AuctionSystem() {}
    
    void addBid(int userId, int itemId, int bidAmount) {
        long long key = getKey(userId, itemId);
        
        // Si el usuario ya tenía una puja para este ítem, la removemos antes de agregar la nueva
        if (userItemBid.find(key) != userItemBid.end()) {
            int oldAmount = userItemBid[key];
            itemBids[itemId].erase(oldAmount);
        }
        
        userItemBid[key] = bidAmount;
        itemBids[itemId][bidAmount] = userId;
    }
    
    void updateBid(int userId, int itemId, int newAmount) {
        // Garantizado que la puja existe, por lo que reutilizamos addBid para actualizar de forma limpia
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
        // Como std::map ordena de menor a mayor, el mayor postor está al final
        return itemBids[itemId].rbegin()->second;
    }
};

int main() {
    AuctionSystem auctionSystem;
    auctionSystem.addBid(1, 7, 5);
    auctionSystem.addBid(2, 7, 6);
    std::cout << "Mayor postor para item 7 (Esperado 2): " << auctionSystem.getHighestBidder(7) << std::endl;
    return 0;
}
