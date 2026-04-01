#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>

using namespace std;

// 1. Định nghĩa hằng số (Phải đặt ở đầu)
const int WIDTH = 40;
const int HEIGHT = 20;

void gotoxy(int column, int line);

struct Point {
    int x, y;
};

// 2. Hàm vẽ khung bản đồ
void VeBanDo() {
    for (int i = 0; i <= WIDTH; i++) {
        gotoxy(i, 0); cout << "#";           // Tường trên
        gotoxy(i, HEIGHT); cout << "#";      // Tường dưới
    }
    for (int i = 0; i <= HEIGHT; i++) {
        gotoxy(0, i); cout << "#";           // Tường trái
        gotoxy(WIDTH, i); cout << "#";       // Tường phải
    }
}

class CONRAN {
public:
    Point A[100];
    int DoDai;
    Point duoiCu; 

    CONRAN() {
        DoDai = 3;
        // Đặt tọa độ sao cho đầu nằm trước thân để không tự cắn khi mới vào
        A[0] = {12, 10}; // Đầu
        A[1] = {11, 10}; // Thân
        A[2] = {10, 10}; // Đuôi
        duoiCu = {0, 0};
    }

    void Ve() {
        // Xóa đuôi cũ 
        gotoxy(duoiCu.x, duoiCu.y);
        cout << " "; 

        // Vẽ rắn mới
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            if (i == 0) cout << "O"; // Đầu rắn
            else cout << "x";        // Thân rắn
        }
    }

    void DiChuyen(int Huong) {
        duoiCu = A[DoDai - 1]; 

        for (int i = DoDai - 1; i > 0; i--) {
            A[i] = A[i - 1];
        }

        if (Huong == 0) A[0].x++; // Phải
        if (Huong == 1) A[0].y++; // Xuống
        if (Huong == 2) A[0].x--; // Trái
        if (Huong == 3) A[0].y--; // Lên
    }

    bool AnMoi(Point food) {
        if (A[0].x == food.x && A[0].y == food.y) {
            DoDai++;
            return true;
        }
        return false;
    }

};

int main() {
    srand(time(NULL)); 
    CONRAN r;
    Point food = {15, 5}; 
    int Huong = 0; // Để mặc định là 0 (đi sang phải) cho khớp với tọa độ khởi tạo
    char t;
    bool dangChoi = true

    system("cls"); 
    VeBanDo();

    while (dangChoi) { 
        if (kbhit()) {
            t = getch();
            if ((t == 'a' || t == 'A') && Huong != 0) Huong = 2;
            if ((t == 'w' || t == 'W') && Huong != 1) Huong = 3;
            if ((t == 'd' || t == 'D') && Huong != 2) Huong = 0;
            if ((t == 's' || t == 'S') && Huong != 3) Huong = 1; 
        }
        
        r.DiChuyen(Huong);

        if (r.AnMoi(food)) {
            food.x = rand() % (WIDTH - 2) + 1;
            food.y = rand() % (HEIGHT - 2) + 1;
        }

        gotoxy(food.x, food.y);
        cout << "*"; // Vẽ mồi

        r.Ve();
        
        Sleep(100); 
    }

    return 0;
}

// 3. Định nghĩa hàm gotoxy ở cuối
void gotoxy(int column, int line) {
    COORD coord = {(SHORT)column, (SHORT)line};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}