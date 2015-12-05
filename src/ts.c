#include <stdio.h>
// #include <stdlib.h>
typedef struct Node
{
	int value;
}Node;

int main(){
	Node node = {0};
	printf("%p\n", &node);
	printf("%i\n", node.value);
	node.value = 1;
	printf("%p\n", &node);
	printf("%i\n", node.value);
}
// int main(){
// 	int glass = 180;
// 	int order_str;
// 	int order;
// 	while(glass>0){
// 		printf("You have %i glasses left\n", glass);
// 		scanf("%2s", order_str);
// 		order = atoi(order_str);
// 		glass = glass - order;
// 		printf("%i glass ordered\n", order);
// 	}
// 	puts("You are out of stock!\n");
// 	return 0;
// }

// int main(){
// 	int contestants[] = {1, 2, 3};
// 	int choice = contestants[0];
// 	contestants[0] = 2;
// 	contestants[1] = contestants[2];
// 	contestants[2] = choice;
// 	choice = contestants[1];
// 	printf("I'm going to pick contestant number %i\n", choice); 
// 	return 0;
// }


// int main(){
// 	char str_1[3] = "AB";
// 	char str_2[][2] = { "A", "B" };
// 	char* str_3 = "AB";	
// 	printf("%c\n", str_1[0]);
// 	printf("%c\n", str_2[0][0]);
// 	printf("%p\n", str_3);
// }


// 指针的练习. & always used for get address of values, and * used for declare pointer variables
// int main(){
// 	char *str = "ABCD";
// 	char str2[] = "ABCD";
// 	// printf("%p\n", str);
// 	printf("%p\n", &(str));
// 	printf("%p\n", str);
// 	printf("%p\n", str2);
// 	printf("%c\n", str[1]);
// 	// char* temp = &str[0]; // defined pointer variable temp
// 	// printf("%p\n", temp); // print pointer of str[0], aka address of str[0]
// 	// printf("%p\n", &temp); // print address of pointter of str[0]
// 	// printf("%p\n", &str[1]);
// 	// printf("%p\n", &str[2]);
// 	// printf("%c\n", str[4]);
// 	return 0;
// }