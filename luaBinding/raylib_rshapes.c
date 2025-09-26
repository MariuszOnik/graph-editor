// Auto-generated Raylib Lua bindings - Module: rshapes
// Based on real raylib source: rshapes.c
// Basic shapes drawing and collision detection
// Functions: 58

#include "raylib.h"
#include "lua.h"
#include "lauxlib.h"
#include <stdlib.h>

// Compatibility wrapper for lua_rawlen (not available in Lua 5.1)
#ifndef lua_rawlen
#define lua_rawlen(L, idx) lua_objlen(L, idx)
#endif

// Draw a pixel
static int lua_DrawPixel(lua_State* L) {
    int posX = luaL_checkinteger(L, 1);
    int posY = luaL_checkinteger(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawPixel(posX, posY, color);

    return 0;
}

// Draw a pixel (Vector version)
static int lua_DrawPixelV(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 position = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawPixelV(position, color);

    return 0;
}

// Draw a line
static int lua_DrawLine(lua_State* L) {
    int startPosX = luaL_checkinteger(L, 1);
    int startPosY = luaL_checkinteger(L, 2);
    int endPosX = luaL_checkinteger(L, 3);
    int endPosY = luaL_checkinteger(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawLine(startPosX, startPosY, endPosX, endPosY, color);

    return 0;
}

// Draw a line (using gl lines)
static int lua_DrawLineV(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 startPos = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 endPos = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawLineV(startPos, endPos, color);

    return 0;
}

// Draw a line (using triangles/quads)
static int lua_DrawLineEx(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 startPos = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 endPos = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float thick = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawLineEx(startPos, endPos, thick, color);

    return 0;
}

// Draw lines sequence (using gl lines)
static int lua_DrawLineStrip(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int points_count = lua_rawlen(L, 1);
    Vector2* points = (Vector2*)malloc(points_count * sizeof(Vector2));
    for (int i = 0; i < points_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        lua_getfield(L, -1, "x");
        lua_getfield(L, -2, "y");
        points[i].x = luaL_checknumber(L, -2);
        points[i].y = luaL_checknumber(L, -1);
        lua_pop(L, 3);
    }
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawLineStrip(points, points_count, color);

    free(points);
    return 0;
}

// Draw line segment cubic-bezier in-out interpolation
static int lua_DrawLineBezier(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 startPos = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 endPos = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float thick = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawLineBezier(startPos, endPos, thick, color);

    return 0;
}

// Draw a color-filled circle
static int lua_DrawCircle(lua_State* L) {
    int centerX = luaL_checkinteger(L, 1);
    int centerY = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCircle(centerX, centerY, radius, color);

    return 0;
}

// Draw a piece of a circle
static int lua_DrawCircleSector(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 center = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float radius = luaL_checknumber(L, 2);
    float startAngle = luaL_checknumber(L, 3);
    float endAngle = luaL_checknumber(L, 4);
    int segments = luaL_checkinteger(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCircleSector(center, radius, startAngle, endAngle, segments, color);

    return 0;
}

// Draw circle sector outline
static int lua_DrawCircleSectorLines(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 center = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float radius = luaL_checknumber(L, 2);
    float startAngle = luaL_checknumber(L, 3);
    float endAngle = luaL_checknumber(L, 4);
    int segments = luaL_checkinteger(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);

    return 0;
}

// Draw a gradient-filled circle
static int lua_DrawCircleGradient(lua_State* L) {
    int centerX = luaL_checkinteger(L, 1);
    int centerY = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color1 = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color2 = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCircleGradient(centerX, centerY, radius, color1, color2);

    return 0;
}

// Draw a color-filled circle (Vector version)
static int lua_DrawCircleV(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 center = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float radius = luaL_checknumber(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCircleV(center, radius, color);

    return 0;
}

// Draw circle outline
static int lua_DrawCircleLines(lua_State* L) {
    int centerX = luaL_checkinteger(L, 1);
    int centerY = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCircleLines(centerX, centerY, radius, color);

    return 0;
}

// Draw circle outline (Vector version)
static int lua_DrawCircleLinesV(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 center = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float radius = luaL_checknumber(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCircleLinesV(center, radius, color);

    return 0;
}

// Draw ellipse
static int lua_DrawEllipse(lua_State* L) {
    int centerX = luaL_checkinteger(L, 1);
    int centerY = luaL_checkinteger(L, 2);
    float radiusH = luaL_checknumber(L, 3);
    float radiusV = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawEllipse(centerX, centerY, radiusH, radiusV, color);

    return 0;
}

// Draw ellipse outline
static int lua_DrawEllipseLines(lua_State* L) {
    int centerX = luaL_checkinteger(L, 1);
    int centerY = luaL_checkinteger(L, 2);
    float radiusH = luaL_checknumber(L, 3);
    float radiusV = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawEllipseLines(centerX, centerY, radiusH, radiusV, color);

    return 0;
}

// Draw ring
static int lua_DrawRing(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 center = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float innerRadius = luaL_checknumber(L, 2);
    float outerRadius = luaL_checknumber(L, 3);
    float startAngle = luaL_checknumber(L, 4);
    float endAngle = luaL_checknumber(L, 5);
    int segments = luaL_checkinteger(L, 6);
    luaL_checktype(L, 7, LUA_TTABLE);
    lua_getfield(L, 7, "r");
    lua_getfield(L, 7, "g");
    lua_getfield(L, 7, "b");
    lua_getfield(L, 7, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);

    return 0;
}

// Draw ring outline
static int lua_DrawRingLines(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 center = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float innerRadius = luaL_checknumber(L, 2);
    float outerRadius = luaL_checknumber(L, 3);
    float startAngle = luaL_checknumber(L, 4);
    float endAngle = luaL_checknumber(L, 5);
    int segments = luaL_checkinteger(L, 6);
    luaL_checktype(L, 7, LUA_TTABLE);
    lua_getfield(L, 7, "r");
    lua_getfield(L, 7, "g");
    lua_getfield(L, 7, "b");
    lua_getfield(L, 7, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);

    return 0;
}

// Draw a color-filled rectangle
static int lua_DrawRectangle(lua_State* L) {
    int posX = luaL_checkinteger(L, 1);
    int posY = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawRectangle(posX, posY, width, height, color);

    return 0;
}

// Draw a color-filled rectangle (Vector version)
static int lua_DrawRectangleV(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 position = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 size = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawRectangleV(position, size, color);

    return 0;
}

// Draw a color-filled rectangle
static int lua_DrawRectangleRec(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "width");
    lua_getfield(L, 1, "height");
    Rectangle rec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawRectangleRec(rec, color);

    return 0;
}

// Draw a color-filled rectangle with pro parameters
static int lua_DrawRectanglePro(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "width");
    lua_getfield(L, 1, "height");
    Rectangle rec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 origin = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float rotation = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawRectanglePro(rec, origin, rotation, color);

    return 0;
}

// Draw a vertical-gradient-filled rectangle
static int lua_DrawRectangleGradientV(lua_State* L) {
    int posX = luaL_checkinteger(L, 1);
    int posY = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color1 = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color2 = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawRectangleGradientV(posX, posY, width, height, color1, color2);

    return 0;
}

// Draw a horizontal-gradient-filled rectangle
static int lua_DrawRectangleGradientH(lua_State* L) {
    int posX = luaL_checkinteger(L, 1);
    int posY = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color1 = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color2 = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawRectangleGradientH(posX, posY, width, height, color1, color2);

    return 0;
}

// Draw a gradient-filled rectangle with custom vertex colors
static int lua_DrawRectangleGradientEx(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "width");
    lua_getfield(L, 1, "height");
    Rectangle rec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color col1 = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color col2 = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color col3 = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color col4 = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawRectangleGradientEx(rec, col1, col2, col3, col4);

    return 0;
}

// Draw rectangle outline
static int lua_DrawRectangleLines(lua_State* L) {
    int posX = luaL_checkinteger(L, 1);
    int posY = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawRectangleLines(posX, posY, width, height, color);

    return 0;
}

// Draw rectangle outline with extended parameters
static int lua_DrawRectangleLinesEx(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "width");
    lua_getfield(L, 1, "height");
    Rectangle rec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    float lineThick = luaL_checknumber(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawRectangleLinesEx(rec, lineThick, color);

    return 0;
}

// Draw rectangle with rounded edges
static int lua_DrawRectangleRounded(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "width");
    lua_getfield(L, 1, "height");
    Rectangle rec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    float roundness = luaL_checknumber(L, 2);
    int segments = luaL_checkinteger(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawRectangleRounded(rec, roundness, segments, color);

    return 0;
}

// Draw rectangle with rounded edges outline
static int lua_DrawRectangleRoundedLines(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "width");
    lua_getfield(L, 1, "height");
    Rectangle rec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    float roundness = luaL_checknumber(L, 2);
    int segments = luaL_checkinteger(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawRectangleRoundedLines(rec, roundness, segments, color);

    return 0;
}

// Draw a color-filled triangle (vertex in counter-clockwise order!)
static int lua_DrawTriangle(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 v1 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 v2 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 v3 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTriangle(v1, v2, v3, color);

    return 0;
}

// Draw triangle outline (vertex in counter-clockwise order!)
static int lua_DrawTriangleLines(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 v1 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 v2 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 v3 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTriangleLines(v1, v2, v3, color);

    return 0;
}

// Draw a triangle fan defined by points (first vertex is the center)
static int lua_DrawTriangleFan(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int points_count = lua_rawlen(L, 1);
    Vector2* points = (Vector2*)malloc(points_count * sizeof(Vector2));
    for (int i = 0; i < points_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        lua_getfield(L, -1, "x");
        lua_getfield(L, -2, "y");
        points[i].x = luaL_checknumber(L, -2);
        points[i].y = luaL_checknumber(L, -1);
        lua_pop(L, 3);
    }
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTriangleFan(points, points_count, color);

    free(points);
    return 0;
}

// Draw a triangle strip defined by points
static int lua_DrawTriangleStrip(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int points_count = lua_rawlen(L, 1);
    Vector2* points = (Vector2*)malloc(points_count * sizeof(Vector2));
    for (int i = 0; i < points_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        lua_getfield(L, -1, "x");
        lua_getfield(L, -2, "y");
        points[i].x = luaL_checknumber(L, -2);
        points[i].y = luaL_checknumber(L, -1);
        lua_pop(L, 3);
    }
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTriangleStrip(points, points_count, color);

    free(points);
    return 0;
}

// Draw a regular polygon (Vector version)
static int lua_DrawPoly(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 center = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    int sides = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    float rotation = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawPoly(center, sides, radius, rotation, color);

    return 0;
}

// Draw a polygon outline of n sides
static int lua_DrawPolyLines(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 center = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    int sides = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    float rotation = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawPolyLines(center, sides, radius, rotation, color);

    return 0;
}

// Draw a polygon outline of n sides with extended parameters
static int lua_DrawPolyLinesEx(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 center = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    int sides = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    float rotation = luaL_checknumber(L, 4);
    float lineThick = luaL_checknumber(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawPolyLinesEx(center, sides, radius, rotation, lineThick, color);

    return 0;
}

// Get (evaluate) spline point: Linear
static int lua_GetSplinePointLinear(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 startPos = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 endPos = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float t = luaL_checknumber(L, 3);

    Vector2 result = GetSplinePointLinear(startPos, endPos, t);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Get (evaluate) spline point: B-Spline
static int lua_GetSplinePointBasis(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 p1 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 p2 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 p3 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    Vector2 p4 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float t = luaL_checknumber(L, 5);

    Vector2 result = GetSplinePointBasis(p1, p2, p3, p4, t);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Get (evaluate) spline point: Catmull-Rom
static int lua_GetSplinePointCatmullRom(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 p1 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 p2 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 p3 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    Vector2 p4 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float t = luaL_checknumber(L, 5);

    Vector2 result = GetSplinePointCatmullRom(p1, p2, p3, p4, t);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Get (evaluate) spline point: Quadratic Bezier
static int lua_GetSplinePointBezierQuad(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 p1 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 c2 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 p3 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float t = luaL_checknumber(L, 4);

    Vector2 result = GetSplinePointBezierQuad(p1, c2, p3, t);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Get (evaluate) spline point: Cubic Bezier
static int lua_GetSplinePointBezierCubic(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 p1 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 c2 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 c3 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    Vector2 p4 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float t = luaL_checknumber(L, 5);

    Vector2 result = GetSplinePointBezierCubic(p1, c2, c3, p4, t);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Check collision between two rectangles
static int lua_CheckCollisionRecs(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "width");
    lua_getfield(L, 1, "height");
    Rectangle rec1 = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "width");
    lua_getfield(L, 2, "height");
    Rectangle rec2 = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);

    bool result = CheckCollisionRecs(rec1, rec2);

    lua_pushboolean(L, result);
    return 1;
}

// Check collision between two circles
static int lua_CheckCollisionCircles(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 center1 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float radius1 = luaL_checknumber(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 center2 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float radius2 = luaL_checknumber(L, 4);

    bool result = CheckCollisionCircles(center1, radius1, center2, radius2);

    lua_pushboolean(L, result);
    return 1;
}

// Check collision between circle and rectangle
static int lua_CheckCollisionCircleRec(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 center = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float radius = luaL_checknumber(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "width");
    lua_getfield(L, 3, "height");
    Rectangle rec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);

    bool result = CheckCollisionCircleRec(center, radius, rec);

    lua_pushboolean(L, result);
    return 1;
}

// Check if point is inside rectangle
static int lua_CheckCollisionPointRec(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 point = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "width");
    lua_getfield(L, 2, "height");
    Rectangle rec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);

    bool result = CheckCollisionPointRec(point, rec);

    lua_pushboolean(L, result);
    return 1;
}

// Check if point is inside circle
static int lua_CheckCollisionPointCircle(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 point = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 center = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float radius = luaL_checknumber(L, 3);

    bool result = CheckCollisionPointCircle(point, center, radius);

    lua_pushboolean(L, result);
    return 1;
}

// Check if point is inside a triangle
static int lua_CheckCollisionPointTriangle(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 point = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 p1 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 p2 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    Vector2 p3 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);

    bool result = CheckCollisionPointTriangle(point, p1, p2, p3);

    lua_pushboolean(L, result);
    return 1;
}

// Check if point is within a polygon described by array of vertices
static int lua_CheckCollisionPointPoly(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 point = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    int points_count = lua_rawlen(L, 2);
    Vector2* points = (Vector2*)malloc(points_count * sizeof(Vector2));
    for (int i = 0; i < points_count; i++) {
        lua_rawgeti(L, 2, i + 1);
        lua_getfield(L, -1, "x");
        lua_getfield(L, -2, "y");
        points[i].x = luaL_checknumber(L, -2);
        points[i].y = luaL_checknumber(L, -1);
        lua_pop(L, 3);
    }

    bool result = CheckCollisionPointPoly(point, points, points_count);

    free(points);
    lua_pushboolean(L, result);
    return 1;
}

// Check the collision between two lines defined by two points each, returns collision point by reference
static int lua_CheckCollisionLines(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 startPos1 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 endPos1 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 startPos2 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    Vector2 endPos2 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 5, LUA_TTABLE);
    int collisionPoint_count = lua_rawlen(L, 5);
    Vector2* collisionPoint = (Vector2*)malloc(collisionPoint_count * sizeof(Vector2));
    for (int i = 0; i < collisionPoint_count; i++) {
        lua_rawgeti(L, 5, i + 1);
        lua_getfield(L, -1, "x");
        lua_getfield(L, -2, "y");
        collisionPoint[i].x = luaL_checknumber(L, -2);
        collisionPoint[i].y = luaL_checknumber(L, -1);
        lua_pop(L, 3);
    }

    bool result = CheckCollisionLines(startPos1, endPos1, startPos2, endPos2, collisionPoint);

    free(collisionPoint);
    lua_pushboolean(L, result);
    return 1;
}

// Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
static int lua_CheckCollisionPointLine(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 point = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    Vector2 p1 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    Vector2 p2 = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    int threshold = luaL_checkinteger(L, 4);

    bool result = CheckCollisionPointLine(point, p1, p2, threshold);

    lua_pushboolean(L, result);
    return 1;
}

// Get collision rectangle for two rectangles collision
static int lua_GetCollisionRec(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "width");
    lua_getfield(L, 1, "height");
    Rectangle rec1 = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "width");
    lua_getfield(L, 2, "height");
    Rectangle rec2 = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);

    Rectangle result = GetCollisionRec(rec1, rec2);

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

// Draw a line in 3D world space
static int lua_DrawLine3D(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 startPos = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 endPos = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawLine3D(startPos, endPos, color);

    return 0;
}

// Draw a circle in 3D world space
static int lua_DrawCircle3D(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 center = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float radius = luaL_checknumber(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "z");
    Vector3 rotationAxis = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float rotationAngle = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);

    return 0;
}

// Draw a color-filled triangle (vertex in counter-clockwise order!)
static int lua_DrawTriangle3D(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 v1 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 v2 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "z");
    Vector3 v3 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTriangle3D(v1, v2, v3, color);

    return 0;
}

// Draw a triangle strip defined by points
static int lua_DrawTriangleStrip3D(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int points_count = lua_rawlen(L, 1);
    Vector3* points = (Vector3*)malloc(points_count * sizeof(Vector3));
    for (int i = 0; i < points_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        lua_getfield(L, -1, "x");
        lua_getfield(L, -2, "y");
        lua_getfield(L, -3, "z");
        points[i].x = luaL_checknumber(L, -3);
        points[i].y = luaL_checknumber(L, -2);
        points[i].z = luaL_checknumber(L, -1);
        lua_pop(L, 4);
    }
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawTriangleStrip3D(points, points_count, color);

    free(points);
    return 0;
}

// Check collision between two spheres
static int lua_CheckCollisionSpheres(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 center1 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float radius1 = luaL_checknumber(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "z");
    Vector3 center2 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float radius2 = luaL_checknumber(L, 4);

    bool result = CheckCollisionSpheres(center1, radius1, center2, radius2);

    lua_pushboolean(L, result);
    return 1;
}

// Check collision between two bounding boxes
static int lua_CheckCollisionBoxes(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "min");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 min1 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 1, "max");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 max1 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    BoundingBox box1 = {min1, max1};
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "min");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 min2 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 2, "max");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 max2 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    BoundingBox box2 = {min2, max2};

    bool result = CheckCollisionBoxes(box1, box2);

    lua_pushboolean(L, result);
    return 1;
}

// Check collision between box and sphere
static int lua_CheckCollisionBoxSphere(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "min");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 min = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 1, "max");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 max = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    BoundingBox box = {min, max};
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 center = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float radius = luaL_checknumber(L, 3);

    bool result = CheckCollisionBoxSphere(box, center, radius);

    lua_pushboolean(L, result);
    return 1;
}

static const struct luaL_Reg rshapes_functions[] = {
    {"DrawPixel", lua_DrawPixel},
    {"DrawPixelV", lua_DrawPixelV},
    {"DrawLine", lua_DrawLine},
    {"DrawLineV", lua_DrawLineV},
    {"DrawLineEx", lua_DrawLineEx},
    {"DrawLineStrip", lua_DrawLineStrip},
    {"DrawLineBezier", lua_DrawLineBezier},
    {"DrawCircle", lua_DrawCircle},
    {"DrawCircleSector", lua_DrawCircleSector},
    {"DrawCircleSectorLines", lua_DrawCircleSectorLines},
    {"DrawCircleGradient", lua_DrawCircleGradient},
    {"DrawCircleV", lua_DrawCircleV},
    {"DrawCircleLines", lua_DrawCircleLines},
    {"DrawCircleLinesV", lua_DrawCircleLinesV},
    {"DrawEllipse", lua_DrawEllipse},
    {"DrawEllipseLines", lua_DrawEllipseLines},
    {"DrawRing", lua_DrawRing},
    {"DrawRingLines", lua_DrawRingLines},
    {"DrawRectangle", lua_DrawRectangle},
    {"DrawRectangleV", lua_DrawRectangleV},
    {"DrawRectangleRec", lua_DrawRectangleRec},
    {"DrawRectanglePro", lua_DrawRectanglePro},
    {"DrawRectangleGradientV", lua_DrawRectangleGradientV},
    {"DrawRectangleGradientH", lua_DrawRectangleGradientH},
    {"DrawRectangleGradientEx", lua_DrawRectangleGradientEx},
    {"DrawRectangleLines", lua_DrawRectangleLines},
    {"DrawRectangleLinesEx", lua_DrawRectangleLinesEx},
    {"DrawRectangleRounded", lua_DrawRectangleRounded},
    {"DrawRectangleRoundedLines", lua_DrawRectangleRoundedLines},
    {"DrawTriangle", lua_DrawTriangle},
    {"DrawTriangleLines", lua_DrawTriangleLines},
    {"DrawTriangleFan", lua_DrawTriangleFan},
    {"DrawTriangleStrip", lua_DrawTriangleStrip},
    {"DrawPoly", lua_DrawPoly},
    {"DrawPolyLines", lua_DrawPolyLines},
    {"DrawPolyLinesEx", lua_DrawPolyLinesEx},
    {"GetSplinePointLinear", lua_GetSplinePointLinear},
    {"GetSplinePointBasis", lua_GetSplinePointBasis},
    {"GetSplinePointCatmullRom", lua_GetSplinePointCatmullRom},
    {"GetSplinePointBezierQuad", lua_GetSplinePointBezierQuad},
    {"GetSplinePointBezierCubic", lua_GetSplinePointBezierCubic},
    {"CheckCollisionRecs", lua_CheckCollisionRecs},
    {"CheckCollisionCircles", lua_CheckCollisionCircles},
    {"CheckCollisionCircleRec", lua_CheckCollisionCircleRec},
    {"CheckCollisionPointRec", lua_CheckCollisionPointRec},
    {"CheckCollisionPointCircle", lua_CheckCollisionPointCircle},
    {"CheckCollisionPointTriangle", lua_CheckCollisionPointTriangle},
    {"CheckCollisionPointPoly", lua_CheckCollisionPointPoly},
    {"CheckCollisionLines", lua_CheckCollisionLines},
    {"CheckCollisionPointLine", lua_CheckCollisionPointLine},
    {"GetCollisionRec", lua_GetCollisionRec},
    {"DrawLine3D", lua_DrawLine3D},
    {"DrawCircle3D", lua_DrawCircle3D},
    {"DrawTriangle3D", lua_DrawTriangle3D},
    {"DrawTriangleStrip3D", lua_DrawTriangleStrip3D},
    {"CheckCollisionSpheres", lua_CheckCollisionSpheres},
    {"CheckCollisionBoxes", lua_CheckCollisionBoxes},
    {"CheckCollisionBoxSphere", lua_CheckCollisionBoxSphere},
    {NULL, NULL}
};

int luaopen_rshapes(lua_State* L) {
    luaL_register(L, "rshapes", rshapes_functions);
    return 1;
}
