//
// Created by saladart on 5/10/19.
//

#include "CHuman.h"




CHuman::CHuman(const std::string &playerName, const std::string &playerPassword) : CPlayer(playerName),
                                                                                   playerPassword(playerPassword) {}
bool CHuman::CheckPassword(const std::string & password) const {
    return password == playerPassword;
}

const std::string &CHuman::getPlayerPassword() const {
    return playerPassword;
}


