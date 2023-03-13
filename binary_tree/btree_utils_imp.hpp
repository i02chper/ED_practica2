/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <queue>

#include "btree_utils.hpp"

template<class T>
int compute_height (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    int height = 0;
    //TODO
    int leftHeigth = 0, rightHeigth = 0;

    if(t->is_empty())
    {
        return -1;
    }

    leftHeigth = compute_height<T>(t->left());
    rightHeigth = compute_height<T>(t->right());

    if (rightHeigth >= leftHeigth)
    {
        height = 1 + rightHeigth;
    }
    else
    {
        height = 1 + leftHeigth;
    }
    //
    return height;
}

template<class T>
size_t compute_size (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    size_t ret_val = 0;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.

    if(t->is_empty())
    {
    return 0;
    }

    ret_val ++;

    ret_val = ret_val + compute_size<T>(t->left());
    ret_val = ret_val + compute_size<T>(t->right());
    //
    return ret_val;
}

template <class T, typename Processor>
bool
prefix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(tree->is_empty() == false)
    {
        retVal = p(tree->item());
        auto left = tree->left();
        if(left->is_empty() == false)
        {
            retVal = retVal && prefix_process<T>(left,p);
        }
        auto right = tree->right();
        if(right->is_empty() == false)
        {
            retVal = retVal && prefix_process<T>(right,p);
        }
    }
    //
    return retVal;
}

template <class T, class Processor>
bool
infix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(not tree->is_empty())
    {
        auto left = tree->left();
        if(left->is_empty() == false)
        {
            retVal = infix_process<T>(left, p);
        }
        retVal = retVal && p(tree->item());

        auto right = tree->right();
        if(right->is_empty() == false)
        {
            retVal = retVal && infix_process<T>(right,p);
        }
    }
    //
    return retVal;
}

template <class T, class Processor>
bool
postfix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(not tree -> is_empty())
    {
        auto left = tree->left();
        if(left->is_empty() == false)
        {
            retVal = postfix_process<T>(left,p);
        }
        auto right = tree->right();
        if(right->is_empty() == false)
        {
            retVal = retVal && postfix_process<T>(right,p);
        }
        retVal = retVal && p(tree->item());
    }
    //
    return retVal;
}


template <class T, class Processor>
bool
breadth_first_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool go_on = true;
    //TODO
    //Hint: think about which data structure can help you to do this kind 
    //  of traversal.
    typename BTree<T>::Ref subtree;
    std::queue<typename BTree<T>::Ref> q;
    q.push(tree);// encolamos el árbol antes de empezar.

    while(!q.empty() && go_on)
    {
        subtree = q.front();    // igualamos al subtree al frente
        if (!subtree->is_empty())
        {
        go_on = p(subtree->item());
        q.push(subtree->right()); // metemos el arbol derecho en la cola
        q.push(subtree->left()); //metemos el árbol izquierdo en la cola
        }
        q.pop();
    }

    //
    return go_on;
}

template <class T>
std::ostream&
print_prefix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a prefix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    if (tree->is.empty()) {
        return out;
    }

    out << tree->item() << " "; // output the current node's value

    // recursively output the left and right subtrees
    print_prefix<T>(out, tree->left());
    print_prefix<T>(out, tree->right());
    //
    return out;
}

template <class T>
std::ostream&
print_infix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use an infix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    if (!tree->is_empty())
    {
        print_infix<T>(out, tree->left());
        out << tree->item() << " ";
        print_infix<T>(out, tree->right());
    }
    //
    return out;
}

template <class T>
std::ostream&
print_postfix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a postfix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    if (!tree->is_empty())
    {
        print_infix<T>(out, tree->left());
        print_infix<T>(out, tree->right());
        out << tree->item() << " ";
    }
    //
    return out;
}

template <class T>
std::ostream&
print_breadth_first(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a breadth_first_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    if (tree->is_empty()){
        return out;
    }

    std::queue<typename BTree<T>::Ref> q;
    q.push(tree);

    while (!q.empty()){
        typename BTree<T>::Ref curr = q.front();
        q.pop();
        out << curr->item() << " ";
        if (curr->left()){
            q.push(curr->left());
        }
        if (curr->right()) {
        q.push(curr->right());
        }
    }
    //
    return out;
}

template <class T>
bool search_prefix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the prefix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    if (tree->is_empty())
    {
            return found;
    }
    count++;
    if (tree->item() == it) {
        found = true;
    }
    found = search_prefix<T>(tree->left(), it, count);
    found = search_prefix<T>(tree->right(), it, count);


    //
    return found;
}

template <class T>
bool search_infix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the infix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    if (tree->is_empty()) {
        return found;
    }
    count++;
    if (search_infix<T>(tree->left(), it, count)) {
        found = true;
    }

    if (tree->item() == it) {
        found = true;
    }

    count++;
    if (search_infix<T>(tree->right(), it, count)) {
        found = true;
    }

    //
    return found;
}

template <class T>
bool search_postfix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the postfix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    std::queue<typename BTree<T>::Ref> q;
    q.push(tree);

    while (!q.empty()) {
        count++;
        typename BTree<T>::Ref node = q.front();
        q.pop();

        if (node->left()) {
            q.push(node->left());
        }
        if (node->right()) {
            q.push(node->right());
        }

        if (node->item() == it) {
            found = true;
        }
    }
    //
    return found;
}

template <class T>
bool search_breadth_first(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the breadth_first_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    if (tree->is.empty()) {
        return found;
    }

    std::queue<typename BTree<T>::Ref> q;
    q.push(tree);

    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        count++;

        if (node->item() == it) {
            found = true;
        }

        if (node->left() != nullptr) {
            q.push(node->left());
        }

        if (node->right() != nullptr) {
            q.push(node->right());
        }
    }
    //
    return found;
}


template<class T>
bool check_btree_in_order(typename BTree<T>::Ref const& tree)
{
    bool ret_val = true;
    //TODO
    //Hint: You can create a lambda function with a parameter to compare it with
    // the last the value seen.
    // Use the lambda with the infix_process.
    if (!tree) {
        // un arbol vacio siempre esta en orden
        return ret_val;
    }
    // miramos el izquierdo
    if (tree->left() && (tree->left()->item() >= tree->item())) {
        return false;
    }
    bool left_in_order = check_btree_in_order<T>(tree->left());

    // miramos el derecho
    if (tree->right() && (tree->right()->item() <= tree->item())) {
        return false;
    }
    bool right_in_order = check_btree_in_order<T>(tree->right());

    // si ambos estan en orden pues devolvemos true
    if(left_in_order && right_in_order)
    {
        ret_val = true;
    }else{
        ret_val = false;
    }


    //
    return ret_val;
}

template<class T>
bool has_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));    
    bool ret_val = false;
    //TODO
    if (tree == nullptr) {
        return ret_val;
    }

    auto node = tree;
    while (node != nullptr) {
        if (node->item() == v) {
            ret_val= true;
        }
        if (v < node->item()) {
            node = node->left();
        } else {
            node = node->right();
        }
    }
    //
    return ret_val;
}

template <class T>
void insert_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));
    //TODO
    if (tree == nullptr) {
        tree = BTree<T>::create(v);
    } else if (v < tree->item()) {
        insert_in_order<T>(tree->left(), v);
    } else if (tree->item() < v) {
        insert_in_order<T>(tree->right(), v);
    }

    //
    assert(has_in_order<T>(tree, v));
}
