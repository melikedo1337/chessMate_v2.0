#include "board.h"
#include "pieces.h"

#include <cctype>
#include <iostream>
#include <string>

namespace {
Piece* createPiece(char pieceCode, Color color) {
    switch (std::tolower(pieceCode)) {
        case 'k': return new King(color);
        case 'q': return new Queen(color);
        case 'r': return new Rook(color);
        case 'b': return new Bishop(color);
        case 'n': return new Knight(color);
        case 'p': return new Pawn(color);
        default: return nullptr;
    }
}

void printInputHelp() {
    std::cout << "Input each piece like: wK e1 (white king on e1)\n";
    std::cout << "Piece letters: K Q R B N P. Colors: w/b.\n";
}
}

int main() {
    Board board;

    std::cout << "=== Checkmate Detector ===\n";
    printInputHelp();

    int pieceCount = 0;
    std::cout << "How many pieces are on the board? ";
    std::cin >> pieceCount;

    for (int i = 0; i < pieceCount; ++i) {
        std::string pieceSpec;
        std::string squareText;

        std::cout << "Piece " << (i + 1) << ": ";
        std::cin >> pieceSpec >> squareText;

        if (pieceSpec.size() != 2) {
            std::cerr << "Invalid piece format: " << pieceSpec << "\n";
            return 1;
        }

        Color color = Board::parseColor(pieceSpec[0]);
        Piece* piece = createPiece(pieceSpec[1], color);
        if (piece == nullptr) {
            std::cerr << "Unknown piece code: " << pieceSpec[1] << "\n";
            return 1;
        }

        Position pos;
        if (!Board::parseSquare(squareText, pos)) {
            std::cerr << "Invalid square: " << squareText << "\n";
            delete piece;
            return 1;
        }

        board.setPiece(pos, piece);
    }

    char turn;
    std::cout << "Check mate for which side? (w/b): ";
    std::cin >> turn;
    Color sideToCheck = Board::parseColor(turn);

    board.print();

    if (board.isCheckmate(sideToCheck)) {
        std::cout << "Checkmate!\n";
    } else if (board.isInCheck(sideToCheck)) {
        std::cout << "In check, but not checkmate.\n";
    } else {
        std::cout << "Not in checkmate.\n";
    }

    return 0;
}
