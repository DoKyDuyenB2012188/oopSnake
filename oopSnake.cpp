#include<iostream>
#include"mylib.h"
using namespace std;
struct position {
    int x, y;
};
class field_cls {
    static const int height = 26;
    static const int width = 100;
public:
    field_cls() {
    }
    void wall_up_down(int x, int y, int lie) {
        while (x <= lie) {
            gotoXY(x, y);
            cout << "+";
            x++;
        }
    }
    void wall_both_sides(int x, int y, int stand) {
        while (y <= stand) {
            gotoXY(x, y);
            cout << "+";
            y++;
        }
    }
    void map1() {
        wall_up_down(10, 1, width);
        wall_up_down(10, 26, width);
        wall_both_sides(10, 1, height);
        wall_both_sides(100, 1, height);
    }
    void map2() {

    }//... tu thiet ke them
    int get_width() const { return width; }
    int get_height() const { return height; }
}field;

class food_cls {
    position pos;
    char symbol;
public:
    food_cls() :symbol('X'), pos() {
        pos.x = pos.y = -1;
    }
    void create_food() {
        pos.x = rand() % (99 - 11 + 1) + 11;
        pos.y = rand() % (25 - 2 + 1) + 2;
        gotoXY(pos.x, pos.y);
        cout << symbol;
    }
    int get_x() const { return pos.x; }
    int get_y() const { return pos.y; }
    char get_symbol() const { return symbol; }
}food;
class snake_cls : public food_cls{
    enum{UP, DOWN, LEFT, RIGHT} dir;
    char symbol, head_symbol;
    position pos[100];
    position& head;
    int speed;
    int size;
public:
    snake_cls(int x, int y) :symbol('#'), head_symbol('@'),
        pos(), speed(1), size(1), dir(RIGHT),
        head(pos[0])
    {
        pos[0].x = x;
        pos[0].y = y;
    }
    bool eat_food() {
        if (food.get_x() == head.x && food.get_y() == head.y) {
            size += 1;
            return true;
        }
        return false;
    }
    void get_input() {
        if (GetAsyncKeyState(VK_UP) && dir != DOWN) {
            dir = UP;
        }
        if (GetAsyncKeyState(VK_DOWN) && dir != UP) {
            dir = DOWN;
        }
        if (GetAsyncKeyState(VK_LEFT) && dir != RIGHT) {
            dir = LEFT;
        }
        if (GetAsyncKeyState(VK_RIGHT) && dir != LEFT) {
            dir = RIGHT;
        }
    }
    void move() {
        position next = { 0, 0 };
        switch (dir) {
        case UP:
            next.y = -speed;
            break;
        case DOWN:
            next.y = speed;
            break;
        case LEFT:
            next.x = -speed;
            break;
        case RIGHT:
            next.x = speed;
        }
        for (int c = size - 1; c > 0; --c) {
            pos[c] = pos[c - 1];
        }
        head.x += next.x;
        head.y += next.y;
        
    }
    void gameOver() {
        for (int i = 1;i < size;i++) {
            if ((head.x == pos[i].x) && (head.y == pos[i].y)) {
                throw "DEADD!!!!";
            }
        }
        if (head.x < 0 || head.y < 0 || head.x >= field.get_width() || head.y >= field.get_height()) {
            throw "DEADD!!!!";
        }
    }
    void draw() {
        for (int i = 0; i < size; i++) {
            gotoXY(pos[i].x, pos[i].y);
            if (i == 0) {
                cout << head_symbol;
            }
            else {
                cout << symbol;
            }
        }
    }
    void clear() {
        for (int i = 0;i < size;i++) {
            gotoXY(pos[i].x, pos[i].y);
            cout << " ";
        }
    }
}snake(50,13);
int main() {
    field.map1();
    food.create_food();
    while (1) {
        snake.clear();
        snake.get_input();
        snake.move();
        
        try {
            snake.gameOver();
        }
        catch (const char* er) {
            cerr << er << endl;
            system("pause");
            return -1;
        }
        snake.draw();
        if (snake.eat_food()) {
            food.create_food();
        }
        Sleep(1000 / 5);
    }

    return 0;
}