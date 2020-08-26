
#include <iostream>
#include "../src/poker.h"



void test_single_hand() {
    auto players = std::vector<Player>{
            Player(Card("HA"), Card("DK")),
            Player(Card("S3"), Card("CT"))
    };
    auto drawn_cards = std::vector<Card>{Card("SA"), Card("-"), Card("-"),
                                         Card("-"), Card("-")};

    auto winners = hold_single_hand(players, drawn_cards);
    for (auto i : winners) {
        std::cout << i << "\t";
    } std::cout << std::endl;
}


void test_single_probabilities() {
    auto players = std::vector<Player>{
            Player(Card("HA"), Card("DK")),
            Player(Card("S3"), Card("CT"))
    };
    auto drawn_cards = std::vector<Card>{Card("S3"), Card("-"),
                                         Card("-"), Card("-"), Card("-")};

    auto chances = calculate_pr(players, drawn_cards, SAMPLE_SIZE::AVR);
    for (auto i : chances) {
        std::cout << i << "\t";
    } std::cout << std::endl;
}





int main() {

    test_single_hand();
    test_single_probabilities();


    return 0;
}

