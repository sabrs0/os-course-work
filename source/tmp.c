#include <stdio.h>
#include <linux/signal.h>
int main(){
    printf("%ld %ld\n", SIGUSR1, SIGUSR2);
    return 0;
}
