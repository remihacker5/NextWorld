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
        string name = "";
        string UID = "";
        string skin = "";
        int location_x = 100;
        int location_y = 100;
        int move_speed_x = 5;
        int move_speed_y = 5;
        Texture2D Remi_skin = LoadTexture("resources/images/player/Remi/Remi.png"); 
        Texture2D Kara_skin = LoadTexture("resources/images/player/Kara/Kara.png"); 

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
        string get_skin () {
            return skin;
        }

        void set_skin (string newskin) {
            skin = newskin;
            return;
        }

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


    // Draw the player character based on their skin and location
        void draw_player(){
            if (skin == "Remi") {
                DrawTextureEx(Remi_skin, Vector2 {location_x, location_y}, 0.0, 5, WHITE);
            } 
            else if (skin == "Kara") {
                // Draw Kara skin here
                DrawTextureEx(Kara_skin, Vector2 {location_x, location_y}, 0.0, 5, WHITE);
            }
        }
};



int main () {


    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NextWorld - PreAlpha 1");
    SetTargetFPS(60);
    log("Screen init SUCCESS");
    
    player local_player = player();
    cout << "Please Enter your characters name: ";
    string newname;
    cin >> newname;
    local_player.set_name(newname);

    cout << "Please Enter your characters skin (Options are Remi or Kara): ";
    string newskin;
    cin >> newskin;
    local_player.set_skin(newskin);



    while (WindowShouldClose() == false){
        local_player.draw_player();

        if (IsKeyDown(KEY_W)) {
            
        }
        if (IsKeyDown(KEY_A)) {
            
        }
        if (IsKeyDown(KEY_S)) {
            
        }
        if (IsKeyDown(KEY_D)) {
            
        }


        BeginDrawing();
            ClearBackground(BLACK);
        
        EndDrawing();
    }

    CloseWindow();
}