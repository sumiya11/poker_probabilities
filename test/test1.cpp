
#include <iostream>
#include "../src/poker.h"



int main() {

    auto players = std::vector<Player>{
        Player(Card("HA"), Card("DK")), Player(Card("S3"), Card("CT"))
    };
    auto drawn_cards = std::vector<Card>{Card("SA"), Card("-"), Card("-"), Card("-"), Card("-")};

    auto winners = hold_single_hand(players, drawn_cards);
    for (auto i : winners) {
        std::cout << i << std::endl;
    }


    return 0;
}