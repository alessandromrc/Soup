#include "base.hpp"

#if SOUP_STANDALONE || SOUP_CODE_INSPECTOR

#include <stdexcept>
#include <string>

using stdexception = std::exception;
using stdstring = std::string;

#if SOUP_CODE_INSPECTOR
#include "soup.h" // Dummy include, prevents IntelliSense from adding this
#endif

#include "RaiiEmulator.hpp"

#include "base40.hpp"
#include "base64.hpp"
#include "Canvas.hpp"
#include "InquiryLang.hpp"
#include "KeyGenId.hpp"
#include "Mixed.hpp"
#include "QrCode.hpp"
#include "rsa.hpp"

using namespace soup;

static RaiiEmulator heap{};
static std::string ret_str_buf{};

[[nodiscard]] static const char* ret_str(std::string&& str)
{
	ret_str_buf = std::move(str);
	return ret_str_buf.c_str();
}

#define returnString(x) return ret_str(x);

// [global namespace]

SOUP_CEXPORT void beginScope()
{
	heap.beginScope();
}

SOUP_CEXPORT void endScope()
{
	heap.endScope();
}

SOUP_CEXPORT void broadenScope(void* inst)
{
	heap.broadenScope(inst);
}

SOUP_CEXPORT void endLifetime(void* inst)
{
	heap.free(inst);
}

SOUP_CEXPORT const char* tryCatch(void(*f)())
{
	try
	{
		f();
	}
	catch (const std::exception& e)
	{
		returnString(e.what());
	}
	catch (...)
	{
		returnString("...");
	}
	return nullptr;
}

// base40

SOUP_CEXPORT const char* base40_encode(const stdstring* x)
{
	returnString(base40::encode(*x));
}

SOUP_CEXPORT stdstring* base40_decode(const char* x)
{
	return heap.add(new std::string(base40::decode(x)));
}

// base64

SOUP_CEXPORT const char* base64_encode(const stdstring* x)
{
	returnString(base64::encode(*x));
}

// Bigint

SOUP_CEXPORT const char* Bigint_toString(const Bigint* x)
{
	returnString(x->toString());
}

// Canvas

SOUP_CEXPORT unsigned int Canvas_getWidth(const Canvas* x)
{
	return x->width;
}

SOUP_CEXPORT unsigned int Canvas_getHeight(const Canvas* x)
{
	return x->height;
}

SOUP_CEXPORT void Canvas_resizeNearestNeighbour(Canvas* x, unsigned int desired_width, unsigned int desired_height)
{
	x->resizeNearestNeighbour(desired_width, desired_height);
}

SOUP_CEXPORT const char* Canvas_toSvg(const Canvas* x, unsigned int scale)
{
	returnString(x->toSvg(scale));
}

SOUP_CEXPORT stdstring* Canvas_toNewPngString(const Canvas* x)
{
	return heap.add(x->toPng());
}

// InquiryLang

SOUP_CEXPORT Mixed* InquiryLang_execute(const char* x)
{
	if (auto res = InquiryLang::execute(x))
	{
		return res.release();
	}
	return nullptr;
}

SOUP_CEXPORT const char* InquiryLang_formatResultLine(const Mixed* x)
{
	returnString(InquiryLang::formatResultLine(*x));
}

// KeyGenId

SOUP_CEXPORT KeyGenId* KeyGenId_newFromSeedsExport(unsigned int bits, const stdstring* str)
{
	return heap.add(new KeyGenId(bits, *str));
}

SOUP_CEXPORT KeyGenId* KeyGenId_generate(unsigned int bits)
{
	return heap.add(KeyGenId::generate(bits));
}

SOUP_CEXPORT stdstring* KeyGenId_toSeedsExport(const KeyGenId* x)
{
	return heap.add(x->toSeedsExport());
}

SOUP_CEXPORT RsaKeypair* KeyGenId_getKeypair(const KeyGenId* x)
{
	return heap.add(x->getKeypair());
}

// Mixed

SOUP_CEXPORT bool Mixed_isCanvas(const Mixed* x)
{
	return x->isCanvas();
}

SOUP_CEXPORT Canvas* Mixed_getCanvas(const Mixed* x)
{
	return &x->getCanvas();
}

// QrCode

SOUP_CEXPORT QrCode* QrCode_newFromText(const char* x)
{
	return heap.add(QrCode::encodeText(x));
}

SOUP_CEXPORT Canvas* QrCode_toNewCanvas(const QrCode* x, unsigned int border, bool black_bg)
{
	return heap.add(x->toCanvas(border, black_bg));
}

// RsaKeypair

SOUP_CEXPORT const Bigint* RsaKeypair_getN(const RsaKeypair* x)
{
	return &x->n;
}

SOUP_CEXPORT const Bigint* RsaKeypair_getP(const RsaKeypair* x)
{
	return &x->p;
}

SOUP_CEXPORT const Bigint* RsaKeypair_getQ(const RsaKeypair* x)
{
	return &x->q;
}

// std::exception

SOUP_CEXPORT const char* exception_what(const stdexception* x)
{
	returnString(x->what());
}

#endif