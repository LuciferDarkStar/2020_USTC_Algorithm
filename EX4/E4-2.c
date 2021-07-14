#include<stdio.h>
#include<stdlib.h>
int T;
typedef struct PCB {
	int id;//�������
	int arrivetime;//���񵽴�ʱ��
	int runtime;//������Ҫִ�е�ʱ��
	int counttime;//��¼������һ��ʱ���,ʣ�µ���Ҫ�����ʱ��
	struct PCB* next;
}*task, pcb;
pcb* creattask(int x, int y, int z) {
	task newtask = (task)malloc(sizeof(pcb));
	newtask->id = x;
	newtask->arrivetime = y;
	newtask->runtime = z;
	newtask->counttime = z;
	newtask->next = NULL;
	return newtask;
}
void deltask(pcb* n, int x) {
	task d;
	if (n != NULL) {
		while (n->next->id != x) {
			n = n->next;
		}
		d = n->next;
		n->next = d->next;
		free(d);
	}
}
void count(pcb* n, int t)
{  //q���ڼ�¼���ȵ��������λ�ã�p���ڱ�������
	pcb* q, *p, *flag, *flag_1;
	int flag_2 = 0;
	int temp = t;
	int time = 0; //time��¼��ǰʱ�䣬temp��¼�������,���ں�������
	flag_1 = n;
	while (t != 0)
	{
		if (flag_2 == 0)
		{
			p = n->next;
			flag = n;
			q = p;
		}
		while (p != NULL)
		{ //�ҵ����ھ����Ķ����������������̵�����
			if (p->arrivetime > time)
				break;
			if ((p->arrivetime <= time || p->arrivetime == q->arrivetime) && p->counttime < q->counttime)
			{
				flag_1 = flag;
				q = p;
			}
			flag = p;
			p = p->next;
		}
		flag_2 = 1;
		q->counttime--;
		if (time < q->arrivetime)//��ֹʱ����ͣ
			time = q->arrivetime;
		time++;
		if (q->counttime == 0)
		{
			T = T + time - q->arrivetime;
			deltask(flag_1, q->id);
			flag_1 = n;
			--t;
			flag_2 = 0;
		}
	}
}
void swap(pcb* x, pcb* y)
{
	int a, b;
	a = x->arrivetime;
	b = x->runtime;
	x->arrivetime = y->arrivetime;
	x->runtime = y->runtime;
	x->counttime = y->counttime;
	y->arrivetime = a;
	y->counttime = b;
	y->runtime = b;
}
pcb* Partition(pcb* head, pcb* tail)
{
	int x = head->arrivetime;
	int y = head->runtime;
	task fast = head->next;
	task slow = head;
	while (fast != tail)
	{
		if (fast->arrivetime < x)
		{
			slow = slow->next;
			swap(slow, fast);
		}
		else if (fast->arrivetime == x && fast->runtime <= y)
		{
			slow = slow->next;
			swap(slow, fast);
		}
		fast = fast->next;
	}
	swap(slow, head);
	return slow;
}
void Quicksort(pcb* head, pcb* tail)
{
	if (head != tail)
	{
		task mid = Partition(head, tail);
		Quicksort(head, mid);
		Quicksort(mid->next, tail);
	}
}
int main() {
	int n, i, y, z;
	T = 0;
	task tail = NULL;
	task head = NULL;
	task Next, temp;
	scanf("%d", &n);
	tail = (task)malloc(sizeof(pcb));
	head = tail;
	for (i = 1; i <= n; i++) {
		scanf("%d", &y);
		scanf("%d", &z);
		tail->next = creattask(i, y, z);
		tail = tail->next;
	}
	temp = tail;
	tail->next = creattask(i + 1, 10000001, 1);
	tail = tail->next;
	Quicksort(head->next, tail);
	temp->next = NULL;
	free(tail);
	tail = temp;
	count(head, n);
	printf("%d\n", T);
	return 0;
}
