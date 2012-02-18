#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <string>

using namespace std;

void *waitForPress(void *argument) {
    bool *presser;
    presser = (bool*) argument;
    int timer = 0;
    while (*presser == false) {
        sleep(1);
        cout << ++timer << endl;
    }
    return NULL;
}

void *signalWhenPress(void *argument) {
    bool *presser;
    presser = (bool*) argument;
    string anything;
    while (true) {
        if (getchar()) {
            *presser = true;
            break;
        }
    }
    return NULL;
}

int main() {
    pthread_t waitForPressThread, signalWhenPressThread;
    bool presser = false;

    pthread_create(&waitForPressThread, NULL, waitForPress, (void *) &presser);
    pthread_create(&signalWhenPressThread, NULL, signalWhenPress, (void *) &presser);

    pthread_join(waitForPressThread, NULL);
    pthread_join(signalWhenPressThread, NULL);
    cout << "Hello World!" << endl;
    return 0;
}

