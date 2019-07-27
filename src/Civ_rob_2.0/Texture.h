/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.15
	file version : 1.7

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
#include "LIB.h"

#ifndef Texture_H
#define Texture_H

/* *********************************************************
 *					 Constantes							   *
 ********************************************************* */

  //--- Constantes concernant la taille des différents tableaux  --------------------------------------------------------------------------------------

  // nombre maximal de polices de la font (ici arial)
const Uint8 MAX_FONT = 160;

//--- Constantes concernant la SDL  -----------------------------------------------------------------------------------------------------------------

/*
	SDL_Color name {Red, Green, Blue, Alpha (transparance)}
	chaque parametre est codé sur 8 bit -> Uint8  (de 0 à 255)
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

// font utilisée pour ce programme
const std::string fontFile = "arial.ttf";



/* *********************************************************
 *					 Enum								   *
 ********************************************************* */

  //--- enum concernant les objets Texture  -----------------------------------------------------------------------------------------------------------

  /*
	  * type de texte :
	  *	-> blended : sans couleur de fond
	  *	-> shaded : avec une couleur de fond
  */
enum Texte_Type : Uint8 { blended, shaded };

/*
	* type de transparance :
	*	-> 0 transparance totale
	*	-> 255 totalement visible
*/
enum Transparance_Type : Uint8 { transparent = 0, semiTransparent = 128, nonTransparent = 255 };

/*
	* type de centrage :
	*	-> nocenter : les positions x et y ne changent pas
	*	-> center_x : la position y ne change pas et centre la position x en focntion de la longueur du texte
	*	-> center_y : la position x ne change pas et centre la position y en focntion de hauteur du texte
	*	-> center : centre totalement le texte en fonction de sa longueur et de sa hauteur
*/
enum Center_Type : Uint8 { nocenter, center_x, center_y, center };

/*
	* type de rotation des textures
	* valeur en degrès
	* par défaut les textures n'ont pas d'angle
*/
enum Rotation_Type : Uint16 { no_angle, inverse = 180 };








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

	 
	/*
	 * NAME : loadImage
	 * ROLE : Allocation dynamique d'une Texture avec ses caractéristiques
	 * INPUT  PARAMETERS : SDL_Renderer*& renderer : le ptr sur la variable contenant SDL_Renderer
	 * INPUT  PARAMETERS : std::vector<Texture*>& tabTexture : le tableau dans lequel sera stocké la Texture (allocation dynamique)
	 * INPUT  PARAMETERS : Uint8 stateScreen, Uint8 select : les variables qui décrivent les différents état de l'écran et les spécifications de la séléction
	 * INPUT  PARAMETERS : std::string path : le chemin d'accès ainsi que le nom de l'image à partir du fichier (inclure le type .png , .bmp ...)
     * INPUT  PARAMETERS : std::string msg : le nom qui permettra d'identifier la Texture dans le tableau
	 * INPUT  PARAMETERS : Uint8 alpha : la valeur de transparance de la Texture -> enum Transparance_Type
	 * INPUT  PARAMETERS : int x, int y	: les valeurs en pixel de la future position
	 * INPUT  PARAMETERS : unsigned int w, unsigned int h : les valeurs de longueur et de largeur permettant de changer la définition de l'image originale sinon mettre NULL
	 * INPUT  PARAMETERS : Uint16 angle : enum Rotation_Type
	 * INPUT  PARAMETERS : Uint8 cnt : le type de centrage -> enum Center_Type
	 * OUTPUT PARAMETERS : Allocation dynamique d'une Texture dans le tableau correspondant
	 * RETURNED VALUE    : void
	 */
	static void loadImage(	SDL_Renderer*& renderer,
							std::vector<Texture*>& tabTexture,
							Uint8 stateScreen,
							Uint8 select,
							std::string path,
							std::string msg,
							Transparance_Type alpha,
							int x,
							int y,
							unsigned int w,
							unsigned int h,
							Rotation_Type angle,
							Center_Type cnt = nocenter
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
	static void centrage(	int& xc,
							int& yc,
							int iW,
							int iH,
							Center_Type cnt = nocenter
						);

	
	
public:
	/* *********************************************************
	 *					Texture::METHODES					   *
	 ********************************************************* */

	Texture(	SDL_Renderer*& renderer,
				SDL_Texture* image,
				std::string msg,
				Uint8 stateScreen,
				Uint8 select,
				unsigned int x,
				unsigned int y,
				int w,
				int h,
				Transparance_Type alpha,
				Rotation_Type angle,
				Center_Type center = nocenter
			);
	~Texture();


	/*
	 * NAME : rectangle
	 * ROLE : Création d'un SDL_Rect à partir des positions x, y et des longueur et hauteur
	 * INPUT  PARAMETERS : int xc, int yc, int w, int h : positions du rectangle
	 * OUTPUT PARAMETERS : Destruction des allocations dynamique du programme
	 * RETURNED VALUE    : SDL_Rect : Rectangle
	 */
	SDL_Rect rectangle(	int xc,
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
	virtual void render(	int = -1,
							int = -1
						);

	/*
	 * NAME : renderTextureTestStates
	 * ROLE : Test les attributs _stateScreen et _select qui correspondent
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Destruction des allocations dynamique du programme
	 * RETURNED VALUE    : void
	 */
	virtual bool renderTextureTestStates(	Uint8 stateScreen,
											Uint8 select,
											int x = -1,
											int y = -1
										);

	

public:
	/* *********************************************************
	 *				Texture::METHODES::GET/SET				   *
	 ********************************************************* */
	 
	 
	inline virtual SDL_Texture* GETtexture() const { return _texture; };
	inline virtual SDL_Texture* GETtextureNonConst() { return _texture; };
	inline virtual SDL_Rect GETdst()const { return _dst; };
	inline virtual int GETdstx()const { return _dst.x; };
	inline virtual int GETdsty()const { return _dst.y; };
	inline virtual int GETdstw()const { return _dst.w; };
	inline virtual int GETdsth()const { return _dst.h; };
	inline virtual std::string GETname() const { return _name; };
	inline virtual Uint8 GETstateScreen() const { return _stateScreen; };
	inline virtual Uint8 GETselect()const { return _select; };
	inline virtual Transparance_Type GETalpha()const { return _alpha; };
	inline virtual Center_Type GETcenter()const { return _center; };
	inline virtual Rotation_Type GETangle()const { return _angle; };

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
	inline virtual void SETangle(Rotation_Type angle) { _angle = angle; };

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

	// ecran dans le quel la Texture s'affiche (titre, play, score)
	Uint8 _stateScreen;

	// selection pour l'affichage (selectnothing, pause, win, lost)
	Uint8 _select;

	// transparance de la Texture
	Transparance_Type _alpha;

	// centrage de la Texture (nocenter, center_x, center_y, center)
	Center_Type _center;

	// angle de rotation de la texture (0 = pas d'angle)
	Rotation_Type _angle;
};
#endif /* Texture_H */







#ifndef Texte_H
#define Texte_H
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
	static SDL_Texture* createSDL_TextureFromTexte(	SDL_Renderer*& renderer,
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
	 * INPUT  PARAMETERS : Uint16 angle : enum Rotation_Type
	 * INPUT  PARAMETERS : Uint8 cnt : enum Center_Type
	 * OUTPUT PARAMETERS : création et ajout d'un objet Texte
	 * RETURNED VALUE    : void
	 */
	static void loadTexte(	SDL_Renderer*& renderer,
							TTF_Font* font[],
							Uint8 stateScreen,
							Uint8 select,
							std::vector<Texte*>& tabTexte,
							Texte_Type type,
							std::string msg,
							SDL_Color color,
							SDL_Color backcolor,
							Uint8 size,
							int x,
							int y,
							Transparance_Type alpha,
							Rotation_Type angle,
							Center_Type cnt = nocenter
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
	 * INPUT  PARAMETERS : Uint16 angle : enum Rotation_Type
	 * INPUT  PARAMETERS : Uint8 cnt : enum Center_Type
	 * OUTPUT PARAMETERS : créer un ptr sur SDL_Texture temporaire pour afficher le texte à l'écran
	 * RETURNED VALUE    : void
	 */
	static void writeTexte(	SDL_Renderer*& renderer,
							TTF_Font* font[],
							Texte_Type type,
							std::string msg,
							SDL_Color color,
							SDL_Color backcolor,
							Uint8 size,
							unsigned int x,
							unsigned int y,
							Rotation_Type angle,
							Center_Type cnt = nocenter
						);



public:
	/* *********************************************************
	 *				Texte::METHODES							   *
	 ********************************************************* */

	Texte(	SDL_Renderer*& renderer,
			TTF_Font* font[],
			SDL_Texture* image,
			std::string msg,
			Uint8 stateScreen,
			Uint8 select,
			int x,
			int y,
			int w,
			int h,
			Texte_Type type,
			SDL_Color txtcolor,
			SDL_Color backcolor,
			Uint8 size,
			Transparance_Type alpha,
			Rotation_Type angle,
			Center_Type center = nocenter
		);
	~Texte();

	
	/*
	 * NAME : isSameColor
	 * ROLE : Comparaison de 2 couleurs SDL_Color
	 * INPUT  PARAMETERS : SDL_Color, SDL_Color: couleur à comparer
	 * OUTPUT PARAMETERS : Destruction des allocations dynamique du programme
	 * RETURNED VALUE    : bool : false = pas les meme/ true = meme couleur
	 */
	virtual bool isSameColor(	SDL_Color,
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
#endif /* Texte_H */








#ifndef ButtonImage_H
#define ButtonImage_H
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
	 * INPUT  PARAMETERS : Uint16 angle : enum Rotation_Type
	 * INPUT  PARAMETERS : Uint8 cnt : le type de centrage -> enum Center_Type
	 * OUTPUT PARAMETERS : création et ajout d'un objet ButtonTexte
	 * RETURNED VALUE    : void
	 */
	static void createButtonImage(	SDL_Renderer*& renderer,
									std::vector<ButtonImage*>& tabButtonImage,
									Uint8 stateScreen,
									Uint8 select,
									std::string path,
									std::string msg,
									Transparance_Type alpha,
									int x,
									int y,
									unsigned int w,
									unsigned int h,
									Rotation_Type angle,
									Center_Type cnt = nocenter
								);


public:
	/* *********************************************************
	 *					ButtonImage::METHODES				   *
	 ********************************************************* */

	ButtonImage(	SDL_Renderer*& renderer,
					SDL_Texture* image,
					const std::string& msg,
					Uint8 stateScreen,
					Uint8 select,
					int x,
					int y, 
					int w, 
					int h,
					Transparance_Type alpha, 
					Rotation_Type angle,
					SDL_Texture* imageOn,
					Center_Type center = nocenter
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
	virtual bool searchButtonImage(	Uint8 stateScreen,
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
	virtual bool renderButtonImage(Uint8 stateScreen);


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
#endif /* ButtonImage_H */








#ifndef ButtonTexte_H
#define ButtonTexte_H
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
	 * INPUT  PARAMETERS : SDL_Renderer*& renderer : le ptr sur la variable contenant SDL_Renderer
	 * INPUT  PARAMETERS : TTF_Font* font[] : tableau de police de la font
	 * INPUT  PARAMETERS : Uint8 stateScreen, Uint8 select : les variables qui décrivent les différents état de l'écran et les spécifications de la séléction
	 * INPUT  PARAMETERS : std::vector<ButtonTexte*>& : le tableau dans lequel sera stocké la ButtonTexte (allocation dynamique)
	 * INPUT  PARAMETERS : Uint8 type : enum Texte_Type
     * INPUT  PARAMETERS : std::string msg : le nom qui permettra d'identifier la Texture dans le tableau
	 * INPUT  PARAMETERS : SDL_Color color : couleur du Texte
	 * INPUT  PARAMETERS : SDL_Color colorback : couleur du fond du Texte
	 * INPUT  PARAMETERS : Uint8 : la taille du Texte
	 * INPUT  PARAMETERS : int x, int y	: les valeurs en pixel de la future position
	 * INPUT  PARAMETERS : Uint8 alpha : la valeur de transparance de la Texture -> enum Transparance_Type
	 * INPUT  PARAMETERS : Uint16 angle : enum Rotation_Type
	 * INPUT  PARAMETERS : Uint8 cnt : le type de centrage -> enum Center_Type
	 * OUTPUT PARAMETERS : création et ajout d'un objet ButtonTexte
	 * RETURNED VALUE    : void
	 */
	static void createButtonTexte(	SDL_Renderer*& renderer,
									TTF_Font* font[],
									Uint8 stateScreen,
									Uint8 select,
									std::vector<ButtonTexte*>& tabButtonTexte,
									Texte_Type type,
									std::string msg,
									SDL_Color color,
									SDL_Color backcolor,
									Uint8 size,
									int x,
									int y,
									Transparance_Type alpha,
									Rotation_Type angle,
									Center_Type centerButtonTexte = nocenter
								);



public:
	/* *********************************************************
	 *				ButtonTexte::METHODES					   *
	 ********************************************************* */

	ButtonTexte(	SDL_Renderer *renderer,
					TTF_Font *font[],
					SDL_Texture* image,
					std::string msg,
					Uint8 stateScreen,
					Uint8 select,
					int x,
					int y,
					int w,
					int h,
					Texte_Type type,
					SDL_Color txtcolor,
					SDL_Color backcolor,
					Uint8 size,
					Transparance_Type alpha,
					Rotation_Type angle,
					SDL_Texture* imageOn,
					Center_Type center = nocenter
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
	virtual bool searchButtonTexte(	Uint8 stateScreen,
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
	virtual void resetOnstateScreen(	Uint8 select,
										unsigned int selectnothing
									);


	/*
	 * NAME : resetOnPlayer
	 * ROLE : Reset l'état _on des boutons
	 * INPUT  PARAMETERS : unsigned int : joueur sélectionné
	 * INPUT  PARAMETERS : std::vector<std::string> : tableau de nom des joueurs
	 * OUTPUT PARAMETERS : Initialisation de map.screen et map.maps
	 * RETURNED VALUE    : void
	 */
	virtual void resetOnPlayer(	unsigned int selectplayer,
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
	virtual bool renderButtonTexte(	Uint8 stateScreen,
									int x = -1,
									int y = -1,
									Center_Type center = nocenter
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
#endif /* ButtonTexte_H */

/*
*	End Of File : Texture.h
*/