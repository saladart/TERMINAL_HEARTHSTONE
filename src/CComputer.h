//
// Created by saladart on 5/10/19.
//

#ifndef FINAL_SEMESTRAL_WORK_CCOMPUTER_H
#define FINAL_SEMESTRAL_WORK_CCOMPUTER_H

/**
 * @brief Class represents bot
 */
class CPlayer;

#include "CPLayer.h"

class CComputer : public CPlayer {
public:
    /**
     *@param[in] pcName players name
     */
    CComputer(std::string pcName) : CPlayer(pcName) {}

    /**
     * @brief Computes suitable bot turn
     *
     * @param[in]cardsOnTableP1 set of cards on table thrown by player 1
     * @param[in]cardsOnTableP2 set of cards on table thrown by player 2
     * @param[out] playerAttacks flag has true value if player is attacking
     * @param[out] attackCard flag has true value if card is attacked
     * @param[out] endTurn flag has true value if player finishes his turn
     * @param[out] throwCard flag has true value if player throws a card
     * @param[out] target shows the turn target (card to throw/ attack target)
     * @param[out] attacker attacker card
     */
    void
    DoSomething(std::list<std::shared_ptr<CCard>> cardsOnTableP1, std::list<std::shared_ptr<CCard>> &cardsOnTableP2,
                bool &playerAttacks, bool &attackCard, bool &endTurn, bool &throwCard,
                std::pair<std::shared_ptr<CCard>, unsigned int> &target,
                std::pair<std::shared_ptr<CCard>, unsigned int> &attacker);

    /**
     * @brief checks if there're ready cards to attack on table
     * @param[in] cardsOnTable set of cards on table
     * @return true if there is at least one card ready to attack
     */
    bool isReadyCards(std::list<std::shared_ptr<CCard>> cardsOnTable);
};


#endif //FINAL_SEMESTRAL_WORK_CCOMPUTER_H
