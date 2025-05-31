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
    const int windowWidth{800};
    const int windowHeight{480};

    // initialize the window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    // Acceleration due to gravity (pixel/s)/s
    const int gravity{1000};

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0 , nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    Rectangle neb2Rec{0.0, 0.0 , nebula.width/8, nebula.height/8};
    Vector2 neb2Pos{windowWidth + 300, windowHeight - neb2Rec.height};
    
    // Nebula animation variables  
    int nebFrame{};
    const float nebUpdateTime(1.0/12.0);
    float nebRunningTime{0.0};

    int neb2Frame{};
    const float neb2UpdateTime{1.0/16.0};
    float neb2RunningTime;

    // nebula X velocity (pixel/second)
    int nebVel{-400};

    // Scarfy texture variable
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // animation frame
    int frame{0};

    // Update time
    const float updateTime{1.0/12.0};
    float runningTime{0.0};

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
        if(scarfyPos.y >= (windowHeight - scarfyRec.height)){
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
        nebPos.x += nebVel * dT;

        // update the second nebula's postion
        neb2Pos.x += nebVel *dT;

        // update scarfy position
        scarfyPos.y += velocity * dT;
        
        // update scarfy animation frame
        if(!isInAir){
            // update running time
            runningTime += dT;

            if(runningTime >= updateTime){
                runningTime = 0.0;
                // update animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;

                if (frame > 5){
                    frame = 0;
                }
            }
        
        }
        
        // update nebula animation frame
        nebRunningTime += dT;
        if(nebRunningTime >= nebUpdateTime){
            nebRunningTime = 0.0;
            // update animation frame
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            
            if (nebFrame > 7){
                nebFrame = 0;
            }
        }

        // update nebula 2 animation frame
        neb2RunningTime += dT;
        if(neb2RunningTime >= neb2UpdateTime){
            neb2RunningTime = 0.0;
            // update animation frame
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            
            if (neb2Frame > 7){
                neb2Frame = 0;
            }
        }

        //DrawRectangle(windowWidth/2, posY, width, height, BLUE);
        // draw Nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE); 
        // dra the second nebula
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);
        
        //draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Stop drawing
        EndDrawing();
    }
    // Unload the texture
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    // Closing window properly
    CloseWindow();
}