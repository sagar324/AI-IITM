#include <bits/stdc++.h>
#include <random>
#include <chrono>
using namespace std::chrono;
using namespace std;
//typedefs and fastIO
//#define STEXT freopen("ain.in","r",stdin);freopen("aout.in","w",stdout)
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL)
#define V vector<int>
#define pb push_back 
#define ff first
#define ss second
//inputs
#define inp(n) int n;cin>>n
#define sinp(s) string s;cin>>s
#define vinp(v,n) V v;fup(i,0,n) {int temp; cin>>temp; v.pb(temp);}
//loops
#define fup(i,L,R) for(int i=L;i<R;i++)
//VECTOR print statements/functions
#define vsubout(v,L,R) fup(i,L,R) {cout<<v[i]<<" ";}
#define vout(v) vsubout(v,0,v.size());cout<<endl
#define vvout(v) fup(i,0,v.size()){fup(j,0,v[i].size()){cout<<v[i][j]<<" ";}cout<<endl;}
#define qsort(v) sort(v.begin(),v.end())

/*void stext(){
    #ifndef ONLINE_JUDGE
        STEXT;
    #endif
}*/

double FindProbab(double deltaE, double T){
    double power = deltaE/T;
    double answer = 1;
    answer = answer/(1.0 + exp(power));
    return answer;
}

vector<int> RandomTour(int n){
    vector<int> ans;
    fup(i,0,n){
        ans.pb(i);
    }
    random_shuffle(ans.begin(), ans.end(),
                        [&](int i) {
                            return std::rand() % i;
                        });
    return ans;
}

double FindCost(vector<int> cycle, vector<vector<double>> adj){
    int n = cycle.size();
    double cost = 0;
    fup(i,0,n-1){
        cost += adj[cycle[i]][cycle[i+1]];
    }
    cost += adj[cycle[n-1]][cycle[0]];
    return cost;
}

void swapint(int& l , int& r){
    int temp = l;
    l = r;
    r = temp;
}

pair<vector<int>,vector<int>> CycleCrossOver(vector<int> p1,vector<int> p2){
    if(p1==p2){
        pair<vector<int>,vector<int>> p;
        p.ff = p1;
        p.ss = p2;
        return p;  
    }
    int n = p1.size();
    vector<int> cycleindex(n,0);
    vector<int> hashmap1(n,-1);
    fup(i,0,n){
        hashmap1[p1[i]] = i;
    }
    int seq_num = 1;
    fup(i,0,n){
        if(cycleindex[i]!=0){
            continue;
        }
        cycleindex[i] = seq_num;
        int next = hashmap1[p2[i]]; 
        while(cycleindex[next]==0){
            cycleindex[next] = seq_num;
            next = hashmap1[p2[next]];
        }
        seq_num++;
    }
    vector<int> child1(n,-1);
    vector<int> child2(n,-1);
    fup(i,0,n){
        if(cycleindex[i]&1){
            child1[i] = p1[i];
            child2[i] = p2[i];
        }
        else{
            child1[i] = p2[i];
            child2[i] = p1[i];
        }
    }
    pair<vector<int>,vector<int>> p;
    p.ff = child1;
    p.ss = child2;
    return p;
}

vector<int> best_tour_cycle_heuristic;
vector<int> real_best_tour;

void CycleHeuristic(int n, vector<vector<double>> adj){
    int loops=0;
    int flag1=0;
    int flag2=0;
    default_random_engine generator;
    double realbestcost = DBL_MAX;
    // initialize n random tours.
    // n random permutations containing 0 1 2 3 . . . n-1
    vector<int> temp;
    int itr = 0;
    vector <pair<double,vector<int>>> v;
    int size = 2000;
    set<pair<double,vector<int>>> s;
    while(v.size()<size){

        temp = RandomTour(n);
        //vout(temp);
        double cost = FindCost(temp,adj);

        pair<double,vector<int>> p; p.ff = cost; p.ss = temp;

        v.pb(p);
    }
    
    qsort(v);
    // store them in a multi_set containing n tours sorted by costs.
    // now we have a starting population of n.
    int loopnum=0;
    
    auto start = high_resolution_clock::now();

    while(1){

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);
        if(duration.count()>20){
            break;
        }

        vector<double> probab(size,0);
        fup(i,0,size){
            probab[i] = 1.0/(v[i].ff);
        }
        discrete_distribution <> dist(probab.begin(),probab.end());
        vector<pair<double,vector<int>>> selected;
        fup(i,0,size){
            int index = dist(generator);
            selected.pb(v[index]);
        }
        
        //partition s into 2 halves.(0 to n/2 and n/2+1 to n-1)
        // and randomly crossover -> equal to generate 2 random nums between 0-n/2 and n/2+1 - n-1 and send to crossover function
        int firstsegmentend = size/2;
        int secondsegmentstart = (size/2)+1;
        vector<pair<double,vector<int>>> offsprings;
        pair<double,vector<int>> off1;
        pair<double,vector<int>> off2;
        fup(j,0,size/2){
            int randNum1 = rand()%(firstsegmentend + 1);
            int randNum2 = rand()%(size-secondsegmentstart) + secondsegmentstart;
            while(randNum2==randNum1){
                randNum2 = rand()%(size-secondsegmentstart) + secondsegmentstart;
            }

            pair<vector<int>,vector<int>> crossoverpair = CycleCrossOver(selected[randNum1].ss,selected[randNum2].ss);
            vector<int> crossover1 = crossoverpair.ss;
            vector<int> crossover2 = crossoverpair.ss;
            double cost1 = FindCost(crossover1,adj);
            double cost2 = FindCost(crossover2,adj);
            off1.ff = cost1;
            off1.ss = crossover1;
            offsprings.pb(off1);
            // stored one offspring
            off2.ff = cost2;
            off2.ss = crossover2;
            offsprings.pb(off2);
        }
        if(size%2!=0){
            offsprings.pb(selected[0]);
        }
        
        // generated offsprings
        // write mutate function 
        double p = 0.01;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> distrib({ 1-p, p });
                                    // ^^^  ^- probability for 1
                                    //  | probability for 0
        
        fup(i,0,size){
            int event = distrib(gen);
            if(event==1){
                flag1++;
                offsprings[i].ss = RandomTour(n);
                offsprings[i].ff = FindCost(offsprings[i].ss,adj);
            }
        }
        // Define  a k , replace k pops with k offs
        
        qsort(v);
        qsort(offsprings);
        
        
        int k = size/2;
        
        pair<double,vector<int>> best = v[0];
        
        fup(i,0,k){
            v[size-1-i] = offsprings[k-1-i];
            if(best.ff>offsprings[k-1-i].ff){
                //loopnum = loops;
                best = offsprings[k-1-i];
                flag2++;
            }
        }
        //vout(best.ss);
        qsort(v);
        if(v[0].ff<realbestcost){
            loopnum = loops;
            realbestcost = v[0].ff;
        }
        loops++;
    }
    
    //cout<<loopnum<<endl;
    
    best_tour_cycle_heuristic = v[0].ss;
    real_best_tour = v[0].ss;
    vout(best_tour_cycle_heuristic);
    cout<<FindCost(best_tour_cycle_heuristic,adj)<<endl;
}

void CoolingFunction(double &T){
    T = 0.999*T;
}

void Simulated_Annealing(int n,vector<vector<double>> adj){
    int iter = 0;// for inner loop iterations.
    int worstcost = 0;
    vector<int> best_tour = best_tour_cycle_heuristic;//RandomTour(n);//
    double bestcost = FindCost(best_tour,adj);
    worstcost = bestcost;
    double realbestcost = bestcost;//= bestcost;
    //vout(best_tour);
    double INIT = 10000;
    double T;
    int itr=0;
    //generated random path
    int ctr=0;
    auto start = high_resolution_clock::now();
    while(1){
        while(1){
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<seconds>(stop - start);
            if(T<0.5||duration.count()>60){
                //cout<<"hello"<<endl;
                T = INIT;
                start = high_resolution_clock::now();
            }
            iter++;
            vector<int> newpath;
            double newcost;
            // l and r change from 1 to n-1
            int l = 0,r = 0;
            l = rand()%(n-1);
            l++;
            while(r==0||r==l){
                r = rand()%n;
            }
            if(l>r){
                swapint(l,r);
            }
            //construct new path
            //cout<<l<<" "<<r<<endl;
            newpath = best_tour;
            fup(itrlol,0,r-l+1){
                if(itrlol>(r-l)/2){
                    continue;
                }
                int temporary = newpath[l+itrlol];
                newpath[l+itrlol] = newpath[r-itrlol];
                newpath[r-itrlol] = temporary;
            }
            newcost = FindCost(newpath,adj);
                //ctr++;
            if(newcost<realbestcost){
                realbestcost = newcost;
                real_best_tour = newpath;
                vout(real_best_tour);
                //ctr=0;
                cout<<realbestcost<<" "<<iter<<" "<<itr<<" "<<T<<endl;
                start = high_resolution_clock::now();
            }

            if(newcost<bestcost){
                best_tour = newpath;
                bestcost = newcost;
                CoolingFunction(T);
                continue;
            }
            //return;
            //calculate newcost,output if more efficient, then calc prob of change; and change tour appropriately
            
            double deltaE = newcost - bestcost;
            double prob = FindProbab(deltaE,T);
            double randomnum = ((double) rand() / (RAND_MAX));
            
            if(randomnum<prob){
                best_tour = newpath;
                bestcost = newcost;
                //CoolingFunction(T);
            }
            
        }   
    }
    cout<<realbestcost<<endl;
    //vout(real_best_tour);
}


int main(){
    //stext();
    FASTIO;
    sinp(s1);
    string s2;
    if(s1=="non"){
        cin>>s2;
    }
    inp(n);
    vector<double> X(n,0);
    vector<double> Y(n,0);
    fup(i,0,n){
        double x,y;
        cin>>x>>y;
        X[i]=x;
        Y[i]=y;
    }
    vector<double> prop(n,0);
    vector<vector<double>> adj(n,prop);
    fup(i,0,n){
        fup(j,0,n){
            double d;
            cin>>d;
            adj[i][j] = d;
        }
    }
    if(s1=="euclidean"){
        fup(i,0,n){
            fup(j,i,n){
                adj[i][j] = sqrt((X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]));
                adj[j][i] = adj[i][j];
            }
        }
        CycleHeuristic(n,adj);
        Simulated_Annealing(n,adj);
        //vvout(adj);
    }
    else if(s1 == "non" && s2 == "euclidean"){
        CycleHeuristic(n,adj);
        Simulated_Annealing(n,adj);
    }
    else{
        cout<<"Type of distance mentioned is invalid."<<endl;
    }
    return 0;
}