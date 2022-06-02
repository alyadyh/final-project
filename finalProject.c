#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define RED 0
#define BLACK 1

struct node{
	int id;
	char stock[20];
	int price;
	int color;
	struct node *parent;
	struct node *left;
	struct node *right;
};

struct node *ROOT;
struct node *NILL;

void left_rotate(struct node *x);
void right_rotate(struct node *x);
void tree_print(struct node *x);
void red_black_insert(int num, char *data, int prc);
void red_black_insert_fixup(struct node *z);
struct node *tree_search(int key);
struct node *tree_minimum(struct node *x);

int main(){
	NILL = malloc(sizeof(struct node));
	NILL->color = BLACK;

	ROOT = NILL;
	
	int tcase, num, prc;
	char data[20];

	int option;
	system("cls");
	do
	{
		printf("\n ==========================================\n");
		printf("\tInventory Management Program\n");
		printf(" ==========================================\n\n");
		printf(" 1: Input data\n");
		printf(" 2: Display data\n");
		printf(" 3: EXIT\n");
		printf("\n Enter your option : ");
		scanf("%d", &option);
		switch(option)
		{
			case 1:
				printf("\n Number of data you want to input: ");
				scanf("%d", &tcase);
				while(tcase--)
				{
					printf("\n Enter product's ID number: ");
					scanf("%d", &num);
					printf(" Enter product's name: ");
					getchar();
					scanf("%[^\n]", &data);
					printf(" Enter product's price: ");
					scanf("%d", &prc);
					red_black_insert(num, data, prc);
				}
				break;
			case 2:
				printf("\n    --- Product's Catalogue --- \n\n");
				printf(" +------+-----------------+----------+\n");
				printf(" |  ID  |     Product     |   Price  |\n");
				printf(" +------+-----------------+----------+\n");
				printf(" |      |                 |          |\n");
				tree_print(ROOT);
				printf(" |      |                 |          |\n");
				printf(" +------+-----------------+----------+\n");
				break;
		}
	} while(option != 3);
	return 0;
}

void tree_print(struct node *x){
	if(x != NILL){
		tree_print(x->left);
		printf(" | %d | %s\t  | Rp%d  |\n", x-> id, x -> stock, x->price);
		tree_print(x->right);
	}
}

struct node *tree_minimum(struct node *x){
	while(x->left != NILL){
		x = x->left;
	}
	return x;
}

void red_black_insert(int num, char *data, int prc){
	struct node *z, *x, *y;
	z = malloc(sizeof(struct node));

	z->id = num;
	strcpy(z->stock, data);
	z->price = prc;
	z->color = RED;
	z->left = NILL;
	z->right = NILL;

	x = ROOT;
	y = NILL;

	while(x != NILL){
		y = x;
		if(z->id <= x->id){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}

	if(y == NILL){
		ROOT = z;
	}
	else if(z->id <= y->id){
		y->left = z;
	}
	else{
		y->right = z;
	}

	z->parent = y;

	red_black_insert_fixup(z);
}

void red_black_insert_fixup(struct node *z){
	while(z->parent->color == RED){

		/* z's parent is left child of z's grand parent*/
		if(z->parent == z->parent->parent->left){

			/* z's grand parent's right child is RED */
			if(z->parent->parent->right != NULL && z->parent->parent->right->color == RED){
				z->parent->color = BLACK;
				z->parent->parent->right->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}

			/* z's grand parent's right child is not RED */
			else{
				
				/* z is z's parent's right child */
				if(z == z->parent->right){
					z = z->parent;
					left_rotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(z->parent->parent);
			}
		}

		/* z's parent is z's grand parent's right child */
		else{
			
			/* z's left uncle or z's grand parent's left child is also RED */
			if(z->parent->parent->left != NULL && z->parent->parent->left->color == RED){
				z->parent->color = BLACK;
				z->parent->parent->left->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}

			/* z's left uncle is not RED */
			else{
				/* z is z's parents left child */
				if(z == z->parent->left){
					z = z->parent;
					right_rotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(z->parent->parent);
			}
		}
	}
	ROOT->color = BLACK;
}

void left_rotate(struct node *x){
	struct node *y;
	
	/* Make y's left child x's right child */
	y = x->right;
	x->right = y->left;
	if(y->left != NILL){
		y->left->parent = x;
	}

	/* Make x's parent y's parent and y, x's parent's child */
	y->parent = x->parent;
	if(y->parent == NILL){
		ROOT = y;
	}
	else if(x == x->parent->left){
		x->parent->left = y;
	}
	else{
		x->parent->right = y;
	}
	
	/* Make x, y's left child & y, x's parent */
	y->left = x;
	x->parent = y;
}

void right_rotate(struct node *x){
	struct node *y;

	/* Make y's right child x's left child */
	y = x->left;
	x->left = y->right;
	if(y->right != NILL){
		y->right->parent = x;
	}

	/* Make x's parent y's parent and y, x's parent's child */
	y->parent = x->parent;
	if(y->parent == NILL){
		ROOT = y;
	}
	else if(x == x->parent->left){
		x->parent->left = y;	
	}
	else{
		x->parent->right = y;
	}

	/* Make y, x's parent and x, y's child */
	y->right = x;
	x->parent = y;
}