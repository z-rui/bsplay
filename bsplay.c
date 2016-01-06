#include "bsplay.h"
#include <assert.h>

void sp_splay(struct sp_node *node)
{
	struct sp_node *P, *GP, *GGP;

	while ((P = node->parent) != 0) {
		if ((GP = P->parent) && (GGP = GP->parent)) {
			link_node(node, GGP, (GGP->left == GP)? &GGP->left : &GGP->right);
		} else {
			node->parent = 0;
		}
		if (P->left == node) {
			if (GP) {
				if (GP->left == P) {
					/* zig-zig */
					link_node(P->right, GP, &GP->left);
					link_node(GP, P, &P->right);
				} else {
					/* zig-zag */
					link_node(node->left, GP, &GP->right);
					link_node(GP, node, &node->left);
				}
			}
			link_node(node->right, P, &P->left);
			link_node(P, node, &node->right);
		} else {
			if (GP) {
				if (GP->right == P) {
					/* zig-zig */
					link_node(P->left, GP, &GP->right);
					link_node(GP, P, &P->left);
				} else {
					/* zig-zag */
					link_node(node->right, GP, &GP->left);
					link_node(GP, node, &node->right);
				}
			}
			link_node(node->left, P, &P->right);
			link_node(P, node, &node->left);
		}
	}
}

void sp_erase(struct sp_node *node, struct sp_node **ptr_root)
{
	struct sp_node *P, **link, *root;

	P = node->parent;
	link = (P == 0) ? ptr_root : (P->left == node) ? &P->left : &P->right;
	if (node->left == 0) {
		root = node->right;
		link_node(root, P, link);
		if (!root) root = P;
		if (root) sp_splay(root);
	} else {
		root = node->left;
		while (root->right)
			root = root->right;
		/* root is the predecessor of node, root->right == NULL */
		node->left->parent = 0;
		sp_splay(root);
		link_node(node->right, root, &root->right);
		link_node(root, P, link);
		sp_splay(root);
	}
	*ptr_root = root;
	node->left = node->right = node->parent = 0;
}
