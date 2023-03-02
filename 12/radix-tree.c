#pragma once
#include <stdlib.h>
#include <stdio.h>

// 内存页大小为4kB
#define MEMPAGE 4096  // 4096个字节

// 初始化内存池的长度
#define INIT_POOL_SIZE (32 * MEMPAGE)

// 初始化备用节点的长度
#define INIT_FREE_SIZE (INIT_POOL_SIZE / 2)

// 初始化备用节点的个数
#define INIT_NODE_NUM (16*32)

#define RADIX_INSERT_VALUE_OCCUPY -1  // 该节点已被占用
#define RADIX_INSERT_VALUE_SAME -2   // 插入了相同的值
#define RADIX_DELETE_ERROR -3   // 删除错误
typedef unsigned int ptr_t;
typedef unsigned int uint32;
#define BITS 2
// 树的高度是固定的
const int radix_tree_height = sizeof (ptr_t) * 8 / BITS;

// 返回key中由pos指定的值，pos = 0,1...16
#define CHECK_BITS(key, pos) ((unsigned int) key >> (sizeof(ptr_t) * 8 - (pos + 1) * BITS)) << (sizeof(ptr_t) * 8 - BITS)

// 基数树的树节点
typedef struct radix_node_t radix_node_t;
struct radix_node_t {
    radix_node_t* parent;
    radix_node_t* child[4];
    ptr_t value;
};

// 使用内存池是为了减少建立节点时重新申请内存空间的时间
// 内存池的描述结构，放在内存池的前半段
typedef struct radix_pool {
    // 内存池是双向循环链表中的一个节点
    struct radix_pool* next;
    struct radix_pool* prev;

    // 已分配内存，但还未使用的内存首地址
    char* start;
    // 已分配内存，但还未使用的内存长度
    size_t size;
} radix_pool, *pool_t;

//基数树的结构
typedef struct radix_tree {
    radix_node_t* root ;  // 根节点
    pool_t pool;  // 正在使用的内存池的地址
    radix_node_t* free;  // 储存已分配，但不在树中的节点
} radix_tree_t;

// 创建管理结构
radix_tree_t* radix_tree_create() {
    int i;
    //  为基数树的管理结构分配存储空间
    radix_tree_t* tree = (radix_tree_t*) malloc(sizeof(radix_tree_t));
    if(!tree) return NULL;

    //  为内存池分配物理页面，用来存放树节点
    char* p = (char*) malloc(INIT_POOL_SIZE);
    if (!p) return NULL;
    // 初始化该内存池的管理结构
    ((pool_t) p) -> next = (pool_t)p;
    ((pool_t) p) -> prev = (pool_t)p;

    // 根节点存放进内存管理结构的后面
    radix_node_t* ns;
    ns = (radix_node_t*)((char*) p + sizeof(radix_pool));
    ns[0].parent = NULL;
    ns[0].child[0] = NULL;
    ns[0].child[1] = NULL;
    ns[0].child[2] = NULL;
    ns[0].child[3] = NULL;
    ns[0].value = NULL;

    // 根据INIT_NODE_NUM把树节点组织起来
    for (i = 1; i < INIT_NODE_NUM; ++i) {
        ns[i].parent = &ns[i + 1];
    }
    // 接着对内存池的start和size属性进行设置
    ((pool_t)p) -> start = (char*)ns + sizeof(radix_node_t) * INIT_NODE_NUM;
    ((pool_t)p) -> size = INIT_POOL_SIZE - sizeof(radix_pool) - sizeof(radix_node_t) * INIT_NODE_NUM;

    // 最后对树的管理结构进行设置
    tree -> pool = (pool_t)p;
    tree -> root = ns;
    tree -> free = &ns[1];
}
// 内存池扩大函数
pool_t get_new_pool(radix_tree_t* t, size_t num) {
    if (num == -1) num = INIT_POOL_SIZE;
    char* pool = (char*)malloc(num);
    if (pool == NULL) return NULL;
    ((pool_t)pool) -> start = (char*)pool - sizeof(radix_pool);
    ((pool_t)pool) -> size = num - sizeof(radix_pool);
    ((pool_t)pool) -> next = t -> pool -> next;
    ((pool_t)pool) -> prev = t -> pool;
    t -> pool -> next -> prev = ((pool_t)pool);
    t -> pool -> next = ((pool_t)pool);
    t-> pool = (pool_t)pool;
    
}

// 创建一个节点，从内存池中取出可用节点
radix_node_t* radix_node_alloc(radix_tree_t* t) {
    radix_node_t* node;
    // 从free中取出节点
    if (t -> free != NULL) {
        node = t -> free;
        t -> free = node -> parent;
    } else {
        // 从内存池中寻找可使用的内存
        if (t -> pool ->size < sizeof(radix_node_t)) {
            get_new_pool(t, -1);
        }
        node = (radix_node_t*)t -> pool -> start;
        t -> pool -> start += sizeof(radix_node_t);
        t -> pool -> size -= sizeof(radix_node_t);
    }
    node -> child[0] = NULL;
    node -> child[1] = NULL;
    node -> child[2] = NULL;
    node -> child[3] = NULL;
    node -> parent = NULL;
    node -> value = NULL;
    return node;
}

// 插入
int radix_tree_insert(radix_tree_t* t, uint32 key, ptr_t value) {
    radix_node_t* node, *child;
    node = t -> root;
    int temp_key;
    for (int i = 0; i < radix_tree_height; ++i) {
        temp_key = CHECK_BITS(key, i);
        // 如果该层Key所对应的树节点不存在，那么就要从内存池中申请一个
        if (!node->child[temp_key]) {
            // 从内存池中申请一个空闲的节点
            child = radix_node_alloc(t);
            if (!child) return NULL;
            child -> parent = node;
            node -> child[temp_key] = child;
            node = node -> child[temp_key];
        } else {
            node = node -> child[temp_key];
        }
    }
    if (node -> value == value) return RADIX_INSERT_VALUE_SAME;
    if (node -> value != NULL) return RADIX_INSERT_VALUE_OCCUPY;
    node -> value = value;
    return 0;
}

// 由于插入时会创建很多节点，为了提高删除效率，这里只会对最底层的节点进行删除
// 然后重置属性free, 以及把最底层节点链接到空闲链表中去
int radix_tree_delete(radix_tree_t* t, uint32 key) {
    radix_node_t* node = t -> root;
    if (node == NULL) return RADIX_DELETE_ERROR;
    radix_node_t* par;
    int i = 0, temp = 0;
    do {
        temp = CHECK_BITS(key, i);
        node = node -> child[temp];
    } while (node && i < radix_tree_height);
    // node 为存储value的节点
    par = node -> parent;
    par -> child[temp] = NULL;
}

void radix_print(radix_node_t* node) {
    if (node == NULL) return;
    if (node -> value != NULL) {
        print("%x\n", node -> value);
    }
    radix_print(node -> child[0]);
    radix_print(node -> child[1]);
    radix_print(node -> child[2]);
    radix_print(node -> child[3]);
}

