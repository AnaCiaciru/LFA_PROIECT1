#include <fstream>
#include <utility>
#include <vector>
#include <map>

#define NMAX 101
using namespace std;


ifstream fin("file.in");
ofstream fout("file.out");

void read(int &n, int &m, int &start, string &str, map <  int, vector < pair < int, char > > > &G, vector < bool > &F){

    int i, x, nrEnd;
    pair <int, char> p;
    fin >> n >> m;
    for(i = 0; i < m; i++){
        fin >> x >> p.first >> p.second;
        G[x].push_back(p);
    }
    fin >> start >> nrEnd;
    for(i = 0; i < nrEnd; i++){
        fin >> x;
        F[x] = true;
    }
    fin >> str;

}

bool final(int x, int pos, string str, vector <bool> F){
    if( str[pos] == 0)
        if(F[x])
            return true;
    return false;
}

void  DFS(int x, int pos, bool&ok, string str, map <int, vector < pair < int, char > > > G, vector <bool> F ){

    //caz particular pentru lambda
    if(str[pos] == '#') // # e codificat ca fiind lambda
    {
        if(F[x]){
            ok = true;
            return;
        }
        else{
            ok = false;
            return ;
        }

    }

    vector < pair < int, char > > :: iterator it;
    for(it = G[x].begin(); it != G[x].end(); it++){
        if( it->second == str[pos]){
            if( final(it->first, pos+1, str, F) ) {
                ok = true;
                return;
            }
            else
                DFS(it->first, pos+1, ok, str, G, F);
        }

    }

}


void accepted(int start, string str, map <  int, vector < pair < int, char > > > G, vector < bool > F) {

    int pos = 0;
    bool ok = false;
    DFS(start, pos, ok, str, G, F);
    if(ok)
        fout << "DA" << endl;
    else
        fout << "NU" << endl;

}

int main() {
    int n, m; // nr-ul de stari si nr-ul de tranzitii
    map <  int, vector < pair < int, char > > > G; // graful
    int start; //starea initiala
    vector < bool > F(NMAX, false); // starile finale
    string str; // cuvantul de verificat

    read(n, m, start, str, G, F);
    accepted(start, str, G, F);
    return 0;
}