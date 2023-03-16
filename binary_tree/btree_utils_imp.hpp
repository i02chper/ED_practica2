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
    if (!tree->is_empty())
    {
        retVal = p(tree->item());
        retVal = retVal && prefix_process<T,Processor>(tree->left(),p);
        retVal = retVal && prefix_process<T,Processor>(tree->right(),p);
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
    if(!tree->is_empty())
    {
        retVal = infix_process<T,Processor>(tree->left(),p);
        retVal = retVal && p(tree->item());
        retVal = retVal && infix_process<T,Processor>(tree->right(),p);
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
    if(!tree->is_empty())
    {
        retVal = postfix_process<T,Processor>(tree->left(),p);
        retVal = retVal && postfix_process<T,Processor>(tree->right(),p);
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
    q.push(tree); //Encolamos el árbol antes de empezar

    while (!q.empty() && go_on)
    {
        subtree = q.front();      //Igualamos al subtree al frente de la cola
        if (!subtree->is_empty()) //Mientras que el subtree no esté vacío, entramos en la condición
        {
            go_on = p(subtree->item());
            q.push(subtree->left());  //Metemos el árbol izquierdo en la cola
            q.push(subtree->right()); //Metemos el árbol derecho en la cola
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
    auto p = [&it, &count, &found](const T& x) {
        count++;
        if (x == it) {
            found = true;
        }
        return true;
    };

    prefix_process<T>(tree, p);
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
    auto process = [&](const T& x) {
        count++;
        if (x == it) {
            found = true;
            return false;
        }
        return true;
    };

    infix_process<T>(tree, process);
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

    auto process = [&](const T& x) {
        count++;
        if (x == it) {
            found = true;
            return false;
        }
        return true;
    };

    postfix_process<T>(tree, process);
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
    auto process = [&](const T& x) {
        count++;
        if (x == it) {
            found = true;
            return false;
        }
        return true;
    };

    breadth_first_process<T>(tree, process);
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
    if(!tree->is_empty())
    {
        if(!tree->left()->is_empty()) //si está vacío, no hace falta que entremos
        {
            auto maxValue = [=] ()->T{
                auto current = tree->left();
                while(!current->right()->is_empty())
                    current = current->right();
                return current->item();
            };
            if(maxValue() > tree->item()) //comparamos con el valor máximo calculado. si no se cumple no esta ordenado
                ret_val = false;
        }

        if(!tree->right()->is_empty())// si esta vacio ni entramos
        {
            auto minValue = [=]()->T{ //Funcion lambda que calcula el valor mínimo
                auto current = tree->right();
                while(!current->left()->is_empty())
                    current=current->left();
                return current->item();
            };
            if(minValue() < tree->item())
                ret_val=false;
        }

        if(!check_btree_in_order<T>(tree->left()) || !check_btree_in_order<T>(tree->right())) //comprobamos que ninguno de los subarboles esta desornedados
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
    if(!tree->is_empty())//si el arbol esta vacio no entramos ya que no hay nada que buscar
    {
        if(v < tree->item()) //Si el valor que buscamos es menor que el nodo raiz buscamos por la rama izquierda ya que el árbol está ordenado
            ret_val = has_in_order<T>(tree->left(),v);
        else if(v > tree->item())//Si el valor que buscamos es mayor que el nodo raiz, buscamos por la rama derecha.
            ret_val = has_in_order<T>(tree->right(),v);
        else //Si es igual, delvolvemos true, ya que lo hemos encontrado
            ret_val = true;
    }
    //
    return ret_val;
}

template <class T>
void insert_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));
    //TODO
    if(tree->is_empty()) //si el árbol esta vacio, creamos directamente el nodo raiz
        tree->create_root(v);
    else if(v < tree->item())
    {
        if(tree->left()->is_empty())//Si el valor que queremos insertar es menor que el item del nodo raiz, vamos por la izquierda
            tree->set_left(BTree<T>::create(v));
        else
            insert_in_order<T>(tree->left(),v);
    }
    else if (v > tree->item()) //Si el valor que queremos insertar es mayor que el item del nodo raiz, vamos por la derecha
    {
        if(tree->right()->is_empty())
            tree->set_right(BTree<T>::create(v));
        else
            insert_in_order<T>(tree->right(),v);
    }
    //
    assert(has_in_order<T>(tree, v));
}
