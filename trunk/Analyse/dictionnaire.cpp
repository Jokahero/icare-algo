#include "dictionnaire.h"

Dictionnaire::Dictionnaire()
{
    m_dico << "glossaire";
    m_dico << "debut";
    m_dico << "fin";
    //type
    m_dico << "reel";
    m_dico << "entier";
    m_dico << "caratere";
    m_dico << "chaine";
    m_dico << "booleen";
    //commentaire
    m_dico << "//";
    //Condition
    m_dico << "si";///////////////
    m_dico << "alors";
    m_dico << "sinon";
    m_dico << "finsi";
    //switch
    m_dico << "selon";
    m_dico << "cas";
    m_dico << "default";
    m_dico << "finselon";
    //While
    m_dico << "tantque";///////////
    m_dico << "faire";
    m_dico << "fintantque";
    //do..while
    m_dico << "repeter";
    m_dico << "jusqua";
    m_dico << "jusqu'?a";
    //for
    m_dico << "pour";
    m_dico << "de";
    m_dico << "a";
    m_dico << "finpour";
    //Liaison
    m_dico << "et";
    m_dico << "ou";
    m_dico << "non";
    m_dico << "=";
    m_dico << "<";
    m_dico << ">";
    m_dico << "<=";
    m_dico << ">=";
    m_dico << "!=";




//utilisation expression reguliere




    //test qDebug() << m_dico.at(1);
}
