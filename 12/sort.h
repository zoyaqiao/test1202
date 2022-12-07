#ifndef SORT_H
#define SORT_H

#include <vector>
namespace stlSort {

    class sort {
    public:
        sort() {};
        virtual ~sort() {};
        virtual void quickSort(std::vector<int>& arr) = 0;
    };

    class vectorSort : public sort {
    public:
        vectorSort() {};
        ~vectorSort() {};
        void quickSort(std::vector<int>& arr, int begin, int end);
        void quickSort(std::vector<int>& arr);

    };

}

#endif // DEBUG