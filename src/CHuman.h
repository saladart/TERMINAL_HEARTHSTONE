//
// Created by saladart on 5/10/19.
//

#ifndef FINAL_SEMESTRAL_WORK_CHUMAN_H
#define FINAL_SEMESTRAL_WORK_CHUMAN_H

class CPlayer;

#include <string>
#include "CPLayer.h"

/**
 *@brief class represents human player
 */
class CHuman : public CPlayer {
public:
    /**
     *@param[in] playerName player's Name
     *@param[in] playerPassword player's password
     */
    CHuman(const std::string &playerName, const std::string &playerPassword);

    /**
     * @param[in] password password typed by the player
     *@returns true if password is correct
     */
    bool CheckPassword(const std::string &password) const;

    //getter
    const std::string &getPlayerPassword() const;


private:
    std::string playerPassword;

};


#endif //FINAL_SEMESTRAL_WORK_CHUMAN_H
