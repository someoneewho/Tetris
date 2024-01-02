#include "game.h"
#include <iostream>

#define MAX_LEVEL 10
#define MAX_SPEED 10

Game::Game(unsigned boardWidth, unsigned boardHeight, sf::RenderWindow& window, unsigned level, unsigned speed, std::string userName) 
    : _window{window}, _tetrisBoard(boardWidth, boardHeight), _userName{userName}
    , _initialLevel{level}, _initialSpeed{speed}
{
    reset();
}

void Game::HandleKeyPress(sf::Keyboard::Key keyCode) {
    switch (keyCode) {
        case sf::Keyboard::Right:
            if (isGameRunning())
                _tetrisBoard.MovePieceRight();
            break;
        case sf::Keyboard::Left:
            if (isGameRunning())
                _tetrisBoard.MovePieceLeft();
            break;
        case sf::Keyboard::Down:
            if (isGameRunning())
                updateDown();
            break;
        case sf::Keyboard::E:
            if (isGameRunning())
                _tetrisBoard.RotatePieceCW();
            break;
        case sf::Keyboard::Q:
            if (isGameRunning())
                _tetrisBoard.RotatePieceCCW();
            break;
        case sf::Keyboard::R:
            if (_isGameOver) {
                reset();
            }
            break;
        case sf::Keyboard::P:
            if (_isGameOver == false) {
                togglePause();
            }
            break;
        
        default:
            break;
    }
}

void Game::Update() {
    if (isGameRunning() == false)
        return;

    if (_clock.getElapsedTime().asSeconds() >= 1 - 0.1 * (_speed - 1)) {

        updateDown();
        _clock.restart();
    }
}

void Game::updateDown() {
    auto [isLocked, clearedRows] = _tetrisBoard.MovePieceDown();

    if (isLocked) {
        updateScore(clearedRows);
        _currentPiece = _nextPiece;
        _nextPiece = Piece::getRandomPiece();
        
        bool status = _tetrisBoard.SetCurrentPiece(&_currentPiece);

        if (status == false) {
            _isGameOver = true;
        }
        
    }
}


void Game::updateScore(unsigned clearedRows) {
    // Increase score for each cleared row
    _score += clearedRows * 100;

    // Check for combo points
    if (clearedRows > 1) {
        // Bonus points for combo (for example, extra points for each additional cleared row)
        int comboBonus = (clearedRows - 1) * 50;
        _score += comboBonus;
    }

    // Change score with level (and level up by 500 points)
    int targetScoreForNextLevel = 500 * (_level + 1);
    if (_score >= targetScoreForNextLevel) {
        if (_level < MAX_LEVEL) {
            _level++;
        }
        //Change speed with score
        if (_speed < MAX_SPEED) {
            _speed++;
        }
    }
}

void Game::reset() {
    _score = 0;
    _level = _initialLevel;
    _speed = _initialSpeed;
    _isPaused = false;
    _isGameOver = false;

    _tetrisBoard.Clear();

    _currentPiece = Piece::getRandomPiece();
    _nextPiece = Piece::getRandomPiece();
    _tetrisBoard.SetCurrentPiece(&_currentPiece);

    _clock.restart();
}

void Game::drawNextPiece() {
    sf::RectangleShape nextPiecePanel(sf::Vector2f(4 * CELL_SIZE, 4 * CELL_SIZE));
    nextPiecePanel.setPosition(_tetrisBoard.getWidth() * CELL_SIZE + CELL_SIZE, CELL_SIZE); 

    _window.draw(nextPiecePanel);

    const Piece::ShapeMatrix& pieceMatrix = _nextPiece.getMatrix();

    for (int row = 0; row < pieceMatrix.rows; ++row) {
        for (int col = 0; col < pieceMatrix.cols; ++col) {
            if (pieceMatrix.data[row][col] != 0) {
                sf::RectangleShape square(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                square.setPosition(nextPiecePanel.getPosition().x + CELL_SIZE / 2 + col * CELL_SIZE, 
                                   nextPiecePanel.getPosition().y + CELL_SIZE / 2 + row * CELL_SIZE);
                square.setFillColor(sf::Color::Green);
                _window.draw(square);
            }
        }
    }
}

void Game::displayGameInfo() {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Magenta);
    scoreText.setPosition(_tetrisBoard.getWidth() * CELL_SIZE + CELL_SIZE, 5 * CELL_SIZE);
    scoreText.setString("Score: " + std::to_string(_score));

    sf::Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(20);
    levelText.setFillColor(sf::Color::Magenta);
    levelText.setPosition(_tetrisBoard.getWidth() * CELL_SIZE + CELL_SIZE, 6 * CELL_SIZE);
    levelText.setString("Level: " + std::to_string(_level));

    sf::Text speedText;
    speedText.setFont(font);
    speedText.setCharacterSize(20);
    speedText.setFillColor(sf::Color::Magenta);
    speedText.setPosition(_tetrisBoard.getWidth() * CELL_SIZE + CELL_SIZE, 7 * CELL_SIZE);
    speedText.setString("Speed: " + std::to_string(_speed));

    sf::Text rotateCountLeftText;
    rotateCountLeftText.setFont(font);
    rotateCountLeftText.setCharacterSize(20);
    rotateCountLeftText.setFillColor(sf::Color::Magenta);
    rotateCountLeftText.setPosition(_tetrisBoard.getWidth() * CELL_SIZE + CELL_SIZE, 8 * CELL_SIZE);

    unsigned rotateCountLeft = 0;
        rotateCountLeft = _currentPiece.getRotationsLeft();

    rotateCountLeftText.setString("Rotations Left: " + std::to_string(rotateCountLeft));


    _window.draw(scoreText);
    _window.draw(levelText);
    _window.draw(speedText);
    _window.draw(rotateCountLeftText);

    if (_isPaused)
    {
        sf::Text pausedText;
        pausedText.setFont(font);
        pausedText.setCharacterSize(24);
        pausedText.setFillColor(sf::Color::Red);
        pausedText.setPosition(_tetrisBoard.getWidth() * CELL_SIZE + CELL_SIZE, 9 * CELL_SIZE);
        pausedText.setString("PAUSED !");
        _window.draw(pausedText);
    }

    if (_isGameOver)
    {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(24);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(_tetrisBoard.getWidth() * CELL_SIZE + CELL_SIZE, 9 * CELL_SIZE);
        gameOverText.setString("GAME OVER !");
        _window.draw(gameOverText);
    }
    
}



void Game::Draw() {
    _window.clear();
    _tetrisBoard.draw(_window);
    drawNextPiece();
    displayGameInfo();
}