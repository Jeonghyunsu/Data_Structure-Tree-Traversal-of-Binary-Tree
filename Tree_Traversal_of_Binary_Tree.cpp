#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <math.h>

using namespace std;

int heap_num=0;
int heap_depth=0;
class Heap
{
	private:
		char *heap;
		int capacity;
		int size;
		char Hheap[43][43];
	
	public:
		Heap(int Capacity=300);
		~Heap();
		void Push(char num);
		void Pop();
		void Swap(char *a, char *b);
		int IndexDepth(int index);
		void Output_regular();
		void Output_90(int root);
		
		void Output_H_start();
		void Output_H(int direction, int heap_num ,int y, int x);
};
Heap::Heap(int Capacity)
{
	capacity=Capacity;
	heap = new char[Heap::capacity];
	size= 0;
	for(int i=0 ; i<43 ; i++)
	{
		for(int j=0 ; j<43 ; j++)
			Hheap[i][j]=' ';
	}
}
Heap::~Heap()
{
	delete [] heap;
}
void Heap::Swap(char *a,char *b)
{
	char temp=*a;
	*a=*b;
	*b=temp;
}
void Heap::Push(char num)
{
	int current= size;
	int parent = (int)((current-1)/2);
	
	if(size >= capacity)
		return;
	heap[size]=num;
	
	while(current >0 && heap[current] < heap[parent])
	{
		Swap(&heap[current], &heap[parent]);
		current = parent;
		parent = (int)((current-1)/2);
	}
	size++;
}
void Heap::Pop()
{
	int parent = 0;
	int left=1;
	int right=2;
	
	if(size ==0)
	{
		cout<<"비어있습니다!!"<<endl;
		return;	
	}	
	
	heap[0]=0;
	size--;
	Swap(&heap[0],&heap[size]);
	
	while(1)
	{
		int choose=0;
		
		if(left >= size)break;
		if(right >= size)choose=left;
		else{
			if(heap[left] > heap[right])choose=right;
			else choose =left;
		}
		if(heap[choose]<heap[parent])
		{
			Swap(&heap[parent],&heap[choose]);
			parent = choose;
		}
		else break;
		
		left =2*parent +1;
		right=2*parent +2;
	}
}
int Heap::IndexDepth(int index)
{
	int depth=0;
	while(1)
	{
		if((index>>1)<1)
			break;
		index=index>>1;
		depth++;
	}
	return depth;
}
void Heap::Output_regular()
{
	int total_depth= IndexDepth(size);
	int depth=total_depth;
	int currentdepth=0;
	int index=0;
	int previous=0;
	
	for(int i=0 ; i <= total_depth ;i++)
	{
		for(int j=1 ; j <= (int)pow(2.0,depth)-1 ; j++)
			cout<<" ";
		
			for(int k=1 ; k <= (int)pow(2.0,currentdepth) ; k++)
			{
				cout<<heap[index++];
				if(index==size)
					break;
				for(int l=1 ; l <= (int)pow(2.0,depth+1)-1 ; l++)
					cout<<" ";
			}
		
		currentdepth++;
		depth--;
		cout<<endl;
	}
	cout<<endl;
}
void Heap::Output_90(int root)
{
	if(root>size)
		return;
	
	Output_90(2*root+1);
	cout<<setw(2*IndexDepth(root))<<heap[root-1]<<endl;
	Output_90(2*root);
}
void Heap::Output_H_start()
{
	int i=0,j=0;
	for(i=0 ; i<43 ; i++)
	{
		for(j=0 ; j<43 ; j++)
			Hheap[i][j]=' ';	
	}	
	Output_H(0,1,22,22);//start 1
	int h=0,v=0;
	int hnum=0,vnum=0;
	for(i=0 ; i<43 ; i++)
	{
		for(j=0 ; j<43; j++)
		{
			if(Hheap[i][j]!=' ')
			{
				h++;
				break;
			}
		}
		if(h!=0)
		{
			hnum=i;
			break;
		}
	}
	for(i=0 ; i<43 ; i++)
	{
		for(j=0 ; j<43; j++)
		{
			if(Hheap[j][i]!=' ')
			{
				v++;
				break;
			}
		}
		if(v!=0)
		{
			vnum=i;
			break;
		}
	}
	for(i=hnum-5 ; i<43 ; i++)
	{	
		for(j=vnum-5 ; j<43 ; j++)
		{
			if(Hheap[i][j]==' ')
				cout<<" ";
			else
				cout<<Hheap[i][j];
		}
		cout<<endl;
	}
	
}
void Heap::Output_H(int direction, int heap_num ,int y, int x)
{
	int depth=IndexDepth(size)-IndexDepth(heap_num);
	if(direction==0)
	{
		if(heap_num <= size) Hheap[y][x]=heap[heap_num-1];
		if(depth<3)
		{
			if(2*heap_num <= size)Output_H(1,2*heap_num,y,x-1);
			if(2*heap_num+1 <= size)Output_H(2,2*heap_num+1,y,x+1);
		}
		else if(depth>=3 && depth<=4)
		{
			Hheap[y][x-1]='-';
			Hheap[y][x+1]='-';
			if(2*heap_num <= size)
			{
				--x;
				Output_H(1,2*heap_num,y,x-1);
				++x;
			}
			if(2*heap_num+1 <= size)
			{
				++x;
				Output_H(2,2*heap_num+1,y,x+1);	
				--x;		
			}
		}
		else if(depth>=5 && depth<=6)
		{
			Hheap[y][x-1]='-';
			Hheap[y][x-2]='-';
			Hheap[y][x-3]='-';
			Hheap[y][x+1]='-';
			Hheap[y][x+2]='-';
			Hheap[y][x+3]='-';
			if(2*heap_num <= size)
			{
				x-=3;
				Output_H(1,2*heap_num,y,x-1);
				x+=3;
			}
			if(2*heap_num+1 <= size)
			{
				x+=3;
				Output_H(2,2*heap_num+1,y,x+1);	
				x-=3;		
			}	
		}
		else if(depth>=7)
		{
			Hheap[y][x-1]='-';
			Hheap[y][x-2]='-';
			Hheap[y][x-3]='-';
			Hheap[y][x-4]='-';
			Hheap[y][x-5]='-';	
			Hheap[y][x+1]='-';
			Hheap[y][x+2]='-';
			Hheap[y][x+3]='-';
			Hheap[y][x+4]='-';
			Hheap[y][x+5]='-';
			if(2*heap_num <= size)
			{
				x-=5;
				Output_H(1,2*heap_num,y,x-1);
				x+=5;
			}
			if(2*heap_num+1 <= size)
			{
				x+=5;
				Output_H(2,2*heap_num+1,y,x+1);	
				x-=5;		
			}	
		}			
	}
	else if(direction==1)
	{
		if(heap_num <= size) Hheap[y][x]=heap[heap_num-1];
		
		if(depth<3)
		{
			if(2*heap_num <= size)Output_H(3,2*heap_num,y-1,x);
			if(2*heap_num+1 <= size)Output_H(4,2*heap_num+1,y+1,x);
		}
		else if(depth>=3 && depth<=4)
		{
			Hheap[y-1][x]='|';
			Hheap[y+1][x]='|';
			if(2*heap_num <= size)
			{
				--y;
				Output_H(3,2*heap_num,y-1,x);
				++y;
			}
			if(2*heap_num+1 <= size)
			{
				++y;
				Output_H(4,2*heap_num+1,y+1,x);	
				--y;		
			}
		}
		else if(depth>=5 && depth<=6)
		{
			Hheap[y-1][x]='|';
			Hheap[y-2][x]='|';
			Hheap[y-3][x]='|';
			Hheap[y+1][x]='|';
			Hheap[y+2][x]='|';
			Hheap[y+3][x]='|';
			if(2*heap_num <= size)
			{
				y-=3;
				Output_H(3,2*heap_num,y-1,x);
				y+=3;
			}
			if(2*heap_num+1 <= size)
			{
				y+=3;
				Output_H(4,2*heap_num+1,y+1,x);	
				y-=3;		
			}	
		}
		else if(depth>=7)
		{
			Hheap[y-1][x]='|';
			Hheap[y-2][x]='|';
			Hheap[y-3][x]='|';
			Hheap[y-4][x]='|';
			Hheap[y-5][x]='|';
			Hheap[y+1][x]='|';
			Hheap[y+2][x]='|';
			Hheap[y+3][x]='|';
			Hheap[y+4][x]='|';
			Hheap[y+5][x]='|';
			if(2*heap_num <= size)
			{
				y-=5;
				Output_H(3,2*heap_num,y-1,x);
				y+=5;
			}
			if(2*heap_num+1 <= size)
			{
				y+=5;
				Output_H(4,2*heap_num+1,y+1,x);	
				y-=5;		
			}	
		}		
	}
	
	else if(direction==2)
	{
		if(heap_num <= size) Hheap[y][x]=heap[heap_num-1];
		
		if(depth<3)
		{
			if(2*heap_num <= size)Output_H(4,2*heap_num,y+1,x);
			if(2*heap_num+1 <= size)Output_H(3,2*heap_num+1,y-1,x);
		}
		else if(depth>=3 && depth<=4)
		{
			Hheap[y-1][x]='|';
			Hheap[y+1][x]='|';
			if(2*heap_num <= size)
			{
				++y;
				Output_H(4,2*heap_num,y+1,x);
				--y;
			}
			if(2*heap_num+1 <= size)
			{
				--y;
				Output_H(3,2*heap_num+1,y-1,x);
				++y;		
			}
		}
		else if(depth>=5 && depth<=6)
		{
			Hheap[y-1][x]='|';
			Hheap[y-2][x]='|';
			Hheap[y-3][x]='|';
			Hheap[y+1][x]='|';
			Hheap[y+2][x]='|';
			Hheap[y+3][x]='|';
			if(2*heap_num <= size)
			{
				y+=3;
				Output_H(4,2*heap_num,y+1,x);
				y-=3;
			}
			if(2*heap_num+1 <= size)
			{
				y-=3;
				Output_H(3,2*heap_num+1,y-1,x);
				y+=3;		
			}	
		}
		else if(depth>=7)
		{
			Hheap[y-1][x]='|';
			Hheap[y-2][x]='|';
			Hheap[y-3][x]='|';
			Hheap[y-4][x]='|';
			Hheap[y-5][x]='|';
			Hheap[y+1][x]='|';
			Hheap[y+2][x]='|';
			Hheap[y+3][x]='|';
			Hheap[y+4][x]='|';
			Hheap[y+5][x]='|';
			if(2*heap_num <= size)
			{
				y+=5;
				Output_H(4,2*heap_num,y+1,x);
				y-=5;
			}
			if(2*heap_num+1 <= size)
			{
				y-=5;
				Output_H(3,2*heap_num+1,y-1,x);	
				y+=5;		
			}	
		}
	}
	else if(direction==3)
	{
		if(heap_num <= size) Hheap[y][x]=heap[heap_num-1];
		
		if(depth<3)
		{
			if(2*heap_num <= size)Output_H(2,2*heap_num,y,x+1);
			if(2*heap_num+1 <= size)Output_H(1,2*heap_num+1,y,x-1);
		}
		else if(depth>=3 && depth<=4)
		{
			Hheap[y][x-1]='-';
			Hheap[y][x+1]='-';
			if(2*heap_num <= size)
			{
				++x;
				Output_H(2,2*heap_num,y,x+1);
				--x;
			}
			if(2*heap_num+1 <= size)
			{
				--x;
				Output_H(1,2*heap_num+1,y,x-1);
				++x;		
			}
		}
		else if(depth>=5 && depth<=6)
		{
			Hheap[y][x-1]='-';
			Hheap[y][x-2]='-';
			Hheap[y][x-3]='-';
			Hheap[y][x+1]='-';
			Hheap[y][x+2]='-';
			Hheap[y][x+3]='-';
			if(2*heap_num <= size)
			{
				x+=3;
				Output_H(2,2*heap_num,y,x+1);
				x-=3;
			}
			if(2*heap_num+1 <= size)
			{
				x-=3;
				Output_H(1,2*heap_num+1,y,x-1);
				x+=3;		
			}	
		}
		else if(depth>=7)
		{
			Hheap[y][x-1]='-';
			Hheap[y][x-2]='-';
			Hheap[y][x-3]='-';
			Hheap[y][x-4]='-';
			Hheap[y][x-5]='-';	
			Hheap[y][x+1]='-';
			Hheap[y][x+2]='-';
			Hheap[y][x+3]='-';
			Hheap[y][x+4]='-';
			Hheap[y][x+5]='-';
			if(2*heap_num <= size)
			{
			
				x+=5;
				 Output_H(2,2*heap_num,y,x+1);
				x-=5;
			}
			if(2*heap_num+1 <= size)
			{
				x-=5;
				Output_H(1,2*heap_num+1,y,x-1);
				x+=5;		
			}	
		}
	}
	else if(direction==4)
	{
		if(heap_num <= size) Hheap[y][x]=heap[heap_num-1];
		
		if(depth<3)
		{
			if(2*heap_num <= size)Output_H(1,2*heap_num,y,x-1);
			if(2*heap_num+1 <= size)Output_H(2,2*heap_num+1,y,x+1);
		}
		else if(depth>=3 && depth<=4)
		{
			Hheap[y][x-1]='-';
			Hheap[y][x+1]='-';
			if(2*heap_num <= size)
			{
				--x;
				Output_H(1,2*heap_num,y,x-1);
				++x;
			}
			if(2*heap_num+1 <= size)
			{
				++x;
				Output_H(2,2*heap_num+1,y,x+1);
				--x;		
			}
		}
		else if(depth>=5 && depth<=6)
		{
			Hheap[y][x-1]='-';
			Hheap[y][x-2]='-';
			Hheap[y][x-3]='-';
			Hheap[y][x+1]='-';
			Hheap[y][x+2]='-';
			Hheap[y][x+3]='-';
			if(2*heap_num <= size)
			{
				x-=3;
				Output_H(1,2*heap_num,y,x-1);
				x+=3;
			}
			if(2*heap_num+1 <= size)
			{
				x+=3;
				Output_H(2,2*heap_num+1,y,x+1);
				x-=3;		
			}	
		}
		else if(depth>=7)
		{
			Hheap[y][x-1]='-';
			Hheap[y][x-2]='-';
			Hheap[y][x-3]='-';
			Hheap[y][x-4]='-';
			Hheap[y][x-5]='-';	
			Hheap[y][x+1]='-';
			Hheap[y][x+2]='-';
			Hheap[y][x+3]='-';
			Hheap[y][x+4]='-';
			Hheap[y][x+5]='-';
			if(2*heap_num <= size)
			{
				x-=5;
				Output_H(1,2*heap_num,y,x-1);
				x+=5;
			}
			if(2*heap_num+1 <= size)
			{
				x+=5;
				Output_H(2,2*heap_num+1,y,x+1);
				x-=5;		
			}	
		}
	}
}

int main()
{
	char input[10];
	int range=0;
	cout<<"range를 입력하세요"<<endl;
	while(1){
		cin>>range;
		if(range>=1 && range<=300)break;
		else cout<<"범위를 넘었습니다. 다시 입력해주세요."<<endl;
	}
	Heap heap(range);
	while(1){
		cout<<"PUSH -> P# / POP -> R / 푸쉬팝을 그만 하고 출력을 보고 싶다면 P!"<<endl;
		while(1)
		{
			for(int i=0 ; i<2 ; i++)
			{
				cin>>input[i];
				if(input[i]==' ' || input[i]=='\n' || input[i]=='R')
					break;
			}
			if(input[0]=='P')
			{	
				if(input[1]>=48 && input[1]<=57)heap.Push(input[1]);
				else if(input[1]>=65 && input[1]<=90)heap.Push(input[1]);
				else if(input[1]>=97 && input[1]<=122)heap.Push(input[1]);
			}
			if(input[0]=='R')heap.Pop();
			if(input[0]=='P' &&input[1]=='!')break;
		}
		cout<<"<<regular heap>>"<<endl;
		heap.Output_regular();
		cout<<endl;
		cout<<"<<90 heap>>"<<endl;
		heap.Output_90(1);
		cout<<endl;
		cout<<"<<H heap>>"<<endl;
		heap.Output_H_start();
		cout<<endl;
	}
	return 0;
}


















