#include <iostream>
#include <iomanip> 


int for_loop(){
    int sum = 0; 
    for (int i=1 ;i<10000; i++){
        if (i%16==7){
            sum+= i;
        };
    };
    return sum;
}

int while_loop() {
    int sum = 0;
    int i = 1;

    while (i < 10000) {
        if (i % 16 == 7) {
            sum += i;
        }
        i++;
    }

    return sum;
}

int do_while_loop() {
    int sum = 0;
    int i = 1;

    do {
        if (i % 16 == 7) {
            sum += i;
        }
        i++;
    } while (i < 10000);

    return sum;
}

int for_loop_with_continue() {
    int sum = 0;
    for (int i = 1; i < 10000; i++) {
        if (i % 16 != 7) {
            continue; 
        }
        sum += i;
    }
    return sum;
}

int main (){

std::cout << "For loop res: " << for_loop() << std::endl;
std::cout << "While loop res: " << while_loop() << std::endl;
std::cout << "Do-While loop res: " << do_while_loop() << std::endl;
std::cout << "For loop with continue res: " << for_loop_with_continue() << std::endl;

return 0;
}

int while_loop_with_continue() {
    int sum = 0;
    int i = 1;
    while (i < 10000) {
        if (i % 16 != 7) {
            i++;
            continue; 
        }
        sum += i;
        i++;
    }
    return sum;
}

int do_while_loop_with_continue() {
    int sum = 0;
    int i = 1;
    do {
        if (i % 16 != 7) {
            i++;
            continue;
        }
        sum += i;
        i++;
    } while (i < 10000);
    return sum;
}

