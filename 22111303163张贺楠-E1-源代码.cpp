#include <stdio.h>
#include <stdlib.h>
#define maxnum 10000

typedef struct //图书信息定义
{
    char no[20];      //图书 ISBN
    char name[50];    //图书名字
    float price;      //图书价格
    float unrealprice; //图书更改后价格
} Book;

typedef struct
{
    Book *elem;
    int length;
    int maxsize;

} Sqlist;

typedef struct LNode
{
    Book data;         //结点的数据域
    int numsize;       //结点的长度
    struct LNode *next; //结点的指针域
} LNode, *LinkList; //LinkList 为指向结构体 LNode 的指针类型

void initsqlist(Sqlist *sqlist)
{
    (*sqlist).elem = (Book *)malloc(sizeof(Book) * maxnum);
    (*sqlist).maxsize = maxnum;
    (*sqlist).length = 0;
}

void inputSqlist(Sqlist *sqlist)
{
    // 加入信息
    int i;
    for (i = 0; i < maxnum; i++)
    {
        scanf("%s %s %f", (*sqlist).elem[i].no, (*sqlist).elem[i].name, &(*sqlist).elem[i].price);

        // 判断是否输入完毕
        if ((*sqlist).elem[i].no[0] == '0' && (*sqlist).elem[i].name[0] == '0' && (*sqlist).elem[i].price == 0.0)
        {
            break;
        }
    }
    // 统计有多少本书
    (*sqlist).length = i;
}

void inputSqlistnum(Sqlist *sqlist, int num)
{
    // 加入信息
    int i;
    for (i = 0; i < num; i++)
    {
        scanf("%s %s %f", (*sqlist).elem[i].no, (*sqlist).elem[i].name, &(*sqlist).elem[i].price);
    }
    // 统计有多少本书
    (*sqlist).length = num;
}

void sqlistfindmax(Sqlist *sqlist)
{
    float max = (*sqlist).elem[0].price;
    int count = 0; //统计有几本
    // 寻找最贵的书
    for (int i = 1; i < (*sqlist).length; i++)
    {
        if ((*sqlist).elem[i].price > max)
        {
            max = (*sqlist).elem[i].price;
            count = 1;
        }
        else if ((*sqlist).elem[i].price == max)
        {
            count++; // 增加数量
        }
    }

    // 输出最贵的书的信息
    printf("最贵的书的价格为%.2f,共有%d本，以下是信息:\n", max, count);
    for (int i = 0; i < (*sqlist).length; i++)
    {
        if ((*sqlist).elem[i].price == max)
        {
            printf("书号ISBN: %s, 书名: %s, 价格为: %.2f\n", (*sqlist).elem[i].no, (*sqlist).elem[i].name, (*sqlist).elem[i].price);
        }
    }
}

void UPForSqlist(Sqlist *sqlist)
{
    // 初始化平均价格
    float sum = 0.0;
    for (int i = 0; i < (*sqlist).length; i++)
    {
        sum += (*sqlist).elem[i].price;
    }
    float averagePrice = sum / (*sqlist).length;

    // 更新价格
    for (int i = 0; i < (*sqlist).length; i++)
    {
        if ((*sqlist).elem[i].price < averagePrice)
        {
            // 涨价20%
            (*sqlist).elem[i].unrealprice = (*sqlist).elem[i].price * 1.2;
        }
        else
        {
            // 涨价 10%
            (*sqlist).elem[i].unrealprice = (*sqlist).elem[i].price * 1.1;
        }
    }
    printf("平均价格为%.2f\n", averagePrice);
    for (int i = 0; i < (*sqlist).length; i++)
        printf("第%d本书的信息为: 书号ISBN: %s, 书名: %s, 修改后的价格为: %.2f, 原来的价格为: %.2f\n", i + 1, (*sqlist).elem[i].no, (*sqlist).elem[i].name, (*sqlist).elem[i].unrealprice, (*sqlist).elem[i].price);
}

void insertsqlist(Sqlist *sqlist, int insertplace)
{
    if (insertplace < 1 || insertplace > (*sqlist).length + 1)
    {
        printf("插入位置不合理，请重新输入\n");
        return;
    }

    Book newBook; // 输入新书的信息
    scanf("%s %s %f", newBook.no, newBook.name, &newBook.price);

    // 插入新书到指定位置
    for (int i = (*sqlist).length; i >= insertplace; i--)
    {
        (*sqlist).elem[i] = (*sqlist).elem[i - 1];
    }
    (*sqlist).elem[insertplace - 1] = newBook;
    (*sqlist).length++;

    printf("插入成功\n");
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
    printf("共有书本%d本\n", sqlist.length);
    for (int i = 0; i < sqlist.length; i++)
        printf("第%d本书的信息为: 书号ISBN: %s, 书名: %s, 价格: %.2f\n", i + 1, sqlist.elem[i].no, sqlist.elem[i].name, sqlist.elem[i].price);
}

void initLinkList(LinkList *linkList)
{
    *linkList = NULL;
}

void insertLinkList(LinkList *linkList, int insertplace, Book newBook)
{
    LNode *newNode = (LNode *)malloc(sizeof(LNode)); // 为新书节点分配内存
    if (newNode == NULL)
    {
        printf("内存分配失败\n");
        return;
    }

    newNode->data = newBook;
    newNode->next = NULL;
    newNode->numsize = 1;
    if (insertplace == 1 || *linkList == NULL)
    {
        // 插入到链表头部
        newNode->next = *linkList;
        *linkList = newNode;
        (*linkList)->numsize=1;
    }
    else
    {
        // 插入到链表中间或尾部
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
            printf("插入位置无效\n");
            free(newNode); // 释放新书节点的内存
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

        // 输入图书信息
        scanf("%s %s %f", newBook.no, newBook.name, &newBook.price);

        // 判断是否输入完毕
        if (newBook.no[0] == '0' && newBook.name[0] == '0' && newBook.price == 0.0)
        {
            break;
        }

        // 插入新节点到链表尾部
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

        // 输入图书信息
        scanf("%s %s %f", newBook.no, newBook.name, &newBook.price);
        // 插入新节点到链表尾部
        insertLinkList(linkList, i, newBook);
        i++;
    }
}
void deleteLinkList(LinkList *linkList, int deleteplace)
{
    if (deleteplace < 1 || *linkList == NULL)
    {
        printf("删除位置不合理，请重新输入\n");
        return;
    }

    // 删除头节点
    if (deleteplace == 1)
    {
        LNode *temp = *linkList;
        *linkList = (*linkList)->next;
        free(temp);
         (*linkList)->numsize--;
    }
    else
    {
        // 删除中间或尾部节点
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
            printf("删除位置不合理，请重新输入\n");
            return;
        }
    }

    printf("删除成功\n");
}


void UPForLinklist(LinkList linkList)
{
    // 初始化平均价格
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

    // 更新价格
    current = linkList;
    while (current != NULL)
    {
        if (current->data.price < averagePrice)
        {
            // 涨价20%
            current->data.unrealprice = current->data.price * 1.2;
        }
        else
        {
            // 涨价 10%
            current->data.unrealprice = current->data.price * 1.1;
        }
        current = current->next;
    }

    printf("平均价格为%.2f\n", averagePrice);
    current = linkList;
    int i = 1;
    while (current != NULL)
    {
        printf("第%d本书的信息为: 书号ISBN: %s, 书名: %s, 修改后的价格为: %.2f, 原来的价格为: %.2f\n", i, current->data.no, current->data.name, current->data.unrealprice, current->data.price);
        current = current->next;
        i++;
    }
}

void linkListFindMax(LinkList linkList)
{
    if (linkList == NULL || linkList->numsize == 0)
    {
        printf("链表为空\n");
        return;
    }

    float max = linkList->data.price;
    int count = 0; // 统计有几本

    // 寻找最贵的书
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
            count++; // 增加数量
        }

        current = current->next;
    }

    // 输出最贵的书的信息
    printf("最贵的书的价格为%.2f, 共有%d本，以下是信息:\n", max, count);

    current = linkList;
    int i = 1;
    while (current != NULL)
    {
        if (current->data.price == max)
        {
            printf("第%d本书的信息为: 书号ISBN: %s, 书名: %s, 价格为: %.2f\n", i, current->data.no, current->data.name, current->data.price);
        i++; 
		}

        current = current->next;
       
    }
}

void outputLinkList(LinkList linkList)
{
    printf("共有书本%d本\n", linkList->numsize);
    LNode *current = linkList;
    int i = 1;
    while (current != NULL)
    {
        printf("第%d本书的信息为: 书号ISBN: %s, 书名: %s, 价格: %.2f\n", i, current->data.no, current->data.name, current->data.price);
        current = current->next;
        i++;
    }
}

int main()
{   printf("本程序用于图书馆的多种操作，包括插入图书，删除图书，查找最贵的书，修改价格，输出图书信息。\n注意：一.所有的输入信息都以空格为间隔，且保持三个空格，否则可能会出现错误\n      二.链表也均采用尾插法\n操作都分为两类：\n1.顺序表操作\n2.链表操作\n请输入选择的序号");
    int choose=0;
	scanf("%d", &choose);
	if(choose==1)
   { Sqlist sqlist;
     initsqlist(&sqlist);
	printf("您选的是顺序表操作，分为以下几种功能，请选择序号：\n");
	printf("1 统计图书表中的图书个数，同时逐行输出每本图书的信息图书信息表的创建和输出。\n");
	printf("2 计算所有图书对的平均价格，将所有低于平均价格的图书价格提高 20，所有高于或等于平均价格的图书价格提高 10。最后，逐行输出价格修改后的图书信息。\n");
    printf("3 查找价格最高的图书，输出相应图书的信息。\n");
    printf("4 根据指定的待入库的新图书的位置和信息，将新图书插入到图书表中指定的位置上。最后，输出新图书入库后所有图书的信息。\n");
    printf("5 根据指定的待出库的旧图书的位置，将该图书从图书表中删除。最后输出该图书出库后的所有图书的信息。\n请输入选择的序号\n");
    int choosemin=0;
	scanf("%d", &choosemin);
	if(choosemin==1)
	{printf("请输入图书信息以0 0 0结尾\n");
	inputSqlist(&sqlist);
	 outputSqlist(sqlist);
	}
	else if(choosemin==2)
	{ printf("请输入图书信息以0 0 0结尾\n");
	  inputSqlist(&sqlist);
	  UPForSqlist(&sqlist);	
	}
	else if(choosemin==3)
	{  printf("请输入图书数量和图书信息\n"); 
		int num;
		scanf("%d", &num);	
		inputSqlistnum(&sqlist,num);
		sqlistfindmax(&sqlist);
	}
	else if(choosemin==4)
	{  int num;
	   printf("请输入图书数量和图书信息\n"); 
		scanf("%d", &num);	
		inputSqlistnum(&sqlist,num);
		int insertplace;
		printf("请输入插入位置和插入图书信息\n"); 
		scanf("%d", &insertplace);	
		insertsqlist(&sqlist,insertplace);
		outputSqlist(sqlist);
	}
	else if(choosemin==5)
	{   printf("请输入图书数量和图书信息\n"); 
		int num;
		scanf("%d", &num);	
		inputSqlistnum(&sqlist,num);
		int deleteplace;
		printf("请输入删除位置\n"); 
		scanf("%d", &deleteplace);	
		deletesqlist(&sqlist,deleteplace);
		outputSqlist(sqlist);
	}
   }
	else
	{ LinkList linkList;
	 initLinkList(&linkList);
	printf("您选的是链表操作，分为以下几种功能，请选择序号：\n");
	printf("1 统计图书表中的图书个数，同时逐行输出每本图书的信息图书信息表的创建和输出。\n");
	printf("2 计算所有图书对的平均价格，将所有低于平均价格的图书价格提高 20，所有高于或等于平均价格的图书价格提高 10。最后，逐行输出价格修改后的图书信息。\n");
    printf("3 查找价格最高的图书，输出相应图书的信息。\n");
    printf("4 根据指定的待入库的新图书的位置和信息，将新图书插入到图书表中指定的位置上。最后，输出新图书入库后所有图书的信息。\n");
    printf("5 根据指定的待出库的旧图书的位置，将该图书从图书表中删除。最后输出该图书出库后的所有图书的信息。\n请输入选择的序号\n");
    int choosemin=0;
	if(choosemin==1)
	{printf("请输入图书信息以0 0 0结尾\n");
	 inputLinkList(&linkList);
	 outputLinkList(linkList);
	}
	else if(choosemin==2)
	{ printf("请输入图书信息以0 0 0结尾\n");
	  inputLinkList(&linkList);
	  UPForLinklist(linkList);	
	}
	else if(choosemin==3)
	{   printf("请输入图书数量和图书信息\n"); 
		int num;
		scanf("%d", &num);	
		inputLinkListNum(&linkList,num);
		linkListFindMax(linkList);
	}
	else if(choosemin==4)
	{  int num;
	   printf("请输入图书数量和图书信息\n"); 
		scanf("%d", &num);	
		inputLinkListNum(&linkList,num);
		int insertplace;
		printf("请输入插入位置和插入图书信息\n"); 
		scanf("%d", &insertplace);
		Book newbook;
		scanf("%s %s %f", newbook.no, newbook.name, &newbook.price);	
		insertLinkList(&linkList,insertplace,newbook);
		outputLinkList(linkList);
	}
	else if(choosemin==5)
	{   printf("请输入图书数量和图书信息\n"); 
		int num;
		scanf("%d", &num);	
		inputLinkListNum(&linkList,num);
		int deleteplace;
		printf("请输入删除位置\n"); 
		scanf("%d", &deleteplace);	
		deleteLinkList(&linkList,deleteplace);
		outputLinkList(linkList);


	}
}
   
    return 0;
}

