#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <fstream> // Thư viện đọc/ghi file (cho High Score)

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;

void gotoxy(int column, int line);

// ==========================================
//        CÁC HÀM XỬ LÝ UI/UX THÊM VÀO
// ==========================================

// Hàm đổi màu chữ trong Console
void TextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Hàm ẩn con trỏ chuột nhấp nháy 
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
    gotoxy(28, 11); cout << "          GAME OVER         ";
    gotoxy(28, 12); cout << "      Your Score: " << score << "      ";
    gotoxy(28, 13); cout << "===========================";
    TextColor(15);
    gotoxy(27, 15); cout << "[ ENTER ] : Play Again";
    gotoxy(27, 16); cout << "[  ESC  ] : Quit to Menu";
}

// ==========================================
//        GIỮ NGUYÊN CODE GỐC CỦA TEAM
// ==========================================
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
        // Đặt tọa độ từ nhánh Map-and-food để tránh tự cắn khi mới vào
        A[0] = {12, 10}; // Đầu
        A[1] = {11, 10}; // Thân
        A[2] = {10, 10}; // Đuôi
        duoiCu = {0, 0};
    }

    void Ve() {
        gotoxy(duoiCu.x, duoiCu.y);
        cout << " "; 

        // Vẽ rắn mới
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            if (i == 0) cout << "O"; 
            else cout << "x";        
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

// ==========================================
//        KẾT THÚC CODE GỐC
// ==========================================

int main() {
    Nocursortype();  // Ẩn con trỏ nhấp nháy
    srand(time(NULL)); 
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
        VeTuong(); // Vẽ tường UI (Khung lớn)
        int score = 0;
        DrawHUD(score, highScore);

        CONRAN r; 
        Point food = {15, 5}; 
        int Huong = 0; // Đi sang phải cho khớp tọa độ khởi tạo
        char t;
        bool gameOver = false;
        bool isPaused = false;

        // Vẽ mồi lần đầu
        gotoxy(food.x, food.y);
        cout << "*";

        // 3. VÒNG LẶP GAME (GAME LOOP)
        while (!gameOver) { 
            // Xử lý Input
            if (kbhit()) {
                t = getch();
                if ((t == 'a' || t == 'A') && Huong != 0) Huong = 2;
                if ((t == 'w' || t == 'W') && Huong != 1) Huong = 3;
                if ((t == 'd' || t == 'D') && Huong != 2) Huong = 0;
                if ((t == 's' || t == 'S') && Huong != 3) Huong = 1; 
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

            // XỬ LÝ ĂN MỒI
            if (r.AnMoi(food)) {
                score += 10;
                DrawHUD(score, highScore);
                // Tạo tọa độ mồi mới (Giới hạn trong khung VeTuong)
                food.x = rand() % (78 - 3 + 1) + 3;
                food.y = rand() % (23 - 3 + 1) + 3;
                gotoxy(food.x, food.y);
                cout << "*";
            }

            // XỬ LÝ VA CHẠM
            // Đụng tường (Theo khung VeTuong)
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

            // Render hình ảnh
            if (!gameOver) {
                TextColor(10); // Màu xanh lá cho rắn
                r.Ve();
                TextColor(7);  
            }
            
            // Tốc độ game
            int speed = 100 - (score / 5);
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
    }

    return 0;
}

// Cần định nghĩa hàm gotoxy ở cuối để code chạy được
void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
