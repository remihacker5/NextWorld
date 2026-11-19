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

struct WorldRect {
    float left, right, top, bottom;
};

WorldRect GetCameraWorldBounds(const Camera2D& camera, int screenWidth, int screenHeight) {
    // Handle rotation safely by checking all 4 screen corners
    Vector2 corners[4] = {
        GetScreenToWorld2D({ 0.0f, 0.0f }, camera),
        GetScreenToWorld2D({ (float)screenWidth, 0.0f }, camera),
        GetScreenToWorld2D({ 0.0f, (float)screenHeight }, camera),
        GetScreenToWorld2D({ (float)screenWidth, (float)screenHeight }, camera)
    };

    float minX = corners[0].x, maxX = corners[0].x;
    float minY = corners[0].y, maxY = corners[0].y;

    for (int i = 1; i < 4; ++i) {
        minX = std::min(minX, corners[i].x);
        maxX = std::max(maxX, corners[i].x);
        minY = std::min(minY, corners[i].y);
        maxY = std::max(maxY, corners[i].y);
    }

    return { minX, maxX, minY, maxY };
}

bool IsInView(const WorldRect& view, float x, float y, float width, float height, float margin = 32.0f) {
    return (x + width + margin >= view.left) &&
           (x - margin <= view.right) &&
           (y + height + margin >= view.top) &&
           (y - margin <= view.bottom);
}

void draw_grass(float x, float y, int randomgrass){
    static Texture2D grass1 = LoadTexture("resources/images/terrain/grass/grass1.png");
    static Texture2D grass2 = LoadTexture("resources/images/terrain/grass/grass2.png");
    static Texture2D grass3 = LoadTexture("resources/images/terrain/grass/grass3.png");
    static Texture2D grass4 = LoadTexture("resources/images/terrain/grass/grass4.png");
    static int tile_scale = 5;
    static string world_map = LoadFileText("resources/world/real_world_map.txt");
    
    if (randomgrass == 1){
        DrawTexturePro(grass1, { 0.0f, 0.0f, (float)grass1.width, (float)grass1.height }, Rectangle { x, y, (float)grass1.width*tile_scale, (float)grass1.height*tile_scale }, Vector2 {0, 0}, 0, WHITE);
        
    } else if (randomgrass == 2){
        DrawTexturePro(grass2, { 0.0f, 0.0f, (float)grass2.width, (float)grass2.height }, Rectangle { x, y, (float)grass2.width*tile_scale, (float)grass2.height*tile_scale }, Vector2 {0, 0}, 0, WHITE);
        
    } else if (randomgrass == 3){
        DrawTexturePro(grass3, { 0.0f, 0.0f, (float)grass3.width, (float)grass3.height }, Rectangle { x, y, (float)grass3.width*tile_scale, (float)grass3.height*tile_scale }, Vector2 {0, 0}, 0, WHITE);
        
    } else if (randomgrass == 4){
        DrawTexturePro(grass4, { 0.0f, 0.0f, (float)grass4.width, (float)grass4.height }, Rectangle { x, y, (float)grass4.width*tile_scale, (float)grass4.height*tile_scale }, Vector2 {0, 0}, 0, WHITE);
    }
}



class player {
    private:
        string name = "Kara1";
        string UID = "";
        Texture2D skin = LoadTexture("resources/images/player/Kara/kara-walk.png");
        int anim_frame = 0;
        int facing = -1;
        float location_x = 0.0f;
        float location_y = 0.0f;
        int move_speed_x = 5;
        int move_speed_y = 5;
        int player_scale = 5;

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

        // LOCATION GETTER AND SETTER
        int get_location_x () {
            return location_x;
        }
        int get_location_y () {
            return location_y;
        }

        void set_location_x (float new_location_x) {
            location_x = new_location_x;
            return;
        }

        void set_location_y (float new_location_y) {
            location_y = new_location_y;
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

    Texture2D grass1 = LoadTexture("resources/images/terrain/grass/grass1.png");
    int tile_scale = 5;
    string world_map = LoadFileText("resources/world/real_world_map.txt");
    int randomgrass = 1;
    player local_player = player();
    Camera2D camera = { 0 };
    camera.target = Vector2{local_player.get_location_x(), local_player.get_location_y()};
    camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;



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
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(BLUE);
        WorldRect view = GetCameraWorldBounds(camera, SCREEN_WIDTH, SCREEN_HEIGHT);
        

        float location_x = 0.0f;
        float location_y = 0.0f;
        draw_grass(location_x, location_y, randomgrass);
        for (size_t i = 0; i < world_map.length(); ++i) {
            randomgrass++;
            if (randomgrass > 4){
                randomgrass = 1;
            }
            if (world_map[i] == '#'){
                location_x += grass1.width * tile_scale;
                if (IsInView(view, location_x, location_y, grass1.width * tile_scale, grass1.height * tile_scale, 32.0f)) {
                    draw_grass(location_x, location_y, randomgrass);
                }
                
            }
            if (world_map[i] == '\n'){
            location_x = 0.0f;
            location_y += grass1.height * tile_scale;
            }
            if (world_map[i] == ' '){
            location_x += grass1.width * tile_scale;
            }            
        }
        randomgrass = 1;

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

        camera.target = Vector2{local_player.get_location_x(), local_player.get_location_y()};
        EndMode2D();
        EndDrawing();
    }

    CloseWindow();
}