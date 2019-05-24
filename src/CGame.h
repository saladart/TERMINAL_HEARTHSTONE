//
// Created by saladart on 5/10/19.
//

#ifndef FINAL_SEMESTRAL_WORK_CGAME_H
#define FINAL_SEMESTRAL_WORK_CGAME_H
class CPlayer;
#include <iostream>
#include <fstream>
#include <algorithm>
#include "CCreature.h"
#include "CWeapon.h"
#include "CSpell.h"
#include "CHuman.h"
#include "CPLayer.h"
#include "CComputer.h"
#include "CDeck.h"
#include <cstdlib>
#include <unistd.h>
/**
 *@brief class represents game class and common stuff (table etc)
 */
class CGame {
public:
    /**
     * @brief initialize game and chose if it is the new game of loaded one
     */
    void InitGame();
    /**
     *@brief choose mode (Player vs Player or Player vs Computer)
     */
    CGame &ChooseMode();
    /**
     * @brief reads decks from file Decks.txt
     */
    CGame & ReadDecks ();
    /**
     * Uploads game from file save.txt
     */
    CGame & UploadGame ();
    void GameLoop ();
    /**
     * @brief prints table template
     */
    void PrintTable () const;
    /**
     * @brief prints cards on table
     */
    void PrintCardsOnTable() const;
    /**
     * @brief updates cards on table (Delete dead ones and add new ones)
     */
    CGame & UpdateCardsOnTable();
    /**
     * @brief method process player's input
     * @param[in] thrownByPLayer1 shows whose turn it is
     * @param[out] isEnd if player finished his turn
     * @param[out] isSave if player Saved game
     */
    CGame & HandleEvents(bool thrownByPLayer1, bool &isEnd, bool & isSave);
    /**
     *@brief in the end of turn method sets all cards ready to attack
     */
    CGame & SetCardsReady();
    /**
     * @brief finds out if there's any ready cards to attack
     * @param[in] thrownByPlayer1 shows whose turn it is
     * @returns true if there's at least one ready card
     */
    bool IsThereAnyReadyCards(bool thrownByPlayer1);
    /**
     * @brief loop of Human player turn
     * @param[in] player1Turn shows whose turn it is
     * @param[out] isSave flag is true if player saved game
     */
    CGame & PLayerTurn(bool player1Turn, bool & isSave);
    /**
     * @brief writes data to file save.txt
     */
    void SaveGame();
    /**
     * @brief gets player's input and define if this is correct target for attack
     * @param[in] attacker string with player's input
     * @param[in] thrownByPLayer1 shows whose turn it is
     * @returns true if attacker is correct
     */
    bool DefineAttacker(std::string & attacker, bool thrownByPLayer1 ) ;
    /**
     * @brief gets player's input and define if this is correct attacker for attack
     * @param[in] target string with player's input
     * @returns true if target is correct
     */
    bool DefineTarget(std::string & target);
    /**
     * @brief finds cards on table
     * @param[out] currentCard card to return
     * @param[in] buffId id of card to find on the table
     * @param[in] deckOfPlayer1 true if we search for card in PLayer 1 hand
     */
    bool FindCardOnTable (std::shared_ptr<CCard> & currentCard, unsigned int buffId, bool deckOfPlayer1) const;
private:
    std::shared_ptr<CPlayer>  player1, player2;
    unsigned int mana;
    bool isRunning, isPvP, isLoaded;
    std::list<CDeck> playingDecks;
    std::list<std::shared_ptr<CCard>> cardsOnTableP1, cardsOnTableP2;
};


#endif //FINAL_SEMESTRAL_WORK_CGAME_H
