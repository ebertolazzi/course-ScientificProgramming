/*-----------------------------------------------------
|                                                     |
|      Manuel Boldrer                                 |
|      Dipartimento di Ingegneria Industriale         |
|      Universita` degli Studi di Trento              |
|      Via Sommarive 9, Trento, Italy                 |
|      email: manuel.boldrer@unitn.it                 |
|                                                     |
|      version: 0.1 01-03-2019                        |
|                                                     |
-----------------------------------------------------*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include <exception>
#include <Eigen/Dense>
#include <algorithm>
#include <fstream>
#include <tuple>
#include <numeric>     

using namespace Eigen;
using namespace std;

class Graph {   
    // Global Variables
    int n_nodes;                                      
    MatrixXd Adj = MatrixXd::Zero(n_nodes, n_nodes);  
    MatrixXd Deg = MatrixXd::Zero(n_nodes, n_nodes);  
    MatrixXd Lap = MatrixXd::Zero(n_nodes, n_nodes);  
    public:
    // Constructor
    Graph(int n):n_nodes(n){
    }
    // Deconstructor
    ~Graph(){
    }
    // Method that adds a link to the Graph (acts on A,D,L)
    void Add_link( int node, int n_neighbours, vector<int>* neighbours) {
        if (node > n_nodes-1) {
            n_nodes++;
            Adj.conservativeResize(Adj.rows()  , Adj.cols()+1);
            Adj.conservativeResize(Adj.rows()+1, Adj.cols()  );
            Deg.conservativeResize(Deg.rows()  , Deg.cols()+1);
            Deg.conservativeResize(Deg.rows()+1, Deg.cols()  );
            Lap.conservativeResize(Lap.rows()  , Lap.cols()+1);   
            Lap.conservativeResize(Lap.rows()+1, Lap.cols()  ); 
            Adj.row(node) =         RowVectorXd::Zero(n_nodes);
            Adj.col(node) =            VectorXd::Zero(n_nodes);        
            Deg.row(node) =         RowVectorXd::Zero(n_nodes);
            Deg.col(node) =            VectorXd::Zero(n_nodes);  
            Lap.row(node) =         RowVectorXd::Zero(n_nodes);
            Lap.col(node) =            VectorXd::Zero(n_nodes);    
        }        
        for ( int i = 0 ; i < n_neighbours ; ++i ) {
            Adj(node,(*neighbours)[i]) = 1;
            Deg(node,node)            += n_neighbours;
        }
        Lap = Deg - Adj; // inefficiente
    }
    // Method that adds links to the Undirected Graph (acts on A,D,L)
    void Add_links(vector<int>*e1, vector<int>*e2) {
        for ( int i = 0 ; i < (*e1).size() ; ++i ) {
            Adj((*e1)[i]-1,(*e2)[i]-1) = 1;
            Adj((*e2)[i]-1,(*e1)[i]-1) = 1;
        }
        for(int i = 0; i < n_nodes; ++i){
            for(int j = 0; j < n_nodes; ++j){
                Deg(i,i) += Adj(i,j);        
            }
        } 
        Lap = Deg - Adj;
    }
    // Method that adds links to the Directed Graph (acts on A,D,L) 
    void Add_linksD(vector<int>*e1, vector<int>*e2) {
        for ( int i = 0 ; i < (*e1).size() ; ++i ) {
            Adj((*e2)[i]-1,(*e1)[i]-1) = 1;
        }
        for(int i = 0; i < n_nodes; ++i){
            for(int j = 0; j < n_nodes; ++j){
                Deg(i,i) += Adj(i,j);        
            }
        } 
        Lap = Deg - Adj; // inefficiente
    }
    // Method that removes a link from the Graph (act on A,D,L)
    void Delete_link(int node, int n_neighbours2delete,vector<int>* neighbours){
            for ( int i = 0 ; i < n_neighbours2delete ; ++i ) {
                Adj(node,(*neighbours)[i]) = 0;
                Deg(node,node)             -= n_neighbours2delete;
            }
            Lap = Deg - Adj; // inefficiente
    }
    void Delete_node(int node){
        n_nodes--;
        RowVectorXd tmpr   = Adj.row(n_nodes);
        Adj.row(n_nodes)   = Adj.row(node) ;
        Adj.row(node)      = tmpr;
        Adj.conservativeResize(Adj.rows()-1  , Adj.cols());
        VectorXd tmpc      = Adj.col(n_nodes);
        Adj.col(n_nodes)   = Adj.col(node) ;
        Adj.col(node)      = tmpc;
        Adj.conservativeResize(Adj.rows()  , Adj.cols()-1);  
        Deg = MatrixXd::Zero(n_nodes, n_nodes);  // Degree    matrix
        for(int i = 0; i < n_nodes; ++i){
            for(int j = 0; j < n_nodes; ++j){
                Deg(i,i) += Adj(i,j);        
            }
        }            
        Lap = Deg - Adj;
    }
    // Methods that prints the main Matrices
    void Print_Laplacian(){cout << "The Laplacian is:        \n" << Lap << "\n";}
    void Print_Adjacency(){cout << "The Adjacency matrix is: \n" << Adj << "\n";}
    void Print_Degree   (){cout << "The Degree matrix is:    \n" << Deg << "\n";}
    // Method that compute the Eigenvalues of the Laplacian
    VectorXcd EigenvalueOfLap(){
        VectorXcd eivals = Lap.eigenvalues();
        return eivals;
    }
    // Method that checks if the Graph is Undirected or Directed
    bool IsUndirected(){
        if (Adj == Adj.transpose()) {
            cout << "The Graph is UNDIRECTED"<<endl;
            return 1;
        }
        else{
            cout << "The Graph is DIRECTED"<<endl;
            return 0;
        }
    }
    // Method that tells me if the Graph is NOT CONNECTED, CONNECTED or STRONGLY CONNECTED
    // Properties of the power of Adjacency matrix.
    // Mark Newman's book - Networks: An Introduction (Page 137, Eq: 6.31) 
    bool IsConnected(){
        MatrixXd A          = Adj;
        int count           = 0;
        int eigenvalue_zero = 0;
        vector<int> V; 

        V = ConnectedSubGraph(0);
        if( V.size()< n_nodes ){
            cout << "The Graph is NOT connected" <<endl;
            return 0;
        }
        repeat:
        for ( int i = 0 ; i < n_nodes ; ++i ) {
            for ( int j = 0 ; j < n_nodes ; ++j ) {
                if ( i!=j && A(i,j) == 0 ){
                    A = A+A*Adj;
                    count++;
                    if(count > n_nodes){
                        VectorXcd eival =  EigenvalueOfLap();
                        for(int i = 0; i < eival.size(); i++){                        
                            if (sqrt(pow(eival(i).real(),2) + pow(eival(i).imag(),2)) < 1e-10) {
                                eigenvalue_zero +=1;
                            }
                        }
                        if (eigenvalue_zero == 1) {
                            cout << "The Graph is WEAKLY connected." <<endl;
                            return 1;
                            goto stop;
                        }
                        else{
                            cout << "The Graph will NEVER reach CONSENSUS." <<endl;
                            return 0;
                            goto stop;
                        }
                    }
                    goto repeat;
                }              
            }
        }
        stop:
        if (count == 0){
            cout << "The Graph is STRONGLY connected, or complete." <<endl;
            return 1;
        }
        if (count >0 && count < n_nodes){
            cout << "The Graph is SIMPLY connected." <<endl;
            return 1;
        }   
    }
    // Method that computes the number of possible spanning trees
    // Kirchhoff's theorem see e.g. https://en.wikipedia.org/wiki/Kirchhoff%27s_theorem
    unsigned long long NumberOfSpanningTree(){ 
        if( IsConnected()){
            MatrixXd Lapsmall = Lap.block(0,0,n_nodes-1,n_nodes-1);
            unsigned long long numberOfSpanningTrees = Lapsmall.determinant();
            cout << "The number of possible spanning trees is: " << numberOfSpanningTrees << " (0 means that is already a spanning tree)."<< endl; 
            return numberOfSpanningTrees;
        }
        else{
            return 0;
        }
    }
    // Method that tells me if the Graph is a Spanning Tree
    // for cycle detection in digraphs I used the  Properties of the power of Adjacency matrix.
    // for cycle detection in undirected graphs I used the Trace(L) and the rank(L) 
    bool IsSpanning_tree(){
        if(true){
            if( IsUndirected() ){
                FullPivLU<MatrixXd> lu_decomp(Lap);
                if ( 0.5*Lap.trace() > lu_decomp.rank() ) {
                    cout << "the Undirected Graph has at least one cycle i.e. is NOT a spanning tree." << endl;
                    return 0;
                }
            }
            else{
                MatrixXd A  = Adj;
                for(int i = 0; i < n_nodes-1; ++i){
                    A = A*Adj;
                    int productAjj = 1;

                    for(int j = 0; j < n_nodes; ++j){
                        productAjj *= A(j,j); 
                    }
                        if (productAjj > 0 ) {
                            cout << "the Digraph has at least one cycle i.e. is NOT a spanning tree." << endl;
                            return 0;
                        }                               
                }
            }
        }
        else{
            if (IsConnected()) {
                cout << "the Graph has no cycle and is connected i.e. is a spanning tree." << endl;
                return 1;
            }
            else{
                cout << "the Graph has no cycle but is not connected i.e. is NOT a spanning tree." << endl;
                return 0;
            }      
        }   
            cout << "the Graph has not a cycle i.e. if it is connected is a spanning tree." << endl;
            return 1;
    }
    // Method that return the indexes of a sorted vector
    vector<int> sort_indexes(vector<int> &v) {
        vector<int> idx(v.size());
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(),[&v](int i1, int i2) {return v[i1] > v[i2];});
        return idx;
    }
    // Method that gives me the Adjacency matrix of a spanning tree
    MatrixXd MinimumHeighSpanningTree(){
        if( IsConnected() ){
            vector<int> visit[n_nodes];
            MatrixXd AdjST = MatrixXd::Zero(n_nodes, n_nodes);
            vector<int> n[n_nodes];
            for(int i = 0; i < n_nodes; ++i){    
                for(int j = 0; j < n_nodes; ++j){
                    if ( Adj.row(i)(j) ){
                        visit[i].push_back(j);
                    }   
                }
            }   
            vector<int> visited;
            vector<int> degree;
            vector<int> sortidx; 
            for(int i = 0; i < n_nodes; ++i){
                degree.push_back(Deg(i,i));
            }
            sortidx = sort_indexes(degree);
            /*
            for(int i = 0; i < n_nodes; ++i){
                for(int k = 0; k < (visit[i].size()); ++k){
                    if(find(visited.begin(), visited.end(), i) != visited.end()){
                        if(find(visited.begin(), visited.end(), visit[i][k]) != visited.end() && AdjST(visit[i][k],i) == 0){
                        }
                        else{
                            visited.push_back(visit[i][k]);
                            AdjST(i,visit[i][k]) = 1; 
                        }                
                    } 
                    else{ 
                        visited.push_back(visit[i][k]);
                        AdjST(i,visit[i][k]) = 1;
                    }
                }
            } 
            */
            for(int i = 0; i < n_nodes; ++i){
                for(int k = 0; k < (visit[sortidx[i]].size()); ++k){
                    if(find(visited.begin(), visited.end(), sortidx[i]) != visited.end()){
                        if(find(visited.begin(), visited.end(), visit[sortidx[i]][k]) != visited.end() && AdjST(visit[sortidx[i]][k],sortidx[i]) == 0){
                        }
                        else{
                            visited.push_back(visit[sortidx[i]][k]);
                            AdjST(sortidx[i],visit[sortidx[i]][k]) = 1; 
                        }                
                    } 
                    else{ 
                        visited.push_back(visit[sortidx[i]][k]);
                        AdjST(sortidx[i],visit[sortidx[i]][k]) = 1;
                    }
                }
            }        
        return AdjST;
        }
        else{
            cout << "DOES NOT EXIST a spanning tree for NOT connected graphs";
            MatrixXd zero =  MatrixXd::Zero(1, 1);
            return zero; 
        }
    }
    // Method that, given a node, return the nodes that are connected to it.
    vector<int> ConnectedSubGraph(int node){
        MatrixXd A = Adj;
        vector<int> V;
        V.push_back(node);
        for ( int i = 0 ; i < n_nodes ; ++i ) {
                A = A+A*Adj;
            }
        for(int i = 0; i < V.size(); i++){
            for(int j = 0; j < n_nodes; j++){
                if ( A(V[i],j)>0 && !(find(V.begin(), V.end(), j) != V.end()) ) {
                    V.push_back(j);
                }
                if ( A(j,V[i])>0 && !(find(V.begin(), V.end(), j) != V.end()) ) {
                    V.push_back(j);
                }
            } 
        }
        return V;
    }
    // Factorial of a number
    unsigned long factorial(unsigned long n){
        if(n > 1)
           return n * factorial(n - 1);
        else
            return 1;
    }
    // Method that return all the n!/(k!(n-k)!) combination without repetition
    // (clique and r values are inverted for this function) 
    MatrixXd Combinations(int n, int clique){        
        unsigned long tmp   = 1;
        int r     = n-clique;
        for(int i = n; i > clique; --i){
            tmp = tmp * i;
        }
        int N   = tmp/(factorial(r));
        MatrixXd A = MatrixXd::Zero(N, r);
        int count = r-1;
        int flag  = 0;
        for(int k = 0; k < N; ++k){ 
                flag=0;          
            for(int j = 0; j < r; ++j){
                if(k==0){
                    A(k,j) = j;
                }
                else{
                    if( A(k-1,j) == n-r+j ){
                        count = j;
                        flag++;
                    }
                    if(flag == 0){
                        if( j!=count ){ 
                            A(k,j) = A(k-1,j);
                        }
                        else{
                            A(k,j) = A(k-1,j)+1;
                        }
                    }
                    else if (flag==1) {                  
                        for( int jj = 0; jj < r; jj++){
                            if(jj < count-1){ 
                                A(k,jj) = A(k-1,jj);
                            }
                            else if(jj == count-1) {
                                A(k,jj) = A(k-1,jj)+1;
                            }
                            else{
                                A(k,jj) = A(k,jj-1)+1; 
                            }
                        }
                    }
                    else{
                    }                                   
                }
            }
        }   
        return A;
    }
    // Methods used to remove n last row of a matrix
    MatrixXd removeRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove){
        unsigned int numRows = matrix.rows()-rowToRemove;
        unsigned int numCols = matrix.cols();
        matrix.conservativeResize(numRows,numCols);
        return matrix;
    }
    // Method that return the cliques of a graph
    MatrixXd StronglyConnectedSubGraph(int clique_dim){
        MatrixXd A           = Adj;
        MatrixXd A_norm      = MatrixXd::Zero(n_nodes, n_nodes);
        int r_dim            = n_nodes - clique_dim;
        unsigned long tmp    = 1;
        for(int i = n_nodes; i > r_dim; --i){
            tmp = tmp * i;
        }
        int N                = tmp/(factorial(clique_dim));
        int flag             = 0;
        int counter          = 0;
        MatrixXd C2R         = Combinations(n_nodes,r_dim);            
        MatrixXd Skew        = MatrixXd::Ones(clique_dim, clique_dim) - MatrixXd::Identity(clique_dim, clique_dim);
        MatrixXd matrixR     = MatrixXd::Zero(clique_dim, n_nodes);
        MatrixXd matrixRC    = MatrixXd::Zero(clique_dim, clique_dim);
        MatrixXd Cliques     = MatrixXd::Zero(N, clique_dim);
        MatrixXd IndexToKeep = MatrixXd::Zero(N, clique_dim);
        A = Adj;       
        for(int i = 0; i < n_nodes; ++i){
            for(int j = 0; j < n_nodes; ++j){
                if (A(i,j)){
                    A_norm(i,j) = A(i,j)/A(i,j);
                }
                else{
                    A_norm(i,j) = 0;
                }    
            }   
        }
        for(int i = 0; i < N; i++){
            for(int j = 0; j < clique_dim; j++){
                matrixR.row(j) =A_norm.row(C2R(i,j));
            }
            for(int j = 0; j < clique_dim; j++){
                matrixRC.col(j) =matrixR.col(C2R(i,j));
            }
            if( matrixRC == Skew ){
                flag = 1;
                Cliques.row(counter) = C2R.row(i);
                counter ++;
            }
        }
        Cliques = removeRow(Cliques, N - counter);
        return Cliques;
    } 
// EOC
};

struct ImportedGraph{
    int nn;
    int ne;
    vector<int> Edge1;
    vector<int> Edge2;
};
// Function to read a file generated with Maple
void ReadMapleGeneratedFile(string namefile, ImportedGraph& GraphInfo){
        ifstream theFile(namefile);   
        int number     ;
        int count  = 0 ;
        int count1 = 0 ;
        int count2 = 0 ;
        theFile >> GraphInfo.nn    ; 
        theFile >> GraphInfo.ne    ;
        while( theFile >> number ){
            if( count % 2 == 0 ){            
                GraphInfo.Edge1.push_back(number);
                count1++;
            }
            else{
                GraphInfo.Edge2.push_back(number);
                count2++;
            }
            count++;
        } 
} 

/*----------------------------------------------------------------------------------------------------------------*/

int main(){
    // name of the file generated with Maple that you want to read
    string str = "k6";
    ImportedGraph MG;
    ReadMapleGeneratedFile(str,MG);
    int N = MG.nn;
    Graph G(MG.nn);
    G.Add_links(&(MG.Edge1),&(MG.Edge2));  
    /*
    Graph G(3);
    vector<int> V0 = {2};
    vector<int> V1 = {};
    vector<int> V2 = {0,1};
    G.Add_link(0,V0.size(),&V0);        
    G.Add_link(1,V1.size(),&V1);        
    G.Add_link(2,V2.size(),&V2);        
    */
    /*
    vector<int> V0 =  {8};
    vector<int> V8 =  {0};

    vector<int> V23 = {35};
    vector<int> V35 = {23};

    G.Add_link(0,V0.size(),&V0);
    G.Add_link(8,V0.size(),&V8);
    G.Add_link(23,V23.size(),&V23);
    G.Add_link(35,V35.size(),&V35);
    vector<int> Vd42 =  {34,32,41};
    G.Delete_link(42,Vd42.size(),&Vd42);
    vector<int> V46 = {9,2,5};

    G.Add_link(46,V46.size(),&V46);
    G.Delete_node(42);
    */
    //G.MinimumHeighSpanningTree();
    //G.Print_Adjacency();
    //G.Print_Degree();
    //G.Print_Laplacian();
    //G.IsSpanning_tree();
    //G.IsConnected();
    //G.IsUndirected();
    //unsigned long long NST = G.NumberOfSpanningTree();
    //cout << "(**ONLY FOR UNDIRECTED GRAPH**) One of the " << NST << " possbile spanning trees has as Adjacency matrix: \n" << G.MinimumHeighSpanningTree()<<endl;
    //vector<int> VVV = G.ConnectedSubGraph(3);
    //int dim_cliques = 3;
    //cout << "The cliques of dimension "<< dim_cliques <<" are the following: \n" << G.StronglyConnectedSubGraph(dim_cliques) <<endl;    
    return 0;
}


