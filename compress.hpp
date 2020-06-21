#include <iostream>
#include <stdexcept>
#include <bitset>

using namespace std;


namespace itertools{

    template <class C, class D> class compress{
        private:
            C container;
            D tester;
            using C_itr = decltype(container.begin());
            using C_type = typename C::value_type;
            using D_itr = decltype(tester.begin());
            using D_type = bool;
        public:
            compress(C c, D d):container(c),tester(d){
                // check that containers have same number of items
                int i =0, j=0;
                for(auto unimportant: c) ++j;
                for(auto unimportant: d) ++i;
                if(i!=j) throw invalid_argument("");
            }
            class iterator{
                private:
                    C_itr cur_cont;
                    D_itr cur_tstr;
                    C_itr lst_cont;
                    
                public:
                    iterator(C_itr c, C_itr lc, D_itr t):cur_cont(c), lst_cont(lc),cur_tstr(t){
                        // get both iterators to the first 'true' value
                        while((cur_cont != lst_cont) && !*cur_tstr){
                            ++cur_cont;
                            ++cur_tstr;
                        }
                    }
                        C_type operator*(){
                            return *cur_cont;
                        }
                        
                        iterator& operator++() {
                            ++cur_cont;
                            ++cur_tstr;
                            // advance while not last or false
                            while((cur_cont != lst_cont) && !*cur_tstr){
                                ++cur_cont;
                                ++cur_tstr;
                            }
                            return *this;
                        }
                        iterator operator++(int) {
                            iterator tmp = *this;
                            ++(*this);
                            return tmp;
                        }
                        bool operator==(iterator& other){
                            if(this->cur_cont== other.cur_cont
                                && this->lst_cont== other.lst_cont
                                    && this->cur_tstr== other.cur_tstr)
                                return true;
                            else
                                return false;
                        }
                        bool operator!=(iterator& other){
                            return !(*this == other);
                        }
                        
                        
                };
            iterator begin(){return iterator{container.begin(),container.end(),tester.begin()};}
            iterator end(){return iterator{container.end(),container.end(),tester.end()};}
    };


}