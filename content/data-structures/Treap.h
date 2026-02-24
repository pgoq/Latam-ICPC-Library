
/**
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data. apply updates the node, push updates children with lazy value.
 * Time: $O(\log N)$
 */
#pragma once
mt19937 rng(123);
struct Node{ // cnt = size of subtree
    Node *l = NULL, *r = NULL;
    int val, cnt = 1;
    uint32_t y;
    Node(){}
    Node(int val) : val(val), y(rng()) {}
    void calc(), push(), apply();
};
int size(Node *n) { return !n ? 0 : n->cnt; }
void Node::calc() { cnt = size(l) + size(r) + 1; }
void Node::apply(){}
void Node::push(){
	if(l) l->apply();
	if(r) r->apply();
}
Node buffer[ms];
// {< x, >= x}
pair<Node*, Node*> split(Node *p, int x){
    if(!p) return {NULL, NULL};
	p->push();
    if(size(p->l) < x){ // "p" stays on the left
        auto [L, R] = split(p->r, x - size(p->l) - 1);
        p->r = L;
        p->calc();
        return {p, R};
    }
    else{ // "p" stays on the right
        auto [L, R] = split(p->l, x);
        p->l = R;
        p->calc();
        return {L, p};
    }
}
 
Node* merge(Node *a, Node *b){
    if(!a) return b;
    if(!b) return a;
	a->push(), b->push();
    if(a->y > b->y){
        a->r = merge(a->r, b);
        a->calc();
        return a;
    }
    else{
        b->l = merge(a, b->l);
        b->calc();
        return b;
    }
}