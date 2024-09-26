#include <iostream>
using namespace std;

//����ÿ������ṹ��
struct Program
{
	int id;		//������
	int len;	//����li
	int pr;		//����pr������ʣ�ʵ�ʸ���pi=pr/��pr
	double tr;	//tr=len*pr������Ϊ���ȶ��г��ӵ��������ҵ��������ȡʱ��Ϊlen*pr/��pr, pi=pr/��pr����pi=1
};


//�Ƚϸ����Ϊi�����������tr�Ĵ�С���Ե����Ϲ���󶥶ѣ�nΪ�������
void heapify(Program arr[], int n, int i)
{
	int largest = i;	//Ĭ�ϸ��ڵ�i��tr���
	int l = 2 * i + 1;	//���ӽ��2*i + 1
	int r = 2 * i + 2;	//���ӽ��2*i + 2
	if (l < n && arr[l].tr > arr[largest].tr)	//������ӽ����������ӽ���tr�ȸ�����tr��
		largest = l;		//��¼�����ӽ��
	if (r < n && arr[r].tr > arr[largest].tr)	//������ӽ����������ӽ���tr��Ŀǰ����tr��
		largest = r;		//��¼�����ӽ��
	if (largest != i)		// ��������������ɴ󶥶�
	{
		swap(arr[i], arr[largest]);	//�����������tr�����ӽ��
		heapify(arr, n, largest);	//�Խ�������ӽ���µ��������Ž��жѵ������ݹ����heapify��largestΪ��Ӧ�����ĸ��������
	}
}

//ͨ�������ʵ�����ȶ��н����Զ�������
void findOrederMRT(Program arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)	//�Ե����Ͻ��ѣ�ͨ��n/2-1������ұ����һ����Ҷ��㿪ʼ���жѵ���������������Ѹ���㣡��(������(index-1)/2, index=n-1)(�ؼ������Ե����Ͻ��н��ѵģ�)
		heapify(arr, n, i);					//����heapify��iΪ���������

	for (int i = n - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);	//���δӴ󶥶����ȶ��жѶ�ȡ��tr���Ľ�������ĩβ��ʵ����tr��������
		heapify(arr, i, 0);		//���ڽ��������Ѹ���㲻��Ϊtr���Ľ�㣬��˶�ʣ�����������д󶥶ѵ�������������������������Ϊ0(������Ѹ����)���ҽ������i�Ѽ�ȥȡ���Ľ�����
	}
}

//������Сƽ����ȡʱ��
double minRetrievalTime(int n, Program PHeap[], long long total)
{
	double MRT = 0;
	for (int i = 1;i <= n;i++)				//����piklik
		MRT += PHeap[i - 1].tr / total * (n - i + 1);	//PHeap[i].tr/totalΪ���������ȡʱ�䣬�Ҧ���piklik�е�i������ᱻ��ȡ(n-i+1)�Σ����1������ᱻ��ȡn�Σ���2���ᱻ��ȡn-1��
	return MRT;
}

//�������Ĵ洢˳��
void printOrder(Program arr[], int n)
{
	for (int i = 0; i < n; ++i)
		cout << arr[i].id << " ";	//��˳������������id
	cout << "\n";
}

//����������ų���li�����Ͷ�ȡ����
void input(int n, Program* PHeap, long long &total)	//&���ô���total
{
	for (int i = 0;i < n;i++)
	{
		PHeap[i].id = i + 1;	//�洢����id
		cout << "��������" << i + 1 << "����Ĵ�ų���li���ȡ���͸���pi��";
		cin >> PHeap[i].len >> PHeap[i].pr;	//����������ų���li�����Ͷ�ȡ����
		PHeap[i].tr = PHeap[i].len * PHeap[i].pr;	//����tr=len*pr
		total += PHeap[i].pr;		//���㦲pr
	}
}


//������
int main()
{
	int n;	//�������
	cout << "������������n��" << endl;
	cin >> n;
	Program* PHeap = (Program*)malloc(n * sizeof(Program));	//��̬��������洢��������ṹ��
	long long total = 0;		//��ʼ��Ϊ0������֮���¼��pr

	input(n, PHeap, total);		//����������ų���li�����Ͷ�ȡ����pr

	findOrederMRT(PHeap, n);	//�Գ����������ʹƽ����ȡʱ����С

	double MRT = minRetrievalTime(n, PHeap, total);	//��ȡ��Сƽ����ȡʱ��
	cout << "����洢��˳��Ϊ��" << endl;
	printOrder(PHeap, n);
	cout << "��Сƽ����ȡʱ��(Minimun Retrieval Time)Ϊ��" << endl;
	cout << MRT << endl;

	return 0;
}
