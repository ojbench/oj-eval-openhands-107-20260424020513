
#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{

    struct NODE {
        int data;
        NODE *next;
    };

    NODE *head = nullptr;
    int len = 0;

    void init() {
        head = nullptr;
        len = 0;
    }
    
    NODE* move(int i) {
        if (len == 0) return nullptr;
        if (i < 0 || i >= len) return nullptr;
        
        NODE *current = head;
        for (int j = 0; j < i; j++) {
            current = current->next;
        }
        return current;
    }
    
    void insert(int i, int x) {
        NODE *new_node = new NODE;
        new_node->data = x;
        
        if (len == 0) {
            // First node, points to itself
            head = new_node;
            new_node->next = new_node;
        } else {
            if (i <= 0) {
                // Insert at head
                NODE *tail = head;
                while (tail->next != head) {
                    tail = tail->next;
                }
                new_node->next = head;
                tail->next = new_node;
                head = new_node;
            } else if (i >= len) {
                // Insert at tail
                NODE *tail = head;
                while (tail->next != head) {
                    tail = tail->next;
                }
                tail->next = new_node;
                new_node->next = head;
            } else {
                // Insert at position i
                NODE *prev = move(i - 1);
                new_node->next = prev->next;
                prev->next = new_node;
            }
        }
        len++;
    }
    
    void remove(int i) {
        if (len == 0) return;
        if (i < 0 || i >= len) return;
        
        if (len == 1) {
            delete head;
            head = nullptr;
        } else {
            if (i == 0) {
                // Remove head
                NODE *tail = head;
                while (tail->next != head) {
                    tail = tail->next;
                }
                NODE *to_delete = head;
                head = head->next;
                tail->next = head;
                delete to_delete;
            } else {
                // Remove at position i
                NODE *prev = move(i - 1);
                NODE *to_delete = prev->next;
                prev->next = to_delete->next;
                delete to_delete;
            }
        }
        len--;
    }
    
    void remove_insert(int i) {
        if (len == 0) return;
        if (i < 0 || i >= len) return;
        
        if (len == 1) return; // Already at tail
        
        NODE *to_move;
        if (i == 0) {
            // Move head to tail
            to_move = head;
            NODE *tail = head;
            while (tail->next != head) {
                tail = tail->next;
            }
            head = head->next;
            tail->next = to_move;
            to_move->next = head;
        } else {
            // Move node at position i to tail
            NODE *prev = move(i - 1);
            to_move = prev->next;
            prev->next = to_move->next;
            
            // Find tail and insert
            NODE *tail = head;
            while (tail->next != head) {
                tail = tail->next;
            }
            tail->next = to_move;
            to_move->next = head;
        }
    }
    
    void get_length() {
        cout << len << endl;
    }
    
    void query(int i) {
        if (i < 0 || i >= len) {
            cout << -1 << endl;
            return;
        }
        NODE *current = move(i);
        if (current) {
            cout << current->data << endl;
        } else {
            cout << -1 << endl;
        }
    }
    
    void get_max() {
        if (len == 0) {
            cout << -1 << endl;
            return;
        }
        
        NODE *current = head;
        int max_val = current->data;
        current = current->next;
        
        for (int i = 1; i < len; i++) {
            if (current->data > max_val) {
                max_val = current->data;
            }
            current = current->next;
        }
        
        cout << max_val << endl;
    }
    
    void clear() {
        if (len == 0) return;
        
        NODE *current = head;
        NODE *next_node;
        
        for (int i = 0; i < len; i++) {
            next_node = current->next;
            delete current;
            current = next_node;
        }
        
        head = nullptr;
        len = 0;
    }

}
int n;
int main()
{
    cin >> n;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_)
    {
        cin >> op;
        switch(op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p,x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}
