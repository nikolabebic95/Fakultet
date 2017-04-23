#include "Semaphore.h"

static const size_t NUMBER_OF_PLAYERS=4;

static Semaphore mutexes[NUMBER_OF_PLAYERS];
static Semaphore semaphores[NUMBER_OF_PLAYERS];
static bool game_over=false;

/**
 * \brief Checks if player won
 * \param index Index of player
 * \return Boolean value indicating whether the player won 
 */
bool checkWin(size_t index);

/**
 * \brief Takes card from the right pile
 * \param index Index of player
 */
void takeCard(size_t index);

/**
 * \brief Puts card to the left pile
 * \param index Index of player
 * \param card Index of card
 */
void putCard(size_t index, size_t card);

/**
 * \brief Decides which card to release
 * \param index Index of player
 * \return Index of card
 */
size_t decide(size_t index);

void cardsPlayerProcess(size_t index){
    while(true){
        if (checkWin(index)){
            game_over=true;
            for(auto& semaphore: semaphores){
                semaphore.signal();
            }
            
            for(auto& mutex: mutexes)
                mutex.signal();
            break;
        }
        else {
            auto left=index;
            auto right=(index+1)%NUMBER_OF_PLAYERS;
            auto card=decide(index);

            if(game_over)
                break;
                
            mutexes[left].wait();
            if(game_over)
                break;
            putCard(index, card);
            semaphores[left].signal();
            mutexes[left].signal();
            
            semaphores[right].wait();
            mutexes[right].wait();
            if(game_over)
                break;
            takeCard(index);
            mutexes[right].signal();
        }   
    }
}

void initialize(){
    for(auto& semaphore: semaphores){
        semaphore.signal();
        semaphore.signal();
    }

    for(auto& mutex: mutexes)
        mutex.signal();
}
