#include<stdio.h>
#include<time.h>

void function_to_time() {
    printf("Function starts here\n");
    printf("Press enter to stop function\n");
    
    for(;;) {
        if(getchar()) {
            break;
        }
    }

    printf("Function ends here\n");
}

int main(int argc, char *argv[]) {
    clock_t t0, t1;
    double time_elapsed;

    //
    // function processing time
    t0 = clock();
    function_to_time();
    t1 = clock();

    time_elapsed = (double) (t1 - t0) / CLOCKS_PER_SEC;

    printf("\nTime taken by function is %f\n", time_elapsed);

    //
    // real time, calendar time (not RT)

    return 0;
}
