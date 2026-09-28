// unoffical table of contents
// get libraries

// Declare classes and functions

// in main function:
// get player information
// set everything up for game engine
// create list of players
// create list of objects
// create world

// While game running:
// get updates
// draw players, objects, world. 


#include <iostream>
#include <raylib.h>
using namespace std;

void log(string msg){
    //cout << "[GAME LOG] - " + msg << endl;
}


class player {
    private:
        string name = "Kara1";
        string UID = "";
        Texture2D skin = LoadTexture("resources/images/player/Remi/Remi-walk.png");
        int anim_frame = 0;
        int facing = -1;
        float location_x = 100;
        float location_y = 100;
        int move_speed_x = 5;
        int move_speed_y = 5;
        int player_scale = 10;

        // LOCATION GETTER AND SETTER
        int get_location_x () {
            return location_x;
        }
        int get_location_y () {
            return location_y;
        }

        void set_location_x (int new_location_x) {
            location_x = new_location_x;
            return;
        }

        void set_location_y (int new_location_y) {
            location_y = new_location_y;
            return;
        }

        // MOVE SPEED GETTER AND SETTER
        int get_move_speed_x () {
            return move_speed_x;
        }
        int get_move_speed_y () {
            return move_speed_y;
        }
         
        void play_walking_animation(int direction_x, int direction_y) {
            
                // Play the walking animation for the player character to the right
                static int frames = 0;
                frames++;

                if (anim_frame == 0 && frames == 10){
                    frames = 0;
                    anim_frame = 1;
                } 
                else if (anim_frame == 1 && frames == 10){
                    frames = 0;
                    anim_frame = 2;
                }
                else if (anim_frame == 2 && frames == 10){
                    frames = 0;
                    anim_frame = 3;
                }
                else if (anim_frame == 3 && frames == 10){
                    frames = 0;
                    anim_frame = 0;
                }
        }

    public:
    // NAME GETTER AND SETTER
        string get_name () {
            return name;
        }

        void set_name (string newname) {
            name = newname;
            return;
        }

    // SKIN GETTER AND SETTER
        Texture2D get_skin () {
            return skin;
        }

        void set_skin (Texture2D newskin) {
            skin = newskin;
            return;
        }

        void walk(int direction_x, int direction_y) {
            
            if (direction_x > 0) {
                // Play the walking animation for the player character to the right
                facing = 1;
                play_walking_animation(direction_x, direction_y);
            }
            if (direction_x < 0) {
                // Play the walking animation for the player character to the left
                facing = -1;
                play_walking_animation(direction_x, direction_y);
            }
            if (direction_y > 0) {
                // Play the walking animation for the player character downwards
                play_walking_animation(direction_x, direction_y);
            }
            if (direction_y < 0) {
                // Play the walking animation for the player character upwards
                play_walking_animation(direction_x, direction_y);
            }
            if (direction_x == 0 && direction_y == 0){
                anim_frame = 0;
                return;
            }
            location_x += direction_x * move_speed_x;
            location_y += direction_y * move_speed_y;

        }

    // Draw the player character based on their skin and location
        void draw_player(){
            DrawTexturePro(skin, { (float)skin.width/4*anim_frame, 0.0f, (float)skin.width/4 * facing, (float)skin.height }, Rectangle { location_x, location_y, (float)skin.width/4*player_scale, (float)skin.height*player_scale }, Vector2 {0, 0}, 0, WHITE);
        }
};



int main () {

    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
    int framesCounter = 0;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NextWorld - PreAlpha 1");
    SetTargetFPS(60);
    log("Screen init SUCCESS");
    player local_player = player();

    /*
    This is where you would initialize the local player's name and skin.

    cout << "Please Enter your characters name: ";
    string newname;
    cin >> newname;
    local_player.set_name(newname);

    cout << "Please Enter your characters skin (Options are Remi or Kara): ";
    string newskin;
    cin >> newskin;
    local_player.set_skin(newskin);
    */


    while (WindowShouldClose() == false){
        framesCounter++;
        local_player.draw_player();

        if (IsKeyDown(KEY_W)) {
            local_player.walk(0, -1);
        }
        if (IsKeyDown(KEY_A)) {
            local_player.walk(-1, 0);
        }
        if (IsKeyDown(KEY_S)) {
            local_player.walk(0, 1);
        }
        if (IsKeyDown(KEY_D)) {
            local_player.walk(1, 0);
        } if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_D)) {
            local_player.walk(0, 0);
        }


        BeginDrawing();
            ClearBackground(BLUE);
        
        EndDrawing();
    }

    CloseWindow();
}