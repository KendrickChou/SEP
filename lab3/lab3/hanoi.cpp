#include "termio.h"
#include "stack.h"

// Do not delete the following line
char Termio::buffer[Termio::CANVAS_HEIGHT][Termio::CANVAS_WIDTH + 1];

//1 base
stack<int> rod[3];

stack<int> X,Y;

int disks_num = 0;

void write_hi(){
    for(int i = 0; i < 41; ++i){
        Termio::buffer[10][i] = '-';
    }
    for(int j = 5; j < 41; j += 15){
        for(int i = 0; i < 11; ++i){
            Termio::buffer[i][j] = '|';
        }
     }
    for(int i = 0; i < 3; ++i){
        for(int j = rod[i].size;j > 0; --j){
            int disk_size = rod[i].visit(j);
            int col = 5 + 15 * i - disk_size;
            int line = 11 - 2*(rod[i].size - j + 1);
            for(int k = 0; k < (disk_size * 2 + 1); ++k)
               {
                Termio::buffer[line][col] = '*';
                ++col;
                }
        }
    }
}

bool check(){
    bool flag = (rod[1].size == disks_num);
    if(flag){
        Termio::ResetBuffer();
        write_hi();
        Termio::Clear();
        Termio::Draw();
        std::cout << "Congratulations! You win!" << std::endl;
        return flag;
    }
    else return false;
}

void refresh(){
    Termio::Clear();
    Termio::ResetBuffer();
    write_hi();
    Termio::Draw();
}

void hanoi(int n,int A,int B,int C){
    if(n == 1) {
        rod[B].push(rod[A].pop());
        std::cout << "Auto moving:" << A + 1 << "->" << B + 1 << '\n';
        Termio::ResetBuffer();
        write_hi();
        Termio::Draw();
    }
    else{
        hanoi(n-1,A,C,B);
        rod[B].push(rod[A].pop());
        std::cout << "Auto moving:" << A + 1 << "->" << B + 1 << '\n';
        Termio::ResetBuffer();
        write_hi();
        Termio::Draw();
        hanoi(n-1,C,B,A);
    }
}

void reversion(){
    while(X.size != 0){
        int x = X.pop();
        int y = Y.pop();
        rod[x].push(rod[y].pop());
        std::cout << "Auto moving:" << y + 1 << "->" << x+1 << '\n';
        Termio::ResetBuffer();
        write_hi();
        Termio::Draw();
    }
}

void AutoPlay(){
    reversion();
    hanoi(disks_num,0,1,2);
};

void run(char sym){
    disks_num = sym - '0';
    rod[1].clear();
    rod[2].clear();
    rod[0].clear();
    X.clear();
    Y.clear();
    for(int i = disks_num; i > 0; --i){
         rod[0].push(i);
    }
    while(!check()){
        int x,y;
        while(true){
            Termio::ResetBuffer();
            write_hi();
            Termio::Clear();
            Termio::Draw();
            std::cout << "Move a disk. Format: x y" << std::endl;
            cin >> x >> y;
            if(x <= 3 && x > 0 && y <= 3 && y > 0){
                --x,--y;
                if(x == y || x > 2 || x < 0 || y > 2 || y < 0){
                    continue;
                }
                if(rod[x].size == 0) continue;
                if(rod[y].size == 0){
                    int move_disk = rod[x].pop();
                    rod[y].push(move_disk);
                    X.push(x),Y.push(y);
                    break;
                }
                if(rod[x].visit(1) > rod[y].visit(1)) continue;
                else{
                    int move_disk = rod[x].pop();
                    rod[y].push(move_disk);
                    X.push(x),Y.push(y);
                    break;
                }
            }
            else if(x == 0 && y ==0){
                AutoPlay();
                break;
            }
        }
    }
}

int main() {
    while(true){
        std::cout << "How many disks do you want? (1 ~ 5)" << std::endl;
        string sym;
        std::cin >> sym;
        if(sym.size() != 1) continue;
        else{
            char cmd = sym[0];
            if(cmd == 'Q') return 0;
            else if(cmd - '0' > 5 || cmd - '0' < 1) continue;
            else {
                run(cmd);
            }
        }
    }
    return 0;
}
// some output hints that you should use.
//    std::cout << "How many disks do you want? (1 ~ 5)" << std::endl;
//    std::cout << "Move a disk. Format: x y" << std::endl;
//    std::cout << "Auto moving:1->2" << std::endl;
//    std::cout << "Congratulations! You win!" << std::endl;
