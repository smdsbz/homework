#ifndef ALGRAPH_H_
#define ALGRAPH_H_

#define MAX_VERTEX_NUM  20
#define GRAPH_POOL_SIZE 10


// 弧数据原子类型
typedef int InfoType;

// 顶点数据原子类型
typedef struct _VertexType {
  int   id;   // 顶点唯一标示域
  int   data; // 顶点值
} VertexType;

typedef struct _ArcNode {
  int               adjvex;   // 弧头标示域的值
  InfoType          info;     // 弧信息
  struct _ArcNode  *nextarc;  // 指向下一条弧
} ArcNode;

typedef struct _VNode {
  VertexType  data;     // 顶点信息
  ArcNode    *firstarc; // 与该顶点关联的第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];


class ALGraph {
public: // a very Pythonic `public` sign :P

  AdjList vertices; // 顶点集
  int     vexnum;   // 顶点总数
  int     arcnum;   // 弧总数

public:

  ALGraph();
  ALGraph(size_t V, InfoType **VR);
  ~ALGraph(void);
  size_t LocateVex(int key);
  int GetVex(int key);
  status PutVex(int key, int value);
  VNode *FirstAdjVex(int key);
  VNode *NextAdjVex(int v, int w);
  status InsertVex(int data=233);
  status DeleteVex(int key);
  status InsertArc(int v, int w, InfoType weight=1);
  status DeleteArc(int v, int w);
  status DFSTraverse(status (*visit)(VNode *));
  status BFSTraverse(status (*visit)(VNode *));

  status CommitToFile(const char *filename, bool overwrite=true);

private:

  inline int _Index2Key(size_t safe_idx);
  inline size_t _Address2Index(VNode *node);
  status _DFSTraverse_RecursionBlock(size_t idx,
        bool *seen, status (*visit)(VNode *));
};


status CreateGraph(ALGraph *&G, size_t V, InfoType **VR);
status DestroyGraph(ALGraph *&G);
status RestoreFromFile(ALGraph *&G, const char *filename);
status SelectGraph(ALGraph *pool[], size_t &working, size_t target);


status VisitNode(VNode *node);

#endif
