#include <iostream>
#include <stdexcept>

//#define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout <<"DEBUG: "<< str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif


namespace itertools{
    // default function
    struct add{
        template<typename T> 
            T operator()(T x, T y)const {return (x+y);}
    }add_inst;

    
    template<class C, class F = add> class accumulate{


        C container;
        const F& oper;

        using C_itr = decltype(container.begin());
        using C_type = typename C::value_type;

        public:
            accumulate(C c,const F& o = add_inst)
                :container(c), oper(o){}
                #ifdef DEBUG
                void print(){
                    cout<<"accumulate fields:"<<endl;
                    cout<<"container first item: "<<*container.begin()<<endl;
                    cout<<"first+first: "<<oper(*container.begin(), *container.begin())<<endl;
                }
                #endif
            class iterator{
                private:
                    const C_itr first;
                    C_itr current;
                    const F& oper;
                public:
                    //constructs iterator with first, current and operator
                    iterator(const C_itr& f, C_itr c,const F& o)
                                :first(f), current(c),oper(o){
                                    DEBUG_MSG("iterator first: "<<*first);
                                    DEBUG_MSG("iterator current: "<<*current);
                                }
                    #ifdef DEBUG
                    void print(){
                        cout<<"iterator fileds:"<<endl;
                        cout<<"first: "<<*first<<endl;
                        cout<<"current: "<<*current<<endl;
                        cout<<"first+current: "<<oper(*first, *current)<<endl;
                    }
                    #endif
                    C_type operator*(){
                        C_itr j = first;
                        C_type tmp;
                        // need to initialize tmp
                        // only if first != current
                        if(j!=current){
                            tmp = *j;
                            ++j;
                        }
                        else{
                            return *current;
                        }
                        while(j!= current){
                            tmp = oper(tmp, *j);
                            ++j;
                        }
                        return oper(tmp, *current);
                    }
                    iterator& operator++() {
                        ++current;
                        return *this;
                    }
                    iterator& operator++(int) {
                        iterator tmp = *this;
                        ++current;
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
            iterator begin(){return iterator{container.begin(),container.begin(),oper};}
            iterator end(){return iterator{container.begin(),container.end(),oper};}

    };

    
}