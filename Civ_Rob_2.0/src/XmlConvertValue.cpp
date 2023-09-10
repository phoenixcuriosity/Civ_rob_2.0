/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.2.0
	file version : 1.6

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

#include <R2D/src/ErrorLog.h> 

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
	if (type.compare("error") == STRINGS::IDENTICAL)
	{
		return State_Type::error;
	}
	else if (type.compare("STATEtitleScreen") == STRINGS::IDENTICAL)
	{
		return State_Type::STATEtitleScreen;
	}
	else if (type.compare("STATEscreennewgame") == STRINGS::IDENTICAL)
	{
		return State_Type::STATEscreenNewgame;
	}
	else if (type.compare("STATEreload") == STRINGS::IDENTICAL)
	{
		return State_Type::STATEreload;
	}
	else if (type.compare("STATEmainmap") == STRINGS::IDENTICAL)
	{
		return State_Type::STATEmainMap;
	}
	else if (type.compare("STATEscience") == STRINGS::IDENTICAL)
	{
		return State_Type::STATEscience;
	}
	else if (type.compare("STATEcitiemap") == STRINGS::IDENTICAL)
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
	if (type.compare("selectnothing") == STRINGS::IDENTICAL)
	{
		return Select_Type::selectnothing;
	}
	else if (type.compare("selectcreate") == STRINGS::IDENTICAL)
	{
		return Select_Type::selectcreate;
	}
	else if (type.compare("selectinspect") == STRINGS::IDENTICAL)
	{
		return Select_Type::selectinspect;
	}
	else if (type.compare("selectmove") == STRINGS::IDENTICAL)
	{
		return Select_Type::selectmove;
	}
	else if (type.compare("selectmoveCitizen") == STRINGS::IDENTICAL)
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
/* NAME : convertUintToUnit_Movement_Type															    	  */
/* ROLE : Convert a unsigned integer from XML document to Unit_Movement_Type from Unit class			      */
/* ROLE : Exit if error : XML document is not properly formated											      */
/* INPUT : unsigned int toConvert																				      */
/* RETURNED VALUE    : Unit_Movement_Type																	  */
/* ---------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------------------------- */
Unit_Movement_Type XmlConvertValue::convertUintToUnit_Movement_Type
(
	unsigned int toConvert
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
		R2D::ErrorLog::logEvent("[ERROR]___: convertUintToUnit_Movement_Type : case default");
		return Unit_Movement_Type::ground;
	}
}


Unit_Movement_Type XmlConvertValue::xmlGiveMovementType
(
	std::string type
)
{
	if (type.compare("ground") == STRINGS::IDENTICAL)
	{
		return Unit_Movement_Type::ground;
	}
	else if (type.compare("air") == STRINGS::IDENTICAL)
	{
		return Unit_Movement_Type::air;
	}
	else if (type.compare("water") == STRINGS::IDENTICAL)
	{
		return Unit_Movement_Type::water;
	}
	else if (type.compare("deepwater") == STRINGS::IDENTICAL)
	{
		return Unit_Movement_Type::deepwater;
	}
	else
	{
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
		R2D::ErrorLog::logEvent("[ERROR]___: convert2ConversionToApply : default");
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
		R2D::ErrorLog::logEvent("[ERROR]___: convert2build_Type : default");
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
		return Emotion_Type::neutral;
	case 1:
		return Emotion_Type::happy;
	case 2:
		return Emotion_Type::ecstatic;
	default:
		R2D::ErrorLog::logEvent("[ERROR]___: convert2Emotion_Type : default");
		return Emotion_Type::neutral;
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
		R2D::ErrorLog::logEvent("[ERROR]___: convert2Religion_Type : default");
		return Religion_Type::catholic;
	}
}

/*
 *	End Of File : XmlConvertValue.cpp
 */