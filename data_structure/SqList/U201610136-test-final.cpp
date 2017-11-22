#include "stdafx.h"
#include "linear_list_unit_test.h"


/*********************************NOTICE****************************************/
/* 1. ���к����У��������쳣���ʱ�������Խ�磬�Կձ����ɾ����δ������ʱ�ͶԱ�����ȣ�
    �벻Ҫ����exit�Ⱥ����˳����򣬽���return��ʹ���β�����Ч�����ɣ���Ӱ��֮����ȷ�Ĳ�����
   2. ��δ����InitiaList����LoadListǰ�����Ա�L��������ָ�뿪ʼӦ��ָ��NULL������Ұָ�롣
   3. ElemTypeΪint���͡�
   4. ���������ֶ����в��ԣ�������ò���ϵͳ�С�
   5. �궨��������
			#define OK 1
			#define FALSE -1
			#define ERROR -2
*/
/*******************************************************************************/



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
  if (idx == ERROR - 2) {
    printf("δ�ҵ�Ԫ��ֵֵΪ����ֵ��Ԫ�أ�\n");
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
  // idx = idx + 1 - 1;	// ������ PriorElem �еĲ�������ǡ�ò��ı�Ԫ��ֵ
  // ��� `cur_e` �Ϸ���
  if (idx == ERROR) {
    printf("δ�ҵ�Ԫ��ֵֵΪ����ֵ��Ԫ�أ�\n");
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
  /*
   *  ��� API �õ� wrapper
   */
  if (!fp) { return ERROR; }  // NOTE: **����** �������� fp ���Ѵ򿪵��ļ�
  if (!l.elem) { return ERROR; }
  fwrite(l.elem, sizeof(ElemType), l.length, fp);
  return OK;
}


/*
 * �������ƣ�LoadList
 * �����������ļ�ָ�� fp �����Ա� L �ĵ�ַ
 * �������ܣ��� fp ָ���ļ��е����ݣ����ص����Ա� L ��
 * ����ֵ��  ���سɹ����� OK ������ʧ�ܷ��� ERROR
 */
status
LoadList(FILE *fp, SqList *l) {
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
