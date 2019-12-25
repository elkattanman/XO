#include <bits/stdc++.h>
using namespace std;

string its(int x){
    string ret;
    stringstream ss;
    ss<<x;
    ss>>ret;
    return  ret;
}

class Point {
private:
    int x, y;
public:
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Point() {}

    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    string toString() {
        return "[" + its(x) + ", " + its(y) + "]";
    }
};

class PointAndScore {
private:
    int score;
    Point point;
public:
    PointAndScore(int score, Point point) : score(score),point(point) {}
};

class Board {
private:
    vector<Point> availablePoints;
    int board[3][3];
    Point computersMove;
public :
    Board(){
        resetBoard();
    }
    bool isGameOver() {
        //Game is over is someone has won, or board is full (draw)
        return (hasXWon() || hasOWon() || getAvailableStates().size() == 0);
    }

    bool hasXWon() {
        if ((board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] == 1) ||
                (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] == 1)) {
            //System.out.println("X Diagonal Win");
            return true;
        }
        for (int i = 0; i < 3; ++i) {
            if (((board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] == 1)
                    || (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] == 1))) {
                // System.out.println("X Row or Column win");
                return true;
            }
        }
        return false;
    }

    bool hasOWon() {
        if ((board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] == 2) ||
                (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] == 2)) {
            // System.out.println("O Diagonal Win");
            return true;
        }
        for (int i = 0; i < 3; ++i) {
            if ((board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] == 2)
                    || (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] == 2)) {
                //  System.out.println("O Row or Column win");
                return true;
            }
        }

        return false;
    }

     vector<Point> getAvailableStates() {
        availablePoints.clear() ;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == 0) {
                    availablePoints.push_back(Point(i, j));
                }
            }
        }
        return availablePoints;
    }

    void placeAMove(Point point, int player) {
        board[point.getX()][point.getY()] = player;   //player = 1 for X, 2 for O
    }

    void takeHumanInput() {
        cout<<"Your move: ";
        int x,y;
        cin>>x>>y;
        while((board[x][y])){
            cout<<"Enter Valid Case:";
            cin>>x>>y;
        }
        Point point(x, y);
        placeAMove(point, 2);
    }

    void displayBoard() {
        cout<<endl;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout<<board[i][j] << " ";
            }
            cout<<endl;

        }
    }

    int minimax(int depth, int turn) {
        if (hasXWon()) return +1;
        if (hasOWon()) return -1;

        vector<Point> pointsAvailable = getAvailableStates();
        if (pointsAvailable.size() == 0) return 0;

            int MN = INT_MAX, MX = INT_MIN;

        for (int i = 0; i < pointsAvailable.size(); ++i) {
            Point point = pointsAvailable[i];
            if (turn == 1) {
                placeAMove(point, 1);
                int currentScore = minimax(depth + 1, 2);
                MX = max(currentScore, MX);

                if(depth == 0)cout<<"Score for position "<<(i+1)<<" = "<<currentScore<<endl;
                if(currentScore >= 0){ if(depth == 0) computersMove = point;}
                if(currentScore == 1){board[point.getX()][point.getY()] = 0; break;}
                if(i == pointsAvailable.size()-1 && MX < 0){if(depth == 0)computersMove = point;}
            } else if (turn == 2) {
                placeAMove(point, 2);
                int currentScore = minimax(depth + 1, 1);
                MN = min(currentScore, MN);
                if(MN == -1){board[point.getX()][point.getY()] = 0; break;}
            }
            board[point.getX()][point.getY()] = 0; //Reset this point
        }
        return turn == 1?MX:MN;
    }

    //Functions for GUI
    int returnNextMove() {
        if (isGameOver()) return -1;
        minimax(0, 1);
        return computersMove.getX() * 3 + computersMove.getY();
    }

    void resetBoard(){
        for(int i = 0;i<3;++i)
            for(int j=0;j<3;++j)
                board[i][j] = 0;
    }
};

int main() {
    Board p;
    while(!p.isGameOver()){
        p.displayBoard();
        p.takeHumanInput();
        p.displayBoard();
        int next=p.returnNextMove();
        if (next != -1) {   //If the game isn't finished yet!
            int indexCell = next;
            cout<<"Computer's move! " << indexCell<<endl;
            p.placeAMove(Point(indexCell / 3, indexCell % 3), 1);

        }

    }
    p.displayBoard();
    if(p.hasXWon()){
        cout<<"Computer is won";
    } else if(p.hasOWon()){
        cout<<"You Win";
    }else{
        cout<<"Draw";
    }
}
