#include "Game.h"
#include "../Pieces/Piece.h"
#include "Board.h"
#include "../Pieces/Queen.h"
#include <string>
#include <iostream>
#define RED "\033[31m"
#define RESET "\033[0m"



Game::Game()
    : board(new Board()), movesPlayed(0), whiteTurn(true), moveMaker(true) {
    moveMaker.setBoard(board);
}

void Game::playGame(){
    
    board->displayBoard();        
    //while !isGameOver needs implemented
    while(!isGameOver())
        {
            std::string move = getUserMove();
            if (!moveMaker.makeMove(move)) {std::cout << "Invalid move\n"; continue;}


            whiteTurn = !whiteTurn;
            board->displayBoard();

        }
        board->displayBoard();      
}

std::string Game::getUserMove() const{
    std::string move;

    while (true)
    {
        if(whiteTurn){std::cout << "Make a move, WHITE (format: re4e6): "; std::cin >> move;}
        else {std::cout << "Make a move, BLACK (format: re4e6): "; std::cin >> move;}

        if(!correctUserMoveFormat(move)) {std::cout << "Illegal move format" << '\n'; continue;}
        else
            {
                break;
            }
        
    }
    return move;
}

bool Game::correctUserMoveFormat(std::string move) const{
    if (move == "0-0" || move == "0-0-0" || move == "u") {return true;}
    if (move.length() != 5) {return false;}

    std::string checkMove = lowerToUpperString(move);

    //Checks for first letter indicating piece type
    if (checkMove.at(0) != 'P' && checkMove.at(0) != 'K' && checkMove.at(0) != 'B' && checkMove.at(0) != 'R' && checkMove.at(0) != 'Q' && checkMove.at(0) != 'N') {return false;}

    //check that letters are valid indexes
    if (checkMove.at(1) != 'A' && checkMove.at(1) != 'B' && checkMove.at(1) != 'C' && checkMove.at(1) != 'D' && checkMove.at(1) != 'E' && checkMove.at(1) != 'F' && checkMove.at(1) != 'G' && checkMove.at(1) != 'H') {return false;}
    if (checkMove.at(3) != 'A' && checkMove.at(3) != 'B' && checkMove.at(3) != 'C' && checkMove.at(3) != 'D' && checkMove.at(3) != 'E' && checkMove.at(3) != 'F' && checkMove.at(3) != 'G' && checkMove.at(3) != 'H') {return false;}

    //check that numbers are valid indexes
    if (checkMove.at(2) != '1' && checkMove.at(2) != '2' && checkMove.at(2) != '3' && checkMove.at(2) != '4' && checkMove.at(2) != '5' && checkMove.at(2) != '6' && checkMove.at(2) != '7' && checkMove.at(2) != '8') {return false;}
    if (checkMove.at(4) != '1' && checkMove.at(4) != '2' && checkMove.at(4) != '3' && checkMove.at(4) != '4' && checkMove.at(4) != '5' && checkMove.at(4) != '6' && checkMove.at(4) != '7' && checkMove.at(4) != '8') {return false;}

    return true;
}

std::string Game::lowerToUpperString(std::string s) const{
    std::string returnString = "";

    for(size_t i = 0; i < s.length(); i ++)
        {
            returnString += toupper(s.at(i));
        }
    
    return returnString;
}

bool Game::isGameOver() const{
    //check if player has a legal move
    if (board->playerHasLegalMove(whiteTurn)) {return false;}

    //Player has no legal moves at this point, check if the game is checkmate or stalemate
    if (board->kingInCheck(whiteTurn)) {std::cout << "Player, " << !whiteTurn << " Won by checkmate!" << '\n'; return true;}
    else {std::cout << "Position is stalemate, Draw!" << '\n'; return true;}
}

void trainAISelfPlay(int numGames){
    
}

void Game::playGameSFML() {
    // Window and drawing setup
    const int SQUARE_SIZE = 60;
    const int BOARD_SIZE = 8 * SQUARE_SIZE;
    const int WINDOW_WIDTH = BOARD_SIZE + 120;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, BOARD_SIZE), "Chess Game");
    window.setFramerateLimit(30);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) 
        {
            std::cout << "Font not found\n";
        }

    // Load piece textures
    std::map<std::string, sf::Texture> pieceTextures;
    std::vector<std::string> names = 
        {
            "wP", "wN", "wB", "wR", "wQ", "wK",
            "bP", "bN", "bB", "bR", "bQ", "bK"
        };

    for (const auto& name : names) 
        {
            pieceTextures[name] = sf::Texture();

            if (!pieceTextures[name].loadFromFile("Game/SFMLassets/" + name + ".png")) 
                {
                    std::cout << "Failed to load Game/SFMLassets/" << name << ".png" << std::endl;
                }
        }

    // Button setup
    sf::RectangleShape kingsideButton(sf::Vector2f(100, 30));
    kingsideButton.setPosition(BOARD_SIZE + 10, 40);
    kingsideButton.setFillColor(sf::Color(200, 200, 200));
    sf::Text kingsideText("Castle K", font, 16);
    kingsideText.setPosition(BOARD_SIZE + 20, 45);
    kingsideText.setFillColor(sf::Color::Black);

    sf::RectangleShape queensideButton(sf::Vector2f(100, 30));
    queensideButton.setPosition(BOARD_SIZE + 10, 80);
    queensideButton.setFillColor(sf::Color(200, 200, 200));
    sf::Text queensideText("Castle Q", font, 16);
    queensideText.setPosition(BOARD_SIZE + 20, 85);
    queensideText.setFillColor(sf::Color::Black);

    sf::RectangleShape undoButton(sf::Vector2f(100, 30));
    undoButton.setPosition(BOARD_SIZE + 10, 120);
    undoButton.setFillColor(sf::Color(200, 200, 200));
    sf::Text undoText("Undo Move", font, 16);
    undoText.setPosition(BOARD_SIZE + 20, 125);
    undoText.setFillColor(sf::Color::Black);

    // Click tracking
    bool firstClick = true;
    int fromRow = -1, fromCol = -1;
    int toRow = -1, toCol = -1;



    // Main game loop

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
            {
                if (event.type == sf::Event::Closed) 
                    {
                        window.close();
                    }
                if (event.type == sf::Event::MouseButtonPressed) 
                    {
                        int mouseX = event.mouseButton.x;
                        int mouseY = event.mouseButton.y;

                        // Check for button clicks
                        if (mouseX >= BOARD_SIZE + 10 && mouseX <= BOARD_SIZE + 110) 
                            {
                                if (mouseY >= 40 && mouseY <= 70) 
                                    {
                                        // Kingside castle
                                        if (moveMaker.makeMove("0-0")) 
                                            {
                                                whiteTurn = !whiteTurn;
                                            }
                                        firstClick = true;
                                        // Check for game over after move
                                        if (isGameOver()) 
                                            {
                                                window.close();
                                            }
                                        continue;
                                    }

                                if (mouseY >= 80 && mouseY <= 110) 
                                    {
                                        // Queenside castle
                                        if (moveMaker.makeMove("0-0-0")) 
                                            {
                                                whiteTurn = !whiteTurn;
                                            }   
                                        firstClick = true;
                                        // Check for game over after move
                                        if (isGameOver()) 
                                            {
                                                window.close();
                                            }
                                        continue;
                                    }
                                if (mouseY >= 120 && mouseY <= 150) 
                                    {
                                        // Undo move
                                        if (moveMaker.makeMove("u")) 
                                            {
                                                whiteTurn = !whiteTurn;
                                            }
                                        firstClick = true;
                                        // Check for game over after move
                                        if (isGameOver()) 
                                            {
                                                window.close();
                                            }
                                        continue;
                                    }
                            }



                        // Check for board clicks
                        if (mouseX < BOARD_SIZE && mouseY < BOARD_SIZE) 
                            {
                                int col = mouseX / SQUARE_SIZE;
                                int row = 7 - (mouseY / SQUARE_SIZE);

                            if (firstClick) 
                                {
                                    Piece* piece = board->getBoard(row, col);
                                    if (piece != nullptr && piece->getIsWhite() == whiteTurn) 
                                        {
                                            fromRow = row;
                                            fromCol = col;
                                            firstClick = false;
                                        }
                                } 
                                
                            else 
                                {
                                    toRow = row;
                                    toCol = col;
                                    // Generate move string
                                    Piece* piece = board->getBoard(fromRow, fromCol);
                                    char pieceChar = 'P';
                                    if (piece != nullptr) 
                                        {
                                            pieceType type = piece->getPieceType();
                                            switch (type) 
                                                {
                                                    case PAWN: pieceChar = 'P'; break;
                                                    case ROOK: pieceChar = 'R'; break;
                                                    case KNIGHT: pieceChar = 'N'; break;
                                                    case BISHOP: pieceChar = 'B'; break;
                                                    case QUEEN: pieceChar = 'Q'; break;
                                                    case KING: pieceChar = 'K'; break;
                                                    default: pieceChar = 'P'; break;
                                                }
                                        }

                                    char fromColChar = 'A' + fromCol;
                                    char fromRowChar = '1' + fromRow;
                                    char toColChar = 'A' + toCol;
                                    char toRowChar = '1' + toRow;
                                    std::string move = "";
                                    move += pieceChar;
                                    move += fromColChar;
                                    move += fromRowChar;
                                    move += toColChar;
                                    move += toRowChar;


                                            
                                    if (moveMaker.makeMove(move)) 
                                        {
                                            whiteTurn = !whiteTurn;

                                            if (!board->pieceCoordsAreAccurate())
                                                {
                                                    std::cout << "[DEBUG][BOARD AND INTERNAL COORDINATES DO NOT MATCH]" << RED << '\n';
                                                }


                                            // Check for game over after move
                                            if (isGameOver()) 
                                                {
                                                    window.close();
                                                }
                                        }
                                    // Reset for next move
                                    firstClick = true;
                                    fromRow = fromCol = toRow = toCol = -1;
                                }
                            }
                    }
        }

        // Draw everything
        window.clear(sf::Color::White);

        // Draw board and pieces
        for (int row = 0; row < 8; row++) 
            {
                for (int col = 0; col < 8; col++) 
                    {
                        sf::RectangleShape square;
                        square.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
                        square.setPosition(col * SQUARE_SIZE, (7 - row) * SQUARE_SIZE);

                        // Highlight selected square
                        if (!firstClick && fromRow == row && fromCol == col) 
                            {
                                square.setFillColor(sf::Color::Yellow);
                            } 
                        else if ((row + col) % 2 == 0) 
                            {
                                square.setFillColor(sf::Color(240, 217, 181));
                            } 
                        else 
                            {
                                square.setFillColor(sf::Color(181, 136, 99));
                            }
                        window.draw(square);

                        // Draw piece as image
                        Piece* piece = board->getBoard(row, col);
                        if (piece != nullptr) 
                            {
                                std::string key = (piece->getIsWhite() ? "w" : "b");
                                switch (piece->getPieceType()) 
                                    {
                                        case PAWN:   key += "P"; break;
                                        case KNIGHT: key += "N"; break;
                                        case BISHOP: key += "B"; break;
                                        case ROOK:   key += "R"; break;
                                        case QUEEN:  key += "Q"; break;
                                        case KING:   key += "K"; break;
                                        default: break;
                                    }
                                if (pieceTextures.count(key)) 
                                    {
                                        sf::Sprite sprite;
                                        sprite.setTexture(pieceTextures[key]);
                                        sprite.setPosition(col * SQUARE_SIZE, (7 - row) * SQUARE_SIZE);

                                        sprite.setScale 
                                            (
                                                float(SQUARE_SIZE) / sprite.getTexture()->getSize().x,
                                                float(SQUARE_SIZE) / sprite.getTexture()->getSize().y
                                            );
                                        window.draw(sprite);
                                    }
                            }
                    }
            }

        // Draw buttons
        window.draw(kingsideButton);
        window.draw(queensideButton);
        window.draw(undoButton);
        window.draw(kingsideText);
        window.draw(queensideText);
        window.draw(undoText);

        window.display();
    }
}







