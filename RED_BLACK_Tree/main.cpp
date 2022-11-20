#include "BST.hpp"
#include "RDT.hpp"
#include "../utility/ft_pair.hpp"
//void print_8_colours()
//{
//    for (int i = 0; i < 108; i++)
//    {
//        if (i % 9 == 0 && i != 0)
//            std::cout << std::endl;
//        printf("\033[%dm %3d\033[m", i, i);
//    }
//}

int main(){



    ft::RedBlackTree<ft::pair<int,int> > tree;

//    tree.RBT_insert(7);
//    tree.RBT_insert(3);
//    tree.RBT_insert(18);
//    tree.RBT_insert(10);
//    tree.RBT_insert(22);
//    tree.RBT_insert(8);
//    tree.RBT_insert(11);
//    tree.RBT_insert(26);
//    tree.RBT_insert(2);
//    tree.RBT_insert(6);
//    tree.RBT_insert(13);


    tree.RBT_insert(ft::pair<int,int>(1,2));
    tree.RBT_insert(ft::pair<int,int>(2,2));
    tree.RBT_insert(ft::pair<int,int>(3,2));
    tree.RBT_insert(ft::pair<int,int>(4,2));
    tree.RBT_insert(ft::pair<int,int>(5,2));
    tree.RBT_insert(ft::pair<int,int>(6,2));
    tree.RBT_insert(ft::pair<int,int>(7,2));
    tree.RBT_insert(ft::pair<int,int>(8,2));
    tree.RBT_insert(ft::pair<int,int>(9,2));
    tree.RBT_insert(ft::pair<int,int>(10,2));
    tree.RBT_insert(ft::pair<int,int>(11,2));
    tree.RBT_insert(ft::pair<int,int>(12,2));
    tree.RBT_insert(ft::pair<int,int>(13,2));
    tree.RBT_insert(ft::pair<int,int>(14,2));
    tree.RBT_insert(ft::pair<int,int>(15,2));
    tree.RBT_insert(ft::pair<int,int>(16,2));
    tree.RBT_insert(ft::pair<int,int>(17,2));
    tree.RBT_insert(ft::pair<int,int>(18,2));

//    tree.delete_elem(ft::pair<int,int> (13, 2));
    ft::RedBlackTree<ft::pair<int, int> >::iter  it;
    it  = tree.begin();
    for(; it != tree.end() ; ++it)
    std::cout << (*it).first << std::endl;
//    tree.RBT_insert(2);
//    tree.RBT_insert(3);
//    tree.RBT_insert(4);
//    tree.RBT_insert(5);
//    tree.RBT_insert(6);


//for (int i = 1 ; i < 10 ; ++i)
//    tree.RBT_insert(i);

//    tree.inorder_traverse((tree.root()));

//    std::cout << "----------------------------------------------" << std::endl;
//
// tree.delete_elem(1);
//    tree.delete_elem(11);
//    tree.delete_elem(3);
//    tree.delete_elem(10);
//    tree.delete_elem(22);
//    tree.inorder_traverse((tree.root()));

//
//    tree.print2D((tree.root()));


//    tree.inorder_traverse(tree.root());
//    tree.LeftRotation(tree.root_ref());
//tree.delete_elem(20);
//    std::cout << "----------------------------------------------" << std::endl;
//    std::cout << "----------------------------------------------" << std::endl;


//    tree.print2D((tree.root()));

//    tree.inorder_traverse(tree.root());

//    tree.rdt_insert(38);
//    tree.rdt_insert(45);
//    tree.rdt_insert(44);
//    tree.rdt_insert(60);
//std::cout << "root: " << tree.root()->_data << std::endl;

//    std::cout << tree.search(90, tree._root)->_data << std::endl;
//    std::cout << tree.successor(tree.search(45, tree._root))->_data << std::endl;
//    tree.clear_tree(tree._tree);
//    tree.delete_elem(50);
//    std::cout << "after deletion\n" << std::endl;
//    tree.inorder_traverse(tree._root);
////    tree.print2D(tree._root);

//std::cout << tree.node_uncle(tree.search(11, tree._root))->_data << std::endl;

    return 0;
}

//int main(){
//    ft::RedBlackTree<int> bst;
//    bst.insert(10);
//    bst.insert(5);
//    bst.insert(2);
//    bst.insert(7);
//    bst.insert(20);
//    bst.insert(25);
//    bst.insert(15);
//    bst.insert(12);
////    bst.insert(17);
////    bst.insert(16);
//
//    bst.print2D(bst.root());
//
//        std::cout << "----------------------------------------------" << std::endl;
//    std::cout << "----------------------------------------------" << std::endl;
//    bst.delete_elem(20);
//        bst.print2D(bst.root());
//
//}