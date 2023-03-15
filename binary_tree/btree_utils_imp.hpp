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
bool prefix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if (tree->is_empty()) {
        return true;
    }

    // Call the processor function on the current item
    // and set the return value accordingly.
    retVal = p(tree->item());

    // Call prefix_process recursively on the left subtree
    // and right subtree, and update the return value accordingly.
    if (retVal) {
        retVal = prefix_process<T, Processor>(tree->left(), p);
    }
    if (retVal) {
        retVal = prefix_process<T, Processor>(tree->right(), p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool infix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.

    if (!tree->is_empty()) {
        // Call infix_process recursively on the left subtree
        // and update the return value accordingly.
        if (tree->left()->is_empty() || infix_process<T, Processor>(tree->left(), p)) {
            // Call the processor function on the current item
            // and set the return value accordingly.
            retVal = p(tree->item());

            // Call infix_process recursively on the right subtree
            // and update the return value accordingly.
            if (retVal && (tree->right()->is_empty() || infix_process<T, Processor>(tree->right(), p))) {
                return retVal = true;
            }
        }
        return retVal=false;
    }
    retVal = true;
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
    if (!tree->is_empty()) {
        // Call postfix_process recursively on the left subtree
        // and right subtree, and update the return value accordingly.
        if (tree->left()->is_empty() || postfix_process<T, Processor>(tree->left(), p)) {
            if (tree->right()->is_empty() || postfix_process<T, Processor>(tree->right(), p)) {
                // Call the processor function on the current item
                // and set the return value accordingly.
                retVal = p(tree->item());
            }
        }
        return retVal;
    }
    return true;
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
    q.push(tree);

    while (!q.empty() && go_on)
    {
        subtree = q.front();
        q.pop();

        if (subtree && !subtree->is_empty()) // fixed this line
        {
            go_on = p(subtree->item());
            q.push(subtree->left());
            q.push(subtree->right());
        }
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
    if (tree->is_empty()) {
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
std::ostream& print_postfix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a postfix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto print_fn = [&out](T item) -> bool {
        out << item << " ";
        return true;
    };

    postfix_process<T>(tree, print_fn);
    //
    return out;
}

template <class T>
std::ostream& print_breadth_first(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a breadth_first_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto lambda = [&](typename BTree<T>::Ref node) {
        out << node->item() << " ";
        return true;
    };

    auto processor = [&](int item) {
        return lambda(BTree<int>::create(item));
    };

    breadth_first_process<T, decltype(processor)>(tree, processor);
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
    auto prefix_compare = [&it, &count](const T& item) -> bool {
        std::string item_str = std::to_string(item);
        std::string it_str = std::to_string(it);
        if (item_str.size() < it_str.size()) {
            return false;
        }
        bool is_prefix = true;
        for (size_t i = 0; i < it_str.size(); ++i) {
            if (item_str[i] != it_str[i]) {
                is_prefix = false;
                break;
            }
        }
        if (is_prefix) {
            ++count;
        }
        return is_prefix;
    };

    prefix_process<T, decltype(prefix_compare)>(tree, prefix_compare);

    found = (count > 0);

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
    if (tree->is_empty()) {
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
