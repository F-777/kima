#include "GameLogic.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Constructor
GameLogic::GameLogic() : lives(3), score(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    spawnIngredients();
}

// Spawn random ingredients
void GameLogic::spawnIngredients() {
    ingredients.clear();
    currentRecipe = {"Carrot", "Tomato", "Potato"};
    for (int i = 0; i < 5; ++i) {
        std::string ingredientName = currentRecipe[std::rand() % currentRecipe.size()];
        ingredients.emplace_back(ingredientName);
    }
}

// Chop an ingredient
void GameLogic::chopIngredient(int index) {
    if (index < 0 || index >= ingredients.size()) return;

    Ingredient& ingredient = ingredients[index];
    if (!ingredient.chopped) {
        ingredient.chopped = true;
        score += 10;
    }
}

// Getters
std::vector<Ingredient>& GameLogic::getIngredients() {
    return ingredients;
}

int GameLogic::getLives() const {
    return lives;
}

int GameLogic::getScore() const {
    return score;
}

bool GameLogic::isGameOver() const {
    return lives <= 0;
}
