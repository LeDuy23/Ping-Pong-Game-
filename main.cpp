#include <iostream>
#include <raylib.h>

using namespace std;

class Ball {
    public:
    float x,y;
    int speed_x;
    int speed_y; 
    int radius; 
    void Draw() {
        DrawCircle(x,y,radius, WHITE);
    }
    void update() { 
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0 ){
            speed_y *= -1; 
        }
         if(x + radius >= GetScreenWidth()|| x- radius <= 0){
            speed_x *= -1; 
        }
    }
};

class Paddle {
 protected: 
 void LimitMovement() {
    if(y <= 0) {
        y = 0; 
    }
    if(y + height >= GetScreenHeight()) {
        y = GetScreenHeight() - height;

    }
 }
 public:
 float x,y;
 float width,height; 
 int speed; 

  void Draw() {
   DrawRectangle(x, y, width, height, WHITE);

  }
  void Update() { 
    if(IsKeyDown(KEY_UP)) {
        y = y - speed;
    }
    if(IsKeyDown(KEY_DOWN)) {
        y = y + speed;
    }
    LimitMovement(); 
  }

};

class CpuPaddle: public Paddle { 
 public: 
 void Update(int ball_y) { 
    if(y+ height/2 > ball_y) {
        y = y -speed; 
    }
    if(y + height/2 <= ball_y) {
        y = y + speed;
    }
    LimitMovement(); 
 }
};

Ball ball;
Paddle player;
CpuPaddle Cpu; 


int main () {

 cout << "Starting the game..." << endl;
 const int screen_width = 1280; 
 const int screen_height= 800;
 InitWindow(screen_width,screen_height, "Ping Pong"); 
 SetTargetFPS(60);

 ball.radius = 20; 
 ball.x = screen_width/2;
 ball.y= screen_height/2;
 ball.speed_x = 7; 
 ball.speed_y = 7;  
 
 player.width = 25; 
 player.height = 120;
 player.x = screen_width - player.width - 10;
 player.y = screen_height/2 - player.height/2;
 player.speed = 6;

 Cpu.width = 25; 
 Cpu.height = 120;
 Cpu.x = 10;
 Cpu.y = screen_height/2 - Cpu.height/2;
 Cpu.speed = 6;


 while(WindowShouldClose() == false) {
    BeginDrawing();
    // Update 
    ball.update();
    player.Update();
    Cpu.Update(ball.y);
   // Drawing 
    ClearBackground(BLACK);
    DrawLine(screen_width/2 , 0, screen_width/2 , screen_height,WHITE);
    ball.Draw(); 
    Cpu.Draw(); 
    player.Draw();
    EndDrawing();
}



CloseWindow(); 

return 0; 
}