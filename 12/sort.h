#ifndef SORT_H
#define SORT_H

#include <vector>
namespace stlSort {

    class sort {
    public:
        virtual sort() {};
        virtual ~sort() {};
        virtual void quickSort(vector<int>& arr, int& begin, int& end) = 0;
    };

    class vectorSort : public sort {
    public:
        vectorSort() {};
        ~vectorSort() {};
        void quickSort(vector<int>& arr, int& begin, int& end);
        
    };

}

#endif // DEBUG