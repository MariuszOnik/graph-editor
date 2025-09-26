// Auto-generated Raylib Lua bindings - Module: misc
// Functions: 118

#include "raylib.h"
#include "lua.h"
#include "lauxlib.h"
#include <stdlib.h>
#include <string.h>
#include "ui_helpers.h" // Include your UI helpers for ShowMessage, etc.

// Compatibility wrapper for Lua 5.1
#ifndef lua_rawlen
#define lua_rawlen(L, idx) lua_objlen(L, idx)
#endif

// Create Color table for Lua
static int lua_NewColor(lua_State* L) {
    unsigned char r = (unsigned char)luaL_checkinteger(L, 1);
    unsigned char g = (unsigned char)luaL_checkinteger(L, 2);
    unsigned char b = (unsigned char)luaL_checkinteger(L, 3);
    unsigned char a = (unsigned char)luaL_optinteger(L, 4, 255); // Default alpha is 255

    // Create new Color table
    lua_newtable(L);
    lua_pushinteger(L, r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, a);
    lua_setfield(L, -2, "a");

    return 1; // Return Color table
}

// Check if window has been initialized successfully
static int lua_IsWindowReady(lua_State* L) {
    bool result = IsWindowReady();

    lua_pushboolean(L, result);
    return 1;
}

// Check if window is currently fullscreen
static int lua_IsWindowFullscreen(lua_State* L) {
    bool result = IsWindowFullscreen();

    lua_pushboolean(L, result);
    return 1;
}

// Check if window is currently hidden (only PLATFORM_DESKTOP)
static int lua_IsWindowHidden(lua_State* L) {
    bool result = IsWindowHidden();

    lua_pushboolean(L, result);
    return 1;
}

// Check if window is currently minimized (only PLATFORM_DESKTOP)
static int lua_IsWindowMinimized(lua_State* L) {
    bool result = IsWindowMinimized();

    lua_pushboolean(L, result);
    return 1;
}

// Check if window is currently maximized (only PLATFORM_DESKTOP)
static int lua_IsWindowMaximized(lua_State* L) {
    bool result = IsWindowMaximized();

    lua_pushboolean(L, result);
    return 1;
}

// Check if window is currently focused (only PLATFORM_DESKTOP)
static int lua_IsWindowFocused(lua_State* L) {
    bool result = IsWindowFocused();

    lua_pushboolean(L, result);
    return 1;
}

// Check if window has been resized last frame
static int lua_IsWindowResized(lua_State* L) {
    bool result = IsWindowResized();

    lua_pushboolean(L, result);
    return 1;
}

// Check if one specific window flag is enabled
static int lua_IsWindowState(lua_State* L) {
    unsigned int flag = luaL_checkinteger(L, 1);

    bool result = IsWindowState(flag);

    lua_pushboolean(L, result);
    return 1;
}

// Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
static int lua_ToggleFullscreen(lua_State* L) {
    ToggleFullscreen();

    return 0;
}

// Toggle window state: borderless windowed (only PLATFORM_DESKTOP)
static int lua_ToggleBorderlessWindowed(lua_State* L) {
    ToggleBorderlessWindowed();

    return 0;
}

// Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
static int lua_MaximizeWindow(lua_State* L) {
    MaximizeWindow();

    return 0;
}

// Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
static int lua_MinimizeWindow(lua_State* L) {
    MinimizeWindow();

    return 0;
}

// Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
static int lua_RestoreWindow(lua_State* L) {
    RestoreWindow();

    return 0;
}

// Get current screen width
static int lua_GetScreenWidth(lua_State* L) {
    int result = GetScreenWidth();

    lua_pushinteger(L, result);
    return 1;
}

// Get current screen height
static int lua_GetScreenHeight(lua_State* L) {
    int result = GetScreenHeight();

    lua_pushinteger(L, result);
    return 1;
}

// Get current render width (it considers HiDPI)
static int lua_GetRenderWidth(lua_State* L) {
    int result = GetRenderWidth();

    lua_pushinteger(L, result);
    return 1;
}

// Get current render height (it considers HiDPI)
static int lua_GetRenderHeight(lua_State* L) {
    int result = GetRenderHeight();

    lua_pushinteger(L, result);
    return 1;
}

// Get number of connected monitors
static int lua_GetMonitorCount(lua_State* L) {
    int result = GetMonitorCount();

    lua_pushinteger(L, result);
    return 1;
}

// Get current connected monitor
static int lua_GetCurrentMonitor(lua_State* L) {
    int result = GetCurrentMonitor();

    lua_pushinteger(L, result);
    return 1;
}

// Get specified monitor position
static int lua_GetMonitorPosition(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);

    Vector2 result = GetMonitorPosition(monitor);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Get specified monitor width (current video mode used by monitor)
static int lua_GetMonitorWidth(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);

    int result = GetMonitorWidth(monitor);

    lua_pushinteger(L, result);
    return 1;
}

// Get specified monitor height (current video mode used by monitor)
static int lua_GetMonitorHeight(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);

    int result = GetMonitorHeight(monitor);

    lua_pushinteger(L, result);
    return 1;
}

// Get specified monitor physical width in millimetres
static int lua_GetMonitorPhysicalWidth(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);

    int result = GetMonitorPhysicalWidth(monitor);

    lua_pushinteger(L, result);
    return 1;
}

// Get specified monitor physical height in millimetres
static int lua_GetMonitorPhysicalHeight(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);

    int result = GetMonitorPhysicalHeight(monitor);

    lua_pushinteger(L, result);
    return 1;
}

// Get specified monitor refresh rate
static int lua_GetMonitorRefreshRate(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);

    int result = GetMonitorRefreshRate(monitor);

    lua_pushinteger(L, result);
    return 1;
}

// Get window position XY on monitor
static int lua_GetWindowPosition(lua_State* L) {
    Vector2 result = GetWindowPosition();

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Get window scale DPI factor
static int lua_GetWindowScaleDPI(lua_State* L) {
    Vector2 result = GetWindowScaleDPI();

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Begin drawing to render texture
static int lua_BeginTextureMode(lua_State* L) {
    RenderTexture2D* target = (RenderTexture2D*)luaL_checkudata(L, 1, "RenderTexture2D");

    BeginTextureMode(*target);

    return 0;
}

// Ends drawing to render texture
static int lua_EndTextureMode(lua_State* L) {
    EndTextureMode();

    return 0;
}

// Begin custom shader drawing
static int lua_BeginShaderMode(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");

    BeginShaderMode(*shader);

    return 0;
}

// End custom shader drawing (use default shader)
static int lua_EndShaderMode(lua_State* L) {
    EndShaderMode();

    return 0;
}

// Begin blending mode (alpha, additive, multiplied, subtract, custom)
static int lua_BeginBlendMode(lua_State* L) {
    int mode = luaL_checkinteger(L, 1);

    BeginBlendMode(mode);

    return 0;
}

// End blending mode (reset to default: alpha blending)
static int lua_EndBlendMode(lua_State* L) {
    EndBlendMode();

    return 0;
}

// Begin scissor mode (define screen area for following drawing)
static int lua_BeginScissorMode(lua_State* L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);

    BeginScissorMode(x, y, width, height);

    return 0;
}

// End scissor mode
static int lua_EndScissorMode(lua_State* L) {
    EndScissorMode();

    return 0;
}

// Get shader uniform location
static int lua_GetShaderLocation(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");
    char * uniformName = luaL_checkstring(L, 2);

    int result = GetShaderLocation(*shader, uniformName);

    lua_pushinteger(L, result);
    return 1;
}

// Get shader attribute location
static int lua_GetShaderLocationAttrib(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");
    char * attribName = luaL_checkstring(L, 2);

    int result = GetShaderLocationAttrib(*shader, attribName);

    lua_pushinteger(L, result);
    return 1;
}

// Unload shader from GPU memory (VRAM)
static int lua_UnloadShader(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");

    UnloadShader(*shader);

    return 0;
}

// Swap back buffer with front buffer (screen drawing)
static int lua_SwapScreenBuffer(lua_State* L) {
    SwapScreenBuffer();

    return 0;
}

// Register all input events
static int lua_PollInputEvents(lua_State* L) {
    PollInputEvents();

    return 0;
}

// Wait for some time (halt program execution)
static int lua_WaitTime(lua_State* L) {
    double seconds = luaL_checknumber(L, 1);

    WaitTime(seconds);

    return 0;
}

// Unload random values sequence - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_UnloadRandomSequence(lua_State* L) {
//     // TODO: Handle parameter int * sequence
// 
//     UnloadRandomSequence(sequence);
// 
//     return 0;
// }

// Takes a screenshot of current screen (filename extension defines format)
static int lua_TakeScreenshot(lua_State* L) {
    char * fileName = luaL_checkstring(L, 1);

    TakeScreenshot(fileName);

    return 0;
}

// Open URL with default system browser (if available) - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_OpenURL(lua_State* L) {
//     char * url = luaL_checkstring(L, 1);
// 
//     OpenURL(url);
// 
//     return 0;
// }

// Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
static int lua_TraceLog(lua_State* L) {
    int logLevel = luaL_checkinteger(L, 1);
    const char * text = luaL_checkstring(L, 2);

    TraceLog(logLevel, "%s", text);

    return 0;
}

// Check file extension (including point: .png, .wav)
static int lua_IsFileExtension(lua_State* L) {
    char * fileName = luaL_checkstring(L, 1);
    char * ext = luaL_checkstring(L, 2);

    bool result = IsFileExtension(fileName, ext);

    lua_pushboolean(L, result);
    return 1;
}

// Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
static int lua_GetFileLength(lua_State* L) {
    char * fileName = luaL_checkstring(L, 1);

    int result = GetFileLength(fileName);

    lua_pushinteger(L, result);
    return 1;
}

// Change working directory, return true on success
static int lua_ChangeDirectory(lua_State* L) {
    char * dir = luaL_checkstring(L, 1);

    bool result = ChangeDirectory(dir);

    lua_pushboolean(L, result);
    return 1;
}

// Check if a given path is a file or a directory
static int lua_IsPathFile(lua_State* L) {
    char * path = luaL_checkstring(L, 1);

    bool result = IsPathFile(path);

    lua_pushboolean(L, result);
    return 1;
}

// Unload filepaths - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_UnloadDirectoryFiles(lua_State* L) {
//     // TODO: Handle parameter FilePathList files
// 
//     UnloadDirectoryFiles(files);
// 
//     return 0;
// }

// Check if a file has been dropped into window
static int lua_IsFileDropped(lua_State* L) {
    bool result = IsFileDropped();

    lua_pushboolean(L, result);
    return 1;
}

// Unload dropped filepaths - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_UnloadDroppedFiles(lua_State* L) {
//     // TODO: Handle parameter FilePathList files
// 
//     UnloadDroppedFiles(files);
// 
//     return 0;
// }

// Get file modification time (last write time)
static int lua_GetFileModTime(lua_State* L) {
    char * fileName = luaL_checkstring(L, 1);

    long result = GetFileModTime(fileName);

    lua_pushinteger(L, result);
    return 1;
}

// Unload automation events list from file - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_UnloadAutomationEventList(lua_State* L) {
//     // TODO: Handle parameter AutomationEventList * list
// 
//     UnloadAutomationEventList(list);
// 
//     return 0;
// }

// Export automation events list as text file - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_ExportAutomationEventList(lua_State* L) {
//     // TODO: Handle parameter AutomationEventList list
//     char * fileName = luaL_checkstring(L, 2);
// 
//     bool result = ExportAutomationEventList(list, fileName);
// 
//     lua_pushboolean(L, result);
//     return 1;
// }

// Start recording automation events (AutomationEventList must be set)
static int lua_StartAutomationEventRecording(lua_State* L) {
    StartAutomationEventRecording();

    return 0;
}

// Stop recording automation events
static int lua_StopAutomationEventRecording(lua_State* L) {
    StopAutomationEventRecording();

    return 0;
}

// Play a recorded automation event - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_PlayAutomationEvent(lua_State* L) {
//     // TODO: Handle parameter AutomationEvent event
// 
//     PlayAutomationEvent(event);
// 
//     return 0;
// }

// Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
static int lua_GetCharPressed(lua_State* L) {
    int result = GetCharPressed();

    lua_pushinteger(L, result);
    return 1;
}

// Draw spline: Linear, minimum 2 points
static int lua_DrawSplineLinear(lua_State* L) {
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
    float thick = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawSplineLinear(points, points_count, thick, color);

    free(points);
    return 0;
}

// Draw spline: B-Spline, minimum 4 points
static int lua_DrawSplineBasis(lua_State* L) {
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
    float thick = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawSplineBasis(points, points_count, thick, color);

    free(points);
    return 0;
}

// Draw spline: Catmull-Rom, minimum 4 points
static int lua_DrawSplineCatmullRom(lua_State* L) {
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
    float thick = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawSplineCatmullRom(points, points_count, thick, color);

    free(points);
    return 0;
}

// Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]
static int lua_DrawSplineBezierQuadratic(lua_State* L) {
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
    float thick = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawSplineBezierQuadratic(points, points_count, thick, color);

    free(points);
    return 0;
}

// Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]
static int lua_DrawSplineBezierCubic(lua_State* L) {
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
    float thick = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawSplineBezierCubic(points, points_count, thick, color);

    free(points);
    return 0;
}

// Draw spline segment: Linear, 2 points
static int lua_DrawSplineSegmentLinear(lua_State* L) {
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
    float thick = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawSplineSegmentLinear(p1, p2, thick, color);

    return 0;
}

// Draw spline segment: B-Spline, 4 points
static int lua_DrawSplineSegmentBasis(lua_State* L) {
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
    float thick = luaL_checknumber(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawSplineSegmentBasis(p1, p2, p3, p4, thick, color);

    return 0;
}

// Draw spline segment: Catmull-Rom, 4 points
static int lua_DrawSplineSegmentCatmullRom(lua_State* L) {
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
    float thick = luaL_checknumber(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawSplineSegmentCatmullRom(p1, p2, p3, p4, thick, color);

    return 0;
}

// Draw spline segment: Quadratic Bezier, 2 points, 1 control point
static int lua_DrawSplineSegmentBezierQuadratic(lua_State* L) {
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
    float thick = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawSplineSegmentBezierQuadratic(p1, c2, p3, thick, color);

    return 0;
}

// Draw spline segment: Cubic Bezier, 2 points, 2 control points
static int lua_DrawSplineSegmentBezierCubic(lua_State* L) {
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
    float thick = luaL_checknumber(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawSplineSegmentBezierCubic(p1, c2, c3, p4, thick, color);

    return 0;
}

// Check if a render texture is ready - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_IsRenderTextureReady(lua_State* L) {
//     RenderTexture2D* target = (RenderTexture2D*)luaL_checkudata(L, 1, "RenderTexture2D");
// 
//     bool result = IsRenderTextureReady(*target);
// 
//     lua_pushboolean(L, result);
//     return 1;
// }

// Update GPU texture with new data
static int lua_UpdateTexture(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    void* pixels = lua_touserdata(L, 2);

    UpdateTexture(*texture, pixels);

    return 0;
}

// Update GPU texture rectangle with new data
static int lua_UpdateTextureRec(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "width");
    lua_getfield(L, 2, "height");
    Rectangle rec = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    void* pixels = lua_touserdata(L, 3);

    UpdateTextureRec(*texture, rec, pixels);

    return 0;
}

// Get hexadecimal value for a Color
static int lua_ColorToInt(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "r");
    lua_getfield(L, 1, "g");
    lua_getfield(L, 1, "b");
    lua_getfield(L, 1, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    int result = ColorToInt(color);

    lua_pushinteger(L, result);
    return 1;
}

// Get pixel data size in bytes for certain format
static int lua_GetPixelDataSize(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    int format = luaL_checkinteger(L, 3);

    int result = GetPixelDataSize(width, height, format);

    lua_pushinteger(L, result);
    return 1;
}

// Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
static int lua_GetGlyphIndex(lua_State* L) {
    Font* font = (Font*)luaL_checkudata(L, 1, "Font");
    int codepoint = luaL_checkinteger(L, 2);

    int result = GetGlyphIndex(*font, codepoint);

    lua_pushinteger(L, result);
    return 1;
}

// Draw a point in 3D space, actually a small line
static int lua_DrawPoint3D(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawPoint3D(position, color);

    return 0;
}

// Draw cube
static int lua_DrawCube(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float width = luaL_checknumber(L, 2);
    float height = luaL_checknumber(L, 3);
    float length = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCube(position, width, height, length, color);

    return 0;
}

// Draw cube (Vector version)
static int lua_DrawCubeV(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 size = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCubeV(position, size, color);

    return 0;
}

// Draw cube wires
static int lua_DrawCubeWires(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float width = luaL_checknumber(L, 2);
    float height = luaL_checknumber(L, 3);
    float length = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCubeWires(position, width, height, length, color);

    return 0;
}

// Draw cube wires (Vector version)
static int lua_DrawCubeWiresV(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 size = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCubeWiresV(position, size, color);

    return 0;
}

// Draw sphere
static int lua_DrawSphere(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 centerPos = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float radius = luaL_checknumber(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "r");
    lua_getfield(L, 3, "g");
    lua_getfield(L, 3, "b");
    lua_getfield(L, 3, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawSphere(centerPos, radius, color);

    return 0;
}

// Draw sphere with extended parameters
static int lua_DrawSphereEx(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 centerPos = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float radius = luaL_checknumber(L, 2);
    int rings = luaL_checkinteger(L, 3);
    int slices = luaL_checkinteger(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawSphereEx(centerPos, radius, rings, slices, color);

    return 0;
}

// Draw sphere wires
static int lua_DrawSphereWires(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 centerPos = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float radius = luaL_checknumber(L, 2);
    int rings = luaL_checkinteger(L, 3);
    int slices = luaL_checkinteger(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawSphereWires(centerPos, radius, rings, slices, color);

    return 0;
}

// Draw a cylinder/cone
static int lua_DrawCylinder(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float radiusTop = luaL_checknumber(L, 2);
    float radiusBottom = luaL_checknumber(L, 3);
    float height = luaL_checknumber(L, 4);
    int slices = luaL_checkinteger(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);

    return 0;
}

// Draw a cylinder with base at startPos and top at endPos
static int lua_DrawCylinderEx(lua_State* L) {
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
    float startRadius = luaL_checknumber(L, 3);
    float endRadius = luaL_checknumber(L, 4);
    int sides = luaL_checkinteger(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCylinderEx(startPos, endPos, startRadius, endRadius, sides, color);

    return 0;
}

// Draw a cylinder/cone wires
static int lua_DrawCylinderWires(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float radiusTop = luaL_checknumber(L, 2);
    float radiusBottom = luaL_checknumber(L, 3);
    float height = luaL_checknumber(L, 4);
    int slices = luaL_checkinteger(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);

    return 0;
}

// Draw a cylinder wires with base at startPos and top at endPos
static int lua_DrawCylinderWiresEx(lua_State* L) {
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
    float startRadius = luaL_checknumber(L, 3);
    float endRadius = luaL_checknumber(L, 4);
    int sides = luaL_checkinteger(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCylinderWiresEx(startPos, endPos, startRadius, endRadius, sides, color);

    return 0;
}

// Draw a capsule with the center of its sphere caps at startPos and endPos
static int lua_DrawCapsule(lua_State* L) {
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
    float radius = luaL_checknumber(L, 3);
    int slices = luaL_checkinteger(L, 4);
    int rings = luaL_checkinteger(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCapsule(startPos, endPos, radius, slices, rings, color);

    return 0;
}

// Draw capsule wireframe with the center of its sphere caps at startPos and endPos
static int lua_DrawCapsuleWires(lua_State* L) {
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
    float radius = luaL_checknumber(L, 3);
    int slices = luaL_checkinteger(L, 4);
    int rings = luaL_checkinteger(L, 5);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawCapsuleWires(startPos, endPos, radius, slices, rings, color);

    return 0;
}

// Draw a plane XZ
static int lua_DrawPlane(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 centerPos = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
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

    DrawPlane(centerPos, size, color);

    return 0;
}

// Draw a ray line - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_DrawRay(lua_State* L) {
//     // TODO: Extract Ray ray from table at position 1
//     luaL_checktype(L, 2, LUA_TTABLE);
//     lua_getfield(L, 2, "r");
//     lua_getfield(L, 2, "g");
//     lua_getfield(L, 2, "b");
//     lua_getfield(L, 2, "a");
//     Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
//     lua_pop(L, 4);
// 
//     DrawRay(ray, color);
// 
//     return 0;
// }

// Draw a grid (centered at (0, 0, 0))
static int lua_DrawGrid(lua_State* L) {
    int slices = luaL_checkinteger(L, 1);
    float spacing = luaL_checknumber(L, 2);

    DrawGrid(slices, spacing);

    return 0;
}

// Draw bounding box (wires)
static int lua_DrawBoundingBox(lua_State* L) {
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
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawBoundingBox(box, color);

    return 0;
}

// Draw a billboard texture
static int lua_DrawBillboard(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "position");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 camera_position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 1, "target");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 target = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 1, "up");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 up = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 1, "fovy");
    float fovy = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, 1, "projection");
    int projection = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    Camera3D camera = {camera_position, target, up, fovy, projection};
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 2, "Texture2D");
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float size = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "r");
    lua_getfield(L, 5, "g");
    lua_getfield(L, 5, "b");
    lua_getfield(L, 5, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawBillboard(camera, *texture, position, size, tint);

    return 0;
}

// Draw a billboard texture defined by source
static int lua_DrawBillboardRec(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "position");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 camera_position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 1, "target");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 target = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 1, "up");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 up = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 1, "fovy");
    float fovy = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, 1, "projection");
    int projection = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    Camera3D camera = {camera_position, target, up, fovy, projection};
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 2, "Texture2D");
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "width");
    lua_getfield(L, 3, "height");
    Rectangle source = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    lua_getfield(L, 4, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "x");
    lua_getfield(L, 5, "y");
    Vector2 size = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawBillboardRec(camera, *texture, source, position, size, tint);

    return 0;
}

// Draw a billboard texture defined by source and rotation
static int lua_DrawBillboardPro(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "position");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 camera_position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 1, "target");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 target = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 1, "up");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 camera_up = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 1, "fovy");
    float fovy = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, 1, "projection");
    int projection = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    Camera3D camera = {camera_position, target, camera_up, fovy, projection};
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 2, "Texture2D");
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "width");
    lua_getfield(L, 3, "height");
    Rectangle source = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    lua_getfield(L, 4, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "x");
    lua_getfield(L, 5, "y");
    lua_getfield(L, 5, "z");
    Vector3 up = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "x");
    lua_getfield(L, 6, "y");
    Vector2 size = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 7, LUA_TTABLE);
    lua_getfield(L, 7, "x");
    lua_getfield(L, 7, "y");
    Vector2 origin = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    float rotation = luaL_checknumber(L, 8);
    luaL_checktype(L, 9, LUA_TTABLE);
    lua_getfield(L, 9, "r");
    lua_getfield(L, 9, "g");
    lua_getfield(L, 9, "b");
    lua_getfield(L, 9, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawBillboardPro(camera, *texture, source, position, up, size, origin, rotation, tint);

    return 0;
}

// Upload mesh vertex data in GPU and provide VAO/VBO ids - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_UploadMesh(lua_State* L) {
//     // TODO: Handle array of Mesh mesh at position 1
//     bool dynamic = lua_toboolean(L, 2);
// 
//     UploadMesh(mesh, dynamic);
// 
//     return 0;
// }

// Update mesh vertex data in GPU for a specific buffer index - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_UpdateMeshBuffer(lua_State* L) {
//     Mesh* mesh = (Mesh*)luaL_checkudata(L, 1, "Mesh");
//     int index = luaL_checkinteger(L, 2);
//     // TODO: Handle parameter void * data
//     int dataSize = luaL_checkinteger(L, 4);
//     int offset = luaL_checkinteger(L, 5);
// 
//     UpdateMeshBuffer(*mesh, index, data, dataSize, offset);
// 
//     return 0;
// }

// Check if a material is ready - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_IsMaterialReady(lua_State* L) {
//     Material* material = (Material*)luaL_checkudata(L, 1, "Material");
// 
//     bool result = IsMaterialReady(*material);
// 
//     lua_pushboolean(L, result);
//     return 1;
// }

// Get master volume (listener)
static int lua_GetMasterVolume(lua_State* L) {
    float result = GetMasterVolume();

    lua_pushnumber(L, result);
    return 1;
}

static int lua_ShowMessage(lua_State* L) {
    const char* message = luaL_checkstring(L, 1);
    ShowMessage(message);
    return 0;
}



// Update sound buffer with new data - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_UpdateSound(lua_State* L) {
//     Sound* sound = (Sound*)luaL_checkudata(L, 1, "Sound");
//     // TODO: Handle parameter void * data
// 
//     UpdateSound(*sound, data, data_count);
// 
//     return 0;
// }

// Export wave data to file, returns true on success - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_ExportWave(lua_State* L) {
//     // TODO: Handle parameter Wave wave
//     char * fileName = luaL_checkstring(L, 2);
// 
//     bool result = ExportWave(wave, fileName);
// 
//     lua_pushboolean(L, result);
//     return 1;
// }

// Export wave sample data to code (.h), returns true on success - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_ExportWaveAsCode(lua_State* L) {
//     // TODO: Handle parameter Wave wave
//     char * fileName = luaL_checkstring(L, 2);
// 
//     bool result = ExportWaveAsCode(wave, fileName);
// 
//     lua_pushboolean(L, result);
//     return 1;
// }

// Crop a wave to defined samples range - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_WaveCrop(lua_State* L) {
//     // TODO: Handle parameter Wave * wave
//     int initSample = luaL_checkinteger(L, 2);
//     int finalSample = luaL_checkinteger(L, 3);
// 
//     WaveCrop(wave, initSample, finalSample);
// 
//     return 0;
// }

// Convert wave data to desired format - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_WaveFormat(lua_State* L) {
//     // TODO: Handle parameter Wave * wave
//     int sampleRate = luaL_checkinteger(L, 2);
//     int sampleSize = luaL_checkinteger(L, 3);
//     int channels = luaL_checkinteger(L, 4);
// 
//     WaveFormat(wave, sampleRate, sampleSize, channels);
// 
//     return 0;
// }

// Update audio stream buffers with data - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_UpdateAudioStream(lua_State* L) {
//     // TODO: Handle parameter AudioStream stream
//     // TODO: Handle parameter void * data
// 
//     UpdateAudioStream(stream, data, data_count);
// 
//     return 0;
// }

// Attach audio stream processor to stream, receives the samples as <float>s - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_AttachAudioStreamProcessor(lua_State* L) {
//     // TODO: Handle parameter AudioStream stream
//     // TODO: Handle parameter AudioCallback processor
// 
//     AttachAudioStreamProcessor(stream, processor);
// 
//     return 0;
// }

// Detach audio stream processor from stream - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_DetachAudioStreamProcessor(lua_State* L) {
//     // TODO: Handle parameter AudioStream stream
//     // TODO: Handle parameter AudioCallback processor
// 
//     DetachAudioStreamProcessor(stream, processor);
// 
//     return 0;
// }

// Attach audio stream processor to the entire audio pipeline, receives the samples as <float>s - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_AttachAudioMixedProcessor(lua_State* L) {
//     // TODO: Handle parameter AudioCallback processor
// 
//     AttachAudioMixedProcessor(processor);
// 
//     return 0;
// }

// Detach audio stream processor from the entire audio pipeline - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_DetachAudioMixedProcessor(lua_State* L) {
//     // TODO: Handle parameter AudioCallback processor
// 
//     DetachAudioMixedProcessor(processor);
// 
//     return 0;
// }

static const struct luaL_Reg misc_functions[] = {
    {"NewColor", lua_NewColor},
    {"IsWindowReady", lua_IsWindowReady},
    {"IsWindowFullscreen", lua_IsWindowFullscreen},
    {"IsWindowHidden", lua_IsWindowHidden},
    {"IsWindowMinimized", lua_IsWindowMinimized},
    {"IsWindowMaximized", lua_IsWindowMaximized},
    {"IsWindowFocused", lua_IsWindowFocused},
    {"IsWindowResized", lua_IsWindowResized},
    {"IsWindowState", lua_IsWindowState},
    {"ToggleFullscreen", lua_ToggleFullscreen},
    {"ToggleBorderlessWindowed", lua_ToggleBorderlessWindowed},
    {"MaximizeWindow", lua_MaximizeWindow},
    {"MinimizeWindow", lua_MinimizeWindow},
    {"RestoreWindow", lua_RestoreWindow},
    {"GetScreenWidth", lua_GetScreenWidth},
    {"GetScreenHeight", lua_GetScreenHeight},
    {"GetRenderWidth", lua_GetRenderWidth},
    {"GetRenderHeight", lua_GetRenderHeight},
    {"GetMonitorCount", lua_GetMonitorCount},
    {"GetCurrentMonitor", lua_GetCurrentMonitor},
    {"GetMonitorPosition", lua_GetMonitorPosition},
    {"GetMonitorWidth", lua_GetMonitorWidth},
    {"GetMonitorHeight", lua_GetMonitorHeight},
    {"GetMonitorPhysicalWidth", lua_GetMonitorPhysicalWidth},
    {"GetMonitorPhysicalHeight", lua_GetMonitorPhysicalHeight},
    {"GetMonitorRefreshRate", lua_GetMonitorRefreshRate},
    {"GetWindowPosition", lua_GetWindowPosition},
    {"GetWindowScaleDPI", lua_GetWindowScaleDPI},
    {"BeginTextureMode", lua_BeginTextureMode},
    {"EndTextureMode", lua_EndTextureMode},
    {"BeginShaderMode", lua_BeginShaderMode},
    {"EndShaderMode", lua_EndShaderMode},
    {"BeginBlendMode", lua_BeginBlendMode},
    {"EndBlendMode", lua_EndBlendMode},
    {"BeginScissorMode", lua_BeginScissorMode},
    {"EndScissorMode", lua_EndScissorMode},
    {"GetShaderLocation", lua_GetShaderLocation},
    {"GetShaderLocationAttrib", lua_GetShaderLocationAttrib},
    {"UnloadShader", lua_UnloadShader},
    {"SwapScreenBuffer", lua_SwapScreenBuffer},
    {"PollInputEvents", lua_PollInputEvents},
    {"WaitTime", lua_WaitTime},
    {"TakeScreenshot", lua_TakeScreenshot},
    {"TraceLog", lua_TraceLog},
    {"IsFileExtension", lua_IsFileExtension},
    {"GetFileLength", lua_GetFileLength},
    {"ChangeDirectory", lua_ChangeDirectory},
    {"IsPathFile", lua_IsPathFile},
    {"IsFileDropped", lua_IsFileDropped},
    {"GetFileModTime", lua_GetFileModTime},
    {"StartAutomationEventRecording", lua_StartAutomationEventRecording},
    {"StopAutomationEventRecording", lua_StopAutomationEventRecording},
    {"GetCharPressed", lua_GetCharPressed},
    {"DrawSplineLinear", lua_DrawSplineLinear},
    {"DrawSplineBasis", lua_DrawSplineBasis},
    {"DrawSplineCatmullRom", lua_DrawSplineCatmullRom},
    {"DrawSplineBezierQuadratic", lua_DrawSplineBezierQuadratic},
    {"DrawSplineBezierCubic", lua_DrawSplineBezierCubic},
    {"DrawSplineSegmentLinear", lua_DrawSplineSegmentLinear},
    {"DrawSplineSegmentBasis", lua_DrawSplineSegmentBasis},
    {"DrawSplineSegmentCatmullRom", lua_DrawSplineSegmentCatmullRom},
    {"DrawSplineSegmentBezierQuadratic", lua_DrawSplineSegmentBezierQuadratic},
    {"DrawSplineSegmentBezierCubic", lua_DrawSplineSegmentBezierCubic},
    {"UpdateTexture", lua_UpdateTexture},
    {"UpdateTextureRec", lua_UpdateTextureRec},
    {"ColorToInt", lua_ColorToInt},
    {"GetPixelDataSize", lua_GetPixelDataSize},
    {"GetGlyphIndex", lua_GetGlyphIndex},
    {"DrawPoint3D", lua_DrawPoint3D},
    {"DrawCube", lua_DrawCube},
    {"DrawCubeV", lua_DrawCubeV},
    {"DrawCubeWires", lua_DrawCubeWires},
    {"DrawCubeWiresV", lua_DrawCubeWiresV},
    {"DrawSphere", lua_DrawSphere},
    {"DrawSphereEx", lua_DrawSphereEx},
    {"DrawSphereWires", lua_DrawSphereWires},
    {"DrawCylinder", lua_DrawCylinder},
    {"DrawCylinderEx", lua_DrawCylinderEx},
    {"DrawCylinderWires", lua_DrawCylinderWires},
    {"DrawCylinderWiresEx", lua_DrawCylinderWiresEx},
    {"DrawCapsule", lua_DrawCapsule},
    {"DrawCapsuleWires", lua_DrawCapsuleWires},
    {"DrawPlane", lua_DrawPlane},
    {"DrawGrid", lua_DrawGrid},
    {"DrawBoundingBox", lua_DrawBoundingBox},
    {"DrawBillboard", lua_DrawBillboard},
    {"DrawBillboardRec", lua_DrawBillboardRec},
    {"DrawBillboardPro", lua_DrawBillboardPro},
    {"GetMasterVolume", lua_GetMasterVolume},
    {"ShowMessage", lua_ShowMessage},
    {NULL, NULL}
};

int luaopen_misc(lua_State* L) {
    luaL_register(L, "rmisc", misc_functions);
    return 1;
}
