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
void deleteTop(IndexMinQueue* queue);
void sink(IndexMinQueue* queue, int i);
void printQueue(IndexMinQueue* queue);
bool isContained(IndexMinQueue* queue, int i);