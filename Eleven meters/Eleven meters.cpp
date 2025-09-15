#include "raylib.h"
#include <iostream>

const int screenWidth = 800;
const int screenHeight = 450;

// Переменная для хранения текущего цвета фона
Color backgroundColor = RAYWHITE;

void MoveRectangle(Rectangle& rec, bool controls) 
{
    if ((controls && IsKeyDown(KEY_UP)) || (!controls && IsKeyDown(KEY_W))) {
        rec.y += -5;
    }
    if ((controls && IsKeyDown(KEY_LEFT)) || (!controls && IsKeyDown(KEY_A))) {
        rec.x += -5;
    }
    if ((controls && IsKeyDown(KEY_RIGHT)) || (!controls && IsKeyDown(KEY_D))) {
        rec.x += 5;
    }
    if ((controls && IsKeyDown(KEY_DOWN)) || (!controls && IsKeyDown(KEY_S))) {
        rec.y += 5;
    }
    if (rec.x + rec.width > screenWidth) {
        rec.x = screenWidth - rec.width - 2;
    }
    if (rec.x < 0) {
        rec.x = 2;
    }
    if (rec.y + rec.height > screenHeight) {
        rec.y = screenHeight - rec.height - 2;
    }
    if (rec.y < 0) {
        rec.y = 2;
    }
}

// Функция для изменения цвета фона
void ChangeBackgroundColor() 
{
    // Создаем массив с разными цветами
    Color colors[] = 
    {
        RAYWHITE,   
        LIGHTGRAY,  
        GRAY,       
        DARKGRAY,  
        YELLOW,     
        GOLD,      
        ORANGE,    
        PINK,      
        RED,        
        MAROON,    
        GREEN,      
        LIME,       
        DARKGREEN,  
        SKYBLUE,   
        BLUE,      
        DARKBLUE,   
        PURPLE,     
        VIOLET,     
        DARKPURPLE, 
        BEIGE,      
        BROWN,      
        DARKBROWN, 
        BLACK       
    };

    static int currentColorIndex = 0;
    currentColorIndex = (currentColorIndex + 1) % (sizeof(colors) / sizeof(colors[0]));
    backgroundColor = colors[currentColorIndex];
}

int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    Image image = LoadImage("рамзан кадыров.png");
    Image image2 = LoadImage("Шеврон_спецназа_«Ахмат».png");
    ImageResize(&image, 132, 114);

    Texture2D texture = LoadTextureFromImage(image);
    Texture2D texture2 = LoadTextureFromImage(image2);

    Rectangle rec = { screenWidth / 2 - 50, screenHeight / 2 - 50, 100, 100 };
    Rectangle rec2 = { screenWidth / 4 - 50, screenHeight / 4 - 50, 100, 100 };

    // Создаем кнопку для изменения фона
    Rectangle changeBgButton = { 10, 10, 220, 40 };
    bool buttonPressed = false;

    while (!WindowShouldClose())
    {
        MoveRectangle(rec, false);
        MoveRectangle(rec2, true);

        // Проверяем нажатие на кнопку
        if (CheckCollisionPointRec(GetMousePosition(), changeBgButton) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ChangeBackgroundColor();
            buttonPressed = true;
        }
        else {
            buttonPressed = false;
        }

        BeginDrawing();

        // Очищаем экран текущим цветом фона
        ClearBackground(backgroundColor);

        // Рисуем кнопку
        DrawRectangleRec(changeBgButton, buttonPressed ? DARKGRAY : LIGHTGRAY); // тернарная операция
        DrawRectangleLinesEx(changeBgButton, 2, BLACK);
        DrawText("Change background", changeBgButton.x + 10, changeBgButton.y + 10, 20, BLACK);

        DrawRectangleRec(rec, BLUE);
        DrawRectangleRec(rec2, RED);
        DrawText("Bob", rec.x, rec.y, 20, BLACK);
        DrawText("John", rec2.x, rec2.y, 20, BLACK);
        DrawTexture(texture, rec.x, rec.y, WHITE);
        DrawTexture(texture2, rec2.x, rec2.y, WHITE);

        EndDrawing();
    }

    UnloadTexture(texture);
    UnloadTexture(texture2);
    CloseWindow();

    return 0;
}