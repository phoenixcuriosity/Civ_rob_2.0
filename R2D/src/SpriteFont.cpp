#include "SpriteFont.h"

#include "SpriteBatch.h"
#include "ValueToScale.h"

#include <SDL/SDL.h>
#include <iostream>
#include "Window.h"


int closestPow2(int i)
{
    i--;
    int pi = 1;
    while (i > 0)
    {
        i >>= 1;
        pi <<= 1;
    }
    return pi;
}

#define MAX_TEXTURE_RES 4096

namespace R2D
{

SpriteFont::SpriteFont(const char* font, int size, char cs, char ce)
{
    init(font, size, cs, ce);
}

void SpriteFont::init(const char* font, int size)
{
    init(font, size, FIRST_PRINTABLE_CHAR, LAST_PRINTABLE_CHAR);
}

void SpriteFont::init(const char* font, int size, char cs, char ce)
{
    // Initialize SDL_ttf
    if (!TTF_WasInit())
    {
        TTF_Init();
    }
    TTF_Font* f = TTF_OpenFont(font, size);
    if (f == nullptr)
    {
        fprintf(stderr, "Failed to open TTF font %s\n", font);
        fflush(stderr);
        throw 281;
    }
    _fontHeight = TTF_FontHeight(f);
    _regStart = cs;
    _regLength = ce - cs + 1;
    int padding = size / 8;

    //std::cout << _regStart << " " << _regLength << std::endl;
    // First neasure all the regions
    glm::ivec4* glyphRects = new glm::ivec4[_regLength];
    int i = 0, advance;
    for (char c = cs; c <= ce; c++)
    {
        TTF_GlyphMetrics(f, c, &glyphRects[i].x, &glyphRects[i].z, &glyphRects[i].y, &glyphRects[i].w, &advance);
        glyphRects[i].z -= glyphRects[i].x;
        glyphRects[i].x = 0;
        glyphRects[i].w -= glyphRects[i].y;
        glyphRects[i].y = 0;
        i++;
    }

    // Find best partitioning of glyphs
    int rows = 1, w, h, bestWidth = 0, bestHeight = 0, area = MAX_TEXTURE_RES * MAX_TEXTURE_RES, bestRows = 0;
    std::vector<int>* bestPartition = nullptr;
    while (rows <= _regLength)
    {
        h = rows * (padding + _fontHeight) + padding;
        auto gr = createRows(glyphRects, _regLength, rows, padding, w);

        // Desire a power of 2 texture
        w = closestPow2(w);
        h = closestPow2(h);

        // A texture must be feasible
        if (w > MAX_TEXTURE_RES || h > MAX_TEXTURE_RES)
        {
            rows++;
            delete[] gr;
            continue;
        }

        // Check for minimal area
        if (area >= w * h) 
        {
            if (bestPartition) delete[] bestPartition;
            bestPartition = gr;
            bestWidth = w;
            bestHeight = h;
            bestRows = rows;
            area = bestWidth * bestHeight;
            rows++;
        }
        else 
        {
            delete[] gr;
            break;
        }
    }

    // Can a bitmap font be made?
    if (!bestPartition)
    {
        fprintf(stderr, "Failed to Map TTF font %s to texture. Try lowering resolution.\n", font);
        fflush(stderr);
        throw 282;
    }
    // Create the texture
    glGenTextures(1, &_texID);
    glBindTexture(GL_TEXTURE_2D, _texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bestWidth, bestHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // Now draw all the glyphs
    SDL_Color fg = { 255, 255, 255, 255 };
    int ly = padding;
    for (int ri = 0; ri < bestRows; ri++) 
    {
        int lx = padding;
        for (size_t ci = 0; ci < bestPartition[ri].size(); ci++) 
        {
            int gi = bestPartition[ri][ci];

            SDL_Surface* glyphSurface = TTF_RenderGlyph_Blended(f, (char)(cs + gi), fg);

            // Pre-multiplication occurs here
            unsigned char* sp = (unsigned char*)glyphSurface->pixels;
            int cp = glyphSurface->w * glyphSurface->h * 4;
            for (int indexI = 0; indexI < cp; indexI += 4)
            {
                float a = sp[indexI + 3] / 255.0f;
                sp[indexI] = (unsigned char)((float)sp[indexI] * a);
                sp[indexI + 1] = sp[indexI];
                sp[indexI + 2] = sp[indexI];
            }

            // Save glyph image and update coordinates
            glTexSubImage2D(GL_TEXTURE_2D, 0, lx, bestHeight - ly - 1 - glyphSurface->h, glyphSurface->w, glyphSurface->h, GL_BGRA, GL_UNSIGNED_BYTE, glyphSurface->pixels);
            glyphRects[gi].x = lx;
            glyphRects[gi].y = ly;
            glyphRects[gi].z = glyphSurface->w;
            glyphRects[gi].w = glyphSurface->h;

            SDL_FreeSurface(glyphSurface);
            glyphSurface = nullptr;

            lx += glyphRects[gi].z + padding;
        }
        ly += _fontHeight + padding;
    }

    // Draw the unsupported glyph
    int rs = padding - 1;
    int* pureWhiteSquare = new int[rs * rs];
    memset(pureWhiteSquare, 0xffffffff, rs * rs * sizeof(int));
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, rs, rs, GL_RGBA, GL_UNSIGNED_BYTE, pureWhiteSquare);
    delete[] pureWhiteSquare;
    pureWhiteSquare = nullptr;

    // Set some texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Create spriteBatch glyphs
    m_glyphs = new CharGlyph[_regLength + 1];
    for (i = 0; i < _regLength; i++) 
    {
        m_glyphs[i].character = (char)(cs + i);
        m_glyphs[i].size = glm::vec2(glyphRects[i].z, glyphRects[i].w);
        m_glyphs[i].uvRect = glm::vec4(
            (float)glyphRects[i].x / (float)bestWidth,
            (float)glyphRects[i].y / (float)bestHeight,
            (float)glyphRects[i].z / (float)bestWidth,
            (float)glyphRects[i].w / (float)bestHeight
        );
    }
    m_glyphs[_regLength].character = ' ';
    m_glyphs[_regLength].size = m_glyphs[0].size;
    m_glyphs[_regLength].uvRect = glm::vec4(0, 0, (float)rs / (float)bestWidth, (float)rs / (float)bestHeight);

    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] glyphRects;
    delete[] bestPartition;
    TTF_CloseFont(f);
}

void SpriteFont::dispose() 
{
    if (_texID != 0)
    {
        glDeleteTextures(1, &_texID);
        _texID = 0;
    }
    if (m_glyphs) 
    {
        delete[] m_glyphs;
        m_glyphs = nullptr;
    }
}

std::vector<int>* SpriteFont::createRows
(
    glm::ivec4* rects,
    int rectsLength,
    int r,
    int padding, int& w
)
{
    // Blank initialize
    std::vector<int>* l = new std::vector<int>[r]();
    int* cw = new int[r]();
    for (int i = 0; i < r; i++)
    {
        cw[i] = padding;
    }

    // Loop through all glyphs
    for (int i = 0; i < rectsLength; i++) 
    {
        // Find row for placement
        int ri = 0;
        for (int rii = 1; rii < r; rii++)
            if (cw[rii] < cw[ri]) ri = rii;

        // Add width to that row
        cw[ri] += rects[i].z + padding;

        // Add glyph to the row list
        l[ri].push_back(i);
    }

    // Find the max width
    w = 0;
    for (int i = 0; i < r; i++) 
    {
        if (cw[i] > w) w = cw[i];
    }

    return l;
}

glm::vec2 SpriteFont::measure(const char* s)
{
    glm::vec2 size(0, _fontHeight);
    float cw = 0;
    for (int si = 0; s[si] != 0; si++)
    {
        char c = s[si];
        if (s[si] == '\n') 
        {
            size.y += _fontHeight;
            if (size.x < cw)
                size.x = cw;
            cw = 0;
        }
        else 
        {
            // Check for correct glyph
            int gi = c - _regStart;
            if (gi < 0 || gi >= _regLength)
                gi = _regLength;
            cw += m_glyphs[gi].size.x;
        }
    }
    if (size.x < cw)
        size.x = cw;
    return size;
}

void SpriteFont::draw
(
    SpriteBatch& batch,
    const char* s,
    glm::vec2 position,
    glm::vec2 scaling,
    float depth, 
    ColorRGBA8 tint,
    Justification just /* = Justification::LEFT */
)
{
    glm::vec2 tp = position;
    // Apply justification
    if (just == Justification::MIDDLE) 
    {
        tp.x -= measure(s).x * scaling.x / 2;
    }
    else if (just == Justification::RIGHT)
    {
        tp.x -= measure(s).x * scaling.x;
    }
    for (int si = 0; s[si] != 0; si++) 
    {
        char c = s[si];
        if (s[si] == '\n') 
        {
            tp.y += _fontHeight * scaling.y;
            tp.x = position.x;
        }
        else
        {
            // Check for correct glyph
            int gi = c - _regStart;
            if (gi < 0 || gi >= _regLength) gi = _regLength;
            glm::vec4 destRect(tp, m_glyphs[gi].size * scaling);
            //if (c == '\u00E4') std::cout << m_glyphs[gi].uvRect.x << " " << m_glyphs[gi].uvRect.y << " " << m_glyphs[gi].uvRect.z << " " << m_glyphs[gi].uvRect.w << std::endl;
            batch.draw(destRect, m_glyphs[gi].uvRect, _texID, depth, tint);
            tp.x += m_glyphs[gi].size.x * scaling.x;
        }
    }
}


float SpriteFont::getScaleFontToScreen
(
    /* IN */
    const float size
)
{
    return
    (
        size *
        float
        (
            ValueToScale::protectedDiv
            (
                double(Window::getVertical()),
                double(FONT::GUI::RESOLUTION::VERTICAL)
            )
        )
    );
}

}