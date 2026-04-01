#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>

using namespace std;

void gotoxy(int column, int line);

struct Point {
    int x, y;
};

class CONRAN {
public:
    Point A[100];
    int DoDai;
    Point duoiCu; // Lưu lại vị trí đuôi cũ để xóa

    CONRAN() {
        DoDai = 3;
        A[0] = {10, 10}; // Đầu rắn
        A[1] = {11, 10}; // Thân
        A[2] = {12, 10}; // Đuôi
    }

    void Ve() {
        // Xóa đuôi cũ 
        gotoxy(duoiCu.x, duoiCu.y);
        cout << " "; 

        // Vẽ đầu và thân mới
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            if (i == 0) cout << "O"; // Đầu rắn
            else cout << "x";        // Thân rắn
        }
    }

    void DiChuyen(int Huong) {
        duoiCu = A[DoDai - 1]; // Lưu lại tọa độ đuôi trước khi di chuyển

        // Thân chạy theo đầu
        for (int i = DoDai - 1; i > 0; i--) {
            A[i] = A[i - 1];
        }

        // Cập nhật đầu rắn theo hướng WASD
        if (Huong == 0) A[0].x++; // Phải (D)
        if (Huong == 1) A[0].y++; // Xuống (S)
        if (Huong == 2) A[0].x--; // Trái (A)
        if (Huong == 3) A[0].y--; // Lên (W)
    }
};

int main() {
    CONRAN r;
    int Huong = 2; 
    char t;

    system("cls"); 

    while (true) { 
        if (kbhit()) {
            t = getch();
            if (t == 'a' && Huong != 0) Huong = 2;
            if (t == 'w' && Huong != 1) Huong = 3;
            if (t == 'd' && Huong != 2) Huong = 0;
            if (t == 's' && Huong != 3) Huong = 1; 
        }
        
        r.DiChuyen(Huong);
        r.Ve();
        
        Sleep(100); 
    }

    return 0;
}

void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}