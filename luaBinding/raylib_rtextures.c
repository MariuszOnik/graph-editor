// Auto-generated Raylib Lua bindings - Module: rtextures
// Based on real raylib source: rtextures.c
// Texture and image loading, generation and drawing
// Functions: 94

#include "raylib.h"
#include "lua.h"
#include "lauxlib.h"
#include <stdlib.h>
#include <string.h>

// Compatibility wrapper for lua_rawlen (not available in Lua 5.1)
#ifndef lua_rawlen
#define lua_rawlen(L, idx) lua_objlen(L, idx)
#endif

// Load image from file into CPU memory (RAM)
static int lua_LoadImage(lua_State* L) {
    const char * fileName = luaL_checkstring(L, 1);

    Image result = LoadImage(fileName);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Load image from RAW file data
static int lua_LoadImageRaw(lua_State* L) {
    const char * fileName = luaL_checkstring(L, 1);
    int width = luaL_checkinteger(L, 2);
    int height = luaL_checkinteger(L, 3);
    int format = luaL_checkinteger(L, 4);
    int headerSize = luaL_checkinteger(L, 5);

    Image result = LoadImageRaw(fileName, width, height, format, headerSize);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Load image from SVG file data or string with specified size - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_LoadImageSvg(lua_State* L) {
//     const char * fileNameOrString = luaL_checkstring(L, 1);
//     int width = luaL_checkinteger(L, 2);
//     int height = luaL_checkinteger(L, 3);
// 
//     Image result = LoadImageSvg(fileNameOrString, width, height);
// 
//     Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
//     *result_ptr = result;
//     luaL_getmetatable(L, "Image");
//     lua_setmetatable(L, -2);
//     return 1;
// }

// Load image sequence from file (frames appended to image.data)
static int lua_LoadImageAnim(lua_State* L) {
    const char * fileName = luaL_checkstring(L, 1);
    int frames = 0;

    Image result = LoadImageAnim(fileName, &frames);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    
    // Return frames count as second value
    lua_pushinteger(L, frames);
    return 2;
}

// Load image from memory buffer, fileType refers to extension: i.e. '.png'
static int lua_LoadImageFromMemory(lua_State* L) {
    const char * fileType = luaL_checkstring(L, 1);
    size_t dataLength;
    const unsigned char* fileData = (const unsigned char*)luaL_checklstring(L, 2, &dataLength);
    int dataSize = luaL_checkinteger(L, 3);

    Image result = LoadImageFromMemory(fileType, fileData, dataSize);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Load image from GPU texture data
static int lua_LoadImageFromTexture(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");

    Image result = LoadImageFromTexture(*texture);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Load image from screen buffer and (screenshot)
static int lua_LoadImageFromScreen(lua_State* L) {
    Image result = LoadImageFromScreen();

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Check if an image is ready - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_IsImageReady(lua_State* L) {
//     Image* image = (Image*)luaL_checkudata(L, 1, "Image");
// 
//     bool result = IsImageReady(*image);
// 
//     lua_pushboolean(L, result);
//     return 1;
// }

// Unload image from CPU memory (RAM)
static int lua_UnloadImage(lua_State* L) {
    Image* image = (Image*)luaL_checkudata(L, 1, "Image");

    UnloadImage(*image);

    return 0;
}

// Export image data to file, returns true on success
static int lua_ExportImage(lua_State* L) {
    Image* image = (Image*)luaL_checkudata(L, 1, "Image");
    const char * fileName = luaL_checkstring(L, 2);

    bool result = ExportImage(*image, fileName);

    lua_pushboolean(L, result);
    return 1;
}

// Export image as code file defining an array of bytes, returns true on success
static int lua_ExportImageAsCode(lua_State* L) {
    Image* image = (Image*)luaL_checkudata(L, 1, "Image");
    const char * fileName = luaL_checkstring(L, 2);

    bool result = ExportImageAsCode(*image, fileName);

    lua_pushboolean(L, result);
    return 1;
}

// Generate image: plain color
static int lua_GenImageColor(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    Image result = GenImageColor(width, height, color);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient
static int lua_GenImageGradientLinear(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    int direction = luaL_checkinteger(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color start = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color end = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    Image result = GenImageGradientLinear(width, height, direction, start, end);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate image: radial gradient
static int lua_GenImageGradientRadial(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    float density = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color inner = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color outer = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    Image result = GenImageGradientRadial(width, height, density, inner, outer);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate image: square gradient
static int lua_GenImageGradientSquare(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    float density = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color inner = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color outer = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    Image result = GenImageGradientSquare(width, height, density, inner, outer);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate image: checked
static int lua_GenImageChecked(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    int checksX = luaL_checkinteger(L, 3);
    int checksY = luaL_checkinteger(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color col1 = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color col2 = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    Image result = GenImageChecked(width, height, checksX, checksY, col1, col2);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate image: white noise
static int lua_GenImageWhiteNoise(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    float factor = luaL_checknumber(L, 3);

    Image result = GenImageWhiteNoise(width, height, factor);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate image: perlin noise
static int lua_GenImagePerlinNoise(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    int offsetX = luaL_checkinteger(L, 3);
    int offsetY = luaL_checkinteger(L, 4);
    float scale = luaL_checknumber(L, 5);

    Image result = GenImagePerlinNoise(width, height, offsetX, offsetY, scale);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate image: cellular algorithm, bigger tileSize means bigger cells
static int lua_GenImageCellular(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    int tileSize = luaL_checkinteger(L, 3);

    Image result = GenImageCellular(width, height, tileSize);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate image: grayscale image from text data
static int lua_GenImageText(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    const char * text = luaL_checkstring(L, 3);

    Image result = GenImageText(width, height, text);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Create an image duplicate (useful for transformations)
static int lua_ImageCopy(lua_State* L) {
    Image* image = (Image*)luaL_checkudata(L, 1, "Image");

    Image result = ImageCopy(*image);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Create an image from another image piece
static int lua_ImageFromImage(lua_State* L) {
    Image* image = (Image*)luaL_checkudata(L, 1, "Image");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "width");
    lua_getfield(L, 2, "height");
    Rectangle rec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);

    Image result = ImageFromImage(*image, rec);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Create an image from text (default font)
static int lua_ImageText(lua_State* L) {
    const char * text = luaL_checkstring(L, 1);
    int fontSize = luaL_checkinteger(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    Image result = ImageText(text, fontSize, color);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Create an image from text (custom sprite font)
static int lua_ImageTextEx(lua_State* L) {
    Font* font = (Font*)luaL_checkudata(L, 1, "Font");
    const char * text = luaL_checkstring(L, 2);
    float fontSize = luaL_checknumber(L, 3);
    float spacing = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    Image result = ImageTextEx(*font, text, fontSize, spacing, tint);

    Image* result_ptr = (Image*)lua_newuserdata(L, sizeof(Image));
    *result_ptr = result;
    luaL_getmetatable(L, "Image");
    lua_setmetatable(L, -2);
    return 1;
}

// Convert image data to desired format
static int lua_ImageFormat(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    int newFormat = luaL_checkinteger(L, 2);

    ImageFormat(image, newFormat);

    return 0;
}

// Convert image to POT (power-of-two)
static int lua_ImageToPOT(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color fill = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageToPOT(image, fill);

    return 0;
}

// Crop an image to a defined rectangle
static int lua_ImageCrop(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "width");
    lua_getfield(L, 2, "height");
    Rectangle crop = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);

    ImageCrop(image, crop);

    return 0;
}

// Crop image depending on alpha value
static int lua_ImageAlphaCrop(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    float threshold = luaL_checknumber(L, 2);

    ImageAlphaCrop(image, threshold);

    return 0;
}

// Clear alpha channel to desired color
static int lua_ImageAlphaClear(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    float threshold = luaL_checknumber(L, 3);

    ImageAlphaClear(image, color, threshold);

    return 0;
}

// Apply alpha mask to image
static int lua_ImageAlphaMask(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    Image* alphaMask = (Image*)luaL_checkudata(L, 2, "Image");

    ImageAlphaMask(image, *alphaMask);

    return 0;
}

// Premultiply alpha channel
static int lua_ImageAlphaPremultiply(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }

    ImageAlphaPremultiply(image);

    return 0;
}

// Apply Gaussian blur using a box blur approximation
static int lua_ImageBlurGaussian(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    int blurSize = luaL_checkinteger(L, 2);

    ImageBlurGaussian(image, blurSize);

    return 0;
}

// Resize image (Bicubic scaling algorithm)
static int lua_ImageResize(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    int newWidth = luaL_checkinteger(L, 2);
    int newHeight = luaL_checkinteger(L, 3);

    ImageResize(image, newWidth, newHeight);

    return 0;
}

// Resize image (Nearest-Neighbor scaling algorithm)
static int lua_ImageResizeNN(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    int newWidth = luaL_checkinteger(L, 2);
    int newHeight = luaL_checkinteger(L, 3);

    ImageResizeNN(image, newWidth, newHeight);

    return 0;
}

// Resize canvas and fill with color
static int lua_ImageResizeCanvas(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    int newWidth = luaL_checkinteger(L, 2);
    int newHeight = luaL_checkinteger(L, 3);
    int offsetX = luaL_checkinteger(L, 4);
    int offsetY = luaL_checkinteger(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color fill = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageResizeCanvas(image, newWidth, newHeight, offsetX, offsetY, fill);

    return 0;
}

// Compute all mipmap levels for a provided image
static int lua_ImageMipmaps(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }

    ImageMipmaps(image);

    return 0;
}

// Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
static int lua_ImageDither(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    int rBpp = luaL_checkinteger(L, 2);
    int gBpp = luaL_checkinteger(L, 3);
    int bBpp = luaL_checkinteger(L, 4);
    int aBpp = luaL_checkinteger(L, 5);

    ImageDither(image, rBpp, gBpp, bBpp, aBpp);

    return 0;
}

// Flip image vertically
static int lua_ImageFlipVertical(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }

    ImageFlipVertical(image);

    return 0;
}

// Flip image horizontally
static int lua_ImageFlipHorizontal(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }

    ImageFlipHorizontal(image);

    return 0;
}

// Rotate image by input angle in degrees (-359 to 359)
static int lua_ImageRotate(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    int degrees = luaL_checkinteger(L, 2);

    ImageRotate(image, degrees);

    return 0;
}

// Rotate image clockwise 90deg
static int lua_ImageRotateCW(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }

    ImageRotateCW(image);

    return 0;
}

// Rotate image counter-clockwise 90deg
static int lua_ImageRotateCCW(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }

    ImageRotateCCW(image);

    return 0;
}

// Modify image color: tint
static int lua_ImageColorTint(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageColorTint(image, color);

    return 0;
}

// Modify image color: invert
static int lua_ImageColorInvert(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }

    ImageColorInvert(image);

    return 0;
}

// Modify image color: grayscale
static int lua_ImageColorGrayscale(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }

    ImageColorGrayscale(image);

    return 0;
}

// Modify image color: contrast (-100 to 100)
static int lua_ImageColorContrast(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    float contrast = luaL_checknumber(L, 2);

    ImageColorContrast(image, contrast);

    return 0;
}

// Modify image color: brightness (-255 to 255)
static int lua_ImageColorBrightness(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    int brightness = luaL_checkinteger(L, 2);

    ImageColorBrightness(image, brightness);

    return 0;
}

// Modify image color: replace color
static int lua_ImageColorReplace(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int image_count = lua_rawlen(L, 1);
    Image* image = (Image*)malloc(image_count * sizeof(Image));
    for (int i = 0; i < image_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        image[i] = *img;
        lua_pop(L, 1);
    }
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color replace = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageColorReplace(image, color, replace);

    return 0;
}

// Unload color data loaded with LoadImageColors()
static int lua_UnloadImageColors(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int colors_count = lua_rawlen(L, 1);
    Color* colors = (Color*)malloc(colors_count * sizeof(Color));
    for (int i = 0; i < colors_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        lua_getfield(L, -1, "r");
        lua_getfield(L, -2, "g");
        lua_getfield(L, -3, "b");
        lua_getfield(L, -4, "a");
        colors[i].r = luaL_checkinteger(L, -4);
        colors[i].g = luaL_checkinteger(L, -3);
        colors[i].b = luaL_checkinteger(L, -2);
        colors[i].a = luaL_checkinteger(L, -1);
        lua_pop(L, 5);
    }

    UnloadImageColors(colors);

    free(colors);
    return 0;
}

// Unload colors palette loaded with LoadImagePalette()
static int lua_UnloadImagePalette(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int colors_count = lua_rawlen(L, 1);
    Color* colors = (Color*)malloc(colors_count * sizeof(Color));
    for (int i = 0; i < colors_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        lua_getfield(L, -1, "r");
        lua_getfield(L, -2, "g");
        lua_getfield(L, -3, "b");
        lua_getfield(L, -4, "a");
        colors[i].r = luaL_checkinteger(L, -4);
        colors[i].g = luaL_checkinteger(L, -3);
        colors[i].b = luaL_checkinteger(L, -2);
        colors[i].a = luaL_checkinteger(L, -1);
        lua_pop(L, 5);
    }

    UnloadImagePalette(colors);

    free(colors);
    return 0;
}

// Get image alpha border rectangle
static int lua_GetImageAlphaBorder(lua_State* L) {
    Image* image = (Image*)luaL_checkudata(L, 1, "Image");
    float threshold = luaL_checknumber(L, 2);

    Rectangle result = GetImageAlphaBorder(*image, threshold);

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

// Get image pixel color at (x, y) position
static int lua_GetImageColor(lua_State* L) {
    Image* image = (Image*)luaL_checkudata(L, 1, "Image");
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);

    Color result = GetImageColor(*image, x, y);

    lua_newtable(L);
    lua_pushinteger(L, result.r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, result.g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, result.b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, result.a);
    lua_setfield(L, -2, "a");
    return 1;
}

// Clear image background with given color
static int lua_ImageClearBackground(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageClearBackground(dst, color);

    return 0;
}

// Draw pixel within an image
static int lua_ImageDrawPixel(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    int posX = luaL_checkinteger(L, 2);
    int posY = luaL_checkinteger(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawPixel(dst, posX, posY, color);

    return 0;
}

// Draw pixel within an image (Vector version)
static int lua_ImageDrawPixelV(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 position = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawPixelV(dst, position, color);

    return 0;
}

// Draw line within an image
static int lua_ImageDrawLine(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    int startPosX = luaL_checkinteger(L, 2);
    int startPosY = luaL_checkinteger(L, 3);
    int endPosX = luaL_checkinteger(L, 4);
    int endPosY = luaL_checkinteger(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawLine(dst, startPosX, startPosY, endPosX, endPosY, color);

    return 0;
}

// Draw line within an image (Vector version)
static int lua_ImageDrawLineV(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 start = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 end = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawLineV(dst, start, end, color);

    return 0;
}

// Draw a filled circle within an image
static int lua_ImageDrawCircle(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    int centerX = luaL_checkinteger(L, 2);
    int centerY = luaL_checkinteger(L, 3);
    int radius = luaL_checkinteger(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawCircle(dst, centerX, centerY, radius, color);

    return 0;
}

// Draw a filled circle within an image (Vector version)
static int lua_ImageDrawCircleV(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 center = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    int radius = luaL_checkinteger(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawCircleV(dst, center, radius, color);

    return 0;
}

// Draw circle outline within an image
static int lua_ImageDrawCircleLines(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    int centerX = luaL_checkinteger(L, 2);
    int centerY = luaL_checkinteger(L, 3);
    int radius = luaL_checkinteger(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawCircleLines(dst, centerX, centerY, radius, color);

    return 0;
}

// Draw circle outline within an image (Vector version)
static int lua_ImageDrawCircleLinesV(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 center = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    int radius = luaL_checkinteger(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawCircleLinesV(dst, center, radius, color);

    return 0;
}

// Draw rectangle within an image
static int lua_ImageDrawRectangle(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    int posX = luaL_checkinteger(L, 2);
    int posY = luaL_checkinteger(L, 3);
    int width = luaL_checkinteger(L, 4);
    int height = luaL_checkinteger(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawRectangle(dst, posX, posY, width, height, color);

    return 0;
}

// Draw rectangle within an image (Vector version)
static int lua_ImageDrawRectangleV(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 position = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 size = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawRectangleV(dst, position, size, color);

    return 0;
}

// Draw rectangle within an image
static int lua_ImageDrawRectangleRec(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "width");
    lua_getfield(L, 2, "height");
    Rectangle rec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawRectangleRec(dst, rec, color);

    return 0;
}

// Draw rectangle lines within an image
static int lua_ImageDrawRectangleLines(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "width");
    lua_getfield(L, 2, "height");
    Rectangle rec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    int thick = luaL_checkinteger(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawRectangleLines(dst, rec, thick, color);

    return 0;
}

// Draw a source image within a destination image (tint applied to source)
static int lua_ImageDraw(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    Image* src = (Image*)luaL_checkudata(L, 2, "Image");
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "width");
    lua_getfield(L, 3, "height");
    Rectangle srcRec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    lua_getfield(L, 4, "width");
    lua_getfield(L, 4, "height");
    Rectangle dstRec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDraw(dst, *src, srcRec, dstRec, tint);

    return 0;
}

// Draw text (using default font) within an image (destination)
static int lua_ImageDrawText(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    const char * text = luaL_checkstring(L, 2);
    int posX = luaL_checkinteger(L, 3);
    int posY = luaL_checkinteger(L, 4);
    int fontSize = luaL_checkinteger(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawText(dst, text, posX, posY, fontSize, color);

    return 0;
}

// Draw text (custom sprite font) within an image (destination)
static int lua_ImageDrawTextEx(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int dst_count = lua_rawlen(L, 1);
    Image* dst = (Image*)malloc(dst_count * sizeof(Image));
    for (int i = 0; i < dst_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        dst[i] = *img;
        lua_pop(L, 1);
    }
    Font* font = (Font*)luaL_checkudata(L, 2, "Font");
    const char * text = luaL_checkstring(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    Vector2 position = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float fontSize = luaL_checknumber(L, 5);
    float spacing = luaL_checknumber(L, 6);
    luaL_checktype(L, 7, LUA_TTABLE);
    lua_getfield(L, 7, "r");
    lua_getfield(L, 7, "g");
    lua_getfield(L, 7, "b");
    lua_getfield(L, 7, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ImageDrawTextEx(dst, *font, text, position, fontSize, spacing, tint);

    return 0;
}

// Load texture from file into GPU memory (VRAM)
static int lua_LoadTexture(lua_State* L) {
    const char * fileName = luaL_checkstring(L, 1);

    Texture2D result = LoadTexture(fileName);

    Texture2D* result_ptr = (Texture2D*)lua_newuserdata(L, sizeof(Texture2D));
    *result_ptr = result;
    luaL_getmetatable(L, "Texture2D");
    lua_setmetatable(L, -2);
    return 1;
}

static int l_LoadTexture(lua_State* L) {
    const char* filename = luaL_checkstring(L, 1);

    Texture2D* tex = (Texture2D*)lua_newuserdata(L, sizeof(Texture2D));
    *tex = LoadTexture(filename);

    luaL_getmetatable(L, "Texture2D");
    lua_setmetatable(L, -2);

    return 1;
}


// Load texture from image data
static int lua_LoadTextureFromImage(lua_State* L) {
    Image* image = (Image*)luaL_checkudata(L, 1, "Image");

    Texture2D result = LoadTextureFromImage(*image);

    Texture2D* result_ptr = (Texture2D*)lua_newuserdata(L, sizeof(Texture2D));
    *result_ptr = result;
    luaL_getmetatable(L, "Texture2D");
    lua_setmetatable(L, -2);
    return 1;
}

// Load cubemap from image, multiple image cubemap layouts supported
static int lua_LoadTextureCubemap(lua_State* L) {
    Image* image = (Image*)luaL_checkudata(L, 1, "Image");
    int layout = luaL_checkinteger(L, 2);

    TextureCubemap result = LoadTextureCubemap(*image, layout);

    // TODO: Handle return type TextureCubemap
    return 1;
}

// Load texture for rendering (framebuffer)
static int lua_LoadRenderTexture(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);

    RenderTexture2D result = LoadRenderTexture(width, height);

    RenderTexture2D* result_ptr = (RenderTexture2D*)lua_newuserdata(L, sizeof(RenderTexture2D));
    *result_ptr = result;
    luaL_getmetatable(L, "RenderTexture2D");
    lua_setmetatable(L, -2);
    return 1;
}

// Check if a texture is ready - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_IsTextureReady(lua_State* L) {
//     Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
// 
//     bool result = IsTextureReady(*texture);
// 
//     lua_pushboolean(L, result);
//     return 1;
// }

// Unload texture from GPU memory (VRAM)
static int lua_UnloadTexture(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");

    UnloadTexture(*texture);

    return 0;
}

// Unload render texture from GPU memory (VRAM)
static int lua_UnloadRenderTexture(lua_State* L) {
    RenderTexture2D* target = (RenderTexture2D*)luaL_checkudata(L, 1, "RenderTexture2D");

    UnloadRenderTexture(*target);

    return 0;
}

// Generate GPU mipmaps for a texture
static int lua_GenTextureMipmaps(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");

    GenTextureMipmaps(texture);

    return 0;
}

// Draw a Texture2D
static int lua_DrawTexture(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    int posX = luaL_checkinteger(L, 2);
    int posY = luaL_checkinteger(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTexture(*texture, posX, posY, tint);

    return 0;
}

// Draw a Texture2D with position defined as Vector2
static int lua_DrawTextureV(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 position = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTextureV(*texture, position, tint);

    return 0;
}

// Draw a Texture2D with extended parameters
static int lua_DrawTextureEx(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 position = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float rotation = luaL_checknumber(L, 3);
    float scale = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTextureEx(*texture, position, rotation, scale, tint);

    return 0;
}

// Draw a part of a texture defined by a rectangle
static int lua_DrawTextureRec(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "width");
    lua_getfield(L, 2, "height");
    Rectangle source = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 position = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTextureRec(*texture, source, position, tint);

    return 0;
}

// Draw a part of a texture defined by a rectangle with 'pro' parameters
static int lua_DrawTexturePro(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "width");
    lua_getfield(L, 2, "height");
    Rectangle source = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "width");
    lua_getfield(L, 3, "height");
    Rectangle dest = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    Vector2 origin = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float rotation = luaL_checknumber(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTexturePro(*texture, source, dest, origin, rotation, tint);

    return 0;
}

// Draws a texture (or part of it) that stretches or shrinks nicely
static int lua_DrawTextureNPatch(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "source");
    luaL_checktype(L, -1, LUA_TTABLE);
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "width");
    lua_getfield(L, -4, "height");
    Rectangle source = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 5);
    lua_getfield(L, 2, "left");
    lua_getfield(L, 2, "top");
    lua_getfield(L, 2, "right");
    lua_getfield(L, 2, "bottom");
    lua_getfield(L, 2, "layout");
    NPatchInfo nPatchInfo = {source, luaL_checkinteger(L, -5), luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 5);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "width");
    lua_getfield(L, 3, "height");
    Rectangle dest = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    Vector2 origin = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float rotation = luaL_checknumber(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTextureNPatch(*texture, nPatchInfo, dest, origin, rotation, tint);

    return 0;
}

// Get color with alpha applied, alpha goes from 0.0f to 1.0f
static int lua_Fade(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "r");
    lua_getfield(L, 1, "g");
    lua_getfield(L, 1, "b");
    lua_getfield(L, 1, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    float alpha = luaL_checknumber(L, 2);

    Color result = Fade(color, alpha);

    lua_newtable(L);
    lua_pushinteger(L, result.r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, result.g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, result.b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, result.a);
    lua_setfield(L, -2, "a");
    return 1;
}

// Get Color normalized as float [0..1]
static int lua_ColorNormalize(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "r");
    lua_getfield(L, 1, "g");
    lua_getfield(L, 1, "b");
    lua_getfield(L, 1, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    Vector4 result = ColorNormalize(color);

    // Push Vector4 as table
    lua_createtable(L, 0, 4);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, result.z);
    lua_setfield(L, -2, "z");
    lua_pushnumber(L, result.w);
    lua_setfield(L, -2, "w");
    
    return 1;
}

// Get Color from normalized values [0..1]
static int lua_ColorFromNormalized(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    lua_getfield(L, 1, "w");
    Vector4 normalized = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);

    Color result = ColorFromNormalized(normalized);

    lua_newtable(L);
    lua_pushinteger(L, result.r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, result.g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, result.b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, result.a);
    lua_setfield(L, -2, "a");
    return 1;
}

// Get HSV values for a Color, hue [0..360], saturation/value [0..1]
static int lua_ColorToHSV(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "r");
    lua_getfield(L, 1, "g");
    lua_getfield(L, 1, "b");
    lua_getfield(L, 1, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    Vector3 result = ColorToHSV(color);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, result.z);
    lua_setfield(L, -2, "z");
    return 1;
}

// Get a Color from HSV values, hue [0..360], saturation/value [0..1]
static int lua_ColorFromHSV(lua_State* L) {
    float hue = luaL_checknumber(L, 1);
    float saturation = luaL_checknumber(L, 2);
    float value = luaL_checknumber(L, 3);

    Color result = ColorFromHSV(hue, saturation, value);

    lua_newtable(L);
    lua_pushinteger(L, result.r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, result.g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, result.b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, result.a);
    lua_setfield(L, -2, "a");
    return 1;
}

// Get color multiplied with another color
static int lua_ColorTint(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "r");
    lua_getfield(L, 1, "g");
    lua_getfield(L, 1, "b");
    lua_getfield(L, 1, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    Color result = ColorTint(color, tint);

    lua_newtable(L);
    lua_pushinteger(L, result.r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, result.g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, result.b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, result.a);
    lua_setfield(L, -2, "a");
    return 1;
}

// Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
static int lua_ColorBrightness(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "r");
    lua_getfield(L, 1, "g");
    lua_getfield(L, 1, "b");
    lua_getfield(L, 1, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    float factor = luaL_checknumber(L, 2);

    Color result = ColorBrightness(color, factor);

    lua_newtable(L);
    lua_pushinteger(L, result.r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, result.g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, result.b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, result.a);
    lua_setfield(L, -2, "a");
    return 1;
}

// Get color with contrast correction, contrast values between -1.0f and 1.0f
static int lua_ColorContrast(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "r");
    lua_getfield(L, 1, "g");
    lua_getfield(L, 1, "b");
    lua_getfield(L, 1, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    float contrast = luaL_checknumber(L, 2);

    Color result = ColorContrast(color, contrast);

    lua_newtable(L);
    lua_pushinteger(L, result.r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, result.g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, result.b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, result.a);
    lua_setfield(L, -2, "a");
    return 1;
}

// Get color with alpha applied, alpha goes from 0.0f to 1.0f
static int lua_ColorAlpha(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "r");
    lua_getfield(L, 1, "g");
    lua_getfield(L, 1, "b");
    lua_getfield(L, 1, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    float alpha = luaL_checknumber(L, 2);

    Color result = ColorAlpha(color, alpha);

    lua_newtable(L);
    lua_pushinteger(L, result.r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, result.g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, result.b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, result.a);
    lua_setfield(L, -2, "a");
    return 1;
}

// Get src alpha-blended into dst color with tint
static int lua_ColorAlphaBlend(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "r");
    lua_getfield(L, 1, "g");
    lua_getfield(L, 1, "b");
    lua_getfield(L, 1, "a");
    Color dst = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color src = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    Color result = ColorAlphaBlend(dst, src, tint);

    lua_newtable(L);
    lua_pushinteger(L, result.r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, result.g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, result.b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, result.a);
    lua_setfield(L, -2, "a");
    return 1;
}

// Get Color structure from hexadecimal value
static int lua_GetColor(lua_State* L) {
    unsigned int hexValue = luaL_checkinteger(L, 1);

    Color result = GetColor(hexValue);

    lua_newtable(L);
    lua_pushinteger(L, result.r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, result.g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, result.b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, result.a);
    lua_setfield(L, -2, "a");
    return 1;
}

// Get Color from a source pixel pointer of certain format
static int lua_GetPixelColor(lua_State* L) {
    size_t srcLength;
    const char* srcData = luaL_checklstring(L, 1, &srcLength);
    void* srcPtr = (void*)srcData;
    int format = luaL_checkinteger(L, 2);

    Color result = GetPixelColor(srcPtr, format);

    lua_newtable(L);
    lua_pushinteger(L, result.r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, result.g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, result.b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, result.a);
    lua_setfield(L, -2, "a");
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

static int RenderTexture2D_gc(lua_State* L) {
    RenderTexture2D* obj = (RenderTexture2D*)luaL_checkudata(L, 1, "RenderTexture2D");
    if (obj != NULL) {
        UnloadRenderTexture(*obj);
    }
    return 0;
}

static void create_RenderTexture2D_metatable(lua_State* L) {
    luaL_newmetatable(L, "RenderTexture2D");
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, RenderTexture2D_gc);
    lua_settable(L, -3);
    lua_pop(L, 1);  // Remove metatable from stack
}

static int Texture2D_gc(lua_State* L) {
    Texture2D* obj = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    if (obj != NULL) {
        UnloadTexture(*obj);
    }
    return 0;
}

// Allow access to Texture2D fields
static int Texture2D_index(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    const char* key = luaL_checkstring(L, 2);
    
    if (strcmp(key, "width") == 0) {
        lua_pushinteger(L, texture->width);
        return 1;
    } else if (strcmp(key, "height") == 0) {
        lua_pushinteger(L, texture->height);
        return 1;
    } else if (strcmp(key, "id") == 0) {
        lua_pushinteger(L, texture->id);
        return 1;
    } else if (strcmp(key, "format") == 0) {
        lua_pushinteger(L, texture->format);
        return 1;
    } else if (strcmp(key, "mipmaps") == 0) {
        lua_pushinteger(L, texture->mipmaps);
        return 1;
    }
    printf("Texture2D_index called for key: %s\n", key);
    
    return 0;  // Return nil for unknown fields
}

static void create_Texture2D_metatable(lua_State* L) {
    luaL_newmetatable(L, "Texture2D");
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, Texture2D_gc);
    lua_settable(L, -3);
    lua_pushstring(L, "__index");
    lua_pushcfunction(L, Texture2D_index);
    lua_settable(L, -3);
    lua_pop(L, 1);  // Remove metatable from stack
}

static const struct luaL_Reg rtextures_functions[] = {
    {"LoadImage", lua_LoadImage},
    {"LoadImageRaw", lua_LoadImageRaw},
    {"LoadImageAnim", lua_LoadImageAnim},
    {"LoadImageFromMemory", lua_LoadImageFromMemory},
    {"LoadImageFromTexture", lua_LoadImageFromTexture},
    {"LoadImageFromScreen", lua_LoadImageFromScreen},
    {"UnloadImage", lua_UnloadImage},
    {"ExportImage", lua_ExportImage},
    {"ExportImageAsCode", lua_ExportImageAsCode},
    {"GenImageColor", lua_GenImageColor},
    {"GenImageGradientLinear", lua_GenImageGradientLinear},
    {"GenImageGradientRadial", lua_GenImageGradientRadial},
    {"GenImageGradientSquare", lua_GenImageGradientSquare},
    {"GenImageChecked", lua_GenImageChecked},
    {"GenImageWhiteNoise", lua_GenImageWhiteNoise},
    {"GenImagePerlinNoise", lua_GenImagePerlinNoise},
    {"GenImageCellular", lua_GenImageCellular},
    {"GenImageText", lua_GenImageText},
    {"ImageCopy", lua_ImageCopy},
    {"ImageFromImage", lua_ImageFromImage},
    {"ImageText", lua_ImageText},
    {"ImageTextEx", lua_ImageTextEx},
    {"ImageFormat", lua_ImageFormat},
    {"ImageToPOT", lua_ImageToPOT},
    {"ImageCrop", lua_ImageCrop},
    {"ImageAlphaCrop", lua_ImageAlphaCrop},
    {"ImageAlphaClear", lua_ImageAlphaClear},
    {"ImageAlphaMask", lua_ImageAlphaMask},
    {"ImageAlphaPremultiply", lua_ImageAlphaPremultiply},
    {"ImageBlurGaussian", lua_ImageBlurGaussian},
    {"ImageResize", lua_ImageResize},
    {"ImageResizeNN", lua_ImageResizeNN},
    {"ImageResizeCanvas", lua_ImageResizeCanvas},
    {"ImageMipmaps", lua_ImageMipmaps},
    {"ImageDither", lua_ImageDither},
    {"ImageFlipVertical", lua_ImageFlipVertical},
    {"ImageFlipHorizontal", lua_ImageFlipHorizontal},
    {"ImageRotate", lua_ImageRotate},
    {"ImageRotateCW", lua_ImageRotateCW},
    {"ImageRotateCCW", lua_ImageRotateCCW},
    {"ImageColorTint", lua_ImageColorTint},
    {"ImageColorInvert", lua_ImageColorInvert},
    {"ImageColorGrayscale", lua_ImageColorGrayscale},
    {"ImageColorContrast", lua_ImageColorContrast},
    {"ImageColorBrightness", lua_ImageColorBrightness},
    {"ImageColorReplace", lua_ImageColorReplace},
    {"UnloadImageColors", lua_UnloadImageColors},
    {"UnloadImagePalette", lua_UnloadImagePalette},
    {"GetImageAlphaBorder", lua_GetImageAlphaBorder},
    {"GetImageColor", lua_GetImageColor},
    {"ImageClearBackground", lua_ImageClearBackground},
    {"ImageDrawPixel", lua_ImageDrawPixel},
    {"ImageDrawPixelV", lua_ImageDrawPixelV},
    {"ImageDrawLine", lua_ImageDrawLine},
    {"ImageDrawLineV", lua_ImageDrawLineV},
    {"ImageDrawCircle", lua_ImageDrawCircle},
    {"ImageDrawCircleV", lua_ImageDrawCircleV},
    {"ImageDrawCircleLines", lua_ImageDrawCircleLines},
    {"ImageDrawCircleLinesV", lua_ImageDrawCircleLinesV},
    {"ImageDrawRectangle", lua_ImageDrawRectangle},
    {"ImageDrawRectangleV", lua_ImageDrawRectangleV},
    {"ImageDrawRectangleRec", lua_ImageDrawRectangleRec},
    {"ImageDrawRectangleLines", lua_ImageDrawRectangleLines},
    {"ImageDraw", lua_ImageDraw},
    {"ImageDrawText", lua_ImageDrawText},
    {"ImageDrawTextEx", lua_ImageDrawTextEx},
    {"LoadTexture", lua_LoadTexture},
    {"LoadTextureFromImage", lua_LoadTextureFromImage},
    {"LoadTextureCubemap", lua_LoadTextureCubemap},
    {"LoadRenderTexture", lua_LoadRenderTexture},
    {"UnloadTexture", lua_UnloadTexture},
    {"UnloadRenderTexture", lua_UnloadRenderTexture},
    {"GenTextureMipmaps", lua_GenTextureMipmaps},
    {"DrawTexture", lua_DrawTexture},
    {"DrawTextureV", lua_DrawTextureV},
    {"DrawTextureEx", lua_DrawTextureEx},
    {"DrawTextureRec", lua_DrawTextureRec},
    {"DrawTexturePro", lua_DrawTexturePro},
    {"DrawTextureNPatch", lua_DrawTextureNPatch},
    {"Fade", lua_Fade},
    {"ColorNormalize", lua_ColorNormalize},
    {"ColorFromNormalized", lua_ColorFromNormalized},
    {"ColorToHSV", lua_ColorToHSV},
    {"ColorFromHSV", lua_ColorFromHSV},
    {"ColorTint", lua_ColorTint},
    {"ColorBrightness", lua_ColorBrightness},
    {"ColorContrast", lua_ColorContrast},
    {"ColorAlpha", lua_ColorAlpha},
    {"ColorAlphaBlend", lua_ColorAlphaBlend},
    {"GetColor", lua_GetColor},
    {"GetPixelColor", lua_GetPixelColor},
    {NULL, NULL}
};

int luaopen_rtextures(lua_State* L) {
    create_Image_metatable(L);
    create_RenderTexture2D_metatable(L);
    create_Texture2D_metatable(L);
    luaL_register(L, "rtextures", rtextures_functions);
    return 1;
}
