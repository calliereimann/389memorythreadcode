#include "barriers.hh"
/*
   Central::Central(int threadc){
        sense_ = false;
        threadc_ = threadc;
        counter_ = 1;
   }*/

id_type joincentral(id_type id){
        bool local_sense = !sense_;
        if (counter_++ == threadc_) {
                counter_ = 1; //taken essentially from the slides, reworked a bit to fit with the setup i had
                sense_ = local_sense;
        } else {
                while (sense_ != local_sense) {
                        /* spin */ }
        }
        return id;
}
