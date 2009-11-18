#ifndef ERREURANALYSE_H
#define ERREURANALYSE_H

class ErreurAnalyse {
public:
    enum {
        VariableNonDeclaree,
        VariableDejaDeclaree,
        TypeIncorrect,
    };
};

#endif // ERREURANALYSE_H
