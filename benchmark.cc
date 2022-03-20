#include <random>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <iostream>

std::vector<int>* listGen(size_t n){
        std::vector<int>* order = new std::vector<int>;
        srand(time(NULL));
        for (size_t i =0; i < n; i++) {
                order->push_back(rand());
        }
        return order;
}

std::vector<int> indexGen(size_t n){
        std::vector<int> order; //generates a list of 100 random indices within the size of n
        for (size_t i =0; i < 100; i++) {
                order.push_back(rand()%n);
        }
        return order;
}

double timecount(std::vector<int>* order, size_t n){
        timespec* start = new timespec;
        timespec* end = new timespec;
        std::vector<int> indices = indexGen(n);
        std::vector<int> holds;
        clock_gettime(CLOCK_MONOTONIC, start);
        for (int i = 0; i < 100; i++) { //this isn't the best way, but it's the only one i've found which doesn't just return 0 ns and 0 clock ticks
                holds.push_back((*order)[indices[i]]);
        }
        clock_gettime(CLOCK_MONOTONIC, end);

        int sum =0;
        for(int i = 0; i < 100; i++) {
                sum += holds[i];
        }
        srand(sum);
        //printf("One hundred accesses took %li clock cycles\n", end-start );
        auto output= (end->tv_nsec - start->tv_nsec)/100.0;
        delete start;
        delete end;
        return output;
}

void measure(size_t n, int count){
        std::vector<int>* order = listGen(n);
        for (int i = 0; i < count; i++) {
                std::cout<<timecount(order, n)<<"  "<<n*4 <<"\n";
        }
        delete order;
}

int main(){
        std::cout<<"ns   bytes\n";
        int sizelist[] = {250, 500, 1000, 250000, 500000, 1000000, 25000000, 250000000, 350000000};
        for (int i = 0; i < 9; i++) {
                measure(sizelist[i], 10);
        }
}
