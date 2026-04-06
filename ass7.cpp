#include <iostream>
#include <climits>
using namespace std;

class UtilityGrid {
    int n;
    int adj[20][20];
    string station[20];
    int dist[20];
    bool visited[20];
public:

    void createGraph() {
        cout<<"Enter number of power stations: ";
        cin>>n;
        cout<<"Enter station number:\n";
        for(int i=0;i<n;i++){
            cin>>station[i];
        }
        cout<<"Enter adjacency matrix (time between stations):\n";
        for(int i=0;i<n;i++) {
            for(int j=i;j<n;j++) {
                cout<<station[i]<<" and "<<station[j]<<": "<<endl;
                cin>>adj[i][j];
                if(adj[i][j]==0 && i!=j){
                    adj[i][j] = INT_MAX;
                }
                adj[j][i] = adj[i][j];
            }
        }
    }

    void dijkstra(int start) {
        for(int i=0;i<n;i++) {
            dist[i] = INT_MAX;
            visited[i] = false;
        }
        dist[start] = 0;
        for(int count=0; count<n-1; count++) {
            int min = INT_MAX, u;
            for(int i=0;i<n;i++) {
                if(!visited[i] && dist[i] <= min) {
                    min = dist[i];
                    u = i;
                }
            }
            visited[u] = true;
            for(int v=0; v<n; v++) {
                if(!visited[v] && adj[u][v] != INT_MAX &&
                   dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
        cout<<"\nMinimum power transmission time:\n";
        for(int i=0;i<n;i++){
            cout<<station[start]<<" -> "<<station[i]<<" = "<<dist[i]<<endl;
        }
    }

    void reachableStations(int limit) {
        cout<<"\nStations reachable within time "<<limit<<":\n";
        bool found = false;
        for(int i=0;i<n;i++) {
            if(dist[i] != INT_MAX && dist[i] <= limit) {
                cout<<station[i]<<" (time "<<dist[i]<<")"<<endl;
                found = true;
            }
        }
        if(!found){
            cout<<"No stations reachable within the time limit."<<endl;
        }
    }
};

int main() {
    UtilityGrid g;
    int start, limit = 0;

    g.createGraph();

    cout<<"Enter source station index: ";
    cin>>start;
    g.dijkstra(start);

    cout<<"\nEnter maintenance time limit: ";
    cin>>limit;
    g.reachableStations(limit);
    
    return 0;
}