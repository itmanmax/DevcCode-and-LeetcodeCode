#include <stdio.h>
#include <stdlib.h>
#define maxnum 10000

typedef struct //ͼ����Ϣ����
{
    char no[20];      //ͼ�� ISBN
    char name[50];    //ͼ������
    float price;      //ͼ��۸�
    float unrealprice; //ͼ����ĺ�۸�
} Book;

typedef struct
{
    Book *elem;
    int length;
    int maxsize;

} Sqlist;

typedef struct LNode
{
    Book data;         //����������
    int numsize;       //���ĳ���
    struct LNode *next; //����ָ����
} LNode, *LinkList; //LinkList Ϊָ��ṹ�� LNode ��ָ������

void initsqlist(Sqlist *sqlist)
{
    (*sqlist).elem = (Book *)malloc(sizeof(Book) * maxnum);
    (*sqlist).maxsize = maxnum;
    (*sqlist).length = 0;
}

void inputSqlist(Sqlist *sqlist)
{
    // ������Ϣ
    int i;
    for (i = 0; i < maxnum; i++)
    {
        scanf("%s %s %f", (*sqlist).elem[i].no, (*sqlist).elem[i].name, &(*sqlist).elem[i].price);

        // �ж��Ƿ��������
        if ((*sqlist).elem[i].no[0] == '0' && (*sqlist).elem[i].name[0] == '0' && (*sqlist).elem[i].price == 0.0)
        {
            break;
        }
    }
    // ͳ���ж��ٱ���
    (*sqlist).length = i;
}

void inputSqlistnum(Sqlist *sqlist, int num)
{
    // ������Ϣ
    int i;
    for (i = 0; i < num; i++)
    {
        scanf("%s %s %f", (*sqlist).elem[i].no, (*sqlist).elem[i].name, &(*sqlist).elem[i].price);
    }
    // ͳ���ж��ٱ���
    (*sqlist).length = num;
}

void sqlistfindmax(Sqlist *sqlist)
{
    float max = (*sqlist).elem[0].price;
    int count = 0; //ͳ���м���
    // Ѱ��������
    for (int i = 1; i < (*sqlist).length; i++)
    {
        if ((*sqlist).elem[i].price > max)
        {
            max = (*sqlist).elem[i].price;
            count = 1;
        }
        else if ((*sqlist).elem[i].price == max)
        {
            count++; // ��������
        }
    }

    // ������������Ϣ
    printf("������ļ۸�Ϊ%.2f,����%d������������Ϣ:\n", max, count);
    for (int i = 0; i < (*sqlist).length; i++)
    {
        if ((*sqlist).elem[i].price == max)
        {
            printf("���ISBN: %s, ����: %s, �۸�Ϊ: %.2f\n", (*sqlist).elem[i].no, (*sqlist).elem[i].name, (*sqlist).elem[i].price);
        }
    }
}

void UPForSqlist(Sqlist *sqlist)
{
    // ��ʼ��ƽ���۸�
    float sum = 0.0;
    for (int i = 0; i < (*sqlist).length; i++)
    {
        sum += (*sqlist).elem[i].price;
    }
    float averagePrice = sum / (*sqlist).length;

    // ���¼۸�
    for (int i = 0; i < (*sqlist).length; i++)
    {
        if ((*sqlist).elem[i].price < averagePrice)
        {
            // �Ǽ�20%
            (*sqlist).elem[i].unrealprice = (*sqlist).elem[i].price * 1.2;
        }
        else
        {
            // �Ǽ� 10%
            (*sqlist).elem[i].unrealprice = (*sqlist).elem[i].price * 1.1;
        }
    }
    printf("ƽ���۸�Ϊ%.2f\n", averagePrice);
    for (int i = 0; i < (*sqlist).length; i++)
        printf("��%d�������ϢΪ: ���ISBN: %s, ����: %s, �޸ĺ�ļ۸�Ϊ: %.2f, ԭ���ļ۸�Ϊ: %.2f\n", i + 1, (*sqlist).elem[i].no, (*sqlist).elem[i].name, (*sqlist).elem[i].unrealprice, (*sqlist).elem[i].price);
}

void insertsqlist(Sqlist *sqlist, int insertplace)
{
    if (insertplace < 1 || insertplace > (*sqlist).length + 1)
    {
        printf("����λ�ò���������������\n");
        return;
    }

    Book newBook; // �����������Ϣ
    scanf("%s %s %f", newBook.no, newBook.name, &newBook.price);

    // �������鵽ָ��λ��
    for (int i = (*sqlist).length; i >= insertplace; i--)
    {
        (*sqlist).elem[i] = (*sqlist).elem[i - 1];
    }
    (*sqlist).elem[insertplace - 1] = newBook;
    (*sqlist).length++;

    printf("����ɹ�\n");
}


void deletesqlist(Sqlist *sqlist, int deleteplace)
{
    for (int i = deleteplace - 1; i < (*sqlist).length - 1; i++)
    {
        (*sqlist).elem[i] = (*sqlist).elem[i + 1];
    }
    (*sqlist).length--;
}

void outputSqlist(Sqlist sqlist)
{
    printf("�����鱾%d��\n", sqlist.length);
    for (int i = 0; i < sqlist.length; i++)
        printf("��%d�������ϢΪ: ���ISBN: %s, ����: %s, �۸�: %.2f\n", i + 1, sqlist.elem[i].no, sqlist.elem[i].name, sqlist.elem[i].price);
}

void initLinkList(LinkList *linkList)
{
    *linkList = NULL;
}

void insertLinkList(LinkList *linkList, int insertplace, Book newBook)
{
    LNode *newNode = (LNode *)malloc(sizeof(LNode)); // Ϊ����ڵ�����ڴ�
    if (newNode == NULL)
    {
        printf("�ڴ����ʧ��\n");
        return;
    }

    newNode->data = newBook;
    newNode->next = NULL;
    newNode->numsize = 1;
    if (insertplace == 1 || *linkList == NULL)
    {
        // ���뵽����ͷ��
        newNode->next = *linkList;
        *linkList = newNode;
        (*linkList)->numsize=1;
    }
    else
    {
        // ���뵽�����м��β��
        LNode *current = *linkList;
        for (int i = 1; i < insertplace - 1 && current != NULL; i++)
        {
            current = current->next;
        }

        if (current != NULL)
        {
            newNode->next = current->next;
            current->next = newNode;
            (*linkList)->numsize++;
        }
        else
        {
            printf("����λ����Ч\n");
            free(newNode); // �ͷ�����ڵ���ڴ�
            return;
        }
    }
}

void inputLinkList(LinkList *linkList)
{

    int i = 1;
    while (1)
    {
        Book newBook;

        // ����ͼ����Ϣ
        scanf("%s %s %f", newBook.no, newBook.name, &newBook.price);

        // �ж��Ƿ��������
        if (newBook.no[0] == '0' && newBook.name[0] == '0' && newBook.price == 0.0)
        {
            break;
        }

        // �����½ڵ㵽����β��
        insertLinkList(linkList, i, newBook);
        
        i++;
    }
}

void inputLinkListNum(LinkList *linkList, int num)
{
    int i = 1;
    while (i <= num)
    {
        Book newBook;

        // ����ͼ����Ϣ
        scanf("%s %s %f", newBook.no, newBook.name, &newBook.price);
        // �����½ڵ㵽����β��
        insertLinkList(linkList, i, newBook);
        i++;
    }
}
void deleteLinkList(LinkList *linkList, int deleteplace)
{
    if (deleteplace < 1 || *linkList == NULL)
    {
        printf("ɾ��λ�ò���������������\n");
        return;
    }

    // ɾ��ͷ�ڵ�
    if (deleteplace == 1)
    {
        LNode *temp = *linkList;
        *linkList = (*linkList)->next;
        free(temp);
         (*linkList)->numsize--;
    }
    else
    {
        // ɾ���м��β���ڵ�
        LNode *current = *linkList;
        for (int i = 1; i < deleteplace - 1 && current != NULL; i++)
        {
            current = current->next;
        }

        if (current != NULL && current->next != NULL)
        {
            LNode *temp = current->next;
            current->next = current->next->next;
            free(temp);
            (*linkList)->numsize--;
        }
        else
        {
            printf("ɾ��λ�ò���������������\n");
            return;
        }
    }

    printf("ɾ���ɹ�\n");
}


void UPForLinklist(LinkList linkList)
{
    // ��ʼ��ƽ���۸�
    float sum = 0.0;
    int length = 0;
    LNode *current = linkList;

    while (current != NULL)
    {
        sum += current->data.price;
        length++;
        current = current->next;
    }

    float averagePrice = sum / length;

    // ���¼۸�
    current = linkList;
    while (current != NULL)
    {
        if (current->data.price < averagePrice)
        {
            // �Ǽ�20%
            current->data.unrealprice = current->data.price * 1.2;
        }
        else
        {
            // �Ǽ� 10%
            current->data.unrealprice = current->data.price * 1.1;
        }
        current = current->next;
    }

    printf("ƽ���۸�Ϊ%.2f\n", averagePrice);
    current = linkList;
    int i = 1;
    while (current != NULL)
    {
        printf("��%d�������ϢΪ: ���ISBN: %s, ����: %s, �޸ĺ�ļ۸�Ϊ: %.2f, ԭ���ļ۸�Ϊ: %.2f\n", i, current->data.no, current->data.name, current->data.unrealprice, current->data.price);
        current = current->next;
        i++;
    }
}

void linkListFindMax(LinkList linkList)
{
    if (linkList == NULL || linkList->numsize == 0)
    {
        printf("����Ϊ��\n");
        return;
    }

    float max = linkList->data.price;
    int count = 0; // ͳ���м���

    // Ѱ��������
    LNode *current = linkList;
    while (current != NULL)
    {
        if (current->data.price > max)
        {
            max = current->data.price;
            count = 1;
        }
        else if (current->data.price == max)
        {
            count++; // ��������
        }

        current = current->next;
    }

    // ������������Ϣ
    printf("������ļ۸�Ϊ%.2f, ����%d������������Ϣ:\n", max, count);

    current = linkList;
    int i = 1;
    while (current != NULL)
    {
        if (current->data.price == max)
        {
            printf("��%d�������ϢΪ: ���ISBN: %s, ����: %s, �۸�Ϊ: %.2f\n", i, current->data.no, current->data.name, current->data.price);
        i++; 
		}

        current = current->next;
       
    }
}

void outputLinkList(LinkList linkList)
{
    printf("�����鱾%d��\n", linkList->numsize);
    LNode *current = linkList;
    int i = 1;
    while (current != NULL)
    {
        printf("��%d�������ϢΪ: ���ISBN: %s, ����: %s, �۸�: %.2f\n", i, current->data.no, current->data.name, current->data.price);
        current = current->next;
        i++;
    }
}

int main()
{   printf("����������ͼ��ݵĶ��ֲ�������������ͼ�飬ɾ��ͼ�飬���������飬�޸ļ۸����ͼ����Ϣ��\nע�⣺һ.���е�������Ϣ���Կո�Ϊ������ұ��������ո񣬷�����ܻ���ִ���\n      ��.����Ҳ������β�巨\n��������Ϊ���ࣺ\n1.˳������\n2.�������\n������ѡ������");
    int choose=0;
	scanf("%d", &choose);
	if(choose==1)
   { Sqlist sqlist;
     initsqlist(&sqlist);
	printf("��ѡ����˳����������Ϊ���¼��ֹ��ܣ���ѡ����ţ�\n");
	printf("1 ͳ��ͼ����е�ͼ�������ͬʱ�������ÿ��ͼ�����Ϣͼ����Ϣ��Ĵ����������\n");
	printf("2 ��������ͼ��Ե�ƽ���۸񣬽����е���ƽ���۸��ͼ��۸���� 20�����и��ڻ����ƽ���۸��ͼ��۸���� 10�������������۸��޸ĺ��ͼ����Ϣ��\n");
    printf("3 ���Ҽ۸���ߵ�ͼ�飬�����Ӧͼ�����Ϣ��\n");
    printf("4 ����ָ���Ĵ�������ͼ���λ�ú���Ϣ������ͼ����뵽ͼ�����ָ����λ���ϡ���������ͼ����������ͼ�����Ϣ��\n");
    printf("5 ����ָ���Ĵ�����ľ�ͼ���λ�ã�����ͼ���ͼ�����ɾ������������ͼ�����������ͼ�����Ϣ��\n������ѡ������\n");
    int choosemin=0;
	scanf("%d", &choosemin);
	if(choosemin==1)
	{printf("������ͼ����Ϣ��0 0 0��β\n");
	inputSqlist(&sqlist);
	 outputSqlist(sqlist);
	}
	else if(choosemin==2)
	{ printf("������ͼ����Ϣ��0 0 0��β\n");
	  inputSqlist(&sqlist);
	  UPForSqlist(&sqlist);	
	}
	else if(choosemin==3)
	{  printf("������ͼ��������ͼ����Ϣ\n"); 
		int num;
		scanf("%d", &num);	
		inputSqlistnum(&sqlist,num);
		sqlistfindmax(&sqlist);
	}
	else if(choosemin==4)
	{  int num;
	   printf("������ͼ��������ͼ����Ϣ\n"); 
		scanf("%d", &num);	
		inputSqlistnum(&sqlist,num);
		int insertplace;
		printf("���������λ�úͲ���ͼ����Ϣ\n"); 
		scanf("%d", &insertplace);	
		insertsqlist(&sqlist,insertplace);
		outputSqlist(sqlist);
	}
	else if(choosemin==5)
	{   printf("������ͼ��������ͼ����Ϣ\n"); 
		int num;
		scanf("%d", &num);	
		inputSqlistnum(&sqlist,num);
		int deleteplace;
		printf("������ɾ��λ��\n"); 
		scanf("%d", &deleteplace);	
		deletesqlist(&sqlist,deleteplace);
		outputSqlist(sqlist);
	}
   }
	else
	{ LinkList linkList;
	 initLinkList(&linkList);
	printf("��ѡ���������������Ϊ���¼��ֹ��ܣ���ѡ����ţ�\n");
	printf("1 ͳ��ͼ����е�ͼ�������ͬʱ�������ÿ��ͼ�����Ϣͼ����Ϣ��Ĵ����������\n");
	printf("2 ��������ͼ��Ե�ƽ���۸񣬽����е���ƽ���۸��ͼ��۸���� 20�����и��ڻ����ƽ���۸��ͼ��۸���� 10�������������۸��޸ĺ��ͼ����Ϣ��\n");
    printf("3 ���Ҽ۸���ߵ�ͼ�飬�����Ӧͼ�����Ϣ��\n");
    printf("4 ����ָ���Ĵ�������ͼ���λ�ú���Ϣ������ͼ����뵽ͼ�����ָ����λ���ϡ���������ͼ����������ͼ�����Ϣ��\n");
    printf("5 ����ָ���Ĵ�����ľ�ͼ���λ�ã�����ͼ���ͼ�����ɾ������������ͼ�����������ͼ�����Ϣ��\n������ѡ������\n");
    int choosemin=0;
	if(choosemin==1)
	{printf("������ͼ����Ϣ��0 0 0��β\n");
	 inputLinkList(&linkList);
	 outputLinkList(linkList);
	}
	else if(choosemin==2)
	{ printf("������ͼ����Ϣ��0 0 0��β\n");
	  inputLinkList(&linkList);
	  UPForLinklist(linkList);	
	}
	else if(choosemin==3)
	{   printf("������ͼ��������ͼ����Ϣ\n"); 
		int num;
		scanf("%d", &num);	
		inputLinkListNum(&linkList,num);
		linkListFindMax(linkList);
	}
	else if(choosemin==4)
	{  int num;
	   printf("������ͼ��������ͼ����Ϣ\n"); 
		scanf("%d", &num);	
		inputLinkListNum(&linkList,num);
		int insertplace;
		printf("���������λ�úͲ���ͼ����Ϣ\n"); 
		scanf("%d", &insertplace);
		Book newbook;
		scanf("%s %s %f", newbook.no, newbook.name, &newbook.price);	
		insertLinkList(&linkList,insertplace,newbook);
		outputLinkList(linkList);
	}
	else if(choosemin==5)
	{   printf("������ͼ��������ͼ����Ϣ\n"); 
		int num;
		scanf("%d", &num);	
		inputLinkListNum(&linkList,num);
		int deleteplace;
		printf("������ɾ��λ��\n"); 
		scanf("%d", &deleteplace);	
		deleteLinkList(&linkList,deleteplace);
		outputLinkList(linkList);


	}
}
   
    return 0;
}

