#ifndef ERREUR_H
#define ERREUR_H

class Erreur {

public:
    Erreur();

    enum {
        DivisionParZero,
        PositionOperateurs,
        Parentheses,
    };
};

#endif // ERREUR_H
