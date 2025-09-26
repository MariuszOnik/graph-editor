// Auto-generated Raylib Lua bindings - Module: rcore
// Based on real raylib source: rcore.c
// Core functionality - window, input, timing, files
// Functions: 132

#include "raylib.h"
#include "camera_input.h"
#include "lua.h"
#include "lauxlib.h"
#include <stdlib.h>
// --- BINDINGI LUA ---
#include "../project_browser.h"
#include <string.h>
#include "rgestures.h"   // żeby mieć GESTURE_* (enum Gesture)


// Lua 5.1 compatibility wrapper
#if LUA_VERSION_NUM < 502
#define lua_rawlen lua_objlen
#endif

static int lua_GetFileList(lua_State* L) {
    const char* path = luaL_checkstring(L, 1);
    int count = 0;
    char** files = GetFileList(path, &count);
    lua_newtable(L);
    for (int i = 0; i < count; ++i) {
        lua_pushstring(L, files[i]);
        lua_rawseti(L, -2, i + 1);
        free(files[i]);
    }
    free(files);
    return 1;
}

// Initialize window and OpenGL context
static int lua_InitWindow(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    char * title = luaL_checkstring(L, 3);

    InitWindow(width, height, title);

    return 0;
}

// Close window and unload OpenGL context
static int lua_CloseWindow(lua_State* L) {
    CloseWindow();

    return 0;
}

// Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
static int lua_WindowShouldClose(lua_State* L) {
    bool result = WindowShouldClose();

    lua_pushboolean(L, result);
    return 1;
}

// Set window configuration state using flags (only PLATFORM_DESKTOP)
static int lua_SetWindowState(lua_State* L) {
    unsigned int flags = luaL_checkinteger(L, 1);

    SetWindowState(flags);

    return 0;
}

// Clear window configuration state flags
static int lua_ClearWindowState(lua_State* L) {
    unsigned int flags = luaL_checkinteger(L, 1);

    ClearWindowState(flags);

    return 0;
}

// Set icon for window (single image, RGBA 32bit, only PLATFORM_DESKTOP)
static int lua_SetWindowIcon(lua_State* L) {
    Image* image = (Image*)luaL_checkudata(L, 1, "Image");

    SetWindowIcon(*image);

    return 0;
}

// Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)
static int lua_SetWindowIcons(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int images_count = lua_rawlen(L, 1);
    Image* images = (Image*)malloc(images_count * sizeof(Image));
    for (int i = 0; i < images_count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image* img = (Image*)luaL_checkudata(L, -1, "Image");
        images[i] = *img;
        lua_pop(L, 1);
    }
    int count = luaL_checkinteger(L, 2);

    SetWindowIcons(images, count);

    return 0;
}

// Set title for window (only PLATFORM_DESKTOP and PLATFORM_WEB)
static int lua_SetWindowTitle(lua_State* L) {
    char * title = luaL_checkstring(L, 1);

    SetWindowTitle(title);

    return 0;
}

// Set window position on screen (only PLATFORM_DESKTOP)
static int lua_SetWindowPosition(lua_State* L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);

    SetWindowPosition(x, y);

    return 0;
}

// Set monitor for the current window
static int lua_SetWindowMonitor(lua_State* L) {
    int monitor = luaL_checkinteger(L, 1);

    SetWindowMonitor(monitor);

    return 0;
}

// Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
static int lua_SetWindowMinSize(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);

    SetWindowMinSize(width, height);

    return 0;
}

// Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
static int lua_SetWindowMaxSize(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);

    SetWindowMaxSize(width, height);

    return 0;
}

// Set window dimensions
static int lua_SetWindowSize(lua_State* L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);

    SetWindowSize(width, height);

    return 0;
}

// Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)
static int lua_SetWindowOpacity(lua_State* L) {
    float opacity = luaL_checknumber(L, 1);

    SetWindowOpacity(opacity);

    return 0;
}

// Set window focused (only PLATFORM_DESKTOP)
static int lua_SetWindowFocused(lua_State* L) {
    SetWindowFocused();

    return 0;
}

// Set clipboard text content
static int lua_SetClipboardText(lua_State* L) {
    char * text = luaL_checkstring(L, 1);

    SetClipboardText(text);

    return 0;
}

// Enable waiting for events on EndDrawing(), no automatic event polling
static int lua_EnableEventWaiting(lua_State* L) {
    EnableEventWaiting();

    return 0;
}

// Disable waiting for events on EndDrawing(), automatic events polling
static int lua_DisableEventWaiting(lua_State* L) {
    DisableEventWaiting();

    return 0;
}

// Shows cursor
static int lua_ShowCursor(lua_State* L) {
    ShowCursor();

    return 0;
}

// Hides cursor
static int lua_HideCursor(lua_State* L) {
    HideCursor();

    return 0;
}

// Check if cursor is not visible
static int lua_IsCursorHidden(lua_State* L) {
    bool result = IsCursorHidden();

    lua_pushboolean(L, result);
    return 1;
}

// Enables cursor (unlock cursor)
static int lua_EnableCursor(lua_State* L) {
    EnableCursor();

    return 0;
}

// Disables cursor (lock cursor)
static int lua_DisableCursor(lua_State* L) {
    DisableCursor();

    return 0;
}

// Check if cursor is on the screen
static int lua_IsCursorOnScreen(lua_State* L) {
    bool result = IsCursorOnScreen();

    lua_pushboolean(L, result);
    return 1;
}

// Set background color (framebuffer clear color)
static int lua_ClearBackground(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "r");
    lua_getfield(L, 1, "g");
    lua_getfield(L, 1, "b");
    lua_getfield(L, 1, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    ClearBackground(color);

    return 0;
}

// Setup canvas (framebuffer) to start drawing
static int lua_BeginDrawing(lua_State* L) {
    BeginDrawing();

    return 0;
}

// End canvas drawing and swap buffers (double buffering)
static int lua_EndDrawing(lua_State* L) {
    EndDrawing();

    return 0;
}

// Begin 2D mode with custom camera (2D)
static int lua_BeginMode2D(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "offset");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    Vector2 offset = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    lua_getfield(L, 1, "target");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    Vector2 target = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    lua_getfield(L, 1, "rotation");
    float rotation = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, 1, "zoom");
    float zoom = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    Camera2D camera = {offset, target, rotation, zoom};

    BeginMode2D(camera);

    return 0;
}

// Ends 2D mode with custom camera
static int lua_EndMode2D(lua_State* L) {
    EndMode2D();

    return 0;
}

// Begin 3D mode with custom camera (3D)
/* static int lua_BeginMode3D(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "position");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
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
    Camera3D camera = {position, target, up, fovy, projection};

    BeginMode3D(camera);

    return 0;
} */
static int lua_BeginMode3D(lua_State* L) {
    Camera3D* camera = (Camera3D*)luaL_checkudata(L, 1, "Camera3D");
    BeginMode3D(*camera);
    return 0;
}
// Ends 3D mode and returns to default 2D orthographic mode
static int lua_EndMode3D(lua_State* L) {
    EndMode3D();

    return 0;
}

// Load VR stereo config for VR simulator device parameters
static int lua_LoadVrStereoConfig(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    
    VrDeviceInfo device;
    lua_getfield(L, 1, "hResolution");
    device.hResolution = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    
    lua_getfield(L, 1, "vResolution");
    device.vResolution = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    
    lua_getfield(L, 1, "hScreenSize");
    device.hScreenSize = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    
    lua_getfield(L, 1, "vScreenSize");
    device.vScreenSize = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    
    lua_getfield(L, 1, "eyeToScreenDistance");
    device.eyeToScreenDistance = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    
    lua_getfield(L, 1, "eyeToScreenDistance");
    device.eyeToScreenDistance = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    
    lua_getfield(L, 1, "lensSeparationDistance");
    device.lensSeparationDistance = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    
    lua_getfield(L, 1, "interpupillaryDistance");
    device.interpupillaryDistance = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    
    // Arrays
    lua_getfield(L, 1, "lensDistortionValues");
    for (int i = 0; i < 4; i++) {
        lua_rawgeti(L, -1, i + 1);
        device.lensDistortionValues[i] = luaL_checknumber(L, -1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    
    lua_getfield(L, 1, "chromaAbCorrection");
    for (int i = 0; i < 4; i++) {
        lua_rawgeti(L, -1, i + 1);
        device.chromaAbCorrection[i] = luaL_checknumber(L, -1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);

    VrStereoConfig result = LoadVrStereoConfig(device);

    VrStereoConfig* result_ptr = (VrStereoConfig*)lua_newuserdata(L, sizeof(VrStereoConfig));
    *result_ptr = result;
    luaL_getmetatable(L, "VrStereoConfig");
    lua_setmetatable(L, -2);
    return 1;
}

// Load shader from files and bind default locations
static int lua_LoadShader(lua_State* L) {
    char * vsFileName = luaL_checkstring(L, 1);
    char * fsFileName = luaL_checkstring(L, 2);

    Shader result = LoadShader(vsFileName, fsFileName);

    Shader* result_ptr = (Shader*)lua_newuserdata(L, sizeof(Shader));
    *result_ptr = result;
    luaL_getmetatable(L, "Shader");
    lua_setmetatable(L, -2);
    return 1;
}

// Load shader from code strings and bind default locations
static int lua_LoadShaderFromMemory(lua_State* L) {
    char * vsCode = luaL_checkstring(L, 1);
    char * fsCode = luaL_checkstring(L, 2);

    Shader result = LoadShaderFromMemory(vsCode, fsCode);

    Shader* result_ptr = (Shader*)lua_newuserdata(L, sizeof(Shader));
    *result_ptr = result;
    luaL_getmetatable(L, "Shader");
    lua_setmetatable(L, -2);
    return 1;
}

// Set shader uniform value
static int lua_SetShaderValue(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");
    int locIndex = luaL_checkinteger(L, 2);
    void* value = lua_touserdata(L, 3);
    int uniformType = luaL_checkinteger(L, 4);

    SetShaderValue(*shader, locIndex, value, uniformType);

    return 0;
}

// Set shader uniform value vector
static int lua_SetShaderValueV(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");
    int locIndex = luaL_checkinteger(L, 2);
    void* value = lua_touserdata(L, 3);
    int uniformType = luaL_checkinteger(L, 4);
    int count = luaL_checkinteger(L, 5);

    SetShaderValueV(*shader, locIndex, value, uniformType, count);

    return 0;
}

// Set shader uniform value (matrix 4x4)
static int lua_SetShaderValueMatrix(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");
    int locIndex = luaL_checkinteger(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    Matrix mat;
    const char* matrix_fields[] = {"m0", "m4", "m8", "m12", "m1", "m5", "m9", "m13", 
                                    "m2", "m6", "m10", "m14", "m3", "m7", "m11", "m15"};
    float* matrix_values = (float*)&mat;
    for (int i = 0; i < 16; i++) {
        lua_getfield(L, 3, matrix_fields[i]);
        matrix_values[i] = luaL_checknumber(L, -1);
        lua_pop(L, 1);
    }

    SetShaderValueMatrix(*shader, locIndex, mat);

    return 0;
}

// Set shader uniform value for texture (sampler2d)
static int lua_SetShaderValueTexture(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");
    int locIndex = luaL_checkinteger(L, 2);
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 3, "Texture2D");

    SetShaderValueTexture(*shader, locIndex, *texture);

    return 0;
}

// Get a ray trace from mouse position
static int lua_GetMouseRay(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 mousePosition = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "position");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 2, "target");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 target = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 2, "up");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 up = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 2, "fovy");
    float fovy = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, 2, "projection");
    int projection = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    Camera3D camera = {position, target, up, fovy, projection};

    Ray result = GetMouseRay(mousePosition, camera);

    lua_newtable(L);
    
    // position field
    lua_newtable(L);
    lua_pushnumber(L, result.position.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.position.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, result.position.z);
    lua_setfield(L, -2, "z");
    lua_setfield(L, -2, "position");
    
    // direction field
    lua_newtable(L);
    lua_pushnumber(L, result.direction.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.direction.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, result.direction.z);
    lua_setfield(L, -2, "z");
    lua_setfield(L, -2, "direction");
    
    return 1;
}

// Get camera transform matrix (view matrix)
static int lua_GetCameraMatrix(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "position");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
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
    Camera3D camera = {position, target, up, fovy, projection};

    Matrix result = GetCameraMatrix(camera);

    lua_newtable(L);
    lua_pushnumber(L, result.m0);
    lua_setfield(L, -2, "m0");
    lua_pushnumber(L, result.m1);
    lua_setfield(L, -2, "m1");
    lua_pushnumber(L, result.m2);
    lua_setfield(L, -2, "m2");
    lua_pushnumber(L, result.m3);
    lua_setfield(L, -2, "m3");
    lua_pushnumber(L, result.m4);
    lua_setfield(L, -2, "m4");
    lua_pushnumber(L, result.m5);
    lua_setfield(L, -2, "m5");
    lua_pushnumber(L, result.m6);
    lua_setfield(L, -2, "m6");
    lua_pushnumber(L, result.m7);
    lua_setfield(L, -2, "m7");
    lua_pushnumber(L, result.m8);
    lua_setfield(L, -2, "m8");
    lua_pushnumber(L, result.m9);
    lua_setfield(L, -2, "m9");
    lua_pushnumber(L, result.m10);
    lua_setfield(L, -2, "m10");
    lua_pushnumber(L, result.m11);
    lua_setfield(L, -2, "m11");
    lua_pushnumber(L, result.m12);
    lua_setfield(L, -2, "m12");
    lua_pushnumber(L, result.m13);
    lua_setfield(L, -2, "m13");
    lua_pushnumber(L, result.m14);
    lua_setfield(L, -2, "m14");
    lua_pushnumber(L, result.m15);
    lua_setfield(L, -2, "m15");
    return 1;
}

// Get camera 2d transform matrix
static int lua_GetCameraMatrix2D(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "offset");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    Vector2 offset = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    lua_getfield(L, 1, "target");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    Vector2 target = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    lua_getfield(L, 1, "rotation");
    float rotation = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, 1, "zoom");
    float zoom = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    Camera2D camera = {offset, target, rotation, zoom};

    Matrix result = GetCameraMatrix2D(camera);

    lua_newtable(L);
    lua_pushnumber(L, result.m0);
    lua_setfield(L, -2, "m0");
    lua_pushnumber(L, result.m1);
    lua_setfield(L, -2, "m1");
    lua_pushnumber(L, result.m2);
    lua_setfield(L, -2, "m2");
    lua_pushnumber(L, result.m3);
    lua_setfield(L, -2, "m3");
    lua_pushnumber(L, result.m4);
    lua_setfield(L, -2, "m4");
    lua_pushnumber(L, result.m5);
    lua_setfield(L, -2, "m5");
    lua_pushnumber(L, result.m6);
    lua_setfield(L, -2, "m6");
    lua_pushnumber(L, result.m7);
    lua_setfield(L, -2, "m7");
    lua_pushnumber(L, result.m8);
    lua_setfield(L, -2, "m8");
    lua_pushnumber(L, result.m9);
    lua_setfield(L, -2, "m9");
    lua_pushnumber(L, result.m10);
    lua_setfield(L, -2, "m10");
    lua_pushnumber(L, result.m11);
    lua_setfield(L, -2, "m11");
    lua_pushnumber(L, result.m12);
    lua_setfield(L, -2, "m12");
    lua_pushnumber(L, result.m13);
    lua_setfield(L, -2, "m13");
    lua_pushnumber(L, result.m14);
    lua_setfield(L, -2, "m14");
    lua_pushnumber(L, result.m15);
    lua_setfield(L, -2, "m15");
    return 1;
}

// Get the screen space position for a 3d world space position
static int lua_GetWorldToScreen(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 worldPosition = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "position");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 cameraPosition = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 2, "target");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 target = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 2, "up");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 up = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 2, "fovy");
    float fovy = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, 2, "projection");
    int projection = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    Camera3D camera = {cameraPosition, target, up, fovy, projection};

    Vector2 result = GetWorldToScreen(worldPosition, camera);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Get the world space position for a 2d camera screen space position
static int lua_GetScreenToWorld2D(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 position = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "offset");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    Vector2 offset = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    lua_getfield(L, 2, "target");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    Vector2 target = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    lua_getfield(L, 2, "rotation");
    float rotation = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, 2, "zoom");
    float zoom = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    Camera2D camera = {offset, target, rotation, zoom};

    Vector2 result = GetScreenToWorld2D(position, camera);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Get size position for a 3d world space position
static int lua_GetWorldToScreenEx(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    lua_getfield(L, 1, "z");
    Vector3 worldPosition = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "position");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 cameraPosition = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 2, "target");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 target = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 2, "up");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 up = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 2, "fovy");
    float fovy = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, 2, "projection");
    int projection = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    Camera3D camera = {cameraPosition, target, up, fovy, projection};
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);

    Vector2 result = GetWorldToScreenEx(worldPosition, camera, width, height);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Get the screen space position for a 2d camera world space position
static int lua_GetWorldToScreen2D(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "x");
    lua_getfield(L, 1, "y");
    Vector2 position = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 2);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "offset");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    Vector2 offset = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    lua_getfield(L, 2, "target");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    Vector2 target = {luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    lua_getfield(L, 2, "rotation");
    float rotation = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, 2, "zoom");
    float zoom = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    Camera2D camera = {offset, target, rotation, zoom};

    Vector2 result = GetWorldToScreen2D(position, camera);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Set target FPS (maximum)
static int lua_SetTargetFPS(lua_State* L) {
    int fps = luaL_checkinteger(L, 1);

    SetTargetFPS(fps);

    return 0;
}

// Get time in seconds for last frame drawn (delta time)
static int lua_GetFrameTime(lua_State* L) {
    float result = GetFrameTime();

    lua_pushnumber(L, result);
    return 1;
}

// Get elapsed time in seconds since InitWindow()
static int lua_GetTime(lua_State* L) {
    double result = GetTime();

    lua_pushnumber(L, result);
    return 1;
}

// Get current FPS
static int lua_GetFPS(lua_State* L) {
    int result = GetFPS();

    lua_pushinteger(L, result);
    return 1;
}

// Set the seed for the random number generator
static int lua_SetRandomSeed(lua_State* L) {
    unsigned int seed = luaL_checkinteger(L, 1);

    SetRandomSeed(seed);

    return 0;
}

// Get a random value between min and max (both included)
static int lua_GetRandomValue(lua_State* L) {
    int min = luaL_checkinteger(L, 1);
    int max = luaL_checkinteger(L, 2);

    int result = GetRandomValue(min, max);

    lua_pushinteger(L, result);
    return 1;
}

// Setup init configuration flags (view FLAGS)
static int lua_SetConfigFlags(lua_State* L) {
    unsigned int flags = luaL_checkinteger(L, 1);

    SetConfigFlags(flags);

    return 0;
}

// Set the current threshold (minimum) log level
static int lua_SetTraceLogLevel(lua_State* L) {
    int logLevel = luaL_checkinteger(L, 1);

    SetTraceLogLevel(logLevel);

    return 0;
}

// Set custom trace log
static int lua_SetTraceLogCallback(lua_State* L) {
    TraceLogCallback callback = (TraceLogCallback)lua_tocfunction(L, 1);

    SetTraceLogCallback(callback);

    return 0;
}

// Set custom file binary data loader
static int lua_SetLoadFileDataCallback(lua_State* L) {
    LoadFileDataCallback callback = (LoadFileDataCallback)lua_tocfunction(L, 1);

    SetLoadFileDataCallback(callback);

    return 0;
}

// Set custom file binary data saver
static int lua_SetSaveFileDataCallback(lua_State* L) {
    SaveFileDataCallback callback = (SaveFileDataCallback)lua_tocfunction(L, 1);

    SetSaveFileDataCallback(callback);

    return 0;
}

// Set custom file text data loader
static int lua_SetLoadFileTextCallback(lua_State* L) {
    LoadFileTextCallback callback = (LoadFileTextCallback)lua_tocfunction(L, 1);

    SetLoadFileTextCallback(callback);

    return 0;
}

// Set custom file text data saver
static int lua_SetSaveFileTextCallback(lua_State* L) {
    SaveFileTextCallback callback = (SaveFileTextCallback)lua_tocfunction(L, 1);

    SetSaveFileTextCallback(callback);

    return 0;
}

// Save data to file from byte array (write), returns true on success
static int lua_SaveFileData(lua_State* L) {
    char * fileName = luaL_checkstring(L, 1);
    size_t dataLength;
    const char* data = luaL_checklstring(L, 2, &dataLength);
    int dataSize = luaL_checkinteger(L, 3);

    bool result = SaveFileData(fileName, (void*)data, dataSize);

    lua_pushboolean(L, result);
    return 1;
}

// Save text data to file (write), string must be '\0' terminated, returns true on success
static int lua_SaveFileText(lua_State* L) {
    char * fileName = luaL_checkstring(L, 1);
    char * text = luaL_checkstring(L, 2);

    bool result = SaveFileText(fileName, text);

    lua_pushboolean(L, result);
    return 1;
}

// Check if file exists
static int lua_FileExists(lua_State* L) {
    char * fileName = luaL_checkstring(L, 1);

    bool result = FileExists(fileName);

    lua_pushboolean(L, result);
    return 1;
}

// Check if a directory path exists
static int lua_DirectoryExists(lua_State* L) {
    char * dirPath = luaL_checkstring(L, 1);

    bool result = DirectoryExists(dirPath);

    lua_pushboolean(L, result);
    return 1;
}

// Load directory filepaths
static int lua_LoadDirectoryFiles(lua_State* L) {
    char * dirPath = luaL_checkstring(L, 1);

    FilePathList result = LoadDirectoryFiles(dirPath);

    lua_newtable(L);
    lua_pushinteger(L, result.capacity);
    lua_setfield(L, -2, "capacity");
    lua_pushinteger(L, result.count);
    lua_setfield(L, -2, "count");
    
    // Create paths array
    lua_newtable(L);
    for (unsigned int i = 0; i < result.count; i++) {
        lua_pushstring(L, result.paths[i]);
        lua_rawseti(L, -2, i + 1);
    }
    lua_setfield(L, -2, "paths");
    
    return 1;
}

// Load directory filepaths with extension filtering and recursive directory scan
static int lua_LoadDirectoryFilesEx(lua_State* L) {
    char * basePath = luaL_checkstring(L, 1);
    char * filter = luaL_checkstring(L, 2);
    bool scanSubdirs = lua_toboolean(L, 3);

    FilePathList result = LoadDirectoryFilesEx(basePath, filter, scanSubdirs);

    lua_newtable(L);
    lua_pushinteger(L, result.capacity);
    lua_setfield(L, -2, "capacity");
    lua_pushinteger(L, result.count);
    lua_setfield(L, -2, "count");
    
    // Create paths array
    lua_newtable(L);
    for (unsigned int i = 0; i < result.count; i++) {
        lua_pushstring(L, result.paths[i]);
        lua_rawseti(L, -2, i + 1);
    }
    lua_setfield(L, -2, "paths");
    
    return 1;
}

// Load dropped filepaths
static int lua_LoadDroppedFiles(lua_State* L) {
    FilePathList result = LoadDroppedFiles();

    lua_newtable(L);
    lua_pushinteger(L, result.capacity);
    lua_setfield(L, -2, "capacity");
    lua_pushinteger(L, result.count);
    lua_setfield(L, -2, "count");
    
    // Create paths array
    lua_newtable(L);
    for (unsigned int i = 0; i < result.count; i++) {
        lua_pushstring(L, result.paths[i]);
        lua_rawseti(L, -2, i + 1);
    }
    lua_setfield(L, -2, "paths");
    
    return 1;
}

// Load automation events list from file, NULL for empty list, capacity = MAX_AUTOMATION_EVENTS
static int lua_LoadAutomationEventList(lua_State* L) {
    char * fileName = luaL_checkstring(L, 1);

    AutomationEventList result = LoadAutomationEventList(fileName);

    lua_newtable(L);
    lua_pushinteger(L, result.capacity);
    lua_setfield(L, -2, "capacity");
    lua_pushinteger(L, result.count);
    lua_setfield(L, -2, "count");
    
    // Create events array
    lua_newtable(L);
    for (unsigned int i = 0; i < result.count; i++) {
        lua_newtable(L);
        lua_pushinteger(L, result.events[i].frame);
        lua_setfield(L, -2, "frame");
        lua_pushinteger(L, result.events[i].type);
        lua_setfield(L, -2, "type");
        
        // Create params array
        lua_newtable(L);
        for (int j = 0; j < 4; j++) {
            lua_pushinteger(L, result.events[i].params[j]);
            lua_rawseti(L, -2, j + 1);
        }
        lua_setfield(L, -2, "params");
        
        lua_rawseti(L, -2, i + 1);
    }
    lua_setfield(L, -2, "events");
    
    return 1;
}

// Set automation event list to record to
static int lua_SetAutomationEventList(lua_State* L) {
    AutomationEventList* list = (AutomationEventList*)luaL_checkudata(L, 1, "AutomationEventList");

    SetAutomationEventList(list);

    return 0;
}

// Set automation event internal base frame to start recording
static int lua_SetAutomationEventBaseFrame(lua_State* L) {
    int frame = luaL_checkinteger(L, 1);

    SetAutomationEventBaseFrame(frame);

    return 0;
}

// Check if a key has been pressed once
static int lua_IsKeyPressed(lua_State* L) {
    int key = luaL_checkinteger(L, 1);

    bool result = IsKeyPressed(key);

    lua_pushboolean(L, result);
    return 1;
}

// Check if a key has been pressed again (Only PLATFORM_DESKTOP)
static int lua_IsKeyPressedRepeat(lua_State* L) {
    int key = luaL_checkinteger(L, 1);

    bool result = IsKeyPressedRepeat(key);

    lua_pushboolean(L, result);
    return 1;
}

// Check if a key is being pressed
static int lua_IsKeyDown(lua_State* L) {
    int key = luaL_checkinteger(L, 1);

    bool result = IsKeyDown(key);

    lua_pushboolean(L, result);
    return 1;
}

// Check if a key has been released once
static int lua_IsKeyReleased(lua_State* L) {
    int key = luaL_checkinteger(L, 1);

    bool result = IsKeyReleased(key);

    lua_pushboolean(L, result);
    return 1;
}

// Check if a key is NOT being pressed
static int lua_IsKeyUp(lua_State* L) {
    int key = luaL_checkinteger(L, 1);

    bool result = IsKeyUp(key);

    lua_pushboolean(L, result);
    return 1;
}

// Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
static int lua_GetKeyPressed(lua_State* L) {
    int result = GetKeyPressed();

    lua_pushinteger(L, result);
    return 1;
}

// Set a custom key to exit program (default is ESC)
static int lua_SetExitKey(lua_State* L) {
    int key = luaL_checkinteger(L, 1);

    SetExitKey(key);

    return 0;
}

// Check if a gamepad is available
static int lua_IsGamepadAvailable(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);

    bool result = IsGamepadAvailable(gamepad);

    lua_pushboolean(L, result);
    return 1;
}

// Check if a gamepad button has been pressed once
static int lua_IsGamepadButtonPressed(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);
    int button = luaL_checkinteger(L, 2);

    bool result = IsGamepadButtonPressed(gamepad, button);

    lua_pushboolean(L, result);
    return 1;
}

// Check if a gamepad button is being pressed
static int lua_IsGamepadButtonDown(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);
    int button = luaL_checkinteger(L, 2);

    bool result = IsGamepadButtonDown(gamepad, button);

    lua_pushboolean(L, result);
    return 1;
}

// Check if a gamepad button has been released once
static int lua_IsGamepadButtonReleased(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);
    int button = luaL_checkinteger(L, 2);

    bool result = IsGamepadButtonReleased(gamepad, button);

    lua_pushboolean(L, result);
    return 1;
}

// Check if a gamepad button is NOT being pressed
static int lua_IsGamepadButtonUp(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);
    int button = luaL_checkinteger(L, 2);

    bool result = IsGamepadButtonUp(gamepad, button);

    lua_pushboolean(L, result);
    return 1;
}

// Get the last gamepad button pressed
static int lua_GetGamepadButtonPressed(lua_State* L) {
    int result = GetGamepadButtonPressed();

    lua_pushinteger(L, result);
    return 1;
}

// Get gamepad axis count for a gamepad
static int lua_GetGamepadAxisCount(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);

    int result = GetGamepadAxisCount(gamepad);

    lua_pushinteger(L, result);
    return 1;
}

// Get axis movement value for a gamepad axis
static int lua_GetGamepadAxisMovement(lua_State* L) {
    int gamepad = luaL_checkinteger(L, 1);
    int axis = luaL_checkinteger(L, 2);

    float result = GetGamepadAxisMovement(gamepad, axis);

    lua_pushnumber(L, result);
    return 1;
}

// Set internal gamepad mappings (SDL_GameControllerDB)
static int lua_SetGamepadMappings(lua_State* L) {
    char * mappings = luaL_checkstring(L, 1);

    int result = SetGamepadMappings(mappings);

    lua_pushinteger(L, result);
    return 1;
}

// Check if a mouse button has been pressed once
static int lua_IsMouseButtonPressed(lua_State* L) {
    int button = luaL_checkinteger(L, 1);

    bool result = IsMouseButtonPressed(button);

    lua_pushboolean(L, result);
    return 1;
}

// Check if a mouse button is being pressed
static int lua_IsMouseButtonDown(lua_State* L) {
    int button = luaL_checkinteger(L, 1);

    bool result = IsMouseButtonDown(button);

    lua_pushboolean(L, result);
    return 1;
}

// Check if a mouse button has been released once
static int lua_IsMouseButtonReleased(lua_State* L) {
    int button = luaL_checkinteger(L, 1);

    bool result = IsMouseButtonReleased(button);

    lua_pushboolean(L, result);
    return 1;
}

// Check if a mouse button is NOT being pressed
static int lua_IsMouseButtonUp(lua_State* L) {
    int button = luaL_checkinteger(L, 1);

    bool result = IsMouseButtonUp(button);

    lua_pushboolean(L, result);
    return 1;
}

// Get mouse position X
static int lua_GetMouseX(lua_State* L) {
    int result = GetMouseX();

    lua_pushinteger(L, result);
    return 1;
}

// Get mouse position Y
static int lua_GetMouseY(lua_State* L) {
    int result = GetMouseY();

    lua_pushinteger(L, result);
    return 1;
}

// Get mouse position XY
static int lua_GetMousePosition(lua_State* L) {
    Vector2 result = GetMousePosition();

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Get mouse delta between frames
static int lua_GetMouseDelta(lua_State* L) {
    Vector2 result = GetMouseDelta();

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Set mouse position XY
static int lua_SetMousePosition(lua_State* L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);

    SetMousePosition(x, y);

    return 0;
}

// Set mouse offset
static int lua_SetMouseOffset(lua_State* L) {
    int offsetX = luaL_checkinteger(L, 1);
    int offsetY = luaL_checkinteger(L, 2);

    SetMouseOffset(offsetX, offsetY);

    return 0;
}

// Set mouse scaling
static int lua_SetMouseScale(lua_State* L) {
    float scaleX = luaL_checknumber(L, 1);
    float scaleY = luaL_checknumber(L, 2);

    SetMouseScale(scaleX, scaleY);

    return 0;
}

// Get mouse wheel movement for X or Y, whichever is larger
static int lua_GetMouseWheelMove(lua_State* L) {
    float result = GetMouseWheelMove();

    lua_pushnumber(L, result);
    return 1;
}

// Get mouse wheel movement for both X and Y
static int lua_GetMouseWheelMoveV(lua_State* L) {
    Vector2 result = GetMouseWheelMoveV();

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Set mouse cursor
static int lua_SetMouseCursor(lua_State* L) {
    int cursor = luaL_checkinteger(L, 1);

    SetMouseCursor(cursor);

    return 0;
}

// Get touch position X for touch point 0 (relative to screen size)
static int lua_GetTouchX(lua_State* L) {
    int result = GetTouchX();

    lua_pushinteger(L, result);
    return 1;
}

// Get touch position Y for touch point 0 (relative to screen size)
static int lua_GetTouchY(lua_State* L) {
    int result = GetTouchY();

    lua_pushinteger(L, result);
    return 1;
}

// Get touch position XY for a touch point index (relative to screen size)
static int lua_GetTouchPosition(lua_State* L) {
    int index = luaL_checkinteger(L, 1);

    Vector2 result = GetTouchPosition(index);

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Get touch point identifier for given index
static int lua_GetTouchPointId(lua_State* L) {
    int index = luaL_checkinteger(L, 1);

    int result = GetTouchPointId(index);

    lua_pushinteger(L, result);
    return 1;
}

// Get number of touch points
static int lua_GetTouchPointCount(lua_State* L) {
    int result = GetTouchPointCount();

    lua_pushinteger(L, result);
    return 1;
}

// Enable a set of gestures using flags
static int lua_SetGesturesEnabled(lua_State* L) {
    unsigned int flags = luaL_checkinteger(L, 1);

    SetGesturesEnabled(flags);

    return 0;
}

// Check if a gesture have been detected
static int lua_IsGestureDetected(lua_State* L) {
    unsigned int gesture = luaL_checkinteger(L, 1);

    bool result = IsGestureDetected(gesture);

    lua_pushboolean(L, result);
    return 1;
}

// Get latest detected gesture
static int lua_GetGestureDetected(lua_State* L) {
    int result = GetGestureDetected();

    lua_pushinteger(L, result);
    return 1;
}

// Get gesture hold time in milliseconds
static int lua_GetGestureHoldDuration(lua_State* L) {
    float result = GetGestureHoldDuration();

    lua_pushnumber(L, result);
    return 1;
}

// Get gesture drag vector
static int lua_GetGestureDragVector(lua_State* L) {
    Vector2 result = GetGestureDragVector();

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Get gesture drag angle
static int lua_GetGestureDragAngle(lua_State* L) {
    float result = GetGestureDragAngle();

    lua_pushnumber(L, result);
    return 1;
}

// Get gesture pinch delta
static int lua_GetGesturePinchVector(lua_State* L) {
    Vector2 result = GetGesturePinchVector();

    lua_newtable(L);
    lua_pushnumber(L, result.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Get gesture pinch angle
static int lua_GetGesturePinchAngle(lua_State* L) {
    float result = GetGesturePinchAngle();

    lua_pushnumber(L, result);
    return 1;
}

// Update camera position for selected mode
static int lua_UpdateCamera(lua_State* L) {
    Camera3D* camera = (Camera3D*)luaL_checkudata(L, 1, "Camera3D");
    int mode = luaL_checkinteger(L, 2);

    UpdateCamera(camera, mode);

    return 0;
}

// Update camera movement/rotation
static int lua_UpdateCameraPro(lua_State* L) {
    Camera3D* camera = (Camera3D*)luaL_checkudata(L, 1, "Camera3D");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 movement = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "z");
    Vector3 rotation = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float zoom = luaL_checknumber(L, 4);

    UpdateCameraPro(camera, movement, rotation, zoom);

    return 0;
}

// Set texture and rectangle to be used on shapes drawing
static int lua_SetShapesTexture(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "width");
    lua_getfield(L, 2, "height");
    Rectangle source = {luaL_checknumber(L, -4), luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);

    SetShapesTexture(*texture, source);

    return 0;
}

// Set texture scaling filter mode
static int lua_SetTextureFilter(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    int filter = luaL_checkinteger(L, 2);

    SetTextureFilter(*texture, filter);

    return 0;
}

// Set texture wrapping mode
static int lua_SetTextureWrap(lua_State* L) {
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    int wrap = luaL_checkinteger(L, 2);

    SetTextureWrap(*texture, wrap);

    return 0;
}

// Set color formatted into destination pixel pointer
static int lua_SetPixelColor(lua_State* L) {
    void* dstPtr = lua_touserdata(L, 1);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "r");
    lua_getfield(L, 2, "g");
    lua_getfield(L, 2, "b");
    lua_getfield(L, 2, "a");
    Color color = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);
    int format = luaL_checkinteger(L, 3);

    SetPixelColor(dstPtr, color, format);

    return 0;
}

// Set vertical line spacing when drawing with line-breaks
static int lua_SetTextLineSpacing(lua_State* L) {
    int spacing = luaL_checkinteger(L, 1);

    SetTextLineSpacing(spacing);

    return 0;
}

// Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...)
static int lua_SetMaterialTexture(lua_State* L) {
    Material* material = (Material*)luaL_checkudata(L, 1, "Material");
    int mapType = luaL_checkinteger(L, 2);
    Texture2D* texture = (Texture2D*)luaL_checkudata(L, 3, "Texture2D");

    SetMaterialTexture(material, mapType, *texture);

    return 0;
}

// Set material for a mesh
static int lua_SetModelMeshMaterial(lua_State* L) {
    Model* model = (Model*)luaL_checkudata(L, 1, "Model");
    int meshId = luaL_checkinteger(L, 2);
    int materialId = luaL_checkinteger(L, 3);

    SetModelMeshMaterial(model, meshId, materialId);

    return 0;
}

// Set master volume (listener)
static int lua_SetMasterVolume(lua_State* L) {
    float volume = luaL_checknumber(L, 1);

    SetMasterVolume(volume);

    return 0;
}

// Set volume for a sound (1.0 is max level)
static int lua_SetSoundVolume(lua_State* L) {
    Sound* sound = (Sound*)luaL_checkudata(L, 1, "Sound");
    float volume = luaL_checknumber(L, 2);

    SetSoundVolume(*sound, volume);

    return 0;
}

// Set pitch for a sound (1.0 is base level)
static int lua_SetSoundPitch(lua_State* L) {
    Sound* sound = (Sound*)luaL_checkudata(L, 1, "Sound");
    float pitch = luaL_checknumber(L, 2);

    SetSoundPitch(*sound, pitch);

    return 0;
}

// Set pan for a sound (0.5 is center)
static int lua_SetSoundPan(lua_State* L) {
    Sound* sound = (Sound*)luaL_checkudata(L, 1, "Sound");
    float pan = luaL_checknumber(L, 2);

    SetSoundPan(*sound, pan);

    return 0;
}

// Set volume for music (1.0 is max level)
static int lua_SetMusicVolume(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");
    float volume = luaL_checknumber(L, 2);

    SetMusicVolume(*music, volume);

    return 0;
}

// Set pitch for a music (1.0 is base level)
static int lua_SetMusicPitch(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");
    float pitch = luaL_checknumber(L, 2);

    SetMusicPitch(*music, pitch);

    return 0;
}

// Set pan for a music (0.5 is center)
static int lua_SetMusicPan(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");
    float pan = luaL_checknumber(L, 2);

    SetMusicPan(*music, pan);

    return 0;
}

// Set volume for audio stream (1.0 is max level)
static int lua_SetAudioStreamVolume(lua_State* L) {
    AudioStream* stream = (AudioStream*)luaL_checkudata(L, 1, "AudioStream");
    float volume = luaL_checknumber(L, 2);

    SetAudioStreamVolume(*stream, volume);

    return 0;
}

// Set pitch for audio stream (1.0 is base level)
static int lua_SetAudioStreamPitch(lua_State* L) {
    AudioStream* stream = (AudioStream*)luaL_checkudata(L, 1, "AudioStream");
    float pitch = luaL_checknumber(L, 2);

    SetAudioStreamPitch(*stream, pitch);

    return 0;
}

// Set pan for audio stream (0.5 is centered)
static int lua_SetAudioStreamPan(lua_State* L) {
    AudioStream* stream = (AudioStream*)luaL_checkudata(L, 1, "AudioStream");
    float pan = luaL_checknumber(L, 2);

    SetAudioStreamPan(*stream, pan);

    return 0;
}

// Default size for new audio streams
static int lua_SetAudioStreamBufferSizeDefault(lua_State* L) {
    int size = luaL_checkinteger(L, 1);

    SetAudioStreamBufferSizeDefault(size);

    return 0;
}

// Audio thread callback to request new data
static int lua_SetAudioStreamCallback(lua_State* L) {
    AudioStream* stream = (AudioStream*)luaL_checkudata(L, 1, "AudioStream");
    AudioCallback callback = (AudioCallback)lua_tocfunction(L, 2);

    SetAudioStreamCallback(*stream, callback);

    return 0;
}


// Metatable definitions for userdata used in this module
static int Shader_gc(lua_State* L) {
    Shader* obj = (Shader*)luaL_checkudata(L, 1, "Shader");
    if (obj != NULL) {
        UnloadShader(*obj);
    }
    return 0;
}

static void create_Shader_metatable(lua_State* L) {
    luaL_newmetatable(L, "Shader");
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, Shader_gc);
    lua_settable(L, -3);
    lua_pop(L, 1);  // Remove metatable from stack
}

// Additional metatables for userdata types
static void create_Image_metatable(lua_State* L) {
    luaL_newmetatable(L, "Image");
    lua_pop(L, 1);  // Remove metatable from stack
}

static void create_Texture2D_metatable(lua_State* L) {
    luaL_newmetatable(L, "Texture2D");
    lua_pop(L, 1);  // Remove metatable from stack
}

/*

// Camera, defines position/orientation in 3d space
typedef struct Camera3D {
    Vector3 position;       // Camera position
    Vector3 target;         // Camera target it looks-at
    Vector3 up;             // Camera up vector (rotation over its axis)
    float fovy;             // Camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic
    int projection;         // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
} Camera3D;

typedef Camera3D Camera;    // Camera type fallback, defaults to Camera3D

//i need make camera in lua whit metatable to akces field

static int lua_CreateCamera3D(lua_State* L) {
    Camera3D* camera = (Camera3D*)lua_newuserdata(L, sizeof(Camera3D));
    luaL_getmetatable(L, "Camera3D");
    lua_setmetatable(L, -2);

    // Initialize camera with default values
    camera->position = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera->target = (Vector3){ 0.0f, 0.0f, 1.0f };
    camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera->fovy = 45.0f;
    camera->projection = CAMERA_PERSPECTIVE;

    return 1; // Return the new camera userdata
}
    
*/
//i need make camera in lua whit metatable to akces field
/* static int Camera3D_gc(lua_State* L) {
    // No dynamic memory to free for Camera3D, but function must exist for __gc
    return 0;
}
static int lua_CreateCamera3D(lua_State* L) {
    Camera3D* camera = (Camera3D*)lua_newuserdata(L, sizeof(Camera3D));
    luaL_getmetatable(L, "Camera3D");
    lua_setmetatable(L, -2);

    // Initialize camera with default values
    camera->position = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera->target = (Vector3){ 0.0f, 0.0f, 1.0f };
    camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera->fovy = 45.0f;
    camera->projection = CAMERA_PERSPECTIVE;

    return 1; // Return the new camera userdata
}

static int Camera3D_index(lua_State* L) {
    Camera3D* camera = (Camera3D*)luaL_checkudata(L, 1, "Camera3D");
    const char* key = luaL_checkstring(L, 2);

    if (strcmp(key, "position") == 0) {
        // Push position as a table or userdata
    } else if (strcmp(key, "target") == 0) {
        // Push target
    } else if (strcmp(key, "up") == 0) {
        // Push up
    } else if (strcmp(key, "fovy") == 0) {
        lua_pushnumber(L, camera->fovy);
    } else if (strcmp(key, "projection") == 0) {
        lua_pushinteger(L, camera->projection);
    } else {
        lua_pushnil(L);
    }
    return 1;
}
//void UpdateCameraGamepadFPS(Camera *camera, float *yaw, float *pitch, float moveSpeed, float lookSpeed)
static int lua_UpdateCameraGamepadFPS(lua_State* L) {
    Camera3D* camera = (Camera3D*)luaL_checkudata(L, 1, "Camera3D");
    float yaw = (float)luaL_checknumber(L, 2);
    float pitch = (float)luaL_checknumber(L, 3);
    float moveSpeed = (float)luaL_checknumber(L, 4);
    float lookSpeed = (float)luaL_checknumber(L, 5);

    UpdateCameraGamepadFPS(camera, &yaw, &pitch, moveSpeed, lookSpeed);

    // Jeśli chcesz zwracać zaktualizowane yaw/pitch do Lua:
    lua_pushnumber(L, yaw);
    lua_pushnumber(L, pitch);
    return 2;
}

static int Camera3D_newindex(lua_State* L) {
    Camera3D* camera = (Camera3D*)luaL_checkudata(L, 1, "Camera3D");
    const char* key = luaL_checkstring(L, 2);

    if (strcmp(key, "position") == 0 && lua_istable(L, 3)) {
        lua_getfield(L, 3, "x"); camera->position.x = (float)lua_tonumber(L, -1); lua_pop(L, 1);
        lua_getfield(L, 3, "y"); camera->position.y = (float)lua_tonumber(L, -1); lua_pop(L, 1);
        lua_getfield(L, 3, "z"); camera->position.z = (float)lua_tonumber(L, -1); lua_pop(L, 1);
    } else if (strcmp(key, "target") == 0 && lua_istable(L, 3)) {
        lua_getfield(L, 3, "x"); camera->target.x = (float)lua_tonumber(L, -1); lua_pop(L, 1);
        lua_getfield(L, 3, "y"); camera->target.y = (float)lua_tonumber(L, -1); lua_pop(L, 1);
        lua_getfield(L, 3, "z"); camera->target.z = (float)lua_tonumber(L, -1); lua_pop(L, 1);
    } else if (strcmp(key, "up") == 0 && lua_istable(L, 3)) {
        lua_getfield(L, 3, "x"); camera->up.x = (float)lua_tonumber(L, -1); lua_pop(L, 1);
        lua_getfield(L, 3, "y"); camera->up.y = (float)lua_tonumber(L, -1); lua_pop(L, 1);
        lua_getfield(L, 3, "z"); camera->up.z = (float)lua_tonumber(L, -1); lua_pop(L, 1);
    } else if (strcmp(key, "fovy") == 0) {
        camera->fovy = (float)lua_tonumber(L, 3);
    } else if (strcmp(key, "projection") == 0) {
        camera->projection = (int)lua_tointeger(L, 3);
    }
    return 0;
}

static void create_Camera3D_metatable(lua_State* L) {
    luaL_newmetatable(L, "Camera3D");
    lua_pushstring(L, "__index");
    lua_pushcfunction(L, Camera3D_index);
    lua_settable(L, -3);
    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, Camera3D_newindex);
    lua_settable(L, -3);
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, Camera3D_gc);
    lua_settable(L, -3);
    lua_pop(L, 1);  // Remove metatable from stack

} */

// Add this function definition before create_Camera3D_metatable or at the top with other gc functions

// --- helpers: Vector3 <-> Lua table ---
static void push_vec3(lua_State* L, Vector3 v){
    lua_newtable(L);
    lua_pushnumber(L, v.x); lua_setfield(L, -2, "x");
    lua_pushnumber(L, v.y); lua_setfield(L, -2, "y");
    lua_pushnumber(L, v.z); lua_setfield(L, -2, "z");
}
static int get_vec3(lua_State* L, int idx, Vector3* out){
    if (!lua_istable(L, idx)) return 0;
    lua_getfield(L, idx, "x"); out->x = (float)luaL_optnumber(L, -1, 0); lua_pop(L,1);
    lua_getfield(L, idx, "y"); out->y = (float)luaL_optnumber(L, -1, 0); lua_pop(L,1);
    lua_getfield(L, idx, "z"); out->z = (float)luaL_optnumber(L, -1, 0); lua_pop(L,1);
    return 1;
}

// --- Camera3D metatable ---
static int Camera3D_gc(lua_State* L){ return 0; }

static int Camera3D_index(lua_State* L){
    Camera3D* cam = (Camera3D*)luaL_checkudata(L, 1, "Camera3D");
    const char* k = luaL_checkstring(L, 2);
    if (!strcmp(k,"position"))    { push_vec3(L, cam->position);   return 1; }
    if (!strcmp(k,"target"))      { push_vec3(L, cam->target);     return 1; }
    if (!strcmp(k,"up"))          { push_vec3(L, cam->up);         return 1; }
    if (!strcmp(k,"fovy"))        { lua_pushnumber(L, cam->fovy);  return 1; }
    if (!strcmp(k,"projection"))  { lua_pushinteger(L, cam->projection); return 1; }
    lua_pushnil(L); return 1;
}

static int Camera3D_newindex(lua_State* L){
    Camera3D* cam = (Camera3D*)luaL_checkudata(L, 1, "Camera3D");
    const char* k = luaL_checkstring(L, 2);
    if (!strcmp(k,"position"))    { Vector3 v; if(get_vec3(L,3,&v)) cam->position=v; return 0; }
    if (!strcmp(k,"target"))      { Vector3 v; if(get_vec3(L,3,&v)) cam->target=v;   return 0; }
    if (!strcmp(k,"up"))          { Vector3 v; if(get_vec3(L,3,&v)) cam->up=v;       return 0; }
    if (!strcmp(k,"fovy"))        { cam->fovy = (float)luaL_checknumber(L,3);        return 0; }
    if (!strcmp(k,"projection"))  { cam->projection = (int)luaL_checkinteger(L,3);   return 0; }
    return 0;
}


// --- konstruktor: rcore.CreateCamera3D() ---
static int lua_CreateCamera3D(lua_State* L){
    Camera3D* cam = (Camera3D*)lua_newuserdata(L, sizeof(Camera3D));
    cam->position = (Vector3){10,10,10};
    cam->target   = (Vector3){0,0,0};
    cam->up       = (Vector3){0,1,0};
    cam->fovy     = 60.0f;
    cam->projection = CAMERA_PERSPECTIVE;
    luaL_getmetatable(L, "Camera3D");
    lua_setmetatable(L, -2);
    return 1;
}


static void create_Camera3D_metatable(lua_State* L){
    if (luaL_newmetatable(L, "Camera3D")){
        lua_pushcfunction(L, Camera3D_index);    lua_setfield(L, -2, "__index");
        lua_pushcfunction(L, Camera3D_newindex); lua_setfield(L, -2, "__newindex");
        lua_pushcfunction(L, Camera3D_gc);       lua_setfield(L, -2, "__gc");
    }
    lua_pop(L,1);
}

// Lua: rcore.UpdateCameraGamepadFPS(camera, yaw, pitch, moveSpeed, lookSpeed) -> newYaw, newPitch
static int lua_UpdateCameraGamepadFPS(lua_State* L){
    Camera3D* cam = (Camera3D*)luaL_checkudata(L, 1, "Camera3D");
    float yaw   = (float)luaL_checknumber(L, 2);
    float pitch = (float)luaL_checknumber(L, 3);
    float move  = (float)luaL_checknumber(L, 4);
    float look  = (float)luaL_checknumber(L, 5);
    UpdateCameraGamepadFPS(cam, &yaw, &pitch, move, look);
    lua_pushnumber(L, yaw);
    lua_pushnumber(L, pitch);
    return 2;
}

static void create_AutomationEventList_metatable(lua_State* L) {
    luaL_newmetatable(L, "AutomationEventList");
    lua_pop(L, 1);  // Remove metatable from stack
}

static void create_Material_metatable(lua_State* L) {
    luaL_newmetatable(L, "Material");
    lua_pop(L, 1);  // Remove metatable from stack
}

static void create_Model_metatable(lua_State* L) {
    luaL_newmetatable(L, "Model");
    lua_pop(L, 1);  // Remove metatable from stack
}

static void create_Sound_metatable(lua_State* L) {
    luaL_newmetatable(L, "Sound");
    lua_pop(L, 1);  // Remove metatable from stack
}

static void create_Music_metatable(lua_State* L) {
    luaL_newmetatable(L, "Music");
    lua_pop(L, 1);  // Remove metatable from stack
}

static void create_AudioStream_metatable(lua_State* L) {
    luaL_newmetatable(L, "AudioStream");
    lua_pop(L, 1);  // Remove metatable from stack

}

static void create_VrStereoConfig_metatable(lua_State* L) {
    luaL_newmetatable(L, "VrStereoConfig");
    lua_pop(L, 1);  // Remove metatable from stack
}

int lua_GetFileAndFolderList(lua_State* L) {
    const char* path = luaL_checkstring(L, 1);
    int count = 0;
    char** files = GetFileAndFolderList(path, &count);

    lua_newtable(L);
    for (int i = 0; i < count; ++i) {
        lua_pushstring(L, files[i]);
        lua_rawseti(L, -2, i + 1);
        free(files[i]);
    }
    free(files);
    return 1; // tabela
}

// Get uniform location
static int lua_GetShaderLocation(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");
    const char* name = luaL_checkstring(L, 2);
    int loc = GetShaderLocation(*shader, name);
    lua_pushinteger(L, loc);
    return 1;
}

// Set one float
static int lua_SetShaderValueFloat(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");
    int locIndex   = luaL_checkinteger(L, 2);
    float v        = (float)luaL_checknumber(L, 3);
    SetShaderValue(*shader, locIndex, &v, SHADER_UNIFORM_FLOAT);
    return 0;
}

// Set one int
static int lua_SetShaderValueInt(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");
    int locIndex   = luaL_checkinteger(L, 2);
    int v          = luaL_checkinteger(L, 3);
    SetShaderValue(*shader, locIndex, &v, SHADER_UNIFORM_INT);
    return 0;
}

// Set vec2/vec3/vec4 from Lua table {x=,y=,(z=),(w=)}
static int lua_SetShaderValueVec(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");
    int locIndex   = luaL_checkinteger(L, 2);
    int comps      = luaL_checkinteger(L, 4); // 2,3,4
    luaL_checktype(L, 3, LUA_TTABLE);

    float tmp[4] = {0,0,0,0};
    const char* keys[4] = {"x","y","z","w"};
    for (int i = 0; i < comps; ++i) {
        lua_getfield(L, 3, keys[i]);
        tmp[i] = (float)luaL_checknumber(L, -1);
        lua_pop(L, 1);
    }

    int type = (comps==2)?SHADER_UNIFORM_VEC2:(comps==3)?SHADER_UNIFORM_VEC3:SHADER_UNIFORM_VEC4;
    SetShaderValue(*shader, locIndex, tmp, type);
    return 0;
}

// Set ivec2/ivec3/ivec4 from Lua table {x=,y=,(z=),(w=)}
static int lua_SetShaderValueIVec(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");
    int locIndex   = luaL_checkinteger(L, 2);
    int comps      = luaL_checkinteger(L, 4); // 2,3,4
    luaL_checktype(L, 3, LUA_TTABLE);

    int tmp[4] = {0,0,0,0};
    const char* keys[4] = {"x","y","z","w"};
    for (int i = 0; i < comps; ++i) {
        lua_getfield(L, 3, keys[i]);
        tmp[i] = luaL_checkinteger(L, -1);
        lua_pop(L, 1);
    }

    int type = (comps==2)?SHADER_UNIFORM_IVEC2:(comps==3)?SHADER_UNIFORM_IVEC3:SHADER_UNIFORM_IVEC4;
    SetShaderValueV(*shader, locIndex, tmp, type, 1);
    return 0;
}

// Set mat4 from Lua table z polami m0..m15 (tak jak już robisz w innych miejscach)
static int lua_SetShaderValueMat4(lua_State* L) {
    Shader* shader = (Shader*)luaL_checkudata(L, 1, "Shader");
    int locIndex   = luaL_checkinteger(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    Matrix mat;
    const char* fields[] = {"m0","m4","m8","m12","m1","m5","m9","m13","m2","m6","m10","m14","m3","m7","m11","m15"};
    float* mv = (float*)&mat;
    for (int i=0;i<16;i++){ lua_getfield(L, 3, fields[i]); mv[i]=(float)luaL_checknumber(L,-1); lua_pop(L,1); }
    SetShaderValueMatrix(*shader, locIndex, mat);
    return 0;
}


static const struct luaL_Reg rcore_functions[] = {
    {"InitWindow", lua_InitWindow},
    {"CloseWindow", lua_CloseWindow},
    {"WindowShouldClose", lua_WindowShouldClose},
    {"SetWindowState", lua_SetWindowState},
    {"ClearWindowState", lua_ClearWindowState},
    {"SetWindowIcon", lua_SetWindowIcon},
    {"SetWindowIcons", lua_SetWindowIcons},
    {"SetWindowTitle", lua_SetWindowTitle},
    {"SetWindowPosition", lua_SetWindowPosition},
    {"SetWindowMonitor", lua_SetWindowMonitor},
    {"SetWindowMinSize", lua_SetWindowMinSize},
    {"SetWindowMaxSize", lua_SetWindowMaxSize},
    {"SetWindowSize", lua_SetWindowSize},
    {"SetWindowOpacity", lua_SetWindowOpacity},
    {"SetWindowFocused", lua_SetWindowFocused},
    {"SetClipboardText", lua_SetClipboardText},
    {"EnableEventWaiting", lua_EnableEventWaiting},
    {"DisableEventWaiting", lua_DisableEventWaiting},
    {"ShowCursor", lua_ShowCursor},
    {"HideCursor", lua_HideCursor},
    {"IsCursorHidden", lua_IsCursorHidden},
    {"EnableCursor", lua_EnableCursor},
    {"DisableCursor", lua_DisableCursor},
    {"IsCursorOnScreen", lua_IsCursorOnScreen},
    {"ClearBackground", lua_ClearBackground},
    {"BeginDrawing", lua_BeginDrawing},
    {"EndDrawing", lua_EndDrawing},
    {"BeginMode2D", lua_BeginMode2D},
    {"EndMode2D", lua_EndMode2D},
    {"BeginMode3D", lua_BeginMode3D},
    {"EndMode3D", lua_EndMode3D},
    {"LoadVrStereoConfig", lua_LoadVrStereoConfig},
    {"LoadShader", lua_LoadShader},
    {"LoadShaderFromMemory", lua_LoadShaderFromMemory},
    {"SetShaderValue", lua_SetShaderValue},
    {"SetShaderValueV", lua_SetShaderValueV},
    {"SetShaderValueMatrix", lua_SetShaderValueMatrix},
    {"SetShaderValueTexture", lua_SetShaderValueTexture},
    {"GetMouseRay", lua_GetMouseRay},
    {"GetCameraMatrix", lua_GetCameraMatrix},
    {"GetCameraMatrix2D", lua_GetCameraMatrix2D},
    {"GetWorldToScreen", lua_GetWorldToScreen},
    {"GetScreenToWorld2D", lua_GetScreenToWorld2D},
    {"GetWorldToScreenEx", lua_GetWorldToScreenEx},
    {"GetWorldToScreen2D", lua_GetWorldToScreen2D},
    {"SetTargetFPS", lua_SetTargetFPS},
    {"GetFrameTime", lua_GetFrameTime},
    {"GetTime", lua_GetTime},
    {"GetFPS", lua_GetFPS},
    {"SetRandomSeed", lua_SetRandomSeed},
    {"GetRandomValue", lua_GetRandomValue},
    {"SetConfigFlags", lua_SetConfigFlags},
    {"SetTraceLogLevel", lua_SetTraceLogLevel},
    {"SetTraceLogCallback", lua_SetTraceLogCallback},
    {"SetLoadFileDataCallback", lua_SetLoadFileDataCallback},
    {"SetSaveFileDataCallback", lua_SetSaveFileDataCallback},
    {"SetLoadFileTextCallback", lua_SetLoadFileTextCallback},
    {"SetSaveFileTextCallback", lua_SetSaveFileTextCallback},
    {"SaveFileData", lua_SaveFileData},
    {"SaveFileText", lua_SaveFileText},
    {"FileExists", lua_FileExists},
    {"DirectoryExists", lua_DirectoryExists},
    {"LoadDirectoryFiles", lua_LoadDirectoryFiles},
    {"LoadDirectoryFilesEx", lua_LoadDirectoryFilesEx},
    {"LoadDroppedFiles", lua_LoadDroppedFiles},
    {"LoadAutomationEventList", lua_LoadAutomationEventList},
    {"SetAutomationEventList", lua_SetAutomationEventList},
    {"SetAutomationEventBaseFrame", lua_SetAutomationEventBaseFrame},
    {"IsKeyPressed", lua_IsKeyPressed},
    {"IsKeyPressedRepeat", lua_IsKeyPressedRepeat},
    {"IsKeyDown", lua_IsKeyDown},
    {"IsKeyReleased", lua_IsKeyReleased},
    {"IsKeyUp", lua_IsKeyUp},
    {"GetKeyPressed", lua_GetKeyPressed},
    {"SetExitKey", lua_SetExitKey},
    {"IsGamepadAvailable", lua_IsGamepadAvailable},
    {"IsGamepadButtonPressed", lua_IsGamepadButtonPressed},
    {"IsGamepadButtonDown", lua_IsGamepadButtonDown},
    {"IsGamepadButtonReleased", lua_IsGamepadButtonReleased},
    {"IsGamepadButtonUp", lua_IsGamepadButtonUp},
    {"GetGamepadButtonPressed", lua_GetGamepadButtonPressed},
    {"GetGamepadAxisCount", lua_GetGamepadAxisCount},
    {"GetGamepadAxisMovement", lua_GetGamepadAxisMovement},
    {"SetGamepadMappings", lua_SetGamepadMappings},
    {"IsMouseButtonPressed", lua_IsMouseButtonPressed},
    {"IsMouseButtonDown", lua_IsMouseButtonDown},
    {"IsMouseButtonReleased", lua_IsMouseButtonReleased},
    {"IsMouseButtonUp", lua_IsMouseButtonUp},
    {"GetMouseX", lua_GetMouseX},
    {"GetMouseY", lua_GetMouseY},
    {"GetMousePosition", lua_GetMousePosition},
    {"GetMouseDelta", lua_GetMouseDelta},
    {"SetMousePosition", lua_SetMousePosition},
    {"SetMouseOffset", lua_SetMouseOffset},
    {"SetMouseScale", lua_SetMouseScale},
    {"GetMouseWheelMove", lua_GetMouseWheelMove},
    {"GetMouseWheelMoveV", lua_GetMouseWheelMoveV},
    {"SetMouseCursor", lua_SetMouseCursor},
    {"GetTouchX", lua_GetTouchX},
    {"GetTouchY", lua_GetTouchY},
    {"GetTouchPosition", lua_GetTouchPosition},
    {"GetTouchPointId", lua_GetTouchPointId},
    {"GetTouchPointCount", lua_GetTouchPointCount},
    {"SetGesturesEnabled", lua_SetGesturesEnabled},
    {"IsGestureDetected", lua_IsGestureDetected},
    {"GetGestureDetected", lua_GetGestureDetected},
    {"GetGestureHoldDuration", lua_GetGestureHoldDuration},
    {"GetGestureDragVector", lua_GetGestureDragVector},
    {"GetGestureDragAngle", lua_GetGestureDragAngle},
    {"GetGesturePinchVector", lua_GetGesturePinchVector},
    {"GetGesturePinchAngle", lua_GetGesturePinchAngle},
    {"UpdateCamera", lua_UpdateCamera},
    {"UpdateCameraPro", lua_UpdateCameraPro},
    {"SetShapesTexture", lua_SetShapesTexture},
    {"SetTextureFilter", lua_SetTextureFilter},
    {"SetTextureWrap", lua_SetTextureWrap},
    {"SetPixelColor", lua_SetPixelColor},
    {"SetTextLineSpacing", lua_SetTextLineSpacing},
    {"SetMaterialTexture", lua_SetMaterialTexture},
    {"SetModelMeshMaterial", lua_SetModelMeshMaterial},
    {"SetMasterVolume", lua_SetMasterVolume},
    {"SetSoundVolume", lua_SetSoundVolume},
    {"SetSoundPitch", lua_SetSoundPitch},
    {"SetSoundPan", lua_SetSoundPan},
    {"SetMusicVolume", lua_SetMusicVolume},
    {"SetMusicPitch", lua_SetMusicPitch},
    {"SetMusicPan", lua_SetMusicPan},
    {"SetAudioStreamVolume", lua_SetAudioStreamVolume},
    {"SetAudioStreamPitch", lua_SetAudioStreamPitch},
    {"SetAudioStreamPan", lua_SetAudioStreamPan},
    {"SetAudioStreamBufferSizeDefault", lua_SetAudioStreamBufferSizeDefault},
    {"SetAudioStreamCallback", lua_SetAudioStreamCallback},
    {"GetFileList", lua_GetFileList},
    {"GetFileAndFolderList", lua_GetFileAndFolderList},
	{"CreateCamera3D", lua_CreateCamera3D},
	{"UpdateCameraGamepadFPS", lua_UpdateCameraGamepadFPS},
	{"GetShaderLocation",     lua_GetShaderLocation},
	{"SetShaderValueFloat",   lua_SetShaderValueFloat},
	{"SetShaderValueInt",     lua_SetShaderValueInt},
	{"SetShaderValueVec",     lua_SetShaderValueVec},     // użyj z comps=2/3/4
	{"SetShaderValueIVec",    lua_SetShaderValueIVec},    // użyj z comps=2/3/4
	{"SetShaderValueMat4",    lua_SetShaderValueMat4},
	{NULL,NULL}
};

int luaopen_rcore(lua_State* L) {
    create_Shader_metatable(L);
    create_Image_metatable(L);
    create_Texture2D_metatable(L);
    create_AutomationEventList_metatable(L);
    create_Material_metatable(L);
    create_Model_metatable(L);
    create_Sound_metatable(L);
    create_Music_metatable(L);
    create_AudioStream_metatable(L);
    create_VrStereoConfig_metatable(L);
	create_Camera3D_metatable(L);
	luaL_register(L, "rcore", rcore_functions);
    // ---- STAŁE: helper
    #define CONSTI(name) do { lua_pushinteger(L, (int)(name)); lua_setfield(L, -2, #name); } while(0)

    // ---- GAMEPAD BUTTONS (z raylib.h)
    CONSTI(GAMEPAD_BUTTON_UNKNOWN);
    CONSTI(GAMEPAD_BUTTON_LEFT_FACE_UP);
    CONSTI(GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    CONSTI(GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    CONSTI(GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    CONSTI(GAMEPAD_BUTTON_RIGHT_FACE_UP);
    CONSTI(GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
    CONSTI(GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    CONSTI(GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
    CONSTI(GAMEPAD_BUTTON_LEFT_TRIGGER_1);
    CONSTI(GAMEPAD_BUTTON_LEFT_TRIGGER_2);
    CONSTI(GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
    CONSTI(GAMEPAD_BUTTON_RIGHT_TRIGGER_2);
    CONSTI(GAMEPAD_BUTTON_MIDDLE_LEFT);
    CONSTI(GAMEPAD_BUTTON_MIDDLE);
    CONSTI(GAMEPAD_BUTTON_MIDDLE_RIGHT);
    CONSTI(GAMEPAD_BUTTON_LEFT_THUMB);
    CONSTI(GAMEPAD_BUTTON_RIGHT_THUMB);

    // ---- GAMEPAD AXES (z raylib.h)
    CONSTI(GAMEPAD_AXIS_LEFT_X);
    CONSTI(GAMEPAD_AXIS_LEFT_Y);
    CONSTI(GAMEPAD_AXIS_RIGHT_X);
    CONSTI(GAMEPAD_AXIS_RIGHT_Y);
    CONSTI(GAMEPAD_AXIS_LEFT_TRIGGER);
    CONSTI(GAMEPAD_AXIS_RIGHT_TRIGGER);

    // ---- GESTURES (z rgestures.h)
    CONSTI(GESTURE_NONE);
    CONSTI(GESTURE_TAP);
    CONSTI(GESTURE_DOUBLETAP);
    CONSTI(GESTURE_HOLD);
    CONSTI(GESTURE_DRAG);
    CONSTI(GESTURE_SWIPE_RIGHT);
    CONSTI(GESTURE_SWIPE_LEFT);
    CONSTI(GESTURE_SWIPE_UP);
    CONSTI(GESTURE_SWIPE_DOWN);
    CONSTI(GESTURE_PINCH_IN);
    CONSTI(GESTURE_PINCH_OUT);

    // ---- (opcjonalnie) MYSZ/KLUCZE – przydatne na PC
    CONSTI(MOUSE_BUTTON_LEFT);
    CONSTI(MOUSE_BUTTON_RIGHT);
    CONSTI(MOUSE_BUTTON_MIDDLE);
    CONSTI(KEY_SPACE);

    #undef CONSTI
    return 1;
}

