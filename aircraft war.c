#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#define framex 5   //����������Ϸ���ֱ߽�
#define framey 5   //ͬ��
#define wide 20    //ͬ��
#define high 20    //ͬ��
//ȫ�ֱ���
int iweapon=0;
int flag=0;
int T;
int iflag;
int M=10,M1=10,m=10;
int e1=8,e2=3,e3=2;
int enemy_x1[8],enemy_y1[8];//�л�һ�ŵ�����
int enemy_x2[3],enemy_y2[3];//�л����ŵ�����
int enemy_x3[2],enemy_y3[2];//�л����ŵ�����
int boss_x1,boss_y1;//bossһ�ŵ�����
int life1=51;
int life2=60;
int life3=100;
int boss_x2,boss_y2;//boss���ŵ�����
int boss_x3,boss_y3;//boss���ŵ�����
int a[47][25]={0};//��ά���鴢����Ϸ�ڵ����Ԫ��1����ҷɻ� 2���ӵ� 3����ʯ 4�ǵл�1 5�ǵл�2 6�ǵл�3 7��BOSS1 8��BOSS2 9��BOSS3 10�ǵ����ӵ�
int i,j,I,J;//�ṩѭ��ʹ��
int ispeed=7000;//�л������ٶ�
int speed=5;
char weapon[3][10]={{"normal"},{"double"},{"strong"}};//��������
int level=1;//��Ϸ�ؿ�
int marks=0;//��Ϸ�÷�
int Nirvana[2]={3,3};//��ɱ��������
void cursorxy(HANDLE hout,int x,int y)//������ƶ������꣨x,y)
{
    COORD pos;
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(hout,pos);
}
void hidden()//���ع��
{
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cci;
GetConsoleCursorInfo(hout,&cci);
cci.bVisible=0;
SetConsoleCursorInfo(hout,&cci);
}
void cover(HANDLE hout)//���� ��Ϸ�Ļ�����Ϣ
{
    cursorxy(hout,framex+wide,framey);
    printf("Hello! welcome to the game----SHOOTING!");
    cursorxy(hout,framex+wide,framey*2);
    printf("��ر��������뷨");//�ر��������뷨��ʾ
    cursorxy(hout,framex+wide*3+20,framey+high);
    printf("������:Rayest Geeta");
    cursorxy(hout,framex+wide*3+20,framey+2+high);
    printf("ʱ��:2017.12.15");
    char a;
    a=getchar();
    system("cls");//����
}
struct Plane{//����ɻ��Ľṹ��
        int x[3],X[3];
        int y[3],Y[3];
        int z[3],Z[3];
};
void makefarme()//��Ϸ���
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    cursorxy(hout,framex+wide*2+5,framey);
    printf( "  SHOOTING");
    cursorxy(hout,framex+wide*2+5,framey+3);
    printf("��Ϸ������ʾ:���������WASD�����Ʒɻ��˶�");//��Ϸ�淨��ʾ
    cursorxy(hout,framex+wide*2+5,framey+5);
    printf("�ո�:���");
    cursorxy(hout,framex+wide*2+5,framey+9);
    printf("������ʾ:$:��ʯ  Z Y:���ӱ�ɱ�� &:�л���ֹ *:��������");
    cursorxy(hout,framex+wide*2+5,framey+7);
    printf("Z X����ʩչǿ����ɱ�� Z ���һ�ŵ��� Y ȫ����ʯ�Զ���ը");
    for(i=0;i<wide*2+1;i++){//5----46
        cursorxy(hout,framex+i,framey);
        printf("-");//��Ϸ���Ͽ��
    }
    for(i=0;i<wide*2+2;i++){//5---47
        cursorxy(hout,framex+i,framey+high);
        printf("-");//��Ϸ���¿��

    }
    for(i=0;i<high;i++){//5----20
        cursorxy(hout,framex,framey+i);
        printf("��");//��Ϸ����߽�
    }
    for(i=0;i<high;i++){
        cursorxy(hout,framex+wide*2+1,framey+i);
        printf("��");//��Ϸ���ұ߽�
    }
}
void infor(){//��Ϸ��Ϣ
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    cursorxy(hout,framex+wide*2+5,framey+13);
    printf("��������:%8s",weapon[iweapon]);//��ʾ��������
    cursorxy(hout,framex+wide*2+5,framey+15);
    printf("�ؿ�:%d",level);//��ʾ�ؿ�
    cursorxy(hout,framex+wide*2+5,framey+17);
    printf("����:%d",marks);//��ʾ����
    cursorxy(hout,framex+wide*2+5,framey+19);
    printf("��ɱ��:Z:%d X:%d",Nirvana[0],Nirvana[1]);//��ʾ��ɱ������
    for(i=7;i<46;i++)
        for(j=6;j<25;j++)
        {
            if(a[i][j]==0)
            {
                cursorxy(hout,i,j);
                printf(" ");
            }
            if(a[i][j]==2)
            {
                cursorxy(hout,i,j);
                printf("|");
            }
            if(a[i][j]==3)
            {
                cursorxy(hout,i,j);
                printf("$");
            }
            if(a[i][j]==10)
            {
                cursorxy(hout,i,j);
                printf("|");
            }
            if(a[i][j]==-1)
            {
                cursorxy(hout,i,j);
                printf("Z");
            }
            if(a[i][j]==-2)
            {
                cursorxy(hout,i,j);
                printf("X");
            }
            if(a[i][j]==-3)
            {
                cursorxy(hout,i,j);
                printf("*");
            }
            if(a[i][j]==-4)
            {
                cursorxy(hout,i,j);
                printf("&");
            }
        }
}
void makeplane(HANDLE hout,struct Plane* plane)//�����ӡ�ɻ�
{
    cursorxy(hout,plane->x[1],plane->X[1]);
    a[plane->x[1]][plane->X[1]]=1;
    printf("_");//�ɻ�ͷ
    cursorxy(hout,plane->z[0],plane->Z[0]);
    printf("-");//�ɻ�����
    a[plane->z[0]][plane->Z[0]]=1;
    cursorxy(hout,plane->z[2],plane->Z[2]);
    printf("-");
    a[plane->z[2]][plane->Z[2]]=1;
    for(i=0;i<3;i++)//�ɻ�β��
    {
        cursorxy(hout,plane->y[i],plane->Y[i]);
        printf("-");
        a[plane->y[i]][plane->Y[i]]=1;
    }
}
void initplane(struct Plane* plane)//��ʼ���ɻ�  ȷ���ɻ��ĳ�ʼλ��
{
    plane->x[1]=wide;//�ɻ�ͷ��������
    plane->X[1]=framey+high-3;//������
    plane->z[0]=wide-1;//�ɻ��������� ��ͬ
    plane->Z[0]=framey+high-1;
    plane->z[2]=wide+1;
    plane->Z[2]=framey+high-1;
    for(i=0;i<3;i++)//�ɻ�β������
    {
        plane->y[i]=wide+i-1;
        plane->Y[i]=framey+high-2;
    }
    a[10][6]=3;//��ʼ����ʯλ��  ʵ��׶�
}
void exe(struct Plane* plane)//�����ϸ�ģ��
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    cursorxy(hout,plane->x[1],plane->X[1]);
    printf(" ");//����һ���ƶ�ǰ�ķɻ�����
    a[plane->x[1]][plane->X[1]]=0;//ͷ��
    printf(" ");
    cursorxy(hout,plane->z[0],plane->Z[0]);
    printf(" ");
    a[plane->z[0]][plane->Z[0]]=0;//����
    cursorxy(hout,plane->z[2],plane->Z[2]);
    printf(" ");
    a[plane->z[2]][plane->Z[2]]=0;
    for(i=0;i<3;i++)//β��
    {
        cursorxy(hout,plane->y[i],plane->Y[i]);
        printf(" ");
        a[plane->y[i]][plane->Y[i]]=0;
    }
}
void limitplane(struct Plane* plane)//��Ϸ����  ���ɻ���������Ϸ�����
{
    if(plane->x[1]<framex+3)//�ɻ�ײ����߽�  �����зɻ�λ�ò���
    {
        plane->x[1]=plane->x[1]+1;
        plane->z[0]=plane->z[0]+1;
        plane->z[2]=plane->z[2]+1;
        for(i=0;i<3;i++)
        {
            plane->y[i]=plane->y[i]+1;
        }
    }
    if(plane->x[1]>=framey+wide*2)//�ɻ�ײ���±߽�  ͬ��
    {
        plane->x[1]=plane->x[1]-1;
        plane->z[0]=plane->z[0]-1;
        plane->z[2]=plane->z[2]-1;
        for(i=0;i<3;i++)
        {
            plane->y[i]=plane->y[i]-1;
        }
    }
    if(plane->X[1]<framey+1)//�ɻ�ײ���ϱ߽�  ͬ��
    {
        plane->X[1]=plane->X[1]+1;
        plane->Z[0]=plane->Z[0]+1;
        plane->Z[2]=plane->Z[2]+1;
        for(i=0;i<3;i++)
        {
            plane->Y[i]=plane->Y[i]+1;
        }
    }
    if(plane->X[1]>=framey+high-2)//�ɻ�ײ����߽� ͬ��
    {
        plane->X[1]=plane->X[1]-1;
        plane->Z[0]=plane->Z[0]-1;
        plane->Z[2]=plane->Z[2]-1;
        for(i=0;i<3;i++)
        {
            plane->Y[i]=plane->Y[i]-1;
        }
    }
}
void enemy1()//������ʯ
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    int k;
    for(k=0;k<8;k++)
    {
        enemy_x1[k] = rand()%39+7;
		enemy_y1[k] = rand()%2+6;
		a[enemy_x1[k]][enemy_y1[k]] = 3;
        cursorxy(hout,enemy_x1[k],framey+1);
        printf("$");//��ӡ��ʯ
    }
}
void enemy2()//�л�2����
{
    int k;
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    for(i=0;i<3;i++)
    {
        enemy_x2[i]=rand()%31+10;
        k=enemy_x2[i];
        enemy_y2[i]=framey+2;
        if((!a[k][framey+2])&&(!a[k-1][framey+1])&&(!a[k+1][framey+1])&&(!a[k][framey+1]))
        {
            a[k][framey+2]=4;
            cursorxy(hout,k,framey+2);
            printf("|");
            cursorxy(hout,k-1,framey+1);
            printf("\\");
            a[k-1][framey+1]=4;
            cursorxy(hout,k+1,framey+1);
            printf("/");
            a[k+1][framey+1]=4;
            cursorxy(hout,k,framey+1);
            printf("-");
            a[k][framey+1]=4;
        }
    }
}
void enemy2no(int x,int y)
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    cursorxy(hout,x,y);
    printf(" ");
    a[x][y]=0;
    cursorxy(hout,x-1,y-1);
    printf(" ");
    a[x-1][y-1]=0;
    cursorxy(hout,x+1,y-1);
    printf(" ");
    a[x+1][y-1]=0;
    cursorxy(hout,x,y-1);
    printf(" ");
    a[x][y-1]=0;
}
void enemy2move(int x,int y)
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    if(y>15&&x<40)
    {
        cursorxy(hout,x+1,y+1);
        printf("|");
        a[x+1][y+1]=4;
        cursorxy(hout,x,y);
        printf("\\");
        a[x][y]=4;
        cursorxy(hout,x+2,y);
        printf("/");
        a[x+2][y]=4;
        cursorxy(hout,x+1,y);
        printf("-");
        a[x+1][y]=4;
    }
    else
    {
        cursorxy(hout,x,y+1);
        printf("|");
        a[x][y+1]=4;
        cursorxy(hout,x-1,y);
        printf("\\");
        a[x-1][y]=4;
        cursorxy(hout,x+1,y);
        printf("/");
        a[x+1][y]=4;
        cursorxy(hout,x,y);
        printf("-");
        a[x][y]=4;
    }
}
void enemy3()//�л�3����
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    int k;
    for(i=0;i<2;i++)
    {
        enemy_x3[i]=rand()%31+10;
        k=enemy_x3[i];
        enemy_y3[i]=framey+2;
        if((!a[k][framey+2])&&(!a[k-1][framey+2])&&(!a[k+1][framey+2])&&(!a[k+1][framey+1])&&(!a[k-1][framey+1]))
        {
            a[k][framey+2]=5;
            cursorxy(hout,k,framey+2);
            printf("|");
            cursorxy(hout,k-1,framey+2);
            printf("<");
            a[k-1][framey+2]=5;
            cursorxy(hout,k+1,framey+2);
            printf(">");
            a[k+1][framey+2]=5;
            cursorxy(hout,k-1,framey+1);
            printf("+");
            a[k-1][framey+1]=5;
            cursorxy(hout,k+1,framey+1);
            printf("+");
            a[k+1][framey+1]=5;
        }
    }
}
void enemy3no(int x,int y)
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    cursorxy(hout,x,y);
    printf(" ");
    a[x][y]=0;
    cursorxy(hout,x-1,y);
    printf(" ");
    a[x-1][y]=0;
    cursorxy(hout,x+1,y);
    printf(" ");
    a[x+1][y]=0;
    cursorxy(hout,x-1,y-1);
    printf(" ");
    a[x-1][y-1]=0;
    cursorxy(hout,x+1,y-1);
    printf(" ");
    a[x+1][y-1]=0;
}
void enemy3move(int x,int y)
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    if(y<15&&y>10&&x>8)
    {
        cursorxy(hout,x-1,y+1);
        printf("|");
        a[x-1][y+1]=5;
        cursorxy(hout,x-2,y+1);
        printf("<");
        a[x-2][y+1]=5;
        cursorxy(hout,x,y+1);
        printf(">");
        a[x][y+1]=5;
        cursorxy(hout,x-2,y);
        printf("+");
        a[x-2][y]=5;
        cursorxy(hout,x,y);
        printf("+");
        a[x][y]=5;
    }
    else
    {
        cursorxy(hout,x,y+1);
        printf("|");
        a[x][y+1]=5;
        cursorxy(hout,x-1,y+1);
        printf("<");
        a[x-1][y+1]=5;
        cursorxy(hout,x+1,y+1);
        printf(">");
        a[x+1][y+1]=5;
        cursorxy(hout,x-1,y);
        printf("+");
        a[x-1][y]=5;
        cursorxy(hout,x+1,y);
        printf("+");
        a[x+1][y]=5;
    }
}
void boss1()//boss1����
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    a[20+framex][framey+4]=6;
    boss_x1=20+framex;
    boss_y1=framey+4;
    for(i=14+framex;i<27+framex;i++)
    {
        cursorxy(hout,i,framey+3);
        printf("*");
        a[i][framey+3]=6;
    }
    for(i=17+5;i<24+framex;i++)
    {
        cursorxy(hout,i,framey+2);
        printf("=");
        a[i][framey+2]=6;
    }
    for(i=18+5;i<23+5;i+=2)
    {
        cursorxy(hout,i,framey+4);
        printf("|");
        a[i][framey+4]=6;
    }
    cursorxy(hout,25,framey+1);
    printf("0");
    a[25][framey+1]=6;
}
void boss1no(int x,int y)
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    a[x][y]=0;
    for(i=x-6;i<x+7;i++)
    {
        cursorxy(hout,i,y-1);
        printf(" ");
        a[i][y-1]=0;
    }
    for(i=x-3;i<x+4;i++)
    {
        cursorxy(hout,i,y-2);
        printf(" ");
        a[i][y-2]=0;
    }
    for(i=x-2;i<x+3;i+=2)
    {
        cursorxy(hout,i,y);
        printf(" ");
        a[i][y]=0;
    }
    cursorxy(hout,x,y-3);
    printf(" ");
    a[x][y-3]=0;
}
void boss1move(int x,int y)
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    if(M>0)
    {
        M--;
        a[x-1][y]=6;
        boss_x1--;
        for(i=x-7;i<x+6;i++)
        {
            cursorxy(hout,i,y-1);
            printf("*");
            a[i][framey+3]=6;
        }
        for(i=x-4;i<x+3;i++)
        {
            cursorxy(hout,i,y-2);
            printf("=");
            a[i][framey+2]=6;
        }
        for(i=x-3;i<x+2;i+=2)
        {
            cursorxy(hout,i,y);
            printf("|");
            a[i][framey+4]=6;
        }
        cursorxy(hout,x-1,y-3);
        printf("0");
        a[x-1][framey+1]=6;
    }
    else
    {
        boss_x1++;
        a[x+1][framey+4]=6;
        for(i=x-5;i<x+8;i++)
        {
            cursorxy(hout,i,y-1);
            printf("*");
            a[i][framey+3]=6;
        }
        for(i=x-2;i<x+5;i++)
        {
            cursorxy(hout,i,y-2);
            printf("=");
            a[i][framey+2]=6;
        }
        for(i=x-1;i<x+4;i+=2)
        {
            cursorxy(hout,i,y);
            printf("|");
            a[i][framey+4]=6;
        }
        cursorxy(hout,x+1,y-3);
        printf("0");
        a[x+1][framey+1]=6;
        M--;
        if(M==-20)
            M=20;
    }
}
void boss2()//boss2����
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    a[25][framey+4]=7;
    boss_x2=25;
    boss_y2=framey+4;
    for(i=23;i<28;i++)
    {
        cursorxy(hout,i,framey+1);
        printf("*");
        a[i][framey+1]=7;
    }
    for(i=19;i<32;i++)
    {
        cursorxy(hout,i,framey+2);
        printf("=");
        a[i][framey+2]=7;
    }
    for(i=23;i<28;i++)
    {
        cursorxy(hout,i,framey+3);
        printf("+");
        a[i][framey+3]=7;
    }
    for(i=23;i<28;i+=2)
    {
        cursorxy(hout,i,framey+4);
        printf("|");
        a[i][framey+4]=7;
    }
}
void boss2no(int x,int y)
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    a[x][y]=0;
    for(i=x-2;i<x+3;i++)
    {
        cursorxy(hout,i,framey+1);
        printf(" ");
        a[i][framey+1]=0;
    }
    for(i=x-6;i<x+7;i++)
    {
        cursorxy(hout,i,framey+2);
        printf(" ");
        a[i][framey+2]=0;
    }
    for(i=x-2;i<x+3;i++)
    {
        cursorxy(hout,i,framey+3);
        printf(" ");
        a[i][framey+3]=0;
    }
    for(i=x-2;i<x+3;i+=2)
    {
        cursorxy(hout,i,framey+4);
        printf(" ");
        a[i][framey+4]=0;
    }
}
void boss2move(int x,int y)
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    if(M1>0)
    {
        M1--;
        a[x-1][y]=7;
        boss_x2--;
        for(i=x-2-1;i<x+3-1;i++)
        {
            cursorxy(hout,i,y-3);
            printf("*");
            a[i][framey+1]=7;
        }
        for(i=x-6-1;i<x+7-1;i++)
        {
            cursorxy(hout,i,y-2);
            printf("=");
            a[i][framey+2]=7;
        }
        for(i=x-2-1;i<x+3-1;i++)
        {
            cursorxy(hout,i,y-1);
            printf("+");
            a[i][framey+3]=7;
        }
        for(i=x-2-1;i<x+3-1;i+=2)
        {
            cursorxy(hout,i,y);
            printf("|");
            a[i][framey+4]=7;
        }
    }
    else
    {
        boss_x2++;
        M1--;
        for(i=x-2+1;i<x+3+1;i++)
        {
            cursorxy(hout,i,y-3);
            printf("*");
            a[i][framey+1]=7;
        }
        for(i=x-6+1;i<x+7+1;i++)
        {
            cursorxy(hout,i,y-2);
            printf("=");
            a[i][framey+2]=7;
        }
        for(i=x-2+1;i<x+3+1;i++)
        {
            cursorxy(hout,i,y-1);
            printf("+");
            a[i][framey+3]=7;
        }
        for(i=x-2+1;i<x+3+1;i+=2)
        {
            cursorxy(hout,i,y);
            printf("|");
            a[i][framey+4]=7;
        }
        a[x+1][y]=7;
        if(M1==-20)
            M1=20;
    }
}
void boss3()
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    a[29][framey+4]=8;
    boss_x3=29;
    boss_y3=framey+4;
    for(i=23;i<36;i++)
    {
        cursorxy(hout,i,framey+3);
        printf("*");
        a[i][framey+3]=8;
    }
    for(i=19;i<24;i++)
    {
        cursorxy(hout,i,framey+2);
        printf("~");
        a[i][framey+2]=8;
    }
    for(i=35;i<40;i++)
    {
        cursorxy(hout,i,framey+2);
        printf("~");
        a[i][framey+2]=8;
    }
    for(i=27;i<32;i+=2)
    {
        cursorxy(hout,i,framey+4);
        printf("|");
        a[i][framey+4]=8;
        cursorxy(hout,i,framey+1);
        printf("^");
        a[i][framey+1]=8;
    }
    cursorxy(hout,25,framey+2);
    printf("[");
    a[25][framey+2]=8;
    cursorxy(hout,33,framey+2);
    printf("]");
    a[33][framey+2]=8;
    cursorxy(hout,24,framey+1);
    printf("|");
    a[24][framey+1]=8;
    cursorxy(hout,34,framey+1);
    printf("|");
    a[34][framey+1]=8;
}
void boss3no(int x,int y)
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    a[x][framey+4]=0;
    for(i=x-6;i<x+7;i++)
    {
        cursorxy(hout,i,framey+3);
        printf(" ");
        a[i][framey+3]=0;
    }
    for(i=x-10;i<x-5;i++)
    {
        cursorxy(hout,i,framey+2);
        printf(" ");
        a[i][framey+2]=0;
    }
    for(i=x+6;i<x+11;i++)
    {
        cursorxy(hout,i,framey+2);
        printf(" ");
        a[i][framey+2]=0;
    }
    for(i=x-2;i<x+3;i+=2)
    {
        cursorxy(hout,i,framey+4);
        printf(" ");
        a[i][framey+4]=0;
        cursorxy(hout,i,framey+1);
        printf(" ");
        a[i][framey+1]=0;
    }
    cursorxy(hout,x-4,framey+2);
    printf(" ");
    a[x-4][framey+2]=0;
    cursorxy(hout,x+4,framey+2);
    printf(" ");
    a[x+4][framey+2]=0;
    cursorxy(hout,x+5,framey+1);
    printf(" ");
    a[x+5][framey+1]=0;
    cursorxy(hout,x-5,framey+1);
    printf(" ");
    a[x-5][framey+1]=0;
}
void boss3move(int x,int y)
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    if(m>0)
    {
        a[x-1][framey+4]=8;
        for(i=x-6-1;i<x+7-1;i++)
        {
        cursorxy(hout,i,y-1);
        printf("*");
        a[i][framey+3]=8;
        }
        for(i=x-10-1;i<x-5-1;i++)
        {
            cursorxy(hout,i,y-2);
            printf("~");
            a[i][framey+2]=8;
        }
        for(i=x+6-1;i<x+11-1;i++)
        {
            cursorxy(hout,i,y-2);
            printf("~");
            a[i][framey+2]=8;
        }
        for(i=x-2-1;i<x+3-1;i+=2)
        {
            cursorxy(hout,i,y);
            printf("|");
            a[i][framey+4]=8;
            cursorxy(hout,i,y-3);
            printf("^");
            a[i][framey+1]=8;
        }
        cursorxy(hout,x-4-1,framey+2);
        printf("[");
        a[x-5][framey+2]=8;
        cursorxy(hout,x+4-1,framey+2);
        printf("]");
        a[x+3][framey+2]=8;
        cursorxy(hout,x+5-1,framey+1);
        printf("|");
        a[x+4][framey+1]=8;
        cursorxy(hout,x-5-1,framey+1);
        printf("|");
        a[x-6][framey+1]=8;
        m--;
        boss_x3--;
    }
    else
    {
        a[x+1][framey+4]=8;
        for(i=x-6+1;i<x+7+1;i++)
        {
        cursorxy(hout,i,framey+3);
        printf("*");
        a[i][framey+3]=8;
        }
        for(i=x-10+1;i<x-5+1;i++)
        {
            cursorxy(hout,i,framey+2);
            printf("~");
            a[i][framey+2]=8;
        }
        for(i=x+6+1;i<x+11+1;i++)
        {
            cursorxy(hout,i,framey+2);
            printf("~");
            a[i][framey+2]=8;
        }
        for(i=x-2+1;i<x+3+1;i+=2)
        {
            cursorxy(hout,i,framey+4);
            printf("|");
            a[i][framey+4]=8;
            cursorxy(hout,i,framey+1);
            printf("^");
            a[i][framey+1]=8;
        }
        cursorxy(hout,x-4+1,framey+2);
        printf("[");
        a[x-3][framey+2]=8;
        cursorxy(hout,x+4+1,framey+2);
        printf("]");
        a[x+5][framey+2]=8;
        cursorxy(hout,x+5+1,framey+1);
        printf("|");
        a[x+6][framey+1]=8;
        cursorxy(hout,x-5+1,framey+1);
        printf("|");
        a[x-4][framey+1]=8;
        m--;
        boss_x3++;
        if(m==-16)
            m=16;
    }
}
void autom(struct Plane* plane)//������޹صĲ���
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    int k;
    static speed1=0;
       if(speed1<speed)
            speed1++;
    if(speed1==speed)
    {
        for(i=45;i>6;i--)
            for(j=23;j>6;j--)
            {
                if(a[i][j]==10)
                {
                    a[i][j+1]=10;
                    a[i][j]=0;
                    if(j==23)
                        a[i][j+1]=0;
                }
            }
        speed1=0;
        if(marks%50==0)
            speed--;
    }
    for (i=7;i<46;i++)
		for (j=6;j<24;j++)
		{
            if (a[i][j]==2)
			{
				for (k=0;k<8;k++)
				{
					if ((i==enemy_x1[k]) && (enemy_y1[k])==j-1)  // �ӵ����ел�
					{
						marks++;
						a[enemy_x1[k]][enemy_y1[k]] = 0;
						enemy_x1[k] = rand()%39+7;           // �����µķɻ�
						enemy_y1[k] =framey+1;
						a[enemy_x1[k]][enemy_y1[k]] = 3;
						a[i][j]=0;      // �ӵ���ʧ
					}
				}
				for(k=0;k<3;k++)
                {
                    if(((i==enemy_x2[k])&&(enemy_y2[k]==j-1))||((i==enemy_x2[k]-1)&&(enemy_y2[k]==j))||((i==enemy_x2[k]+1)&&(enemy_y2[k]==j)))
                    {
                        marks+=1;
                        enemy2no(enemy_x2[k],enemy_y2[k]);
                        enemy_x2[k]=rand()%31+10;
                        enemy_y2[k]=framey+2;
                        if((!a[enemy_x2[k]][framey+2])&&(!a[enemy_x2[k]-1][framey+1])&&(!a[enemy_x2[k]+1][framey+1])&&(!a[enemy_x2[k]][framey+1]))
                        {
                            a[enemy_x2[k]][framey+2]=4;
                            cursorxy(hout,enemy_x2[k],framey+2);
                            printf("|");
                            cursorxy(hout,enemy_x2[k]-1,framey+1);
                            printf("\\");
                            a[enemy_x2[k]-1][framey+1]=4;
                            cursorxy(hout,enemy_x2[k]+1,framey+1);
                            printf("/");
                            a[enemy_x2[k]+1][framey+1]=4;
                            cursorxy(hout,enemy_x2[k],framey+1);
                            printf("-");
                            a[enemy_x2[k]][framey+1]=4;
                            //a[i][j-1]=0;
                            a[i][j]=0;
                        }
                    }
                }
                for(k=0;k<2;k++)
                {
                    if(((i==enemy_x3[k])&&(enemy_y3[k]==j-1))||((i==enemy_x3[k]-1)&&(enemy_y3[k]==j-1))||((i==enemy_x3[k]+1)&&(enemy_y3[k]==j-1)))
                    {
                        marks+=1;
                        enemy3no(enemy_x3[k],enemy_y3[k]);
                        enemy_x3[k]=rand()%31+10;
                        enemy_y3[k]=framey+2;
                        if((!a[enemy_x3[k]][framey+2])&&(!a[enemy_x3[k]-1][framey+2])&&(!a[enemy_x3[k]+1][framey+2])&&(!a[enemy_x3[k]-1][framey+1])&&(!a[enemy_x3[k]+1][framey+1]))
                        {
                            a[enemy_x3[k]][framey+2]=5;
                            cursorxy(hout,enemy_x3[k],framey+2);
                            printf("|");
                            cursorxy(hout,enemy_x3[k]-1,framey+2);
                            printf("<");
                            a[enemy_x3[k]-1][framey+2]=5;
                            cursorxy(hout,enemy_x3[k]+1,framey+2);
                            printf(">");
                            a[enemy_x3[k]+1][framey+2]=5;
                            cursorxy(hout,enemy_x3[k]-1,framey+1);
                            printf("+");
                            a[enemy_x3[k]-1][framey+1]=5;
                            cursorxy(hout,enemy_x3[k]+1,framey+1);
                            printf("+");
                            a[enemy_x3[k]+1][framey+1]=5;
                            a[i][j]=0;
                        }
                    }
                }
				// �ӵ������ƶ�
				if(a[i][j]==2)
                {
                    a[i][j-1] = 2;
					a[i][j]=0;
                }
            }
            static int speed = 0,speed2=0,speed3=0;
            if (speed<ispeed)
            speed++;
            if(speed2<ispeed)
                speed2++;
            if(speed3<ispeed)
                speed3++;
            if(a[i][j]<0&&(a[i][j+1]==1||a[i-1][j]==1||a[i+1][j]==1||a[i][j-1]==1))
            {
                if(a[i][j]==-1)
                {
                    Nirvana[0]++;
                    a[i][j]=0;
                }
                if(a[i][j]==-2)
                {
                    Nirvana[1]++;
                    a[i][j]=0;
                }
                if(a[i][j]==-3)
                {
                    if(iweapon<3)
                        iweapon++;
                    a[i][j]=0;
                }
                if(a[i][j]==-4)
                {
                    e1=0;e2=0;e3=0;
                    T=marks;
                    iflag=1;
                }
            }
            if(e1==0&&marks>T+3&&iflag==1)
            {
                e1=8;e2=3;e3=2;
                iflag=0;
            }
            if(a[i][j]!=0&&a[i][j]!=1&&a[i][j+1]==1&&a[i][j]>0)
            {
                cursorxy(hout,24,15);
                printf("GAME OVER��\n");
                Sleep(3000);
                system("cls");
                boss3();
                boss1move(29,15);
                boss2move(29,21);
                cursorxy(hout,46,3);
                printf("do not worry,you have tried your best\n\n");
                getch();
                getch();
                system("pause");
                exit(0);
            }
            for(k=0;k<e1;k++)
            {
                if (enemy_y1[k]>23)   // �л��ܳ���ʾ��Ļ
                {
                    a[enemy_x1[k]][enemy_y1[k]] = 0;
                    enemy_x1[k] = rand()%39+7;           // �����µķɻ�
                    enemy_y1[k] = framey+1;
                    a[enemy_x1[k]][enemy_y1[k]] = 3;
                }
                if (speed ==ispeed)
                {
			// �л�����
                    for (k=0;k<e1;k++)
                    {
                        a[enemy_x1[k]][enemy_y1[k]] = 0;
                        enemy_y1[k]++;
                        speed = 0;
                        a[enemy_x1[k]][enemy_y1[k]] = 3;
                    }
                }
            }
            for(k=0;k<e2;k++)
            {
                if(enemy_y2[k]>23)
                {
                    enemy2no(enemy_x2[k],enemy_y2[k]);
                    enemy_x2[k]=rand()%31+10;
                    enemy_y2[k]=framey+2;
                    if((!a[enemy_x2[k]][framey+2])&&(!a[enemy_x2[k]-1][framey+1])&&(!a[enemy_x2[k]+1][framey+1])&&(!a[enemy_x2[k]][framey+1]))
                    {
                        a[enemy_x2[k]][framey+2]=4;
                        cursorxy(hout,enemy_x2[k],framey+2);
                        printf("|");
                        cursorxy(hout,enemy_x2[k]-1,framey+1);
                        printf("\\");
                        a[enemy_x2[k]-1][framey+1]=4;
                        cursorxy(hout,enemy_x2[k]+1,framey+1);
                        printf("/");
                        a[enemy_x2[k]+1][framey+1]=4;
                        cursorxy(hout,enemy_x2[k],framey+1);
                        printf("-");
                        a[enemy_x2[k]][framey+1]=4;
                    }
                }
                if(speed2==ispeed)
                {
                    for(k=0;k<e2;k++)
                    {
                        enemy2no(enemy_x2[k],enemy_y2[k]);
                        enemy2move(enemy_x2[k],enemy_y2[k]);
                        speed2=0;
                        if(enemy_y2[k]>15&&enemy_x2[k]<40)
                        {
                            enemy_x2[k]++;
                            enemy_y2[k]++;
                        }
                        else
                            enemy_y2[k]++;
                    }
                }
               /* if(enemy_y2[k]==15)
                {
                    a[enemy_x2[k]][enemy_y2[k]+1]=10;
                }*/
            }
            for(k=0;k<e3;k++)
            {
                if(enemy_y3[k]>23)
                {
                    enemy3no(enemy_x3[k],enemy_y3[k]);
                    enemy_x3[k]=rand()%31+10;
                    enemy_y3[k]=framey+2;
                    if((!a[enemy_x3[k]][framey+2])&&(!a[enemy_x3[k]-1][framey+2])&&(!a[enemy_x3[k]+1][framey+2])&&(!a[enemy_x3[k]-1][framey+1])&&(!a[enemy_x3[k]+1][framey+1]))
                    {
                        a[enemy_x3[k]][framey+2]=5;
                        cursorxy(hout,enemy_x3[k],framey+2);
                        printf("|");
                        cursorxy(hout,enemy_x3[k]-1,framey+2);
                        printf("<");
                        a[enemy_x3[k]-1][framey+2]=5;
                        cursorxy(hout,enemy_x3[k]+1,framey+2);
                        printf(">");
                        a[enemy_x3[k]+1][framey+2]=5;
                        cursorxy(hout,enemy_x3[k]-1,framey+1);
                        printf("+");
                        a[enemy_x3[k]-1][framey+1]=5;
                        cursorxy(hout,enemy_x3[k]+1,framey+1);
                        printf("+");
                        a[enemy_x3[k]+1][framey+1]=5;
                    }
                }
                if(speed3==ispeed)
                {
                    for(k=0;k<e3;k++)
                    {
                        enemy3no(enemy_x3[k],enemy_y3[k]);
                        enemy3move(enemy_x3[k],enemy_y3[k]);
                        speed3=0;
                        if(enemy_y3[k]>10&&enemy_y3[k]<15&&enemy_x3[k]>8)
                        {
                            enemy_x3[k]--;
                            enemy_y3[k]++;
                        }
                        else
                            enemy_y3[k]++;
                    }
                }
              /*  if(enemy_y3[k]==9)
                {
                    a[enemy_x3[k]][enemy_y3[k]+1]=10;
                }*/
            }
            if(marks%10==0)
            {
                marks++;
                I=rand()%31+10;
                J=rand()%20+10;
                a[I][J]=rand()%4-4;
            }
        }
    if(flag==1)
        {
            cursorxy(hout,20,4);
            printf("life:%2d",life1);
            e1=0;e2=0;e3=0;
            for (i=7;i<46;i++)
                for (j=6;j<24;j++)
                {
                    if(a[i][j]==2)
                    {
                        for(k=boss_x1-2;k<boss_x1+3;k+=2)
                        {
                            if((i==k)&&(boss_y1==j-1))
                            {
                                life1--;
                                a[i][j]=0;
                            }
                        }
                        for(k=boss_x1-6;k<boss_x1+7;k++)
                        {
                            if((i==k)&&(boss_y1==j-1))
                            {
                                a[i][j]=0;
                            }
                        }
                        if(life1<1)
                        {
                            boss1no(boss_x1,boss_y1);
                            cursorxy(hout,20,4);
                            printf("            ");
                            flag=2;
                            cursorxy(hout,20,15);
                            printf("ROUND 2");
                            Sleep(2000);
                            cursorxy(hout,20,15);
                            printf("       ");
                            e1=8;e2=3;e3=2;
                            level++;
                        }
                        if(j>5&&a[i][j]==2)
                        {
                            a[i][j-1] = 2;
                            a[i][j]=0;
                        }
                    }
                    if(boss_x1%5==0)
                        a[boss_x1][boss_y1+1]=10;
                    if(boss_x1==23||boss_x1==33)
                        {
                            for(k=boss_x1-2;k<boss_x1+3;k+=2)
                                a[k][boss_y1+1]=10;
                        }
                    static bspeed1=0;
                    if(bspeed1<ispeed)
                        bspeed1++;
                    if(bspeed1==ispeed)
                    {
                        boss1no(boss_x1,boss_y1);
                        boss1move(boss_x1,boss_y1);
                        bspeed1=0;
                    }
                }
        }
        if(flag==3)
        {
            cursorxy(hout,20,4);
            printf("life:%2d",life2);
            e1=0;e2=0;e3=0;
            for (i=7;i<46;i++)
                for (j=6;j<24;j++)
                {
                    if(a[i][j]==2)
                    {
                        for(k=boss_x2-2;k<boss_x2+3;k+=2)
                        {
                            if((i==k)&&(boss_y2==j-1))
                            {
                                life2--;
                                a[i][j]=0;
                            }
                        }
                        for(k=boss_x2-2;k<boss_x2+3;k++)
                        {
                            if((i==k)&&(boss_y2==j-1))
                            {
                                a[i][j]=0;
                            }
                        }
                        for(k=boss_x2-6;k<boss_x2+7;k++)
        				{
            				if((i==k)&&(boss_y2==j-1))
            				{
            					a[i][j]=0;
							}
        				}
                        if(life2<1)
                        {
                            boss2no(boss_x2,boss_y2);
                            cursorxy(hout,20,4);
                            printf("         ");
                            flag=4;
                            cursorxy(hout,20,15);
                            printf("ROUND 3");
                            level++;
                            Sleep(2000);
                            cursorxy(hout,20,15);
                            printf("       ");
                            e1=8;e2=3;e3=2;
                        }
                        if(j>5&&a[i][j]==2)
                        {
                            a[i][j-1] = 2;
                            a[i][j]=0;
                        }
                    }
                    if(boss_x2%3==0)
                        a[boss_x2][boss_y2+1]=10;
                    if(boss_x2==20||boss_x2==30)
                        {
                            for(k=boss_x2-2;k<boss_x2+3;k+=2)
                                a[k][boss_y2+1]=10;
                        }
                    static bspeed2=0;
                    if(bspeed2<ispeed)
                        bspeed2++;
                    if(bspeed2==ispeed)
                    {
                        boss2no(boss_x2,boss_y2);
                        boss2move(boss_x2,boss_y2);
                        bspeed2=0;
                    }
                }
            }
        if(flag==5)
        {
            cursorxy(hout,20,4);
            printf("life:%3d",life3);
            e1=0;e2=0;e3=0;
            for (i=7;i<46;i++)
                for (j=6;j<24;j++)
                {
                    if(a[i][j]==2)
                    {
                        for(k=boss_x3-2;k<boss_x3+3;k+=2)
                        {
                            if((i==k)&&(boss_y3==j-1))
                            {
                                a[i][j]=0;
                                life3--;
                            }
                        }
                        for(k=boss_x3-6;k<boss_x3+7;k++)
                        {
                            if((i==k)&&(boss_y3==j-1))
                            {
                                a[i][j]=0;
                            }
                        }
                        for(k=boss_x3-10;k<boss_x3-5;k++)
                        {
                            if((i==k)&&(boss_y3==j-1))
                            {
                                a[i][j]=0;
                            }
                        }
                        for(k=boss_x3+6;k<boss_x3+11;k++)
                        {
                            if((i==k)&&(boss_y3==j-1))
                            {
                                a[i][j]=0;
                            }
                        }
                        if(life3<1)
                        {
                            boss3no(boss_x3,boss_y3);
                            cursorxy(hout,20,4);
                            printf("         ");
                            flag=6;
                            e1=8;e2=3;e3=2;
                            cursorxy(hout,20,13);
                            printf("Congratulations!");
                            cursorxy(hout,10,15);
                            printf("You have passed the game!Perfect!");
                            getch();
                            getch();
                            getch();
                            system("pause");
                            exit(0);
                        }
                        if(j>5&&a[i][j]==2)
                        {
                            a[i][j-1] = 2;
                            a[i][j]=0;
                        }
                    }
                    if(boss_x3%3==0)
                        a[boss_x3][boss_y3+1]=10;
                    if(boss_x3==20||boss_x3==30)
                        {
                            for(k=boss_x3-2;k<boss_x3+3;k+=2)
                                a[k][boss_y3+1]=10;
                        }
                    if(boss_x3==25)
                    {
                        for(k=boss_x3-5;k<boss_x3+6;k+=3)
                            a[k][boss_y3+1]=10;
                    }
                static bspeed3=0;
                if(bspeed3<ispeed)
                bspeed3++;
                if(bspeed3==ispeed)
                {
                    boss3no(boss_x3,boss_y3);
                    boss3move(boss_x3,boss_y3);
                    bspeed3=0;
                }
            }
        }
}
void moveplane(struct Plane* plane)//�������صĲ��� �ɻ��ƶ� �����ӵ�  ��ɱ��
{
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    int k=1;
    char ch;
    //Sleep(35);//�ƶ���ʱ
    if(kbhit())//�ж�����ü���
    {
        ch=getch();//�����õ�ֵ
    switch(ch)
    {
        case'W':
        case 'w' ://�����ƶ�
        case 72:{
            exe(plane);//����
            plane->X[1]=plane->X[1]-1;
            plane->Z[0]=plane->Z[0]-1;
            plane->Z[2]=plane->Z[2]-1;
            for(i=0;i<3;i++)
            {
                plane->Y[i]=plane->Y[i]-1;
            }//�ɻ��������
            limitplane(plane);//���Ʒɻ��ڿ����
            makeplane(hout,plane);//��ӡ�ƶ���ķɻ�
            break;
        }
        case'S':
        case 's'://�����ƶ�
        case 80:{
            exe(plane);//����
            plane->X[1]=plane->X[1]+1;
            plane->Z[0]=plane->Z[0]+1;
            plane->Z[2]=plane->Z[2]+1;
            for(i=0;i<3;i++)
            {
                plane->Y[i]=plane->Y[i]+1;
            }//�ɻ����������ƶ�һ����λ
            limitplane(plane);//���Ʒɻ��ڿ����
            makeplane(hout,plane);//��ӡ�ƶ���ķɻ�
            break;
        }
        case'A':
        case 'a'://�����ƶ�
        case 75:{
            exe(plane);//���
            plane->x[1]=plane->x[1]-1;
            plane->z[0]=plane->z[0]-1;
            plane->z[2]=plane->z[2]-1;
            for(i=0;i<3;i++)
            {
                plane->y[i]=plane->y[i]-1;
            }//�ɻ����������ƶ�һλ
            limitplane(plane);//���Ʒɻ��ڿ����
            makeplane(hout,plane);//��ӡ�ƶ���ķɻ�
            break;
        }
        case'D':
        case 'd'://�����ƶ�
        case 77:{
            exe(plane);//���
            plane->x[1]=plane->x[1]+1;
            plane->z[0]=plane->z[0]+1;
            plane->z[2]=plane->z[2]+1;
            for(i=0;i<3;i++)
            {
                plane->y[i]=plane->y[i]+1;
            }//�ɻ����������ƶ�һ����λ
            limitplane(plane);//���Ʒɻ��ڿ����
            makeplane(hout,plane);//��ӡ�ƶ���ķɻ�
            break;
        }
        case ' ':
            {//�����ӵ�
                if(iweapon==0)
            {cursorxy(hout,plane->x[1],plane->X[1]-1);
            printf("|");
            i=plane->x[1];
            j=plane->X[1]-1;
            a[i][j]=2;}
            if(iweapon==1)
            {
                for(i=plane->x[1]-1;i<plane->x[1]+2;i+=2)
                {
                    cursorxy(hout,i,plane->X[1]-1);
                    printf("|");
                    a[i][plane->X[1]-1]=2;
                }
            }
            if(iweapon==2)
            {
                for(i=plane->x[1]-1;i<plane->x[1]+2;i++)
                {
                    cursorxy(hout,i,plane->X[1]-1);
                    printf("|");
                    a[i][plane->X[1]-1]=2;
                }
            }
            break;
        }
        case 'z':
        case 'Z':
            {
                if(Nirvana[0]>0)
                {
                    for(i=7;i<46;i++)
                    {
                        cursorxy(hout,i,plane->X[1]-1);
                        printf("|");
                        a[i][plane->X[1]-1]=2;
                    }
                Nirvana[0]--;
                }
                break;
            }
        case 'x':
        case 'X':
            {
                if(Nirvana[1]>0)
                {
                    for(i=7;i<46;i++)
                        for(j=6;j<24;j++)
                            if(a[i][j]==3)
                            a[i][j+2]=2;
                            Nirvana[1]--;
                }
                break;
            }
    }
    }
}
int main()
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    hidden();//���ع��
    cover(hout);//����
    srand((unsigned)time(NULL));
    struct Plane p,*plane=&p;//�����ɻ��ṹ��
    makefarme();//���//������Ϣ
    initplane(plane);//���Ʒɻ�
    enemy2();
    enemy1();//�л����γ���
    enemy3();
    while(1)//ѭ�����в���
    {
        if(marks>100&&flag==0)
        {
            flag=1;
             for(i=7;i<46;i++)
                for(j=6;j<24;j++)
                {
                    if(a[i][j]!=1)
                    {
                        a[i][j]=0;
                        cursorxy(hout,i,j);
                        printf(" ");
                    }
                }
            cursorxy(hout,16,15);
            printf("the FIRST BOSS is coming!!!");
            Sleep(2000);
            cursorxy(hout,16,25);
            printf(" ");
            boss1();
        }
        if(marks>200&&flag==2)
        {
            flag=3;
            for(i=7;i<46;i++)
                for(j=6;j<24;j++)
                {
                    if(a[i][j]!=1)
                    {
                        a[i][j]=0;
                        cursorxy(hout,i,j);
                        printf(" ");
                    }
                }
            cursorxy(hout,16,15);
            printf("the SECOND BOSS is coming!!!");
            Sleep(2000);
            cursorxy(hout,16,25);
            printf(" ");
            boss2();
        }
        if(marks>300&&flag==4)
        {
            flag=5;
            for(i=7;i<46;i++)
                for(j=6;j<24;j++)
                {
                    if(a[i][j]!=1)
                    {
                        a[i][j]=0;
                        cursorxy(hout,i,j);
                        printf(" ");
                    }
                }
            cursorxy(hout,16,15);
            printf("the FINAL BOSS is coming!!!");
            Sleep(2000);
            cursorxy(hout,16,25);
            printf(" ");
            boss3();
        }
        infor();
        moveplane(plane);//����Ҳ����йصĸ���
        autom(plane);
    }//����Ҳ����޹صĸ���
    return 0;
}
