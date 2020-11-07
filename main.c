#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int identifier; // �˵ı��
    int code; // �������е�����
    struct Node *next; // ָ����һ����
} Node;

Node *createRing( int ); // ��������ͷ���Ļ�������Ϊ�������������
void deleteNode( Node *, int ); // ɾ����㣬����Ϊ����Ҫɾ�Ľ��ı��
void initializeCodeOfPeople( Node *, int [], int ); // ��ʼ�����е�������,����Ϊ������̬���顢�����С
void reportNumber( Node *, int ); // ����

void display( Node * ); // �������еĽ�㣬����ʹ��

int main()
{
    int maxValue = 0; // ��������ֵ
    int numberOfPeople = 0; // ����
    Node *head = NULL; // ��
    int *codeArray = NULL; // ��̬���鴢�������˵�����

    printf( "���뱨������ֵ��������\n" );
    scanf( "%d%d", &maxValue, &numberOfPeople );
    printf( "���������˵����룺\n" );

    codeArray = ( int * )malloc( numberOfPeople * sizeof( int ) ); // Ϊ��̬��������㹻��С�Ŀռ�
    for ( int i = 0; i < numberOfPeople; ++i ) // ��ʼ����̬����
    {
        scanf( "%d", &codeArray[ i ] );
    }
    head = createRing( numberOfPeople ); // ����
    initializeCodeOfPeople( head, codeArray, numberOfPeople ); // ��ʼ�������˵�����

    printf( "������˵ĳ���˳��Ϊ��\n" );
    reportNumber( head, maxValue );

//    deleteNode( head, 1 );
//    display( head );

    return 0;
}

Node *createRing( int numberOfNodes )
{
    Node *head = NULL; // ͷָ�룬ָ���һ����㣬Ҳ���ǵ�һ����
    Node *temp = NULL; // һֱָ��մ����Ľ��
    Node *tail = NULL; // βָ�룬ָ�����һ�����

    head = ( Node * )malloc( sizeof( struct Node ) ); // ͷ�ڵ�
    if ( !head ) // �ж��Ƿ���䵽�ڴ�
    {
        printf( "�������ʧ�ܣ�" );
        exit( 0 );
    }
    head->identifier = 0; // ͷ����������
    head->code = numberOfNodes; // ͷ��������Ϊ�����˵ĸ���
    head->next = NULL;
    tail = head;

    for ( int i = 1; i <= numberOfNodes; ++i ) // ����
    {
        temp = ( Node * )malloc( sizeof( struct Node ) ); // ������
        if ( !temp ) // �ж��Ƿ���䵽�ڴ�
        {
            printf( "�������ʧ�ܣ�" );
            exit( 0 );
        }
        temp->identifier = i;
        temp->next = tail->next; // temp�����Զָ��ͷ�ڵ����һ�����
        tail->next = temp; // β�巨
        tail = temp; // βָ��ָ�����һ�����
    }
    tail->next = head->next; // ���һ�����ָ���һ����㣨����ͷ��㣩�����ɻ�

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
    int count = 0; // ����������
    Node *temp = head->next; // tempָ���һ�����
    Node *preTemp = head;

    while ( head->next != NULL ) // �ж��Ƿ������˳���
    {
        do
        {
            ++count;
            preTemp = temp; // preTempָ��������
            temp = temp->next; // tempָ��Ҫ��������
        } while ( count < mValue ); // �Ƿ񵽴ﱨ��ֵ
        mValue = preTemp->code; // �ó��е��˵����������±���ֵ
        deleteNode( head, preTemp->identifier ); // ɾ���ﵽ��������ֵ�Ľ��
        count = 0;
    }
}

void deleteNode( Node *head, int number )
{
    Node *temp = head->next; // ָ���һ����
    Node *preTemp = head;

    while ( temp->identifier != number ) // �Ƿ��Ƕ�Ӧ����
    {
        preTemp = temp;
        temp = temp->next;
    }
    if ( head->next->identifier == number ) // ɾ����һ�����
    {
        Node *tmp = temp->next;
        while ( tmp->next->identifier != temp->identifier ) // �ҵ����һ�����
        {
            tmp = tmp->next; // tmpָ�����һ�����
        }
        tmp->next = temp->next;
        preTemp->next = temp->next;
    }
    else
        preTemp->next = temp->next;
    printf( "%d ", temp->identifier ); // ������
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
    } while ( temp->identifier != head->next->identifier ); // temp�Ƿ�ָ���һ�����
}
