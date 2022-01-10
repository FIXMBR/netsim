//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#ifndef CONFIG_HPP_
#define CONFIG_HPP_

// ID ćwiczenia na zajęciach z C++
#define EXERCISE_ID 3

#define EXERCISE_ID_PACKAGES    1
#define EXERCISE_ID_NODES       2
#define EXERCISE_ID_FACTORY     3
#define REPORTING               4
#define SIMULATION              5

#if defined(EXERCISE_ID)
    #if EXERCISE_ID >= EXERCISE_ID_NODES
        #define WITH_PROBABILITY_GENERATOR
    #endif

    #if EXERCISE_ID >= EXERCISE_ID_FACTORY
        #define WITH_RECEIVER_TYPE
    #endif
#endif

#endif /* CONFIG_HPP_ */
//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)