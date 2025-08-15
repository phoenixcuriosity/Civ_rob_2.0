/*

    Civ_rob_2
    Copyright SAUTER Robin 2017-2025 (robin.sauter@orange.fr)

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

#include <R2D/src/IMainGame.h>

#include <memory>

class CityScreen;
class GamePlayScreen;
class MainMenuScreen;
class NewGameScreen;
class ReloadMenuScreen;

/**
 * @class App
 * @brief The main application class derived from IMainGame.
 */
class App : public R2D::IMainGame
{
private:
    static constexpr char FILE_PATH_CONFIG[] = "bin/filePath.json"; ///< Path to the configuration file.

private:
    using MainMenuScreenPtrT = std::shared_ptr<MainMenuScreen>; ///< Type alias for a shared pointer to MainMenuScreen.
    using NewGameScreenPtrT = std::shared_ptr<NewGameScreen>; ///< Type alias for a shared pointer to NewGameScreen.
    using ReloadMenuScreenPtrT = std::shared_ptr<ReloadMenuScreen>; ///< Type alias for a shared pointer to ReloadMenuScreen.
    using GamePlayScreenPtrT = std::shared_ptr<GamePlayScreen>; ///< Type alias for a shared pointer to GamePlayScreen.
    using CityScreenPtrT = std::shared_ptr<CityScreen>; ///< Type alias for a shared pointer to CityScreen.

public:
    /**
     * @brief Constructor for the App class.
     */
    App();

    /**
     * @brief Destructor for the App class.
     */
    ~App();

    /**
     * @brief Initializes the application.
     */
    void onInit() override;

    /**
     * @brief Initializes the shaders.
     */
    void InitShaders() override;

    /**
     * @brief Exits the application.
     */
    void onExit() override;

    /**
     * @brief Adds the screens to the application.
     */
    void addScreens() override;

    /**
     * @brief Initializes the textures.
     */
    void InitTexture() override;

    /**
     * @brief Initializes the main components of the application.
     */
    void initMain();

    /**
     * @brief Destroys the application components.
     */
    void destroy();

private:
    MainMenuScreenPtrT m_mainMenuScreen; ///< Pointer to the main menu screen.
    NewGameScreenPtrT m_newGameScreen; ///< Pointer to the new game screen.
    ReloadMenuScreenPtrT m_reloadMenuScreen; ///< Pointer to the reload menu screen.
    GamePlayScreenPtrT m_gamePlayScreen; ///< Pointer to the gameplay screen.
    CityScreenPtrT m_CityScreen; ///< Pointer to the city screen.
};