#include <iostream>;
#include <vector>;


inline std::vector<std::vector<std::string>> position_pieces{
    {"T", "C", "F", "D", "R", "F", "C", "T"},
    {"P", "P", "P", "P", "P", "P", "P", "P"},
    {"V", "V", "V", "V", "V", "V", "V", "V"},
    {"V", "V", "V", "V", "V", "V", "V", "V"},
    {"V", "V", "V", "V", "V", "V", "V", "V"},
    {"V", "V", "V", "V", "V", "V", "V", "V"},
    {"P", "P", "P", "P", "P", "P", "P", "P"},
    {"T", "C", "F", "D", "R", "F", "C", "T"}
}; // tableau de positions initiales des pièces.

class Piece {
    std::string label;
};