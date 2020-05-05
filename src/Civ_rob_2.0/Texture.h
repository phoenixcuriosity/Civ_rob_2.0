/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:0.20.2.1
	file version : 1.12

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


#ifndef Texture_H
#define Texture_H

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "LIB.h"

/* *********************************************************
 *						Constants						   *
 ********************************************************* */

//--- Constants related to the size of arrays ---------------------------------------------------------------------------------------------------

/* Define the max number of font */
const Uint8 MAX_FONT = 160;

/* Define a max angle to rotate Texture */
const Uint16 MAX_ANGLE = 360;

//--- Constants related to SDL  -----------------------------------------------------------------------------------------------------------------

/*
	SDL_Color name {Red, Green, Blue, Alpha (transparency)}
	Each parameter uses 8 bits -> Uint8  (from 0 to 255)
*/

const SDL_Color Black = { 0, 0, 0, 255 };
const SDL_Color White = { 255, 255, 255, 255 };
const SDL_Color Red = { 255, 0, 0, 255 };
const SDL_Color Green = { 0, 255, 0, 255 };
const SDL_Color Blue = { 0, 0, 255, 255 };
const SDL_Color Yellow = { 255, 255, 0, 255 };
const SDL_Color WriteColorButton = { 255, 64, 0, 255 }; // orange
const SDL_Color BackColorButton = { 64, 64, 64, 255 }; // gris
const SDL_Color NoColor = { 0, 0, 0, 0 };

// font use for the game
const std::string fontFile = "arial.ttf";

//--- Constants related to the screen  ----------------------------------------------------------------------------------------------------------

/* Define a pixel out of range of the screen on x */
#define SCREEN_MIN_X_OUT_OF_RANGE -1

/* Define a pixel out of range of the screen on y */
#define SCREEN_MIN_Y_OUT_OF_RANGE -1

/* *********************************************************
 *					 Enum								   *
 ********************************************************* */

// Define all State of the game, relate to screen
enum class State_Type : Uint8
{
	error,					/* ### Reserved on error detection ### */
	STATEtitleScreen,		/* Title screen : first screen selection */
	STATEscreennewgame,		/* New game screen : selection of options of a new game */
	STATEreload,			/* Load screen : selection of saves to load */
	STATEmainmap,			/* Maip map screen */
	STATEscience,			/* Science screen ### Not implemented as of 0.20.0.3  ### */
	STATEcitiemap			/* Citie map screen : Unit and buildings creation */
};

// Define all Selection in the game, relate to mouse click
enum class Select_Type : Uint8
{
	selectnothing,			/* Nothing is selected */
	selectcreate,			/* ### Reserved on debug as of 0.20.0.3 ### */
	selectinspect,			/* ### Reserved on debug as of 0.20.0.3 ### */
	selectmove,				/* Selection to move a Unit */
	selectmoveCitizen		/* ### Not use as of 0.20.0.3 ### */
};

//--- enum related to Texture -----------------------------------------------------------------------------------------------------------

/* Define Text type in SDL_ttf */
enum class Texte_Type : Uint8 
{
	blended,	/* No background color */
	shaded		/* With background color */
};

/* Define transparency type in SDL_ttf */
enum Transparance_Type : Uint8
{ 
	transparent = 0,			/* Total transparency */
	semiTransparent = 128,		/* Half transparency */
	nonTransparent = 255		/* No transparency  */
};

/* Define center type for Texture to print on the screen */
enum class Center_Type : Uint8
{
	nocenter,	/* Positions x and y are unchanged */
	center_x,	/* Positions y is unchanged and x is center depending on the length of the texte */
	center_y,	/* Positions x is unchanged and y is center depending on the height of the texte */
	center		/* Positions x and y are center depending on the length and the height of the texte */
};

/* 
 * Define rotation type to apply on Texture
 * The angle is in degrees (from 0 to 360)
 * ### TODO as of 0.20.0.3 : change type to double ###
 */
enum Rotation_Type : Uint16 
{
	no_angle,			/* No angle */
	inverse = 180		/* Rotate the Texture by 180 degrees */
};


/* *********************************************************
 *						 Classes						   *
 ********************************************************* */

  //--- Texture --------------------------------------------------------------------------------------------------------------------------------------
  /*
	  * La classe Texture permet de d'afficher des images sur la fenetre à partir de fichier image (.png, jpg, .bmp)
	  * Pour créer un objet Texture 2 méthodes peuvent etre utilisées :
	  *		1] utiliser LoadImage (recommandé)
	  *		2] directement utiliser le constructeur (préalable : déja avoir le ptr SDL_Texture)

  */
class Texture
{
public:
	/* *********************************************************
	 *					Texture::STATIC						   *
	 ********************************************************* */


	/* ---------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------- */
	/* NAME : loadImage																			*/
	/* ROLE : Dynamic allocation of the Texture with specifications								*/
	/* IN : SDL_Renderer*& renderer : Ptr on SDL_Renderer										*/
	/* OUT : std::unordered_map<std::string, Texture*>& : map where the Texture will be stored  */
	/* IN : Uint8 stateScreen : enum class State_Type											*/
	/* IN : Uint8 select : enum class Select_Type												*/
	/* IN : std::string path : Path to the picture											    */
	/* IN : std::string msg : Name of the Texture									  		    */
	/* IN : Uint8 alpha : enum Transparance_Type										 	    */
	/* IN : int x, int y : Positions before center of the Texture							    */
	/* IN : unsigned int w : length of the Texture (compute length of Picture if w == 0)	    */
	/* IN : unsigned int h : height of the Texture (compute height of Picture if h == 0)	    */
	/* IN : Uint16 angle : enum Rotation_Type : will compute modulo if over 360				    */
	/* IN : Uint8 cnt : enum class Center_Type											        */
	/* RETURNED VALUE    : void																	*/
	/* ---------------------------------------------------------------------------------------- */
	/* ---------------------------------------------------------------------------------------- */
	static void loadImage
	(
		SDL_Renderer*& renderer,
		std::unordered_map<std::string, Texture*>& tabTexture,
		State_Type stateScreen,
		Select_Type select,
		std::string path,
		std::string msg,
		Transparance_Type alpha,
		int x,
		int y,
		unsigned int w,
		unsigned int h,
		Uint16 angle,
		Center_Type cnt = Center_Type::nocenter
	);
		
	/*
	 * NAME : assertRangeAngle
	 * ROLE : Limitation sur 360°
	 * INPUT  PARAMETERS : Uint16* angle : angle de rotation
	 * OUTPUT PARAMETERS : angle %= MAX_ANGLE
	 * RETURNED VALUE    : void
	 */
	static void assertRangeAngle
	(
		Uint16* angle
	);

	/*
	 * NAME : deleteAll
	 * ROLE : Permet de centrer la Texture selon enum Center_Type
	 * INPUT  PARAMETERS : int& xc, int& yc : positions demandées
	 * INPUT  PARAMETERS : int iW, int iH : largeur et hauteur de la Texture
	 * INPUT  PARAMETERS : Uint8 cnt : type de centrage : par défaut nocenter
	 * OUTPUT PARAMETERS : Permet de centrer la Texture
	 * RETURNED VALUE    : void
	 */
	static void centrage
	(	
		int& xc,
		int& yc,
		int iW,
		int iH,
		Center_Type cnt = Center_Type::nocenter
	);

	
	
public:
	/* *********************************************************
	 *					Texture::METHODES					   *
	 ********************************************************* */

	Texture
	(	
		SDL_Renderer*& renderer,
		SDL_Texture* image,
		std::string msg,
		State_Type stateScreen,
		Select_Type select,
		unsigned int x,
		unsigned int y,
		int w,
		int h,
		Transparance_Type alpha,
		Uint16 angle,
		Center_Type center = Center_Type::nocenter
	);

	~Texture();


	/*
	 * NAME : rectangle
	 * ROLE : Création d'un SDL_Rect à partir des positions x, y et des longueur et hauteur
	 * INPUT  PARAMETERS : int xc, int yc, int w, int h : positions du rectangle
	 * OUTPUT PARAMETERS : Destruction des allocations dynamique du programme
	 * RETURNED VALUE    : SDL_Rect : Rectangle
	 */
	SDL_Rect rectangle
	(	
		int xc,
		int yc,
		int w, 
		int h
	);

	
public:
	/* *********************************************************
	 *				Texture::METHODES::Affichage			   *
	 ********************************************************* */

	/*
	 * NAME : render
	 * ROLE : Permet de rendre la Texture au coordonnées voulues
	 * INPUT  PARAMETERS : int = -1, int = -1 : coordonnées optionnelles
	 * OUTPUT PARAMETERS : rendre la Texture
	 * RETURNED VALUE    : void
	 */
	virtual void render
	(	
		int = SCREEN_MIN_X_OUT_OF_RANGE,
		int = SCREEN_MIN_Y_OUT_OF_RANGE
	);

	/*
	 * NAME : renderTextureTestStates
	 * ROLE : Test les attributs _stateScreen et _select qui correspondent
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Destruction des allocations dynamique du programme
	 * RETURNED VALUE    : void
	 */
	virtual bool renderTextureTestStates
	(	
		State_Type stateScreen,
		Select_Type select,
		int x = SCREEN_MIN_X_OUT_OF_RANGE,
		int y = SCREEN_MIN_Y_OUT_OF_RANGE
	);

	

public:
	/* *********************************************************
	 *				Texture::METHODES::GET/SET				   *
	 ********************************************************* */
	 
	 
	inline virtual SDL_Texture* GETtexture()const			{ return _texture; };
	inline virtual SDL_Texture* GETtextureNonConst()		{ return _texture; };
	inline virtual SDL_Rect GETdst()const					{ return _dst; };
	inline virtual SDL_Rect* GETdstPtr()					{ return &_dst; };
	inline virtual int GETdstx()const						{ return _dst.x; };
	inline virtual int GETdsty()const						{ return _dst.y; };
	inline virtual int GETdstw()const						{ return _dst.w; };
	inline virtual int GETdsth()const						{ return _dst.h; };
	inline virtual std::string GETname() const				{ return _name; };
	inline virtual State_Type GETstateScreen() const		{ return _stateScreen; };
	inline virtual Select_Type GETselect()const				{ return _select; };
	inline virtual Transparance_Type GETalpha()const		{ return _alpha; };
	inline virtual Center_Type GETcenter()const				{ return _center; };
	inline virtual Uint16 GETangle()const					{ return _angle; };

	inline virtual void SETtexture(SDL_Texture* texture)
	{
		if (_texture != texture)
		{
			if (_texture != nullptr)
			{
				SDL_DestroyTexture(_texture);
				_texture = nullptr;
			}
			_texture = texture;
		}
	};
	inline virtual void SETdstx(int x) { _dst.x = x; };
	inline virtual void SETdsty(int y) { _dst.y = y; };
	inline virtual void SETdstw(int w) { _dst.w = w; };
	inline virtual void SETdsth(int h) { _dst.h = h; };
	inline virtual void SETname(std::string msg) { _name = msg; };
	inline virtual void SETalpha(Transparance_Type alpha)
	{
		if (_alpha != alpha)
		{
			_alpha = alpha;
			if (SDL_SetTextureAlphaMod(_texture, _alpha) != 0)
				_alpha = (Transparance_Type)255;
		}
	}
	inline virtual void SETcenter(Center_Type cen)
	{
		if (_center != cen)
		{
			_center = cen;
			centrage(_dst.x, _dst.y, _dst.w, _dst.h, _center);
		}
	};
	inline virtual void SETangle(Uint16 angle) { _angle = angle; };

protected:
	inline SDL_Renderer *& GETrenderer() { return _renderer; };

	
private:
	/* *********************************************************
	 *				Texture::ATTRIBUTS						   *
	 ********************************************************* */

	// ptr sur le renderer crée par la SDL
	SDL_Renderer* _renderer;

	// ptr sur la SDL_Texture : image 
	SDL_Texture* _texture;

	// rectangle des positions en x et y et la longueur et hauteur
	SDL_Rect _dst;

	// nom de la Texture
	std::string _name;

	// ecran dans le quel la Texture s'affiche
	State_Type _stateScreen;

	// selection pour l'affichage
	Select_Type _select;

	// transparance de la Texture
	Transparance_Type _alpha;

	// centrage de la Texture (nocenter, center_x, center_y, center)
	Center_Type _center;

	// angle de rotation de la texture (0 = pas d'angle)
	Uint16 _angle;
};


//--- Texte ----------------------------------------------------------------------------------------------------------------------------------------

class Texte : public Texture
{


public:
	/* *********************************************************
	 *				Texte::STATIC							   *
	 ********************************************************* */
	 
	 
	/*
	 * NAME : createSDL_TextureFromTexte
	 * ROLE : Permet de créer un ptr sur une SDL_Texture
	 * ROLE : pour par la suite créer un objet Texte
	 * INPUT  PARAMETERS : SDL_Renderer*& renderer : le ptr sur la variable contenant SDL_Renderer
	 * INPUT  PARAMETERS : Uint8 type : enum Texte_Type
	 * INPUT  PARAMETERS : std::string message : Texte
	 * INPUT  PARAMETERS : SDL_Color color : couleur du Texte
     * INPUT  PARAMETERS : SDL_Color colorback : couleur du fond du Texte
	 * INPUT  PARAMETERS : TTF_Font* font : Taille de la font utilisée
	 * OUTPUT PARAMETERS : Permet de créer un ptr sur une SDL_Texture
	 * RETURNED VALUE    : SDL_Texture*
	 */
	static SDL_Texture* createSDL_TextureFromTexte
	(	
		SDL_Renderer*& renderer,
		Texte_Type type,
		std::string message,
		SDL_Color color,
		SDL_Color colorback,
		TTF_Font* font
	);

		
	/*
	 * NAME : loadTexte
	 * ROLE : création et ajout d'un objet Texte dans le tableau de Texte choisi
	 * INPUT  PARAMETERS : SDL_Renderer*& renderer : le ptr sur la variable contenant SDL_Renderer
	 * INPUT  PARAMETERS : TTF_Font* font[] : tableau de police de la font
	 * INPUT  PARAMETERS : Uint8 stateScreen, Uint8 select : les variables qui décrivent les différents état de l'écran et les spécifications de la séléction
	 * INPUT  PARAMETERS : std::vector<Texte*>& tabTexte : tableau de Texte* ou sera rangé le nouveau Texte
	 * INPUT  PARAMETERS : Uint8 type : enum Texte_Type
     * INPUT  PARAMETERS : std::string msg : Le Texte dans le tableau
	 * INPUT  PARAMETERS : SDL_Color color : couleur du Texte
     * INPUT  PARAMETERS : SDL_Color colorback : couleur du fond du Texte
	 * INPUT  PARAMETERS : Uint8 : la taille du Texte
	 * INPUT  PARAMETERS : int x, int y	: les valeurs en pixel de la future position
	 * INPUT  PARAMETERS : Uint8 alpha : la valeur de transparance de la Texture -> enum Transparance_Type
	 * INPUT  PARAMETERS : Uint16 angle : enum Uint16
	 * INPUT  PARAMETERS : Uint8 cnt : enum Center_Type
	 * OUTPUT PARAMETERS : création et ajout d'un objet Texte
	 * RETURNED VALUE    : void
	 */
	static void loadTexte
	(	
		SDL_Renderer*& renderer,
		TTF_Font* font[],
		State_Type stateScreen,
		Select_Type select,
		std::unordered_map<std::string, Texte*>& tabTexte,
		Texte_Type type,
		std::string msg,
		SDL_Color color,
		SDL_Color backcolor,
		Uint8 size,
		int x,
		int y,
		Transparance_Type alpha,
		Uint16 angle,
		Center_Type cnt = Center_Type::nocenter
	);


	/*
	 * NAME : writeTexte
	 * ROLE : créer un ptr sur SDL_Texture temporaire pour afficher le texte à l'écran
	 * ROLE : le ptr et la SDL_Texture sont détruit après l'affichage
	 * INPUT  PARAMETERS : SDL_Renderer*& renderer : le ptr sur la variable contenant SDL_Renderer
	 * INPUT  PARAMETERS : TTF_Font* font[] : tableau de police de la font
	 * INPUT  PARAMETERS : Uint8 type : enum Texte_Type
     * INPUT  PARAMETERS : std::string msg : Le Texte dans le tableau
	 * INPUT  PARAMETERS : SDL_Color color : couleur du Texte
     * INPUT  PARAMETERS : SDL_Color colorback : couleur du fond du Texte
	 * INPUT  PARAMETERS : Uint8 : la taille du Texte
	 * INPUT  PARAMETERS : int x, int y	: les valeurs en pixel de la future position
	 * INPUT  PARAMETERS : Uint8 alpha : la valeur de transparance de la Texture -> enum Transparance_Type
	 * INPUT  PARAMETERS : Uint16 angle : enum Uint16
	 * INPUT  PARAMETERS : Uint8 cnt : enum Center_Type
	 * OUTPUT PARAMETERS : créer un ptr sur SDL_Texture temporaire pour afficher le texte à l'écran
	 * RETURNED VALUE    : void
	 */
	static void writeTexte
	(	
		SDL_Renderer*& renderer,
		TTF_Font* font[],
		Texte_Type type,
		std::string msg,
		SDL_Color color,
		SDL_Color backcolor,
		Uint8 size,
		unsigned int x,
		unsigned int y,
		Uint16 angle,
		Center_Type cnt = Center_Type::nocenter
	);



public:
	/* *********************************************************
	 *				Texte::METHODES							   *
	 ********************************************************* */

	Texte
	(	
		SDL_Renderer*& renderer,
		TTF_Font* font[],
		SDL_Texture* image,
		std::string msg,
		State_Type stateScreen,
		Select_Type select,
		int x,
		int y,
		int w,
		int h,
		Texte_Type type,
		SDL_Color txtcolor,
		SDL_Color backcolor,
		Uint8 size,
		Transparance_Type alpha,
		Uint16 angle,
		Center_Type center = Center_Type::nocenter
	);

	~Texte();

	
	/*
	 * NAME : isSameColor
	 * ROLE : Comparaison de 2 couleurs SDL_Color
	 * INPUT  PARAMETERS : SDL_Color, SDL_Color: couleur à comparer
	 * OUTPUT PARAMETERS : Destruction des allocations dynamique du programme
	 * RETURNED VALUE    : bool : false = pas les meme/ true = meme couleur
	 */
	virtual bool isSameColor
	(	
		SDL_Color,
		SDL_Color
	) const;


	/*
	 * NAME : resizeTexte
	 * ROLE : recentre le Texte lors de changement de taille du texte
	 * INPUT  PARAMETERS : void
	 * OUTPUT PARAMETERS : recentre le Texte lors de changement de taille du texte
	 * RETURNED VALUE    : void
	 */
	virtual void resizeTexte();

	
	
public:
	/* *********************************************************
	 *				Texte::METHODES::GET/SET				   *
	 ********************************************************* */

	inline virtual Texte_Type GETtype()const				{ return _type; };
	inline virtual SDL_Color GETtxtcolor() const	{ return _txtcolor; };
	inline virtual SDL_Color GETbackcolor() const	{ return _backcolor; };
	inline virtual Uint8 GETsize()const				{ return _size; };

	virtual void SETname(std::string msg);
	virtual void SETtype(Texte_Type type);
	virtual void SETsize(Uint8 type);
	virtual void SETtxtcolor(SDL_Color txtcolor);
	virtual void SETbackcolor(SDL_Color backcolor);

protected:
	inline TTF_Font** GETfont() { return _font; };

	
	
private:
	/* *********************************************************
	 *					Texte::ATTRIBUTS					   *
	 ********************************************************* */
	
	
	// tableau des différents polices de la font 
	TTF_Font* _font[MAX_FONT];

	/*
		* type de texte :
		*	-> blended : sans couleur de fond
		*	-> shaded : avec une couleur de fond
	*/
	Texte_Type _type;

	// couleur appliquée au texte
	SDL_Color _txtcolor;

	// couleur appliquée au sous texte
	SDL_Color _backcolor;

	// taile du texte (int 1 - 160)
	Uint8 _size;
};

//--- ButtonImage ---------------------------------------------------------------------------------------------------------------------------------------

class ButtonImage : public Texture
{

public:
	/* *********************************************************
	 *					ButtonImage::STATIC					   *
	 ********************************************************* */
	 

	/*
	 * NAME : createButtonImage
	 * ROLE : création et ajout d'un objet ButtonTexte dans le tableau de ButtonTexte choisi
	 * INPUT  PARAMETERS : SDL_Renderer*& renderer : le ptr sur la variable contenant SDL_Renderer
	 * INPUT  PARAMETERS : std::vector<ButtonImage*>& : le tableau dans lequel sera stocké la ButtonImage (allocation dynamique)
	 * INPUT  PARAMETERS : Uint8 stateScreen, Uint8 select : les variables qui décrivent les différents état de l'écran et les spécifications de la séléction
	 * INPUT  PARAMETERS : std::string path : le chemin d'accès ainsi que le nom de l'image à partir du fichier (inclure le type .png , .bmp ...)
     * INPUT  PARAMETERS : std::string msg : le nom qui permettra d'identifier la Texture dans le tableau
	 * INPUT  PARAMETERS : Uint8 alpha : la valeur de transparance de la Texture -> enum Transparance_Type
	 * INPUT  PARAMETERS : int x, int y	: les valeurs en pixel de la future position
	 * INPUT  PARAMETERS : unsigned int w, unsigned int h : les valeurs de longueur et de largeur permettant de changer la définition de l'image originale sinon mettre NULL
	 * INPUT  PARAMETERS : Uint16 angle : enum Uint16
	 * INPUT  PARAMETERS : Uint8 cnt : le type de centrage -> enum Center_Type
	 * OUTPUT PARAMETERS : création et ajout d'un objet ButtonTexte
	 * RETURNED VALUE    : void
	 */
	static void createButtonImage
	(	
		SDL_Renderer*& renderer,
		std::unordered_map<std::string,ButtonImage*>& tabButtonImage,
		State_Type stateScreen,
		Select_Type select,
		std::string path,
		std::string msg,
		Transparance_Type alpha,
		int x,
		int y,
		unsigned int w,
		unsigned int h,
		Uint16 angle,
		Center_Type cnt = Center_Type::nocenter
	);


public:
	/* *********************************************************
	 *					ButtonImage::METHODES				   *
	 ********************************************************* */

	ButtonImage
	(	
		SDL_Renderer*& renderer,
		SDL_Texture* image,
		const std::string& msg,
		State_Type stateScreen,
		Select_Type select,
		int x,
		int y, 
		int w, 
		int h,
		Transparance_Type alpha, 
		Uint16 angle,
		SDL_Texture* imageOn,
		Center_Type center = Center_Type::nocenter
	);

	~ButtonImage();


	/*
	 * NAME : searchButtonImage
	 * ROLE : Recherche si les coordonnées en entrée sont celles du bouton
	 * INPUT  PARAMETERS : Uint8 stateScreen : enum State_Type
	 * INPUT  PARAMETERS : signed int x, signed int y : coordonnées souris
	 * OUTPUT PARAMETERS : Validation ou non du bouton
	 * RETURNED VALUE    : bool : false = pas valide / true = valide
	 */
	virtual bool searchButtonImage
	(	
		State_Type stateScreen,
		signed int x,
		signed int y
	);


	/*
	 * NAME : renderButtonImage
	 * ROLE : Affiche le bouton si le contexte est valide
	 * INPUT  PARAMETERS : Uint8 stateScreen :  enum State_Type
	 * OUTPUT PARAMETERS : Affiche le bouton
	 * RETURNED VALUE    : bool : false = non affiché / true = affichage
	 */
	virtual bool renderButtonImage
	(
		State_Type stateScreen
	);


	/*
	 * NAME : changeOn
	 * ROLE : alterne l'attribut booléen _on
	 * INPUT  PARAMETERS : void
	 * OUTPUT PARAMETERS : alterne l'attribut booléen _on
	 * RETURNED VALUE    : void
	 */
	virtual void changeOn();

	
public:
	/* *********************************************************
	 *			  ButtonImage::METHODES::GET/SET			   *
	 ********************************************************* */

	 
	inline virtual SDL_Texture* GETimageOn() const 	{return _imageOn;};
	inline virtual bool GETon() const				{return _on;};

	inline virtual void SETalpha(Transparance_Type alpha)
	{
		this->SETalpha(alpha);
		SDL_SetTextureAlphaMod(this->GETtextureNonConst(), this->GETalpha());
		SDL_SetTextureAlphaMod(_imageOn, this->GETalpha());
	};
	inline virtual void SETon(bool on) { _on = on; };
	
	


private:
	/* *********************************************************
	 *				ButtonImage::ATTRIBUTS					   *
	 ********************************************************* */

	// ptr sur la SDL_Texture : image du bouton activé
	SDL_Texture* _imageOn;

	// bouton on/off : permet de changer la couleur du bouton
	bool _on;
};


//--- ButtonTexte ---------------------------------------------------------------------------------------------------------------------------------------
/*

	ButtonTexte :
	Cette classe est la représentation d'un objet ButtonTextes qui est heritié de la classe mère Texte

	Un ButtonTextes est défini par une image et une imageOn qui sont contenu dans SDL_Texture* de la classe mère et celle-ci
	Cet objet hérite de tous les attributs de la classe Texture
	_on représente l'état du bouton l'image est normal ou On

	searchButtonTexte permet de chercher le bouton en fonction de son nom ainsi que de l'ecran et de la position x,y
	renderButtonTexteTexte permet d'afficher le bouton avec l'aide de la fonction de la SDL2.0.6 SDL_RenderCopy
	resetOnstateScreen permet de reset l'image si l'on n'est plus sur la bonne séléction ou sur le bon écran
	resetOnPlayer permet de reset l'image si le joueur séléctionner n'est plus le meme
	changeOn permet de changer entre l'imageOn et l'image

*/
class ButtonTexte : public Texte
{
public:
	/* *********************************************************
	 *				ButtonTexte::STATIC						   *
	 ********************************************************* */
	 

	/*
	 * NAME : createButtonTexte
	 * ROLE : création et ajout d'un objet ButtonTexte dans le tableau de ButtonTexte choisi
	 * INPUT : SDL_Renderer*& renderer : le ptr sur la variable contenant SDL_Renderer
	 * INPUT : TTF_Font* font[] : tableau de police de la font
	 * INPUT : Uint8 stateScreen, Uint8 select : les variables qui décrivent les différents état de l'écran et les spécifications de la séléction
	 * INPUT : std::vector<ButtonTexte*>& : le tableau dans lequel sera stocké la ButtonTexte (allocation dynamique)
	 * INPUT : Uint8 type : enum Texte_Type
     * INPUT : std::string msg : le nom qui permettra d'identifier la Texture dans le tableau
	 * INPUT : SDL_Color color : couleur du Texte
	 * INPUT : SDL_Color colorback : couleur du fond du Texte
	 * INPUT : Uint8 : la taille du Texte
	 * INPUT : int x, int y	: les valeurs en pixel de la future position
	 * INPUT : Uint8 alpha : la valeur de transparance de la Texture -> enum Transparance_Type
	 * INPUT : Uint16 angle : enum Uint16
	 * INPUT : Uint8 cnt : le type de centrage -> enum Center_Type
	 * OUTPUT : création et ajout d'un objet ButtonTexte
	 * RETURNED VALUE    : void
	 */
	static void createButtonTexte
	(	
		SDL_Renderer*& renderer,
		TTF_Font* font[],
		State_Type stateScreen,
		Select_Type select,
		std::unordered_map<std::string, ButtonTexte*>& tabButtonTexte,
		Texte_Type type,
		std::string msg,
		SDL_Color color,
		SDL_Color backcolor,
		Uint8 size,
		int x,
		int y,
		Transparance_Type alpha,
		Uint16 angle,
		Center_Type centerButtonTexte = Center_Type::nocenter
	);

	static void createButtonTexte
	(
		SDL_Renderer*& renderer,
		TTF_Font* font[],
		State_Type stateScreen,
		Select_Type select,
		DequeButtonTexte& tabButtonTexte,
		Texte_Type type,
		std::string msg,
		SDL_Color color,
		SDL_Color backcolor,
		Uint8 size,
		int x,
		int y,
		Transparance_Type alpha,
		Uint16 angle,
		Center_Type centerButtonTexte
	);



public:
	/* *********************************************************
	 *				ButtonTexte::METHODES					   *
	 ********************************************************* */

	ButtonTexte
	(	
		SDL_Renderer *renderer,
		TTF_Font *font[],
		SDL_Texture* image,
		std::string msg,
		State_Type stateScreen,
		Select_Type select,
		int x,
		int y,
		int w,
		int h,
		Texte_Type type,
		SDL_Color txtcolor,
		SDL_Color backcolor,
		Uint8 size,
		Transparance_Type alpha,
		Uint16 angle,
		SDL_Texture* imageOn,
		Center_Type center = Center_Type::nocenter
	);


	~ButtonTexte();


	/*
	 * NAME : searchButtonTexte
	 * ROLE : Recherche le bouton aux coordonnées en entrée
	 * INPUT  PARAMETERS : Uint8 stateScreen :  enum State_Type
	 * INPUT  PARAMETERS : signed int x, signed int y : coordonnées en entrée
	 * OUTPUT PARAMETERS : Validation ou non
	 * RETURNED VALUE    : bool : false = non valide / true = valide
	 */
	virtual bool searchButtonTexte
	(	
		State_Type stateScreen,
		signed int x,
		signed int y
	);


	/*
	 * NAME : resetOnstateScreen
	 * ROLE : Reset l'état _on des boutons
	 * INPUT  PARAMETERS : Uint8 select, unsigned int selectnothing : enum State_Type
	 * OUTPUT PARAMETERS : Reset l'état _on des boutons
	 * RETURNED VALUE    : void
	 */
	virtual void resetOnstateScreen
	(	
		Select_Type select
	);


	/*
	 * NAME : resetOnPlayer
	 * ROLE : Reset l'état _on des boutons
	 * INPUT  PARAMETERS : unsigned int : joueur sélectionné
	 * INPUT  PARAMETERS : std::vector<std::string> : tableau de nom des joueurs
	 * OUTPUT PARAMETERS : Initialisation de map.screen et map.maps
	 * RETURNED VALUE    : void
	 */
	virtual void resetOnPlayer
	(	
		unsigned int selectplayer,
		std::vector<std::string> tabPlayerName
	);


	/*
	 * NAME : renderButtonTexte
	 * ROLE : Affichage du ButtonTexte en fonction du contexte
	 * INPUT  PARAMETERS : Uint8 stateScreen :  enum State_Type
	 * INPUT  PARAMETERS : int x = -1, int y = -1 : positions optionnelles
	 * INPUT  PARAMETERS : Uint8 center = nocenter : enum Center_Type
	 * OUTPUT PARAMETERS : Initialisation de map.screen et map.maps
	 * RETURNED VALUE    : bool : false = non afficher / true = affichage
	 */
	virtual bool renderButtonTexte
	(
		State_Type stateScreen,
		int x = SCREEN_MIN_X_OUT_OF_RANGE,
		int y = SCREEN_MIN_Y_OUT_OF_RANGE,
		Center_Type center = Center_Type::nocenter
	);


	/*
	 * NAME : changeOn
	 * ROLE : alterne l'attribut booléen _on
	 * INPUT  PARAMETERS : void
	 * OUTPUT PARAMETERS : alterne l'attribut booléen _on
	 * RETURNED VALUE    : void
	 */
	virtual void changeOn();



public:
	/* *********************************************************
	 *			ButtonTexte::METHODES::GET/SET				   *
	 ********************************************************* */


	virtual SDL_Texture* GETimageOn() const {return _imageOn;};
	virtual bool GETon() const 				{return _on;};

	virtual void SETalpha(Transparance_Type alpha)
	{
		this->SETalpha(alpha);
		SDL_SetTextureAlphaMod(this->GETtextureNonConst(), this->GETalpha());
		SDL_SetTextureAlphaMod(_imageOn, this->GETalpha());
	};
	virtual void SETon(bool on) { _on = on;};
	



private:
	/* *********************************************************
	 *				ButtonTexte::ATTRIBUTS					   *
	 ********************************************************* */

	// ptr sur la SDL_Texture : image du bouton activé
	SDL_Texture* _imageOn;

	// bouton on/off : permet de changer la couleur du bouton
	bool _on;
};
#endif /* Texture_H */

/*
*	End Of File : Texture.h
*/