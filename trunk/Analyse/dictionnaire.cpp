#include "dictionnaire.h"
#include <QRegExp>



Dictionnaire::typeLigne Dictionnaire::getType(QString pLigne ){
//if
//
//        else
//
//
//
//            else
//
//
//                else
//
//

if (isSi(pLigne))
    return Dictionnaire::Si;
else
    return Dictionnaire::TypeInconnu;


}

bool Dictionnaire::isSi(QString pLigne) {
    QRegExp rx("^si\\s+*$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}


//
//
//
//Dictionnaire::Dictionnaire()
//{
//    m_dico << QRegExp("^glossaire\\s?:?$");
//    m_dico << QRegExp("^d[eé]but\\s?:?$");
//    m_dico << QRegExp("^fin$");
//    //type
//    m_dico << QRegExp("^(entier|r[ée]el|cha[îi]ne|caract[eè]re|bool[ée]en)\\s+([a-zA-Z]+)\\s+((?:\\w*\\s*)*)$");
//    m_dico << "^r[ée]el ..............................";
//    m_dico << "^entier$";
//    m_dico << "^caract[èe]re$";
//    m_dico << "^cha[îi]ne$";
//    m_dico << "^bool[ée]en$";
//    //commentaire
//    m_dico << "^//";

//      a ne pas mettre

//    m_dico << "^/\\*";
//    m_dico << "\\*/";



//    //Condition
//    m_dico << "^si[a-z]+=[]alors$";
//    m_dico << "^sinon$";                    //apre le sinon il peut y avoir un autre si...
//    m_dico << "^sinon+(si[]+=[]alors)";
//    m_dico << "^finsi$";
//    //switch
//    m_dico << "^selon (+";
//    m_dico << "^cas[0-9]{1,2}:?$";          //uniquement avec deschffre ou bienavec des valeur texte ?????
//    m_dico << "^cas (*\S):$";               //() contient les differente valeur possible de la variable
//
//    m_dico << "^default$";
//    m_dico << "^finselon$";
//    //While
//    m_dico << "^tantque      faire$";
//    m_dico << "^fintantque$";
//    //do..while
//    m_dico << "^repeter$";
//    m_dico << "^jusqua";
//    m_dico << "^jusqu'?a";
//    //for
//    m_dico << "pour";
//    m_dico << "de";
//    m_dico << "a";
//    m_dico << "^finpour$";
//    //Liaison
//    m_dico << "et";
//    m_dico << "ou";
//    m_dico << "non";
//    m_dico << "=";
//    m_dico << "<";
//    m_dico << ">";
//    m_dico << "<=";
//    m_dico << ">=";
//    m_dico << "!=";
//



//utilisation expression reguliere




//test qDebug() << m_dico.at(1);}


























