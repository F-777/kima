// Variabel skor tertinggi
int highScore = readHighScore();

gameOverText.setString("Game Over!\nYour Score: " + std::to_string(score) + 
                       "\nHigh Score: " + std::to_string(highScore));

if (score > highScore) {
    saveHighScore(score);
    gameOverText.setString("Game Over!\nYour Score: " + std::to_string(score) + 
                           "\nNew High Score!");
}
