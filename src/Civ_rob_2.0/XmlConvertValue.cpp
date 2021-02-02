/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.22.0.0
	file version : 1.0

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Civ_rob_2.0

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "XmlConvertValue.h"

#include "End.h"
#include "civ_lib.h"

/* *********************************************************
 *						 Classes						   *
 ********************************************************* */


/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : xmlGiveStateType																			    	  */
/* ROLE : Convert an std::string from XML document to State_Type from Texture class						      */
/* INPUT : std::string type																				      */
/* RETURNED VALUE    : State_Type																			  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
State_Type XmlConvertValue::xmlGiveStateType
(
	std::string type
)
{
	if (type.compare("error") == IDENTICAL_STRINGS)
	{
		return State_Type::error;
	}
	else if (type.compare("STATEtitleScreen") == IDENTICAL_STRINGS)
	{
		return State_Type::STATEtitleScreen;
	}
	else if (type.compare("STATEscreennewgame") == IDENTICAL_STRINGS)
	{
		return State_Type::STATEscreenNewgame;
	}
	else if (type.compare("STATEreload") == IDENTICAL_STRINGS)
	{
		return State_Type::STATEreload;
	}
	else if (type.compare("STATEmainmap") == IDENTICAL_STRINGS)
	{
		return State_Type::STATEmainMap;
	}
	else if (type.compare("STATEscience") == IDENTICAL_STRINGS)
	{
		return State_Type::STATEscience;
	}
	else if (type.compare("STATEcitiemap") == IDENTICAL_STRINGS)
	{
		return State_Type::STATEcityMap;
	}
	else
	{
		return State_Type::error;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : xmlGiveSelectType																			    	  */
/* ROLE : Convert an std::string from XML document to Select_Type from Texture class					      */
/* INPUT : std::string type																				      */
/* RETURNED VALUE    : Select_Type																			  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
Select_Type XmlConvertValue::xmlGiveSelectType
(
	std::string type
)
{
	if (type.compare("selectnothing") == IDENTICAL_STRINGS)
	{
		return Select_Type::selectnothing;
	}
	else if (type.compare("selectcreate") == IDENTICAL_STRINGS)
	{
		return Select_Type::selectcreate;
	}
	else if (type.compare("selectinspect") == IDENTICAL_STRINGS)
	{
		return Select_Type::selectinspect;
	}
	else if (type.compare("selectmove") == IDENTICAL_STRINGS)
	{
		return Select_Type::selectmove;
	}
	else if (type.compare("selectmoveCitizen") == IDENTICAL_STRINGS)
	{
		return Select_Type::selectmoveCitizen;
	}
	else
	{
		return Select_Type::selectnothing;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : xmlGiveTexteConteneur																		    	  */
/* ROLE : Convert an std::string from XML document to MapTexte from global struct Sysinfo				      */
/* INPUT : AllTextes& allTextes	: Define all TexteMap													      */
/* INPUT : std::string type																				      */
/* RETURNED VALUE    : MapTexte																				  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
MapTexte& XmlConvertValue::xmlGiveTexteConteneur
(
	AllTextes& allTextes,
	std::string type
)
{
	if (type.compare("titleScreen") == IDENTICAL_STRINGS)
	{
		return allTextes.titleScreen;
	}
	else if (type.compare("newGame") == IDENTICAL_STRINGS)
	{
		return allTextes.newGame;
	}
	else if (type.compare("mainMap") == IDENTICAL_STRINGS)
	{
		return allTextes.mainMap;
	}
	else if (type.compare("citieMap") == IDENTICAL_STRINGS)
	{
		return allTextes.cityMap;
	}
	else
	{
		return allTextes.titleScreen;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : xmlGiveTexteType																			    	  */
/* ROLE : Convert an std::string from XML document to Texte_Type from Texture class						      */
/* INPUT : std::string type																				      */
/* RETURNED VALUE    : Texte_Type																			  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
Texte_Type XmlConvertValue::xmlGiveTexteType
(
	std::string type
)
{
	if (type.compare("blended") == IDENTICAL_STRINGS)
	{
		return Texte_Type::blended;
	}
	else if (type.compare("shaded") == IDENTICAL_STRINGS)
	{
		return Texte_Type::shaded;
	}
	else
	{
		return Texte_Type::blended;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : xmlGiveColor																				    	  */
/* ROLE : Convert an std::string from XML document to SDL_Color from Texture class						      */
/* INPUT : std::string type																				      */
/* RETURNED VALUE    : SDL_Color																			  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
SDL_Color XmlConvertValue::xmlGiveColor
(
	std::string type
)
{
	if (type.compare("Black") == IDENTICAL_STRINGS)
	{
		return Black;
	}
	else if (type.compare("White") == IDENTICAL_STRINGS)
	{
		return White;
	}
	else if (type.compare("Red") == IDENTICAL_STRINGS)
	{
		return Red;
	}
	else if (type.compare("Green") == IDENTICAL_STRINGS)
	{
		return Green;
	}
	else if (type.compare("Blue") == IDENTICAL_STRINGS)
	{
		return Blue;
	}
	else if (type.compare("Blue") == IDENTICAL_STRINGS)
	{
		return Blue;
	}
	else if (type.compare("Yellow") == IDENTICAL_STRINGS)
	{
		return Yellow;
	}
	else if (type.compare("WriteColorButton") == IDENTICAL_STRINGS)
	{
		return WriteColorButton;
	}
	else if (type.compare("BackColorButton") == IDENTICAL_STRINGS)
	{
		return BackColorButton;
	}
	else if (type.compare("NoColor") == IDENTICAL_STRINGS)
	{
		return NoColor;
	}
	else
	{
		return NoColor;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : xmlGiveAlpha																				    	  */
/* ROLE : Convert an std::string from XML document to Transparance_Type from Texture class				      */
/* INPUT : std::string type																				      */
/* RETURNED VALUE    : Transparance_Type																	  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
Transparance_Type XmlConvertValue::xmlGiveAlpha
(
	std::string type
)
{
	if (type.compare("nonTransparent") == IDENTICAL_STRINGS)
	{
		return nonTransparent;
	}
	else if (type.compare("semiTransparent") == IDENTICAL_STRINGS)
	{
		return semiTransparent;
	}
	else if (type.compare("transparent") == IDENTICAL_STRINGS)
	{
		return transparent;
	}
	else
	{
		return nonTransparent;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : xmlGiveAngle																				    	  */
/* ROLE : Convert an std::string from XML document to Uint16 from Texture class							      */
/* INPUT : std::string type																				      */
/* RETURNED VALUE    : Uint16																				  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
Uint16 XmlConvertValue::xmlGiveAngle
(
	std::string type
)
{
	if (type.compare("no_angle") == IDENTICAL_STRINGS)
	{
		return no_angle;
	}
	else if (type.compare("inverse") == IDENTICAL_STRINGS)
	{
		return inverse;
	}
	else
	{
		return no_angle;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : xmlGiveCenter																				    	  */
/* ROLE : Convert an std::string from XML document to Center_Type from Texture class					      */
/* INPUT : std::string type																				      */
/* RETURNED VALUE    : Center_Type																			  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
Center_Type XmlConvertValue::xmlGiveCenter
(
	std::string type
)
{
	if (type.compare("nocenter") == IDENTICAL_STRINGS)
	{
		return Center_Type::nocenter;
	}
	else if (type.compare("center_x") == IDENTICAL_STRINGS)
	{
		return Center_Type::center_x;
	}
	else if (type.compare("center_y") == IDENTICAL_STRINGS)
	{
		return Center_Type::center_y;
	}
	else if (type.compare("center") == IDENTICAL_STRINGS)
	{
		return Center_Type::center;
	}
	else
	{
		return Center_Type::nocenter;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : convertUintToUnit_Movement_Type															    	  */
/* ROLE : Convert a unsigned integer from XML document to Unit_Movement_Type from Unit class			      */
/* ROLE : Exit if error : XML document is not properly formated											      */
/* INPUT : Uint8 toConvert																				      */
/* RETURNED VALUE    : Unit_Movement_Type																	  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
Unit_Movement_Type XmlConvertValue::convertUintToUnit_Movement_Type
(
	Uint8 toConvert
)
{
	switch (toConvert)
	{
	case 0:
		return Unit_Movement_Type::ground;
	case 1:
		return Unit_Movement_Type::air;
	case 2:
		return Unit_Movement_Type::water;
	case 3:
		return Unit_Movement_Type::deepwater;
	default:
		End::exitError("[ERROR]___: convertUintToUnit_Movement_Type : case default");
		return Unit_Movement_Type::ground;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : convert2ConversionToApply																	    	  */
/* ROLE : Convert an integer from XML document to conversionSurplus_Type from City class				      */
/* ROLE : Exit if error : XML document is not properly formated											      */
/* INPUT : int toConvert																				      */
/* RETURNED VALUE    : conversionSurplus_Type																  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
conversionSurplus_Type XmlConvertValue::convert2ConversionToApply
(
	int toConvert
)
{
	switch (toConvert)
	{
	case 0:
		return conversionSurplus_Type::No_Conversion;
	case 1:
		return conversionSurplus_Type::FoodToWork;
	case 2:
		return conversionSurplus_Type::FoodToGold;
	case 3:
		return conversionSurplus_Type::WorkToFood;
	case 4:
		return conversionSurplus_Type::WorkToGold;
	case 5:
		return conversionSurplus_Type::GoldToFood;
	case 6:
		return conversionSurplus_Type::GoldToWork;
	default:
		End::exitError("[ERROR]___: convert2ConversionToApply : default");
		return conversionSurplus_Type::No_Conversion;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : convert2build_Type																		    	  */
/* ROLE : Convert an integer from XML document to build_Type from City class							      */
/* ROLE : Exit if error : XML document is not properly formated											      */
/* INPUT : int toConvert																				      */
/* RETURNED VALUE    : build_Type																			  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
build_Type XmlConvertValue::convert2build_Type
(
	int toConvert
)
{
	switch (toConvert)
	{
	case 0:
		return build_Type::building;
	case 1:
		return build_Type::unit;
	default:
		End::exitError("[ERROR]___: convert2ConversionToApply : default");
		return build_Type::building;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : convert2Emotion_Type																		    	  */
/* ROLE : Convert an integer from XML document to Emotion_Type from City class							      */
/* ROLE : Exit if error : XML document is not properly formated											      */
/* INPUT : int toConvert																				      */
/* RETURNED VALUE    : Emotion_Type																			  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
Emotion_Type XmlConvertValue::convert2Emotion_Type
(
	int toConvert
)
{
	switch (toConvert)
	{
	case -2:
		return Emotion_Type::angry;
	case -1:
		return Emotion_Type::sad;
	case 0:
		return Emotion_Type::neutre;
	case 1:
		return Emotion_Type::happy;
	case 2:
		return Emotion_Type::ecstatic;
	default:
		End::exitError("[ERROR]___: convert2Emotion_Type : default");
		return Emotion_Type::neutre;
	}
}

/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
/* NAME : convert2Religion_Type																		    	  */
/* ROLE : Convert an integer from XML document to Religion_Type from City class							      */
/* ROLE : Exit if error : XML document is not properly formated											      */
/* INPUT : int toConvert																				      */
/* RETURNED VALUE    : Religion_Type																		  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
Religion_Type XmlConvertValue::convert2Religion_Type
(
	int toConvert
)
{
	switch (toConvert)
	{
	case 0:
		return Religion_Type::catholic;
	case 1:
		return Religion_Type::protestant;
	case 2:
		return Religion_Type::reformed;
	case 3:
		return Religion_Type::anglican;
	case 4:
		return Religion_Type::orthodox;
	case 5:
		return Religion_Type::coptic;
	case 6:
		return Religion_Type::sunni;
	case 7:
		return Religion_Type::shiite;
	case 8:
		return Religion_Type::ibadi;
	case 9:
		return Religion_Type::buddhism;
	case 10:
		return Religion_Type::vajrayana;
	case 11:
		return Religion_Type::mahayana;
	case 12:
		return Religion_Type::confucianism;
	case 13:
		return Religion_Type::shinto;
	case 14:
		return Religion_Type::hinduism;
	case 15:
		return Religion_Type::sikhism;
	case 16:
		return Religion_Type::animism;
	case 17:
		return Religion_Type::shamanism;
	case 18:
		return Religion_Type::totemism;
	case 19:
		return Religion_Type::inti;
	case 20:
		return Religion_Type::nahuatl;
	case 21:
		return Religion_Type::jewish;
	case 22:
		return Religion_Type::zoroastrian;
	default:
		End::exitError("[ERROR]___: convert2Religion_Type : default");
		return Religion_Type::catholic;
	}
}

/*
 *	End Of File : XmlConvertValue.cpp
 */