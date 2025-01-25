#include <fstream> // Untuk file handling (Leaderboard)

// Fungsi untuk membaca skor tertinggi dari file
int readHighScore() {
    std::ifstream file("highscore.txt");
    int highScore = 0;
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
    return highScore;
}

// Fungsi untuk menyimpan skor tertinggi ke file
void saveHighScore(int score) {
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        file << score;
        file.close();
    }
}
