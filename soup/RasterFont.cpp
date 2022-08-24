#include "RasterFont.hpp"

#include "base.hpp"

#include "Canvas.hpp"
#include "unicode.hpp"

namespace soup
{
	using Glyph = RasterFont::Glyph;

	Canvas Glyph::getCanvas() const
	{
		return Canvas(width, height, pixels);
	}

	[[nodiscard]] static RasterFont generateSimple5()
	{
		RasterFont f{};
		f.baseline_glyph_height = 5;
		f.glyphs.emplace('A', Glyph(3, 5, {
			0,1,0,
			1,0,1,
			1,1,1,
			1,0,1,
			1,0,1,
		}));
		f.glyphs.emplace('B', Glyph(3, 5, {
			1,1,0,
			1,0,1,
			1,1,0,
			1,0,1,
			1,1,0,
		}));
		f.glyphs.emplace('C', Glyph(3, 5, {
			1,1,1,
			1,0,0,
			1,0,0,
			1,0,0,
			1,1,1,
		}));
		f.glyphs.emplace('D', Glyph(3, 5, {
			1,1,0,
			1,0,1,
			1,0,1,
			1,0,1,
			1,1,0,
		}));
		f.glyphs.emplace('E', Glyph(3, 5, {
			1,1,1,
			1,0,0,
			1,1,1,
			1,0,0,
			1,1,1,
		}));
		f.glyphs.emplace('F', Glyph(3, 5, {
			1,1,1,
			1,0,0,
			1,1,1,
			1,0,0,
			1,0,0,
		}));
		f.glyphs.emplace('G', Glyph(3, 5, {
			1,1,1,
			1,0,0,
			1,0,1,
			1,0,1,
			1,1,1,
		}));
		f.glyphs.emplace('H', Glyph(3, 5, {
			1,0,1,
			1,0,1,
			1,1,1,
			1,0,1,
			1,0,1,
		}));
		f.glyphs.emplace('I', Glyph(3, 5, {
			1,1,1,
			0,1,0,
			0,1,0,
			0,1,0,
			1,1,1,
		}));
		f.glyphs.emplace('J', Glyph(3, 5, {
			1,1,1,
			0,0,1,
			0,0,1,
			1,0,1,
			1,1,1,
		}));
		f.glyphs.emplace('K', Glyph(3, 5, {
			1,0,1,
			1,0,1,
			1,1,0,
			1,0,1,
			1,0,1,
		}));
		f.glyphs.emplace('L', Glyph(3, 5, {
			1,0,0,
			1,0,0,
			1,0,0,
			1,0,0,
			1,1,1,
		}));
		f.glyphs.emplace('M', Glyph(5, 5, {
			1,0,0,0,1,
			1,1,0,1,1,
			1,0,1,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
		}));
		f.glyphs.emplace('N', Glyph(5, 5, {
			1,0,0,0,1,
			1,1,0,0,1,
			1,0,1,0,1,
			1,0,0,1,1,
			1,0,0,0,1,
		}));
		f.glyphs.emplace('O', Glyph(3, 5, {
			1,1,1,
			1,0,1,
			1,0,1,
			1,0,1,
			1,1,1,
		}));
		f.glyphs.emplace('P', Glyph(3, 5, {
			1,1,1,
			1,0,1,
			1,1,1,
			1,0,0,
			1,0,0,
		}));
		f.glyphs.emplace('Q', Glyph(4, 5, {
			1,1,1,1,
			1,0,0,1,
			1,0,0,1,
			1,1,1,0,
			0,0,1,1,
		}));
		f.glyphs.emplace('R', Glyph(3, 5, {
			1,1,1,
			1,0,1,
			1,1,0,
			1,0,1,
			1,0,1,
		}));
		f.glyphs.emplace('S', Glyph(3, 5, {
			1,1,1,
			1,0,0,
			1,1,1,
			0,0,1,
			1,1,1,
		}));
		f.glyphs.emplace('T', Glyph(3, 5, {
			1,1,1,
			0,1,0,
			0,1,0,
			0,1,0,
			0,1,0,
		}));
		f.glyphs.emplace('U', Glyph(3, 5, {
			1,0,1,
			1,0,1,
			1,0,1,
			1,0,1,
			1,1,1,
		}));
		f.glyphs.emplace('V', Glyph(3, 5, {
			1,0,1,
			1,0,1,
			1,0,1,
			1,0,1,
			0,1,0,
		}));
		f.glyphs.emplace('W', Glyph(5, 5, {
			1,0,1,0,1,
			1,0,1,0,1,
			1,0,1,0,1,
			1,0,1,0,1,
			0,1,0,1,0,
		}));
		f.glyphs.emplace('X', Glyph(3, 5, {
			1,0,1,
			1,0,1,
			0,1,0,
			1,0,1,
			1,0,1,
		}));
		f.glyphs.emplace('Y', Glyph(3, 5, {
			1,0,1,
			1,0,1,
			0,1,0,
			0,1,0,
			0,1,0,
		}));
		f.glyphs.emplace('Z', Glyph(3, 5, {
			1,1,1,
			0,0,1,
			0,1,0,
			1,0,0,
			1,1,1,
		}));

		f.glyphs.emplace('a', Glyph(3, 5, {
			1,1,1,
			0,0,1,
			1,1,1,
			1,0,1,
			1,1,1,
		}));
		f.glyphs.emplace('b', Glyph(3, 5, {
			1,0,0,
			1,0,0,
			1,1,1,
			1,0,1,
			1,1,1,
		}));
		f.glyphs.emplace('c', Glyph(3, 4, {
			1,1,1,
			1,0,0,
			1,0,0,
			1,1,1,
		}, 1));
		f.glyphs.emplace('d', Glyph(3, 5, {
			0,0,1,
			0,0,1,
			1,1,1,
			1,0,1,
			1,1,1,
		}));
		f.glyphs.emplace('e', Glyph(3, 5, {
			1,1,1,
			1,0,1,
			1,1,1,
			1,0,0,
			1,1,1,
		}));
		f.glyphs.emplace('f', Glyph(3, 5, {
			0,0,1,
			0,1,0,
			1,1,1,
			0,1,0,
			0,1,0,
		}));
		f.glyphs.emplace('g', Glyph(3, 5, {
			0,1,1,
			1,0,1,
			1,1,1,
			0,0,1,
			1,1,0,
		}));
		f.glyphs.emplace('h', Glyph(3, 5, {
			1,0,0,
			1,0,0,
			1,1,0,
			1,0,1,
			1,0,1,
		}));
		f.glyphs.emplace('i', Glyph(1, 5, {
			1,
			0,
			1,
			1,
			1,
		}));
		f.glyphs.emplace('j', Glyph(2, 5, {
			0,1,
			0,1,
			0,1,
			0,1,
			1,0,
		}));
		f.glyphs.emplace('k', Glyph(3, 5, {
			1,0,0,
			1,0,1,
			1,1,0,
			1,0,1,
			1,0,1,
		}));
		f.glyphs.emplace('l', Glyph(2, 5, {
			1,0,
			1,0,
			1,0,
			1,0,
			0,1,
		}));
		f.glyphs.emplace('m', Glyph(5, 4, {
			1,1,0,1,0,
			1,0,1,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
		}, 1));
		f.glyphs.emplace('n', Glyph(3, 4, {
			1,1,0,
			1,0,1,
			1,0,1,
			1,0,1,
		}, 1));
		f.glyphs.emplace('o', Glyph(3, 4, {
			0,1,0,
			1,0,1,
			1,0,1,
			0,1,0,
		}, 1));
		f.glyphs.emplace('p', Glyph(3, 4, {
			1,1,0,
			1,0,1,
			1,1,0,
			1,0,0,
		}, 1));
		f.glyphs.emplace('q', Glyph(3, 4, {
			1,1,0,
			1,0,1,
			0,1,1,
			0,0,1,
		}, 1));
		f.glyphs.emplace('r', Glyph(3, 4, {
			1,1,0,
			1,0,1,
			1,0,0,
			1,0,0,
		}, 1));
		f.glyphs.emplace('s', Glyph(3, 5, {
			0,1,1,
			1,0,0,
			0,1,0,
			0,0,1,
			1,1,0,
		}));
		f.glyphs.emplace('t', Glyph(3, 5, {
			0,1,0,
			1,1,1,
			0,1,0,
			0,1,0,
			0,0,1,
		}));
		f.glyphs.emplace('u', Glyph(3, 4, {
			1,0,1,
			1,0,1,
			1,0,1,
			1,1,1,
		}, 1));
		f.glyphs.emplace('v', Glyph(3, 4, {
			1,0,1,
			1,0,1,
			1,0,1,
			0,1,0,
		}, 1));
		f.glyphs.emplace('w', Glyph(5, 4, {
			1,0,1,0,1,
			1,0,1,0,1,
			1,0,1,0,1,
			0,1,0,1,0,
		}, 1));
		f.glyphs.emplace('x', Glyph(3, 3, {
			1,0,1,
			0,1,0,
			1,0,1,
		}, 2));
		f.glyphs.emplace('y', Glyph(3, 4, {
			1,0,1,
			1,0,1,
			0,1,0,
			1,0,0,
		}, 1));
		f.glyphs.emplace('z', Glyph(3, 5, {
			1,1,0,
			0,0,1,
			0,1,0,
			1,0,0,
			0,1,1,
		}));

		f.glyphs.emplace('0', Glyph(3, 5, {
			1,1,1,
			1,0,1,
			1,0,1,
			1,0,1,
			1,1,1,
		}));
		f.glyphs.emplace('1', Glyph(2, 5, {
			0,1,
			1,1,
			0,1,
			0,1,
			0,1,
		}));
		f.glyphs.emplace('2', Glyph(3, 5, {
			1,1,1,
			0,0,1,
			1,1,1,
			1,0,0,
			1,1,1,
		}));
		f.glyphs.emplace('3', Glyph(3, 5, {
			1,1,1,
			0,0,1,
			1,1,1,
			0,0,1,
			1,1,1,
		}));
		f.glyphs.emplace('4', Glyph(3, 5, {
			1,0,1,
			1,0,1,
			1,1,1,
			0,0,1,
			0,0,1,
		}));
		f.glyphs.emplace('5', Glyph(3, 5, {
			1,1,1,
			1,0,0,
			1,1,1,
			0,0,1,
			1,1,1,
		}));
		f.glyphs.emplace('6', Glyph(3, 5, {
			1,1,1,
			1,0,0,
			1,1,1,
			1,0,1,
			1,1,1,
		}));
		f.glyphs.emplace('7', Glyph(3, 5, {
			1,1,1,
			0,0,1,
			0,0,1,
			0,0,1,
			0,0,1,
		}));
		f.glyphs.emplace('8', Glyph(3, 5, {
			1,1,1,
			1,0,1,
			1,1,1,
			1,0,1,
			1,1,1,
		}));
		f.glyphs.emplace('9', Glyph(3, 5, {
			1,1,1,
			1,0,1,
			1,1,1,
			0,0,1,
			0,0,1,
		}));

		f.glyphs.emplace(' ', Glyph(3, 1, {
			0,0,0,
		}));
		f.glyphs.emplace('.', Glyph(1, 1, {
			1,
		}, 4));
		f.glyphs.emplace(',', Glyph(2, 2, {
			0,1,
			1,0,
		}, 4));
		f.glyphs.emplace(':', Glyph(1, 4, {
			1,
			0,
			0,
			1,
		}, 1));
		f.glyphs.emplace(';', Glyph(2, 5, {
			0,1,
			0,0,
			0,0,
			0,1,
			1,0,
		}, 1));
		f.glyphs.emplace('?', Glyph(2, 5, {
			1,1,
			0,1,
			1,0,
			0,0,
			1,0,
		}));
		f.glyphs.emplace(0xFFFD, Glyph(7, 7, {
			0,0,0,1,0,0,0,
			0,0,1,0,1,0,0,
			0,1,1,1,0,1,0,
			1,1,1,0,1,1,1,
			0,1,1,1,1,1,0,
			0,0,1,0,1,0,0,
			0,0,0,1,0,0,0,
		}, -1));
		f.glyphs.emplace('!', Glyph(1, 5, {
			1,
			1,
			1,
			0,
			1,
		}));
		f.glyphs.emplace('+', Glyph(3, 5, {
			0,0,0,
			0,1,0,
			1,1,1,
			0,1,0,
			0,0,0,
		}));
		f.glyphs.emplace('-', Glyph(3, 5, {
			0,0,0,
			0,0,0,
			1,1,1,
			0,0,0,
			0,0,0,
		}));
		f.glyphs.emplace('*', Glyph(3, 3, {
			1,0,1,
			0,1,0,
			1,0,1,
		}, 1));
		f.glyphs.emplace('/', Glyph(3, 5, {
			0,0,1,
			0,0,1,
			0,1,0,
			1,0,0,
			1,0,0,
		}));
		f.glyphs.emplace('\\', Glyph(3, 5, {
			1,0,0,
			1,0,0,
			0,1,0,
			0,0,1,
			0,0,1,
		}));
		f.glyphs.emplace('_', Glyph(3, 1, {
			1,1,1,
		}, 4));
		return f;
	}

	[[nodiscard]] static RasterFont generateSimple8()
	{
		RasterFont f{};
		f.baseline_glyph_height = 8;
		f.glyphs.emplace('A', Glyph(7, 8, {
			0,0,0,1,0,0,0,
			0,0,1,0,1,0,0,
			0,0,1,0,1,0,0,
			0,1,0,0,0,1,0,
			0,1,1,1,1,1,0,
			0,1,0,0,0,1,0,
			1,0,0,0,0,0,1,
			1,0,0,0,0,0,1,
		}));
		f.glyphs.emplace('B', Glyph(5, 8, {
			1,1,1,1,0,
			1,0,0,0,1,
			1,0,0,0,1,
			1,1,1,1,0,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,1,1,1,0,
		}));
		f.glyphs.emplace('C', Glyph(5, 8, {
			0,1,1,1,1,
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
			0,1,1,1,1,
		}));
		f.glyphs.emplace('D', Glyph(5, 8, {
			1,1,1,1,0,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,1,1,1,0,
		}));
		f.glyphs.emplace('E', Glyph(5, 8, {
			1,1,1,1,1,
			1,0,0,0,0,
			1,0,0,0,0,
			1,1,1,1,0,
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
			1,1,1,1,1,
		}));
		f.glyphs.emplace('F', Glyph(5, 8, {
			1,1,1,1,1,
			1,0,0,0,0,
			1,0,0,0,0,
			1,1,1,1,0,
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
		}));
		f.glyphs.emplace('G', Glyph(5, 8, {
			0,1,1,1,1,
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,1,1,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			0,1,1,1,0,
		}));
		f.glyphs.emplace('H', Glyph(5, 8, {
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,1,1,1,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
		}));
		f.glyphs.emplace('I', Glyph(5, 8, {
			1,1,1,1,1,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,1,0,0,
			1,1,1,1,1,
		}));
		f.glyphs.emplace('J', Glyph(5, 8, {
			1,1,1,1,1,
			0,0,0,0,1,
			0,0,0,0,1,
			0,0,0,0,1,
			0,0,0,0,1,
			0,0,0,0,1,
			1,0,0,0,1,
			0,1,1,1,0,
		}));
		f.glyphs.emplace('K', Glyph(5, 8, {
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,1,0,
			1,1,1,0,0,
			1,0,0,1,0,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,0,
		}));
		f.glyphs.emplace('L', Glyph(5, 8, {
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
			1,1,1,1,1,
		}));
		f.glyphs.emplace('M', Glyph(7, 8, {
			1,0,0,0,0,0,1,
			1,1,0,0,0,1,1,
			1,0,1,0,1,0,1,
			1,0,0,1,0,0,1,
			1,0,0,0,0,0,1,
			1,0,0,0,0,0,1,
			1,0,0,0,0,0,1,
			1,0,0,0,0,0,1,
		}));
		f.glyphs.emplace('N', Glyph(6, 8, {
			1,0,0,0,0,1,
			1,1,0,0,0,1,
			1,0,1,0,0,1,
			1,0,0,1,0,1,
			1,0,0,0,1,1,
			1,0,0,0,0,1,
			1,0,0,0,0,1,
			1,0,0,0,0,1,
		}));
		f.glyphs.emplace('O', Glyph(5, 8, {
			0,1,1,1,0,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			0,1,1,1,0,
		}));
		f.glyphs.emplace('P', Glyph(4, 8, {
			1,1,1,0,
			1,0,0,1,
			1,0,0,1,
			1,1,1,0,
			1,0,0,0,
			1,0,0,0,
			1,0,0,0,
			1,0,0,0,
		}));
		f.glyphs.emplace('Q', Glyph(5, 8, {
			0,1,1,1,0,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,1,0,
			0,1,1,0,1,
		}));
		f.glyphs.emplace('R', Glyph(4, 8, {
			1,1,1,0,
			1,0,0,1,
			1,0,0,1,
			1,1,1,0,
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
		}));
		f.glyphs.emplace('S', Glyph(4, 8, {
			0,1,1,1,
			1,0,0,0,
			1,0,0,0,
			0,1,1,0,
			0,0,0,1,
			0,0,0,1,
			0,0,0,1,
			1,1,1,0,
		}));
		f.glyphs.emplace('T', Glyph(5, 8, {
			1,1,1,1,1,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,1,0,0,
		}));
		f.glyphs.emplace('U', Glyph(5, 8, {
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			0,1,1,1,0,
		}));
		f.glyphs.emplace('V', Glyph(7, 8, {
			1,0,0,0,0,0,1,
			1,0,0,0,0,0,1,
			0,1,0,0,0,1,0,
			0,1,0,0,0,1,0,
			0,1,0,0,0,1,0,
			0,0,1,0,1,0,0,
			0,0,1,0,1,0,0,
			0,0,0,1,0,0,0,
		}));
		f.glyphs.emplace('W', Glyph(11, 8, {
			1,0,0,0,0,1,0,0,0,0,1,
			1,0,0,0,0,1,0,0,0,0,1,
			0,1,0,0,0,1,0,0,0,1,0,
			0,1,0,0,0,1,0,0,0,1,0,
			0,1,0,0,1,0,1,0,0,1,0,
			0,0,1,0,1,0,1,0,1,0,0,
			0,0,1,0,1,0,1,0,1,0,0,
			0,0,0,1,0,0,0,1,0,0,0,
		}));
		f.glyphs.emplace('X', Glyph(5, 8, {
			1,0,0,0,1,
			1,0,0,0,1,
			0,1,0,1,0,
			0,0,1,0,0,
			0,1,0,1,0,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
		}));
		f.glyphs.emplace('Y', Glyph(5, 8, {
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			0,1,0,1,0,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,1,0,0,
		}));
		f.glyphs.emplace('Z', Glyph(6, 8, {
			1,1,1,1,1,1,
			0,0,0,0,0,1,
			0,0,0,0,1,0,
			0,0,0,1,0,0,
			0,0,1,0,0,0,
			0,1,0,0,0,0,
			1,0,0,0,0,0,
			1,1,1,1,1,1,
		}));

		f.glyphs.emplace('a', Glyph(5, 5, {
			0,1,1,0,0,
			0,0,0,1,0,
			0,1,1,1,0,
			1,0,0,1,0,
			0,1,1,0,1,
		}, 3));
		f.glyphs.emplace('b', Glyph(4, 8, {
			1,0,0,0,
			1,0,0,0,
			1,0,0,0,
			1,1,1,0,
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
			1,1,1,0,
		}));
		f.glyphs.emplace('c', Glyph(4, 5, {
			0,1,1,1,
			1,0,0,0,
			1,0,0,0,
			1,0,0,0,
			0,1,1,1,
		}, 3));
		f.glyphs.emplace('d', Glyph(5, 8, {
			0,0,0,1,0,
			0,0,0,1,0,
			0,0,0,1,0,
			0,1,1,1,0,
			1,0,0,1,0,
			1,0,0,1,0,
			1,0,0,1,0,
			0,1,1,0,1,
		}));
		f.glyphs.emplace('e', Glyph(4, 5, {
			0,1,1,0,
			1,0,0,1,
			1,1,1,0,
			1,0,0,0,
			0,1,1,1,
		}, 3));
		f.glyphs.emplace('f', Glyph(4, 8, {
			0,0,1,1,
			0,1,0,0,
			0,1,0,0,
			1,1,1,0,
			0,1,0,0,
			0,1,0,0,
			0,1,0,0,
			0,1,0,0,
		}));
		f.glyphs.emplace('g', Glyph(4, 6, {
			0,1,1,0,
			1,0,0,1,
			0,1,1,1,
			0,0,0,1,
			0,0,0,1,
			0,1,1,0,
		}, 3));
		f.glyphs.emplace('h', Glyph(4, 8, {
			1,0,0,0,
			1,0,0,0,
			1,0,0,0,
			1,1,1,0,
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
		}));
		f.glyphs.emplace('i', Glyph(1, 7, {
			1,
			0,
			1,
			1,
			1,
			1,
			1,
		}, 1));
		f.glyphs.emplace('j', Glyph(2, 8, {
			0,1,
			0,0,
			0,1,
			0,1,
			0,1,
			0,1,
			0,1,
			1,0,
		}, 1));
		f.glyphs.emplace('k', Glyph(4, 7, {
			1,0,0,0,
			1,0,0,1,
			1,0,1,0,
			1,1,0,0,
			1,0,1,0,
			1,0,0,1,
			1,0,0,1,
		}, 1));
		f.glyphs.emplace('l', Glyph(1, 7, {
			1,
			1,
			1,
			1,
			1,
			1,
			1,
		}, 1));
		f.glyphs.emplace('m', Glyph(5, 5, {
			1,1,0,1,0,
			1,0,1,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
		}, 3));
		f.glyphs.emplace('n', Glyph(3, 5, {
			1,1,0,
			1,0,1,
			1,0,1,
			1,0,1,
			1,0,1,
		}, 3));
		f.glyphs.emplace('o', Glyph(4, 5, {
			0,1,1,0,
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
			0,1,1,0,
		}, 3));
		f.glyphs.emplace('p', Glyph(4, 7, {
			1,1,1,0,
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
			1,1,1,0,
			1,0,0,0,
			1,0,0,0,
		}, 3));
		f.glyphs.emplace('q', Glyph(4, 7, {
			0,1,1,1,
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
			0,1,1,1,
			0,0,0,1,
			0,0,0,1,
		}, 3));
		f.glyphs.emplace('r', Glyph(4, 5, {
			1,0,1,1,
			1,1,0,0,
			1,0,0,0,
			1,0,0,0,
			1,0,0,0,
		}, 3));
		f.glyphs.emplace('s', Glyph(3, 5, {
			0,1,1,
			1,0,0,
			0,1,0,
			0,0,1,
			1,1,0,
		}, 3));
		f.glyphs.emplace('t', Glyph(3, 6, {
			0,1,0,
			1,1,1,
			0,1,0,
			0,1,0,
			0,1,0,
			0,0,1,
		}, 2));
		f.glyphs.emplace('u', Glyph(4, 5, {
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
			0,1,1,0,
		}, 3));
		f.glyphs.emplace('v', Glyph(5, 5, {
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			0,1,0,1,0,
			0,0,1,0,0,
		}, 3));
		f.glyphs.emplace('w', Glyph(7, 5, {
			1,0,0,1,0,0,1,
			1,0,0,1,0,0,1,
			1,0,0,1,0,0,1,
			0,1,0,1,0,1,0,
			0,0,1,0,1,0,0,
		}, 3));
		f.glyphs.emplace('x', Glyph(3, 5, {
			1,0,1,
			1,0,1,
			0,1,0,
			1,0,1,
			1,0,1,
		}, 3));
		f.glyphs.emplace('y', Glyph(3, 5, {
			1,0,1,
			1,0,1,
			1,0,1,
			0,1,0,
			1,0,0,
		}, 3));
		f.glyphs.emplace('z', Glyph(4, 5, {
			1,1,1,1,
			0,0,0,1,
			0,0,1,0,
			0,1,0,0,
			1,1,1,1,
		}, 3));

		f.glyphs.emplace('0', Glyph(5, 8, {
			0,1,1,1,0,
			1,0,0,0,1,
			1,0,0,1,1,
			1,0,1,0,1,
			1,1,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			0,1,1,1,0,
		}));
		f.glyphs.emplace('1', Glyph(3, 8, {
			0,0,1,
			1,1,1,
			0,0,1,
			0,0,1,
			0,0,1,
			0,0,1,
			0,0,1,
			0,0,1,
		}));
		f.glyphs.emplace('2', Glyph(5, 8, {
			0,1,1,1,0,
			0,0,0,0,1,
			0,0,0,0,1,
			0,1,1,1,0,
			1,0,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
			0,1,1,1,0,
		}));
		f.glyphs.emplace('3', Glyph(4, 8, {
			1,1,1,0,
			0,0,0,1,
			0,0,0,1,
			1,1,1,0,
			0,0,0,1,
			0,0,0,1,
			0,0,0,1,
			1,1,1,0,
		}));
		f.glyphs.emplace('4', Glyph(5, 8, {
			0,0,0,1,1,
			0,0,1,0,1,
			0,1,0,0,1,
			1,0,0,0,1,
			1,1,1,1,1,
			0,0,0,0,1,
			0,0,0,0,1,
			0,0,0,0,1,
		}));
		f.glyphs.emplace('5', Glyph(5, 8, {
			1,1,1,1,1,
			1,0,0,0,0,
			1,0,0,0,0,
			1,1,1,1,0,
			0,0,0,0,1,
			0,0,0,0,1,
			1,0,0,0,1,
			0,1,1,1,0,
		}));
		f.glyphs.emplace('6', Glyph(5, 8, {
			0,1,1,1,1,
			1,0,0,0,0,
			1,0,0,0,0,
			1,1,1,1,0,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			0,1,1,1,0,
		}));
		f.glyphs.emplace('7', Glyph(5, 8, {
			1,1,1,1,1,
			0,0,0,0,1,
			0,0,0,0,1,
			0,0,0,1,0,
			0,0,0,1,0,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,1,0,0,
		}));
		f.glyphs.emplace('8', Glyph(5, 8, {
			0,1,1,1,0,
			1,0,0,0,1,
			1,0,0,0,1,
			0,1,1,1,0,
			1,0,0,0,1,
			1,0,0,0,1,
			1,0,0,0,1,
			0,1,1,1,0,
		}));
		f.glyphs.emplace('9', Glyph(5, 8, {
			0,1,1,1,0,
			1,0,0,0,1,
			1,0,0,0,1,
			0,1,1,1,1,
			0,0,0,0,1,
			0,0,0,0,1,
			1,0,0,0,1,
			0,1,1,1,0,
		}));

		f.glyphs.emplace(' ', Glyph(3, 1, {
			0,0,0,
		}, 7));
		f.glyphs.emplace('.', Glyph(1, 1, {
			1,
		}, 7));
		f.glyphs.emplace(',', Glyph(2, 2, {
			0,1,
			1,0,
		}, 7));
		f.glyphs.emplace(':', Glyph(1, 4, {
			1,
			0,
			0,
			1,
		}, 4));	
		f.glyphs.emplace(';', Glyph(2, 5, {
			0,1,
			0,0,
			0,0,
			0,1,
			1,0,
		}, 4));
		f.glyphs.emplace('?', Glyph(5, 8, {
			0,1,1,1,0,
			1,0,0,0,1,
			0,0,0,0,1,
			0,0,0,1,0,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,0,0,0,
			0,0,1,0,0,
		}));
		f.glyphs.emplace(0xFFFD, Glyph(11, 11, {
			0,0,0,0,0,1,0,0,0,0,0,
			0,0,0,0,1,1,1,0,0,0,0,
			0,0,0,1,0,0,0,1,0,0,0,
			0,0,1,0,1,1,1,0,1,0,0,
			0,1,1,1,1,1,1,0,1,1,0,
			1,1,1,1,1,1,0,1,1,1,1,
			0,1,1,1,1,0,1,1,1,1,0,
			0,0,1,1,1,0,1,1,1,0,0,
			0,0,0,1,1,1,1,1,0,0,0,
			0,0,0,0,1,0,1,0,0,0,0,
			0,0,0,0,0,1,0,0,0,0,0,
		}, -2));
		f.glyphs.emplace('!', Glyph(1, 8, {
			1,
			1,
			1,
			1,
			1,
			1,
			0,
			1,
		}));
		f.glyphs.emplace('+', Glyph(5, 5, {
			0,0,1,0,0,
			0,0,1,0,0,
			1,1,1,1,1,
			0,0,1,0,0,
			0,0,1,0,0,
		}, 1));
		f.glyphs.emplace('-', Glyph(5, 1, {
			1,1,1,1,1,
		}, 3));
		f.glyphs.emplace('*', Glyph(5, 5, {
			1,0,0,0,1,
			0,1,0,1,0,
			0,0,1,0,0,
			0,1,0,1,0,
			1,0,0,0,1,
		}, 1));
		f.glyphs.emplace('/', Glyph(5, 8, {
			0,0,0,0,1,
			0,0,0,0,1,
			0,0,0,1,0,
			0,0,1,0,0,
			0,0,1,0,0,
			0,1,0,0,0,
			1,0,0,0,0,
			1,0,0,0,0,
		}));
		f.glyphs.emplace('\\', Glyph(5, 8, {
			1,0,0,0,0,
			1,0,0,0,0,
			0,1,0,0,0,
			0,0,1,0,0,
			0,0,1,0,0,
			0,0,0,1,0,
			0,0,0,0,1,
			0,0,0,0,1,
		}));
		f.glyphs.emplace('_', Glyph(5, 1, {
			1,1,1,1,1,
		}, 7));
		return f;
	}

	const RasterFont& RasterFont::simple5()
	{
		static RasterFont simple5_inst = generateSimple5();
		return simple5_inst;
	}

	const RasterFont& RasterFont::simple8()
	{
		static RasterFont simple8_inst = generateSimple8();
		return simple8_inst;
	}

	const Glyph& RasterFont::get(uint32_t c) const
	{
		auto e = glyphs.find(c);
		if (e == glyphs.end())
		{
			e = glyphs.find(0xFFFD);
			if (e == glyphs.end())
			{
				e = glyphs.find('?');
				if (e == glyphs.end())
				{
					return glyphs.at(0);
				}
			}
		}
		return e->second;
	}

	uint32_t RasterFont::getFallback() const
	{
#if SOUP_CPP20
		if (glyphs.contains(0xFFFD))
#else
		if (glyphs.find(0xFFFD) != glyphs.end())
#endif
		{
			return 0xFFFD;
		}
#if SOUP_CPP20
		if (glyphs.contains('?'))
#else
		if (glyphs.find('?') != glyphs.end())
#endif
		{
			return '?';
		}
		return glyphs.cbegin()->first;
	}

	size_t RasterFont::measureWidth(const std::string& text) const
	{
		return measureWidth(unicode::utf8_to_utf32(text));
	}

	size_t RasterFont::measureWidth(const std::u32string& text) const
	{
		size_t x = 0;
		for (auto c = text.begin(); c != text.end(); ++c)
		{
			if (c != text.begin())
			{
				x += 1;
			}
			x += get(*c).width;
		}
		return x;
	}

	std::pair<size_t, size_t> RasterFont::measure(const std::string& text) const
	{
		return measure(unicode::utf8_to_utf32(text));
	}

	std::pair<size_t, size_t> RasterFont::measure(const std::u32string& text) const
	{
		size_t width = 0;
		size_t height = 0;
		for (auto c = text.begin(); c != text.end(); ++c)
		{
			if (c != text.begin())
			{
				width += 1;
			}
			const Glyph& g = get(*c);
			width += g.width;
			if (g.height > height)
			{
				height = g.height;
			}
		}
		return { width, height };
	}
}
