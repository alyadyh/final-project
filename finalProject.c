#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define RED 0
#define BLACK 1

struct node
{
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

void left_rotate(struct node *);
void right_rotate(struct node *);
void tree_print(struct node *);
void red_black_insert(int num, char *data, int prc);
void red_black_insert_fixup(struct node *);
struct node *searching(int key);
void deleteNode(struct node *);

int main()
{
	NILL = malloc(sizeof(struct node));
	NILL->color = BLACK;

	ROOT = NILL;

	int tcase, num, prc, search_key;
	char data[20];

	int option;
	system("cls");
	do
	{
		printf("\n ==========================================\n");
		printf("\tInventory Management Program\n");
		printf(" ==========================================\n\n");
		printf(" 1: Insert data\n");
		printf(" 2: Display data\n");
		printf(" 3: Search\n");
		printf(" 4: Delete data\n");
		printf(" 5: Update data\n");
		printf(" 6: EXIT\n");
		printf("\n Enter your option : ");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			printf("\n Number of data you want to input: ");
			scanf("%d", &tcase);
			while (tcase--)
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
			if (ROOT == NILL)
			{
				printf("\n +-----------------------------------+\n");
				printf(" |\t     TREE IS EMPTY \t     |\n");
				printf(" +-----------------------------------+\n");
			}
			else
			{
				printf("\n    --- Product's Catalogue --- \n\n");
				printf(" +------+-----------------+----------+\n");
				printf(" |  ID  |     Product     |   Price  |\n");
				printf(" +------+-----------------+----------+\n");
				printf(" |      |                 |          |\n");
				tree_print(ROOT);
				printf(" |      |                 |          |\n");
				printf(" +------+-----------------+----------+\n");
			}
			break;
		case 3:
			if (ROOT == NILL)
			{
				printf("\n +-----------------------------------+\n");
				printf(" |\t     TREE IS EMPTY \t     |\n");
				printf(" +-----------------------------------+\n");
			}
			else
			{
				printf("\nProduct ID: ");
				scanf("%d", &search_key);

				searching(search_key);
			}
			break;
		case 4:
			if (ROOT == NILL)
			{
				printf("\n +-----------------------------------+\n");
				printf(" |\t     TREE IS EMPTY \t     |\n");
				printf(" +-----------------------------------+\n");
			}
			else
			{
				struct node *data;
				printf("\nEnter which product ID that should be deleted: ");
				scanf("%d", &search_key);

				data = searching(search_key);

				if (data != NULL)
				{
					deleteNode(data);

					printf(" +-----------------------------------+\n");
					printf(" |\t      DATA DELETED \t     |\n");
					printf(" +-----------------------------------+\n");
				}
			}
			break;
		case 5:
			if (ROOT == NILL)
			{
				printf("\n +-----------------------------------+\n");
				printf(" |\t     TREE IS EMPTY \t     |\n");
				printf(" +-----------------------------------+\n");
			}
			else
			{
				struct node *data;
				printf("\nEnter which product ID you want to update: ");
				scanf("%d", &search_key);

				data = searching(search_key);

				if (data != NULL)
				{
					update(data);
				}
			}
			break;
		}
	} while (option != 6);
	return 0;
}

void update(struct node *data)
{
	char stock[30];
	int price;

	printf("\n +----------------------------------+\n");
	printf(" |\t   UPDATE YOUR DATA\t    |\n");
	printf(" +----------------------------------+\n");

	printf(" Name: ");
	getchar();
	scanf("%[^\n]", stock);
	printf(" Price: ");
	getchar();
	scanf("%d", &price);

	strcpy(data->stock, stock);
	data->price = price;

	printf("\n +----------------------------------+\n");
	printf(" |\t     DATA UPDATED \t    |\n");
	printf(" +----------------------------------+\n");
}

struct node *maximum(struct node *max)
{
	while (max->right != NILL)
	{
		max = max->right;
	}

	return max;
}

void tree_print(struct node *x)
{
	if (x != NILL)
	{
		tree_print(x->left);
		printf(" | %d | %s\t  | Rp%d  |\n", x->id, x->stock, x->price);
		tree_print(x->right);
	}
}

void red_black_insert(int num, char *data, int prc)
{
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

	while (x != NILL)
	{
		y = x;
		if (z->id <= x->id)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}

	if (y == NILL)
	{
		ROOT = z;
	}
	else if (z->id <= y->id)
	{
		y->left = z;
	}
	else
	{
		y->right = z;
	}

	z->parent = y;

	red_black_insert_fixup(z);
}

void red_black_insert_fixup(struct node *z)
{
	while (z->parent->color == RED)
	{

		/* z's parent is left child of z's grand parent*/
		if (z->parent == z->parent->parent->left)
		{

			/* z's grand parent's right child is RED */
			if (z->parent->parent->right != NULL && z->parent->parent->right->color == RED)
			{
				z->parent->color = BLACK;
				z->parent->parent->right->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}

			/* z's grand parent's right child is not RED */
			else
			{

				/* z is z's parent's right child */
				if (z == z->parent->right)
				{
					z = z->parent;
					left_rotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(z->parent->parent);
			}
		}

		/* z's parent is z's grand parent's right child */
		else
		{

			/* z's left uncle or z's grand parent's left child is also RED */
			if (z->parent->parent->left != NULL && z->parent->parent->left->color == RED)
			{
				z->parent->color = BLACK;
				z->parent->parent->left->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}

			/* z's left uncle is not RED */
			else
			{
				/* z is z's parents left child */
				if (z == z->parent->left)
				{
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

void left_rotate(struct node *x)
{
	struct node *y;

	/* Make y's left child x's right child */
	y = x->right;
	x->right = y->left;
	if (y->left != NILL)
	{
		y->left->parent = x;
	}

	/* Make x's parent y's parent and y, x's parent's child */
	y->parent = x->parent;
	if (y->parent == NILL)
	{
		ROOT = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	/* Make x, y's left child & y, x's parent */
	y->left = x;
	x->parent = y;
}

void right_rotate(struct node *x)
{
	struct node *y;

	/* Make y's right child x's left child */
	y = x->left;
	x->left = y->right;
	if (y->right != NILL)
	{
		y->right->parent = x;
	}

	/* Make x's parent y's parent and y, x's parent's child */
	y->parent = x->parent;
	if (y->parent == NILL)
	{
		ROOT = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	/* Make y, x's parent and x, y's child */
	y->right = x;
	x->parent = y;
}

void deleteNode(struct node *del)
{
	struct node *temp, *temp2;
	int tempColor;

	temp = del;
	tempColor = temp->color;

	if (del->right == NILL && del->left == NILL)
	{
		ROOT = NILL;
		return;
	}

	if (del->right == NILL)
	{
		temp2 = del->left;
		reconnect(del, del->left);
	}
	else if (del->left == NILL)
	{
		temp2 = del->right;
		reconnect(del, del->right);
	}
	else
	{
		temp = maximum(del->left);
		tempColor = temp->color;

		temp2 = temp->left;

		if (temp->parent == del)
		{
			temp2->parent = temp;
		}
		else
		{
			reconnect(temp, temp->left);
			temp->left = del->left;
			temp->left->parent = temp;
		}

		reconnect(del, temp);

		temp->right = del->right;
		temp->right->parent = temp;
		temp->color = del->color;
	}

	if (tempColor == BLACK)
	{
		deleteFixed(del);
	}
}

void deleteFixed(struct node *del)
{
	struct node *temp;

	while (del != ROOT && del->color == BLACK)
	{
		if (del == del->parent->left)
		{
			temp = del->parent->right;

			if (temp->color == RED)
			{
				temp->color = BLACK;
				del->parent->color = RED;
				left_rotate(del->parent);
				temp = del->parent->right;
			}
			if (temp->left->color == BLACK && temp->right->color == BLACK)
			{
				temp->color = RED;
				del->parent->color = BLACK;
				del = del->parent;
			}
			else
			{
				if (temp->right->color == BLACK)
				{
					temp->color = RED;
					temp->left->color = BLACK;
					right_rotate(temp);
					temp = del->parent->right;
				}

				temp->color = del->parent->color;
				del->parent->color = BLACK;
				del->right->color = BLACK;
				left_rotate(del->parent);
				del = ROOT;
			}
		}
		else
		{
			temp = del->parent->left;

			if (temp->color == RED)
			{
				temp->color = BLACK;
				del->parent->color = BLACK;
				right_rotate(del->parent);
				temp = del->parent->left;
			}
			if (temp->left->color == BLACK && temp->right->color == BLACK)
			{
				temp->color = RED;
				del->parent->color = BLACK;
				del = del->parent;
			}
			else
			{
				if (temp->left->color == BLACK)
				{
					temp->color = RED;
					temp->right->color = BLACK;
					left_rotate(temp);
					temp = del->parent->left;
				}

				temp->color = del->parent->color;
				del->parent->color = BLACK;
				temp->left->color = BLACK;
				right_rotate(del->parent);
				del = ROOT;
			}
		}
	}

	del->color = BLACK;
}

void reconnect(struct node *first, struct node *second)
{
	if (first->parent == NILL)
	{
		ROOT = second;
	}
	else if (first == first->parent->left)
	{
		first->parent->left = second;
	}
	else if (first == first->parent->right)
	{
		first->parent->right = second;
	}

	second->parent = first->parent;
}

struct node *searching(int search_key)
{
	struct node *target;
	int flag = 0;

	target = ROOT;

	while (target != NILL)
	{
		if (search_key < target->id)
		{
			target = target->left;
		}
		else if (search_key > target->id)
		{
			target = target->right;
		}
		else if (search_key == target->id)
		{
			flag = 1;
			break;
		}
	}

	if (flag == 1)
	{
		printf("\n +-----------------------------------+\n");
		printf(" |\t       DATA FOUND\t     |\n");
		printf(" +-----------------------------------+\n");
		printf(" |  ID  |     Product     |   Price  |\n");
		printf(" +------+-----------------+----------+\n");
		printf(" |      |                 |          |\n");
		printf(" | %d | %s\t  | Rp%d  |\n", target->id, target->stock, target->price);
		printf(" |      |                 |          |\n");
		printf(" +-----------------------------------+\n\n");

		return target;
	}
	else
	{
		printf("\n+----------------------------------+\n");
		printf("|\t   Data Not Found \t   |\n");
		printf("+----------------------------------+\n\n");

		return NULL;
	}
}