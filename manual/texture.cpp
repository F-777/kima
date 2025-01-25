#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
#include <fstream>

// Peta untuk menyimpan tekstur bahan makanan
std::map<std::string, sf::Texture> ingredientTextures;

// Fungsi untuk memuat tekstur bahan makanan
void loadTextures() {
    std::vector<std::string> ingredientNames = {"Carrot", "Tomato", "Potato", "Onion", "Cucumber"};
    for (const auto& name : ingredientNames) {
        sf::Texture texture;
        if (texture.loadFromFile("assets/" + name + ".png")) {
            ingredientTextures[name] = texture;
        } else {
            std::cout << "Error loading texture for " << name << std::endl;
        }
    }
}

struct Ingredient {
    sf::Sprite sprite;   // Sprite untuk bahan makanan
    std::string name;    // Nama bahan
    bool chopped = false;
};

// Fungsi untuk spawn ingredients dengan tekstur
auto spawnIngredients = [&]() {
    ingredients.clear();
    recipeTracker.clear();
    currentRecipe.ingredients.clear();

    std::vector<std::string> ingredientNames = {"Carrot", "Tomato", "Potato", "Onion", "Cucumber"};

    // Pilih bahan untuk resep
    int numIngredients = 3 + level; // Tambahkan bahan seiring naiknya level
    for (int i = 0; i < numIngredients; ++i) {
        std::string ingredientName = ingredientNames[rand() % ingredientNames.size()];
        currentRecipe.ingredients.push_back(ingredientName);
        recipeTracker[ingredientName] = false;
    }

    // Tampilkan resep
    std::string recipeDisplay = "Recipe: ";
    for (const auto& ing : currentRecipe.ingredients) {
        recipeDisplay += ing + " ";
    }
    recipeText.setString(recipeDisplay);

    // Spawn bahan makanan di layar
    for (int i = 0; i < 8; ++i) { // Spawn random ingredients
        Ingredient ingredient;
        ingredient.name = ingredientNames[rand() % ingredientNames.size()];

        // Set sprite dengan tekstur
        if (ingredientTextures.find(ingredient.name) != ingredientTextures.end()) {
            ingredient.sprite.setTexture(ingredientTextures[ingredient.name]);
            ingredient.sprite.setScale(0.5f, 0.5f); // Skala agar tidak terlalu besar
            ingredient.sprite.setPosition(rand() % 700 + 50, rand() % 400 + 100);
        }

        ingredients.push_back(ingredient);
    }
};

