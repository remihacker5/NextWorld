#include <iostream>
#include <raylib.h>

using namespace std;
class player {
    private:
        string name = "";
        string UID = "";
        int location_x = 100;
        int location_y = 100;
        int move_speed_x = 5;
        int move_speed_y = 5;

    public:

        int get_location_x () {
            return location_x;
        }
        int get_location_y () {
            return location_y;
        }
        int get_move_speed_x () {
            return move_speed_x;
        }
        int get_move_speed_y () {
            return move_speed_y;
        }

        
};



int main () {

    player localplayer;
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;


    cout << "Hello World" << endl;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Web Game!");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){

        if (IsKeyDown(KEY_W)) {
            newball.update_ball_radius(1);
        }
        if (IsKeyDown(KEY_S)) {
            newball.update_ball_radius(-1);
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircle(ball_x,ball_y,ball_radius, WHITE);
        EndDrawing();
    }

    CloseWindow();
}