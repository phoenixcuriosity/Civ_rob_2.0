/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2024 (robin.sauter@orange.fr)

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

#include "ValueToScale.h"

double 
R2D::ValueToScale
::computeValueToScale(const double value,
					  const double minValue,
					  const double maxValue,
					  const double minScale,
					  const double maxScale,
					  const int divToScaleSize)
{
	if (checkMinMaxValidityRange(minValue, maxValue) && checkMinMaxValidityRange(minScale, maxScale))
	{
		double result{ value };
		const double rangeValue{ maxValue - minValue };
		const double rangeScale{ maxScale - minScale };

		result = protectedDiv(result, divToScaleSize);

		result -= minValue;

		result = protectedDiv(result, rangeValue);

		result *= rangeScale;

		result += minScale;

		return result;
	}
	else
	{
		throw("[ERROR]___: computeValueToScale : checkMinMaxValidityRange");
	}
}

double 
R2D::ValueToScale
::protectedDiv( const double num,
				const double den)
{
	if (den > VALUE_PRECISION::DIV)
	{
		return num / den;
	}
	else
	{
		throw("[ERROR]___: protectedDiv: div by 0");
	}
}

bool 
R2D::ValueToScale
::checkMinMaxValidityRange(const double min,
						   const double max)
{
	if (min < max)
	{
		return true;
	}
	else
	{
		return false;
	}
}