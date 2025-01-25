// Variabel untuk nyawa
int lives = 3;

// Text untuk menampilkan nyawa
sf::Text livesText;
livesText.setFont(font);
livesText.setCharacterSize(24);
livesText.setFillColor(sf::Color::Red);
livesText.setPosition(10, 80);
livesText.setString("Lives: " + std::to_string(lives));

// Update lives saat bahan salah dipotong
if (std::find(currentRecipe.ingredients.begin(), currentRecipe.ingredients.end(), ingredient.name) == currentRecipe.ingredients.end()) {
    lives--;
    if (lives <= 0) {
        gameOver = true;
        gameOverSound.play();
    }
}
livesText.setString("Lives: " + std::to_string(lives));
