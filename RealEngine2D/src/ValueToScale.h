/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	last modification on this file on version:0.25.6.1
	file version : 1.3

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

#ifndef ValueToScale_H
#define ValueToScale_H

namespace VALUE_PRECISION
{
	const double DIV = 1e-12;
}

namespace RealEngine2D
{

	class ValueToScale
	{
	public:

		/* ---------------------------------------------------------------------------------------------------------- */
		/* NAME : computeValueToScale																		    	  */
		/* ROLE : Scale a value from an initial range to a target range											      */
		/* ROLE : Error management : Throw error if checkMinMaxValidityRange return false						      */
		/* IN : double value : The value to scale																      */
		/* IN : double minValue : The minimum value	of the initial range										      */
		/* IN : double maxValue : The maximum value	of the initial range										      */
		/* IN : double minScale : The minimum value	of the target range											      */
		/* IN : double maxScale : The maximum value	of the target range											      */
		/* IN : int divToScaleSize : A factor to scale the initial value, default value is 1					      */
		/* RETURNED VALUE : double : result the value in the target range											  */
		/* ---------------------------------------------------------------------------------------------------------- */
		static double computeValueToScale
		(
			/* IN */
			const double value,
			const double minValue,
			const double maxValue,
			const double minScale,
			const double maxScale,
			const int divToScaleSize = 1
		);

	public:


		/* ---------------------------------------------------------------------------------------------------------- */
		/* NAME : protectedDiv																				    	  */
		/* ROLE : Check if the denominator is 0.0 then throw error, else do the division.						      */
		/* IN : double num : The numerator																		      */
		/* IN : double den : The denominator																	      */
		/* RETURNED VALUE : double -> result from division															  */
		/* ---------------------------------------------------------------------------------------------------------- */
		static double protectedDiv
		(
			/* IN */
			const double num,
			const double den
		);


		/* ---------------------------------------------------------------------------------------------------------- */
		/* NAME : checkMinMaxValidityRange																	    	  */
		/* ROLE : Check if the min value is strictly lower than max value										      */
		/* IN : double min : The minimum value																	      */
		/* IN : double max : The maximum value																	      */
		/* RETURNED VALUE : bool : false -> min is greater than or equal to max										  */
		/* RETURNED VALUE : bool : true -> min strictly lower than max value										  */
		/* ---------------------------------------------------------------------------------------------------------- */
		static bool checkMinMaxValidityRange
		(
			/* IN */
			const double min,
			const double max
		);
	};
}

#endif // !ValueToScale_H

