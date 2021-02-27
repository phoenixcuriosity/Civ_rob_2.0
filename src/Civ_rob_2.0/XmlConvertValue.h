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

#ifndef XmlConvertValue_H
#define XmlConvertValue_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

#include "City.h"
#include "Citizen.h"
#include "Unit.h"

 /* *********************************************************
  *					 Constantes							   *
  ********************************************************* */

  /* N/A */

  /* *********************************************************
   *							 Enum						   *
   ********************************************************* */

   /* N/A */

  /* *********************************************************
   *						 Structs						   *
   ********************************************************* */

   /* N/A */

   /* *********************************************************
	*						 Classes						   *
	********************************************************* */

class XmlConvertValue
{
public:
	/* *********************************************************
	 *				XmlConvertValue::STATIC					   *
	 ********************************************************* */

	 /* ---------------------------------------------------------------------------------------------------------- */
	 /* ---------------------------------------------------------------------------------------------------------- */
	 /* NAME : xmlGiveStateType																			    	  */
	 /* ROLE : Convert an std::string from XML document to State_Type from Texture class						      */
	 /* INPUT : std::string type																				      */
	 /* RETURNED VALUE    : State_Type																			  */
	 /* ---------------------------------------------------------------------------------------------------------- */
	 /* ---------------------------------------------------------------------------------------------------------- */
	static State_Type xmlGiveStateType
	(
		std::string type
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : xmlGiveSelectType																			    	  */
	/* ROLE : Convert an std::string from XML document to Select_Type from Texture class					      */
	/* INPUT : std::string type																				      */
	/* RETURNED VALUE    : Select_Type																			  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static Select_Type xmlGiveSelectType
	(
		std::string type
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : convertUintToUnit_Movement_Type															    	  */
	/* ROLE : Convert a unsigned integer from XML document to Unit_Movement_Type from Unit class			      */
	/* ROLE : Exit if error : XML document is not properly formated											      */
	/* INPUT : Uint8 toConvert																				      */
	/* RETURNED VALUE    : Unit_Movement_Type																	  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static Unit_Movement_Type convertUintToUnit_Movement_Type
	(
		Uint8 toConvert
	);

	static Unit_Movement_Type xmlGiveMovementType
	(
		std::string type
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : convert2ConversionToApply																	    	  */
	/* ROLE : Convert an integer from XML document to conversionSurplus_Type from City class				      */
	/* ROLE : Exit if error : XML document is not properly formated											      */
	/* INPUT : int toConvert																				      */
	/* RETURNED VALUE    : conversionSurplus_Type																  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static conversionSurplus_Type convert2ConversionToApply
	(
		int toConvert
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : convert2build_Type																		    	  */
	/* ROLE : Convert an integer from XML document to build_Type from City class							      */
	/* ROLE : Exit if error : XML document is not properly formated											      */
	/* INPUT : int toConvert																				      */
	/* RETURNED VALUE    : build_Type																			  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static build_Type convert2build_Type
	(
		int toConvert
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : convert2Emotion_Type																		    	  */
	/* ROLE : Convert an integer from XML document to Emotion_Type from City class							      */
	/* ROLE : Exit if error : XML document is not properly formated											      */
	/* INPUT : int toConvert																				      */
	/* RETURNED VALUE    : Emotion_Type																			  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static Emotion_Type convert2Emotion_Type
	(
		int toConvert
	);

	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* NAME : convert2Religion_Type																		    	  */
	/* ROLE : Convert an integer from XML document to Religion_Type from City class							      */
	/* ROLE : Exit if error : XML document is not properly formated											      */
	/* INPUT : int toConvert																				      */
	/* RETURNED VALUE    : Religion_Type																		  */
	/* ---------------------------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------------------------- */
	static Religion_Type convert2Religion_Type
	(
		int toConvert
	);


};


#endif // !XmlConvertValue_H

/*
 *	End Of File : XmlConvertValue.h
 */
