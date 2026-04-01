#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
<<<<<<< HEAD
#include <fstream> // Thư viện đọc/ghi file (cho High Score)
=======
>>>>>>> ee51f26be13303a9c4d5dc5391c371b03e7fdace

using namespace std;

void gotoxy(int column, int line);

<<<<<<< HEAD
// ==========================================
//        CÁC HÀM XỬ LÝ UI/UX THÊM VÀO
// ==========================================

// Hàm đổi màu chữ trong Console
void TextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Hàm ẩn con trỏ chuột nhấp nháy (Giúp UX mượt mắt hơn)
void Nocursortype() {
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// Vẽ khung viền tường
void VeTuong() {
    TextColor(8); // Màu xám cho tường
    for (int i = 2; i <= 80; i++) {
        gotoxy(i, 2); cout << char(219);  // Cạnh trên
        gotoxy(i, 25); cout << char(219); // Cạnh dưới
    }
    for (int i = 2; i <= 25; i++) {
        gotoxy(2, i); cout << char(219);  // Cạnh trái
        gotoxy(80, i); cout << char(219); // Cạnh phải
    }
    TextColor(7); // Trả lại màu mặc định
}

// Bảng thông tin điểm số
void DrawHUD(int score, int highScore) {
    TextColor(14); // Màu vàng
    gotoxy(5, 1); cout << " SCORE: " << score << " ";
    gotoxy(60, 1); cout << " HIGH SCORE: " << highScore << " ";
    TextColor(7);
}

// Đọc điểm cao nhất từ file
int DocHighScore() {
    ifstream file("highscore.txt");
    int hs = 0;
    if (file.is_open()) {
        file >> hs;
        file.close();
    }
    return hs;
}

// Ghi điểm kỷ lục mới ra file
void GhiHighScore(int score) {
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << score;
        file.close();
    }
}

// Màn hình bắt đầu game
void ShowMenu() {
    system("cls");
    TextColor(10);
    gotoxy(30, 8);  cout << "=======================";
    gotoxy(30, 9);  cout << "      SNAKE GAME       ";
    gotoxy(30, 10); cout << "=======================";
    TextColor(15);
    gotoxy(30, 12); cout << "[ ENTER ] : Start Game";
    gotoxy(30, 13); cout << "[  ESC  ] : Exit";
}

// Màn hình Game Over
void ShowGameOver(int score) {
    TextColor(12); // Màu đỏ cảnh báo
    gotoxy(28, 10); cout << "===========================";
    gotoxy(28, 11); cout << "         GAME OVER         ";
    gotoxy(28, 12); cout << "      Your Score: " << score << "      ";
    gotoxy(28, 13); cout << "===========================";
    TextColor(15);
    gotoxy(27, 15); cout << "[ ENTER ] : Play Again";
    gotoxy(27, 16); cout << "[  ESC  ] : Quit to Menu";
}

// ==========================================
//        GIỮ NGUYÊN CODE GỐC CỦA TEAM
// ==========================================
=======
>>>>>>> ee51f26be13303a9c4d5dc5391c371b03e7fdace
struct Point {
    int x, y;
};

class CONRAN {
public:
    Point A[100];
    int DoDai;
<<<<<<< HEAD
    Point duoiCu;

    CONRAN() {
        DoDai = 3;
        A[0] = {10, 10};
        A[1] = {11, 10};
        A[2] = {12, 10};
    }

    void Ve() {
        gotoxy(duoiCu.x, duoiCu.y);
        cout << " ";

        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            if (i == 0) cout << "O";
            else cout << "x";
=======
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
>>>>>>> ee51f26be13303a9c4d5dc5391c371b03e7fdace
        }
    }

    void DiChuyen(int Huong) {
<<<<<<< HEAD
        duoiCu = A[DoDai - 1];

=======
        duoiCu = A[DoDai - 1]; // Lưu lại tọa độ đuôi trước khi di chuyển

        // Thân chạy theo đầu
>>>>>>> ee51f26be13303a9c4d5dc5391c371b03e7fdace
        for (int i = DoDai - 1; i > 0; i--) {
            A[i] = A[i - 1];
        }

<<<<<<< HEAD
        if (Huong == 0) A[0].x++;
        if (Huong == 1) A[0].y++;
        if (Huong == 2) A[0].x--;
        if (Huong == 3) A[0].y--;
    }
};
// ==========================================
//        KẾT THÚC CODE GỐC
// ==========================================

int main() {
    Nocursortype();  // Ẩn con trỏ nhấp nháy
    int highScore = DocHighScore();

    while (true) {
        // 1. GIAO DIỆN MENU
        ShowMenu();
        char choice;
        do {
            choice = getch();
        } while (choice != 13 && choice != 27); // 13 là Enter, 27 là ESC

        if (choice == 27) break; // Thoát hẳn

        // 2. KHỞI TẠO MÀN CHƠI MỚI
        system("cls");
        VeTuong();
        int score = 0;
        DrawHUD(score, highScore);

        CONRAN r;
        int Huong = 2;
        char t;
        bool gameOver = false;
        bool isPaused = false;

        // -> CHÈN CODE KHỞI TẠO MỒI LẦN ĐẦU CỦA TEAM VÀO ĐÂY <-

        // 3. VÒNG LẶP GAME (GAME LOOP)
        while (!gameOver) {
            // Xử lý Input
            if (kbhit()) {
                t = getch();
                if (t == 'a' && Huong != 0) Huong = 2;
                if (t == 'w' && Huong != 1) Huong = 3;
                if (t == 'd' && Huong != 2) Huong = 0;
                if (t == 's' && Huong != 3) Huong = 1;
                if (t == 'p' || t == 'P') isPaused = !isPaused; // Tạm dừng
            }

            // Xử lý Pause
            if (isPaused) {
                TextColor(14); gotoxy(36, 1); cout << " PAUSED "; TextColor(7);
                Sleep(100);
                continue;
            } else {
                gotoxy(36, 1); cout << "        ";
            }

            // Rắn di chuyển
            r.DiChuyen(Huong);

            // XỬ LÝ VA CHẠM
            // Đụng tường
            if (r.A[0].x <= 2 || r.A[0].x >= 80 || r.A[0].y <= 2 || r.A[0].y >= 25) {
                gameOver = true;
                Beep(400, 400);
            }

            // Tự cắn đuôi
            for (int i = 1; i < r.DoDai; i++) {
                if (r.A[0].x == r.A[i].x && r.A[0].y == r.A[i].y) {
                    gameOver = true;
                    Beep(400, 400);
                }
            }

            // -> CHÈN CODE XỬ LÝ ĂN MỒI, SINH MỒI MỚI VÀ TĂNG CHIỀU DÀI RẮN CỦA TEAM VÀO ĐÂY <-
            // Lưu ý: Nhớ cộng biến `score` và gọi lại hàm `DrawHUD(score, highScore);` để HUD cập nhật điểm nhé!

            // Render hình ảnh
            if (!gameOver) {
                TextColor(10); // Màu xanh lá cho rắn
                r.Ve();
                TextColor(7);
            }

            // Tốc độ game (Tùy chỉnh lại theo logic điểm của team)
            int speed = 100 - (score);
            if (speed < 30) speed = 30;
            Sleep(speed);
        }

        // 4. XỬ LÝ SAU KHI THUA
        if (score > highScore) {
            highScore = score;
            GhiHighScore(highScore);
        }

        ShowGameOver(score);
        do {
            choice = getch();
        } while (choice != 13 && choice != 27);

        if (choice == 27) break;
=======
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
>>>>>>> ee51f26be13303a9c4d5dc5391c371b03e7fdace
    }

    return 0;
}

void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
<<<<<<< HEAD
}
=======
}
>>>>>>> ee51f26be13303a9c4d5dc5391c371b03e7fdace
