#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int identifier; // 人的编号
    int code; // 人所持有的密码
    struct Node *next; // 指向下一个人
} Node;

Node *createRing( int ); // 创建带有头结点的环，参数为人数（结点数）
void deleteNode( Node *, int ); // 删除结点，参数为环、要删的结点的编号
void initializeCodeOfPeople( Node *, int [], int ); // 初始化环中的密码域,参数为环、动态数组、数组大小
void reportNumber( Node *, int ); // 报数

void display( Node * ); // 遍历环中的结点，测试使用

int main()
{
    int maxValue = 0; // 报数上限值
    int numberOfPeople = 0; // 人数
    Node *head = NULL; // 环
    int *codeArray = NULL; // 动态数组储存所有人的密码

    printf( "输入报数上限值和人数：\n" );
    scanf( "%d%d", &maxValue, &numberOfPeople );
    printf( "输入所有人的密码：\n" );

    codeArray = ( int * )malloc( numberOfPeople * sizeof( int ) ); // 为动态数组分配足够大小的空间
    for ( int i = 0; i < numberOfPeople; ++i ) // 初始化动态数组
    {
        scanf( "%d", &codeArray[ i ] );
    }
    head = createRing( numberOfPeople ); // 建环
    initializeCodeOfPeople( head, codeArray, numberOfPeople ); // 初始化所有人的密码

    printf( "各编号人的出列顺序为：\n" );
    reportNumber( head, maxValue );

//    deleteNode( head, 1 );
//    display( head );

    return 0;
}

Node *createRing( int numberOfNodes )
{
    Node *head = NULL; // 头指针，指向第一个结点，也就是第一个人
    Node *temp = NULL; // 一直指向刚创建的结点
    Node *tail = NULL; // 尾指针，指向最后一个结点

    head = ( Node * )malloc( sizeof( struct Node ) ); // 头节点
    if ( !head ) // 判断是否分配到内存
    {
        printf( "结点申请失败！" );
        exit( 0 );
    }
    head->identifier = 0; // 头结点的特殊标记
    head->code = numberOfNodes; // 头结点的密码为所有人的个数
    head->next = NULL;
    tail = head;

    for ( int i = 1; i <= numberOfNodes; ++i ) // 建环
    {
        temp = ( Node * )malloc( sizeof( struct Node ) ); // 申请结点
        if ( !temp ) // 判断是否分配到内存
        {
            printf( "结点申请失败！" );
            exit( 0 );
        }
        temp->identifier = i;
        temp->next = tail->next; // temp结点永远指向头节点的下一个结点
        tail->next = temp; // 尾插法
        tail = temp; // 尾指针指向最后一个结点
    }
    tail->next = head->next; // 最后一个结点指向第一个结点（不是头结点），构成环

    return head;
}

void initializeCodeOfPeople( Node *head, int array[], int size )
{
    Node *temp;

    temp = head->next;

    for ( int i = 0; i < size; ++i )
    {
        temp->code = array[ i ];
        temp = temp->next;
    }
}

void reportNumber( Node *head, int mValue )
{
    int count = 0; // 报数计数器
    Node *temp = head->next; // temp指向第一个结点
    Node *preTemp = head;

    while ( head->next != NULL ) // 判断是否所有人出列
    {
        do
        {
            ++count;
            preTemp = temp; // preTemp指向报数的人
            temp = temp->next; // temp指向将要报数的人
        } while ( count < mValue ); // 是否到达报数值
        mValue = preTemp->code; // 用出列的人的密码来更新报数值
        deleteNode( head, preTemp->identifier ); // 删除达到报数上限值的结点
        count = 0;
    }
}

void deleteNode( Node *head, int number )
{
    Node *temp = head->next; // 指向第一个人
    Node *preTemp = head;

    while ( temp->identifier != number ) // 是否是对应的人
    {
        preTemp = temp;
        temp = temp->next;
    }
    if ( head->next->identifier == number ) // 删除第一个结点
    {
        Node *tmp = temp->next;
        while ( tmp->next->identifier != temp->identifier ) // 找到最后一个结点
        {
            tmp = tmp->next; // tmp指向最后一个结点
        }
        tmp->next = temp->next;
        preTemp->next = temp->next;
    }
    else
        preTemp->next = temp->next;
    printf( "%d ", temp->identifier ); // 输出编号
    if ( temp->next == temp )
        head->next =  NULL;
    free( temp );
}

void display( Node *head )
{
    Node *temp;

    temp = head->next;

    if ( head->next == NULL )
    {
        printf( "0" );
        return;
    }
    do
    {
        printf( "%d ", temp->identifier );
        temp = temp->next;
    } while ( temp->identifier != head->next->identifier ); // temp是否指向第一个结点
}
