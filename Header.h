#pragma once
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
#include<utility>
#include<queue>
#include<type_traits>
namespace panos {//prajeis gia iterators,allocator_support
    //rota sisia gia move semantics
    //swap funcs?? 
    // pio kaloi iterators??



#define _NODISCARD [[nodiscard]]
    template<class u, class allocator = std::allocator<u>>
    class single_linked_list final {
    private:

        class list_node {
        public:
            list_node* next;
            u data;



            inline  list_node()noexcept :data{ 0 }, next{ nullptr }
            {

            }

            inline  list_node(const u& data1) : data{ data1 }, next{ nullptr }
            {

            }


            inline list_node(u&& data1) :data{ std::move(data1) }, next{ nullptr }
            {


            }





        };
        // list_node(const u& data1)->list_node<u data1>;
        class ITERATOR {
            list_node* it;
        public:
            inline ITERATOR()noexcept {
                it = nullptr;
            }
            ITERATOR(list_node* a)noexcept {

                it = a;
            }
            inline void operator ++() {
                if (it != nullptr) {
                    it = it->next;
                    return;
                }
                abort();

            }
            inline void operator ++(int not_used) {
                if (it != nullptr) {
                    it = it->next;
                    return;
                }
                abort();


            }
            _NODISCARD inline bool operator !=(list_node* a) {
                if (it == a)return 0;
                return 1;
            }
            inline void operator =(list_node* a) {
                it = a;
            }
            _NODISCARD inline u& operator *()& {
                //std::cout << "pateras"<<'\n';
                if (it != nullptr) {
                    return it->data;
                }
                abort();
            }
            _NODISCARD inline u operator *()&& {

                if (it == nullptr)abort();
                return std::move(it->data);



            }

        };
        class CONST_ITERATOR {
            list_node* it;
        public:
            inline CONST_ITERATOR()noexcept {
                it = nullptr;
            }
            inline CONST_ITERATOR(list_node* a)noexcept {
                it = a;
            }
            inline void operator ++() {
                if (it != nullptr) {
                    it = it->next;
                    return;
                }

                abort();


            }
            inline void operator ++(int not_used) {
                if (it != nullptr) {
                    it = it->next;
                    return;
                }
                abort();

            }
            _NODISCARD inline bool operator !=(list_node* a) {
                if (it == a)return 0;
                return 1;
            }
            inline void operator =(list_node* a) {
                it = a;
            }
            _NODISCARD inline const u& operator *()const& {

                if (it != nullptr) {
                    return it->data;
                }
                abort();
            }
            _NODISCARD inline const u operator *()const&& {//rota sisia ,telei const h oxi gia return

                if (it == nullptr)abort();
                return std::move(it->data);



            }
        };

        size_t size1 = 0;
        list_node* head;
        list_node* ptr;


    public:

        static_assert(std::is_object_v<u>, "The C++ Standard forbids containers of non-object types ");
        static_assert(!std::is_const_v<u>, "The C++ Standard forbids containers of const elements ");
        // std::is_const<T>::value will return true only if T is a const - qualified type.
        // It does not check whether the pointer itself is const; it only checks if the type being pointed to is const.
        static_assert(!std::is_reference_v<u>, "The C++ Standard forbids allocators for reference elements ");
        static_assert(!std::is_function_v<u>, "The C++ Standard forbids allocators for function elements "
            "because of [allocator.requirements].");
        //iterators
        using iterator = ITERATOR;
        using const_iterator = CONST_ITERATOR;
        using allocator_type = allocator;
        using value_type = u;

        //constructors
        inline single_linked_list() noexcept :head{ nullptr }, ptr{ nullptr }, size1{ 0 }
        {



        }
        inline  single_linked_list(const std::initializer_list<u>& a)noexcept :head{ nullptr }, ptr{ nullptr }, size1{ 0 } {

            const u* b = a.begin();

            for (size_t i = 0; i < a.size(); i++) {
                push_back(*b);
                b++;
            }
        }
        inline single_linked_list(const single_linked_list& a)noexcept {//efoson edo kano mono copies yparxei pitanothta na kanei throw kano mono sto stack allocations kai to push back exei noexcept 

            if (this != &a) {


                const list_node* ptr1 = a.head;

                for (size_t i = 0; i < a.size1; i++) {
                    push_back(ptr1->data);

                    ptr1 = ptr1->next;

                }
                size1 = a.size1;
                if (size1 == 0) {//empty object to empty object
                    head = nullptr;
                    ptr = nullptr;
                }
            }
            else {

                head = nullptr;
                size1 = 0;
                ptr = nullptr;

            }
            return;

        }

        inline single_linked_list(single_linked_list&& a) noexcept(std::is_nothrow_move_constructible_v<u>) {//ofeilo kai na prosteso to idio gia olo to list node 
            static_assert(std::is_nothrow_move_constructible_v<u>, "the move constructor might throw");
            if (this != &a) {


                //list_node* ptr1 = a.head;
                //for (size_t i = 0; i < a.size1; i++) {
                //    push_back(std::move(ptr1->data));

                //    ptr1 = ptr1->next;

                //}
                head = std::exchange(a.head, nullptr);
                ptr = std::exchange(a.ptr, nullptr);
                size1 = std::exchange(a.size1, 0);



            }
            else {

                head = nullptr;
                size1 = 0;
                ptr = nullptr;

            }
            return;

        }


        //functions of the class

        inline void push_back(const u& data1) noexcept {//ginetai na kanei throw h push_back();
            if (size1 == 4294967295) {
                std::cout << "out of size\n";
                exit(1);
            }
            if (size1 == 0) {
                size1++;
                head = new(std::nothrow) list_node(data1);

                if (head == nullptr) { exit(1); };
                ptr = head;


            }
            else {
                size1++;
                ptr->next = new(std::nothrow) list_node(data1);
                if (ptr->next == nullptr) { exit(1); };
                ptr = ptr->next;

            }
            return;
        }

        inline void push_back(u&& data1)noexcept {
            if (size1 == 4294967295) {
                std::cout << "out of size\n";
                exit(1);
            }
            if (size1 == 0) {
                size1++;
                head = new(std::nothrow) list_node(std::move(data1));

                if (head == nullptr) { exit(1); };
                ptr = head;


            }
            else {
                size1++;
                ptr->next = new(std::nothrow) list_node(std::move(data1));
                if (ptr->next == nullptr) { exit(1); };
                ptr = ptr->next;
            }
            return;
        }

        /* template<typename t>
         requires(std::is_same_v<u,int> || std::is_same_v<u,std::string>||std::is_same_v<u,unsigned int> || std::is_same_v<u, short int> || std::is_same_v<u,unsigned short int> || std::is_same_v<u, long int> || std::is_same_v<u,unsigned long int> || std::is_same_v<u, long long int> || std::is_same_v<u, unsigned long long int > || std::is_same_v<u,signed char> || std::is_same_v<u,unsigned char > || std::is_same_v<u, float> || std::is_same_v<u,double> || std::is_same_v<u,long double> || std::is_same_v<u, wchar_t> || std::is_same_v<u, char>)
         inline void show(const t& a)const noexcept {
             using std::cout;
              list_node* ptr1 = head;
              for (size_t i = 0; i < size1; i++) {
                  cout << ptr1->data << '\n';
                  ptr1 = ptr1->next;
              }

              return;
         }*/
        template<typename  t = char>
            requires(std::is_same_v<u, int> || std::is_same_v<u, std::string> || std::is_same_v<u, unsigned int> || std::is_same_v<u, short int> ||
        std::is_same_v<u, unsigned short int> || std::is_same_v<u, long int> || std::is_same_v<u, unsigned long int> || std::is_same_v<u, long long int> ||
            std::is_same_v<u, unsigned long long int> || std::is_same_v<u, signed char> || std::is_same_v<u, unsigned char> || std::is_same_v<u, float> || std::is_same_v<u, double> || std::is_same_v<u, long double> ||
            std::is_same_v<u, wchar_t> || std::is_same_v<u, char> || std::is_same_v<u, const char*>)
            inline void show()const noexcept {
            using std::cout;
            list_node* ptr1 = head;
            for (size_t i = 0; i < size1; i++) {
                cout << ptr1->data << '\n';
                ptr1 = ptr1->next;
            }

            return;
        }

        inline void pop_back()noexcept {
            if (size1 > 1) {
                delete ptr;
                size1--;
                ptr = head;
                for (int i = 0; i < size1 - 1; i++) {
                    ptr = ptr->next;
                }
                ptr->next = nullptr;
                return;

            }
            else if (size1 == 1) {
                size1 = 0;
                ptr = nullptr;
                delete head;
                head = nullptr;
            }

            return;

        }
        _NODISCARD inline  bool empty()const noexcept {
            if (head == nullptr)return true;
            else return false;
        }

        inline void sort()const noexcept {//maybe faster with priority queue
            using std::priority_queue;
            using std::vector;
            if (size1 != 0) {
                /*  for (size_t i = 0; i < size1 - 1; i++) {

                      list_node* ptr1 = head;
                      for (size_t j = 0; j < size1 - i - 1; j++) {
                          if (ptr1 != nullptr && ptr1->next != nullptr) {
                              if (ptr1->data > ptr1->next->data) {
                                  u temp = ptr1->data;
                                  ptr1->data = ptr1->next->data;
                                  ptr1->next->data = temp;
                              }
                              ptr1 = ptr1->next;
                          }

                      }
                  }*/
                priority_queue<u, vector<u>, std::greater<u>>a;
                list_node* ptr1 = head;
                for (size_t i = 0; i < size1; i++) {
                    a.push(ptr1->data);
                    ptr1 = ptr1->next;

                }
                ptr1 = head;

                for (size_t i = 0; i < size1; i++) {
                    ptr1->data = a.top();
                    ptr1 = ptr1->next;
                    a.pop();

                }

            }
            return;
        }
        _NODISCARD inline list_node* begin()const noexcept {
            return head;
        }
        _NODISCARD inline list_node* end()const noexcept {
            return nullptr;
        }
        _NODISCARD inline list_node* cbegin()const noexcept {
            return head;
        }
        _NODISCARD inline list_node* cend() {
            return nullptr;
        }
        inline size_t size() const noexcept {
            return size1;
        }
        inline void clear() const noexcept {
            this->~single_linked_list();
        }
        inline void reverse()const  noexcept {
            using std::vector;
            vector<u>k;
            list_node* ptr1 = head;
            for (size_t i = 0; i < size1; i++) {
                k.push_back(ptr1->data);
                ptr1 = ptr1->next;
            }
            std::reverse(k.begin(), k.end());
            ptr1 = head;
            for (size_t i = 0; i < size1; i++) {
                ptr1->data = k[i];
                ptr1 = ptr1->next;
            }

            return;
        }


        //overloaded operators



        inline void operator =(const single_linked_list& a)noexcept {

            if (this != &a) {
                if (this->head != nullptr) {

                    this->~single_linked_list();


                    const list_node* ptr1 = a.head;
                    for (size_t i = 0; i < a.size1; i++) {
                        push_back(ptr1->data);

                        ptr1 = ptr1->next;
                    }
                    size1 = a.size1;
                }
                else {


                    const  list_node* ptr1 = a.head;
                    for (size_t i = 0; i < a.size1; i++) {
                        push_back(ptr1->data);

                        ptr1 = ptr1->next;
                    }
                    size1 = a.size1;

                }


            }
            return;
        }
        inline void operator=(single_linked_list&& a)noexcept(std::is_nothrow_move_assignable_v<u>) {
            //ta mporouses na allajeis deiktes kai apla to head=a.head kai na mhn kaneis deallocate alla rota sisia ??
            static_assert(std::is_nothrow_move_assignable_v<u>, "the move assigment operator might throw");
            if (this != &a) {
                if (this->head != nullptr) {
                    if (a.head == nullptr) {
                        this->~single_linked_list();
                        return;
                    }
                    this->~single_linked_list();


                    /*  list_node* ptr1 = a.head;
                      for (size_t i = 0; i < a.size1; i++) {
                          push_back(std::move(ptr1->data));
                          std::cout << ptr1->data << '\n';
                          ptr1 = ptr1->next;
                      }*/
                    head = std::exchange(a.head, nullptr);
                    ptr = std::exchange(a.ptr, nullptr);
                    size1 = std::exchange(a.size1, 0);
                }
                else {

                    if (a.head == nullptr) {
                        return;
                    }
                    /*  list_node* ptr1 = a.head;

                      for (size_t i = 0; i < a.size1; i++) {
                          push_back(std::move(ptr1->data));

                          ptr1 = ptr1->next;
                      }*/
                    head = std::exchange(a.head, nullptr);
                    ptr = std::exchange(a.ptr, nullptr);
                    size1 = std::exchange(a.size1, 0);

                }


            }
            else {
                this->~single_linked_list();
            }
            return;
        }
        //inline void operator=(single_linked_list&& a) noexcept(std::is_nothrow_move_assignable_v<u>) {
        //    static_assert(std::is_nothrow_move_assignable_v<u>, "the move assignment operator might throw");

        //    if (this != &a) {
        //        // Καθαρίζουμε πρώτα τους υπάρχοντες πόρους:
        //        clear();  // Ή μπορείτε να αναθέσετε νέα τιμή σε head, ptr, size1

        //        // Μεταφέρουμε τους πόρους από το `a`:
        //        head = a.head;
        //        ptr = a.ptr;
        //        size1 = a.size1;

        //        // "Αδειάζουμε" το `a` για να μην υπάρχει διπλό `delete`:
        //        a.head = nullptr;
        //        a.ptr = nullptr;
        //        a.size1 = 0;
        //    }   
        //    else {
        //        //std::cout << "hello\n";
        //        clear();
        //        a.head = nullptr;
        //        a.ptr = nullptr;
        //        a.size1 = 0;
        //    }
        //}




        //destructor
        ~single_linked_list() noexcept {

            list_node* ptr1 = head;
            list_node* ptr2 = head;
            for (size_t i = 0; i < size1; i++) {
                ptr2 = ptr2->next;
                delete ptr1;
                ptr1 = ptr2;


            }
            size1 = 0;
            head = nullptr;
            ptr = nullptr;
            return;

        }


    };


}