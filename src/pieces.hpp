#include <iostream>;
#include <vector>;

inline std::vector<std::vector<std::string>> position_pieces{
    {"Tn", "Cn", "Fn", "Dn", "Rn", "Fn", "Cn", "Tn"},
    {"Pn", "Pn", "Pn", "Pn", "Pn", "Pn", "Pn", "Pn"},
    {"V", "V", "V", "V", "V", "V", "V", "V"},
    {"V", "V", "V", "V", "V", "V", "V", "V"},
    {"V", "V", "V", "V", "V", "V", "V", "V"},
    {"V", "V", "V", "V", "V", "V", "V", "V"},
    {"Pb", "Pb", "Pb", "Pb", "Pb", "Pb", "Pb", "Pb"},
    {"Tb", "Cb", "Fb", "Db", "Rb", "Fb", "Cb", "Tb"}
}; // tableau de positions initiales des pièces.

class Piece {
    private:
        std::string label;
        int color; //0:blanc 1:noire

    public:
        void move(); 
};