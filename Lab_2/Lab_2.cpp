#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

struct Node
{
    int key, value;
    Node(int k, int v) : key(k), value(v) {}
};

class BinaryHeap
{
    vector<Node> heap;
public:
    void push(Node node)
    {
        heap.push_back(node);
        int i = heap.size() - 1;
        while (i > 0 && heap[(i - 1) / 2].key > node.key)
        {
            heap[i] = heap[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        heap[i] = node;
    }

    Node top()
    {
        return heap[0];
    }

    void pop() {
        if (heap.empty())
        {
            return;
        }
        heap[0] = heap.back();
        heap.pop_back();
        if (heap.empty())
        {
            return;
        }
        int i = 0;
        while (i < heap.size())
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left >= heap.size())
            {
                break;
            }
            int j = left;
            if (right < heap.size() && heap[right].key < heap[left].key)
            {
                j = right;
            }
            if (heap[i].key <= heap[j].key)
            {
                break;
            }
            swap(heap[i], heap[j]);
            i = j;
        }
    }


    bool empty()
    {
        return heap.empty();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    int n, s;
    cout << "Введите количество вершин и исток (нумерация вершин начинается с 0)\n";
    cin >> n >> s;

    cout << "Матрица смежности\n";
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }

    BinaryHeap heap;
    vector<int> dist(n, INF);
    heap.push(Node(0, s));
    dist[s] = 0;

    while (!heap.empty())
    {
        int u = heap.top().value;
        heap.pop();
        for (int v = 0; v < n; v++)
        {
            if (v != u && v >= 0 && v < n && graph[u][v] != 0)
            {
                int alt = dist[u] + graph[u][v];
                if (alt < dist[v])
                {
                    dist[v] = alt;
                    heap.push(Node(dist[v], v));
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << "Расстояние до вершины " << i << " - " << dist[i] << endl;
    }
    return 0;
}