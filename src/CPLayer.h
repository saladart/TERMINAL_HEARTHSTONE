//
// Created by saladart on 5/10/19.
//

#ifndef FINAL_SEMESTRAL_WORK_CPLAYER_H
#define FINAL_SEMESTRAL_WORK_CPLAYER_H

class CDeck;
class CGame;

/**
 * @brief calss represents a player in the game and has two subclasses (CHuman and CComputer)
 */
#include <memory>
#include "CDeck.h"
//#include "CGame.h"


class CPlayer {
public:
    /**
     *@param[in] playerName name of the player
     */
    explicit CPlayer(const std::string &playerName);
    /**
     *@brief method commits throwing card to the table (find it firs and put to appropriate place)
     * @param[in] currTable set of card where we are putting the card
     * @param[out] cardFound true if card was found in players hand
     * @param[out] enoughMana true if player has enough mana to throw the card
     * @param[out] isSpell true if thrown card has spell type
     * @param[in] id of card to throw
     */
    CPlayer & ThrowCard (std::list<std::shared_ptr<CCard>> &  currTable,  bool & cardFound, bool & enoughMana, bool & isSpell,  const unsigned int cardId);
    /**
     * @param[in] currHarm damage which gets the player
0     */
    CPlayer & GetHit (unsigned int currHarm);
    /**
     * @brief method commits attack to an opponent with players weapon
     * @param[in] opponent target player
     */
    CPlayer & AttackOtherPLayer (std::shared_ptr<CPlayer> & opponent);
    /**
     * @brief method commits attack to an opponent card with players weapon
     * @param[in] opponentCard opponent card to attack
     */
    CPlayer & AttackCard (std::shared_ptr<CCard> &opponentCard);
    /**
     *@brief player takes currDeck
     * @param[in] currDeck deck to take
     */
    CPlayer & TakeDeck(const std::shared_ptr<CDeck> &currDeck);
    /**
     *@brief player takes N cards from Deck
     * @param[in] numberOfCards number of cards to take
     */
    CPlayer & TakeNCardsFromDeck (unsigned int numberOfCards);
    /**
     *@brief method prints characteristics of player
     */
    void PrintCharacteristics();
    /**
     * @brief method prints the whole hand of player
     */
    void PrintHand() const;
    /**
     * @brief method deletes the card from hand
     * @param[in] currCard card to delete
     */
    CPlayer & DeleteCardFromHand (std::shared_ptr<CCard> &currCard);
    /**
     * @brief sets current hand for player (method for loading the game)
     * @param[in] currentHand list of card to set the hand
     */
    void setCurrentHand(const std::list<std::shared_ptr<CCard>> &currentHand);

    //Setters
    CPlayer & setMana (unsigned int Mana);
    void setHealthPoints(unsigned int healthPoints);
    void setPlayersWeapon(const std::shared_ptr<CCard> &playersWeapon);
    void setHaveWeapon(bool haveWeapon);
    //Getters
    unsigned int getHealthPoints() const;
    const std::shared_ptr<CDeck> &getPlayersDeck() const;
    bool isAlive ();
    bool HaveWeapon() const;
    virtual const std::string &getPlayerName() const;
    const std::shared_ptr<CCard> &getPlayersWeapon() const;
    const std::list<std::shared_ptr<CCard>> &getCurrentHand() const;

    unsigned int getCurrentMana() const;

private:
    std::shared_ptr<CDeck> playersDeck;
    std::list<std::shared_ptr<CCard>> currentHand;
    std::shared_ptr<CCard> playersWeapon;
    unsigned int healthPoints = 30;
    bool haveWeapon = false;
    std::string playerName;
    unsigned int currentMana = 0;
};
#endif //FINAL_SEMESTRAL_WORK_CPLAYER_H
