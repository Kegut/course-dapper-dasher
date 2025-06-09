#include "raylib.h"

struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main(){
    // Set variables for window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;
    
    // initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

    // Acceleration due to gravity (pixel/s)/s
    const int gravity{1000};

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    
    // AnimData for nebula
    AnimData nebData{ 
        {0.0, 0.0, static_cast<float>(nebula.width/8.0), static_cast<float>(nebula.height/8.0)}, // Rectangle rec
        {static_cast<float>(windowDimensions[0]), static_cast<float>(windowDimensions[1] - nebula.height/8.0)}, // Vector2 pos
        0, // int frame
        1.0/12.0, // float updateTime
        0 // float runningTime
    };

    AnimData neb2Data{ 
        {0.0, 0.0, static_cast<float>(nebula.width/8.0), static_cast<float>(nebula.height/8.0)}, // Rectangle rec
        {static_cast<float>(windowDimensions[0] + 300 ), static_cast<float>(windowDimensions[1] - nebula.height/8.0)}, // Vector2 pos
        0, // int frame
        1.0/16.0, // float updateTime
        0 // float runningTime
    };

    // nebula X velocity (pixel/second)
    int nebVel{-400};

    // Scarfy texture variable
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    // Is the rectangle in the air
    bool isInAir{false};
    // jump velocity pixel per second
    const int jumpVel{-600};

    int velocity{0};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        // detalta time (time since last frame)
        const float dT{GetFrameTime()};

        //Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Start gaming logic

        // Perform ground check
        if(scarfyData.pos.y >= (windowDimensions[1] - scarfyData.rec.height)){
            // rectangle is on the ground
            // apply gravity
            velocity = 0;
            isInAir = false;
        }else{
            // rectangle is in the air
            // apply gravity
            velocity += gravity * dT;
            isInAir = true;
        }

        // Jump check
        if(IsKeyPressed(KEY_SPACE) && !isInAir){
            velocity += jumpVel;
        }

        // update nebula position
        nebData.pos.x += nebVel * dT;

        // update the second nebula's postion
        neb2Data.pos.x += nebVel *dT;

        // update scarfy position
        scarfyData.pos.y += velocity * dT;
        
        // update scarfy animation frame
        if(!isInAir){
            // update running time
            scarfyData.runningTime += dT;

            if(scarfyData.runningTime >= scarfyData.updateTime){
                scarfyData.runningTime = 0.0;
                // update animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;

                if (scarfyData.frame > 5){
                    scarfyData.frame = 0;
                }
            }
        
        }
        
        // update nebula animation frame
        nebData.runningTime += dT;
        if(nebData.runningTime >= nebData.updateTime){
            nebData.runningTime = 0.0;
            // update animation frame
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            
            if (nebData.frame > 7){
                nebData.frame = 0;
            }
        }

        // update nebula 2 animation frame
        neb2Data.runningTime += dT;
        if(neb2Data.runningTime >= neb2Data.updateTime){
            neb2Data.runningTime = 0.0;
            // update animation frame
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            
            if (neb2Data.frame > 7){
                neb2Data.frame = 0;
            }
        }

        //DrawRectangle(windowWidth/2, posY, width, height, BLUE);
        // draw Nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE); 
        // dra the second nebula
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);
        
        //draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Stop drawing
        EndDrawing();
    }
    // Unload the texture
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    // Closing window properly
    CloseWindow();
}