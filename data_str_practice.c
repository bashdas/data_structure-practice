#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct arrNode {
    int t;
    char str[100];
} arrNode; //Array 구조체

typedef struct LkNode {
    int t;
    char str[100];
    struct LkNode* po;
} LkNode; //linked list 구조체

typedef struct MhNode {
    int t;
    char str[100];
} MhNode; //Max heap 구조체

typedef struct BstNode {
    int t;
    char str[100];
    struct BstNode* left;
    struct BstNode* right;
} BstNode; //BST 구조체

void Remove(int r, arrNode* arr, int inputnum); //Array pop(+sorting)
void nodelink(int r, LkNode* Node, LkNode** p); //Linked list push(+sorting)
void Maxheap_push(int r, MhNode* Node, int inputnum); //Max heap push
void Maxheap_pop(int* n, MhNode* Node); //Max heap pop
void Bst_push(int r, BstNode* Node, BstNode** firstP); //BST push
void Bst_pop(BstNode* Node, BstNode** firstP); //BST pop

int main(void) {
    int inputnum;
    printf("input: ");
    scanf("%d", &inputnum); //input(inputnum)

    double start1, start2, start3, start4, end1, end2, end3, end4;
    start1 = clock();
    //array part start
    arrNode arr[inputnum]; //Array 구조체 배열 선언
    for (int i = 0; i < inputnum; i++) {
        arr[i].t = rand() % 1000; //구조체 배열에 모두 priority 초기화
    }
    for (int r = 0; r < inputnum; r++) {
        Remove(r, arr, inputnum); //prioirty 에 따라 pop
    }
    //array part finish
    end1 = clock();

    printf("\n\n");
    start2 = clock();
    //Linked list part start
    LkNode link_node[inputnum + 1]; //구조체 배열 선언
    LkNode* first_node = &link_node[1]; //시작 노드를 가리키는 포인터
    LkNode** first_p = &first_node; //시작 노드를 가리키는 포인터의 포인터

    for (int i = 1; i <= inputnum; i++) {
        link_node[i].t = rand() % 1000; // 모든 노드에 priority 초기화
        link_node[i].po = &link_node[0]; //모든 노드의 포인트멤버에 node[0]의 주소
    }
    for (int l = 2; l <= inputnum; l++) {
        nodelink(l, link_node, first_p);
    } //insert & sorting

    LkNode* temp = first_node;
    for (int k = 1; k <= inputnum; k++) {
        printf("%d\n", temp->t);
        temp = temp->po;
    } // priority 값 print(pop)
    //Linked list part finish
    end2 = clock();
    printf("\n\n");
    start3 = clock();
    //Max heap part start
    MhNode Maxheap_Node[inputnum + 1]; //구조체 배열 선언
    int n = inputnum;
    for (int r = 1; r <= inputnum; r++) {
        Maxheap_push(r, Maxheap_Node, inputnum);
    } // insert
    for (int r = 1; r <= inputnum; r++) {
        Maxheap_pop(&n, Maxheap_Node);
    } // pop(print)
    //Max heap part finish
    end3 = clock();
    printf("\n\n");
    start4 = clock();
    //BST part start
    BstNode Bstarr[inputnum + 1];
    Bstarr[0].t = rand() % 1000; //채워두기만 하고 의미 X
    Bstarr[0].left = &Bstarr[0];
    Bstarr[0].right = &Bstarr[0]; //leaf node 들이 가리킬 노드의 멤버초기화
    Bstarr[1].t = rand() % 1000;
    Bstarr[1].left = &Bstarr[0];
    Bstarr[1].right = &Bstarr[0];

    BstNode* first = &Bstarr[1]; //시작노드의 주소
    BstNode** firstP = &first; //시작노드를 가리키는 포인터의 포인터
    for (int r = 2; r <= inputnum; r++) {
        Bst_push(r, Bstarr, firstP);
    } // insert
    for (int r = 0; r < inputnum; r++) {
        Bst_pop(Bstarr, firstP); // pop(print)
    }
    //BST part finish
    end4 = clock();
    printf("Running time\n");
    printf("Array : %f ms\n", end1 - start1);
    printf("Linked List : %f ms\n", end2 - start2);
    printf("Max heap : %f ms\n", end3 - start3);
    printf("BST : %f ms\n", end4 - start4); //output
}

void Remove(int r, arrNode* arr, int inputnum) { //Array pop(+sorting)
    int max = r;
    for (int k = r; k < inputnum; k++) {
        if (arr[k].t > arr[max].t) {
            max = k;
        }
    } //priority 가장 높은 값을 가진 노드 찾기
    printf("%d\n", arr[max].t); //priority 가장 높은 값 출력(pop)
    arrNode temp;
    temp = arr[r];
    arr[r] = arr[max];
    arr[max] = temp; //sorting
    return;
}

void nodelink(int r, LkNode* Node, LkNode** p) { //Linked list push(+sorting)
    LkNode* temp = *p;
    LkNode* tempParent; //temp 의 이전 노드에 접근하기 위함
    while (1) { //노드들의 대소비교 & 노드 연결
        if (Node[r].t < temp->t) { //새로운 노드가 list 의 노드보다 작을 때
            if             ((temp->po) == &Node[0]) {
                temp->po = &Node[r];
                break; //들어가려는 위치에 노드가 없을 때 insert, break
            }
            tempParent = temp;
            temp = temp->po;
        }
        else { //새로운 노드가 llist 의 노드보다 클 때
            if (temp == *p) {
                Node[r].po = temp;
                *p = &Node[r];
                break; //들어가려는 위치에 노드가 없을 때 insert, break
            }
            Node[r].po = temp;
            tempParent->po = &Node[r];
            break;
        }
    }
}

void Maxheap_push(int r, MhNode* Node, int inputnum) { //Max heap push
    Node[r].t = rand() % 1000; //priority 초기화
    int nodenum = r; //insert 위치
    MhNode temp = Node[nodenum];

    while ((nodenum != 1) && (Node[nodenum].t > Node[nodenum / 2].t)) {
        Node[nodenum] = Node[nodenum / 2];
        nodenum = nodenum / 2;
        Node[nodenum] = temp; //parent 보다 priority 가 더 높을 때 위치 교환
    }
}

void Maxheap_pop(int* n, MhNode* Node) { //Max heap pop
    int parent, child;
    MhNode item, temp;
    item = Node[1]; //return 할 node(priority 가 가장 높은 node)
    temp = Node[(*n)--];
    parent = 1;
    child = 2;
    while (child <= (*n)) {
        if ((child < *n) && (Node[child].t < Node[child + 1].t))
            child++; //기준이 되는 노드의 left,right 중 더 큰 노드 선택
        if (temp.t > Node[child].t)
            break; //맨 마지막 노드와 위에서 선택한 노드의 대소비교
        Node[parent] = Node[child];
        parent = child;
        child *= 2; //기준이 되는 노드 변경
    }
    Node[parent] = temp; //맨 마지막 노드의 위치를 찾아 insert
    printf("%d\n", item.t);
}

void Bst_push(int r, BstNode* Node, BstNode** firstP) { //BST push
    Node[r].t = rand() % 1000;
    Node[r].left = &Node[0];
    Node[r].right = &Node[0]; //leaf Node 들 모두 Node[0]을 가리키게 함
    BstNode* temp = &Node[1]; //root 의 주소를 temp 노드로
    while (1) { //새로운 노드가 들어갈 위치 찾고 insert
        if (Node[r].t < (temp->t)) { //새로운 노드보다 temp 노드가 더 클 때
            if ((temp->left) == &Node[0]) {
                temp->left = &Node[r];
                break; //들어가려는 위치에 노드가 없을 때 insert, break
            }
            temp = temp->left;
        }
        else if (Node[r].t >= (temp->t)) { //새로운 노드보다 temp 노드가 더 작을 때
            if ((temp->right) == &Node[0]) {
                temp->right = &Node[r];
                break; //들어가려는 위치에 노드가 없을 때 insert, break
            }
            temp = temp->right;
        }
    }
}

void Bst_pop(BstNode* Node, BstNode** firstP) {
    BstNode* temp = *firstP;
    BstNode* tempParent;
    if (temp->right == &Node[0]) {
        printf("%d\n", (*firstP)->t);
        if ((*firstP)->left != &Node[0])
            *firstP = (*firstP)->left; // root 의 left 가 존재할 때..
        return;
    } // root node 의 오른쪽 child 가 없을 때
    while (temp->right != &Node[0]) {
        tempParent = temp;
        temp = temp->right;
    }
    printf("%d\n", temp->t); //pop
    if (temp->left == &Node[0])
        tempParent->right = &Node[0];
    if (temp->left != &Node[0]) // one child(left)
        tempParent->right = temp->left;
}