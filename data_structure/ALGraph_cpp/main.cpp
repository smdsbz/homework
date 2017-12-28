#include <iostream>

#include "configs.hpp"
#include "ALGraph.hpp"

using namespace std;


int main(void) {

#if defined(_WIN32) || defined(_WIN64)
  system("chcp 65001");
#endif

  ALGraph *graph_pool[GRAPH_POOL_SIZE] = { nullptr };
  size_t working = 0;


  int op = -1;
  while (op) {
#if defined(__unix__) || defined(__linux__) || defined(__MACH__)
    system("clear");
#elif defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
    cout << "\n" << endl;

    // 操作选择提示
    cout << "    Menu for Graph On Adjacency List Structure     " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "       1. CreateGraph     2. DestroyGraph          " << endl;
    cout << "       3. LocateVex       4. GetVex                " << endl;
    cout << "       5. PutVex          6. FirstAdjVex           " << endl;
    cout << "       7. NextAdjVex      8. InsertVex             " << endl;
    cout << "       9. DeleteVex      10. InsertArc             " << endl;
    cout << "      11. DeleteArc      12. DFSTraverse           " << endl;
    cout << "      13. BFSTraverse                              " << endl;
    cout << endl;
    cout << "--------------------- EXTRA -----------------------" << endl;
    cout << "      14. SaveGraph     15. LoadGraph              " << endl;
    cout << "      16. SelectGraph                              " << endl;
    cout << endl;
    cout << "       0. Exit                                     " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "    请选择你的操作[0~16] ";
    cin >> op;

    // 检查是否有图的实例可以操作
    if (graph_pool[working] == nullptr
        && (op != 0 && op != 1 && op != 15 && op != 16)) {
      cout << "图还没有被创建！" << endl;
      getchar(); getchar();
      continue;
    }

    // 执行操作
    switch (op) {
      case 1: {
        cout << "请输入图顶点的个数：";
        size_t V; cin >> V;
        if (V <= 0 || V > MAX_VERTEX_NUM) {
          cout << "无法初始化图！" << endl;
          break;
        }
        cout << "请输入图的邻接矩阵：" << endl;
        InfoType **VR = new InfoType *[V];
        for (size_t row = 0; row < V; row++) {
          VR[row] = new InfoType[V];
          for (size_t col = 0; col < V; col++) {
            cin >> VR[row][col];
          }
        } // VR input
        if (CreateGraph(graph_pool[working], V, VR) == OK) {
          cout << "成功初始化图！" << endl;
        } else {
          cout << "初始化图失败！" << endl;
        }
        // delete VR
        for (size_t row = 0; row < V; row++) {
          delete [] VR[row];
        }
        delete [] VR;
        getchar(); getchar(); break;
      }
      case 2: {
        if (DestroyGraph(graph_pool[working]) == OK) {
          cout << "成功销毁图！" << endl;
        } else {
          cout << "销毁图失败！" << endl;
        }
        getchar(); getchar(); break;
      }
      case 3: {
        cout << "请输入顶点的ID：";
        int key; cin >> key;
        size_t ret = graph_pool[working]->LocateVex(key);
        if (ret == 0) {
          cout << "操作失败！" << endl;
        } else {
          cout << "顶点在 ALGraph.vertices 中的位序为 " << ret << endl;
        }
        getchar(); getchar(); break;
      }
      case 4: {
        cout << "请输入顶点的ID：";
        int key; cin >> key;
        int ret = graph_pool[working]->GetVex(key);
        if (ret == 0) {
          cout << "操作失败！" << endl;
        } else {
          cout << "顶点的值为 " << ret << endl;
        }
        getchar(); getchar(); break;
      }
      case 5: {
        cout << "请输入顶点的ID：";
        int key; cin >> key;
        cout << "请输入顶点新的值：";
        int val; cin >> val;
        if (graph_pool[working]->PutVex(key, val) == OK) {
          cout << "操作成功！" << endl;
        } else {
          cout << "操作失败！" << endl;
        }
        getchar(); getchar(); break;
      }
      case 6: {
        cout << "请输入顶点的ID：";
        int key; cin >> key;
        VNode *vex = graph_pool[working]->FirstAdjVex(key);
        if (vex == nullptr) {
          cout << "操作失败！" << endl;
        } else {
          cout << "所求顶点为 "
               << "<VNode @ " << vex << "ID = " << vex->data.id
               << " data = " << vex->data.data << ">" << endl;
        }
        getchar(); getchar(); break;
      }
      case 7: {
        cout << "请输入弧尾的ID：";
        int v; cin >> v;
        cout << "请输入弧头的ID：";
        int w; cin >> w;
        VNode *vex = graph_pool[working]->NextAdjVex(v, w);
        if (vex == nullptr) {
          cout << "操作失败！" << endl;
        } else {
          cout << "所求顶点为 "
               << "<VNode @ " << vex << "ID = " << vex->data.id
               << " data = " << vex->data.data << ">" << endl;
        }
        getchar(); getchar(); break;
      }
      case 0: { break; }
      default: { break; }
    }
  }

  for (working = 0; working < GRAPH_POOL_SIZE; working++) {
    DestroyGraph(graph_pool[working]);
  }

  return 0;
}
