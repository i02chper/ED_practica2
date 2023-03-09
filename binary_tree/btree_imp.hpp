/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include "btree.hpp"

template<class T>
BTNode<T>::BTNode (T const& it, BTNode<T>::Ref l,
                   BTNode<T>::Ref r)
{
    //TODO
    this->item_ = it;
    this->right_ = r;
    this->left_ = l;
    //
    assert(item()==it);
    assert(left()==l);
    assert(right()==r);
}

template<class T>
typename BTNode<T>::Ref BTNode<T>::create(T const& it,
                                          BTNode<T>::Ref left,
                                          BTNode<T>::Ref right)
{
    return std::make_shared<BTNode<T>> (it, left, right);
}

template<class T>
T BTNode<T>::item() const
{

    T ret_v;
    //TODO
    ret_v = this->item_;
    //
    return ret_v;
}



template<class T>
typename BTNode<T>::Ref BTNode<T>::left() const
{

    typename BTNode<T>::Ref child;
    //TODO
    child = this->left_;
    //
    return child;
}


template<class T>
typename BTNode<T>::Ref BTNode<T>::right() const
{

    typename BTNode<T>::Ref child;
    //TODO
    child = this->right_;
    //
    return child;
}

template<class T>
void BTNode<T>::set_item(const T& new_it)
{
    //TODO
    this->item_ = new_it;
    //
    assert(item()==new_it);
}

template<class T>
void BTNode<T>::set_left(BTNode<T>::Ref new_child)
{
    //TODO
    this->left_ = new_child;
    //
    assert(left()==new_child);
}

template<class T>
void BTNode<T>::set_right(BTNode<T>::Ref new_child)
{
    //TODO
    this->right_ = new_child;
    //
    assert(right()==new_child);
}

/**
 * ADT BTree.
 * Models a BTree of T.
 */
template<class T>
BTree<T>::BTree ()
{
    //TODO
    this->root_ = nullptr;
    //
    assert(is_empty());
}

    template<class T>
BTree<T>::BTree (const T& it)
{
    //TODO
    this->root_ = typename BTNode<T>::Ref(new BTNode<T>(it, nullptr, nullptr));
    //
    assert(!is_empty());
    assert(item()==it);
    assert(left()->is_empty());
    assert(right()->is_empty());
}

template<class T>
typename BTree<T>::Ref BTree<T>::create()
{
    return std::make_shared<BTree<T>> ();
}

template<class T>
typename BTree<T>::Ref BTree<T>::create(T const& item)
{
    return std::make_shared<BTree<T>>(item);
}

template<class T>
typename BTree<T>::Ref BTree<T>::create (std::istream& in) noexcept(false)
{
    auto tree = BTree<T>::create();
    std::string token;
    //TODO
    //Remember: throw std:runtime_error exception with text
    //"Wrong input format." when an input format error is found.
    in >> token;

    if(!in)
    {
        throw std::runtime_error("Wrong input format.");
    }

    if (token == "[")
    {
        T new_item; // en este item almaceno el item que leemos del stream y que vamos a meter en el árbol
        in >> token;
        std::istringstream aux(token); // hay que hacerlo como en la practica 1, ya que no podemos cargar el token directamente en el new_item
        aux >> new_item;
        tree->create_root(new_item);
        tree->set_left(create(in));
        tree->set_right(create(in));
        in >> token;// si no se añade esta linea da error los tests;
        if (token != "]")
        {
            throw std::runtime_error("Wrong input format.");
        }
    }else if ( token != "[]") //si el stream es un un arbol vacio el formato no es [], nos da error de formato
    {
        throw std::runtime_error("Wrong input format.");
    }
    //
    return tree;
}

template<class T>
bool BTree<T>::is_empty () const
{
    bool ret_v = false;
    //TODO
    if (this->root_ == nullptr)
    {
        ret_v = true;
    }
    //
    return ret_v;
}

template<class T>
  T BTree<T>::item() const
  {
    assert(!is_empty());
    T ret_v;
    //TODO
    ret_v = this->root_->item();
    //
    return ret_v;
  }

template<class T>
typename BTree<T>::Ref BTree<T>::left() const
{
    assert(!is_empty());
    BTree<T>::Ref subtree = nullptr;
    //TODO
    //Hint: use the private constructor given a root node.
    subtree = BTree<T>::create();
    subtree->root_ = this->root_->left();
    //
    return subtree;
}

template<class T>
 typename BTree<T>::Ref BTree<T>::right() const
 {
    assert(!is_empty());
    BTree<T>::Ref subtree = nullptr;
    //TODO
    //Hint: use the private constructor given a root node.
    subtree = BTree<T>::create();
    subtree->root_ = this->root_->right();
    //
    return subtree;
 }

template<class T>
std::ostream& BTree<T>::fold(std::ostream& out) const
{
    //TODO

    if (this->root_ == nullptr) // en caso de que es este vacio el out sera []
    {
        out << "[]";
    }
    else
    {
        out << "[ ";
        out << this->root_->item();
        out << " ";
        this->left()->fold(out);
        out << " ";
        this->right()->fold(out);
        out << " ]";
    }
    //
    return out;
}

  template<class T>
void BTree<T>::create_root(const T& it)
{
    assert(is_empty());
    //TODO
    this->root_ = typename BTNode<T>::Ref(new BTNode<T>(it, nullptr, nullptr));//creo un puntero a nodo con item = item
    //
    assert(!is_empty());
    assert(item()==it);
    assert(left()->is_empty());
    assert(right()->is_empty());

}

template<class T>
void BTree<T>::set_item(const T& new_it)
{
    assert(!is_empty());
    //TODO
    this->root_->set_item(new_it);
    //
    assert(item()==new_it);
}

template<class T>
void BTree<T>::set_left(typename BTree<T>::Ref new_left)
{
    assert(!is_empty());
    //TODO
    this->root_->set_left(new_left->root_);
    //
    assert(left()->root()==new_left->root());
}

template<class T>
void BTree<T>::set_right(typename BTree<T>::Ref new_right)
{
    assert(!is_empty());
    //TODO
    this->root_->set_right(new_right->root_);
    //
    assert(right()->root()==new_right->root());
}

template<class T>
BTree<T>::BTree (typename BTNode<T>::Ref n)
{
    //TODO
    this->create_root(n);
    /*auto tree = BTree<T>::create();
    tree->create_root(n);*/
    //
    assert(root()==n);
}

template<class T>
typename BTree<T>::Ref BTree<T>::create(typename BTNode<T>::Ref root)
  {
      //We cannot use std::make_shared here
      //because the constructor is protected.
      typename BTree<T>::Ref tree ( new BTree<T>(root) );
      return tree;
  }

template<class T>
typename BTNode<T>::Ref BTree<T>::root() const
{
    typename BTNode<T>::Ref node;
    //TODO
    node = this->root_;
    //
    return node;
}

template<class T>
void BTree<T>::set_root(typename BTNode<T>::Ref new_root)
{
    //TODO
    this->root_ = new_root;
    //
    assert(root()==new_root);
}

