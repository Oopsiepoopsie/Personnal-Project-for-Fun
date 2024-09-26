#include <iostream>
using namespace std;

//定义每个程序结构体
struct Program
{
	int id;		//程序编号
	int len;	//长度li
	int pr;		//整型pr代表概率，实际概率pi=pr/Σpr
	double tr;	//tr=len*pr，且作为优先队列出队的条件，且单个程序读取时间为len*pr/Σpr, pi=pr/Σpr，Σpi=1
};


//比较根结点为i的子树各结点tr的大小，自底向上构造大顶堆，n为结点总数
void heapify(Program arr[], int n, int i)
{
	int largest = i;	//默认根节点i的tr最大
	int l = 2 * i + 1;	//左子结点2*i + 1
	int r = 2 * i + 2;	//右子结点2*i + 2
	if (l < n && arr[l].tr > arr[largest].tr)	//如果左子结点存在且左子结点的tr比根结点的tr大
		largest = l;		//记录该左子结点
	if (r < n && arr[r].tr > arr[largest].tr)	//如果右子结点存在且右子结点的tr比目前结点的tr大
		largest = r;		//记录该右子结点
	if (largest != i)		// 如果该子树不构成大顶堆
	{
		swap(arr[i], arr[largest]);	//交换根结点与tr最大的子结点
		heapify(arr, n, largest);	//对交换后的子结点下的子树接着进行堆调整，递归调用heapify，largest为对应子树的根结点索引
	}
}

//通过二叉堆实现优先队列进行自定义排序
void findOrederMRT(Program arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)	//自底向上建堆，通过n/2-1获得最右边最后一个非叶结点开始进行堆调整，依次至二叉堆根结点！！(或者是(index-1)/2, index=n-1)(关键！！自底向上进行建堆的？)
		heapify(arr, n, i);					//调用heapify，i为子树根结点

	for (int i = n - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);	//依次从大顶堆优先队列堆顶取出tr最大的结点放置在末尾，实现以tr升序排序
		heapify(arr, i, 0);		//由于交换后二叉堆根结点不再为tr最大的结点，因此对剩余程序继续进行大顶堆调整，其中需调整的子树根结点为0(即二叉堆根结点)，且结点数量i已减去取出的结点个数
	}
}

//计算最小平均读取时间
double minRetrievalTime(int n, Program PHeap[], long long total)
{
	double MRT = 0;
	for (int i = 1;i <= n;i++)				//ΣΣpiklik
		MRT += PHeap[i - 1].tr / total * (n - i + 1);	//PHeap[i].tr/total为单个程序读取时间，且ΣΣpiklik中第i个程序会被读取(n-i+1)次，如第1个程序会被读取n次，第2个会被读取n-1次
	return MRT;
}

//输出程序的存储顺序
void printOrder(Program arr[], int n)
{
	for (int i = 0; i < n; ++i)
		cout << arr[i].id << " ";	//按顺序输出各程序的id
	cout << "\n";
}

//输入各程序存放长度li与整型读取概率
void input(int n, Program* PHeap, long long &total)	//&引用传递total
{
	for (int i = 0;i < n;i++)
	{
		PHeap[i].id = i + 1;	//存储程序id
		cout << "请输入编号" << i + 1 << "程序的存放长度li与读取整型概率pi：";
		cin >> PHeap[i].len >> PHeap[i].pr;	//输入各程序存放长度li与整型读取概率
		PHeap[i].tr = PHeap[i].len * PHeap[i].pr;	//计算tr=len*pr
		total += PHeap[i].pr;		//计算Σpr
	}
}


//主函数
int main()
{
	int n;	//程序个数
	cout << "请输入程序个数n：" << endl;
	cin >> n;
	Program* PHeap = (Program*)malloc(n * sizeof(Program));	//动态分配数组存储各个程序结构体
	long long total = 0;		//初始化为0，用于之后记录Σpr

	input(n, PHeap, total);		//输入各程序存放长度li与整型读取概率pr

	findOrederMRT(PHeap, n);	//对程序进行排序使平均读取时间最小

	double MRT = minRetrievalTime(n, PHeap, total);	//获取最小平均读取时间
	cout << "程序存储的顺序为：" << endl;
	printOrder(PHeap, n);
	cout << "最小平均读取时间(Minimun Retrieval Time)为：" << endl;
	cout << MRT << endl;

	return 0;
}
