// Auto-generated Raylib Lua bindings - Module: rtext
// Based on real raylib source: rt// Checks if a font is ready - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_IsFontReady(lua_State* L) {
//     Font* font = (Font*)luaL_checkudata(L, 1, "Font");
// 
//     bool result = IsFontReady(*font);
// 
//     lua_pushboolean(L, result);
//     return 1;
// }Font loading and text drawing
// Functions: 32

#include "raylib.h"
#include "lua.h"
#include "lauxlib.h"
#if LUA_VERSION_NUM < 502
#define lua_rawlen lua_objlen
#endif
#include <stdlib.h>
#include <string.h>

// Get the default Font
static int lua_GetFontDefault(lua_State* L) {
    Font result = GetFontDefault();

    Font* result_ptr = (Font*)lua_newuserdata(L, sizeof(Font));
    *result_ptr = result;
    luaL_getmetatable(L, "Font");
    lua_setmetatable(L, -2);
    return 1;
}

// Load font from file into GPU memory (VRAM)
static int lua_LoadFont(lua_State* L) {
    const char * fileName = luaL_checkstring(L, 1);

    Font result = LoadFont(fileName);

    Font* result_ptr = (Font*)lua_newuserdata(L, sizeof(Font));
    *result_ptr = result;
    luaL_getmetatable(L, "Font");
    lua_setmetatable(L, -2);
    return 1;
}

// Load font from file with extended parameters
static int lua_LoadFontEx(lua_State* L) {
    const char * fileName = luaL_checkstring(L, 1);
    int fontSize = luaL_checkinteger(L, 2);
    
    // Check if user provided custom codepoints (optional 3rd parameter)
    Font result;
    if (lua_gettop(L) >= 3 && lua_istable(L, 3)) {
        // User provided codepoints table
        int count = lua_rawlen(L, 3);
        int* codepoints = (int*)malloc(count * sizeof(int));
        
        for (int i = 0; i < count; i++) {
            lua_rawgeti(L, 3, i + 1);
            codepoints[i] = luaL_checkinteger(L, -1);
            lua_pop(L, 1);
        }
        
        result = LoadFontEx(fileName, fontSize, codepoints, count);
        free(codepoints);
    } else {
        // Try loading with Polish characters first
        int polishCodepoints[] = {
            // ASCII printable characters (32-126)
            32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
            48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
            64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
            80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
            96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
            112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126,
            // Polish characters (if supported by font)
            260, 261, 262, 263, 280, 281, 321, 322, 323, 324, 211, 243, 346, 347, 377, 378, 379, 380
        };
        int polishCount = sizeof(polishCodepoints) / sizeof(polishCodepoints[0]);
        
        // Load font with Polish charset - raylib will handle missing glyphs automatically
        result = LoadFontEx(fileName, fontSize, polishCodepoints, polishCount);
        
        // If font loading failed completely, fallback to default font
        if (result.texture.id == 0) {
            result = GetFontDefault();
        }
    }

    Font* result_ptr = (Font*)lua_newuserdata(L, sizeof(Font));
    *result_ptr = result;
    luaL_getmetatable(L, "Font");
    lua_setmetatable(L, -2);
    return 1;
}

// Load font from Image (XNA style)
static int lua_LoadFontFromImage(lua_State* L) {
    Image* image = (Image*)luaL_checkudata(L, 1, "Image");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color key = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    int firstChar = luaL_checkinteger(L, 3);

    Font result = LoadFontFromImage(*image, key, firstChar);

    Font* result_ptr = (Font*)lua_newuserdata(L, sizeof(Font));
    *result_ptr = result;
    luaL_getmetatable(L, "Font");
    lua_setmetatable(L, -2);
    return 1;
}

// Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
static int lua_LoadFontFromMemory(lua_State* L) {
    const char * fileType = luaL_checkstring(L, 1);
    size_t dataLength;
    const unsigned char* fileData = (const unsigned char*)luaL_checklstring(L, 2, &dataLength);
    int dataSize = (int)dataLength;
    int fontSize = luaL_checkinteger(L, 4);
    // For simplicity, using NULL for codepoints and 0 for count (loads default charset)

    Font result = LoadFontFromMemory(fileType, fileData, dataSize, fontSize, NULL, 0);

    Font* result_ptr = (Font*)lua_newuserdata(L, sizeof(Font));
    *result_ptr = result;
    luaL_getmetatable(L, "Font");
    lua_setmetatable(L, -2);
    return 1;
}

// Check if a font is ready - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_IsFontReady(lua_State* L) {
//     Font* font = (Font*)luaL_checkudata(L, 1, "Font");
// 
//     bool result = IsFontReady(*font);
// 
//     lua_pushboolean(L, result);
//     return 1;
// }

// Generate image font atlas using chars info
static int lua_GenImageFontAtlas(lua_State* L) {
    // Complex function - simplified implementation for now
    // Returns empty image as placeholder
    luaL_error(L, "GenImageFontAtlas not fully implemented yet");
    
    Image result = {0};
    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Unload font chars info data (RAM)
static int lua_UnloadFontData(lua_State* L) {
    // Complex function - simplified implementation for now
    luaL_error(L, "UnloadFontData not fully implemented yet");
    return 0;
}

// Unload font from GPU memory (VRAM)
static int lua_UnloadFont(lua_State* L) {
    Font* font = (Font*)luaL_checkudata(L, 1, "Font");

    UnloadFont(*font);

    return 0;
}

// Export font as code file, returns true on success
static int lua_ExportFontAsCode(lua_State* L) {
    Font* font = (Font*)luaL_checkudata(L, 1, "Font");
    const char * fileName = luaL_checkstring(L, 2);

    bool result = ExportFontAsCode(*font, fileName);

    lua_pushboolean(L, result);
    return 1;
}

// Draw current FPS
static int lua_DrawFPS(lua_State* L) {
    int posX = luaL_checkinteger(L, 1);
    int posY = luaL_checkinteger(L, 2);

    DrawFPS(posX, posY);

    return 0;
}

// Draw text (using default font)
static int lua_DrawText(lua_State* L) {
    const char * text = luaL_checkstring(L, 1);
    int posX = luaL_checkinteger(L, 2);
    int posY = luaL_checkinteger(L, 3);
    int fontSize = luaL_checkinteger(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawText(text, posX, posY, fontSize, color);

    return 0;
}

// Draw text using font and additional parameters
static int lua_DrawTextEx(lua_State* L) {
    Font* font = (Font*)luaL_checkudata(L, 1, "Font");
    const char * text = luaL_checkstring(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 position = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float fontSize = luaL_checknumber(L, 4);
    float spacing = luaL_checknumber(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTextEx(*font, text, position, fontSize, spacing, tint);

    return 0;
}

// Draw text using Font and pro parameters (rotation)
static int lua_DrawTextPro(lua_State* L) {
    Font* font = (Font*)luaL_checkudata(L, 1, "Font");
    const char * text = luaL_checkstring(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 position = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    Vector2 origin = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float rotation = luaL_checknumber(L, 5);
    float fontSize = luaL_checknumber(L, 6);
    float spacing = luaL_checknumber(L, 7);
    luaL_checktype(L, 8, LUA_TTABLE);
    lua_getfield(L, 8, "r");
    lua_getfield(L, 8, "g");
    lua_getfield(L, 8, "b");
    lua_getfield(L, 8, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTextPro(*font, text, position, origin, rotation, fontSize, spacing, tint);

    return 0;
}

// Draw one character (codepoint)
static int lua_DrawTextCodepoint(lua_State* L) {
    Font* font = (Font*)luaL_checkudata(L, 1, "Font");
    int codepoint = luaL_checkinteger(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 position = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float fontSize = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTextCodepoint(*font, codepoint, position, fontSize, tint);

    return 0;
}

// Draw multiple character (codepoint)
static int lua_DrawTextCodepoints(lua_State* L) {
    // Font* font = (Font*)luaL_checkudata(L, 1, "Font"); // nieużywane, stub
    // Complex function - simplified implementation for now
    luaL_error(L, "DrawTextCodepoints not fully implemented yet");
    return 0;
}

// Measure string width for default font
static int lua_MeasureText(lua_State* L) {
    const char * text = luaL_checkstring(L, 1);
    int fontSize = luaL_checkinteger(L, 2);

    int result = MeasureText(text, fontSize);

    lua_pushinteger(L, result);
    return 1;
}

// Measure string size for Font
static int lua_MeasureTextEx(lua_State* L) {
    Font* font = (Font*)luaL_checkudata(L, 1, "Font");
    const char * text = luaL_checkstring(L, 2);
    float fontSize = luaL_checknumber(L, 3);
    float spacing = luaL_checknumber(L, 4);

    Vector2 result = MeasureTextEx(*font, text, fontSize, spacing);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// TextFormat: formats text with arguments
static int lua_TextFormat(lua_State* L) {
    const char* fmt = luaL_checkstring(L, 1);
    char buf[1024];
    int nargs = lua_gettop(L) - 1;
    if (nargs == 0) snprintf(buf, sizeof(buf), "%s", fmt);
    else if (nargs == 1) snprintf(buf, sizeof(buf), fmt, luaL_checkstring(L, 2));
    else if (nargs == 2) snprintf(buf, sizeof(buf), fmt, luaL_checkstring(L, 2), luaL_checkstring(L, 3));
    else if (nargs == 3) snprintf(buf, sizeof(buf), fmt, luaL_checkstring(L, 2), luaL_checkstring(L, 3), luaL_checkstring(L, 4));
    else snprintf(buf, sizeof(buf), fmt, luaL_checkstring(L, 2), luaL_checkstring(L, 3), luaL_checkstring(L, 4), luaL_checkstring(L, 5));
    lua_pushstring(L, buf);
    return 1;
}

// TextFormat: formats text with arguments

static int lua_SetTextLineSpacing(lua_State* L) {
    int spacing = luaL_checkinteger(L, 1);
    SetTextLineSpacing(spacing);
    return 0;
}

static int lua_GetGlyphIndex(lua_State* L) {
    Font* font = (Font*)luaL_checkudata(L, 1, "Font");
    int codepoint = luaL_checkinteger(L, 2);
    int idx = GetGlyphIndex(*font, codepoint);
    lua_pushinteger(L, idx);
    return 1;
}

static int lua_LoadUTF8(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int len = lua_rawlen(L, 1);
    int* codepoints = malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++) {
        lua_rawgeti(L, 1, i+1);
        codepoints[i] = luaL_checkinteger(L, -1);
        lua_pop(L, 1);
    }
    char* result = LoadUTF8(codepoints, len);
    free(codepoints);
    lua_pushstring(L, result);
    UnloadUTF8(result);
    return 1;
}

static int lua_LoadCodepoints(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    int count = 0;
    int* codepoints = LoadCodepoints(text, &count);
    lua_newtable(L);
    for (int i = 0; i < count; i++) {
        lua_pushinteger(L, codepoints[i]);
        lua_rawseti(L, -2, i+1);
    }
    UnloadCodepoints(codepoints);
    return 1;
}


static int lua_CodepointToUTF8(lua_State* L) {
    int codepoint = luaL_checkinteger(L, 1);
    int utf8Size = 0;
    const char* result = CodepointToUTF8(codepoint, &utf8Size);
    lua_pushstring(L, result);
    lua_pushinteger(L, utf8Size);
    return 2;
}

static int lua_TextSubtext(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    int pos = luaL_checkinteger(L, 2);
    int len = luaL_checkinteger(L, 3);
    const char* result = TextSubtext(text, pos, len);
    lua_pushstring(L, result);
    return 1;
}

static int lua_TextReplace(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    const char* replace = luaL_checkstring(L, 2);
    const char* by = luaL_checkstring(L, 3);
    char* result = TextReplace(text, replace, by);
    lua_pushstring(L, result);
    free(result);
    return 1;
}

static int lua_TextInsert(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    const char* insert = luaL_checkstring(L, 2);
    int pos = luaL_checkinteger(L, 3);
    char* result = TextInsert(text, insert, pos);
    lua_pushstring(L, result);
    free(result);
    return 1;
}

static int lua_TextJoin(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int count = lua_rawlen(L, 1);
    const char** list = malloc(sizeof(char*) * count);
    for (int i = 0; i < count; i++) {
        lua_rawgeti(L, 1, i+1);
        list[i] = luaL_checkstring(L, -1);
        lua_pop(L, 1);
    }
    const char* delim = luaL_checkstring(L, 2);
    const char* result = TextJoin(list, count, delim);
    lua_pushstring(L, result);
    free(list);
    return 1;
}

static int lua_TextSplit(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    char delim = luaL_checkstring(L, 2)[0];
    int count = 0;
    const char** parts = TextSplit(text, delim, &count);
    lua_newtable(L);
    for (int i = 0; i < count; i++) {
        lua_pushstring(L, parts[i]);
        lua_rawseti(L, -2, i+1);
    }
    return 1;
}

static int lua_TextToUpper(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    const char* result = TextToUpper(text);
    lua_pushstring(L, result);
    return 1;
}

static int lua_TextToLower(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    const char* result = TextToLower(text);
    lua_pushstring(L, result);
    return 1;
}

static int lua_TextToPascal(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    const char* result = TextToPascal(text);
    lua_pushstring(L, result);
    return 1;
}

static int lua_TextToSnake(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    const char* result = TextToSnake(text);
    lua_pushstring(L, result);
    return 1;
}

static int lua_TextToCamel(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    const char* result = TextToCamel(text);
    lua_pushstring(L, result);
    return 1;
}

static int lua_TextToFloat(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    float result = TextToFloat(text);
    lua_pushnumber(L, result);
    return 1;
}

// Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
static int lua_GetGlyphInfo(lua_State* L) {
    // TODO: Push GlyphInfo jako tabela
    return 1;
}

// Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found
static int lua_GetGlyphAtlasRec(lua_State* L) {
    Font* font = (Font*)luaL_checkudata(L, 1, "Font");
    int codepoint = luaL_checkinteger(L, 2);

    Rectangle result = GetGlyphAtlasRec(*font, codepoint);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, result.width);
    lua_setfield(L, -2, "width");
    lua_pushnumber(L, result.height);
    lua_setfield(L, -2, "height");
    return 1;
}

// Unload UTF-8 text encoded from codepoints array
static int lua_UnloadUTF8(lua_State* L) {
    const char * text = luaL_checkstring(L, 1);

    UnloadUTF8((char*)text);

    return 0;
}

// Unload codepoints data from memory
static int lua_UnloadCodepoints(lua_State* L) {
    // Complex function - simplified implementation for now
    luaL_error(L, "UnloadCodepoints not fully implemented yet");
    return 0;
}

// Get total number of codepoints in a UTF-8 encoded string
static int lua_GetCodepointCount(lua_State* L) {
    const char * text = luaL_checkstring(L, 1);

    int result = GetCodepointCount(text);

    lua_pushinteger(L, result);
    return 1;
}

// Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
static int lua_GetCodepoint(lua_State* L) {
    const char * text = luaL_checkstring(L, 1);
    int codepointSize = 0;

    int result = GetCodepoint(text, &codepointSize);

    lua_pushinteger(L, result);
    lua_pushinteger(L, codepointSize);  // Also return the size
    return 2;
}

// Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
static int lua_GetCodepointNext(lua_State* L) {
    const char * text = luaL_checkstring(L, 1);
    int codepointSize = 0;

    int result = GetCodepointNext(text, &codepointSize);

    lua_pushinteger(L, result);
    lua_pushinteger(L, codepointSize);  // Also return the size
    return 2;
}

// Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
static int lua_GetCodepointPrevious(lua_State* L) {
    const char * text = luaL_checkstring(L, 1);
    int codepointSize = 0;

    int result = GetCodepointPrevious(text, &codepointSize);

    lua_pushinteger(L, result);
    lua_pushinteger(L, codepointSize);  // Also return the size
    return 2;
}

// Copy one string to another, returns bytes copied
static int lua_TextCopy(lua_State* L) {
    const char * src = luaL_checkstring(L, 2);
    char buf[1024];
    int result = TextCopy(buf, src);
    lua_pushinteger(L, result);
    return 1;
}

// Check if two text string are equal
static int lua_TextIsEqual(lua_State* L) {
    const char * text1 = luaL_checkstring(L, 1);
    const char * text2 = luaL_checkstring(L, 2);

    bool result = TextIsEqual(text1, text2);

    lua_pushboolean(L, result);
    return 1;

    // TextFormat: formats text with arguments
}

// Get text length, checks for '\0' ending
static int lua_TextLength(lua_State* L) {
    const char * text = luaL_checkstring(L, 1);

    unsigned int result = TextLength(text);

    lua_pushinteger(L, result);
    return 1;
}

// Append text at specific position and move cursor!
static int lua_TextAppend(lua_State* L) {
    const char * text = luaL_checkstring(L, 1);
    const char * append = luaL_checkstring(L, 2);
    int position = luaL_checkinteger(L, 3);
    char buf[1024];
    strncpy(buf, text, sizeof(buf));
    TextAppend(buf, append, &position);
    lua_pushinteger(L, position);  // Zwraca nową pozycję
    return 1;
}

// Find first text occurrence within a string
static int lua_TextFindIndex(lua_State* L) {
    const char * text = luaL_checkstring(L, 1);
    const char * find = luaL_checkstring(L, 2);

    int result = TextFindIndex(text, find);

    lua_pushinteger(L, result);
    return 1;
}

// Get integer value from text (negative values not supported)
static int lua_TextToInteger(lua_State* L) {
    const char * text = luaL_checkstring(L, 1);

    int result = TextToInteger(text);

    lua_pushinteger(L, result);
    return 1;
}


// Metatable definitions for userdata used in this module
static int Image_gc(lua_State* L) {
    Image* obj = (Image*)luaL_checkudata(L, 1, "Image");
    if (obj != NULL) {
        UnloadImage(*obj);
    }
    return 0;
}

static void create_Image_metatable(lua_State* L) {
    luaL_newmetatable(L, "Image");
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, Image_gc);
    lua_settable(L, -3);
    lua_pop(L, 1);  // Remove metatable from stack
}

static int Font_gc(lua_State* L) {
    Font* obj = (Font*)luaL_checkudata(L, 1, "Font");
    if (obj != NULL) {
        UnloadFont(*obj);
    }
    return 0;
}

static void create_Font_metatable(lua_State* L) {
    luaL_newmetatable(L, "Font");
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, Font_gc);
    lua_settable(L, -3);
    lua_pop(L, 1);  // Remove metatable from stack
}

static const struct luaL_Reg rtext_functions[] = {
    {"GetFontDefault", lua_GetFontDefault},
    {"LoadFont", lua_LoadFont},
    {"LoadFontEx", lua_LoadFontEx},
    {"LoadFontFromImage", lua_LoadFontFromImage},
    {"LoadFontFromMemory", lua_LoadFontFromMemory},
    {"GenImageFontAtlas", lua_GenImageFontAtlas},
    {"UnloadFontData", lua_UnloadFontData},
    {"UnloadFont", lua_UnloadFont},
    {"ExportFontAsCode", lua_ExportFontAsCode},
    {"DrawFPS", lua_DrawFPS},
    {"DrawText", lua_DrawText},
    {"DrawTextEx", lua_DrawTextEx},
    {"DrawTextPro", lua_DrawTextPro},
    {"DrawTextCodepoint", lua_DrawTextCodepoint},
    {"DrawTextCodepoints", lua_DrawTextCodepoints},
    {"MeasureText", lua_MeasureText},
    {"MeasureTextEx", lua_MeasureTextEx},
    {"GetGlyphInfo", lua_GetGlyphInfo},
    {"GetGlyphAtlasRec", lua_GetGlyphAtlasRec},
    {"UnloadUTF8", lua_UnloadUTF8},
    {"UnloadCodepoints", lua_UnloadCodepoints},
    {"GetCodepointCount", lua_GetCodepointCount},
    {"GetCodepoint", lua_GetCodepoint},
    {"GetCodepointNext", lua_GetCodepointNext},
    {"GetCodepointPrevious", lua_GetCodepointPrevious},
    {"TextCopy", lua_TextCopy},
    {"TextIsEqual", lua_TextIsEqual},
    {"TextLength", lua_TextLength},
    {"TextAppend", lua_TextAppend},
    {"TextFindIndex", lua_TextFindIndex},
    {"TextToInteger", lua_TextToInteger},
    {"TextFormat", lua_TextFormat},
    {"SetTextLineSpacing", lua_SetTextLineSpacing},
    {"GetGlyphIndex", lua_GetGlyphIndex},
    {"LoadUTF8", lua_LoadUTF8},
    {"LoadCodepoints", lua_LoadCodepoints},
    {"UnloadCodepoints", lua_UnloadCodepoints},
    {"CodepointToUTF8", lua_CodepointToUTF8},
    {"TextSubtext", lua_TextSubtext},
    {"TextReplace", lua_TextReplace},
    {"TextInsert", lua_TextInsert},
    {"TextJoin", lua_TextJoin},
    {"TextSplit", lua_TextSplit},
    {"TextToUpper", lua_TextToUpper},
    {"TextToLower", lua_TextToLower},
    {"TextToPascal", lua_TextToPascal},
    {"TextToSnake", lua_TextToSnake},
    {"TextToCamel", lua_TextToCamel},
    {"TextToFloat", lua_TextToFloat},
    {NULL, NULL}
};

int luaopen_rtext(lua_State* L) {
    create_Image_metatable(L);
    create_Font_metatable(L);
    luaL_register(L, "rtext", rtext_functions);
    return 1;
}
