#ifndef TEST_HPP
#define TEST_HPP

/* Part 2
a) It tests final result. If there is any problem in this program, it will show 'false'. So it is enough to prove that it always shows that my program always produces exact solutions.
b) we can check the vote result in each constituency if there is more time.
c) If two parties get same votes in one constituency, which is rare in reality, my program cannot compute correctly.
*/


bool run_test(unsigned int arr1[], unsigned int arr2[]){

    bool all_passed = true;

    // initialize input array
    unsigned int correct_pulr[3] = {4, 2, 0};
    unsigned int correct_prop[3] = {2, 3, 1};

    // test each election system
    for (unsigned int i=0; i<3; ++i){
        if (arr1[i] != correct_pulr[i]) {
            all_passed = false;
            std::cout<<"test is failed for plurality system\n";    
        }
        if (arr2[i] != correct_prop[i]) {
            all_passed = false;
            std::cout<<"test is failed for proportional system\n";
        }
    }

    if (all_passed==true) {std::cout<<"all test is passed\n";}

    return all_passed;
}

#endif