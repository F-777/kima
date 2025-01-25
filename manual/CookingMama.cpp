#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include <fstream>

// Struct untuk bahan makanan
struct Ingredient {
    sf::RectangleShape shape;
    std::string name; // Nama bahan
    bool chopped = false;
};

// Struct untuk resep
struct Recipe {
    std::vector<std::string> ingredients; // Bahan yang dibutuhkan
};

int main() {
    // Setup window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cooking Game with Recipes");
    window.setFramerateLimit(60);

    // Variables for game state
    int score = 0;
    float timer = 30.0f; // 30 seconds per recipe
    int level = 1;
    bool gameOver = false;
    std::vector<Ingredient> ingredients;
    sf::Font font;
    font.loadFromFile("arial.ttf"); // Make sure you have an appropriate font file

    // Recipe management
    Recipe currentRecipe;
    std::map<std::string, bool> recipeTracker; // Track ingredients used
    bool recipeCompleted = false;

    // Sound effects
    sf::SoundBuffer chopSoundBuffer, gameOverSoundBuffer;
    chopSoundBuffer.loadFromFile("chop.wav"); // Add your own sound file
    gameOverSoundBuffer.loadFromFile("gameover.wav");
    sf::Sound chopSound(chopSoundBuffer);
    sf::Sound gameOverSound(gameOverSoundBuffer);

    // Text elements
    sf::Text scoreText, timerText, gameOverText, levelText, recipeText, restartText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10, 10);

    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(650, 10);

    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::Blue);
    levelText.setPosition(350, 10);

    recipeText.setFont(font);
    recipeText.setCharacterSize(20);
    recipeText.setFillColor(sf::Color::Black);
    recipeText.setPosition(10, 50);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(250, 250);
    gameOverText.setString("Game Over!");

    restartText.setFont(font);
    restartText.setCharacterSize(20);
    restartText.setFillColor(sf::Color::Green);
    restartText.setPosition(300, 350);
    restartText.setString("Press R to Restart");

    // Function to spawn ingredients
    auto spawnIngredients = [&]() {
        ingredients.clear();
        recipeTracker.clear();
        currentRecipe.ingredients.clear();

        std::vector<std::string> ingredientNames = {"Carrot", "Tomato", "Potato", "Onion", "Cucumber"};

        // Randomly select recipe ingredients
        int numIngredients = 3 + level; // Increase recipe complexity with level
        for (int i = 0; i < numIngredients; ++i) {
            std::string ingredientName = ingredientNames[rand() % ingredientNames.size()];
            currentRecipe.ingredients.push_back(ingredientName);
            recipeTracker[ingredientName] = false;
        }

        // Display recipe
        std::string recipeDisplay = "Recipe: ";
        for (const auto& ing : currentRecipe.ingredients) {
            recipeDisplay += ing + " ";
        }
        recipeText.setString(recipeDisplay);

        // Spawn ingredients on screen
        for (int i = 0; i < 8; ++i) { // Add extra random ingredients
            Ingredient ingredient;
            ingredient.shape.setSize(sf::Vector2f(100, 50));
            ingredient.shape.setFillColor(sf::Color::Green);
            ingredient.shape.setPosition(rand() % 700 + 50, rand() % 400 + 100);
            ingredient.name = ingredientNames[rand() % ingredientNames.size()];
            ingredients.push_back(ingredient);
        }
    };

    // Initial setup
    srand(static_cast<unsigned>(time(0)));
    spawnIngredients();

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle ingredient chopping
            if (!gameOver && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                for (auto& ingredient : ingredients) {
                    if (ingredient.shape.getGlobalBounds().contains(mousePos) && !ingredient.chopped) {
                        ingredient.chopped = true;
                        ingredient.shape.setFillColor(sf::Color::Red); // Change color when chopped
                        chopSound.play();

                        // Check if ingredient is part of the recipe
                        if (std::find(currentRecipe.ingredients.begin(), currentRecipe.ingredients.end(), ingredient.name) != currentRecipe.ingredients.end()) {
                            recipeTracker[ingredient.name] = true;
                            score += 10;
                        } else {
                            score -= 5; // Penalize wrong ingredient
                        }
                        break;
                    }
                }
            }

            // Restart game
            if (gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                score = 0;
                timer = 30.0f;
                level = 1;
                gameOver = false;
                spawnIngredients();
            }
        }

        // Check if recipe is completed
        recipeCompleted = true;
        for (const auto& pair : recipeTracker) {
            if (!pair.second) {
                recipeCompleted = false;
                break;
            }
        }

        // Update timer
        if (!gameOver && !recipeCompleted) {
            timer -= 0.016f; // Assuming 60 FPS
            if (timer <= 0) {
                gameOver = true;
                gameOverSound.play();
            }
        }

        // Advance level
        if (recipeCompleted) {
            level++;
            timer = 30.0f;
            spawnIngredients();
        }

        // Update texts
        scoreText.setString("Score: " + std::to_string(score));
        timerText.setString("Time: " + std::to_string(static_cast<int>(timer)));
        levelText.setString("Level: " + std::to_string(level));

        // Render game
        window.clear(sf::Color::White);

        for (const auto& ingredient : ingredients) {
            window.draw(ingredient.shape);
        }

        window.draw(scoreText);
        window.draw(timerText);
        window.draw(levelText);
        window.draw(recipeText);

        if (gameOver) {
            window.draw(gameOverText);
            window.draw(restartText);
        }

        window.display();
    }

    return 0;
}
