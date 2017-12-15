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
status IntiaList(SqList *l);
status DestroyList(SqList *l);
status ClearList(SqList *l);
status ListEmpty(SqList l);
int ListLength(SqList l);
status GetElem(SqList l, int i, ElemType *e);
status LocateElem(SqList l, ElemType e);
status PriorElem(SqList l, ElemType cur, ElemType *pre_e);
status NextElem(SqList l, ElemType cur, ElemType *next_e);
status ListInsert(SqList *l, int i, ElemType e);
status ListDelete(SqList *l, int i, ElemType *e);
status ListTrabverse(SqList l);
/* �ļ����� */
status SaveList(FILE *fp, SqList l);
status LoadList(FILE *fp, SqList *l);
status SqList_writeToFile(SqList l, const char *filename);
status SqList_readFromFile(SqList *l, const char *path);
/* ������ */
status SelectList(SqList *l, SqList pool[], int *cur, int idx);


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
    puts("[LOG] before cls"); // HACK: ������һ�п��Խ�������л�����
                              //       Win10 ������У����ܺ����������غ�
                              //       ���ܿ����� `system("cls")` �����⡣
                              //       ���ھ���ԭ����Ҳ�������
                              //       ������ **���** ���������
    system("cls"); printf("\n\n");  // PLATFORM: Win only

    /* ����ѡ����ʾ */
    printf("   Menu for Linear Table On Sequence Structure\n");
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
        int result = ListEmpty(L);
        if (result == TRUE) { printf("���Ա�Ϊ�ձ�\n"); }
        // NOTE: ���� FALSE �� ERROR ֵ��Ϊ 0 ���ʵ����Ա�û�д���ʱ��ʹ��
        //       �ù��ܽ�ͬʱ��������Ա�û�б����������͡����Ա�Ϊ�ձ���
        else if (result == FALSE) { printf("���Ա�Ϊ�ձ�\n"); }
        else { printf("����ʧ�ܣ�\n"); }
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
        int index; ElemType result; // ��������
        printf("������Ԫ��λ�� "); scanf("%d", &index);
        int ret = GetElem(L, index, &result);  // ��ȡ����״̬��
        if (ret == OK) { printf("��Ԫ��ֵΪ %d ��\n", result); }
        else { printf("��ȡԪ��ֵʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 7: {
        int target;
        printf("������Ҫ���ҵ�Ԫ�ص�ֵ�� "); scanf("%d", &target);
        int ret = LocateElem(L, target);
        if (ret == 0) { printf("��Ԫ�ز������Ա��У�\n"); }
        else { printf("��Ԫ�������Ա��е�λ��Ϊ %d ��\n", ret); }
        getchar(); getchar();
        break;
      }
      case 8: {
        ElemType current, previous;
        printf("������Ŀ��Ԫ�ص�ֱ�Ӻ�̵�ֵ�� "); scanf("%d", &current);
        int ret = PriorElem(L, current, &previous);
        if (ret == OK) { printf("Ŀ��Ԫ��ֵΪ %d ��\n", previous); }
        else { printf("��ȡĿ��Ԫ��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 9: {
        ElemType current, next;
        printf("������ҪĿ��Ԫ�ص�ֱ��ǰ����ֵ�� "); scanf("%d", &current);
        int ret = NextElem(L, current, &next);
        if (ret == OK) { printf("Ŀ��Ԫ��ֵΪ %d ��\n", next); }
        else { printf("��ȡĿ��Ԫ��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 10: {
        int key; ElemType value;
        printf("������Ҫ����Ԫ�ص�λ�ã� "); scanf("%d", &key);
        printf("������Ҫ����Ԫ�ص�ֵ�� "); scanf("%d", &value);
        if (ListInsert(&L, key, value) == OK) { printf("�ɹ�����Ԫ�أ�\n"); }
        else { printf("����Ԫ��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 11: {
        int key; ElemType value;
        printf("������Ҫɾ��Ԫ�ص�λ�� "); scanf("%d", &key);
        int ret = ListDelete(&L, key, &value);
        if (ret == OK) { printf("�ɹ�ɾ��Ԫ�أ���ֵΪ %d ��\n", value); }
        else { printf("ɾ��Ԫ��ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 12: {
        if (!ListTrabverse(L)) { printf("���Ա��ǿձ�\n"); }
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
        if (SelectList(&L, list_pool, &current_list, index) == OK) {
          printf("�л�������ɹ���\n");
        } else { printf("�л�������ʧ�ܣ�\n"); }
        getchar(); getchar();
        break;
      }
      case 0: { break; }  // ��Ч����
      default: { break; }
    } // switch
  } // while

  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
  return 0; // ����Ͳ����� OK �ˣ���Ȼ shell �����쳣�˳���
}


/*** ��������ʵ�� ***/

/*
 * �������ƣ�IntiaList
 * �������������Ա� L ��ָ��
 * �������ܣ�����һ���յ����Ա�
 * ����ֵ��  �ɹ����췵�� OK �����򷵻� ERROR
 */
status
IntiaList(SqList *L) {
  if (L->elem) { printf("���߳������й��ص����Ա�\n"); return ERROR; }
  L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
  if (!L->elem) { return ERROR; }
  L->length = 0; L->list_size = LIST_INIT_SIZE;
#ifdef DEBUG
  L->length = 10; // ֱ�Ӵ������ֵ����ʼֵ��������������
  L->elem[2] = 1; L->elem[3] = 2; L->elem[4] = 5;
#endif
  return OK;
}


/*
 * �������ƣ�ListTrabverse
 * �������������Ա� L
 * �������ܣ����η��ʲ���ʾ���Ա��е�ÿ��Ԫ��
 * ����ֵ��  �ɹ��������� OK �����򷵻�ERROR
 */
status
ListTrabverse(SqList L) {
  if (!L.elem) { printf("���Ա�û�б�������\n"); return ERROR; }
  int i;
  printf("\n-----------all elements -----------------------\n");
  for (i = 0; i < L.length; i++) { printf("%d ", L.elem[i]); }
  printf("\n------------------ end ------------------------\n");
  return L.length;
}


/*
 * �������ƣ�DestroyList
 * �������������Ա� L ��ָ��
 * �������ܣ��������Ա�
 * ����ֵ��  �ɹ����ٷ��� OK �����򷵻� ERROR
 */
status
DestroyList(SqList *l) {
  // �Ϸ��Լ��
  if (!l->elem) { printf("���Ա�û�б�������\n"); return ERROR; }
  // �ͷſռ�
  free(l->elem);
  l->elem = NULL; l->length = 0; l->list_size = 0;
  return OK;
}


/*
 * �������ƣ�ClearList
 * �������������Ա� L ��ָ��
 * �������ܣ��������Ա�
 * ����ֵ��  �ɹ��ÿշ��� OK �����򷵻� ERROR
 */
status
ClearList(SqList *l) {
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


/*
 * �������ƣ�ListEmpty
 * �������������Ա� L
 * �������ܣ��ж����Ա��Ƿ�Ϊ��
 * ����ֵ��  �� L Ϊ�ձ��򷵻� TRUE �����򷵻� FALSE
 *           �ж�ʧ�ܷ��� ERROR
 */
status
ListEmpty(SqList l) {
  // �Ϸ��Լ��
  if (!l.elem) { printf("���Ա�û�б�������\n"); return ERROR; }
  if (l.length) { return FALSE; }
  return TRUE;
}


/*
 * �������ƣ�ListLength
 * �������������Ա� L
 * �������ܣ��������Ա� L ������Ԫ�صĸ���
 * ����ֵ��  ����ɹ��򷵻� L ������Ԫ�صĸ���������ʧ�ܷ��� ERROR
 */
int
ListLength(SqList l) {
  // �Ϸ��Լ��
  if (!l.elem) { printf("���Ա�û�б�������\n"); return ERROR; }
  // ֱ�ӷ��ؽṹ���ж���ı�
  return l.length;  // NOTE: ��Ϊ��ʱ���� 0 �������� ERROR ��ֵ���������޷����֣�
}


/*
 * �������ƣ�GetElem
 * �������������Ա� L ���� e ���ص� i ������Ԫ�ص�ֵ
 * �������ܣ����Ҳ��� e ���ص� i ��Ԫ�ص�ֵ
 * ����ֵ��  ���ҳɹ��򷵻� OK �����򷵻� ERROR
 */
status
GetElem(SqList l, int idx, ElemType *e) {
  // �Ϸ��Լ��
  if (!l.elem) { printf("���Ա�û�б�������\n"); return ERROR; }
  if (idx > l.length || idx < 1) {
    printf("�����ַ��ʽ���Ϸ���\n");
    return ERROR;
  }
  // ȡ������ֵ
  *e = l.elem[idx - 1];
  return OK;
}


/*
 * �������ƣ�LocateElem
 * �������������Ա� L ����ȶԵ�Ԫ��ֵ
 * �������ܣ����� L ������ֵ�� e ��ͬ��Ԫ�����ڵ�λ��
 * ����ֵ��  �ɹ��򷵻ص�һ���� e ��ͬ��Ԫ�����ڵ�λ�򣬲������򷵻� 0��
 *           ���򷵻� ERROR
 */
status
LocateElem(SqList l, ElemType e) {
  // �Ϸ��Լ��
  if (!l.elem) { printf("���Ա�û�б�������\n"); return ERROR; }
  // ��������Ԫ��
  int idx = 1;  // ֱ�Ӵ� 1 ��ʼ�ӣ�ʡ�ú�������תλ��Ҫ��һ
  for (; l.elem[idx - 1] != e; idx++) {
    if (idx > l.length) { return 0; }
  }
  // �ҵ��ˣ����أ�
  return idx;
}


/*
 * �������ƣ�PriorElem
 * �������������Ա� L �����ҵ����� cur_e ����ǰ��ֵ�� pre_e ����
 * �������ܣ����� L ���� cur_e ��ͬ�ĵ�һ�����ݣ����� pre_e ������ǰ����ֵ
 * ����ֵ��  �����ɹ��򷵻� OK �����򷵻� ERROR
 */
status
PriorElem(SqList l, ElemType cur_e, ElemType *pre_e) {
  // �Ϸ��Լ��
  if (!l.elem) { printf("���Ա�û�б�������\n"); return ERROR; }
  // ��ȡ `cur_e` λ��
  int idx = LocateElem(l, cur_e);  // NOTE: �ظ��˺Ϸ��Լ��
  idx -= 2; // ��ȡ `pre_e` �Ի���ַ��ƫ����
            // ��һ�� -1 : ǰһ��Ԫ��
            // �ڶ��� -1 : λ��תƫ����
  // ��� `cur_e` �Ϸ���
  if (idx == -2) {
    printf("δ�ҵ�Ԫ��ֵΪ����ֵ��Ԫ�أ�\n");
    return ERROR;
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


/*
 * �������ƣ�NextElem
 * �������������Ա� L �����ҵ����� cur_e ������ֵ�� next_e ����
 * �������ܣ����� L ���� cur_e ��ͬ�ĵ�һ�����ݣ����� next_e �������̵�ֵ
 * ����ֵ��  �����ɹ��򷵻� OK �����򷵻� ERROR
 */
status
NextElem(SqList l, ElemType cur_e, ElemType *next_e) {
  // �Ϸ��Լ��
  if (!l.elem) { printf("���Ա�û�б�������\n"); return ERROR; }
  // ��ȡ `cur_e` λ��
  int idx = LocateElem(l, cur_e);
  // idx = idx + 1 - 1; // ������ PriorElem �еĲ�������ǡ�ò��ı�Ԫ��ֵ
  // ��� `cur_e` �Ϸ���
  if (idx == 0) {
    printf("δ�ҵ�Ԫ��ֵΪ����ֵ��Ԫ�أ�\n");
    return ERROR;
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


/*
 * �������ƣ�ListInsert
 * �������������Ա� L �ĵ�ַ�������λ�� i �����������Ԫ�� e
 * �������ܣ��� L �ĵ� i ��λ��֮ǰ�����µ�����Ԫ�� e
 *           ���Ѳ��������շ����������������Ŀռ䣬�ٲ���
 * ����ֵ��  �ɹ����뷵�� OK �����򷵻� ERROR
 */
status
ListInsert(SqList *l, int i, ElemType e) {
  // �Ϸ��Լ��
  if (!l->elem) { printf("���Ա�û�б�������\n"); return ERROR; }
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


/*
 * �������ƣ�ListDelete
 * �������������Ա� L �ĵ�ַ��ɾ����λ�� i ���������ݵ�ָ�� e
 * �������ܣ�ɾ�� L �ĵ� i ������Ԫ�أ��� e ������ֵ
 *           ��������С����������ָ���Ŀռ䣬�����·����С�Ŀռ�
 * ����ֵ��  �ɹ�ɾ������ OK �����򷵻� ERROR
 */
status
ListDelete(SqList *l, int i, ElemType *e) {
  // �Ϸ��Լ��
  if (!l->elem) { printf("���Ա�û�б�������\n"); return ERROR; }
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


/*
 * �������ƣ�SaveList
 * �����������ļ�ָ�� fp �����Ա� L
 * �������ܣ��� L �е����ݱ��浽 fp ָ����ļ���
 * ����ֵ��  �ɹ����淵�� OK �����򷵻� ERROR
 */
status
SaveList(FILE *fp, SqList l) {
  if (!fp) { return ERROR; }  // NOTE: **����** �������� fp ���Ѵ򿪵��ļ�
  if (!l.elem) { return ERROR; }
  fwrite(l.elem, sizeof(ElemType), l.length, fp);
  return OK;
}


status
SqList_writeToFile(SqList l, const char *filename) {
  // �Ϸ��Լ��
  if (!l.elem) { printf("���Ա�û�б�������\n"); return ERROR; }
  // �����ļ�
  FILE *fp;
  if ((fp = fopen(filename, "w")) == NULL) {
    printf("���ܹ������ļ���\n");
    return ERROR;
  }
  // д��
  if (SaveList(fp, l) != OK) {
    /* pass */
    return ERROR;
  }
  fclose(fp); return OK;  // �ͷž��������
}


/*
 * �������ƣ�LoadList
 * �����������ļ�ָ�� fp �����Ա� L �ĵ�ַ
 * �������ܣ��� fp ָ���ļ��е����ݣ����ص����Ա� L ��
 * ����ֵ��  ���سɹ����� OK ������ʧ�ܷ��� ERROR
 */
status
LoadList(FILE *fp, SqList *l) {
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
  if (l->elem) { printf("���й��ص����Ա�\n"); return ERROR; }
  // ���ļ�
  FILE *fp;
  if ((fp = fopen(path, "r")) == NULL) {
    printf("���ܹ���ȡ�ļ���\n");
    return ERROR;
  }
  // ��ȡ
  if (LoadList(fp, l) != OK) {
    /* pass */
    return ERROR;
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
SelectList(SqList *l, SqList pool[], int *current_list, int idx) {
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
