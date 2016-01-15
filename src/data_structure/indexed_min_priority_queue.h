typedef enum { false, true } bool;
typedef struct{
	int* pq;
	int* qp;
	int size;
	double* keys;
}IndexMinQueue;

void insert(IndexMinQueue* queue, int i, double value);
void swim(IndexMinQueue* queue, int i);
bool isEmpty(IndexMinQueue* queue);
double topValue(IndexMinQueue* queue);
