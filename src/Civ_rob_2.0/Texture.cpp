/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.22.0.0
	file version : 1.16

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

#include "Texture.h"
#include "civ_lib.h"
#include "LoadConfig.h"
#include "End.h"

/* *********************************************************
 *						 Static Var						   *
 ********************************************************* */

static VectorTexte staticIndexVectorTextes;

/* *********************************************************
 *				START Texture::STATIC					   *
 ********************************************************* */


/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : loadImage																			*/
/* ROLE : Dynamic allocation of the Texture with specifications								*/
/* RETURNED VALUE : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
void Texture::loadImage
(	
	SDL_Renderer*& renderer,								/* IN : Ptr on SDL_Renderer */
	std::unordered_map<std::string, Texture*>& tabTexture,  /* OUT : map where the Texture will be stored */
	State_Type stateScreen,									/* IN : enum class State_Type */
	Select_Type select,										/* IN : Select_Type */		
	std::string path,										/* IN : Path to the picture */
	std::string msg,										/* IN : Name of the Texture */
	Transparance_Type alpha,								/* IN : enum Transparance_Type */					
	int x,													/* IN : Position x before center of the Texture */
	int y,													/* IN : Position y before center of the Texture */
	unsigned int w,											/* IN : length of the Texture(compute length of Picture if w == 0) */
	unsigned int h,											/* IN : height of the Texture(compute height of Picture if h == 0) */
	Uint16 angle,											/* IN : enum Rotation_Type : will compute modulo if over 360 */
	Center_Type cnt											/* IN : Uint8 cnt : enum class Center_Type */
)
{
	int xt(0), yt(0), wt(0), ht(0);
	if (SCREEN_MIN_X_OUT_OF_RANGE < x)
	{
		xt = x;
	}
	if (SCREEN_MIN_Y_OUT_OF_RANGE < y)
	{
		yt = y;
	}

	assertRangeAngle(&angle);

	SDL_Texture* newTexture(nullptr);
	SDL_Surface* loadedSurface(IMG_Load(path.c_str()));
	if (w == 0 && h == 0)
	{
		wt = loadedSurface->w;
		ht = loadedSurface->h;
	}
	else
	{
		wt = w;
		ht = h;
	}

	if (nullptr != loadedSurface)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (nullptr != newTexture)
		{
			if (nonTransparent > alpha)
			{
				if (SDL_SetTextureAlphaMod(newTexture, alpha) != 0)
				{
					throw("[ERROR]___: alpha");
					/* TODO catch */
				}
			}
			centrage(xt, yt, wt, ht, cnt);
			tabTexture[msg]
				= new Texture
						(
							renderer, 
							newTexture,
							msg,
							stateScreen,
							select,
							xt,
							yt,
							wt,
							ht,
							alpha, 
							angle,
							cnt
						);
		}
		else
		{
			End::exitError("[ERROR]___: loadImage : cannot create Texture from : " + path);
		}
		SDL_FreeSurface(loadedSurface);
	}
	else
	{
		End::exitError("[ERROR]___: loadImage : path or image are corrupt : " + path);
	}
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : assertRangeAngle																	*/
/* ROLE : Limit the range on angle from 0.0 to 360.0										*/
/* IN/OUT : Uint16* angle : rotation angle													*/
/* RETURNED VALUE : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
void Texture::assertRangeAngle
(
	Uint16* angle
)
{
	*angle %= MAX_ANGLE;
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : centrage																			*/
/* ROLE : Permet de centrer la Texture selon enum Center_Type								*/
/* IN/OUT : int& xc : X position in pixels to center										*/
/* IN/OUT : int& yc : Y position in pixels to center										*/
/* IN : int iW : width of the Texture														*/
/* IN : int iH : height of the Texture														*/
/* IN : Uint8 cnt : enum class Center_Type ### default type : nocenter ###					*/
/* RETURNED VALUE : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
void Texture::centrage
(	
	int& xc,
	int& yc,
	int iW,
	int iH,
	Center_Type cnt
)
{
	switch (cnt)
	{
	case Center_Type::nocenter:
		/* N/A */
		break;
	case Center_Type::center_x:
		xc -= (iW / 2);
		break;
	case Center_Type::center_y:
		yc -= (iH / 2);
		break;
	case Center_Type::center:
		xc -= (iW / 2);
		yc -= (iH / 2);
		break;
	default:
		/* N/A */
		break;
	}
}


/* *********************************************************
 *				END Texture::STATIC						   *
 ********************************************************* */




/* *********************************************************
 *				START Texture::METHODS					   *
 ********************************************************* */

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : Texture																			*/
/* ROLE : Default constructor by value														*/
/* IN : SDL_Renderer*& renderer : Ptr on SDL_Renderer										*/
/* IN : SDL_Texture* image : ptr on picture create by SDL									*/
/* IN : std::string msg : Name of the Texture									  		    */
/* IN : Uint8 stateScreen : enum class State_Type											*/
/* IN : Uint8 select : enum class Select_Type												*/
/* IN : int x, int y : Positions before center of the Texture							    */
/* IN : unsigned int w : length of the Texture (compute length of Picture if w == 0)	    */
/* IN : unsigned int h : height of the Texture (compute height of Picture if h == 0)	    */
/* IN : Uint8 alpha : enum Transparance_Type										 	    */
/* IN : Uint16 angle : enum Rotation_Type												    */
/* IN : Uint8 cnt : enum class Center_Type											        */
/* RETURNED VALUE    : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
Texture::Texture
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
	Center_Type center
)
	: _renderer(renderer),
	_texture(image), _dst(rectangle(x, y, w, h)), _name(msg),
	_stateScreen(stateScreen), _select(select), _alpha(alpha), _angle(angle), _center(center)
{
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : ~Texture																			*/
/* ROLE : Default Destructor																*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
Texture::~Texture()
{
	if (_renderer != nullptr)
	{
		_renderer = nullptr;
	}	

	if (_texture != nullptr) 
	{
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : rectangle																			*/
/* ROLE : Create a SDL Rectangle with with x, y, w and h inputs dimensions					*/
/* IN : int x : upper left corner pixel														*/
/* IN : int y : bottom left corner pixel													*/
/* IN : int w : width of the Texture													    */
/* IN : int h : height of the Texture														*/
/* RETURNED VALUE : SDL_Rect : Rectangle with x, y, w and h dimensions						*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
SDL_Rect Texture::rectangle
(
	int x,
	int y,
	int w,
	int h
)
{
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
	return rectangle;
}


/* *********************************************************
 *				END Texture::METHODS					   *
 ********************************************************* */



/* *********************************************************
 *			START Texture::METHODS::Affichage			   *
 ********************************************************* */


/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : render																			*/
/* ROLE : By default render with Texture positions											*/
/* ROLE : If x or y are not equal to SCREEN_MIN_X_OUT_OF_RANGE or SCREEN_MIN_Y_OUT_OF_RANGE */
/* ROLE : then change Texture positions and render											*/
/* IN : int = SCREEN_MIN_X_OUT_OF_RANGE	: x position to render in pixel # default value #	*/
/* IN : int = SCREEN_MIN_Y_OUT_OF_RANGE	: y position to render in pixel # default value #	*/
/* RETURNED VALUE : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
void Texture::render
(
	int x,
	int y
)
{
	if (SCREEN_MIN_X_OUT_OF_RANGE < x)
	{
		_dst.x = x;
	}
	if (SCREEN_MIN_Y_OUT_OF_RANGE < y)
	{
		_dst.y = y;
	}

	SDL_RenderCopyEx(_renderer, _texture, NULL, &_dst, _angle, NULL, SDL_FLIP_NONE);
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : renderTextureTestStates															*/
/* ROLE : By default render with Texture positions if the input state and selection is		*/
/* ROLE : equal to the Texture																*/
/* IN : State_Type stateScreen : enum class State_Type										*/
/* IN : Select_Type select : enum class Select_Type											*/
/* IN : int = SCREEN_MIN_X_OUT_OF_RANGE	: x position to render in pixel # default value #	*/
/* IN : int = SCREEN_MIN_Y_OUT_OF_RANGE	: y position to render in pixel # default value #	*/
/* RETURNED VALUE : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
bool Texture::renderTextureTestStates
(
	State_Type stateScreen,
	Select_Type select,
	int x,
	int y
)
{
	if (_stateScreen == stateScreen && _select == select)
	{
		render(x, y);
		return true;
	}
	return false;
}

/* *********************************************************
 *			END Texture::METHODS::Affichage				   *
 ********************************************************* */









//--- Texte ----------------------------------------------------------------------------------------------------------------------------------------

/* *********************************************************
 *				START Texte::STATIC						   *
 ********************************************************* */


/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : initializeStaticVectorTextes														*/
/* ROLE : Clear and initialize the vector staticIndexVectorTextes					 		*/
/* IN : void																				*/
/* RETURNED VALUE : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
void Texte::initializeStaticVectorTextes()
{
	staticIndexVectorTextes.clear();
	staticIndexVectorTextes.resize((Uint8)Index_staticIndexVectorTextes::MAX_INDEX);
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : deleteStaticVectorTextes															*/
/* ROLE : Delete ptr in staticIndexVectorTextes then clear							 		*/
/* IN : void																				*/
/* RETURNED VALUE : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
void Texte::deleteStaticVectorTextes()
{
	for (Uint8 i(0); i < (Uint8)Index_staticIndexVectorTextes::MAX_INDEX; i++)
	{
		if (staticIndexVectorTextes[i] != nullptr)
		{
			LoadConfig::logfileconsole("[INFO]___: Delete Texte name = " + staticIndexVectorTextes[i]->GETname() + " Success");
			delete staticIndexVectorTextes[i];
			staticIndexVectorTextes[i] = nullptr;
		}
	}
	staticIndexVectorTextes.clear();
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : createSDL_TextureFromTexte														*/
/* ROLE : Create a pointer on an SDL_Texture compute by the inputs parameters				*/
/* ROLE : Use to create SDL_Texture for Texte								 				*/
/* IN: SDL_Renderer*& renderer : ptr on SDL_Renderer										*/
/* IN : Uint8 type : enum class Texte_Type												    */
/* IN : std::string message : Texte	to render												*/
/* IN : SDL_Color color : Texte color														*/
/* IN : SDL_Color colorback : background color											    */
/* IN : TTF_Font* font : Size of the font in use										    */
/* RETURNED VALUE : ptr on SDL_Texture														*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
SDL_Texture* Texte::createSDL_TextureFromTexte
(	
	SDL_Renderer*& renderer,
	Texte_Type type,
	std::string message,
	SDL_Color color,
	SDL_Color colorback,
	TTF_Font* font
)
{
	SDL_Surface *surf(nullptr);

	switch (type)
	{
	case Texte_Type::blended:
		surf = TTF_RenderText_Blended(font, message.c_str(), color);
		break;
	case Texte_Type::shaded:
		surf = TTF_RenderText_Shaded(font, message.c_str(), color, colorback);
		break;
	default:
		/* N/A */
		break;
	}

	SDL_Texture *texture(SDL_CreateTextureFromSurface(renderer, surf));
	if (texture == nullptr)
	{
		End::exitError("[ERROR]___:___________ERROR : renderTextShaded nullptr for : " + message);
	}

	SDL_FreeSurface(surf);

	return texture;
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : loadTexte																			*/
/* ROLE : Dynamic allocation of the Texte with specifications								*/
/* IN : SDL_Renderer*& renderer : Ptr on SDL_Renderer										*/
/* IN : TTF_Font* font[] : array of ptr on font in use										*/
/* IN : State_Type stateScreen : enum class State_Type										*/
/* IN : Select_Type select : enum class Select_Type											*/
/* OUT : std::unordered_map<std::string, Texte*>& : map where the Texte will be stored		*/
/* IN : Texte_Type type : enum class Texte_Type											    */
/* IN : std::string msg : Texte to render										  		    */
/* IN : SDL_Color color : Texte color												  	    */
/* IN : SDL_Color colorback : background color										  	    */
/* IN : Uint8 size : size to render the Texte (use in TTF_Font* font[])				  	    */
/* IN : int x, int y : Positions before center of the Texture							    */
/* IN : Uint8 alpha : enum Transparance_Type										 	    */
/* IN : Uint16 angle : enum Rotation_Type : will compute modulo if over 360				    */
/* IN : Uint8 cnt : enum class Center_Type	### default Center_Type::nocenter ###		    */
/* RETURNED VALUE : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
void Texte::loadTexte
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
	Center_Type cnt
)
{
	assertRangeAngle(&angle);

	SDL_Texture *image(createSDL_TextureFromTexte(renderer, type, msg, color, backcolor, font[size]));
	if (alpha != nonTransparent)
	{
		SDL_SetTextureAlphaMod(image, alpha);
	}	
	int xc(x), yc(y), iW(0), iH(0);
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);

	tabTexte[msg] = new Texte(renderer, font, image, msg, stateScreen, select, xc, yc, iW, iH,
		type, color, backcolor, size, alpha, angle, cnt);
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : loadTexteStaticVector																*/
/* ROLE : Dynamic allocation of the Texte with specifications in staticIndexVectorTextes	*/
/* IN : SDL_Renderer*& renderer : Ptr on SDL_Renderer										*/
/* IN : TTF_Font* font[] : array of ptr on font in use										*/
/* IN : Index_staticIndexVectorTextes : index enum class Index_staticIndexVectorTextes		*/
/* IN : Texte_Type type : enum class Texte_Type											    */
/* IN : std::string msg : Texte to render										  		    */
/* IN : SDL_Color color : Texte color												  	    */
/* IN : SDL_Color colorback : background color										  	    */
/* IN : Uint8 size : size to render the Texte (use in TTF_Font* font[])				  	    */
/* IN : int x, int y : Positions before center of the Texture							    */
/* IN : Uint8 alpha : enum Transparance_Type										 	    */
/* IN : Uint16 angle : enum Rotation_Type : will compute modulo if over 360				    */
/* IN : Uint8 cnt : enum class Center_Type	### default Center_Type::nocenter ###		    */
/* RETURNED VALUE : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
void Texte::loadTexteStaticVector
(
	SDL_Renderer*& renderer,
	TTF_Font* font[],
	Index_staticIndexVectorTextes index,
	Texte_Type type,
	std::string msg,
	SDL_Color color,
	SDL_Color backcolor,
	Uint8 size,
	int x,
	int y,
	Transparance_Type alpha,
	Uint16 angle,
	Center_Type cnt
)
{
	if (nullptr != staticIndexVectorTextes[(Uint8)index])
	{
		delete staticIndexVectorTextes[(Uint8)index];
		staticIndexVectorTextes[(Uint8)index] = nullptr;
	}

	assertRangeAngle(&angle);
	SDL_Texture* image(createSDL_TextureFromTexte(renderer, type, msg, color, backcolor, font[size]));
	if (alpha != nonTransparent)
	{
		SDL_SetTextureAlphaMod(image, alpha);
	}

	int xc(x), yc(y), iW(0), iH(0);
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);

	staticIndexVectorTextes[(Uint8)index] = new Texte
	(renderer, font, image, msg, State_Type::STATEnothing, Select_Type::selectnothing, xc, yc, iW, iH,
		type, color, backcolor, size, alpha, angle, cnt);
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : writeTexte																		*/
/* ROLE : Fast load and render Texte														*/
/* ROLE : ### Only works with enum class Index_staticIndexVectorTextes ###					*/
/* IN : SDL_Renderer*& renderer : Ptr on SDL_Renderer										*/
/* IN : TTF_Font* font[] : array of ptr on font in use										*/
/* IN : Index_staticIndexVectorTextes : index enum class Index_staticIndexVectorTextes		*/
/* IN : Texte_Type type : enum class Texte_Type											    */
/* IN : std::string msg : Texte to render										  		    */
/* IN : SDL_Color color : Texte color												  	    */
/* IN : SDL_Color colorback : background color										  	    */
/* IN : Uint8 size : size to render the Texte (use in TTF_Font* font[])				  	    */
/* IN : int x, int y : Positions before center of the Texture							    */
/* IN : Uint8 alpha : enum Transparance_Type										 	    */
/* IN : Uint16 angle : enum Rotation_Type : will compute modulo if over 360				    */
/* IN : Uint8 cnt : enum class Center_Type	### default Center_Type::nocenter ###		    */
/* RETURNED VALUE : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
void Texte::writeTexte
(	
	SDL_Renderer*& renderer,
	TTF_Font* font[],
	Index_staticIndexVectorTextes index,
	Texte_Type type,
	std::string msg,
	SDL_Color color,
	SDL_Color backcolor,
	Uint8 size,
	unsigned int x,
	unsigned int y,
	Transparance_Type alpha,
	Uint16 angle,
	Center_Type cnt
)
{
	if  (
			nullptr == staticIndexVectorTextes[(Uint8)index]
			||
			staticIndexVectorTextes[(Uint8)index]->GETname().compare(msg) != IDENTICAL_STRINGS
		)
	{
		loadTexteStaticVector
		(renderer, font, index,
			type, msg, color, backcolor, size, x, y, alpha, angle, cnt);
	}
	staticIndexVectorTextes[(Uint8)index]->render();
}


/* *********************************************************
 *					END Texte::STATIC					   *
 ********************************************************* */



/* *********************************************************
 *				START Texte::METHODS					   *
 ********************************************************* */


/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : Texte																				*/
/* ROLE : Constructor by Value																*/
/* IN : SDL_Renderer*& renderer : Ptr on SDL_Renderer										*/
/* IN : TTF_Font* font[] : array of ptr on font in use										*/
/* IN : SDL_Texture* : ptr on Texture of the Texte											*/
/* IN : std::string msg : Texte to render										  		    */
/* IN : State_Type stateScreen : enum class State_Type										*/
/* IN : Select_Type select : enum class Select_Type											*/
/* IN : int x, int y : Positions before center of the Texture							    */
/* IN : unsigned int w : length of the Texture 											    */
/* IN : unsigned int h : height of the Texture											    */
/* IN : Texte_Type type : enum class Texte_Type											    */
/* IN : SDL_Color color : Texte color												  	    */
/* IN : SDL_Color colorback : background color										  	    */
/* IN : Uint8 size : size to render the Texte (use in TTF_Font* font[])				  	    */
/* IN : Uint8 alpha : enum Transparance_Type										 	    */
/* IN : Uint16 angle : enum Rotation_Type : will compute modulo if over 360				    */
/* IN : Uint8 cnt : enum class Center_Type	### default Center_Type::nocenter ###		    */
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
Texte::Texte
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
	Center_Type center
):
	Texture(renderer, image, msg, stateScreen, select, x, y, w, h, alpha, angle, center),
	_type(type), _txtcolor(txtcolor), _backcolor(backcolor),
	_size(size), _font()
{
	for (unsigned int i(0); i < MAX_FONT; i++)
	{
		_font[i] = font[i];
	}	
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : ~Texte																			*/
/* ROLE : Default Destructor																*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
Texte::~Texte()
{
	for (unsigned int i(0); i < MAX_FONT; i++)
	{
		/* Ptr delete in End::deleteAll */
		_font[i] = nullptr;
	}	
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : isSameColor																		*/
/* ROLE : Compare 2 SDL_Color by the 4 parameters											*/
/* IN : SDL_Color color1																	*/
/* IN : SDL_Color color2																	*/
/* RETURNED VALUE : bool : false -> The colors are differents								*/
/* RETURNED VALUE : bool : true -> The colors are the same									*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
bool Texte::isSameColor
(
	SDL_Color color1,
	SDL_Color color2
)const
{
	if (color1.a != color2.a || color1.b != color2.b || color1.g != color2.g || color1.r != color2.r)
	{
		return false;
	}
	else
	{
		return true;
	}	
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : resizeTexte																		*/
/* ROLE : Resize the Texte																	*/
/* IN : void																				*/
/* RETURNED VALUE : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
void Texte::resizeTexte()
{
	int xc(0), yc(0), iW(0), iH(0);

	switch (this->GETcenter())
	{
	case Center_Type::nocenter:
		xc = this->GETdstx();
		yc = this->GETdsty();
		break;
	case Center_Type::center_x:
		xc = this->GETdstx() + this->GETdstw() / 2;
		yc = this->GETdsty();
		break;
	case Center_Type::center_y:
		xc = this->GETdstx();
		yc = this->GETdsty() + this->GETdsth() / 2;
		break;
	case Center_Type::center:
		xc = this->GETdstx() + this->GETdstw() / 2;
		yc = this->GETdsty() + this->GETdsth() / 2;
		break;
	default:
		/* N/A */
		break;
	}

	SDL_QueryTexture(this->GETtextureNonConst(), NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, this->GETcenter());
	this->SETdstx(xc); this->SETdsty(yc); this->SETdstw(iW); this->SETdsth(iH);
}

/* *********************************************************
 *				END Texte::METHODS						   *
 ********************************************************* */




/* *********************************************************
 *			START Texte::METHODES::GET/SET				   *
 ********************************************************* */

void Texte::SETname
(
	std::string msg
)
{
	if (this->GETname().compare(msg) != 0)
	{
		this->Texture::SETname(msg);
		this->SETtexture(createSDL_TextureFromTexte(this->GETrenderer(), _type, this->GETname(), _txtcolor, _backcolor, _font[_size]));
		resizeTexte();
	}
	else
	{
		/* N/A */
	}
}
void Texte::SETtype
(
	Texte_Type type
)
{
	if (type != _type)
	{
		_type = type;
		this->SETtexture(createSDL_TextureFromTexte(this->GETrenderer(), _type, this->GETname(), _txtcolor, _backcolor, _font[_size]));
	}
	else
	{
		/* N/A */
	}
}
void Texte::SETsize
(
	Uint8 size
)
{
	if (size != _size)
	{
		_size = size;
		this->SETtexture(createSDL_TextureFromTexte(this->GETrenderer(), _type, this->GETname(), _txtcolor, _backcolor, _font[_size]));
		resizeTexte();
	}
	else
	{
		/* N/A */
	}
}
void Texte::SETtxtcolor
(
	SDL_Color txtcolor
)
{
	if (!isSameColor(txtcolor, _txtcolor))
	{
		_txtcolor = txtcolor;
		this->SETtexture(createSDL_TextureFromTexte(this->GETrenderer(), _type, this->GETname(), _txtcolor, _backcolor, _font[_size]));
	}
	else
	{
		/* N/A */
	}
}
void Texte::SETbackcolor
(
	SDL_Color backcolor
)
{
	if (!isSameColor(backcolor, _backcolor))
	{
		_backcolor = backcolor;
		this->SETtexture(createSDL_TextureFromTexte(this->GETrenderer(), _type, this->GETname(), _txtcolor, _backcolor, _font[_size]));
	}
	else
	{
		/* N/A */
	}
}


/* *********************************************************
 *				END Texte::METHODES::GET/SET			   *
 ********************************************************* */





 //--- ButtonImage ---------------------------------------------------------------------------------------------------------------------------------------

/* *********************************************************
 *				START ButtonImage::STATIC				   *
 ********************************************************* */


/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : createButtonImage																	*/
/* ROLE : Dynamic allocation of the ButtonImage with specifications							*/
/* IN : SDL_Renderer*& renderer : Ptr on SDL_Renderer										*/
/* OUT : std::unordered_map<std::string, ButtonImage*>& : unmap selected					*/
/* IN : State_Type stateScreen : enum class State_Type										*/
/* IN : Select_Type select : enum class Select_Type											*/
/* IN : Texte_Type type : enum class Texte_Type											    */
/* IN : std::string path : Path to the Image									  		    */
/* IN : std::string msg : Texte to render										  		    */
/* IN : Uint8 alpha : enum Transparance_Type										 	    */
/* IN : Uint8 size : size to render the Texte (use in TTF_Font* font[])				  	    */
/* IN : int x, int y : Positions before center of the Texture							    */
/* IN : Uint16 angle : enum Rotation_Type : will compute modulo if over 360				    */
/* IN : Uint8 cnt : enum class Center_Type	### default Center_Type::nocenter ###		    */
/* RETURNED VALUE : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
void ButtonImage::createButtonImage
(	
	SDL_Renderer*& renderer,
	std::unordered_map<std::string, ButtonImage*>& tabButtonImage,
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
	Center_Type cnt
)
{

	int xt(0), yt(0), wt(0), ht(0);
	if (SCREEN_MIN_X_OUT_OF_RANGE < x)
	{
		xt = x;
	}
	if (SCREEN_MIN_Y_OUT_OF_RANGE < y)
	{
		yt = y;
	}

	assertRangeAngle(&angle);

	SDL_Surface* loadedSurface(IMG_Load(path.c_str()));
	std::size_t found(path.find('.'));
	if (found != std::string::npos)
		path.insert(found, "On");
	SDL_Surface* loadedSurfaceOn(IMG_Load(path.c_str()));
	if (w == 0 && h == 0)
	{
		wt = loadedSurface->w;
		ht = loadedSurface->h;
	}
	else
	{
		wt = w;
		ht = h;
	}

	if (loadedSurface != nullptr && loadedSurfaceOn != nullptr)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		SDL_SetColorKey(loadedSurfaceOn, SDL_TRUE, SDL_MapRGB(loadedSurfaceOn->format, 0, 0xFF, 0xFF));
		SDL_Texture *image(SDL_CreateTextureFromSurface(renderer, loadedSurface));
		SDL_Texture *imageOn(SDL_CreateTextureFromSurface(renderer, loadedSurfaceOn));
		if (image != nullptr && imageOn != nullptr)
		{
			if (alpha != nonTransparent)
			{
				SDL_SetTextureAlphaMod(image, alpha);
				SDL_SetTextureAlphaMod(imageOn, alpha);
			}
			else
			{
				/* N/A */
			}

			centrage(xt, yt, wt, ht, cnt);
			tabButtonImage[msg] = new ButtonImage(renderer, image, msg, stateScreen, select, xt, yt, wt, ht, alpha, angle, imageOn, cnt);
		}
		else
			LoadConfig::logfileconsole("[ERROR]___:___________ERROR : createButtonImage : cannot create Texture from : " + path);
		SDL_FreeSurface(loadedSurface);
		SDL_FreeSurface(loadedSurfaceOn);
	}
	else
		LoadConfig::logfileconsole("[ERROR]___:___________ERROR : createButtonImage : path or image are corrupt : " + path);


	LoadConfig::logfileconsole("Create ButtonImage n:" + std::to_string(tabButtonImage.size() - 1) + " msg = " + msg + " Success");
}

/* *********************************************************
 *				END ButtonImage::STATIC					   *
 ********************************************************* */



/* *********************************************************
 *				START ButtonImage::METHODES				   *
 ********************************************************* */


/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : ButtonImage																		*/
/* ROLE : Constructor by Value																*/
/* IN : SDL_Renderer*& renderer : Ptr on SDL_Renderer										*/
/* IN : SDL_Texture* : ptr on Texture of the image											*/
/* IN : std::string msg : Texte to render										  		    */
/* IN : State_Type stateScreen : enum class State_Type										*/
/* IN : Select_Type select : enum class Select_Type											*/
/* IN : int x, int y : Positions before center of the Texture							    */
/* IN : unsigned int w : length of the Texture 											    */
/* IN : unsigned int h : height of the Texture											    */
/* IN : Transparance_Type alpha : enum Transparance_Type							 	    */
/* IN : Uint16 angle : enum Rotation_Type : will compute modulo if over 360				    */
/* IN : SDL_Texture* : ptr on Texture of the imageOn										*/
/* IN : Center_Type cnt : enum class Center_Type	### default Center_Type::nocenter ###   */
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
ButtonImage::ButtonImage
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
	Center_Type center
)
	: Texture(renderer, image, msg, stateScreen, select, x, y, w, h, alpha, angle, center),
	_imageOn(imageOn), _on(false)
{
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : ~ButtonImage																		*/
/* ROLE : Default Destructor																*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
ButtonImage::~ButtonImage()
{
	if (_imageOn != nullptr)
	{
		SDL_DestroyTexture(_imageOn);
		_imageOn = nullptr;
	}
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : searchButtonImage																	*/
/* ROLE : Search the position of ButtonImage / depends of State_Type						*/
/* IN : State_Type stateScreen : State_Type to compare with the ButtonImage				    */
/* IN : int x, int y : Positions before center of the Texture							    */
/* RETURNED VALUE : bool : false -> x or/and y are not in the range	of the ButtonImage		*/
/* RETURNED VALUE : bool : true -> x and y are in the range of the ButtonImage				*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
bool ButtonImage::searchButtonImage
(
	State_Type stateScreen,
	signed int x,
	signed int y
)
{
	if (stateScreen == this->GETstateScreen())
	{
		if (x >= this->GETdstx() && x <= this->GETdstx() + this->GETdstw())
		{
			if (y >= this->GETdsty() && y <= this->GETdsty() + this->GETdsth())
			{
				return true;
			}
		}
	}
	return false;
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : renderButtonImage																	*/
/* ROLE : Render the ButtonImage if the State_Type is identical								*/
/* IN : State_Type stateScreen : State_Type to compare with the ButtonImage				    */
/* RETURNED VALUE : bool : false -> ButtonImage	is not render								*/
/* RETURNED VALUE : bool : true -> ButtonImage is render									*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
bool ButtonImage::renderButtonImage
(
	State_Type stateScreen
)
{
	if (this->GETstateScreen() == stateScreen)
	{
		if (_on)
			SDL_RenderCopyEx(this->GETrenderer(), _imageOn, NULL, this->GETdstPtr(), this->GETangle(), NULL, SDL_FLIP_NONE);
		else
			SDL_RenderCopyEx(this->GETrenderer(), this->GETtexture(), NULL, this->GETdstPtr(), this->GETangle(), NULL, SDL_FLIP_NONE);
		return true;
	}
	return false;
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* NAME : changeOn																			*/
/* ROLE : Change bool state of _on															*/
/* IN : void																			    */
/* RETURNED VALUE : void																	*/
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
void ButtonImage::changeOn()
{
	_on = !_on;
}


/* *********************************************************
 *				END ButtonImage::METHODES				   *
 ********************************************************* */





 //--- ButtonTexte ---------------------------------------------------------------------------------------------------------------------------------------

/* *********************************************************
 *				START ButtonTexte::STATIC				   *
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
 * INPUT  PARAMETERS : Uint16 angle : enum Uint16
 * INPUT  PARAMETERS : Uint8 cnt : le type de centrage -> enum Center_Type
 * OUTPUT PARAMETERS : création et ajout d'un objet ButtonTexte
 * RETURNED VALUE    : void
 */
void ButtonTexte::createButtonTexte
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
	Center_Type centerButtonTexte
)
{
	int iW(0), iH(0);

	assertRangeAngle(&angle);

	SDL_Texture *image(createSDL_TextureFromTexte(renderer, type, msg, color, backcolor, font[size]));
	SDL_Texture *imageOn(createSDL_TextureFromTexte(renderer, type, msg, color, { 64,128,64,255 }, font[size]));

	if (alpha != nonTransparent)
	{
		SDL_SetTextureAlphaMod(image, alpha);
		SDL_SetTextureAlphaMod(imageOn, alpha);
	}
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(x, y, iW, iH, centerButtonTexte);
	tabButtonTexte[msg] = new ButtonTexte(renderer, font, image, msg, stateScreen, select, x, y, iW, iH,
		type, color, backcolor, size, alpha, angle, imageOn, centerButtonTexte);

	LoadConfig::logfileconsole("[INFO]___: Create ButtonTexte n:" + std::to_string(tabButtonTexte.size() - 1) + " msg = " + msg + " Success");
}

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
 * INPUT  PARAMETERS : Uint16 angle : enum Uint16
 * INPUT  PARAMETERS : Uint8 cnt : le type de centrage -> enum Center_Type
 * OUTPUT PARAMETERS : création et ajout d'un objet ButtonTexte
 * RETURNED VALUE    : void
 */
void ButtonTexte::createButtonTexte
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
)
{
	int iW(0), iH(0);

	assertRangeAngle(&angle);

	SDL_Texture* image(createSDL_TextureFromTexte(renderer, type, msg, color, backcolor, font[size]));
	SDL_Texture* imageOn(createSDL_TextureFromTexte(renderer, type, msg, color, { 64,128,64,255 }, font[size]));

	if (alpha != nonTransparent)
	{
		SDL_SetTextureAlphaMod(image, alpha);
		SDL_SetTextureAlphaMod(imageOn, alpha);
	}
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(x, y, iW, iH, centerButtonTexte);
	tabButtonTexte.push_back
		(
			new ButtonTexte
				(renderer, font, image, msg, stateScreen, select, x, y, iW, iH,
				type, color, backcolor, size, alpha, angle, imageOn, centerButtonTexte)
		);

	LoadConfig::logfileconsole("[INFO]___: Create ButtonTexte n:" + std::to_string(tabButtonTexte.size() - 1) + " msg = " + msg + " Success");
}

/* *********************************************************
 *				END ButtonTexte::STATIC					   *
 ********************************************************* */



/* *********************************************************
 *				START ButtonTexte::METHODS				   *
 ********************************************************* */


ButtonTexte::ButtonTexte
(	
	SDL_Renderer* renderer,
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
	SDL_Texture* imageOn,
	Center_Type center
)
	: Texte(renderer, font, image, msg, stateScreen, select, x, y, w, h, type, txtcolor, backcolor, size, alpha, angle, center),
	_imageOn(imageOn), _on(false)
{
}
ButtonTexte::~ButtonTexte()
{
	if (_imageOn != nullptr)
	{
		SDL_DestroyTexture(_imageOn);
		_imageOn = nullptr;
	}
}


/*
 * NAME : searchButtonTexte
 * ROLE : Recherche le bouton aux coordonnées en entrée
 * INPUT  PARAMETERS : Uint8 stateScreen :  enum State_Type
 * INPUT  PARAMETERS : signed int x, signed int y : coordonnées en entrée
 * OUTPUT PARAMETERS : Validation ou non
 * RETURNED VALUE    : bool : false = non valide / true = valide
 */
bool ButtonTexte::searchButtonTexte
(
	State_Type stateScreen,
	signed int x,
	signed int y
)
{
	if (stateScreen == this->GETstateScreen())
	{
		if (x >= this->GETdstx() && x <= this->GETdstx() + this->GETdstw())
		{
			if (y >= this->GETdsty() && y <= this->GETdsty() + this->GETdsth())
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}


/*
 * NAME : resetOnstateScreen
 * ROLE : Reset l'état _on des boutons
 * INPUT  PARAMETERS : Uint8 select, unsigned int selectnothing : enum State_Type
 * OUTPUT PARAMETERS : Reset l'état _on des boutons
 * RETURNED VALUE    : void
 */
void ButtonTexte::resetOnstateScreen
(
	Select_Type select
)
{
	if (this->GETselect() != select && this->GETselect() != Select_Type::selectnothing)
	{
		_on = false;
	}
}


/*
 * NAME : resetOnPlayer
 * ROLE : Reset l'état _on des boutons
 * INPUT  PARAMETERS : unsigned int : joueur sélectionné
 * INPUT  PARAMETERS : std::vector<std::string> : tableau de nom des joueurs
 * OUTPUT PARAMETERS : Initialisation de map.screen et map.maps
 * RETURNED VALUE    : void
 */
void ButtonTexte::resetOnPlayer
(
	unsigned int selectplayer,
	std::vector<std::string> tabPlayerName
)
{
	for (unsigned int i(0); i < tabPlayerName.size(); i++)
	{
		if (i != selectplayer && this->GETname().compare(tabPlayerName[i]) == 0)
		{
			_on = false;
		}
	}
}


/*
 * NAME : renderButtonTexte
 * ROLE : Affichage du ButtonTexte en fonction du contexte
 * INPUT  PARAMETERS : Uint8 stateScreen :  enum State_Type
 * INPUT  PARAMETERS : int x = -1, int y = -1 : positions optionnelles
 * INPUT  PARAMETERS : Uint8 center = nocenter : enum Center_Type
 * OUTPUT PARAMETERS : Initialisation de map.screen et map.maps
 * RETURNED VALUE    : bool : false = non afficher / true = affichage
 */
bool ButtonTexte::renderButtonTexte
(
	State_Type stateScreen,
	int x,
	int y,
	Center_Type center
)
{
	if (this->GETstateScreen() == stateScreen)
	{
		if (SCREEN_MIN_X_OUT_OF_RANGE < x && SCREEN_MIN_Y_OUT_OF_RANGE < y)
		{
			centrage(x, y, this->GETdstw(), this->GETdsth(), center);
			this->SETdstx(x);
			this->SETdsty(y);
		}
		if (_on)
		{
			SDL_RenderCopy(this->GETrenderer(), _imageOn, NULL, this->GETdstPtr());
		}
		else
		{
			SDL_RenderCopy(this->GETrenderer(), this->GETtexture(), NULL, this->GETdstPtr());
		}	
		return true;
	}
	return false;
}


/*
 * NAME : changeOn
 * ROLE : alterne l'attribut booléen _on
 * INPUT  PARAMETERS : void
 * OUTPUT PARAMETERS : alterne l'attribut booléen _on
 * RETURNED VALUE    : void
 */
void ButtonTexte::changeOn()
{
	_on = !_on;
}

/* *********************************************************
 *				END ButtonTexte::METHODS				   *
 ********************************************************* */



/*
*	End Of File : Texture.cpp
*/