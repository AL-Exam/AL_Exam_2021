// Created by Dan10022002 on 08.01.2022

#include <atomic>
template<typename T>
struct Node
{
    T data;
    Node* next;
    Node(const T& data) : data(data), next(nullptr) {}
};
 
template<typename T>
class LockFreeStack
{
    std::atomic<Node<T>*> head;
 public:
 
    // std::memory_order_relaxed не накладывает никаких ограничений,
        // необходима для гарантирования атомарности операции
      
        // std::memory_order_release необходима для того, чтобы
        // запись и чтение в текущем потоке не могли быть переупорядочены,
        // и другие потоки могли видеть данную атомарную переменную
      
        // compare_exchange_weak побитово сравнивает lhs и rhs и меняет
        // lhs на rhs только когда они побитово равны
    
    void Push(const T& data) {
        node<T>* new_node = new node<T>(data);
        new_node->next = head.load(std::memory_order_relaxed); 
        while(!head.compare_exchange_weak(new_node->next, new_node,
                                        std::memory_order_release,
                                        std::memory_order_relaxed));
    }
    
    bool TryPop(T& value) {
        Node* old_head = head.load(std::memory_order_relaxed);
        while (old.head && !head.compare_exchange_weak (old_head, old_head -> next,
                                                        std::memory_order_relaese,
                                                        std::memory_order_relaxed));
        return old_head ? true : false;
    }

};
