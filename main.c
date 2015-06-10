#include <stdio.h>

unsigned char* huff_encode(unsigned char htree[], int N,  unsigned char data[], unsigned long length){
    unsigned long i = 0;
    for (i = 0; i < length; i++) {

    }
    return 0;
}

unsigned char read_one_bit(unsigned char buffer[], unsigned long bit_num){
    unsigned long byte_num = bit_num / 8;
    int bit_within_byte = bit_num % 8;

    return buffer[byte_num] & (1 << (7 - bit_within_byte));
};


char huff_decode2(unsigned char htree[], int N, unsigned char buffer[], unsigned long *bit_num){
    //N = # of symbols
    unsigned short left_mask = 0xFF00; //to extract upper byte(left child)
    unsigned short  right_mask = 0x00FF; //to extract lower byte(right child)
    int loc0, loc = ( N - 1 ) + N; //start from root; add offset N to
    // distinguish pointers from symbols

    do {
        loc0 = loc - N;
        if ( read_one_bit(buffer, (*bit_num)++) == 0 ){  //a 0, go left
            loc = ( htree[loc0] & left_mask ) >> 8;
        } else{
            loc =  htree[loc0] & right_mask;
        }
    } while ( loc >= N );       //traverse until reaches leaf
    return loc;                 //symbol value = loc
}



char huff_decode(unsigned char htree[], int N, unsigned char buffer[], unsigned long *bit_num){
    int loc0, loc = 3 * N - 3;             //start from root, N = # of symbols
    do {
        loc0 = loc;                //in is data pointer pointing to
        //  encoded data
        if ( read_one_bit(buffer, (*bit_num)++) == 0 ) //a 0, go left
            loc = htree[loc0];
        else
            loc =  htree[loc0 - 1];  //a 1, go right
    } while ( loc >= N );        //traverse until reach leaf
    return htree[loc];           //return symbol
}


int main(int argc, const char * argv[]) {
    static unsigned long bit_num = 0;
    unsigned char buffer[] = {239, 38, 133, 212};
    unsigned char htree[] = {'l', 'o', 'a', ' ', 'h', 'e', 5, 4, 7, 3, 2, 1, 9, 11, 13, 0};

    printf("Decoded sequence: ");
    do{
        printf("%c", huff_decode(htree, 6, buffer,  &bit_num));
    }while(bit_num < sizeof(buffer) * 8);

    return 0;
}
