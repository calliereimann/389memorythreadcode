#include <thread>
#include <atomic>
#include <iostream>
#include <cassert>
#pragma once

using id_type = std::thread::id;


struct Central {
        int threadc_;
        std::atomic<int> counter_;
        bool sense_;
};

Central createcentral(int n);

id_type joincentral(id_type id, Central barrier);
/*
   class Dissemination {
   Dissemination(int threadc);
   ~Dissemination() = default;

   void joindissemination(id_type id);

   int threadc_;
   int counter_;
   bool sense_;
   };
 */
