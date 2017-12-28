#ifndef ALGRAPH_H_
#define ALGRAPH_H_

#define MAX_VERTEX_NUM  20
#define GRAPH_POOL_SIZE 10


typedef int InfoType;

typedef struct _VertexType {
  size_t  id;
  int     data;
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
private:

  AdjList vertices;
  int     vexnum;
  int     arcnum;

public:

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
  // status DFSTraverse(status visit(VNode &));
  // status BFSTraverse(status visit(void));
};


status CreateGraph(ALGraph *&G, size_t V, InfoType **VR);
status DestroyGraph(ALGraph *&G);


#endif
