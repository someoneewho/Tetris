#pragma once
#include <string>

#include "piece.h"
#include "board.h"

#include <SFML/Graphics.hpp>

class Game {
public:
    Game(unsigned boardWidth, unsigned boardHeight, sf::RenderWindow& window, unsigned level = 1, unsigned speed = 1, std::string userName = "");
    void HandleKeyPress(sf::Keyboard::Key keyCode);
    void Update();
    void Draw();

private:
    void togglePause() {
        _isPaused = !_isPaused;
    }

    void reset();
    void updateDown();
    void drawNextPiece();
    void displayGameInfo();
    void updateScore(unsigned clearedRows);
    bool isGameRunning() {
        return !(_isPaused || _isGameOver);
    }


private:
    sf::RenderWindow& _window;
    Board _tetrisBoard;
    std::string _userName;
    unsigned _level;
    unsigned _speed;
    unsigned _score = 0;

    Piece _currentPiece;
    Piece _nextPiece;

    bool _isPaused = false;
    bool _isGameOver = false;;

    const unsigned _initialLevel;
    const unsigned _initialSpeed;

    sf::Clock _clock;
};

