//
// Created by saladart on 5/10/19.
//

#ifndef FINAL_SEMESTRAL_WORK_CSPELL_H
#define FINAL_SEMESTRAL_WORK_CSPELL_H


#include <string>
#include <iostream>
#include <iomanip>
#include "CCard.h"
#include "CCreature.h"

/**
 *@brief class represents card of type Spell
 */
class CSpell : public CCard {
public:
    /**
     *@param[in] currCardId card identifier
     *@param[in] currCardName name of Card
     *@param[in] currManaRequired price of card
     *@param[in] currAttackDamage power of the card
     *@param[in] currSelfHarm shows how much damage will get player thrown the card
     */
    CSpell(unsigned int currCardId, const std::string &currCardName, unsigned int currManaRequired,
           unsigned int currAttackDamage,
           unsigned int currSelfHarm);

    /**
     *@returns shared pointer of card with new address
     */
    std::shared_ptr<CCard> Clone() const override;

    /**
     * @brief Method commits attack to player (player loses all mana)
     * @param[in] opponent opponent to attack
     */
    CCard &AttackPlayer(std::shared_ptr<CPlayer> &opponent) override;

    /**
    * @brief Method commits attack to card (card cannot attacks next round)
    * @param[in] opponentCard target card
    */
    CCard &AttackCard(std::shared_ptr<CCard> opponentCard) override;

    void Print();

    //getter
    unsigned int getSelfHarm() const;

private:

    unsigned int selfHarm;
};


#endif //FINAL_SEMESTRAL_WORK_CSPELL_H
