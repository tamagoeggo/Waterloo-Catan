#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
enum class Player {Blue, Red, Orange, Yellow, None};

std::ostream &operator<<(std::ostream &out, const Player &player) const{
    if (player == Player::Blue) {
        return out << "Blue";
    }
    else if (player == Player::Red) {
        return out << "Red";
    }
    else if (player == Player::Orange) {
        return out << "Orange";
    }
    else if (player == Player::Yellow) {
        return out << "Yellow";
    }
    else {
        return out << "Throw an exception in player ostream overload";
    }
}

#endif
