#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>
#include <string>
#include "Ingredient.h"

class GameLogic {
private:
    std::vector<Ingredient> ingredients;
    std::vector<std::string> currentRecipe;
    int lives;
    int score;

public:
    GameLogic();
    void spawnIngredients();
    void chopIngredient(int index);
    std::vector<Ingredient>& getIngredients();
    int getLives() const;
    int getScore() const;
    bool isGameOver() const;
};

#endif // GAMELOGIC_H
