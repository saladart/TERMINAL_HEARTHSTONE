//
// Created by saladart on 5/10/19.
//

#ifndef FINAL_SEMESTRAL_WORK_CWEAPON_H
#define FINAL_SEMESTRAL_WORK_CWEAPON_H


#include <string>
#include "CCard.h"
#include "CCreature.h"

/**
 *class represents Card of type weapon (with number of hits left declared)
 */
class CWeapon : public CCard {
public:
    /**
     *@param[in] currCardId card identifier
     *@param[in] currCardName name of Card
     *@param[in] currManaRequired price of card
     *@param[in] currAttackDamage power of the card
     *@param[in] currHitsLeft shows how many hits you can make with weapon
     */
    CWeapon(unsigned int currCardId, const std::string &currCardName, unsigned int currManaRequired,
            unsigned int currAttackDamage, unsigned int currHitsLeft);

    /**
     *@return returns shared pointer of card with new address
     */
    std::shared_ptr<CCard> Clone() const override;

    /**
     * @brief Method commits attack to player and weapon loses one hit
     * @param[in] opponent opponent to attack
     */
    CCard &AttackPlayer(std::shared_ptr<CPlayer> &opponent) override;

    /**
     * @brief Method commits attack to card and weapon loses one hit
     * @param[in] opponentCard target card
     */
    CCard &AttackCard(std::shared_ptr<CCard> opponentCard) override;

    void Print() override;

    void PrintWeaponInHand();

    //getter
    unsigned int getHitsLeft() const;

private:

    unsigned int hitsLeft;
};


#endif //FINAL_SEMESTRAL_WORK_CWEAPON_H
