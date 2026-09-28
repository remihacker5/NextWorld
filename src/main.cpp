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
    cout << "[GAME LOG] - " + msg << endl;
}


class player {
    private:
        string name = "Kara1";
        string UID = "";
        Texture2D skin = LoadTexture("resources/images/player/Kara/Kara.png");
        
        float location_x = 100;
        float location_y = 100;
        int move_speed_x = 5;
        int move_speed_y = 5;

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
            if (direction_x > 0) {
                // Play the walking animation for the player character to the right
            }
            if (direction_x < 0) {
                // Play the walking animation for the player character to the left
                skin = LoadTexture("resources/images/player/Kara/Kara_walk_left.png");
            }
            if (direction_y > 0) {
                // Play the walking animation for the player character downwards
            }
            if (direction_y < 0) {
                // Play the walking animation for the player character upwards
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
            }
            if (direction_x < 0) {
                // Play the walking animation for the player character to the left

            }
            if (direction_y > 0) {
                // Play the walking animation for the player character downwards
            }
            if (direction_y < 0) {
                // Play the walking animation for the player character upwards
            }
            location_x += direction_x * move_speed_x;
            location_y += direction_y * move_speed_y;

        }

    // Draw the player character based on their skin and location
        void draw_player(){
            DrawTextureEx(skin, Vector2 {location_x, location_y}, 0.0, 5, WHITE);
        }
};



int main () {

    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
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
        }


        BeginDrawing();
            ClearBackground(BLACK);
        
        EndDrawing();
    }

    CloseWindow();
}