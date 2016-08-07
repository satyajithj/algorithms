/*
	author: satyajith
	algorithm: breadth first search

	complexity: O (|V| + |E|)
                linear in the size of the adjacency list

    -- determines the minimum number of edges to take, to reach
       vertices from the source vertex
*/

#include <iostream>
#include <climits>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

int main() {

	const int VERTICES = 6;		// set number of vertices here
    // graph as an adjacency list
    vector<vector<int>* > adj_list;
    adj_list.push_back(NULL);
    adj_list.push_back(new vector<int> ({2, 5}));
    adj_list.push_back(new vector<int> ({1, 5, 4, 3}));
    adj_list.push_back(new vector<int> ({2, 4}));
    adj_list.push_back(new vector<int> ({5, 2, 3}));
    adj_list.push_back(new vector<int> ({1, 2, 4}));

    bool visited[VERTICES];
    int dist[VERTICES];

    // initialize
    for(int i = 0; i < VERTICES; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
    }

    // 0 index is not used
    visited[0] = true;
    dist[0] = -1;

    // for output
    ostream_iterator<int> output(cout, " ");

    int source = 2;     // specify the source vertex
    dist[source] = 0;   // set distance of source to itself as zero
    visited[source] = true;     // source is marked as visited

    list<int> Q;
    Q.push_back(source);
    vector<int>* t_vec = NULL;

    while (Q.size() != 0) {

        int u = Q.front();
        Q.pop_front();
        t_vec = adj_list[u];

        for (int i = 0; i < t_vec->size(); i++) {
            if (!visited[(*t_vec)[i]]) {
                visited[(*t_vec)[i]] = true;
                dist[(*t_vec)[i]] = dist[u] + 1;

                for (int j = 0; j < adj_list[i + 1]->size(); j++)
                    Q.push_back((*adj_list[i + 1])[j]);
            }
        }
    }

    // display distance array
    cout << "edges to traverse: ";
    copy(dist + 1, dist + sizeof(dist)/sizeof(int), output);
    cout << endl;

    adj_list.clear();
    Q.clear();

    return 0;
}