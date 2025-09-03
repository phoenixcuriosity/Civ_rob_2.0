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

#include <R2D/src/IRegister.h>
#include "City.h"

class Player;

namespace city
{

/**
 * @class CityFactory
 * @brief A factory class for creating and managing City objects.
 *
 * The CityFactory class provides methods to create new City instances and manage their initialization.
 * It also interacts with the game map and player data to properly configure cities.
 */
class CityFactory
{
private:
    using Coor = R2D::Coor; ///< Alias for coordinates used in the game.
    using CityName = std::string; ///< Alias for the name of a city.
    using CityPtrT = std::shared_ptr<City>; ///< Alias for a shared pointer to a City object.
    using PlayerPtrT = std::shared_ptr<Player>;
    using VectMapPtr = std::vector<Tile*>; ///< Alias for a vector of pointers to Tile objects.

    /**
     * @brief Adds a subscriber to the register.
     *
     * This method is used internally to manage subscriptions for the factory.
     *
     * @return A vector of register pairs.
     */
    R2D::RegisterPairVector addSubscriber();

public:
    /**
     * @struct CityNamePlayerId
     * @brief Represents a structure containing player ID and city vector size.
     *
     * This structure is used to associate a player with their cities.
     */
    struct CityNamePlayerId
    {
        int playerId = 0; ///< The ID of the player.
        size_t cityVectSize = 0; ///< The size of the city vector for the player.
    };

public:
    /**
     * @brief Constructs a new CityFactory object.
     */
    CityFactory();

    /**
     * @brief Creates a new City object.
     *
     * This method creates a new City instance with default parameters.
     *
     * @return A shared pointer to the newly created City object.
     */
    CityPtrT CreateCity(const PlayerPtrT& player);

    /**
     * @brief Creates a new City object with specific parameters.
     *
     * This method creates a new City instance and initializes it with the given parameters.
     *
     * @param id A structure containing the player ID and city vector size.
     * @param coor The coordinates where the city will be created.
     * @param tiles A vector of pointers to tiles that the city will occupy.
     * @return A shared pointer to the newly created City object.
     */
    CityPtrT CreateCity(const CityNamePlayerId& id, const Coor coor, VectMapPtr& tiles, const PlayerPtrT& player);

private:
    R2D::RegisterPtrT m_loader;
};

}