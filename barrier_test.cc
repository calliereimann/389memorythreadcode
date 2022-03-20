#include <random>
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <cassert>
#include <vector>

std::atomic<int> counter = 1;
const int THREADC = 4;
const int ROUNDS = log2(THREADC);


using id_type = std::thread::id;

id_type joincentral(id_type id, int threadc, std::atomic<bool> &sense){
        bool local_sense = !sense;
        if (counter++ == threadc) {
                counter = 1; //taken essentially from the slides, reworked a bit to fit with the setup i had
                sense = local_sense;
        } else {
                while (sense != local_sense) {
                        /* spin */ }
        }
        return id;
}

void threadCentral(int threadc, std::atomic<bool> &sense){
        std::chrono::milliseconds delay (rand()%30);
        std::this_thread::sleep_for(delay);
        joincentral(std::this_thread::get_id(), threadc, sense);
        delay = std::chrono::milliseconds{(rand()%50)};
        std::cout<<"thread "<<std::this_thread::get_id()<<" through first barrier\n";
        delay = std::chrono::milliseconds{(rand()%50)};
        std::this_thread::sleep_for(delay);
        joincentral(std::this_thread::get_id(), threadc, sense);
        delay = std::chrono::milliseconds{(rand()%50)};
        std::cout<<"thread "<<std::this_thread::get_id()<<" through second barrier\n";
        delay = std::chrono::milliseconds{(rand()%50)};
        std::this_thread::sleep_for(delay);
        joincentral(std::this_thread::get_id(), threadc, sense);
        std::cout<<"thread "<<std::this_thread::get_id()<<" through third barrier\n";
}

void centraltest(){
        std::atomic<bool> sense = false;
        std::vector<std::thread> threads;
        for (int i = 0; i < THREADC; i++) {
                threads.push_back(std::thread(threadCentral, THREADC, std::ref(sense)));
        }
        /*
           std::thread one (threadAction, 5, std::ref(sense));
           std::thread two (threadAction, 5, std::ref(sense));
           std::thread three (threadAction, 5, std::ref(sense));
           std::thread four (threadAction, 5, std::ref(sense));
           std::thread five (threadAction, 5, std::ref(sense));
         */
        for (int i = 0; i < THREADC; i++) {
                threads[i].join();
        }
        /*
           one.join();
           two.join();
           three.join();
           four.join();
           five.join();
         */
}

id_type joindissemination(id_type id, int threadc, int position, std::atomic<bool> &sense, std::atomic<int> &parity, std::atomic<bool> flags[][2][ROUNDS]){
        for (int i = 0; i < ROUNDS; i++) {
                auto partner = (position + (2^i)) % threadc;
                flags[partner][parity][i] = !sense;
                while (flags[position][parity][i] == sense) { /* spin */ }
        } if (parity == 1) { sense = !sense;} parity = 1 - parity;
        return id;
}

void threadDissemination(int threadc, int position, std::atomic<bool> &sense, std::atomic<int> &parity, std::atomic<bool> flags[][2][ROUNDS]){
        std::chrono::milliseconds delay (rand()%30);
        std::this_thread::sleep_for(delay);
        joindissemination(std::this_thread::get_id(), threadc, position, sense, parity, flags);
        std::cout<<"thread "<<std::this_thread::get_id()<<" through first barrier\n";
        delay = std::chrono::milliseconds{(rand()%70)};
        std::this_thread::sleep_for(delay);
        joindissemination(std::this_thread::get_id(), threadc, position, sense, parity, flags);
        std::cout<<"thread "<<std::this_thread::get_id()<<" through second barrier\n";
        delay = std::chrono::milliseconds{(rand()%70)};
        std::this_thread::sleep_for(delay);
        joindissemination(std::this_thread::get_id(), threadc, position, sense, parity, flags);
        std::cout<<"thread "<<std::this_thread::get_id()<<" through third barrier\n";
}

void disseminationtest(){
        std::atomic<bool> sense = false;
        std::atomic<int> parity = 0;
        std::atomic<bool> flags[THREADC][2][ROUNDS]; //allocated in local storage per thread
        for (int i = 0; i < THREADC; i++) {
                for (int j = 0; j < 2; j++) {
                        for (int k = 0; k < ROUNDS; k++) {
                                flags[i][j][k] = false;
                        }
                }
        }
        std::vector<std::thread> threads;
        for (int i = 0; i < THREADC; i++) {
                threads.push_back(std::thread(threadDissemination, THREADC, i, std::ref(sense), std::ref(parity), std::ref(flags)));
        }
        /*
           std::thread one (threadAction, 5, std::ref(sense));
           std::thread two (threadAction, 5, std::ref(sense));
           std::thread three (threadAction, 5, std::ref(sense));
           std::thread four (threadAction, 5, std::ref(sense));
           std::thread five (threadAction, 5, std::ref(sense));
         */
        for (int i = 0; i < THREADC; i++) {
                threads[i].join();
        }
        /*
           one.join();
           two.join();
           three.join();
           four.join();
           five.join();
         */
}

int main() {
        srand(time(NULL));
        //std::cout<<"Central Barrier: \n";
        //centraltest();
        std::cout<<"Dissemination Barrier: \n";
        disseminationtest();
}
