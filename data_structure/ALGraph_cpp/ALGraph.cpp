
#include <iostream>

#include "configs.hpp"
#include "ALGraph.hpp"



/*
 *  函数名称：ALGraph（构造函数）
 *  函数参数：顶点数量 V ，用于初始化的邻接矩阵 VR
 *  函数功能：根据给定的 V 与 VR 创建图
 *  返回值：  初始化成功返回 ALGraph 对象，否则抛出 ERROR
 */
ALGraph::ALGraph(size_t V, InfoType **VR) {
  if (V == 0) {
    std::cout << "顶点数不能为零！" << std::endl;
    throw ERROR;
  }
  if (V > MAX_VERTEX_NUM) {
    std::cout << "顶点数目超过规定最大数目！" << std::endl;
    throw ERROR;
  }
  // 创建顶点信息
  vexnum = (int) V;
  for (size_t curr = 0; curr < vexnum; curr++) {
    vertices[curr].data.id = curr;  // NOTE: 从 0 开始编号
    vertices[curr].data.data = 233;
    vertices[curr].firstarc = nullptr;
  }
  // 创建弧信息
  for (size_t row = 0; row < vexnum; row++) {
    for (size_t col = 0; col < vexnum; col++) {
      if (VR[row][col] != 0) {  // row 与 col 之间有边
        this->InsertArc(row, col);
        arcnum++;
      }
    }
  }
} // Constructor


/*
 *  函数名称：~ALGraph（析构函数）
 *  函数参数：无
 *  函数功能：销毁图
 *  返回值：  无
 */
ALGraph::~ALGraph(void) {
  // 遍历每个顶点
  for (size_t vex = 0; vex < vexnum; vex++) {
    // 释放其每条弧所占用的空间
    ArcNode *curr = vertices[vex].firstarc;
    ArcNode *arc_to_free = curr;
    while (arc_to_free != nullptr) {
      curr = curr->nextarc;
      delete arc_to_free;
      arc_to_free = curr;
    }
  }
} // Destructor


/*
 *  函数名称：CreateGraph
 *  函数参数：图对象的引用 G，顶点数量 V ，用于初始化的邻接矩阵 VR
 *  函数功能：根据给定的 V 与 VR 在 G 上创建图
 *  返回值：  初始化成功返回 OK，否则返回 ERROR
 */
status
CreateGraph(ALGraph *&G, size_t V, InfoType **VR) {
  try {
    G = new ALGraph(V, VR);
  } catch (status e) {
    return e;
  }
  return OK;
}


/*
 *  函数名称：DestroyGraph
 *  函数参数：图对象的引用 G
 *  函数功能：销毁图
 *  返回值：  销毁成功返回 OK，否则返回 ERROR
 */
status
DestroyGraph(ALGraph *&G) {
  if (G == nullptr) { return ERROR; }
  delete G;   // TODO: 现在还不是很清楚怎么 catch 不正常的 delete。。
  G = nullptr;
  return OK;
}


/*
 *  函数名称：LocateVex
 *  函数参数：所求顶点的唯一标示域 key
 *  函数功能：返回所求顶点在 ALGraph.vertices 顶点数组中的位序
 *  返回值：  查找成功返回位序值，查找失败返回 0
 */
size_t
ALGraph::LocateVex(int key) {
  if (key >= vexnum || key < 0) { return 0; }
  return (size_t) (key + 1);
} // LocateVex


/*
 *  函数名称：GetVex
 *  函数参数：要访问顶点的唯一标示域 key
 *  函数功能：返回所求顶点的值
 *  返回值：  所求顶点的的值
 */
int
ALGraph::GetVex(int key) {
  size_t vex = this->LocateVex(key);
  if (vex == 0) {
    std::cout << "未找到满足要求的顶点！" << std::endl;
    return 0;
  }
  return vertices[vex - 1].data.data;
} // GetVex


/*
 *  函数名称：PutVex
 *  函数参数：要赋值顶点的唯一标示域 key，要赋的值 val
 *  函数功能：给指定顶点赋值
 *  返回值：  操作成功返回 OK，否则返回 ERROR
 */
status
ALGraph::PutVex(int key, int val) {
  size_t vex = this->LocateVex(key);
  if (vex == 0) {
    std::cout << "未找到满足要求的顶点！" << std::endl;
    return ERROR;
  }
  vertices[vex - 1].data.data = val;
  return OK;
} // PutVex


/*
 *  函数名称：FirstAdjVex
 *  函数参数：弧尾的标示域 key
 *  函数功能：返回指定顶点的第一个邻接顶点
 *  返回值：  操作成功返回所求顶点的地址，否则返回空指针
 */
VNode *
ALGraph::FirstAdjVex(int key) {
  size_t vex = this->LocateVex(key);
  if (vex == 0) {
    std::cout << "未找到满足要求的顶点！" << std::endl;
    return nullptr;
  }
  return &vertices[ vertices[vex - 1].firstarc->adjvex ];
} // FirstAdjVex


/*
 *  函数名称：NextAdjVex
 *  函数参数：弧尾标示域 v，弧头标示域 w
 *  函数功能：获取 v 相对于 w 的下一个邻接顶点
 *  返回值：  操作成功返回所求顶点的地址，否则返回空指针
 */
VNode *
ALGraph::NextAdjVex(int v, int w) {
  size_t v_vex = this->LocateVex(v);
  size_t w_vex = this->LocateVex(w);
  if (v_vex == 0 || w_vex == 0) {
    std::cout << "未找到满足要求的顶点！" << std::endl;
    return nullptr;
  }
  if (v_vex == w_vex) {
    std::cout << "不存在弧 <v, w>！" << std::endl;
    return nullptr;
  }
  v_vex--; w_vex--;
  // 遍历查找弧 <v, w>
  ArcNode *arc = vertices[v_vex].firstarc;
  while (arc != nullptr) {
    if (arc->adjvex == w_vex) { break; }
    else { arc = arc->nextarc; }
  }
  if (arc == nullptr) { // 未找到满足条件 <v, w> 的弧
    std::cout << "不存在弧 <v, w>！" << std::endl;
    return nullptr;
  }
  if ((arc = arc->nextarc) == nullptr) {
    std::cout << "弧 <v, w> 已经是邻接表中最后一条弧了！" << std::endl;
    return nullptr;
  }  // 链表中没有下一条弧
  return &vertices[arc->adjvex];
}


/*
 *  函数名称：InsertVex
 *  函数参数：新插入节点的数据 data
 *  函数功能：在图中插入新的节点，并令其数据域为 data
 *  返回值：  操作成功返回 OK，否则返回 ERROR
 */
status
ALGraph::InsertVex(int data) {
  if (vexnum == MAX_VERTEX_NUM) {
    std::cout << "顶点集已满！" << std::endl;
    return ERROR;
  }
  vertices[vexnum].data.id = vexnum;  // vexnum 为栈顶
  vertices[vexnum].data.data = data;
  vexnum++;
  return OK;
}


/*
 *  函数名称：DeleteVex
 *  函数参数：要删除节点的标示域 key
 *  函数功能：从图中删除最顶节点及所有与其相关的弧
 *  返回值：  操作成功返回 OK，否则返回 ERROR
 */
status
ALGraph::DeleteVex(int key) {
  size_t vex = this->LocateVex(key);
  if (vex == 0) {
    std::cout << "未找到满足要求的顶点！" << std::endl;
    return ERROR;
  }
  vex--;  // vertices[vex] 为要删除的顶点
  // 删除所有以 vex 为弧头的边
  for (size_t other = 0; other < vexnum; other++) {
    if (other == vex) { continue; } // 之后再处理 vex ，先跳过
    ArcNode *arc = vertices[other].firstarc;
    // - firstarc 弧头为 vex
    while (arc->adjvex == vex) {
      vertices[other].firstarc = arc->nextarc;
      delete arc;
      arc = vertices[other].firstarc;
    }
    // - 链表中间某条弧的弧头为 vex || 链表尾的弧头为 vex
    for (; arc->nextarc != nullptr; arc = arc->nextarc) {
      if (arc->nextarc->adjvex == vex) {
        ArcNode *arc_to_free = arc->nextarc;
        arc->nextarc = arc_to_free->nextarc;
        delete arc_to_free;
      }
    }
  }
  // 删除 vertices[vex]
  // - 删除以 vex 为弧尾的弧
  ArcNode *curr_arc = vertices[vex].firstarc;
  ArcNode *arc_to_free = curr_arc;
  while (arc_to_free != nullptr) {
    curr_arc = curr_arc->nextarc;
    delete arc_to_free;
    arc_to_free = curr_arc;
  }
  // - 从 vertices 中删除 vex
  vexnum--; // 注册改动
  for (; vex < vexnum; vex++) {
    vertices[vex] = vertices[vex + 1];  // 前移
  }
  return OK;
}


/*
 *  函数名称：InsertArc
 *  函数参数：弧尾标示域 v，弧头标示域 w，权重 weight （默认值为1）
 *  函数功能：在图中插入弧 <v, w>
 *  返回值：  操作成功返回 OK，否则返回 ERROR
 */
status
ALGraph::InsertArc(int v, int w, InfoType weight) {
  size_t v_vex = this->LocateVex(v);
  size_t w_vex = this->LocateVex(w);
  if (v_vex == 0 || w_vex == 0) {
    std::cout << "输入数据格式不合法！" << std::endl;
    return ERROR;
  }
  v_vex--; w_vex--;
  // 创建新弧空间
  ArcNode *new_arc = new ArcNode;
  new_arc->adjvex = (int) w_vex;
  new_arc->info = weight;
  new_arc->nextarc = nullptr;
  // 获取弧链表尾地址
  ArcNode *tail = vertices[v].firstarc;
  if (tail != nullptr) {  // - 不是该顶点的第一个弧
    for (; tail->nextarc != nullptr; tail = tail->nextarc) ;
    tail->nextarc = new_arc;
  } else {  // - 是该顶点的第一个弧
    vertices[v].firstarc = new_arc;
  }
  arcnum++;
  return OK;
} // InsertArc


/*
 *  函数名称：DeleteArc
 *  函数参数：弧尾标示域 v，弧头标示域 w
 *  函数功能：在图中删除弧 <v, w>
 *  返回值：  操作成功返回 OK，否则返回 ERROR
 */
status
ALGraph::DeleteArc(int v, int w) {
  size_t v_vex = this->LocateVex(v);
  size_t w_vex = this->LocateVex(w);
  if (v_vex == 0 || w_vex == 0) {
    std::cout << "未找到满足条件的顶点！" << std::endl;
    return ERROR;
  }
  v_vex--; w_vex--;
  // 遍历搜索 <v, w>
  ArcNode *arc = vertices[v_vex].firstarc;
  // - 要删除的是 v 的第一个弧
  if (arc->adjvex == w_vex) { // NOTE: 不考虑多重图情况
    vertices[v_vex].firstarc = arc->nextarc;
    delete arc;
    return OK;
  }
  // - 要删除的不是 v 的第一个弧
  for (; arc->nextarc && arc->nextarc->adjvex == w_vex; arc = arc->nextarc) ;
  if (arc->nextarc == nullptr) {
    std::cout << "未找到满足条件的弧！" << std::endl;
    return ERROR;
  }
  ArcNode *arc_to_free = arc->nextarc;
  arc->nextarc = arc_to_free->nextarc;
  delete arc_to_free;
  return OK;
}


// status
// ALGraph::_DFSTraverse_ConnectedComponent(
//         bool *&seen, size_t start, status visit(VNode &)) {
//   while (true) {
//
//   }
// }
