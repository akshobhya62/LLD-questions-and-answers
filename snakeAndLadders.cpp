#include<bits/stdc++.h>
using namespace std;

class Cell{
    public:
    int x, y, from, to, id;
    public: void setx(int x){this->x = x;}
    public: void sety(int y){this->y = y;}
    public: void setfrom(int from){this->from = from;}
    public: void setto(int to){this->to = to;}
    public: void setid(int id){this->id = id;}
};

class User{
    public:
    // vector<Game*> gamesPlayed;
    string userName;
    string userID;
    User(){}
    User(string userName, string userID){
        this->userID = userID;
        this->userName = userName;
    }
    // vector<Game*> getGamesPlayed(){return gamesPlayed;}
};

class Move{
    public:
    int start, end;
    User player;
    Move(User player, int start, int end){
        this->start = start;
        this->end = end;
        this->player = player;
    }
};

class Game{
    public: vector<vector<Cell*>> board;
    public: vector<User*> players;
    private: vector<Move*> moves;
    private: unordered_map<User*, Cell*> loc;
    private: unordered_map<int, Cell*> getCell;//maps cell id to cell object
    private: int numOfDiceFace;
    private: int indexOfCurPlayer;
    private: bool gameOver;
    private: User* victor;
    public: Game(int board_width, int board_height, vector<User*> players, int diceFaces){
        this->board.resize(board_width, vector<Cell*>(board_height));
        this->players = players;
        this->moves.clear();
        indexOfCurPlayer = 0;
        gameOver = false;
        this->numOfDiceFace = diceFaces;;
    }
    public: void initilise(){
        int cur = 1;
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board.size(); j++){
                Cell* cell = new Cell();
                cell->setx(i);
                cell->sety(j);
                cell->setfrom(cur);
                cell->setto(cur);
                cell->setid(cur);
                getCell[cur] = cell;
                cur++;
                board[i][j] = cell; 
            }
        }
        for(auto i : players){
            loc[i] = board[0][0];
        }
    }
    public: void play(){
        while(!gameOver){
            User* curPlayer = players[indexOfCurPlayer % players.size()];
            cout<<"\ncurPlayer = "<<curPlayer->userID<<endl;
            int rollDice = rand() % numOfDiceFace + 1;
            cout<<"rolled = "<<rollDice<<endl;
            int newLocation = loc[curPlayer]->id + rollDice;
            if(newLocation >= board.size() * board[0].size()){
                gameOver = true;
                victor = curPlayer;
                cout<<"horray player "<<curPlayer->userName<<" won\n";
                break;
            }
            cout<<"value ="<<newLocation<<endl;
            loc[curPlayer] = getCell[newLocation];
            cout<<"new location = "<<loc[curPlayer]->from<<endl;
            if(loc[curPlayer]->from >= board.size() * board[0].size()){
                gameOver = true;
                victor = curPlayer;
                break;
            }
            while(loc[curPlayer]->from != loc[curPlayer]->to){
                loc[curPlayer] = getCell[loc[curPlayer]->to];
            }
            if(loc[curPlayer]->from >= board.size() * board[0].size()){
                gameOver = true;
                victor = curPlayer;
            }
            indexOfCurPlayer++;
        }
    }
    public: void addSnakes(){}
    public: void addLadders(){}
};
int main()
{
    int board_width = 10, board_height = 10;
    User* a = new User("a", "1");
    User* b = new User("b", "2");
    vector<User*> players;
    players.push_back(a);
    players.push_back(b);
    Game* game = new Game(board_width, board_height, players, 6);
    game->initilise();
    for(int i = 0; i < game->board.size(); i++){
        for(int j = 0; j < game->board[0].size(); j++){
            cout<<game->board[i][j]->id<<" ";
        }
        cout<<endl;
    }
    for(int i = 0; i < game->players.size(); i++)cout<<"playerId : "<<game->players[i]->userID<<", playerName: "<<game->players[i]->userName<<endl;
    game->play();
}
