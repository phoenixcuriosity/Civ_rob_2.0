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

#pragma once

#include "CityFactory.h"

namespace city
{

/**
 * @class CityManager
 * @brief Manages a collection of cities in the game.
 *
 * The CityManager class provides functionality to add, remove, and retrieve cities.
 * It interacts with the CityFactory to create new cities and maintains a list of city objects.
 */
class CityManager
{
private:
    using Coor = R2D::Coor; ///< Alias for coordinates used in the game.
    using CityName = std::string; ///< Alias for the name of a city.
    using CityPtrTVector = std::vector<std::shared_ptr<City>>; ///< Alias for a vector of shared pointers to City objects.
    using CityNamePlayerId = CityFactory::CityNamePlayerId; ///< Alias for player ID and city name structure.
    using VectMapPtr = std::vector<Tile*>; ///< Alias for a vector of pointers to tiles.

    CityPtrTVector m_city; ///< Vector storing shared pointers to City objects.

    /**
     * @brief Retrieves the singleton instance of the CityFactory.
     *
     * This method ensures that only one instance of the CityFactory exists and provides access to it.
     *
     * @return A reference to the singleton CityFactory instance.
     */
    static CityFactory& getFactory()
    {
        static CityFactory factory;
        return factory;
    }

public:
    /**
     * @brief Constructs a CityManager object.
     *
     * Initializes the city vector and ensures the CityFactory is instantiated.
     */
    CityManager() : m_city()
    {
        getFactory();
    }

    /**
     * @brief Adds a new city to the manager.
     *
     * This method creates a new city for the specified player at the given coordinates
     * and assigns the provided tiles to the city.
     *
     * @param playerId The ID of the player who owns the city.
     * @param coor The coordinates where the city will be created.
     * @param tiles A vector of pointers to tiles that the city will occupy.
     */
    void addCity(const int playerId, const Coor coor, VectMapPtr& tiles);

    /**
     * @brief Adds an empty city to the manager.
     *
     * This method creates a placeholder city without any specific attributes.
     */
    void addEmptyCity();

    /**
     * @brief Removes a city from the manager.
     *
     * This method removes the city at the specified index from the city vector.
     *
     * @param index The index of the city to be removed.
     */
    void removeCity(const size_t index);

    /**
     * @brief Retrieves a constant reference to the vector of cities.
     *
     * This method provides read-only access to the list of cities managed by the CityManager.
     *
     * @return A constant reference to the vector of shared pointers to City objects.
     */
    const CityPtrTVector& getCities() const noexcept { return m_city; }

    /**
     * @brief Retrieves a reference to the vector of cities.
     *
     * This method provides read-write access to the list of cities managed by the CityManager.
     *
     * @return A reference to the vector of shared pointers to City objects.
     */
    CityPtrTVector& getCities() noexcept { return m_city; }
};

}