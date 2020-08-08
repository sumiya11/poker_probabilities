
#include <iostream>
#include "headers/main_classes.h"


void process() {


    std::vector<Player> players;
    std::vector<Card> flops;

    {
        size_t n;
        std::cout << "players count...\n";
        std::cin >> n;
        players.resize(n);
    }
    {
        std::cout << "player_1 is assigned to you. \n(format: '[H-D-C-S] + [2-T-A]' OR '-' ; gap=space)\n";
        for (size_t i = 1; i <= players.size(); i ++) {
            std::cout << "player_" + std::to_string(i)  + " cards (2)... \n";
            std::string term1, term2;
            std::cin >> term1 >> term2;
            players[i - 1].assign_cards(Card(term1), Card(term2));
        }
    }
    {
        std::cout << "Flop|Turn|River cards (5)...\n";
        std::string term1, term2, term3, term4, term5;
        std::cin >> term1 >> term2 >> term3 >> term4 >> term5;
        flops = {Card(term1), Card(term2), Card(term3), Card(term4), Card(term5)};
    }

    Match match(players, flops);

    auto chances = match.calc_chances(poker_const::SAMPLE_SIZE::size_2);
    for (double p : chances) {
        std::cout << 100 * p << " %" << " -- ";
    }


}

int main() {

    process();

    return 0;
}