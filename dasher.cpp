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
    AnimData nebulae[3]{};

    for (int i = 0; i < 3; i++){
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.width/8;
        nebulae[i].pos.y = windowDimensions[1]  - nebula.height/8;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0/16.0;
    };

    nebulae[0].pos.x = windowDimensions[0];
    nebulae[1].pos.x = windowDimensions[0]+300;
    nebulae[2].pos.x = windowDimensions[0]+600;

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
        nebulae[0].pos.x += nebVel * dT;

        // update the second nebula's postion
        nebulae[1].pos.x += nebVel *dT;

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
        nebulae[0].runningTime += dT;
        if(nebulae[0].runningTime >= nebulae[0].updateTime){
            nebulae[0].runningTime = 0.0;
            // update animation frame
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            
            if (nebulae[0].frame > 7){
                nebulae[0].frame = 0;
            }
        }

        // update nebula 2 animation frame
        nebulae[1].runningTime += dT;
        if(nebulae[1].runningTime >= nebulae[1].updateTime){
            nebulae[1].runningTime = 0.0;
            // update animation frame
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            
            if (nebulae[1].frame > 7){
                nebulae[1].frame = 0;
            }
        }

        //DrawRectangle(windowWidth/2, posY, width, height, BLUE);
        // draw Nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE); 
        // dra the second nebula
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);
        
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