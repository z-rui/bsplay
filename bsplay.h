#ifndef BSPLAY_H
#define BSPLAY_H

#include <stddef.h>

#ifdef container_of
# undef container_of
#endif
#define container_of(x, t, f) ((t *)((char *) (x) - offsetof(t, f)))

struct sp_node {
	struct sp_node *parent, *left, *right;
};

extern void sp_splay(struct sp_node *node);
extern void sp_erase(struct sp_node *node, struct sp_node **ptr_root);

static inline void link_node(struct sp_node *node, struct sp_node *parent, struct sp_node **link)
{
	*link = node;
	if (node)
		node->parent = parent;
}
#endif
