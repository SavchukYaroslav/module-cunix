#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "../include/stream.h"


 void stream_print_test(stream_t* stream){
     printf("\n---STREAM---\n");
     printf("LIMIT: %d\n", stream->limit);
     printf("SIZE: %d\n", stream->size);
     stream_print(stream);
 }
/*
int main(){
    printf("TEST\n");
    stream_t* stream = stream_init();
    
    stream_append(stream, "aaa");
    stream_print_test(stream);

    stream_append(stream, "12345678901234567");
    stream_print_test(stream);

    stream_append(stream, "iwe12345678901234567");
    stream_print_test(stream);

    stream_append(stream, "ids1234567890\n1234567");
    stream_print_test(stream);

    stream_append(stream, "ids1234567890\n1234567");
    stream_print_test(stream);

    stream_destroy(stream);

}
*/
