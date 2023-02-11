//#include "../test/Threads_C_API_test.hpp" // zadatak 2, niti C API i sinhrona promena konteksta
//#include "../h/Threads_CPP_API_test.hpp" // zadatak 2., niti CPP API i sinhrona promena konteksta
//#include "../h/workers.hpp"
//#include "../h/ConsumerProducer_C_API_test.hpp" // zadatak 3., kompletan C API sa semaforima, sinhrona promena konteksta
#include "../h/ConsumerProducer_CPP_API_test.hpp" // zadatak 3., kompletan CPP API sa semaforima, sinhrona promena konteksta
#include "../h/syscall_c.h"
#include "../h/riscv.hpp"
//#include "../h/modifikacija.hpp"


void userMain(void*) {

    //pokreni_mod_test();







    //
    //Threads_C_API_test(); // zadatak 2., niti C API i sinhrona promena konteksta
    //Threads_CPP_API_test(); // zadatak 2., niti CPP API i sinhrona promena konteksta

    //producerConsumer_C_API(); // zadatak 3., kompletan C API sa semaforima, sinhrona promena konteksta

    producerConsumer_CPP_Sync_API(); // zadatak 3., kompletan CPP API sa semaforima, sinhrona promena konteksta
    //printString("Test gotov\n");

}
