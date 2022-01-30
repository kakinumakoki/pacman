#include<iostream>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<bitset>
#include<vector>
#include<string>
#include <iomanip>
#include <deque>
#include<list>
#include <windows.h>
#include<time.h>
#include<random>
#include<math.h>
#include<stdlib.h>
#define rep(i,n) for(int i=0;i<(n);i++)
using namespace std;
using ll=long long;
using P=pair<int,int>;
using P_S=pair<int,string>;
using P_D=pair<double,int>;
using T=tuple<int,int,char,ll,string>;

int dx[5]={1,-1,0,0,0};
int dy[5]={0,0,1,-1,0};
const int H = 27,W = 33;//Mapサイズ

const int Map[H][W] = { {1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},//移動制御マップ
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,0,0,1,0,1,1,1,1,1,1,0,1},
                        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,0,1},
                        {0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0},
                        {1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,0,1,1,0,1,0,1,1,1,1,0,1},
                        {1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,0,0,0,1,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,1},
                        {1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1},
                        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,1,0,1,1,1,1,0,1},
                        {1,0,0,0,1,1,1,1,0,1,0,1,1,0,0,0,1,1,1,0,1,0,0,0,0,1,0,0,0,1,1,0,1},
                        {1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1},
                        {1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,1,0,1,0,1,1,0,1,0,1,1,1,1,1,1},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
                        {1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1},
                        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,1},
                        {1,0,0,0,1,1,1,1,0,1,1,1,1,0,1,0,1,1,1,0,0,0,1,1,0,1,0,1,1,1,1,0,1},
                        {1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1},
                        {1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,1,0,1,0,1,1,1,1},
                        {1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,0,1,1},
                        {1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1},
                        {1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1},
                        {0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0,1,1,1,1,0,0},
                        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1}};//0は移動可能 1は移動不可
//0は何もない 1はポイント設置不可 2はポイント 3はplayer or enemy 4は陣地
int Point_Map[H][W]  = { {1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},//移動制御マップ
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,0,0,1,0,1,1,1,1,1,1,0,1},
                        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,0,1},
                        {0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0},
                        {1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,0,1,1,0,1,0,1,1,1,1,0,1},
                        {1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,0,0,0,1,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,1},
                        {1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1},
                        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,1,0,1,1,1,1,0,1},
                        {1,0,0,0,1,1,1,1,0,1,0,1,1,0,0,0,1,1,1,0,1,0,0,0,0,1,0,0,0,1,1,0,1},
                        {1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1},
                        {1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,1,0,1,0,1,1,0,1,0,1,1,1,1,1,1},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
                        {1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1},
                        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,1},
                        {1,0,0,0,1,1,1,1,0,1,1,1,1,0,1,0,1,1,1,0,0,0,1,1,0,1,0,1,1,1,1,0,1},
                        {1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1},
                        {1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,1,0,1,0,1,1,1,1},
                        {1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,0,1,1},
                        {1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1},
                        {1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1},
                        {0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0,1,1,1,1,0,0},
                        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1}};
/*class Rand {//https://qiita.com/gis/items/dc312fb5a056505f0a9f
private:
    //32ビット版メルセンヌ・ツイスタ
    std::mt19937 mt;
    //非決定論的な乱数
    std::random_device rd;

public:
    //コンストラクタ(初期化)
    Rand() { mt.seed(rd()); }

    //初期値
    void seed() {
        mt.seed(rd());
    }
    void seed(const std::uint_fast32_t seed_) {
        mt.seed(seed_);
    }

    //通常の乱数
    std::uint_fast32_t operator()() {
        return mt();
    }
    //0～最大値-1 (余りの範囲の一様分布乱数)
    std::int_fast32_t operator()(const std::int_fast32_t max_) {
        std::uniform_int_distribution<> uid(0, ((max_ > 0) ? (std::int_fast32_t)max_ - 1 : 0));
        return uid(mt);
    }
    //最小値～最大値
    std::int_fast32_t operator()(const std::int_fast32_t min_, const std::int_fast32_t max_) {
        std::uniform_int_distribution<> uid((min_ <= max_) ? min_ : max_, (min_ <= max_) ? max_ : min_);
        return uid(mt);
    }
    //確率
    bool randBool(const double probability_) {
        std::bernoulli_distribution uid(probability_);
        return uid(mt);
    }
    bool randBool() {
        std::uniform_int_distribution<> uid(0, 1);
        return ((uid(mt)) ? true : false);
    }
};
static thread_local Rand rnd;
*/
struct Point
{
    int x;
    int y;
};
int sub_Map[H][W];
double player_dist[H][W];//playerからの距離
double enemy_dist[H][W];//enemyからの距離
double point_dist[H][W];//pointからの距離
double player_enemy_dist[H][W];
double get_score_dist[H][W];//pointを還元できるエリアへの距離
vector<Point> can_set_point;//壁ない場所格納
vector<Point> point_position;//pointがある場所
double weight_enemy,weight_point;//意思決定の重み
int can_move_num = 0;//動けるマスの数
int number_of_enemy;//敵の数
int how_long_times;//何ステップやるか
int times;//現ステップ
int number_of_points;//point何個出現させるか

struct Player//プレイヤー
{
    public:
        Point now;
        int score;
        int death_count;
        int have_point;

    void Initialize(int y,int x){
        now.x = x;
        now.y = y;
        score = 0;
        death_count = 0;
        have_point = 0;
    }
    

    void AddScore()
    {
        //cout<<"point get!!!"<<endl;
        this->score+=have_point;
        this->have_point = 0;
    }
    void Add_have_point()
    {
        this->have_point++;
    }
    void death()
    {
        this->have_point=0;
        this->death_count++;
    }
    void random_walk()//random
    {
        vector<Point> next_position;
        rep(i,5){
            int next_x=(this->now.x+dx[i]+W)%W,next_y=(this->now.y+dy[i]+H)%H;
            if(Map[next_y][next_x]!=1){
                if(Map[next_y][next_x]==0){
                    Point next;
                    next.x = next_x;
                    next.y = next_y;
                    next_position.push_back(next);
                }
            }
        }
        int select = rand()%next_position.size();
        this->now = next_position[select];
    }

    void flee_from_enemy(Point player)//enemyと距離遠くなるように動く
    {
        double min_dist=1000;
        vector<Point> next;
        rep(i,5){
            int next_x=(player.x+dx[i]+W)%W,next_y=(player.y+dy[i]+H)%H;
            if(Map[next_y][next_x]!=1){
                double weight = enemy_dist[next_y][next_x];
                if(weight == min_dist){
                    next.push_back({next_x,next_y});
                }
                else if(weight<min_dist){
                    while(!next.empty()) next.erase(next.begin());
                    min_dist = weight;
                    next.push_back({next_x,next_y});
                }
            }
        }
        int s = next.size();
        if(s>1){//最短になる経路複数あった場合ランダム
            int select = rand()%s;
            this->now = next[select];
        }
        else this->now = next[0];
    }

    void consider_enemy_and_point(Point player)//敵とポイントの位置考慮して移動
    {
        double min_dist=1000;
        vector<Point> next;
        vector<vector<double>> new_map(H,vector<double>(W,1000));
        rep(i,H){
            rep(j,W){
                if(Map[i][j]==0)new_map[i][j] = weight_enemy*enemy_dist[i][j] + weight_point*point_dist[i][j];
            }
        }
        /*cout<<"new_map"<<endl;
        rep(i,H){
            rep(j,W){
                if(new_map[i][j]>1) cout<<"  .  ";
                else printf("%.2f ",new_map[i][j]);
            }
            cout<<endl;
        }*/

        rep(i,4){
            int next_x=(player.x+dx[i]+W)%W,next_y=(player.y+dy[i]+H)%H;
            if(Map[next_y][next_x]!=1){
                double weight = new_map[next_y][next_x];
                if(weight == min_dist){
                    next.push_back({next_x,next_y});
                }
                else if(weight<min_dist){
                    while(!next.empty()) next.erase(next.begin());
                    min_dist = weight;
                    next.push_back({next_x,next_y});
                }
            }
        }
        int s = next.size();
        if(s>1){//最良経路複数あった場合ランダム
            int select = rand()%s;
            this->now = next[select];
        }
        else this->now = next[0];
    }

    void consider_enemy_and_point_upgrade(Player player)//ポイントある程度とったら敵考慮しつつ陣地に帰る
    {
        double min_dist=1000;
        vector<Point> next;
        vector<vector<double>> new_map(H,vector<double>(W,1000));
        if(player.have_point>=2){//ある程度ポイント持っている場合
            //cout<<"!!!go_home!!!!!"<<endl;
            double weight_gohome=1-weight_enemy;
            rep(i,H){
                rep(j,W){
                    if(Map[i][j]==0)new_map[i][j] = weight_enemy*enemy_dist[i][j] + weight_gohome*get_score_dist[i][j];
                }
            }
            rep(i,4){
                int next_x=(player.now.x+dx[i]+W)%W,next_y=(player.now.y+dy[i]+H)%H;
                if(Map[next_y][next_x]!=1){
                    double weight = new_map[next_y][next_x];
                    if(weight == min_dist){
                        next.push_back({next_x,next_y});
                    }
                    else if(weight<min_dist){
                        while(!next.empty()) next.erase(next.begin());
                        min_dist = weight;
                        next.push_back({next_x,next_y});
                    }
                }
            }
            int s = next.size();
            if(s>1){//最良経路複数あった場合ランダム
                int select = rand()%s;
                this->now = next[select];
            }
            else this->now = next[0];
        }
        else{
            rep(i,H){
                rep(j,W){
                    if(Map[i][j]==0)new_map[i][j] = weight_enemy*enemy_dist[i][j] + weight_point*point_dist[i][j];
                }
            }
            /*cout<<"new_map"<<endl;
            rep(i,H){
                rep(j,W){
                    if(new_map[i][j]>1) cout<<"  .  ";
                    else printf("%.2f ",new_map[i][j]);
                }
                cout<<endl;
            }*/

            rep(i,4){
                int next_x=(player.now.x+dx[i]+W)%W,next_y=(player.now.y+dy[i]+H)%H;
                if(Map[next_y][next_x]!=1){
                    double weight = new_map[next_y][next_x];
                    if(weight == min_dist){
                        next.push_back({next_x,next_y});
                    }
                    else if(weight<min_dist){
                        while(!next.empty()) next.erase(next.begin());
                        min_dist = weight;
                        next.push_back({next_x,next_y});
                    }
                }
            }
            int s = next.size();
            if(s>1){//最良経路複数あった場合ランダム
                int select = rand()%s;
                this->now = next[select];
            }
            else this->now = next[0];

        }
    }

    void test(Player player)
    {
        double min_dist=1000;
        vector<Point> next;
        vector<vector<double>> new_map(H,vector<double>(W,1000));
        double weight_gohome;
        double p_h = (double)player.have_point;
        if(player.have_point<=4){
            weight_gohome = p_h*0.1;
            if(enemy_dist[player.now.y][player.now.x]<0.7)
            {
                weight_point = 0.7;
                weight_enemy = 1-(weight_gohome+weight_point);
            }
            else{
                weight_enemy = 0.6;
                weight_point = 1-(weight_gohome+weight_enemy);
            }
        }
        else{
            weight_gohome =0.4;
            weight_point = 0.1;
            weight_enemy = 0.5;
        }
        rep(i,H){
                rep(j,W){
                if(Map[i][j]==0)new_map[i][j] = weight_enemy*enemy_dist[i][j] + weight_point*point_dist[i][j] + weight_gohome*get_score_dist[i][j];
            }
        }

        rep(i,4){
            int next_x=(player.now.x+dx[i]+W)%W,next_y=(player.now.y+dy[i]+H)%H;
            if(Map[next_y][next_x]!=1){
                double weight = new_map[next_y][next_x];
                if(weight == min_dist){
                    next.push_back({next_x,next_y});
                 }
                else if(weight<min_dist){
                    while(!next.empty()) next.erase(next.begin());
                     min_dist = weight;
                    next.push_back({next_x,next_y});
                 }
            }
         }
        int s = next.size();
        if(s>1){//最良経路複数あった場合ランダム
            int select = rand()%s;
            this->now = next[select];
         }
         else this->now = next[0];

    }
};

struct Enemy//敵
{
    Point now;
    int move_pattern;
    bool which;

    void Initialize(int y,int x){
        now.x = x;
        now.y = y;
        which = true;
        /*cout<<"decide enemy move pattern ";
        cout<<"0 : random.  1:chase_to_player 2:change_move 3:player_enemy_consider: ";
        while(1){
            int input;
            cin>>input;
            if(input>3) cout<<"!!!!!!!!!!!!!! input<4 !!!!!!!!!!!!!!!!"<<endl;
            else {
                move_pattern=input;
                break;
            }
        }*/
    }
    
    void random_walk()//random
    {
        vector<Point> next_position;
        rep(i,4){
            int next_x=(this->now.x+dx[i]+W)%W,next_y=(this->now.y+dy[i]+H)%H;
            if(Map[next_y][next_x]!=1){
                if(Map[next_y][next_x]==0){
                    Point next;
                    next.x = next_x;
                    next.y = next_y;
                    next_position.push_back(next);
                }
            }
        }
        int select = rand()%next_position.size();
        this->now = next_position[select];
    }
    
    void chase_to_player(Point enemy){//playerとの距離短くなるほうに動く
        double min_dist=H*W;
        vector<Point> next;
        rep(i,5){
            int next_x=(enemy.x+dx[i]+W)%W,next_y=(enemy.y+dy[i]+H)%H;
            if(Map[next_y][next_x]!=1){
                int weight = player_dist[next_y][next_x];
                if(weight == min_dist){
                    next.push_back({next_x,next_y});
                }
                else if(weight<min_dist){
                    while(!next.empty()) next.erase(next.begin());
                    min_dist = weight;
                    next.push_back({next_x,next_y});
                }
            }
        }
        int s = next.size();
        if(s>1){//最短になる経路複数あった場合ランダム
            int select = rand()%s;
            this->now = next[select];
        }
        else this->now = next[0];
    }

    void change_Regularly( ){//敵追いかける　追いかけないを15ステップごとに切り替え
        if(times%15 ==0){
            which = !which;
        }

        if(player_dist[this->now.y][this->now.x]<=4){
            which = true;
            //cout<<"near!!!!!!!!!"<<endl;
        }

        if(which){
            chase_to_player(this->now);
        }
        else random_walk();
    }

    void consider_enemy(Point enemy)
    {
        double min_dist=H*W;
        vector<Point> next;
        rep(i,5){
            int next_x=(enemy.x+dx[i]+W)%W,next_y=(enemy.y+dy[i]+H)%H;
            if(sub_Map[next_y][next_x]!=1){
                int weight = player_enemy_dist[next_y][next_x];
                if(weight == min_dist){
                    next.push_back({next_x,next_y});
                }
                else if(weight<min_dist){
                    while(!next.empty()) next.erase(next.begin());
                    min_dist = weight;
                    next.push_back({next_x,next_y});
                }
            }
        }
        int s = next.size();
        if(s>1){//最短になる経路複数あった場合ランダム
            int select = rand()%s;
            this->now = next[select];
        }
        else this->now = next[0];

    }

    void decide_next_move(){
        if(this->move_pattern == 0)
        {
            random_walk();
        }
        else if(this->move_pattern == 1)
        {
            chase_to_player(this->now);
        }
        else if(this->move_pattern == 2){
            change_Regularly();
        }
        else if(this->move_pattern ==3)
        {
            consider_enemy(this->now);
        }
    }

};

struct calculate//計算系のこと
{
    void calculate_player_dist(Point player){//playerからの距離計算
        vector<vector<bool>> seen(H,vector<bool>(W,false));
        seen[player.y][player.x]=true;
        rep(i,H){
            rep(j,W){
                player_dist[i][j] = 1000; 
            }
        }
        player_dist[player.y][player.x]=0;
        queue<Point> q;
        q.push(player);
        double max_num = 0;
        while(!q.empty())
        {
            Point now=q.front();
            q.pop();
            rep(i,4){
                int next_x=(now.x+dx[i]+W)%W,next_y=(now.y+dy[i]+H)%H;
                if(seen[next_y][next_x] == false&&Map[next_y][next_x]!=1){
                    seen[next_y][next_x] =true;
                    player_dist[next_y][next_x]=player_dist[now.y][now.x]+1;
                    if(max_num < player_dist[next_y][next_x]) max_num = player_dist[next_y][next_x];
                    Point next={next_x,next_y};
                    q.push(next);
                }
            }
        }
        /*rep(i,H){
            rep(j,W){
                player_dist[i][j] = player_dist[i][j]/max_num;
            }
        }*/
    }
    void calculate_player_dist_enemy(Point player,vector<Enemy>enemy,Enemy e)
    {
        rep(i,H){
            rep(j,W){
                sub_Map[i][j]=Map[i][j];
            }
        }
        rep(i,enemy.size()){
            if((enemy[i].now.x!=e.now.x)&&(enemy[i].now.y!=e.now.y)){
                sub_Map[enemy[i].now.y][enemy[i].now.x]=1;
                rep(j,4)
                {
                    sub_Map[(enemy[i].now.y+dy[j])%H][(enemy[i].now.x+dx[j])%W]=1;                    
                }
            }
        }

        vector<vector<bool>> seen(H,vector<bool>(W,false));
        seen[player.y][player.x]=true;
        rep(i,H){
            rep(j,W){
                player_enemy_dist[i][j] = 1000; 
            }
        }
        player_enemy_dist[player.y][player.x]=0;
        queue<Point> q;
        q.push(player);
        double max_num = 0;
        while(!q.empty())
        {
            Point now=q.front();
            q.pop();
            rep(i,4){
                int next_x=(now.x+dx[i]+W)%W,next_y=(now.y+dy[i]+H)%H;
                if(seen[next_y][next_x] == false&&sub_Map[next_y][next_x]!=1){
                    seen[next_y][next_x] =true;
                    player_enemy_dist[next_y][next_x]=player_enemy_dist[now.y][now.x]+1;
                    if(max_num < player_enemy_dist[next_y][next_x]) max_num = player_enemy_dist[next_y][next_x];
                    Point next={next_x,next_y};
                    q.push(next);
                }
            }
        }

    }
    void calculate_enemy_dist(vector<Enemy> enemy){//enemyからの距離計算
        vector<vector<bool>> seen(H,vector<bool>(W,false));
        queue<Point> q;
        double max_num=0;
        rep(i,H){
            rep(j,W){
                enemy_dist[i][j] = 1000; 
            }
        }
        rep(i,number_of_enemy){
            seen[enemy[i].now.y][enemy[i].now.x]=true;
            enemy_dist[enemy[i].now.y][enemy[i].now.x]=0;   
            q.push(enemy[i].now);                
        }
        while(!q.empty())
        {
            Point now=q.front();
            q.pop();
            rep(i,4){
                int next_x=(now.x+dx[i]+W)%W,next_y=(now.y+dy[i]+H)%H;
                if(Map[next_y][next_x]!=1&&enemy_dist[next_y][next_x]>enemy_dist[now.y][now.x]+1){
                    seen[next_y][next_x] =true;
                    enemy_dist[next_y][next_x]=enemy_dist[now.y][now.x]+1;
                    Point next={next_x,next_y};
                    q.push(next);
                }
            }
        }
        rep(i,H){
            rep(j,W){
                if(max_num < enemy_dist[i][j] && Map[i][j] == 0) max_num = enemy_dist[i][j];      
            }
        }
        rep(i,H){
            rep(j,W){
                if(enemy_dist[i][j]!=1000)enemy_dist[i][j] =  (max_num - enemy_dist[i][j])/max_num;
            }
        }
    }

    void calculate_point_dist(vector<Point> point){//enemyからの距離計算
        vector<vector<bool>> seen(H,vector<bool>(W,false));
        queue<Point> q;
        rep(i,H){
            rep(j,W){
                point_dist[i][j] = 1000; 
            }
        }
        rep(i,number_of_points){
            seen[point[i].y][point[i].x]=true;
            point_dist[point[i].y][point[i].x]=0;
            q.push(point[i]);
        }
        double max_num=0;
        while(!q.empty())
        {
            Point now=q.front();
            q.pop();
            rep(i,4){
                int next_x=(now.x+dx[i]+W)%W,next_y=(now.y+dy[i]+H)%H;
                if(Map[next_y][next_x]!=1&&point_dist[next_y][next_x]>point_dist[now.y][now.x]+1){
                    seen[next_y][next_x] =true;
                    point_dist[next_y][next_x]=point_dist[now.y][now.x]+1;
                    if(max_num < point_dist[next_y][next_x]) max_num = point_dist[next_y][next_x];
                    Point next={next_x,next_y};
                    q.push(next);
                }
            }
        }
        rep(i,H){
            rep(j,W){
                point_dist[i][j]  = point_dist[i][j]/max_num;
            }
        }
    }
    
    void calculate_get_score_dist()
    {
        vector<vector<bool>> seen(H,vector<bool>(W,false));
        queue<Point> q;
        rep(i,H){
            rep(j,W){
                if(Point_Map[i][j] == 4){
                    q.push({j,i});
                    get_score_dist[i][j] = 0;
                    seen[i][j] = true;
                }
                else get_score_dist[i][j]=1000;
            }
        }
        double max_num=0;
        while(!q.empty())
        {
            Point now=q.front();
            q.pop();
            rep(i,4){
                int next_x=(now.x+dx[i]+W)%W,next_y=(now.y+dy[i]+H)%H;
                if(seen[next_y][next_x] == false&&Map[next_y][next_x]!=1){
                    seen[next_y][next_x] =true;
                    get_score_dist[next_y][next_x]=get_score_dist[now.y][now.x]+1;
                    Point next={next_x,next_y};
                    q.push(next);
                }
            }
        }
        rep(i,H){
            rep(j,W){
                if(max_num < get_score_dist[i][j] && Map[i][j] == 0) max_num = get_score_dist[i][j];      
            }
        }

        rep(i,H){
            rep(j,W){
                get_score_dist[i][j]  = get_score_dist[i][j]/max_num;
            }
        }
    }
};
calculate information;

struct Show//表示する系のこと
{
    void print_map(Point player,vector<Enemy> enemy)//map情報表示
    {
        int number;
        rep(i,H){
            rep(j,W){
                int flag=0;
                rep(k,number_of_enemy){
                    if(i==enemy[k].now.y&&j==enemy[k].now.x) {
                        flag = 1;
                        number = k;
                    }
                }
                if(flag == 1)
                {
                    //cout<<" E ";
                    printf("\x1b[41m %d \x1b[m",number);
                }
                else if(i==player.y&&j==player.x){
                     //cout<<" P ";
                    printf("\x1b[42m   \x1b[m");
                }
                else if(Map[i][j]==1){
                    //cout<<"+++";
                    printf("\x1b[45m   \x1b[m");
                }
                else {
                    if(Point_Map[i][j] == 2) cout<<" 0 ";
                    else if(Point_Map[i][j] ==4) printf("\x1b[43m   \x1b[m");
                    else cout<<"   ";
                }
            }
            cout<<endl;
        }
        cout<<endl;
        for(int i=0;i<W;i++) cout<<"===";
        cout<<endl;
    }
    void print_player_enemy_dist(){//playerからの距離表示
        cout<<"player_enemy_dist"<<endl;
        rep(i,H){
            rep(j,W){
                if(player_enemy_dist[i][j] >= 1000) printf(" .  ");
                else printf("%4.0f",player_enemy_dist[i][j]);
            }
            cout<<endl;
        }
    }

    void print_player_dist(){//playerからの距離表示
        cout<<"player_dist"<<endl;
        rep(i,H){
            rep(j,W){
                if(player_dist[i][j] >= 1000) printf(" .  ");
                else printf("%4.0f",player_dist[i][j]);
            }
            cout<<endl;
        }
    }
    
    void print_enemy_dist()//enemyからの距離表示
    {
        cout<<"enemy_dist"<<endl;
        rep(i,H){
            rep(j,W){
                if(Map[i][j] == 1) printf("  .  ");
                else printf("%.2f ",enemy_dist[i][j]);
            }
            cout<<endl;
        }
    }
    
    void print_point_dist()//pointからの距離表示
    {
        cout<<"point_dist"<<endl;;
        rep(i,H){
            rep(j,W){
                if(point_dist[i][j]  >1) printf("  .  ");
                else printf("%.2f ",point_dist[i][j]);
            }
            cout<<endl;
        }
    }
    
    void print_get_score_dist()
    {
        cout<<"get_score_dist"<<endl;;
        rep(i,H){
            rep(j,W){
                if(Map[i][j]==1) printf("  .  ");
                else printf("%.2f ",get_score_dist[i][j]);
                //else printf("%5.0f",get_score_dist[i][j]);
            }
            cout<<endl;
        }

    }
    
    void print_Point_Map()//pointからの距離表示
    {
        rep(i,H){
            rep(j,W){
                cout<<" "<<Point_Map[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    
    void print_player_status(Player player){
        cout<<"player score : "<<player.score<<endl;
        cout<<"player have points : "<<player.have_point<<endl;
        cout<<"player death count : "<<player.death_count<<endl;
    }
};

struct GameSystem{


    void Initialize()
    {
        for(int i=0;i<H;i++){//移動できるマスをカウント
            for(int j=0;j<W;j++){
                if(Map[i][j] != 1) {
                    can_move_num++;
                    can_set_point.push_back({j,i});
                }
            }
        }
        
        cout<<"How many steps? :";
        cin>>how_long_times;
        cout<<"How many points? :";
        cin>>number_of_points;
        point_position.resize(number_of_points);
        /*cout<<"Input Weight (0<=100)"<<endl;
        while(1){
            cout<<"enemy_dist_weight : ";
            cin>>weight_enemy;
            cout<<"point_dist_weight : ";
            cin>>weight_point;
            if((weight_point + weight_enemy) ==100){
                weight_enemy/=100;
                weight_point/=100;
                break;
            }
            else{
                cout<<"!!!!!!!!!!!you must sum = 100 and weight<=100!!!!!!!!!!!"<<endl;
            }
        }*/

        /*cout<<"Input_number_of_Enemy (max 4) : ";
        cin>>number_of_enemy;*/
        number_of_enemy = 2;
        int select = rand()%can_set_point.size();
        Point_Map[can_set_point[select].y][can_set_point[select].x] = 4;
    }

    bool is_GameOver(Point player,vector<Enemy> enemy)
    {
        rep(i,number_of_enemy){
        if((fabs(player.x-enemy[i].now.x) == 1&&player.y-enemy[i].now.y ==0)||(player.x-enemy[i].now.x == 0&&fabs(player.y-enemy[i].now.y) ==1)||(player.x-enemy[i].now.x==0&&player.y-enemy[i].now.y==0)) return true;
        }
        return false;
    }
    
    bool is_spone(Point player,vector<Enemy> enemy)
    {
        rep(i,number_of_enemy){
        if((fabs(player.x-enemy[i].now.x) == 1&&player.y-enemy[i].now.y ==0)||(player.x-enemy[i].now.x == 0&&fabs(player.y-enemy[i].now.y) ==1)||(player.x-enemy[i].now.x==0&&player.y-enemy[i].now.y==0)) return true;
        }
        return false;
    }
    
    void set_Point(Point player,vector<Enemy> enemy)
    {
        Point_Map[player.y][player.x] =3;
        rep(i,number_of_enemy){
            Point_Map[enemy[i].now.y][enemy[i].now.x] = 3;
        }
        rep(i,number_of_points) point_position[i] = {-1,-1};
        int c=0;
        rep(i,H){
            rep(j,W){
                if(Point_Map[i][j] == 2){
                    point_position[c]={j,i};
                    c++;
                }
            }
        }
        while(c<number_of_points){
            int random_set;
            random_set = rand()%can_set_point.size();
            if(Point_Map[can_set_point[random_set].y][can_set_point[random_set].x] != 2 && (Point_Map[can_set_point[random_set].y][can_set_point[random_set].x] != 3)&&(Point_Map[can_set_point[random_set].y][can_set_point[random_set].x] != 4))
            {
                Point_Map[can_set_point[random_set].y][can_set_point[random_set].x] = 2;
                point_position[c] = {can_set_point[random_set].x,can_set_point[random_set].y};
                c++;
            }
        }
    }

    bool check_player_point(Player player,vector<Enemy> enemy)
    {
        if(Point_Map[player.now.y][player.now.x] == 2){
            Point_Map[player.now.y][player.now.x] = 0;
            rep(i,number_of_enemy){
                Point_Map[enemy[i].now.y][enemy[i].now.y] = 0;
            }
            set_Point(player.now,enemy);
            return true;
        }
        return false;
    }
    
    bool check_player_get_score(Player player)
    {
        if(Point_Map[player.now.y][player.now.x] == 4){
            return true;
        }
        return false;
    }
};
GameSystem GameManager;


int main()
{
    srand(time(NULL));
    times = 0;
    Player player;
    Show show;
    GameManager.Initialize();
    //-------------player関連初期化---------------------
    player.Initialize(13,16);
    //------------------敵関連の初期化-------------------
    vector<Enemy> enemy(number_of_enemy);
    rep(i,number_of_enemy){//enemy初期位置
        while(1){
            Point candidate = can_set_point[rand()%can_set_point.size()];
            int flag=0;
            rep(j,i){//playerと他のenemyと被ってないか確認
                if((candidate.x==player.now.x&&candidate.y==player.now.y)||((enemy[j].now.x==candidate.x)&&(enemy[j].now.y==candidate.y))){
                    flag=1;
                }
            }
            if(flag==0){
                enemy[i].Initialize(candidate.y,candidate.x);
                break;
            }
        }
    }
    enemy[0].move_pattern = 1;
    enemy[1].move_pattern = 3;
    //---------------------------------------------------
    GameManager.set_Point(player.now,enemy);
    information.calculate_get_score_dist();
    
    while(times < how_long_times){
        system("cls");//より動いてるように見えるようになる
        show.print_map(player.now,enemy);
        if(GameManager.is_spone(player.now,enemy)) {
            //show.print_map(player.now,enemy);
            player.death();
            Point_Map[player.now.y][player.now.x] = 0;
            cout<<"--------------player_spone-------------------"<<endl;
            int select = rand()%can_set_point.size();
            player.now.x = can_set_point[select].x;
            player.now.y = can_set_point[select].y;
            Point_Map[player.now.y][player.now.x] = 3;
        }
        //---------------------calculate系---------------------------------
        information.calculate_player_dist(player.now);
        information.calculate_enemy_dist(enemy);
        information.calculate_point_dist(point_position);
        information.calculate_player_dist_enemy(player.now,enemy,enemy[1]);
        //---------------------print系------------------------------------
        show.print_player_status(player);       
        //show.print_player_dist();
        //show.print_enemy_dist();
        //show.print_point_dist();
        //show.print_get_score_dist();
        //show.print_Point_Map();
        show.print_player_enemy_dist();
        //--------------------playerとenemy次の行動決める--------------------
        Point pre_player_position = player.now;
        vector<Point> pre_enemy_position(number_of_enemy);
        rep(i,number_of_enemy){
            pre_enemy_position[i] = enemy[i].now;
        }
        //--------------------------player-----------------------------------
        //player.random_walk();
        //player.flee_from_enemy(pre_player_position);
        //player.consider_enemy_and_point(pre_player_position);
        //player.consider_enemy_and_point_upgrade(player);
        player.test(player);
        //--------------------------enemy----------------------------------
        rep(i,number_of_enemy){
            enemy[i].decide_next_move();
        }

        //--------------------------------判定-------------------------------
        if(GameManager.check_player_point(player,enemy))
        {
            player.Add_have_point();
            information.calculate_point_dist(point_position);       
        }
        if(GameManager.check_player_get_score(player)){
            player.AddScore();
        }
        Sleep(3 * 100);
        cout<<times<<endl;
        times++;
    }
    
    if(times == how_long_times) cout<<"!!!!!!!!!!finish!!!!!!!!!!!!!!!!"<<endl;
    //show.print_player_status(player);
    
}