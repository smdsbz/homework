/*
 *  ����˳��洢�ṹ�����Ա�ʵ��
 *    ---- by U201610136 ������ У�ʽ���1601��
 */

#include <stdio.h>
#include <stdlib.h>

// #define DEBUG

/* Page 10 */
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASABLE  -1
#define OVERFLOW    -2

/* ����Ԫ�����Ͷ��� */
typedef int status;
typedef int ElemType;

/* Page 22 */
#define LIST_INIT_SIZE  2
#define LIST_INC_SIZE   1

#define LIST_POOL_SIZE  20

/* ����˳��洢�ṹ�����Ա����ݽṹ���� */
typedef struct _SqList {
  ElemType *elem;       // ָ�����Դ洢��
  int       length;     // ��
  int       list_size;  // ������
} SqList;

/* Page 19 */
status SqList_init(SqList *l);
status SqList_destroy(SqList *l);
status SqList_clear(SqList *l);
status SqList_empty(SqList l);
int SqList_length(SqList l);
status SqList_getElem(SqList l, int i, ElemType *e);
status Sqlist_locateElem(SqList l, ElemType e);
status SqList_priorElem(SqList l, ElemType cur, ElemType *pre_e);
status SqList_nextElem(SqList l, ElemType cur, ElemType *next_e);
status SqList_insert(SqList *l, int i, ElemType e);
status SqList_delete(SqList *l, int i, ElemType *e);
status SqList_traverse(SqList l);
/* �ļ����� */
status SqList_writeToFile(SqList l, const char *filename);
status SqList_readFromFile(SqList *l, const char *path);
/* ������ */
status SqList_selectList(SqList *l, SqList pool[], int *cur, int idx);


/* Main */
int main(int argc, const char *argv[]) {
  // ��ʼ�����
  SqList list_pool[LIST_POOL_SIZE]; // ���
  int current_list = 0; // ���� L �� list_pool �е�λ��
  int i = 0;  // HACK: ��������� `op` ����ʡ�ڴ�ռ䣨����Ҳ�� 4 ���ֽڡ���
  for (; i < LIST_POOL_SIZE; i++) {
    list_pool[i].elem = NULL;
    list_pool[i].length = 0;
    list_pool[i].list_size = 0;
  }
  SqList L; L.elem = NULL; L.length = 0; L.list_size = 0;  // ��ʼ��
  int op=1; // ������ʾ��
  while (op) {
    system("cls");  // Win
    printf("\n\n");

    /* ����ѡ����ʾ */
    printf("   Menu for Linear Table On Sequence Structure\n");
    printf("-------------------------------------------------\n");
    printf("       1. InitList        7. LocateElem\n");
    printf("       2. DestroyList     8. PriorElem\n");
    printf("       3. ClearList       9. NextElem\n");
    printf("       4. ListEmpty      10. ListInsert\n");
    printf("       5. ListLength     11. ListDelete\n");
    printf("       6. GetElem        12. ListTraverse\n");
    printf("\n");
    printf("--------------------- EXTRA ---------------------\n");
    printf("      13. WriteToFile    14. ReadFromFile\n");
    printf("      15. SelectList\n");
    printf("\n");
    printf("       0. Exit\n");
    printf("-------------------------------------------------\n");
    printf("    ��ѡ����Ĳ���[0~12]:");
    scanf("%d", &op);

    /* ִ�в��� */
    switch (op) {
      case 1: {
        if (SqList_init(&L) == OK) { printf("���Ա����ɹ���\n"); }
        else { printf("���Ա���ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 2: {
        if (SqList_destroy(&L) == OK) { printf("���Ա����ٳɹ���\n"); }
        else { printf("���Ա�����ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 3: {
        if (SqList_clear(&L) == OK) { printf("���Ա��ÿճɹ���\n"); }
        else { printf("���Ա��ÿ�ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 4: {
        int result = SqList_empty(L);
        if (result == TRUE) { printf("���Ա�Ϊ�ձ�\n"); }
        // NOTE: ���� FALSE �� ERROR ֵ��Ϊ 0 ���ʵ����Ա�û�д���ʱ��ʹ��
        //       �ù��ܽ�ͬʱ��������Ա�û�б����������͡����Ա�Ϊ�ձ���
        else if (result == FALSE) { printf("���Ա�Ϊ�ձ�\n"); }
        else { printf("����ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 5: {
        int ret = SqList_length(L);
        if (ret != ERROR) { printf("���Ա��Ϊ %d ��\n", ret); }
        else { printf("��ȡ���Ա��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 6: {
        int index; ElemType result; // ��������
        printf("������Ԫ��λ�� "); scanf("%d", &index);
        int ret = SqList_getElem(L, index, &result);  // ��ȡ����״̬��
        if (ret == OK) { printf("��Ԫ��ֵΪ %d ��\n", result); }
        else { printf("��ȡԪ��ֵʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 7: {
        int target;
        printf("������Ҫ���ҵ�Ԫ�ص�ֵ�� "); scanf("%d", &target);
        int ret = Sqlist_locateElem(L, target);
        if (ret == 0) { printf("��Ԫ�ز������Ա��У�\n"); }
        else { printf("��Ԫ�������Ա��е�λ��Ϊ %d ��\n", ret); }
        getchar(); getchar();
        break;
      }
      case 8: {
        ElemType current, previous;
        printf("������ҪĿ��Ԫ�ص�ֱ�Ӻ�̵�Ԫ��ֵ�� "); scanf("%d", &current);
        int ret = SqList_priorElem(L, current, &previous);
        if (ret == OK) { printf("Ŀ��Ԫ��ֵΪ %d ��\n", previous); }
        else { printf("��ȡĿ��Ԫ��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 9: {
        ElemType current, next;
        printf("������ҪĿ��Ԫ�ص�ֱ��ǰ����Ԫ��ֵ�� "); scanf("%d", &current);
        int ret = SqList_nextElem(L, current, &next);
        if (ret == OK) { printf("Ŀ��Ԫ��ֵΪ %d ��\n", next); }
        else { printf("��ȡĿ��Ԫ��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 10: {
        int key; ElemType value;
        printf("������Ҫ����Ԫ�ص�λ�ã� "); scanf("%d", &key);
        printf("������Ҫ����Ԫ�ص�ֵ�� "); scanf("%d", &value);
        if (SqList_insert(&L, key, value) == OK) { printf("�ɹ�����Ԫ�أ�\n"); }
        else { printf("����Ԫ��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 11: {
        int key; ElemType value;
        printf("������Ҫɾ��Ԫ�ص�λ�� "); scanf("%d", &key);
        int ret = SqList_delete(&L, key, &value);
        if (ret == OK) { printf("�ɹ�ɾ��Ԫ�أ���ֵΪ %d ��\n", value); }
        else { printf("ɾ��Ԫ��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 12: {
        if (!SqList_traverse(L)) { printf("���Ա��ǿձ�\n"); }
        getchar(); getchar();
        break;
      }
      case 13: {
        char filename[100];
        printf("�������ļ����� "); scanf("%s", filename);
        if (SqList_writeToFile(L, filename) == OK) {
          printf("�ɹ�д���ļ���\n");
        } else { printf("д���ļ�ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 14: {
        char filename[100];
        printf("�������ļ����� "); scanf("%s", filename);
        int ret = SqList_readFromFile(&L, filename);
        if (ret == OK) { printf("�ɹ����ļ���ȡ��\n"); }
        else { printf("���ļ���ȡʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 15: {
        int index;
        printf("������Ҫ�����ı��λ�� "); scanf("%d", &index);
        if (SqList_selectList(&L, list_pool, &current_list, index) == OK) {
          printf("�л�������ɹ���\n");
        } else { printf("�л�������ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 0: { break; }  // ��Ч����
    } // switch
  } // while

  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
  return 0; // ����Ͳ����� OK �ˣ���Ȼ shell �����쳣�˳���
}


/*** ��������ʵ�� ***/

status
SqList_init(SqList *L) {
  if (L->elem) {
    printf("���߳������й��ص����Ա�\n"); return ERROR; }
  L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
  if (!L->elem) { return ERROR; }
  L->length = 0; L->list_size = LIST_INIT_SIZE;
#ifdef DEBUG
  L->length = 10; // ֱ�Ӵ������ֵ����ʼֵ��������������
  L->elem[2] = 1; L->elem[3] = 2; L->elem[4] = 5;
#endif
  return OK;
}


status
SqList_traverse(SqList L) {
  if (!L.elem) {
    printf("���Ա�û�б�������\n");
    return ERROR;
  }
  int i;
  printf("\n-----------all elements -----------------------\n");
  for (i = 0; i < L.length; i++) { printf("%d ", L.elem[i]); }
  printf("\n------------------ end ------------------------\n");
  return L.length;
}


status
SqList_destroy(SqList *l) {
  // �Ϸ��Լ��
  if (!l->elem) {
    printf("���Ա�û�б�������\n");
    return ERROR;
  }
  // �ͷſռ�
  free(l->elem);
  l->elem = NULL; l->length = 0; l->list_size = 0;
  return OK;
}


status
SqList_clear(SqList *l) {
  // �Ϸ��Լ��
  if (!l->elem) {
    printf("���Ա�û�б�������\n");
    return ERROR;
  }
  // ֱ�ӽ����С�� 0
  l->length = 0;
  // ���ٿռ�ռ��
  if (l->list_size > LIST_INIT_SIZE) {
    free(l->elem);
    l->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!l->elem) { return ERROR; }
  }
  return OK;
}


status
SqList_empty(SqList l) {
  // �Ϸ��Լ��
  if (!l.elem) {
    printf("���Ա�û�б�������\n");
    return ERROR;
  }
  if (l.length) { return FALSE; }
  return TRUE;
}


int
SqList_length(SqList l) {
  // �Ϸ��Լ��
  if (!l.elem) {
    printf("���Ա�û�б�������\n");
    return ERROR;
  }
  // ֱ�ӷ��ؽṹ���ж���ı�
  return l.length;  // NOTE: ��Ϊ��ʱ���� 0 �������� ERROR ��ֵ���������޷����֣�
}


status
SqList_getElem(SqList l, int idx, ElemType *e) {
  // �Ϸ��Լ��
  if (!l.elem) {
    printf("���Ա�û�б�������\n");
    return ERROR;
  }
  if (idx > l.length || idx < 1) {
    printf("�����ַ��ʽ���Ϸ���\n");
    return ERROR;
  }
  // ȡ������ֵ
  *e = l.elem[idx - 1];
  return OK;
}


status
Sqlist_locateElem(SqList l, ElemType e) {
  // �Ϸ��Լ��
  if (!l.elem) {
    printf("���Ա�û�б�������\n");
    return ERROR;
  }
  // ��������Ԫ��
  int idx = 1;  // ֱ�Ӵ� 1 ��ʼ�ӣ�ʡ�ú�������תλ��Ҫ��һ
  for (; l.elem[idx - 1] != e; idx++) {
    if (idx > l.length) { return 0; }
  }
  // �ҵ��ˣ����أ�
  return idx;
}


status
SqList_priorElem(SqList l, ElemType cur_e, ElemType *pre_e) {
  // �Ϸ��Լ��
  if (!l.elem) {
    printf("���Ա�û�б�������\n");
    return ERROR;
  }
  // ��ȡ `cur_e` λ��
  int idx = Sqlist_locateElem(l, cur_e);  // NOTE: �ظ��˺Ϸ��Լ��
  idx -= 2; // ��ȡ `pre_e` �Ի���ַ��ƫ����
            // ��һ�� -1 : ǰһ��Ԫ��
            // �ڶ��� -1 : λ��תƫ����
  // ��� `cur_e` �Ϸ���
  if (idx == ERROR - 2) {
    printf("δ�ҵ�Ԫ��ֵֵΪ����ֵ��Ԫ�أ�\n");
    return FALSE;
  }
  if (idx == -1) {
    printf("Ԫ��ֵΪ����ֵ��Ԫ��Ϊ���е�һ��Ԫ�أ�\n");
    return ERROR;
  } else {  // ����
    // �� `pre_e` ��ֵ
    *pre_e = l.elem[idx];
    return OK;
  }
}


status
SqList_nextElem(SqList l, ElemType cur_e, ElemType *next_e) {
  // �Ϸ��Լ��
  if (!l.elem) {
    printf("���Ա�û�б�������\n");
    return ERROR;
  }
  // ��ȡ `cur_e` λ��
  int idx = Sqlist_locateElem(l, cur_e);
  // idx = idx + 1 - 1;
  // ��� `cur_e` �Ϸ���
  if (idx == ERROR) {
    printf("δ�ҵ�Ԫ��ֵֵΪ����ֵ��Ԫ�أ�\n");
    return FALSE;
  }
  if (idx == l.length) {
    printf("Ԫ��ֵΪ����ֵ��Ԫ��Ϊ�������һ��Ԫ�أ�\n");
    return ERROR;
  } else {  // ����
    // �� `next_e` ��ֵ
    *next_e = l.elem[idx];
    return OK;
  }
}


status
SqList_insert(SqList *l, int i, ElemType e) {
  // �Ϸ��Լ��
  if (!l->elem) {
    printf("���Ա�û�б�������\n");
    return ERROR;
  }
  // - `i` ��Χ����
  if ((l->length == 0 && i != 1)  // �ձ�
      || (l->length > 0 && (i < 1 || i > l->length))) {  // �ǿձ�`i`Ӧ�з�Χ
    printf("�����ַ��ʽ���Ϸ���\n");
    return ERROR;
  }
  // �ռ��Ƿ�������
  if (l->length == l->list_size) {
    // ����ռ�
    l->list_size += LIST_INC_SIZE;
    // �������ƶ����ռ����ԣ�ĵط�
    l->elem = (ElemType *)realloc(l->elem, l->list_size);
    if (!l->elem) { return OVERFLOW; }  // ���
  }
  // �ƶ�����λ��֮�������Ԫ��
  i--;  // ת��Ϊƫ����
  int bak_ptr = l->length - 1;
  for (; bak_ptr >= i; bak_ptr--) {
    l->elem[bak_ptr + 1] = l->elem[bak_ptr];
  }
  // ��Ŀ��λ�ø�ֵ
  l->elem[i] = e;
  // ����ɼ���
  l->length += 1;
  return OK;
}


status
SqList_delete(SqList *l, int i, ElemType *e) {
  // �Ϸ��Լ��
  if (!l->elem) {
    printf("���Ա�û�б�������\n");
    return ERROR;
  }
  if (i < 1 || i > l->length) {
    printf("�����ַ��ʽ���Ϸ���\n");
    return ERROR;
  }
  // ɾ��Ԫ��ֵ����
  i--; l->length -= 1;
  *e = l->elem[i];
  // ɾ��λ�ú�Ԫ������ǰ��
  for (; i < l->length; i++) {
    l->elem[i] = l->elem[i + 1];
  }
  // ����Ƿ���Լ�С����
  // HACK: ����һ�����кϲ����Լ�Сʱ������
  if (l->list_size - l->length > LIST_INC_SIZE) {
    l->elem = (ElemType *)realloc(l->elem,
        (l->list_size - LIST_INC_SIZE) * sizeof(ElemType));
    if (!l->elem) { return ERROR; }
  }
  return OK;
}


status
SqList_saveList(FILE *fp, SqList l) {
  /*
   *  ��� API �õ� wrapper
   */
  if (!fp) { return ERROR; }  // NOTE: **����** �������� fp ���Ѵ򿪵��ļ�
  if (!l.elem) { return ERROR; }
  fwrite(l.elem, sizeof(ElemType), l.length, fp);
  return OK;
}


status
SqList_writeToFile(SqList l, const char *filename) {
  // �Ϸ��Լ��
  if (!l.elem) {
    printf("���Ա�û�б�������\n");
    return ERROR;
  }
  // �����ļ�
  FILE *fp;
  if ((fp = fopen(filename, "w")) == NULL) {
    printf("���ܹ������ļ���\n");
    return ERROR;
  }
  // д��
  if (SqList_saveList(fp, l) != OK) {
    /* pass */
    return ERROR;
  }
  fclose(fp); return OK;  // �ͷž��������
}


status
SqList_loadList(FILE *fp, SqList *l) {
  /*
   *  ��� API �õ� wrapper
   */
  if (!fp) { return ERROR; }
  if (l->elem) { return ERROR; }  // �������������صı�
  // ��ʼ�����ؽṹ��
  // - ��ȡ�ļ���С
  fseek(fp, 0, SEEK_END);
  size_t filesize = ftell(fp) / sizeof(ElemType);
  fseek(fp, 0, SEEK_SET);
  // - ��Ҫʱ�����ռ�
  if ((!l->elem) || l->length < filesize) { // û�пռ� �� �ռ�̫С
    if (l->elem) { free(l->elem); } // NOTE: �����֧����ִ�У�
                                    //       �ѽ�ֹ���ǹ��ر�Ĳ�����
    l->elem = (ElemType *)malloc(filesize * sizeof(ElemType));
    if (!l->elem) { return ERROR; }
  }
  // һ���Զ�ȡ�ļ�����
  l->length = filesize; l->list_size = filesize;
  fread(l->elem, sizeof(ElemType), filesize, fp);
  return OK;
}


status
SqList_readFromFile(SqList *l, const char *path) {
  // ����Ƿ����б����
  if (l->elem) {
    printf("���й��ص����Ա�\n");
    return ERROR;
  }
  // ���ļ�
  FILE *fp;
  if ((fp = fopen(path, "r")) == NULL) {
    printf("���ܹ���ȡ�ļ���\n");
    return ERROR;
  }
  // ��ȡ
  if (SqList_loadList(fp, l) != OK) {
    /* pass */
    return ERROR;
  }
  return OK;
}


status
SqList_selectList(SqList *l, SqList pool[], int *current_list, int idx) {
  // �Ϸ��Լ��
  if (idx < 1 || idx > LIST_POOL_SIZE) {
    printf("�����ַ��ʽ���Ϸ���\n");
    return ERROR;
  }
  idx--;  // λ��תƫ����
  // ����д洢������
  pool[*current_list] = *l;
  // ����Ŀ�������
  // NOTE: ���� `L` ���� malloc �����ģ�����ֱ�Ӹı���ָ��
  l->elem = pool[idx].elem;
  l->length = pool[idx].length;
  l->list_size = pool[idx].list_size;
  // �Ķ���ָ��
  *current_list = idx;
  return OK;
}
