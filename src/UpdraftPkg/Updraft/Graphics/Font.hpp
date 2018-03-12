#pragma once

extern "C" {
#include <Uefi.h>
}

#include "../Utils/Types.hpp"
#include "../Utils/Array.hpp"
#include "Point.hpp"
#include "Color.hpp"
#include "ColorPalette.hpp"

class Font
{
  Array<uint8> m_data;

  uint8 m_height;

  uint8 getGlyphWidth(const char ch) const;

  const uint8 *getGlyphDataPtr(const char ch) const;

  void drawGlyph(const char ch, const Point pos, const Color color) const;

public:
  Font(const wchar_t *fileName);

  void draw(const CHAR8 *str, const Point pos, const Color color = Palette::Black) const;
};
