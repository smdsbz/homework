
#include <iostream>
#include <vector>
#include <fstream>

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
    // std::cout << "顶点数不能为零！" << std::endl;
    throw ERROR;
  }
  if (V > MAX_VERTEX_NUM) {
    // std::cout << "顶点数目超过规定最大数目！" << std::endl;
    throw ERROR;
  }
  // 创建顶点信息
  vexnum = (int) V; // 根据教材 P163 定义，vexnum 为 int 型
  for (size_t curr = 0; curr < vexnum; curr++) {
    vertices[curr].data.id = (int) curr;  // NOTE: ID 从 0 开始编号
                                          //       溢出绕回无影响
    vertices[curr].data.data = 233;
    vertices[curr].firstarc = nullptr;
  }
  // 创建弧信息
  for (size_t row = 0; row < vexnum; row++) {
    for (size_t col = 0; col < vexnum; col++) {
      if (VR[row][col] != 0) {  // row 与 col 之间有边
        InsertArc(row, col);
      }
    }
  }
} // Constructor


/*
 *  函数名称：ALGraph（构造函数）
 *  函数参数：无
 *  函数功能：创建空图
 *  返回值：  无
 */
ALGraph::ALGraph() {
  // double-check
  vexnum = 0;
  arcnum = 0;
}


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
  if (G != nullptr) {
    // std::cout << "已经有挂载的图了！" << std::endl;
    return ERROR;
  }
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
  size_t ret = 0;
  for (; ret < vexnum; ret++) {
    if (vertices[ret].data.id == key) { break; }
  }
  if (ret == vexnum) { return 0; }
  return (size_t) (ret + 1);
} // LocateVex


/*
 *  函数名称：_Index2Key
 *  函数参数：顶点的内部下标
 *  函数功能：获得该顶点的 key 值
 *  返回值：  返回顶点的 key 值
 */
inline int
ALGraph::_Index2Key(size_t safe_idx) {
  return vertices[safe_idx].data.id;
}


/*
 *  函数名称：GetVex
 *  函数参数：要访问顶点的唯一标示域 key
 *  函数功能：返回所求顶点的值
 *  返回值：  所求顶点的的值
 */
int
ALGraph::GetVex(int key) {
  size_t vex = LocateVex(key);
  if (vex == 0) {
    // std::cout << "未找到满足要求的顶点！" << std::endl;
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
  size_t vex = LocateVex(key);
  if (vex == 0) {
    // std::cout << "未找到满足要求的顶点！" << std::endl;
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
  size_t vex = LocateVex(key);
  if (vex == 0) {
    // std::cout << "未找到满足要求的顶点！" << std::endl;
    return nullptr;
  }
  // 该顶点邻接表为空
  if (vertices[vex - 1].firstarc == nullptr) {
    // std::cout << "没有以该顶点为弧尾的弧！" << std::endl;
    return nullptr;
  }
  return &vertices[ LocateVex(vertices[vex - 1].firstarc->adjvex) - 1 ];
} // FirstAdjVex


/*
 *  函数名称：NextAdjVex
 *  函数参数：弧尾标示域 v，弧头标示域 w
 *  函数功能：获取 v 相对于 w 的下一个邻接顶点
 *  返回值：  操作成功返回所求顶点的地址，否则返回空指针
 */
VNode *
ALGraph::NextAdjVex(int v, int w) {
  size_t v_vex = LocateVex(v);
  size_t w_vex = LocateVex(w);
  if (v_vex == 0 || w_vex == 0) {
    // std::cout << "未找到满足要求的顶点！" << std::endl;
    return nullptr;
  }
  if (v_vex == w_vex) {
    // std::cout << "不存在弧 <v, w>！" << std::endl;
    return nullptr;
  }
  v_vex--; w_vex--;
  // 遍历查找弧 <v, w>
  ArcNode *arc = vertices[v_vex].firstarc;
  while (arc != nullptr) {
    if (LocateVex(arc->adjvex) - 1 == w_vex) { break; }
    else { arc = arc->nextarc; }
  }
  if (arc == nullptr) { // 未找到满足条件 <v, w> 的弧
    // std::cout << "不存在弧 <v, w>！" << std::endl;
    return nullptr;
  }
  if ((arc = arc->nextarc) == nullptr) {
    // std::cout << "弧 <v, w> 已经是邻接表中最后一条弧了！" << std::endl;
    return nullptr;
  }  // 链表中没有下一条弧
  return &vertices[LocateVex(arc->adjvex) - 1];
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
    // std::cout << "顶点集已满！" << std::endl;
    return ERROR;
  }
  // HACK: 借用数据库中 AUTOINCREMENT 概念
  //       由于顶点集中最后一个元素一定是最晚添加进来的，故 VNode.data.id 一定唯一
  if (vexnum == 0) {  // - 图中顶点被全部删除后，第一个被添加进来的顶点
    vertices[vexnum].data.id = 0;
  } else {
    vertices[vexnum].data.id = vertices[vexnum - 1].data.id + 1;
  }
  vertices[vexnum].data.data = data;
  vertices[vexnum].firstarc = nullptr;
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
  size_t vex = LocateVex(key);
  if (vex == 0) {
    // std::cout << "未找到满足要求的顶点！" << std::endl;
    return ERROR;
  }
  vex--;  // vertices[vex] 为要删除的顶点
  // 删除所有以 vex 为弧头的边
  for (size_t other = 0; other < vexnum; other++) {
    if (other == vex) { continue; } // 之后再处理 vex ，先跳过
    ArcNode *arc = vertices[other].firstarc;
    // - firstarc 弧头为 vex
    while (arc && LocateVex(arc->adjvex) - 1 == vex) {
      vertices[other].firstarc = arc->nextarc;
      delete arc;
      arcnum--;
      arc = vertices[other].firstarc;
    }
    // - 链表中间某条弧的弧头为 vex || 链表尾的弧头为 vex
    for (; arc && arc->nextarc != nullptr; arc = arc->nextarc) {
      if (LocateVex(arc->nextarc->adjvex) - 1 == vex) {
        ArcNode *arc_to_free = arc->nextarc;
        arc->nextarc = arc_to_free->nextarc;
        delete arc_to_free;
        arcnum--;
      }
    }
  } // for other than vex
  // 删除 vertices[vex]
  // - 删除以 vex 为弧尾的弧
  ArcNode *curr_arc = vertices[vex].firstarc;
  ArcNode *arc_to_free = curr_arc;
  while (arc_to_free != nullptr) {
    curr_arc = curr_arc->nextarc;
    delete arc_to_free;
    arcnum--;
    arc_to_free = curr_arc;
  }
  // - 从 vertices 中删除 vex
  vexnum--; // 注册改动
  for (; vex < vexnum; vex++) {
    vertices[vex] = vertices[vex + 1];  // 前移
  }
  // 提示信息
  if (vexnum == 0) {
    // std::cout << "图中现在已经没有顶点了！" << std::endl;
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
  size_t v_vex = LocateVex(v);
  size_t w_vex = LocateVex(w);
  if (v_vex == 0 || w_vex == 0) {
    // std::cout << "输入数据格式不合法！" << std::endl;
    return ERROR;
  }
  v_vex--; w_vex--;
  // 创建新弧空间
  ArcNode *new_arc = new ArcNode;
  new_arc->adjvex = w;  // NOTE: 考虑到后面可能涉及到顶点的删除，
                        //       这里 **必须** 存储顶点的标示域
  new_arc->info = weight;
  new_arc->nextarc = nullptr;
  // 获取弧链表尾地址
  // NOTE: 新弧在邻接表中位置并不重要
  ArcNode *tail = vertices[v_vex].firstarc;
  if (tail != nullptr) {  // - 不是该顶点的第一个弧
    // -- 检查弧是否已经存在
    if (LocateVex(tail->adjvex) - 1 == w_vex) {
      // std::cout << "弧 <v, w> 已经存在！" << std::endl;
      delete new_arc;
      return ERROR;
    }
    for (; tail->nextarc != nullptr; tail = tail->nextarc) {
      // -- 检查弧是否已经存在
      if (LocateVex(tail->nextarc->adjvex) - 1 == w_vex) {
        // std::cout << "弧 <v, w> 已经存在！" << std::endl;
        delete new_arc;
        return ERROR;
      }
    }
    tail->nextarc = new_arc;
  } else {  // - 是该顶点的第一个弧
    vertices[v_vex].firstarc = new_arc;
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
  size_t v_vex = LocateVex(v);
  size_t w_vex = LocateVex(w);
  if (v_vex == 0 || w_vex == 0) {
    // std::cout << "未找到满足条件的顶点！" << std::endl;
    return ERROR;
  }
  v_vex--; w_vex--;
  // 遍历搜索 <v, w>
  ArcNode *arc = vertices[v_vex].firstarc;
  // - 要删除的是 v 的第一个弧
  if (LocateVex(arc->adjvex) - 1 == w_vex) { // NOTE: 不考虑多重图情况
    vertices[v_vex].firstarc = arc->nextarc;
    delete arc;
    return OK;
  }
  // - 要删除的不是 v 的第一个弧
  for (; arc->nextarc
            && LocateVex(arc->nextarc->adjvex) - 1 == w_vex;
         arc = arc->nextarc) ;
  if (arc->nextarc == nullptr) {
    // std::cout << "未找到满足条件的弧！" << std::endl;
    return ERROR;
  }
  ArcNode *arc_to_free = arc->nextarc;
  arc->nextarc = arc_to_free->nextarc;
  delete arc_to_free;
  arcnum--;
  return OK;
}


/*
 *  函数名称：VisitNode
 *  函数参数：顶点 node 的地址
 *  函数功能：对 node 执行访问操作，即输出其数据信息
 *  返回值：  访问成功返回 OK，否则返回 ERROR
 */
status
VisitNode(VNode *node) {
  if (node == nullptr) { return ERROR; }
  std::cout << "<VNode @ " << node << " ID = " << node->data.id
            << " data = " << node->data.data << ">" << std::endl;
  return OK;
}


/*
 *  函数名称：_Address2Index
 *  函数参数：顶点 node 的地址
 *  函数功能：获取 node 在 ALGraph 中的下标
 *  返回值：  node 在 ALGraph.vertices 中的下标
 */
inline size_t
ALGraph::_Address2Index(VNode *node) {
  if (node == nullptr) { throw ERROR; }
  return (size_t) (node - vertices);
}


/*
 *  函数名称：_DFSTraverse_RecursionBlock
 *  函数参数：当前顶点的下标 index，标志数组 seen，访问应用方法 visit
 *  函数功能：对当前顶点调用 visit，对与当前顶点邻接的更深层的顶点递归调用自身
 *  返回值：  访问均成功返回 OK，否则返回 ERROR
 */
status
ALGraph::_DFSTraverse_RecursionBlock(size_t index, bool *seen,
      status (*visit)(VNode *)) {
  seen[index] = true;
  if (visit(&vertices[index]) != OK) { return ERROR; }
  VNode *deeper_node = FirstAdjVex(_Index2Key(index));
  while (deeper_node != nullptr) {
    if (!seen[_Address2Index(deeper_node)]) {
      _DFSTraverse_RecursionBlock(_Address2Index(deeper_node), seen, visit);
    }
    deeper_node = NextAdjVex(_Index2Key(index),
                             _Index2Key(_Address2Index(deeper_node)));
  }
  return OK;
}


/*
 *  函数名称：DFSTraverse
 *  函数参数：访问函数 visit
 *  函数功能：应用深度优先搜索方式遍历图，并对其中的每一个顶点调用 visit
 *  返回值：  若遍历成功返回 OK，若遍历过程中 visit 调用失败则返回 ERROR
 */
status
ALGraph::DFSTraverse(status (*visit)(VNode *)) {
  bool *seen = new bool[vexnum];
  for (size_t vex = 0; vex < vexnum; vex++) { seen[vex] = false; }
  for (size_t index = 0; index < vexnum; index++) {
    if (!seen[index]) {
      if (_DFSTraverse_RecursionBlock(index, seen, visit) != OK) {
        return ERROR;
      } // visit
    } // if enter recursion
  } // outer for
  return OK;
}


/*
 *  函数名称：BFSTraverse
 *  函数参数：访问函数 visit
 *  函数功能：应用广度优先搜索方式遍历图，并对其中的每一个顶点调用 visit
 *  返回值：  若遍历成功返回 OK，若遍历过程中 visit 调用失败则返回 ERROR
 */
status
ALGraph::BFSTraverse(status (*visit)(VNode *)) {
  bool *seen = new bool[vexnum];  // 标志数组
  for (size_t vex = 0; vex < vexnum; vex++) { seen[vex] = false; }
  std::vector<size_t> outskirt; // 用于存储最外层顶点的队列
  for (size_t index = 0; index < vexnum; index++) {
    if (!seen[index]) {
      seen[index] = true;
      if (visit(&vertices[index]) != OK) { return ERROR; }
      outskirt.insert(outskirt.begin(), index); // 当前顶点入队列
      while (!outskirt.empty()) {
        // 出队列，准备以此为中心进行扩展
        size_t center = outskirt.back();
        outskirt.pop_back();
        VNode *outer = FirstAdjVex(_Index2Key(center)); // center 外层中某个元素
        while (outer != nullptr) {
          if (!seen[_Address2Index(outer)]) {
            // 访问其周边的顶点，并使其入队列，成为新的边界
            seen[_Address2Index(outer)] = true;
            if (visit(outer) != OK) { return ERROR; }
            outskirt.insert(outskirt.begin(), _Address2Index(outer));
          }
          outer = NextAdjVex(_Index2Key(center),
                             _Index2Key(_Address2Index(outer)));
        } // while center has outskirt
      } // while same connected component
    }
  } // while BFS not done
  return OK;
}


/*
 *  函数名称：CommitToFile
 *  函数参数：文件名 filename，覆盖写标志 overwrite
 *  函数功能：将图保存到文件中，若有重名文件且 overwrite 为 true，则覆盖现有文件
 *  返回值：  保存成功返回 OK，否则返回 ERROR
 */
status
ALGraph::CommitToFile(const char*filename, bool overwrite) {
  std::ofstream outfile;
  std::fstream::openmode mode = std::fstream::out | std::fstream::binary;
  if (overwrite) { mode |= std::fstream::trunc; }
  outfile.open(filename, mode);
  if (outfile.is_open()) {
    char *buffer;
    // 表头信息
    buffer = (char *) &vexnum;
    outfile.write(buffer, sizeof(int) * 1);   // 确定要存储的顶点的数量
    buffer = (char *) &arcnum;
    outfile.write(buffer, sizeof(int) * 1);   // 没什么用，要不用来检查文件完整性吧？
    // 顶点信息写入文件
    for (size_t vex = 0; vex < vexnum; vex++) {
      // NOTE: 顶点 ID 也写入
      buffer = (char *) &vertices[vex].data;
      outfile.write(buffer, sizeof(VertexType) * 1);
    }
    // 邻接链表信息，用三元组的方式存储
    for (size_t vex = 0; vex < vexnum; vex++) {
      for (ArcNode *arc = vertices[vex].firstarc; arc; arc = arc->nextarc) {
        buffer = (char *) &vertices[vex].data.id;
        outfile.write(buffer, sizeof(int) * 1); // 弧尾 ID
        buffer = (char *) &arc->adjvex;
        outfile.write(buffer, sizeof(int) * 1); // 弧头 ID
        buffer = (char *) &arc->info;
        outfile.write(buffer, sizeof(InfoType) * 1);  // 弧权重
      } // for each arc adjacent to vertex
    } // for each vertex
  } else { return ERROR; }
  outfile.close();
  return OK;
}


/*
 *  函数名称：RestoreFromFile
 *  函数参数：图挂载点 G，文件名 filename
 *  函数功能：从文件中恢复图
 *  返回值：  保存读取返回 OK，否则返回 ERROR
 */
status
RestoreFromFile(ALGraph *&G, const char *filename) {
  if (G != nullptr) {
    std::cout << "已有挂载的图！" << std::endl;
    return ERROR;
  }
  std::ifstream infile;
  std::fstream::openmode mode = std::fstream::in | std::fstream::binary;
  infile.open(filename, mode);
  if (infile.is_open()) {
    G = new ALGraph();  // 创建空图
    // 提取文件大小信息
    size_t filesize = 0;
    infile.seekg(0, infile.end);
    filesize = infile.tellg();  // NOTE: no assertion
    infile.seekg(0, infile.beg);
    // 读取 ALGraph.vexnum
    int vexnum;
    infile.read((char *) &vexnum, sizeof(int) * 1);
    // 暂存文件中的 ALGraph.arcnum，用作之后检查文件完整性
    int arcnum;
    infile.read((char *) &arcnum, sizeof(int) * 1);
    filesize -= sizeof(int) * 2;
    // 读取 ALGraph.vertices
    VertexType node;
    for (size_t vex = 0; vex < vexnum; vex++) {
      infile.read((char *) &node, sizeof(VertexType) * 1);
      // NOTE: 重新分配 ID，分配策略与构造函数一样（从 0 开始）
      G->InsertVex(node.data);
      filesize -= sizeof(VertexType) * 1;
    }
    // 读取弧
    int vec[2] = { 0 }; InfoType weight;
    for (; filesize != 0;
          filesize -= (sizeof(int) * 2) + (sizeof(InfoType) * 1)) {
      infile.read((char *) vec, sizeof(int) * 2);
      infile.read((char *) &weight, sizeof(InfoType) * 1);
      G->InsertArc(vec[0], vec[1], weight);
    }
    // 文件完整性检查
    if ((vexnum != G->vexnum) || (arcnum != G->arcnum)) {
      G->DFSTraverse(VisitNode);
      delete G;
      return ERROR;
    }
  } else { return ERROR; }
  infile.close();
  return OK;
}


/*
 *  函数名称：SelectGraph
 *  函数参数：图池 pool，工作图在池中的位置 working，要切换到的位置 target
 *  函数功能：切换当前工作表 pool[working] 至 pool[target]
 *  返回值：  操作成功返回 OK，否则返回 ERROR
 */
status
SelectGraph(ALGraph *pool[], size_t &working, size_t target) {
  if (target > MAX_VERTEX_NUM) { return ERROR; }
  working = target - 1;
  return OK;
}
