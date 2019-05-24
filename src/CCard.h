//
// Created by saladart on 5/10/19.
//

#ifndef FINAL_SEMESTRAL_WORK_CCARD_H
#define FINAL_SEMESTRAL_WORK_CCARD_H

/**
 * @brief Class represents the card
*/
class CPlayer;

#include <string>
#include <memory>
#include "CPLayer.h"


class CCard {
public:
    /**
     *@param[in] currCardId card identifier
     *@param[in] currCardName name of Card
     *@param[in] currManaRequired price of card
     * @param[in] currAttackDamage power of the card
     */
    CCard(unsigned int currCardId, const std::string &currCardName, unsigned int currManaRequired,
          unsigned int currAttackDamage);

    /**
     *@return returns shared pointer of card with new address
     */
    virtual std::shared_ptr<CCard> Clone() const = 0;

    /**
     * @brief Method commits attack to player
     * @param[in] opponent opponent to attack
     */
    virtual CCard &AttackPlayer(std::shared_ptr<CPlayer> &opponent) = 0;

    /**
     * @brief Method commits attack to card
     * @param[in] opponentCard target card
     */
    virtual CCard & AttackCard(std::shared_ptr<CCard> opponentCard) = 0;

    virtual void Print() = 0;

    bool isReadyToAttack() const;

    /**
     * @brief Method changes readiness of card to attack
     *@param[in] readyToAttack new state of card
     */
    //Setter
    void setReadyToAttack(bool readyToAttack);

    //Getters
    unsigned int getManaRequired() const;

    unsigned int getCardId() const;

    const std::string &getCardName() const;

    unsigned int getAttackDamage() const;


protected:
    unsigned int cardId;
    std::string cardName;
    bool readyToAttack = false;
    unsigned int manaRequired,
            attackDamage;
};


#endif //FINAL_SEMESTRAL_WORK_CCARD_H
