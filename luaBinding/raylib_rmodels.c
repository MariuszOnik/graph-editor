// Auto-generated Raylib Lua bindings - Module: rmodels
// Based on real raylib source: rmodels.c
// 3D model loading, generation and drawing
// Functions: 37

#include "raylib.h"
#include "lua.h"
#include "lauxlib.h"
#include <stdlib.h>
#include <string.h>

// Compatibility wrapper for Lua 5.1 - lua_rawlen doesn't exist in 5.1
#ifndef lua_rawlen
#define lua_rawlen(L,i) lua_objlen(L,i)
#endif

// Helper function to extract Ray from Lua table
static Ray extract_ray_from_table(lua_State* L, int index) {
    Ray ray;
    luaL_checktype(L, index, LUA_TTABLE);
    
    // Extract position Vector3
    lua_getfield(L, index, "position");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    ray.position.x = luaL_checknumber(L, -3);
    ray.position.y = luaL_checknumber(L, -2);
    ray.position.z = luaL_checknumber(L, -1);
    lua_pop(L, 4);
    
    // Extract direction Vector3
    lua_getfield(L, index, "direction");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    ray.direction.x = luaL_checknumber(L, -3);
    ray.direction.y = luaL_checknumber(L, -2);
    ray.direction.z = luaL_checknumber(L, -1);
    lua_pop(L, 4);
    
    return ray;
}

// Helper function to push RayCollision to Lua table
static void push_ray_collision_to_table(lua_State* L, RayCollision collision) {
    lua_newtable(L);
    
    lua_pushboolean(L, collision.hit);
    lua_setfield(L, -2, "hit");
    
    lua_pushnumber(L, collision.distance);
    lua_setfield(L, -2, "distance");
    
    // Push point Vector3
    lua_newtable(L);
    lua_pushnumber(L, collision.point.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, collision.point.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, collision.point.z);
    lua_setfield(L, -2, "z");
    lua_setfield(L, -2, "point");
    
    // Push normal Vector3
    lua_newtable(L);
    lua_pushnumber(L, collision.normal.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, collision.normal.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, collision.normal.z);
    lua_setfield(L, -2, "z");
    lua_setfield(L, -2, "normal");
}

// Helper function to extract ModelAnimation from Lua table
static ModelAnimation extract_model_animation_from_table(lua_State* L, int index) {
    ModelAnimation anim;
    luaL_checktype(L, index, LUA_TTABLE);
    
    lua_getfield(L, index, "boneCount");
    anim.boneCount = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    
    lua_getfield(L, index, "frameCount");
    anim.frameCount = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    
    lua_getfield(L, index, "name");
    const char* name = luaL_optstring(L, -1, "");
    strncpy(anim.name, name, 31);
    anim.name[31] = '\0';
    lua_pop(L, 1);
    
    // Extract bones array
    lua_getfield(L, index, "bones");
    if (lua_istable(L, -1) && anim.boneCount > 0) {
        anim.bones = (BoneInfo*)malloc(anim.boneCount * sizeof(BoneInfo));
        
        for (int i = 0; i < anim.boneCount; i++) {
            lua_rawgeti(L, -1, i + 1);
            luaL_checktype(L, -1, LUA_TTABLE);
            
            // Extract bone name
            lua_getfield(L, -1, "name");
            const char* boneName = luaL_optstring(L, -1, "");
            strncpy(anim.bones[i].name, boneName, 31);
            anim.bones[i].name[31] = '\0';
            lua_pop(L, 1);
            
            // Extract parent index
            lua_getfield(L, -1, "parent");
            anim.bones[i].parent = luaL_checkinteger(L, -1);
            lua_pop(L, 1);
            
            lua_pop(L, 1); // Pop bone table
        }
    } else {
        anim.bones = NULL;
    }
    lua_pop(L, 1); // Pop bones array
    
    // Extract framePoses array
    lua_getfield(L, index, "framePoses");
    if (lua_istable(L, -1) && anim.frameCount > 0 && anim.boneCount > 0) {
        anim.framePoses = (Transform**)malloc(anim.frameCount * sizeof(Transform*));
        
        for (int frame = 0; frame < anim.frameCount; frame++) {
            lua_rawgeti(L, -1, frame + 1);
            luaL_checktype(L, -1, LUA_TTABLE);
            
            anim.framePoses[frame] = (Transform*)malloc(anim.boneCount * sizeof(Transform));
            
            for (int bone = 0; bone < anim.boneCount; bone++) {
                lua_rawgeti(L, -1, bone + 1);
                luaL_checktype(L, -1, LUA_TTABLE);
                
                // Extract translation Vector3
                lua_getfield(L, -1, "translation");
                lua_getfield(L, -1, "x");
                lua_getfield(L, -2, "y");
                lua_getfield(L, -3, "z");
                anim.framePoses[frame][bone].translation.x = luaL_checknumber(L, -3);
                anim.framePoses[frame][bone].translation.y = luaL_checknumber(L, -2);
                anim.framePoses[frame][bone].translation.z = luaL_checknumber(L, -1);
                lua_pop(L, 4);
                
                // Extract rotation Quaternion
                lua_getfield(L, -1, "rotation");
                lua_getfield(L, -1, "x");
                lua_getfield(L, -2, "y");
                lua_getfield(L, -3, "z");
                lua_getfield(L, -4, "w");
                anim.framePoses[frame][bone].rotation.x = luaL_checknumber(L, -4);
                anim.framePoses[frame][bone].rotation.y = luaL_checknumber(L, -3);
                anim.framePoses[frame][bone].rotation.z = luaL_checknumber(L, -2);
                anim.framePoses[frame][bone].rotation.w = luaL_checknumber(L, -1);
                lua_pop(L, 5);
                
                // Extract scale Vector3
                lua_getfield(L, -1, "scale");
                lua_getfield(L, -1, "x");
                lua_getfield(L, -2, "y");
                lua_getfield(L, -3, "z");
                anim.framePoses[frame][bone].scale.x = luaL_checknumber(L, -3);
                anim.framePoses[frame][bone].scale.y = luaL_checknumber(L, -2);
                anim.framePoses[frame][bone].scale.z = luaL_checknumber(L, -1);
                lua_pop(L, 4);
                
                lua_pop(L, 1); // Pop transform table
            }
            lua_pop(L, 1); // Pop frame array
        }
    } else {
        anim.framePoses = NULL;
    }
    lua_pop(L, 1); // Pop framePoses array
    
    return anim;
}

// Helper function to push ModelAnimation to Lua table
static void push_model_animation_to_table(lua_State* L, ModelAnimation anim) {
    lua_newtable(L);
    
    lua_pushinteger(L, anim.boneCount);
    lua_setfield(L, -2, "boneCount");
    
    lua_pushinteger(L, anim.frameCount);
    lua_setfield(L, -2, "frameCount");
    
    lua_pushstring(L, anim.name);
    lua_setfield(L, -2, "name");
    
    // Push bones array
    if (anim.bones != NULL && anim.boneCount > 0) {
        lua_newtable(L);
        for (int i = 0; i < anim.boneCount; i++) {
            lua_newtable(L);
            lua_pushstring(L, anim.bones[i].name);
            lua_setfield(L, -2, "name");
            lua_pushinteger(L, anim.bones[i].parent);
            lua_setfield(L, -2, "parent");
            lua_rawseti(L, -2, i + 1);
        }
        lua_setfield(L, -2, "bones");
    } else {
        lua_pushnil(L);
        lua_setfield(L, -2, "bones");
    }
    
    // Push framePoses array
    if (anim.framePoses != NULL && anim.frameCount > 0 && anim.boneCount > 0) {
        lua_newtable(L);
        for (int frame = 0; frame < anim.frameCount; frame++) {
            lua_newtable(L);
            for (int bone = 0; bone < anim.boneCount; bone++) {
                lua_newtable(L);
                
                // Push translation Vector3
                lua_newtable(L);
                lua_pushnumber(L, anim.framePoses[frame][bone].translation.x);
                lua_setfield(L, -2, "x");
                lua_pushnumber(L, anim.framePoses[frame][bone].translation.y);
                lua_setfield(L, -2, "y");
                lua_pushnumber(L, anim.framePoses[frame][bone].translation.z);
                lua_setfield(L, -2, "z");
                lua_setfield(L, -2, "translation");
                
                // Push rotation Quaternion
                lua_newtable(L);
                lua_pushnumber(L, anim.framePoses[frame][bone].rotation.x);
                lua_setfield(L, -2, "x");
                lua_pushnumber(L, anim.framePoses[frame][bone].rotation.y);
                lua_setfield(L, -2, "y");
                lua_pushnumber(L, anim.framePoses[frame][bone].rotation.z);
                lua_setfield(L, -2, "z");
                lua_pushnumber(L, anim.framePoses[frame][bone].rotation.w);
                lua_setfield(L, -2, "w");
                lua_setfield(L, -2, "rotation");
                
                // Push scale Vector3
                lua_newtable(L);
                lua_pushnumber(L, anim.framePoses[frame][bone].scale.x);
                lua_setfield(L, -2, "x");
                lua_pushnumber(L, anim.framePoses[frame][bone].scale.y);
                lua_setfield(L, -2, "y");
                lua_pushnumber(L, anim.framePoses[frame][bone].scale.z);
                lua_setfield(L, -2, "z");
                lua_setfield(L, -2, "scale");
                
                lua_rawseti(L, -2, bone + 1);
            }
            lua_rawseti(L, -2, frame + 1);
        }
        lua_setfield(L, -2, "framePoses");
    } else {
        lua_pushnil(L);
        lua_setfield(L, -2, "framePoses");
    }
}

// Load model from files (meshes and materials)
static int lua_LoadModel(lua_State* L) {
    const char * fileName = luaL_checkstring(L, 1);

    Model result = LoadModel(fileName);

    Model* result_ptr = (Model*)lua_newuserdata(L, sizeof(Model));
    *result_ptr = result;
    luaL_getmetatable(L, "Model");
    lua_setmetatable(L, -2);
    return 1;
}

// Load model from generated mesh (default material)
static int lua_LoadModelFromMesh(lua_State* L) {
    Mesh* mesh = (Mesh*)luaL_checkudata(L, 1, "Mesh");

    Model result = LoadModelFromMesh(*mesh);

    Model* result_ptr = (Model*)lua_newuserdata(L, sizeof(Model));
    *result_ptr = result;
    luaL_getmetatable(L, "Model");
    lua_setmetatable(L, -2);
    return 1;
}

// Check if a model is ready
static int lua_IsModelReady(lua_State* L) {
    Model* model = (Model*)luaL_checkudata(L, 1, "Model");

    bool result = IsModelValid(*model);

    lua_pushboolean(L, result);
    return 1;
}

// Unload model (including meshes) from memory (RAM and/or VRAM)
static int lua_UnloadModel(lua_State* L) {
    Model* model = (Model*)luaL_checkudata(L, 1, "Model");

    UnloadModel(*model);

    return 0;
}

// Compute model bounding box limits (considers all meshes)
static int lua_GetModelBoundingBox(lua_State* L) {
    Model* model = (Model*)luaL_checkudata(L, 1, "Model");

    BoundingBox result = GetModelBoundingBox(*model);

    // Push BoundingBox as table with min and max Vector3
    lua_newtable(L);
    
    // Create min Vector3
    lua_newtable(L);
    lua_pushnumber(L, result.min.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.min.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, result.min.z);
    lua_setfield(L, -2, "z");
    lua_setfield(L, -2, "min");
    
    // Create max Vector3
    lua_newtable(L);
    lua_pushnumber(L, result.max.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.max.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, result.max.z);
    lua_setfield(L, -2, "z");
    lua_setfield(L, -2, "max");
    
    return 1;
}

// Draw a model (with texture if set)
static int lua_DrawModel(lua_State* L) {
    Model* model = (Model*)luaL_checkudata(L, 1, "Model");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float scale = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawModel(*model, position, scale, tint);

    return 0;
}

// Draw a model with extended parameters
static int lua_DrawModelEx(lua_State* L) {
    Model* model = (Model*)luaL_checkudata(L, 1, "Model");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "z");
    Vector3 rotationAxis = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float rotationAngle = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "x");
    lua_getfield(L, 5, "y");
    lua_getfield(L, 5, "z");
    Vector3 scale = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawModelEx(*model, position, rotationAxis, rotationAngle, scale, tint);

    return 0;
}

// Draw a model wires (with texture if set)
static int lua_DrawModelWires(lua_State* L) {
    Model* model = (Model*)luaL_checkudata(L, 1, "Model");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float scale = luaL_checknumber(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "r");
    lua_getfield(L, 4, "g");
    lua_getfield(L, 4, "b");
    lua_getfield(L, 4, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawModelWires(*model, position, scale, tint);

    return 0;
}

// Draw a model wires (with texture if set) with extended parameters
static int lua_DrawModelWiresEx(lua_State* L) {
    Model* model = (Model*)luaL_checkudata(L, 1, "Model");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 position = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "z");
    Vector3 rotationAxis = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float rotationAngle = luaL_checknumber(L, 4);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "x");
    lua_getfield(L, 5, "y");
    lua_getfield(L, 5, "z");
    Vector3 scale = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_getfield(L, 6, "r");
    lua_getfield(L, 6, "g");
    lua_getfield(L, 6, "b");
    lua_getfield(L, 6, "a");
    Color tint = {luaL_checkinteger(L, -4), luaL_checkinteger(L, -3), luaL_checkinteger(L, -2), luaL_checkinteger(L, -1)};
    lua_pop(L, 4);

    DrawModelWiresEx(*model, position, rotationAxis, rotationAngle, scale, tint);

    return 0;
}

// Unload mesh data from CPU and GPU
static int lua_UnloadMesh(lua_State* L) {
    Mesh* mesh = (Mesh*)luaL_checkudata(L, 1, "Mesh");

    UnloadMesh(*mesh);

    return 0;
}

// Draw a 3d mesh with material and transform
static int lua_DrawMesh(lua_State* L) {
    Mesh* mesh = (Mesh*)luaL_checkudata(L, 1, "Mesh");
    Material* material = (Material*)luaL_checkudata(L, 2, "Material");
    luaL_checktype(L, 3, LUA_TTABLE);
    Matrix transform;
    const char* matrix_fields[] = {"m0", "m4", "m8", "m12", "m1", "m5", "m9", "m13", 
                                    "m2", "m6", "m10", "m14", "m3", "m7", "m11", "m15"};
    float* matrix_values = (float*)&transform;
    for (int i = 0; i < 16; i++) {
        lua_getfield(L, 3, matrix_fields[i]);
        matrix_values[i] = luaL_checknumber(L, -1);
        lua_pop(L, 1);
    }

    DrawMesh(*mesh, *material, transform);

    return 0;
}

// Draw multiple mesh instances with material and different transforms
static int lua_DrawMeshInstanced(lua_State* L) {
    Mesh* mesh = (Mesh*)luaL_checkudata(L, 1, "Mesh");
    Material* material = (Material*)luaL_checkudata(L, 2, "Material");
    luaL_checktype(L, 3, LUA_TTABLE);
    int instances = luaL_checkinteger(L, 4);
    
    int transformCount = lua_rawlen(L, 3);
    if (transformCount != instances) {
        luaL_error(L, "Transform array size (%d) doesn't match instances count (%d)", transformCount, instances);
        return 0;
    }
    
    Matrix* transforms = (Matrix*)malloc(instances * sizeof(Matrix));
    const char* matrix_fields[] = {"m0", "m4", "m8", "m12", "m1", "m5", "m9", "m13", 
                                    "m2", "m6", "m10", "m14", "m3", "m7", "m11", "m15"};
    
    for (int i = 0; i < instances; i++) {
        lua_rawgeti(L, 3, i + 1);
        luaL_checktype(L, -1, LUA_TTABLE);
        
        float* matrix_values = (float*)&transforms[i];
        for (int j = 0; j < 16; j++) {
            lua_getfield(L, -1, matrix_fields[j]);
            matrix_values[j] = luaL_checknumber(L, -1);
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }

    DrawMeshInstanced(*mesh, *material, transforms, instances);

    free(transforms);
    return 0;
}

// Export mesh data to file, returns true on success
static int lua_ExportMesh(lua_State* L) {
    Mesh* mesh = (Mesh*)luaL_checkudata(L, 1, "Mesh");
    const char* fileName = luaL_checkstring(L, 2);

    bool result = ExportMesh(*mesh, fileName);

    lua_pushboolean(L, result);
    return 1;
}

// Compute mesh bounding box limits
static int lua_GetMeshBoundingBox(lua_State* L) {
    Mesh* mesh = (Mesh*)luaL_checkudata(L, 1, "Mesh");

    BoundingBox result = GetMeshBoundingBox(*mesh);

    // Create BoundingBox table with min and max Vector3 fields
    lua_newtable(L);
    
    // Create min Vector3 table
    lua_newtable(L);
    lua_pushnumber(L, result.min.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.min.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, result.min.z);
    lua_setfield(L, -2, "z");
    lua_setfield(L, -2, "min");
    
    // Create max Vector3 table
    lua_newtable(L);
    lua_pushnumber(L, result.max.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, result.max.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, result.max.z);
    lua_setfield(L, -2, "z");
    lua_setfield(L, -2, "max");
    
    return 1;
}

// Compute mesh tangents
static int lua_GenMeshTangents(lua_State* L) {
    Mesh* mesh = (Mesh*)luaL_checkudata(L, 1, "Mesh");

    GenMeshTangents(mesh);

    return 0;
}

// Generate polygonal mesh
static int lua_GenMeshPoly(lua_State* L) {
    int sides = luaL_checkinteger(L, 1);
    float radius = luaL_checknumber(L, 2);

    Mesh result = GenMeshPoly(sides, radius);

    Mesh* result_ptr = (Mesh*)lua_newuserdata(L, sizeof(Mesh));
    *result_ptr = result;
    luaL_getmetatable(L, "Mesh");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate plane mesh (with subdivisions)
static int lua_GenMeshPlane(lua_State* L) {
    float width = luaL_checknumber(L, 1);
    float length = luaL_checknumber(L, 2);
    int resX = luaL_checkinteger(L, 3);
    int resZ = luaL_checkinteger(L, 4);

    Mesh result = GenMeshPlane(width, length, resX, resZ);

    Mesh* result_ptr = (Mesh*)lua_newuserdata(L, sizeof(Mesh));
    *result_ptr = result;
    luaL_getmetatable(L, "Mesh");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate cuboid mesh
static int lua_GenMeshCube(lua_State* L) {
    float width = luaL_checknumber(L, 1);
    float height = luaL_checknumber(L, 2);
    float length = luaL_checknumber(L, 3);

    Mesh result = GenMeshCube(width, height, length);

    Mesh* result_ptr = (Mesh*)lua_newuserdata(L, sizeof(Mesh));
    *result_ptr = result;
    luaL_getmetatable(L, "Mesh");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate sphere mesh (standard sphere)
static int lua_GenMeshSphere(lua_State* L) {
    float radius = luaL_checknumber(L, 1);
    int rings = luaL_checkinteger(L, 2);
    int slices = luaL_checkinteger(L, 3);

    Mesh result = GenMeshSphere(radius, rings, slices);

    Mesh* result_ptr = (Mesh*)lua_newuserdata(L, sizeof(Mesh));
    *result_ptr = result;
    luaL_getmetatable(L, "Mesh");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate half-sphere mesh (no bottom cap)
static int lua_GenMeshHemiSphere(lua_State* L) {
    float radius = luaL_checknumber(L, 1);
    int rings = luaL_checkinteger(L, 2);
    int slices = luaL_checkinteger(L, 3);

    Mesh result = GenMeshHemiSphere(radius, rings, slices);

    Mesh* result_ptr = (Mesh*)lua_newuserdata(L, sizeof(Mesh));
    *result_ptr = result;
    luaL_getmetatable(L, "Mesh");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate cylinder mesh
static int lua_GenMeshCylinder(lua_State* L) {
    float radius = luaL_checknumber(L, 1);
    float height = luaL_checknumber(L, 2);
    int slices = luaL_checkinteger(L, 3);

    Mesh result = GenMeshCylinder(radius, height, slices);

    Mesh* result_ptr = (Mesh*)lua_newuserdata(L, sizeof(Mesh));
    *result_ptr = result;
    luaL_getmetatable(L, "Mesh");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate cone/pyramid mesh
static int lua_GenMeshCone(lua_State* L) {
    float radius = luaL_checknumber(L, 1);
    float height = luaL_checknumber(L, 2);
    int slices = luaL_checkinteger(L, 3);

    Mesh result = GenMeshCone(radius, height, slices);

    Mesh* result_ptr = (Mesh*)lua_newuserdata(L, sizeof(Mesh));
    *result_ptr = result;
    luaL_getmetatable(L, "Mesh");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate torus mesh
static int lua_GenMeshTorus(lua_State* L) {
    float radius = luaL_checknumber(L, 1);
    float size = luaL_checknumber(L, 2);
    int radSeg = luaL_checkinteger(L, 3);
    int sides = luaL_checkinteger(L, 4);

    Mesh result = GenMeshTorus(radius, size, radSeg, sides);

    Mesh* result_ptr = (Mesh*)lua_newuserdata(L, sizeof(Mesh));
    *result_ptr = result;
    luaL_getmetatable(L, "Mesh");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate trefoil knot mesh
static int lua_GenMeshKnot(lua_State* L) {
    float radius = luaL_checknumber(L, 1);
    float size = luaL_checknumber(L, 2);
    int radSeg = luaL_checkinteger(L, 3);
    int sides = luaL_checkinteger(L, 4);

    Mesh result = GenMeshKnot(radius, size, radSeg, sides);

    Mesh* result_ptr = (Mesh*)lua_newuserdata(L, sizeof(Mesh));
    *result_ptr = result;
    luaL_getmetatable(L, "Mesh");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate heightmap mesh from image data
static int lua_GenMeshHeightmap(lua_State* L) {
    Image* heightmap = (Image*)luaL_checkudata(L, 1, "Image");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 size = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);

    Mesh result = GenMeshHeightmap(*heightmap, size);

    Mesh* result_ptr = (Mesh*)lua_newuserdata(L, sizeof(Mesh));
    *result_ptr = result;
    luaL_getmetatable(L, "Mesh");
    lua_setmetatable(L, -2);
    return 1;
}

// Generate cubes-based map mesh from image data
static int lua_GenMeshCubicmap(lua_State* L) {
    Image* cubicmap = (Image*)luaL_checkudata(L, 1, "Image");
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 cubeSize = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);

    Mesh result = GenMeshCubicmap(*cubicmap, cubeSize);

    Mesh* result_ptr = (Mesh*)lua_newuserdata(L, sizeof(Mesh));
    *result_ptr = result;
    luaL_getmetatable(L, "Mesh");
    lua_setmetatable(L, -2);
    return 1;
}

// Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
static int lua_LoadMaterialDefault(lua_State* L) {
    Material result = LoadMaterialDefault();

    Material* result_ptr = (Material*)lua_newuserdata(L, sizeof(Material));
    *result_ptr = result;
    luaL_getmetatable(L, "Material");
    lua_setmetatable(L, -2);
    return 1;
}

// Unload material from GPU memory (VRAM)
static int lua_UnloadMaterial(lua_State* L) {
    Material* material = (Material*)luaL_checkudata(L, 1, "Material");

    UnloadMaterial(*material);

    return 0;
}

// Update model animation pose
static int lua_UpdateModelAnimation(lua_State* L) {
    Model* model = (Model*)luaL_checkudata(L, 1, "Model");
    ModelAnimation anim = extract_model_animation_from_table(L, 2);
    int frame = luaL_checkinteger(L, 3);

    UpdateModelAnimation(*model, anim, frame);

    return 0;
}

// Unload animation data
static int lua_UnloadModelAnimation(lua_State* L) {
    ModelAnimation anim = extract_model_animation_from_table(L, 1);

    UnloadModelAnimation(anim);

    return 0;
}

// Load model animations from file
static int lua_LoadModelAnimations(lua_State* L) {
    const char* fileName = luaL_checkstring(L, 1);
    int animCount = 0;
    
    ModelAnimation* animations = LoadModelAnimations(fileName, &animCount);
    
    if (animations != NULL && animCount > 0) {
        lua_newtable(L);
        for (int i = 0; i < animCount; i++) {
            push_model_animation_to_table(L, animations[i]);
            lua_rawseti(L, -2, i + 1);
        }
        lua_pushinteger(L, animCount);
        return 2; // Return animations table and count
    } else {
        lua_pushnil(L);
        lua_pushinteger(L, 0);
        return 2;
    }
}

// Unload animation array data
static int lua_UnloadModelAnimations(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int animCount = lua_rawlen(L, 1);
    
    if (animCount > 0) {
        ModelAnimation* animations = (ModelAnimation*)malloc(animCount * sizeof(ModelAnimation));
        
        for (int i = 0; i < animCount; i++) {
            lua_rawgeti(L, 1, i + 1);
            animations[i] = extract_model_animation_from_table(L, -1);
            lua_pop(L, 1);
        }
        
        UnloadModelAnimations(animations, animCount);
        free(animations);
    }

    return 0;
}

// Check model animation skeleton match
static int lua_IsModelAnimationValid(lua_State* L) {
    Model* model = (Model*)luaL_checkudata(L, 1, "Model");
    ModelAnimation anim = extract_model_animation_from_table(L, 2);

    bool result = IsModelAnimationValid(*model, anim);

    lua_pushboolean(L, result);
    return 1;
}

// Get collision info between ray and sphere
static int lua_GetRayCollisionSphere(lua_State* L) {
    Ray ray = extract_ray_from_table(L, 1);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 center = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    float radius = luaL_checknumber(L, 3);

    RayCollision result = GetRayCollisionSphere(ray, center, radius);

    push_ray_collision_to_table(L, result);
    return 1;
}

// Get collision info between ray and box
static int lua_GetRayCollisionBox(lua_State* L) {
    Ray ray = extract_ray_from_table(L, 1);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "min");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 min = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    lua_getfield(L, 2, "max");
    lua_getfield(L, -1, "x");
    lua_getfield(L, -2, "y");
    lua_getfield(L, -3, "z");
    Vector3 max = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 4);
    BoundingBox box = {min, max};

    RayCollision result = GetRayCollisionBox(ray, box);

    push_ray_collision_to_table(L, result);
    return 1;
}

// Get collision info between ray and mesh
static int lua_GetRayCollisionMesh(lua_State* L) {
    Ray ray = extract_ray_from_table(L, 1);
    Mesh* mesh = (Mesh*)luaL_checkudata(L, 2, "Mesh");
    luaL_checktype(L, 3, LUA_TTABLE);
    Matrix transform;
    const char* matrix_fields[] = {"m0", "m4", "m8", "m12", "m1", "m5", "m9", "m13", 
                                    "m2", "m6", "m10", "m14", "m3", "m7", "m11", "m15"};
    float* matrix_values = (float*)&transform;
    for (int i = 0; i < 16; i++) {
        lua_getfield(L, 3, matrix_fields[i]);
        matrix_values[i] = luaL_checknumber(L, -1);
        lua_pop(L, 1);
    }

    RayCollision result = GetRayCollisionMesh(ray, *mesh, transform);

    push_ray_collision_to_table(L, result);
    return 1;
}

// Get collision info between ray and triangle
static int lua_GetRayCollisionTriangle(lua_State* L) {
    Ray ray = extract_ray_from_table(L, 1);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 p1 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "z");
    Vector3 p2 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    lua_getfield(L, 4, "z");
    Vector3 p3 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);

    RayCollision result = GetRayCollisionTriangle(ray, p1, p2, p3);

    push_ray_collision_to_table(L, result);
    return 1;
}

// Get collision info between ray and quad
static int lua_GetRayCollisionQuad(lua_State* L) {
    Ray ray = extract_ray_from_table(L, 1);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "x");
    lua_getfield(L, 2, "y");
    lua_getfield(L, 2, "z");
    Vector3 p1 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 3, LUA_TTABLE);
    lua_getfield(L, 3, "x");
    lua_getfield(L, 3, "y");
    lua_getfield(L, 3, "z");
    Vector3 p2 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 4, LUA_TTABLE);
    lua_getfield(L, 4, "x");
    lua_getfield(L, 4, "y");
    lua_getfield(L, 4, "z");
    Vector3 p3 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);
    luaL_checktype(L, 5, LUA_TTABLE);
    lua_getfield(L, 5, "x");
    lua_getfield(L, 5, "y");
    lua_getfield(L, 5, "z");
    Vector3 p4 = {luaL_checknumber(L, -3), luaL_checknumber(L, -2), luaL_checknumber(L, -1)};
    lua_pop(L, 3);

    RayCollision result = GetRayCollisionQuad(ray, p1, p2, p3, p4);

    push_ray_collision_to_table(L, result);
    return 1;
}

// int rmodels.ModelGetMaterialsCount(Model* model)
static int lua_ModelGetMaterialsCount(lua_State* L) {
    Model* model = (Model*)luaL_checkudata(L, 1, "Model");
    lua_pushinteger(L, model->materialCount);
    return 1;
}


// Shader rmodels.ModelGetMaterialShader(Model* model, int materialIndex)
static int lua_ModelGetMaterialShader(lua_State* L) {
    Model* model = (Model*)luaL_checkudata(L, 1, "Model");
    int matIndex = luaL_checkinteger(L, 2);
    luaL_argcheck(L, matIndex >= 0 && matIndex < model->materialCount, 2, "material index out of range");

    Shader* out = (Shader*)lua_newuserdata(L, sizeof(Shader));
    *out = model->materials[matIndex].shader; // kopia struktury Shader (id itd.)
    luaL_getmetatable(L, "Shader");
    lua_setmetatable(L, -2);
    return 1;
}


// void rmodels.ModelSetMaterialShader(Model* model, int materialIndex, Shader shader)
static int lua_ModelSetMaterialShader(lua_State* L) {
    Model* model   = (Model*)luaL_checkudata(L, 1, "Model");
    int    matIndex= luaL_checkinteger(L, 2);
    Shader* shader = (Shader*)luaL_checkudata(L, 3, "Shader");

    luaL_argcheck(L, model != NULL, 1, "invalid Model");
    luaL_argcheck(L, matIndex >= 0 && matIndex < model->materialCount, 2, "material index out of range");
    luaL_argcheck(L, shader != NULL, 3, "invalid Shader");

    // raylib: po prostu przypisujemy shader do materiału
    model->materials[matIndex].shader = *shader;
    return 0;
}




// Metatable definitions for userdata used in this module
static int Model_gc(lua_State* L) {
    Model* obj = (Model*)luaL_checkudata(L, 1, "Model");
    if (obj != NULL) {
        UnloadModel(*obj);
    }
    return 0;
}


static void create_Model_metatable(lua_State* L) {
    luaL_newmetatable(L, "Model");
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, Model_gc);
    lua_settable(L, -3);
    lua_pop(L, 1);  // Remove metatable from stack
}

static const struct luaL_Reg rmodels_functions[] = {
    {"LoadModel", lua_LoadModel},
    {"LoadModelFromMesh", lua_LoadModelFromMesh},
    {"IsModelReady", lua_IsModelReady},
    {"UnloadModel", lua_UnloadModel},
    {"GetModelBoundingBox", lua_GetModelBoundingBox},
    {"DrawModel", lua_DrawModel},
    {"DrawModelEx", lua_DrawModelEx},
    {"DrawModelWires", lua_DrawModelWires},
    {"DrawModelWiresEx", lua_DrawModelWiresEx},
    {"UnloadMesh", lua_UnloadMesh},
    {"DrawMesh", lua_DrawMesh},
    {"DrawMeshInstanced", lua_DrawMeshInstanced},
    {"ExportMesh", lua_ExportMesh},
    {"GetMeshBoundingBox", lua_GetMeshBoundingBox},
    {"GenMeshTangents", lua_GenMeshTangents},
    {"GenMeshPoly", lua_GenMeshPoly},
    {"GenMeshPlane", lua_GenMeshPlane},
    {"GenMeshCube", lua_GenMeshCube},
    {"GenMeshSphere", lua_GenMeshSphere},
    {"GenMeshHemiSphere", lua_GenMeshHemiSphere},
    {"GenMeshCylinder", lua_GenMeshCylinder},
    {"GenMeshCone", lua_GenMeshCone},
    {"GenMeshTorus", lua_GenMeshTorus},
    {"GenMeshKnot", lua_GenMeshKnot},
    {"GenMeshHeightmap", lua_GenMeshHeightmap},
    {"GenMeshCubicmap", lua_GenMeshCubicmap},
    {"LoadMaterialDefault", lua_LoadMaterialDefault},
    {"UnloadMaterial", lua_UnloadMaterial},
    {"LoadModelAnimations", lua_LoadModelAnimations},
    {"UpdateModelAnimation", lua_UpdateModelAnimation},
    {"UnloadModelAnimation", lua_UnloadModelAnimation},
    {"UnloadModelAnimations", lua_UnloadModelAnimations},
    {"IsModelAnimationValid", lua_IsModelAnimationValid},
    {"GetRayCollisionSphere", lua_GetRayCollisionSphere},
    {"GetRayCollisionBox", lua_GetRayCollisionBox},
    {"GetRayCollisionMesh", lua_GetRayCollisionMesh},
    {"GetRayCollisionTriangle", lua_GetRayCollisionTriangle},
    {"GetRayCollisionQuad", lua_GetRayCollisionQuad},
    {"ModelGetMaterialsCount", lua_ModelGetMaterialsCount},
    {"ModelGetMaterialShader", lua_ModelGetMaterialShader},
    {"ModelSetMaterialShader", lua_ModelSetMaterialShader}, // opcjonalnie

    {NULL, NULL}
};

int luaopen_rmodels(lua_State* L) {
    create_Model_metatable(L);
    luaL_register(L, "rmodels", rmodels_functions);
    return 1;
}
