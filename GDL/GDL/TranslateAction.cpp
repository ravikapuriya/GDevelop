/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

#if defined(GD_IDE_ONLY)

#include <string>
#include <vector>
#include <sstream>
#include <wx/log.h>
#include "GDL/CommonTools.h"
#include "GDL/BitmapGUIManager.h"
#include "GDL/ExtensionBase.h"
#include "GDL/TranslateAction.h"
#include "GDL/tinyxml.h"
#include <wx/wx.h>
#include <wx/bitmap.h>
#include <iostream>
#include <map>

using namespace std;

////////////////////////////////////////////////////////////
/// Traduction compl�te
///
/// Traduction en une phrase compl�te d'une action et ses param�tres
////////////////////////////////////////////////////////////
string TranslateAction::Translate(const Instruction & action, const InstructionInfos & infos)
{
    string trad = infos.sentence;
    RemoveHTMLTags(trad);

    //Remplacement des _PARAMx_ par la valeur des param�tres
    for (unsigned int i =0;i<infos.parameters.size();++i)
    {
        while ( trad.find( "_PARAM"+ToString(i)+"_" ) != string::npos )
        {
            string parameter = action.GetParameterSafely( i ).GetPlainString();
            RemoveHTMLTags(parameter);
            AddHTMLToParameter(parameter, infos.parameters[i].type);

            trad.replace(   trad.find( "_PARAM"+ToString(i)+"_" ), //Chaine � remplacer
                            string("_PARAM"+ToString(i)+"_").length(), //Longueur de la chaine
                            parameter );
        }
    }

    return trad;
}

void TranslateAction::RemoveHTMLTags(string & str)
{
    size_t pos = 0;
    while ( str.find("&", pos) != string::npos)
    {
        str.replace( str.find( "&", pos), 1, "&amp;" );
        pos = str.find( "&", pos)+1;
    }

    while ( str.find("<") != string::npos)
        str.replace( str.find( "<" ), 1, "&lt;" );

    while ( str.find(">") != string::npos)
        str.replace( str.find( ">" ), 1, "&gt;" );
}

////////////////////////////////////////////////////////////
/// Renvoi le nom du bouton en fonction du type
////////////////////////////////////////////////////////////
string TranslateAction::LabelFromType(string type)
{
    if ( type == "" )
        return "";
    else if ( type == "expression" )
        return ToString(_("Expression"));
    else if ( type == "object" )
        return ToString(_("Choisir l'objet"));
    else if ( type == "automatism" )
        return ToString(_("Choisir l'automatisme"));
    else if ( type == "operator" )
        return ToString(_("Choisir le signe"));
    else if ( type == "file" )
        return ToString(_("Choisir le fichier"));
    else if ( type == "yesorno" )
        return ToString(_("Oui ou non"));
    else if ( type == "police" )
        return ToString(_("Choisir la police"));
    else if ( type == "color" )
        return ToString(_("Choisir la couleur"));
    else if ( type == "string" )
        return ToString(_("Editer le texte"));
    else if ( type == "musicfile" )
        return ToString(_("Choisir la musique"));
    else if ( type == "soundfile" )
        return ToString(_("Choisir le son"));
    else if ( type == "password" )
        return ToString(_("Cr�er un mot de passe"));
    else if ( type == "layer" )
        return ToString(_("Choisir le calque"));
    else if ( type == "joyaxis" )
        return ToString(_("Choisir l'axe"));
    else if ( type == "objectvar" )
        return ToString(_("Choisir la variable de l'objet"));
    else if ( type == "scenevar" )
        return ToString(_("Choisir la variable de la sc�ne"));
    else if ( type == "globalvar" )
        return ToString(_("Choisir la variable globale"));

    return "undefined";
}

////////////////////////////////////////////////////////////
/// Renvoi le bitmap du bouton en fonction du type
////////////////////////////////////////////////////////////
wxBitmap TranslateAction::BitmapFromType(string type)
{
    BitmapGUIManager * bitmapGUIManager = BitmapGUIManager::GetInstance();

    if ( type == "" )
        return bitmapGUIManager->unknownBt;
    else if ( type == "expression" )
        return bitmapGUIManager->expressionBt;
    else if ( type == "object" )
        return bitmapGUIManager->objectBt;
    else if ( type == "automatism" )
        return bitmapGUIManager->automatismBt;
    else if ( type == "operator" )
        return bitmapGUIManager->signeBt;
    else if ( type == "file" )
        return bitmapGUIManager->fileBt;
    else if ( type == "yesorno" )
        return bitmapGUIManager->yesnoBt;
    else if ( type == "police" )
        return bitmapGUIManager->policeBt;
    else if ( type == "color" )
        return bitmapGUIManager->colorBt;
    else if ( type == "string" )
        return bitmapGUIManager->texteBt;
    else if ( type == "musicfile" )
        return bitmapGUIManager->musicBt;
    else if ( type == "soundfile" )
        return bitmapGUIManager->soundBt;
    else if ( type == "password" )
        return bitmapGUIManager->passwordBt;
    else if ( type == "layer" )
        return bitmapGUIManager->layerBt;
    else if ( type == "joyaxis" )
        return bitmapGUIManager->joyaxisBt;
    else if ( type == "objectvar" )
        return bitmapGUIManager->varBt;
    else if ( type == "scenevar" )
        return bitmapGUIManager->varBt;
    else if ( type == "globalvar" )
        return bitmapGUIManager->varBt;

    return bitmapGUIManager->unknownBt;
}

////////////////////////////////////////////////////////////
/// D�core un param�tre avec du html, suivant son type
////////////////////////////////////////////////////////////
string TranslateAction::AddHTMLToParameter(string & parameter, string type)
{
    if ( type == "expression" )
        parameter = /*"<FONT color=#CC2222>"+*/parameter/*+"</FONT>"*/;
    else if ( type == "object" )
        parameter = /*"<FONT color=#29780E><b>"+*/parameter/*+"</b></FONT>"*/;
    else if ( type == "operator" )
        parameter = /*"<FONT color=##0404B4><b>"+*/parameter/*+"</b></FONT>"*/;
    else if ( type == "file" )
        parameter = "<i>"+parameter+"</i>";
    else if ( type == "yesorno" )
        parameter = "<b>"+parameter+"</b>";
    else if ( type == "police" )
        parameter = "<b>"+parameter+"</b>";
    else if ( type == "musicfile" )
        parameter = "<b>"+parameter+"</b>";
    else if ( type == "soundfile" )
        parameter = "<b>"+parameter+"</b>";
    else if ( type == "layer" )
        parameter = "<b>"+parameter+"</b>";
    else if ( type == "joyaxis" )
        parameter = "<b>"+parameter+"</b>";

    return parameter;
}



#endif
