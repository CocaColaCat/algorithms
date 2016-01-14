typedef struct{
	int* pq;
	int* qp;
	int size;
	double keys[];
}IndexMinQueue;

void insert(IndexMinQueue* queue, int i, double value);
void swim(IndexMinQueue* queue, int i);