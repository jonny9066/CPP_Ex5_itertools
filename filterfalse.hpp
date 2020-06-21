
namespace itertools{

    template <class F, class C> class filterfalse{
        private:
            C container;
            const F& filter;
            using C_itr = decltype(container.begin());
            using C_type = typename C::value_type;
        public:

            filterfalse(const F& f, C c):filter(f),container(c){}
            class iterator{
                private:
                    const C_itr last;
                    C_itr current;
                    const F& filter;
                    
                public:
                    iterator(C_itr c, const C_itr l,const F& f):current(c),last(l), filter(f){
                        // set current to the first value that is not filtered
                        while(current != last && filter(*current)){
                            ++current;
                        }
                    }
                        C_type operator*(){
                            return *current;
                        }
                        
                        iterator& operator++() {
                            // advance until either last or is not filtered
                            ++current;
                            while(current != last && filter(*current)){
                                ++current;
                            }
                            return *this;
                        }
                        iterator operator++(int) {
                            iterator tmp = *this;
                            ++(*this);
                            return tmp;
                        }
                        bool operator==(iterator& other){
                            if(this->current!= other.current)
                                return false;
                            else
                                return true;
                        }
                        bool operator!=(iterator& other){
                            if(this->current== other.current)
                                return false;
                            else
                                return true;
                        }
                        
                        
                };
            iterator begin(){return iterator{container.begin(),container.end(),filter};}
            iterator end(){return iterator{container.end(),container.end(),filter};}
    };


}