
#include "poker.h"


/*
 *   This file contains poker.h methods implementation
 */


std::vector<int> hold_single_hand(const std::vector<Player>& players, const std::vector<Card>& flops) {
    return hold_single_hand(Match(players, flops));
}

std::vector<int> hold_single_hand(const Match& match) {
    Match tmp(match);
    tmp.augment_to_det();
    return tmp.get_winners();
}


std::vector<double> calculate_pr(const std::vector<Player>& players, const std::vector<Card>& flops,
        SAMPLE_SIZE sample_size=SAMPLE_SIZE::SMALL) {
    return calculate_pr(Match(players, flops), sample_size);
}

std::vector<double > calculate_pr(const Match& match, SAMPLE_SIZE sample_size=SAMPLE_SIZE::SMALL) {
    return match.calc_chances(sample_size);
}



