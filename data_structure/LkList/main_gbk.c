/*
 *  ������ʽ�洢�ṹ�����Ա�ʵ��
 *    ---- by U201610136 ������ У�ʽ���1601��
 */



#include <stdio.h>
#include <stdlib.h>

#define DEBUG

/* Page 10 */
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       -3  // ������������ֵ������ ListLength() Ϊ
                        // �ձ�ʱ�ķ���ֵ
#define INFEASABLE  -1
#define OVERFLOW    -2

/* ����Ԫ�����Ͷ��� */
typedef int status;
typedef int ElemType; // HACK: ͷ�ڵ�������ڴ�ű�

#define LIST_POOL_SIZE  20

/* Page 28 */
typedef struct _LNode {
  ElemType        data; // ������ͷ�ڵ��ű���
  struct _LNode  *next; // ��һ���ڵ�
} LNode;
typedef LNode *LkList;

/* Page 19 */
status IntiaList(LkList *L);
status DestroyList(LkList *L);
status ClearList(LkList *L);
status ListEmpty(LkList L);
int ListLength(LkList L);
status GetElem(LkList L, int idx, ElemType *rst);
status ListTrabverse(LkList L);
status ListInsert(LkList L, int i, ElemType e);
status ListDelete(LkList L, int i, ElemType *e);
int LocateElem(LkList L, ElemType e);
status PriorElem(LkList L, ElemType cur, ElemType *pre_e);
status NextElem(LkList L, ElemType cur, ElemType *next_e);
status SaveList(FILE *fp, LkList L);
status LoadList(FILE *fp, LkList *L);
status SelectList(LkList *L, LkList pool[], int *cur, int tgt);


/* Main */
int main(int argc, const char *argv[]) {
  LkList list_pool[LIST_POOL_SIZE] = { NULL };
  int current_list = 0;
  LkList L = list_pool[current_list];

  int op = 1;
  while (op) {
    system("cls"); printf("\n\n");  // PLATFORM: Win

    /* ����ѡ����ʾ */
    printf("   Menu for Linear Table On Linked Structure\n");
    printf("-------------------------------------------------\n");
    printf("       1. IntiaList       7. LocateElem\n");
    printf("       2. DestroyList     8. PriorElem\n");
    printf("       3. ClearList       9. NextElem\n");
    printf("       4. ListEmpty      10. ListInsert\n");
    printf("       5. ListLength     11. ListDelete\n");
    printf("       6. GetElem        12. ListTrabverse\n");
    printf("\n");
    printf("--------------------- EXTRA ---------------------\n");
    printf("      13. SaveList       14. LoadList\n");
    printf("      15. SelectList\n");
    printf("\n");
    printf("       0. Exit\n");
    printf("-------------------------------------------------\n");
    printf("    ��ѡ����Ĳ���[0~15]:");
    scanf("%d", &op);

    /* ִ�в��� */
    switch (op) {
      case 1: {
        if (IntiaList(&L) == OK) { printf("���Ա����ɹ���\n"); }
        else { printf("���Ա���ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 2: {
        if (DestroyList(&L) == OK) { printf("���Ա����ٳɹ���\n"); }
        else { printf("���Ա�����ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 3: {
        if (ClearList(&L) == OK) { printf("���Ա��ÿճɹ���\n"); }
        else { printf("���Ա��ÿ�ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 4: {
        int ret = ListEmpty(L);
        if (ret == TRUE) { printf("���Ա�Ϊ�ձ�\n"); }
        else if (ret == FALSE) { printf("���Ա�ǿա�\n"); }
        else { printf("��ȡ���Ա�״̬ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 5: {
        int ret = ListLength(L);
        if (ret != ERROR) { printf("���Ա��Ϊ %d ��\n", ret); }
        else { printf("��ȡ���Ա��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 6: {
        int index; ElemType result;
        printf("������Ԫ��λ�� "); scanf("%d", &index);
        int ret = GetElem(L, index, &result);
        if (ret == OK) { printf("��Ԫ�ص�ֵΪ %d ��\n", result); }
        else { printf("��ȡԪ��ֵʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 7: {
        int target;
        printf("������Ҫ����Ԫ�ص�ֵ�� "); scanf("%d", &target);
        int ret = LocateElem(L, target);
        if (ret == 0) { printf("��Ԫ�ز������Ա��У�\n"); }
        else { printf("��Ԫ�������Ա��е�λ��Ϊ %d ��\n", ret); }
        getchar(); getchar();
        break;
      }
      case 8: {
        int current, previous;
        printf("������Ŀ��Ԫ�ص�ֱ�Ӻ�̵�ֵ�� "); scanf("%d", &current);
        int ret = PriorElem(L, current, &previous);
        if (ret == OK) { printf("Ŀ��Ԫ��ֵΪ %d ��\n", previous); }
        else { printf("��ȡĿ��Ԫ��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 9: {
        int current, next;
        printf("������Ŀ��Ԫ�ص�ֱ��ǰ����ֵ�� "); scanf("%d", &current);
        int ret = NextElem(L, current, &next);
        if (ret == OK) { printf("Ŀ��Ԫ��ֵΪ %d ��\n", next); }
        else { printf("��ȡĿ��Ԫ��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 10: {
        int key; ElemType val;
        printf("������Ҫ����Ԫ�ص�λ�� "); scanf("%d", &key);
        printf("������Ҫ����Ԫ�ص�ֵ�� "); scanf("%d", &val);
        int ret = ListInsert(L, key, val);
        if (ret == OK) { printf("�ɹ�����Ԫ�أ�\n"); }
        else { printf("����Ԫ��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 11: {
        int key; ElemType val;
        printf("������Ҫɾ��Ԫ�ص�λ�� "); scanf("%d", &key);
        int ret = ListDelete(L, key, &val);
        if (ret == OK) { printf("�ɹ�ɾ��Ԫ�أ���ֵΪ %d ��\n", val); }
        else { printf("ɾ��Ԫ��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 12: {
        if (ListTrabverse(L) == OK) { /* pass */ ; }
        else { /* pass */ ;}
        getchar(); getchar();
        break;
      }
      case 13: {
        FILE *fp; char filename[100];
        printf("�������ļ����� "); scanf("%s", filename);
        if ((fp = fopen(filename, "w")) == NULL) {
          printf("���ܹ������ļ���\n");
        } else {
          if (SaveList(fp, L) == OK) {
            printf("�ɹ�д���ļ���\n");
          } else { printf("д���ļ�ʧ�ܣ�\n"); }
        }
        fclose(fp);
        getchar(); getchar();
        break;
      }
      case 14: {
        FILE *fp; char filename[100];
        printf("�������ļ����� "); scanf("%s", filename);
        if ((fp = fopen(filename, "rb")) == NULL) {
          printf("���ܹ���ȡ�ļ���\n");
        } else {
          if (LoadList(fp, &L) == OK) {
            printf("�ɹ����ļ���ȡ��\n");
          } else { printf("���ļ���ȡʧ�ܣ�\n"); }
        }
        fclose(fp);
        getchar(); getchar();
        break;
      }
      case 15: {
        int index;
        printf("������Ҫ�����ı��λ�� "); scanf("%d", &index);
        if (SelectList(&L, list_pool, &current_list, index) == OK) {
          printf("�л�������ɹ���\n");
        } else { printf("�л�������ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 0: { break; }
    } // switch
  } // while


  return 0;
}


/*
 * �������ƣ�IntiaList
 * �������������Ա� L ��ָ��
 * �������ܣ�����һ���յ����Ա�
 * ����ֵ��  �ɹ����췵�� OK �����򷵻� ERROR
 */
status
IntiaList(LkList *L) {
  if (*L) { printf("���й��ص����Ա�\n"); return ERROR; }
  *L = (LkList)malloc(sizeof(LNode));  // ����ͷ�ڵ�ռ�
  if (!(*L)) { printf("�ڴ�ռ䲻�㣡\n"); return ERROR; }
  (*L)->data = 0;    // ͷ�ڵ��ű�
  (*L)->next = NULL;
  return OK;
}


/*
 * �������ƣ�DestroyList
 * �������������Ա� L ��ָ��
 * �������ܣ��������Ա�
 * ����ֵ��  �ɹ����ٷ��� OK �����򷵻� ERROR
 */
status
DestroyList(LkList *L) {
  LkList cur = *L;
  if (!cur) { printf("���Ա�û�б�������\n"); return ERROR; }
  // ����ռ�
  LkList nxt = cur->next; // ���汻���Ԫ�غ�̵ĵ�ַ
  for (; nxt; cur = nxt, nxt = nxt->next) { free(cur); }
  // ��ʱ nxt == NULL ��cur ָ���β
  free(cur);  // �ͷű�β��ռ�ռ�
  *L = NULL;
  return OK;
}


/*
 * �������ƣ�ClearList
 * �������������Ա� L ��ָ��
 * �������ܣ��������Ա�
 * ����ֵ��  �ɹ��ÿշ��� OK �����򷵻� ERROR
 */
status
ClearList(LkList *L) {
  if (DestroyList(L) == OK && IntiaList(L) == OK) { return OK; }
  else { return ERROR; }
}


/*
 * �������ƣ�ListEmpty
 * �������������Ա� L
 * �������ܣ��ж����Ա��Ƿ�Ϊ��
 * ����ֵ��  �� L Ϊ�ձ��򷵻� TRUE �����򷵻� FALSE
 *           �ж�ʧ�ܷ��� ERROR
 */
status
ListEmpty(LkList L) {
  if (!L) { printf("���Ա�û�б�������\n"); return ERROR; }
  if (L->next) { return FALSE; }
  else { return TRUE; }
}


/*
 * �������ƣ�ListLength
 * �������������Ա� L
 * �������ܣ��������Ա� L ������Ԫ�صĸ���
 * ����ֵ��  ����ɹ��򷵻� L ������Ԫ�صĸ���������ʧ�ܷ��� ERROR
 */
int
ListLength(LkList L) {
  if (!L) { printf("���Ա�û�б�������\n"); return ERROR; }
  return L->data; // HACK: ��ͷ�ڵ��ű�
}


/*
 * �������ƣ�GetElem
 * �������������Ա� L ���� e ���ص� i ������Ԫ�ص�ֵ
 * �������ܣ����Ҳ��� e ���ص� i ��Ԫ�ص�ֵ
 * ����ֵ��  ���ҳɹ��򷵻� OK �����򷵻� ERROR
 */
status
GetElem(LkList L, int idx, ElemType *rst) {
  if (!L) { printf("���Ա�û�б�������\n"); return ERROR; }
  if (idx < 1 || idx > ListLength(L)) {
    printf("�����λ���С���Ϸ���\n");
    return ERROR;
  }
  for (; idx > 0; idx--) { L = L->next; }
  *rst = L->data;
  return OK;
}


/*
 * �������ƣ�ListInsert
 * �������������Ա� L �ĵ�ַ�������λ�� i �����������Ԫ�� e
 * �������ܣ��� L �ĵ� i ��λ��֮ǰ�����µ�����Ԫ�� e
 *           ���Ѳ��������շ����������������Ŀռ䣬�ٲ���
 * ����ֵ��  �ɹ����뷵�� OK �����򷵻� ERROR
 */
status
ListInsert(LkList L, int key, ElemType val) {
  if (!L) { printf("���Ա�û�б�������\n"); return ERROR; }
  if ((ListLength(L) == 0 && key != 1)
      || (ListLength(L) != 0
          && (key < 1 || key > ListLength(L)))) {
    printf("�����λ���С���Ϸ���\n");
    return ERROR;
  }
  // ���޸ı������� L ����ָ���ͷ�ڵ�
  L->data += 1;
  // ��ȡҪ���λ��Ԫ�ص�ǰ������ L ָ��
  for (; key > 1; key--) { L = L->next; }
  // Ϊ�µ�����Ԫ�ط���ռ�
  LkList new_node = (LkList)malloc(sizeof(LNode));
  if (!new_node) { printf("�ڴ�ռ䲻�㣡\n"); return ERROR; }
  // ���½ڵ��������
  new_node->next = L->next;
  L->next = new_node;
  // ����Ԫ�ظ�ֵ
  new_node->data = val;
  return OK;
}


/*
 * �������ƣ�ListDelete
 * �������������Ա� L �ĵ�ַ��ɾ����λ�� i ���������ݵ�ָ�� e
 * �������ܣ�ɾ�� L �ĵ� i ������Ԫ�أ��� e ������ֵ
 *           ��������С����������ָ���Ŀռ䣬�����·����С�Ŀռ�
 * ����ֵ��  �ɹ�ɾ������ OK �����򷵻� ERROR
 */
status
ListDelete(LkList L, int key, ElemType *val) {
  // �Ϸ��Լ��
  if (!L) { printf("���Ա�û�б�������\n"); return ERROR; }
  if (key < 1 || key > L->data) {
    printf("�����ַ��ʽ���Ϸ���\n");
    return ERROR;
  }
  // ���ı�
  L->data -= 1;
  // ɾ��Ԫ��
  // - Ѱ��ǰ��
  LkList prev = L;
  for (; key > 1; key--) { prev = prev->next; }
  // - ֵ����
  *val = prev->next->data;
  // - �ͷſռ�
  L = prev->next->next; // �������ı�ͷ��ַ�Ѿ�����������
  free(prev->next);
  // - ������������
  prev->next = L;
  return OK;
}


/*
 * �������ƣ�LocateElem
 * �������������Ա� L ����ȶԵ�Ԫ��ֵ
 * �������ܣ����� L ������ֵ�� e ��ͬ��Ԫ�����ڵ�λ��
 * ����ֵ��  �ɹ��򷵻ص�һ���� e ��ͬ��Ԫ�����ڵ�λ�򣬲������򷵻� 0��
 *           ���򷵻� ERROR
 */
int
LocateElem(LkList L, ElemType val) {
  // �Ϸ��Լ��
  if (!L) { printf("���Ա�û�б�������\n"); return ERROR; }
  // ������Ѱ�ҷ���������Ԫ��
  int idx = 1;
  for (L = L->next; L && val != L->data; L = L->next) { idx++; }
  if (!L) { return 0; } // ����һ��û���ҵ�����������Ԫ��
  return idx;
}


/*
 * �������ƣ�PriorElem
 * �������������Ա� L �����ҵ����� cur_e ����ǰ��ֵ�� pre_e ����
 * �������ܣ����� L ���� cur_e ��ͬ�ĵ�һ�����ݣ����� pre_e ������ǰ����ֵ
 * ����ֵ��  �����ɹ��򷵻� OK �����򷵻� ERROR
 */
status
PriorElem(LkList L, ElemType cur_e, ElemType *pre_e) {
  // �Ϸ��Լ��
  if (!L) { printf("���Ա�û�б�������\n"); return ERROR; }
  // ���������� cur_e ��ǰ��
  LkList prev = L;
  for (; prev->next && prev->next->data != cur_e;
         prev = prev->next) { /* pass */ ; }
  // ���ҵ���ǰ�������ж�
  if (prev->next == NULL) { // - û���ҵ�
    printf("δ�ҵ�Ԫ��ֵΪ����ֵ��Ԫ�أ�\n");
    return ERROR;
  }
  if (prev == L) {  // - cur_e Ϊ���е�һ��Ԫ�أ�
                    //   �� prev ָ���ͷ�ڵ�
    printf("Ԫ��ֵΪ����ֵ��Ԫ���Ǳ��еĵ�һ��Ԫ�أ�\n");
    return ERROR;
  }
  // - �������
  *pre_e = prev->data;
  return OK;
}


/*
 * �������ƣ�NextElem
 * �������������Ա� L �����ҵ����� cur_e ������ֵ�� next_e ����
 * �������ܣ����� L ���� cur_e ��ͬ�ĵ�һ�����ݣ����� next_e �������̵�ֵ
 * ����ֵ��  �����ɹ��򷵻� OK �����򷵻� ERROR
 */
status
NextElem(LkList L, ElemType cur_e, ElemType *nxt_e) {
  // �Ϸ��Լ��
  if (!L) { printf("���Ա�û�б�������\n"); return ERROR; }
  // ���������� cur_e
  LkList curr = L->next;  // NOTE: curr ָ��ǰԪ��
  for (; curr && curr->data != cur_e;
         curr = curr->next) { /* pass */ ; }
  // ���ҵ���Ԫ�ؽ����ж�
  if (curr == NULL) { // - û���ҵ�
    printf("δ�ҵ�Ԫ��ֵΪ����ֵ��Ԫ�أ�\n");
    return ERROR;
  }
  if (curr->next == NULL) { // - cur_e Ϊ�������һ��Ԫ��
    printf("Ԫ��ֵΪ����ֵ��Ԫ���Ǳ��е����һ��Ԫ�أ�\n");
    return ERROR;
  }
  // - �������
  *nxt_e = curr->next->data;
  return OK;
}


/*
 * �������ƣ�ListTrabverse
 * �������������Ա� L
 * �������ܣ����η��ʲ���ʾ���Ա��е�ÿ��Ԫ��
 * ����ֵ��  �ɹ��������� OK �����򷵻�ERROR
 */
status
ListTrabverse(LkList L) {
  if (!L) { printf("���Ա�û�б�������\n");  return ERROR; }
  // ���������
  printf(" ------------- All Elements -------------\n    ");
  for (L = L->next; L; L = L->next) {
    printf("%d ", L->data);
  }
  printf("\n ----------------- End ------------------\n");
  return OK;
}


/*
 * �������ƣ�SaveList
 * �����������ļ�ָ�� fp �����Ա� L
 * �������ܣ��� L �е����ݱ��浽 fp ָ����ļ���
 * ����ֵ��  �ɹ����淵�� OK �����򷵻� ERROR
 */
status
SaveList(FILE *fp, LkList L) {
  if (!fp) { return ERROR; }
  if (!L) { printf("���Ա�û�д�����\n"); return ERROR; }
  for (; L; L = L->next) {
    fwrite(&L->data, sizeof(ElemType), 1, fp);
  }
  return OK;
}


/*
 * �������ƣ�LoadList
 * �����������ļ�ָ�� fp �����Ա� L �ĵ�ַ
 * �������ܣ��� fp ָ���ļ��е����ݣ����ص����Ա� L ��
 * ����ֵ��  ���سɹ����� OK ������ʧ�ܷ��� ERROR
 */
status
LoadList(FILE *fp, LkList *L) {
  if (!fp) { return ERROR; }
  if ((*L)) { printf("���й��ص����Ա�\n"); return ERROR; }
  // �����ļ��б�
  fseek(fp, 0, SEEK_END);
  size_t filesize = ftell(fp) / sizeof(ElemType) - 1; // ��ͷ�ڵ㲻�Ʊ�
  rewind(fp);
  //  ��ȡ���Ա�һ�ζ�һ��
  // - ��ȡ��ͷ���������Ա�
  *L = (LkList)malloc(sizeof(LNode));
  if (!(*L)) { return ERROR; }
  fread(&( (*L)->data ), sizeof(ElemType), 1, fp);
  // - ����ͷ�����Ƿ�Ϊ��
  if ((*L)->data != filesize) {
    printf("�ļ��𻵣�\n");
    free(*L); *L = NULL;
    return ERROR;
  }
  // - ��ȡʣ�ಿ��
  LkList new_node = *L;
  for (; filesize; filesize--) {
    new_node->next = (LkList)malloc(sizeof(LNode));
    if (!new_node->next) { return ERROR; }
    new_node = new_node->next; new_node->next = NULL;
    fread(&new_node->data, sizeof(ElemType), 1, fp);
  }
  return OK;
}


/*
 * �������ƣ�SelectList
 * �������������Ա� L �ĵ�ַ��������� pool ��
 *           ��� L �� pool ��λ�õ� current_list ��0-�±꣩�ĵ�ַ��
 *           Ҫ�л��������Ա��� pool �е�λ�� idx ��1-�±꣩
 * �������ܣ��л������� pool �е� idx �����Ա�
 * ����ֵ��  �ɹ��л����� OK �����򷵻� ERROR
 */
status
SelectList(LkList *L, LkList pool[], int *cur, int tgt) {
  if (tgt < 1 || tgt > LIST_POOL_SIZE) {
    printf("�����ַ��ʽ���Ϸ���\n");
    return ERROR;
  }
  pool[*cur] = *L;
  *L = pool[tgt - 1];
  *cur = tgt - 1;
  return OK;
}
