#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char data[100];
    struct node *left, *right;
}node;

node* newnode(char* x)
{
    node *n =malloc(sizeof(node));
    n->left = n->right = NULL;
    strcpy(n->data, x);
    return n;
}

node* search(node *root, char val[])
{
    if(root == NULL || strcmp(root->data, val) == 0)
        return root;
    else if(strcmp(root->data, val) == 1)
    {
        if(root->left == NULL)
        {
//            printf("\t\t");
//            puts(root->data);
            return root;
        }
        return search(root->left,val);
    }
    else if(strcmp(root->data, val) == -1)
    {
        if(root->right == NULL)
        {
//            printf("\t\t");
//            puts(root->data);
            return root;
        }
        return search(root->right,val);
    }
}
node* Find(node *root,char *data) {
	if(root == NULL)
    {
        printf("\n\tin find\t\n");
        return NULL;
    }
	else if(strcmp(root->data, data) == 0) return root;
	else if(strcmp(root->data, data) == -1) return Find(root->right,data);
	else return Find(root->left,data);
}

node* FindMin(node* root) {
	if(root == NULL) return NULL;
	while(root->left != NULL)
		root = root->left;
	return root;
}
node* FindMax(node* root) {
	if(root == NULL) return NULL;
	while(root->right != NULL)
		root = root->right;
	return root;
}


node* Getsuccessor(node *root,char *data) {

	node* current = Find(root,data);
	if(current == NULL)
	    return NULL;
	if(current->right != NULL) {
		return FindMin(current->right);
	}
	else {
		node* successor = NULL;
		node* ancestor = root;
		while(ancestor != current) {
			if(strcmp(current->data, ancestor->data) == -1) {
				successor = ancestor;
				ancestor = ancestor->left;
			}
			else
				ancestor = ancestor->right;
		}
		return successor;
	}
}
node* GetAncestor(node *root,char *data) {
	node* current = Find(root,data);
	if(current == NULL)
	    return NULL;
	if(current->left != NULL) {
		return FindMax(current->left);
	}
	else {
		node* successor = root;
		node* ancestor = NULL;
		while(successor != current) {
			if(strcmp(current->data, successor->data) == 1) {
				ancestor=successor;
				successor = successor->right;
			}
			else
				successor = successor->left;
		}
		return ancestor;
	}
}

node* insert(node *root, char x[])
{
    if (root == NULL)
    {
        node *n = newnode(x);
        root = n;
    }
    else if(strcmp(x, root->data) == -1)
        root -> left = insert(root->left, x);
    else if(strcmp(x, root->data) == 1)
        root ->right = insert(root->right, x);

    return root;
}

void inorder(node *root)
{
    if(root)
    {
        inorder(root->left);
        puts(root->data);
        inorder(root->right);
    }
}

int height(node*root)
{
    if(root==NULL)
        return -1;
    else
    {
          int l = 1+height(root->left);
          int r = 1+height(root->right);
          return l>r?l:r;
    }
}

int main()
{
    node *root = NULL;
    FILE *dic = fopen("Dictionary.txt", "r");
    char word[100];
    int c=0;
    while(!feof(dic))
    {
        fscanf(dic, "%s", word);
        int i=0;
        while(i<strlen(word))
        {
            word[i]=tolower(word[i]);
            i++;
        }
        root = insert(root, word);
        c++;
    }
    printf("Dictionary Loaded Successfuly...!\n");
    printf(".................................\n");
    printf("Size = %d\n",c);
    printf(".................................\n");
    printf("Height = %d\n",height(root));
    printf(".................................\n");
    printf("Enter a sentence :\n");
    char input[200];
    gets(input);
    char *token = strtok(input, " ");
    while(token != NULL)
    {
        printf("\n");
        printf("%s - ", token);
        int i=0;
        while(i<strlen(token))
        {
            token[i]=tolower(token[i]);
            i++;
        }
        node *nn = search(root, token);
        if(strcmp(nn, token) == 0)
            printf("Correct\n");
        else
        {
            printf("Incorrect, Suggestions : ");
            printf("%s, ",nn->data);
            node *successor = Getsuccessor(root, nn->data);
            if(successor) printf("%s, ", successor);
            node* ancestor = GetAncestor(root, nn->data);
            if(successor) puts(ancestor->data);
        }
        printf("\n");
        token = strtok(NULL, " ");
    }
    fclose(dic);
    return 0;
}
