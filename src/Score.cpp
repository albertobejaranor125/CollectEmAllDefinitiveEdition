#include "Score.h"
int highScore = 0;
void LoadHighScore() {
    std::ifstream file("score.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
}
void SaveHighScore() {
    std::ofstream file("score.txt");
    if (file.is_open()) {
        file << highScore;
        file.close();
    }
}