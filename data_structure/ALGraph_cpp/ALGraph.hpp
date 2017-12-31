#ifndef ALGRAPH_H_
#define ALGRAPH_H_

#define MAX_VERTEX_NUM  20
#define GRAPH_POOL_SIZE 10


typedef int InfoType;

typedef struct _VertexType {
  int   id;
  int   data;
} VertexType;

typedef struct _ArcNode {
  int               adjvex;
  InfoType          info;
  struct _ArcNode  *nextarc;
} ArcNode;

typedef struct _VNode {
  VertexType  data;
  ArcNode    *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];


// typedef struct _ALGraph {
//   AdjList   vertices;
//   int       vexnum, arcnum;
//   // int       kind;
// } ALGraph;



class ALGraph {
public: // a very Pythonic `public` sign :P

  AdjList vertices;
  int     vexnum;
  int     arcnum;

public:

  ALGraph();
  ALGraph(size_t V, InfoType **VR);
  ~ALGraph(void);
  size_t LocateVex(int key);
  int GetVex(int key);
  status PutVex(int key, int value);
  VNode *FirstAdjVex(int key);
  VNode *NextAdjVex(int v, int w);
  status InsertVex(int data=0);
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
