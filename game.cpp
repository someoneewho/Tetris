#include "game.h"

Game::Game(unsigned boardWidth, unsigned boardHeight, sf::RenderWindow& window, unsigned level, unsigned speed, std::string userName) 
    : _window{window}, _tetrisBoard(boardWidth, boardHeight), _userName{userName}
    , _currentPiece{Piece::getRandomPieceType()}, _nextPiece{Piece::getRandomPieceType()}
{
    // check min-max boundries
    _level = level;
    _speed = speed;
    _tetrisBoard.SetCurrentPiece(&_currentPiece);
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
            // resetGame();
            break;
        case sf::Keyboard::P:
            togglePause();
            break;
        
        default:
            break;
    }
}

void Game::Update() {
    if (isGameRunning() == false)
        return;

    if (_clock.getElapsedTime().asSeconds() >= 1.0) {

        updateDown();
        _clock.restart();
    }
}

void Game::updateDown() {
    auto [isLocked, clearedRows] = _tetrisBoard.MovePieceDown();

    if (isLocked) {
        _currentPiece = _nextPiece;
        _nextPiece = Piece(Piece::getRandomPieceType());
        
        bool status = _tetrisBoard.SetCurrentPiece(&_currentPiece);

        if (status == false) {
            _isGameOver = true;
        }

        // score, level, and speed calculation
    }
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


void Game::Draw() {
    _window.clear();
    _tetrisBoard.draw(_window);
    drawNextPiece();
}