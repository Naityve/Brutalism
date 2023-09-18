/*
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
*/

#include <raylib.h>
#include <rcamera.h>

#define MAX_COLUMNS 20


int main(void)
{
   
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Brutalism-DevelopmentBuild");

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    int cameraMode = CAMERA_FIRST_PERSON;

    // Generates some random columns
    float heights[MAX_COLUMNS] = { 0 };
    Vector3 positions[MAX_COLUMNS] = { 0 };
    Color colors[MAX_COLUMNS] = { 0 };

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)GetRandomValue(1, 12);
        positions[i] = (Vector3){ (float)GetRandomValue(-15, 15), heights[i]/2.0f, (float)GetRandomValue(-15, 15) };
        colors[i] = (Color){ GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255 };
    }

    DisableCursor();               
    SetTargetFPS(60);                 
    while (!WindowShouldClose())       
    {    
        cameraMode = CAMERA_FIRST_PERSON;
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
    


      
        UpdateCamera(&camera, cameraMode);                 
        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);
        /*
        DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
        DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
        DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
        DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall
        DrawPlane((Vector3){0.0f,0.5f,0.0f}, (Vector2){5,5},RED);
        */

        for (int i = 0; i < MAX_COLUMNS; i++)
        {
                    DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
                    DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
        }

        if (cameraMode == CAMERA_THIRD_PERSON)
        {
            DrawCube(camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
            DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
        }

        EndMode3D();
        EndDrawing();
    }

   
    CloseWindow();       

    return 0;
}
