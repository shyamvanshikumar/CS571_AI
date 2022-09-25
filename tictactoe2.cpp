#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define vvi vector<vector<char> >
#define MAXLEVEL 3
const int INF = 1e9+7;

int k;

pair<int,vvi> Max_value(const vvi &, int, int, int);
pair<int,vvi> Min_value(const vvi &, int, int, int);
int terminal_check(const vvi &, int);

string Alpha_Beta_Search(const vvi &state, char player) {
    pair<int, vvi> move_pair = Max_value(state, -INF, INF, 0);
    vvi move = move_pair.second;

    int n = state.size();

    bool one = false;
    string ans;
    ans.push_back(player);
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(state[i][j] != move[i][j]) {
                if(!one) {
                    ans.append(to_string(i+1));
                    ans.push_back('a'+j);
                }
                else {
                    throw invalid_argument("More than one actions taken");
                }
            }
        }
    }
    return ans;
}

pair<int, vvi> Max_value(const vvi &state, int alpha, int beta, int level) {
    // static int maxcall=0;
    // cout<<maxcall++<<"\n";
    int t = terminal_check(state, level);
    if(t != -2)
        return {t, state};

    int v = -INF;
    int n = state.size();
    vvi nstate(state), ans;

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(nstate[i][j] == '\0') {
                nstate[i][j] = 'x';
                pair<int, vvi> v2 = Min_value(nstate, alpha, beta, level+1);
                if(v2.first > v) {
                    v = v2.first;
                    ans = nstate;
                    alpha = max(alpha,v);
                }
                if(v >= beta) {
                    return {v, ans};
                }
                nstate[i][j] = '\0';
            }
        }
    }
    return {v,ans};
}

pair<int, vvi> Min_value(const vvi &state, int alpha, int beta, int level) {
    // static int mincall=100;
    // cout<<mincall++<<"\n";

    int n = state.size();
    // cout<<"\n";
    // for(int i=0;i<n;i++) {
    //     for(int j=0;j<n;j++)
    //         cout<<state[i][j];
    //     cout<<"\n";
    // }

    int t = terminal_check(state, level);
    if(t != -2)
        return {t, state};

    int v = INF;
    vvi nstate(state), ans;

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(nstate[i][j] == '\0') {
                nstate[i][j] = 'o';
                pair<int, vvi> v2 = Max_value(nstate, alpha, beta, level+1);
                if(v2.first < v) {
                    v = v2.first;
                    ans = nstate;
                    beta = min(beta,v);
                }
                if(v <= alpha) {
                    return {v, ans};
                }
                nstate[i][j] = '\0';
            }
        }
    }
    return {v,ans};
}

int terminal_check(const vvi &state, int level) {
    bool com = true;
    int n = state.size();

    int nx=0, no=0;
    for(int i=0;i<n;i++) {
        nx = no = 0;
        for(int j=0;j<n;j++) {
            if(state[i][j] == 'x') {
                if(nx==0 || (nx!=0 && state[i][j-1]=='x'))
                    nx++;
                no = 0;
            }
            else if(state[i][j] == 'o') {
                if(no==0 || (no!=0 && state[i][j-1]=='o'))
                    no++;
                nx = 0;
            }
            else {
                nx = no = 0;
            }
            //cout<<nx<<" "<<no<<"\n";
            if(nx == k)
                return 1;
            if(no == k)
                return -1;
        }
    }

    //cout<<"Code Check Terminal 1\n";

    //nx = no = 0;
    for(int j=0;j<n;j++) {
        nx = no = 0;
        for(int i=0;i<n;i++) {
            if(state[i][j] == 'x') {
                if(nx==0 || (nx!=0 && state[i-1][j]=='x'))
                    nx++;
                no = 0;
            }
            else if(state[i][j] == 'o') {
                if(no==0 || (no!=0 && state[i-1][j]=='o'))
                    no++;
                nx = 0;
            }
            else {
                nx = no = 0;
            }
            //cout<<nx<<" "<<no<<"\n";
            if(nx == k)
                return 1;
            if(no == k)
                return -1;
        }
    }

    //cout<<"Code Check Terminal 1\n";

    //nx = no = 0;
    for(int m=2*n-1;m>=0;m--) {
        int si = (m>=n) ? m-n : 0;
        int sj = (m>=n) ? 0 : n-m;
        nx = no = 0;
        for(int l=0;l<n-max(si,sj);l++) {
            int i = si+l;
            int j = sj+l;

            if(state[i][j] == 'x') {
                if(nx==0 || (nx!=0 && state[i-1][j-1]=='x'))
                    nx++;
                no = 0;
            }
            else if(state[i][j] == 'o') {
                if(no==0 || (no!=0 && state[i-1][j-1]=='o'))
                    no++;
                nx = 0;
            }
            else {
                nx = no = 0;
            }
            //cout<<nx<<" "<<no<<"\n";

            if(nx == k)
                return 1;
            if(no == k)
                return -1;
        }
    }
    //cout<<"Code Check Terminal 1\n";

    //nx = no = 0;
    for(int m=2*n-1;m>=0;m--) {
        int si = (m>=n) ? 0 : n-m;
        int sj = (m>=n) ? 2*n-1-m : n-1;
        int u = (m>=n) ? sj+1 : n-si;
        nx = no = 0;
        for(int l=0;l<u;l++) {
            int i = si+l;
            int j = sj-l;

            //cout<<i<<" "<<j<<"\n\n";

            if(state[i][j] == 'x') {
                if(nx==0 || (nx!=0 && state[i-1][j+1]=='x'))
                    nx++;
                no = 0;
            }
            else if(state[i][j] == 'o') {
                if(no==0 || (no!=0 && state[i-1][j+1]=='o'))
                    no++;
                nx = 0;
            }
            else {
                nx = no = 0;
            }
            //cout<<nx<<" "<<no<<"\n";

            if(nx == k)
                return 1;
            if(no == k)
                return -1;
        }
    }

    //cout<<"Code Check Terminal 1\n";
    int openPos = 0;
    if(level >= MAXLEVEL) {
        for(int i=0;i<n;i++) {
            for(int j=0;j<=n-k;j++) {
                bool outO = true, withX = false;
                for(int l=0;l<k;l++) {
                    if(state[i][j+l] == 'o') {
                        outO = false;
                        break;
                    }
                    if(state[i][j+l] == 'x')
                        withX = true;
                }
                if(outO && withX)
                    openPos++;
            }
        }

        for(int j=0;j<n;j++) {
            for(int i=0;i<=n-k;i++) {
                bool outO = true, withX = false;
                for(int l=0;l<k;l++) {
                    if(state[i+l][j] == 'o') {
                        outO = false;
                        break;
                    }
                    if(state[i+l][j] == 'x')
                        withX = true;
                }
                if(outO && withX)
                    openPos++;
            }
        }

        for(int i=0;i<=n-k;i++) {
            for(int j=0;j<=n-k;j++) {
                bool outO = true, withX = false;
                for(int l=0;l<k;l++) {
                    if(state[i+l][j+l] == 'o') {
                        outO = false;
                        break;
                    }
                    if(state[i+l][j+l] == 'x')
                        withX = true;
                }
                if(outO && withX)
                    openPos++;
            }
        }

        for(int i=0;i<=n-k;i++) {
            for(int j=k-1;j<n;j++) {
                bool outO = true, withX = false;
                for(int l=0;l<k;l++) {
                    if(state[i+l][j-l] == 'o') {
                        outO = false;
                        break;
                    }
                    if(state[i+l][j-l] == 'x')
                        withX = true;
                }
                if(outO && withX)
                    openPos++;
            }
        }
        return openPos;
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(state[i][j] == '\0') {
                return -2;
            }
        }
    }

    return 0;
}

int main() {
    int n;
    cout<<"Enter the size of the board and value of k\n";
    cin>>n>>k;
    cout<<"Enter whether first player(x) or second player(o)\n";
    char p;
    cin>>p;
    string mov;
    vvi state(n, vector<char>(n,'\0'));

    // for(int i=0;i<n;i++)
    //     state[i][n-1-i] = 'o';

    if(p == 'o') {
        cout<<"I am second player\n";
        cout<<"Enter your move\n";
        cin>>mov;
        int i = mov[1]-'1';
        int j = mov[2]-'a';
        state[i][j] = 'o';      //Though I am second player, I will use o for opponent and x for me.
    }

    char turn = 'x';
    while(1) {
        int result = terminal_check(state, 0);
        // cout<<"\n";
        // for(int i=0;i<n;i++) {
        //     for(int j=0;j<n;j++)
        //         cout<<state[i][j];
        //     cout<<"\n";
        // }
        if(result != -2) {
            if(result == 1)
                cout<<"I win\n";
            else if(result == -1)
                cout<<"You win\n";
            else 
                cout<<"Match draw\n";
            break;
        }

        if(turn=='x') {
            mov = Alpha_Beta_Search(state, p);
            cout<<mov<<"\n";
            int i = mov[1]-'1';
            int j = mov[2]-'a';
            state[i][j] = 'x';
            turn = 'o';
        }

        else {
            cout<<"Enter your move\n";
            cin>>mov;
            int i = mov[1]-'1';
            int j = mov[2]-'a';
            state[i][j] = 'o';
            turn = 'x';
        }
    }
    
    return 0;
}
