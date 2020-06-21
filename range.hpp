#include <iostream>
#include <stdexcept>

using namespace std;

namespace itertools{
    /* represents the numbers between a and b, including a
    and not including b.*/
    class range{
        private:
            int first;
            int last;
        public:
            typedef int value_type;
            int size(){return last-first;}
            range(int a, int b):first(a),last(b){
                if(a>b){
                    throw invalid_argument("a cannot be smaller than b");
                }
            }

            class iterator{
                private:
                    int current;
                    int last;
                public:
                    iterator(int c, int l):current(c), last(l){}
                    int operator*()const{
                        if(current >= last){
                            out_of_range("Iterator of 'range' out of bounds");
                        }
                        return current;
                    }
                    iterator& operator++() {
                        current++;
                        return *this;
                    }
                    iterator operator++(int) {
                        iterator tmp = *this;
                        current++;
                        return tmp;
                    }
                    bool operator==(const iterator& other) const{
                        if(this->current!= other.current)
                            return false;
                        else
                            return true;
                    }
                    bool operator!=(const iterator& other)const{
                        if(this->current== other.current)
                            return false;
                        else
                            return true;
                    }
                    
                    
            };
            iterator begin(){return iterator{first, last};}
            iterator end(){return iterator{last, last};}

    };



}