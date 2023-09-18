#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

Camera camera = { 0 };
Vector3 cubePosition = { 0 };

static void UpdateDrawFrame(void);          

int main() 
{
    //
    // Variables
    //

    const int screenWidth = 1024;
    const int screenHeight = 720;


    //
    // Inits
    //

    InitWindow(screenWidth, screenHeight, "Brutalism");
    InitAudioDevice();

    const Music music = LoadMusicStream("resources/SeaShanty2.mp3"); // must be called after INITAUDIODEVICE()

    camera.position = (Vector3){ 10.0f, 10.0f, 8.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(0);     
    PlayMusicStream(music);          

    while (!WindowShouldClose())    
    {
        UpdateMusicStream(music);
        SetMusicVolume(music, 1);
        UpdateDrawFrame();
    }

    StopMusicStream(music);
    CloseWindow();     
    return 0;
}

static void UpdateDrawFrame(void)
{
    
    UpdateCamera(&camera, CAMERA_ORBITAL);
    
    BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);

        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, GREEN);

        EndMode3D();

        DrawFPS(10, 10);

    EndDrawing();
}