// Auto-generated Raylib Lua bindings - Module: raudio
// Based on real raylib source: raudio.c
// Audio device and sound/music loading and playing
// Functions: 42

#include "raylib.h"
#include "lua.h"
#include "lauxlib.h"
#include <stdlib.h>

// Compatibility wrapper for Lua 5.1 - lua_rawlen doesn't exist in 5.1
#ifndef lua_rawlen
#define lua_rawlen(L,i) lua_objlen(L,i)
#endif

// Initialize audio device and context
static int lua_InitAudioDevice(lua_State* L) {
    InitAudioDevice();

    return 0;
}

// Close the audio device and context
static int lua_CloseAudioDevice(lua_State* L) {
    CloseAudioDevice();

    return 0;
}

// Check if audio device has been initialized successfully
static int lua_IsAudioDeviceReady(lua_State* L) {
    bool result = IsAudioDeviceReady();

    lua_pushboolean(L, result);
    return 1;
}

// Load wave data from file
static int lua_LoadWave(lua_State* L) {
    const char * fileName = luaL_checkstring(L, 1);

    Wave result = LoadWave(fileName);

    Wave* result_ptr = (Wave*)lua_newuserdata(L, sizeof(Wave));
    *result_ptr = result;
    luaL_getmetatable(L, "Wave");
    lua_setmetatable(L, -2);
    return 1;
}

// Load wave from memory buffer, fileType refers to extension: i.e. '.wav'
static int lua_LoadWaveFromMemory(lua_State* L) {
    const char * fileType = luaL_checkstring(L, 1);
    size_t dataLength;
    const unsigned char* fileData = (const unsigned char*)luaL_checklstring(L, 2, &dataLength);
    int dataSize = luaL_checkinteger(L, 3);

    Wave result = LoadWaveFromMemory(fileType, fileData, dataSize);

    Wave* result_ptr = (Wave*)lua_newuserdata(L, sizeof(Wave));
    *result_ptr = result;
    luaL_getmetatable(L, "Wave");
    lua_setmetatable(L, -2);
    return 1;
}

// Checks if wave data is ready - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_IsWaveReady(lua_State* L) {
//     Wave* wave = (Wave*)luaL_checkudata(L, 1, "Wave");
// 
//     bool result = IsWaveReady(*wave);
// 
//     lua_pushboolean(L, result);
//     return 1;
// }

// Load sound from file
static int lua_LoadSound(lua_State* L) {
    char * fileName = luaL_checkstring(L, 1);

    Sound result = LoadSound(fileName);

    Sound* result_ptr = (Sound*)lua_newuserdata(L, sizeof(Sound));
    *result_ptr = result;
    luaL_getmetatable(L, "Sound");
    lua_setmetatable(L, -2);
    return 1;
}

// Load sound from wave data
static int lua_LoadSoundFromWave(lua_State* L) {
    Wave* wave = (Wave*)luaL_checkudata(L, 1, "Wave");

    Sound result = LoadSoundFromWave(*wave);

    Sound* result_ptr = (Sound*)lua_newuserdata(L, sizeof(Sound));
    *result_ptr = result;
    luaL_getmetatable(L, "Sound");
    lua_setmetatable(L, -2);
    return 1;
}

// Create a new sound that shares the same sample data as the source sound, does not own the sound data
static int lua_LoadSoundAlias(lua_State* L) {
    Sound* source = (Sound*)luaL_checkudata(L, 1, "Sound");

    Sound result = LoadSoundAlias(*source);

    Sound* result_ptr = (Sound*)lua_newuserdata(L, sizeof(Sound));
    *result_ptr = result;
    luaL_getmetatable(L, "Sound");
    lua_setmetatable(L, -2);
    return 1;
}

// Checks if a sound is ready - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_IsSoundReady(lua_State* L) {
//     Sound* sound = (Sound*)luaL_checkudata(L, 1, "Sound");
// 
//     bool result = IsSoundReady(*sound);
// 
//     lua_pushboolean(L, result);
//     return 1;
// }

// Unload wave data
static int lua_UnloadWave(lua_State* L) {
    Wave* wave = (Wave*)luaL_checkudata(L, 1, "Wave");

    UnloadWave(*wave);

    return 0;
}

// Unload sound
static int lua_UnloadSound(lua_State* L) {
    Sound* sound = (Sound*)luaL_checkudata(L, 1, "Sound");

    UnloadSound(*sound);

    return 0;
}

// Unload a sound alias (does not deallocate sample data)
static int lua_UnloadSoundAlias(lua_State* L) {
    Sound* alias = (Sound*)luaL_checkudata(L, 1, "Sound");

    UnloadSoundAlias(*alias);

    return 0;
}

// Play a sound
static int lua_PlaySound(lua_State* L) {
    Sound* sound = (Sound*)luaL_checkudata(L, 1, "Sound");

    PlaySound(*sound);

    return 0;
}

// Stop playing a sound
static int lua_StopSound(lua_State* L) {
    Sound* sound = (Sound*)luaL_checkudata(L, 1, "Sound");

    StopSound(*sound);

    return 0;
}

// Pause a sound
static int lua_PauseSound(lua_State* L) {
    Sound* sound = (Sound*)luaL_checkudata(L, 1, "Sound");

    PauseSound(*sound);

    return 0;
}

// Resume a paused sound
static int lua_ResumeSound(lua_State* L) {
    Sound* sound = (Sound*)luaL_checkudata(L, 1, "Sound");

    ResumeSound(*sound);

    return 0;
}

// Check if a sound is currently playing
static int lua_IsSoundPlaying(lua_State* L) {
    Sound* sound = (Sound*)luaL_checkudata(L, 1, "Sound");

    bool result = IsSoundPlaying(*sound);

    lua_pushboolean(L, result);
    return 1;
}

// Copy a wave to a new wave
static int lua_WaveCopy(lua_State* L) {
    Wave* wave = (Wave*)luaL_checkudata(L, 1, "Wave");

    Wave result = WaveCopy(*wave);

    Wave* result_ptr = (Wave*)lua_newuserdata(L, sizeof(Wave));
    *result_ptr = result;
    luaL_getmetatable(L, "Wave");
    lua_setmetatable(L, -2);
    return 1;
}

// Unload samples data loaded with LoadWaveSamples()
static int lua_UnloadWaveSamples(lua_State* L) {
    float* samples = (float*)lua_touserdata(L, 1);
    
    if (samples != NULL) {
        UnloadWaveSamples(samples);
    }

    return 0;
}

// Load music stream from file
static int lua_LoadMusicStream(lua_State* L) {
    char * fileName = luaL_checkstring(L, 1);

    Music result = LoadMusicStream(fileName);

    Music* result_ptr = (Music*)lua_newuserdata(L, sizeof(Music));
    *result_ptr = result;
    luaL_getmetatable(L, "Music");
    lua_setmetatable(L, -2);
    return 1;
}

// Load music stream from data
static int lua_LoadMusicStreamFromMemory(lua_State* L) {
    const char * fileType = luaL_checkstring(L, 1);
    size_t dataLength;
    const unsigned char* data = (const unsigned char*)luaL_checklstring(L, 2, &dataLength);
    int dataSize = luaL_checkinteger(L, 3);

    Music result = LoadMusicStreamFromMemory(fileType, data, dataSize);

    Music* result_ptr = (Music*)lua_newuserdata(L, sizeof(Music));
    *result_ptr = result;
    luaL_getmetatable(L, "Music");
    lua_setmetatable(L, -2);
    return 1;
}

// Checks if a music stream is ready - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_IsMusicReady(lua_State* L) {
//     Music* music = (Music*)luaL_checkudata(L, 1, "Music");
// 
//     bool result = IsMusicReady(*music);
// 
//     lua_pushboolean(L, result);
//     return 1;
// }

// Unload music stream
static int lua_UnloadMusicStream(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");

    UnloadMusicStream(*music);

    return 0;
}

// Start music playing
static int lua_PlayMusicStream(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");

    PlayMusicStream(*music);

    return 0;
}

// Check if music is playing
static int lua_IsMusicStreamPlaying(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");

    bool result = IsMusicStreamPlaying(*music);

    lua_pushboolean(L, result);
    return 1;
}

// Updates buffers for music streaming
static int lua_UpdateMusicStream(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");

    UpdateMusicStream(*music);

    return 0;
}

// Stop music playing
static int lua_StopMusicStream(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");

    StopMusicStream(*music);

    return 0;
}

// Pause music playing
static int lua_PauseMusicStream(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");

    PauseMusicStream(*music);

    return 0;
}

// Resume playing paused music
static int lua_ResumeMusicStream(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");

    ResumeMusicStream(*music);

    return 0;
}

// Seek music to a position (in seconds)
static int lua_SeekMusicStream(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");
    float position = luaL_checknumber(L, 2);

    SeekMusicStream(*music, position);

    return 0;
}

// Get music time length (in seconds)
static int lua_GetMusicTimeLength(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");

    float result = GetMusicTimeLength(*music);

    lua_pushnumber(L, result);
    return 1;
}

// Get current music time played (in seconds)
static int lua_GetMusicTimePlayed(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");

    float result = GetMusicTimePlayed(*music);

    lua_pushnumber(L, result);
    return 1;
}

// Load audio stream (to stream raw audio pcm data)
static int lua_LoadAudioStream(lua_State* L) {
    unsigned int sampleRate = luaL_checkinteger(L, 1);
    unsigned int sampleSize = luaL_checkinteger(L, 2);
    unsigned int channels = luaL_checkinteger(L, 3);

    AudioStream result = LoadAudioStream(sampleRate, sampleSize, channels);

    AudioStream* result_ptr = (AudioStream*)lua_newuserdata(L, sizeof(AudioStream));
    *result_ptr = result;
    luaL_getmetatable(L, "AudioStream");
    lua_setmetatable(L, -2);
    return 1;
}

// Checks if an audio stream is ready - REMOVED: Function not supported in raylib-nx-5.5
// static int lua_IsAudioStreamReady(lua_State* L) {
//     AudioStream* stream = (AudioStream*)luaL_checkudata(L, 1, "AudioStream");
// 
//     bool result = IsAudioStreamReady(*stream);
// 
//     lua_pushboolean(L, result);
//     return 1;
// }

// Unload audio stream and free memory
static int lua_UnloadAudioStream(lua_State* L) {
    AudioStream* stream = (AudioStream*)luaL_checkudata(L, 1, "AudioStream");

    UnloadAudioStream(*stream);

    return 0;
}

// Check if any audio stream buffers requires refill
static int lua_IsAudioStreamProcessed(lua_State* L) {
    AudioStream* stream = (AudioStream*)luaL_checkudata(L, 1, "AudioStream");

    bool result = IsAudioStreamProcessed(*stream);

    lua_pushboolean(L, result);
    return 1;
}

static int lua_SetMusicPitch(lua_State* L) {
    Music* music = (Music*)luaL_checkudata(L, 1, "Music");
    float pitch = luaL_checknumber(L, 2);

    SetMusicPitch(*music, pitch);

    return 0;
}

// Play audio stream
static int lua_PlayAudioStream(lua_State* L) {
    AudioStream* stream = (AudioStream*)luaL_checkudata(L, 1, "AudioStream");

    PlayAudioStream(*stream);

    return 0;
}

// Pause audio stream
static int lua_PauseAudioStream(lua_State* L) {
    AudioStream* stream = (AudioStream*)luaL_checkudata(L, 1, "AudioStream");

    PauseAudioStream(*stream);

    return 0;
}

// Resume audio stream
static int lua_ResumeAudioStream(lua_State* L) {
    AudioStream* stream = (AudioStream*)luaL_checkudata(L, 1, "AudioStream");

    ResumeAudioStream(*stream);

    return 0;
}

// Check if audio stream is playing
static int lua_IsAudioStreamPlaying(lua_State* L) {
    AudioStream* stream = (AudioStream*)luaL_checkudata(L, 1, "AudioStream");

    bool result = IsAudioStreamPlaying(*stream);

    lua_pushboolean(L, result);
    return 1;
}

// Stop audio stream
static int lua_StopAudioStream(lua_State* L) {
    AudioStream* stream = (AudioStream*)luaL_checkudata(L, 1, "AudioStream");

    StopAudioStream(*stream);

    return 0;
}


// Metatable definitions for userdata used in this module
static int Music_gc(lua_State* L) {
    Music* obj = (Music*)luaL_checkudata(L, 1, "Music");
    if (obj != NULL) {
        UnloadMusicStream(*obj);
    }
    return 0;
}

static void create_Music_metatable(lua_State* L) {
    luaL_newmetatable(L, "Music");
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, Music_gc);
    lua_settable(L, -3);
    lua_pop(L, 1);  // Remove metatable from stack
}

static int Sound_gc(lua_State* L) {
    Sound* obj = (Sound*)luaL_checkudata(L, 1, "Sound");
    if (obj != NULL) {
        UnloadSoundAlias(*obj);
    }
    return 0;
}

static void create_Sound_metatable(lua_State* L) {
    luaL_newmetatable(L, "Sound");
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, Sound_gc);
    lua_settable(L, -3);
    lua_pop(L, 1);  // Remove metatable from stack
}

static int Wave_gc(lua_State* L) {
    Wave* obj = (Wave*)luaL_checkudata(L, 1, "Wave");
    if (obj != NULL) {
        UnloadWave(*obj);
    }
    return 0;
}

static void create_Wave_metatable(lua_State* L) {
    luaL_newmetatable(L, "Wave");
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, Wave_gc);
    lua_settable(L, -3);
    lua_pop(L, 1);  // Remove metatable from stack
}

static int AudioStream_gc(lua_State* L) {
    AudioStream* obj = (AudioStream*)luaL_checkudata(L, 1, "AudioStream");
    if (obj != NULL) {
        UnloadAudioStream(*obj);
    }
    return 0;
}

static void create_AudioStream_metatable(lua_State* L) {
    luaL_newmetatable(L, "AudioStream");
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, AudioStream_gc);
    lua_settable(L, -3);
    lua_pop(L, 1);  // Remove metatable from stack
}

static const struct luaL_Reg raudio_functions[] = {
    {"InitAudioDevice", lua_InitAudioDevice},
    {"CloseAudioDevice", lua_CloseAudioDevice},
    {"IsAudioDeviceReady", lua_IsAudioDeviceReady},
    {"LoadWave", lua_LoadWave},
    {"LoadWaveFromMemory", lua_LoadWaveFromMemory},
    {"LoadSound", lua_LoadSound},
    {"LoadSoundFromWave", lua_LoadSoundFromWave},
    {"LoadSoundAlias", lua_LoadSoundAlias},
    {"UnloadWave", lua_UnloadWave},
    {"UnloadSound", lua_UnloadSound},
    {"UnloadSoundAlias", lua_UnloadSoundAlias},
    {"PlaySound", lua_PlaySound},
    {"StopSound", lua_StopSound},
    {"PauseSound", lua_PauseSound},
    {"ResumeSound", lua_ResumeSound},
    {"IsSoundPlaying", lua_IsSoundPlaying},
    {"WaveCopy", lua_WaveCopy},
    {"UnloadWaveSamples", lua_UnloadWaveSamples},
    {"LoadMusicStream", lua_LoadMusicStream},
    {"LoadMusicStreamFromMemory", lua_LoadMusicStreamFromMemory},
    {"UnloadMusicStream", lua_UnloadMusicStream},
    {"PlayMusicStream", lua_PlayMusicStream},
    {"IsMusicStreamPlaying", lua_IsMusicStreamPlaying},
    {"UpdateMusicStream", lua_UpdateMusicStream},
    {"StopMusicStream", lua_StopMusicStream},
    {"PauseMusicStream", lua_PauseMusicStream},
    {"ResumeMusicStream", lua_ResumeMusicStream},
    {"SeekMusicStream", lua_SeekMusicStream},
    {"GetMusicTimeLength", lua_GetMusicTimeLength},
    {"GetMusicTimePlayed", lua_GetMusicTimePlayed},
    {"LoadAudioStream", lua_LoadAudioStream},
    {"UnloadAudioStream", lua_UnloadAudioStream},
    {"IsAudioStreamProcessed", lua_IsAudioStreamProcessed},
    {"PlayAudioStream", lua_PlayAudioStream},
    {"PauseAudioStream", lua_PauseAudioStream},
    {"ResumeAudioStream", lua_ResumeAudioStream},
    {"IsAudioStreamPlaying", lua_IsAudioStreamPlaying},
    {"StopAudioStream", lua_StopAudioStream},
    {"SetMusicPitch", lua_SetMusicPitch},
    {NULL, NULL}
};

int luaopen_raudio(lua_State* L) {
    create_Music_metatable(L);
    create_Sound_metatable(L);
    create_Wave_metatable(L);
    create_AudioStream_metatable(L);
    luaL_register(L, "raudio", raudio_functions);
    return 1;
}
