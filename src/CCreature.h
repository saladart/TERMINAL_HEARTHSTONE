//
// Created by saladart on 5/10/19.
//

#ifndef FINAL_SEMESTRAL_WORK_CCREATURE_H
#define FINAL_SEMESTRAL_WORK_CCREATURE_H

#include <string>
#include <iostream>
#include <iomanip>
#include <iostream>
#include "CCard.h"

/**
 *@brief represent Card of type creature. Creatures attack better with higher level of HP. Got extra attribute healthLevel;
 */
class CCreature : public CCard {
public:
    /**
     *@param[in] currCardId card identifier
     *@param[in] currCardName name of Card
     *@param[in] currManaRequired price of card
     *@param[in] currAttackDamage power of the card
     *@param[in] currCardHealthLevel hp of the card
     */
    CCreature(unsigned int currCardId, const std::string &currCardName, unsigned int currManaRequired,
              unsigned int currAttackDamage, unsigned int currCardHealthLevel);

    /**
     *@returns returns shred pointer of card with new address
     */
    std::shared_ptr<CCard> Clone() const override;

    /**
     * @brief decrease hp when card is attacked
     * @param[in] damage damage that card gets
     */
    CCreature &GetHit(const unsigned int damage);

    /**
     * @brief Method commits attack to player
     * @param[in] opponent opponent to attack
     */
    CCard &AttackPlayer(std::shared_ptr<CPlayer> &opponent) override;

    /**
     * @brief Method commits attack to card
     * @param[in] opponentCard target card
     */
    CCard &AttackCard(std::shared_ptr<CCard> opponentCard) override;

    void Print() override;

    //getter
    unsigned int getHealthLevel() const;

    //setter
    void setHealthLevel(unsigned int healthLevel);

private:

    unsigned int healthLevel;
};


#endif //FINAL_SEMESTRAL_WORK_CCREATURE_H
