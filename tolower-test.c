/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 18/08/2021
*/

/*
 . This program is a recreation of a similar program [1] 
 . which itself is the result of the back and forth between 
 . Oleg Razgulyaev (oraz) [2] and Zed (jfs) [3] in one of 
 . Oleg's answers [4] to a question from stackoverflow about 
 . tolower() alternatives. 
 . 
 . Paraphrasing the original author [3], the purpose of this 
 . program is to "compare the relative performance of tolower() 
 . alternative functions".
 . 
 . The reason why I re-made the program was to see the inner 
 . workings of it and understand it better. Also, to add an 
 . in-program time counter instead of using Valgrind as the 
 . original program did. Sorry for that.
 . 
 . -- References --
 . 
 .     [1] https://gist.github.com/zed/370497
 .     [2] https://stackoverflow.com/users/2153550/oleg-razgulyaev
 .     [3] https://stackoverflow.com/users/4279/jfs
 .         https://gist.github.com/zed
 .     [4] https://stackoverflow.com/a/2661917/2167133
 . 
 . -- Results --
*/

/* -- Includes -- */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* -- Types -- */

typedef char * (*fun_t) (char *);

/* -- Variables and Functions -- */

/*
 . test_tolower_func()
 . 
 .     fun_t tolower_func - A pointer to a tolower function 
 .     int   tries        - N of times to test the function
 . 
 . tolower_func() must accept a char * (a string) as its 
 . only parameter.
*/

const char test_str[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71,
 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107,
 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 
 123, 124, 125, 126, 127, '\0'
};

const int test_str_len = sizeof(test_str) / sizeof(*test_str);

void test_tolower_func (fun_t tolower_func, int tries) {
  
    // char *str = malloc(test_str_len + 1);

    char *str = malloc(test_str_len);

    if (!str) {

        perror("malloc");
    
        exit(1);
    
    }

    str = strncpy(str, test_str, test_str_len);

    // str[test_str_len] = '\0';

    for (int i = 0; i < tries; ++i) tolower_func(str);

    free(str);
    
    return;

}

/*
 . tolower_oraz()
 . 
 . Parameters
 . 
 .     car * str - The string to convert
 . 
 . Based on the answer mentioned in the begining of the 
 . file. Uses tolower_oraz_ch() as its character version 
 . which is a macro instead of a function to help with
 . performance.
*/

#define tolower_oraz_ch(ch) \
    (ch >= 'A' && ch <= 'Z' ? ch | 0x60 : ch)

char * tolower_oraz (char * str) { 
    
    char * p;

    for (p = str; *p; ++p) {
        
        *p = tolower_oraz_ch(*p);
    
    }
    
    return p;

}

/*
 . tolower_oraz_2()
 . 
 . Parameters
 . 
 .     car * str - The string to convert
 . 
 . Based on an upgrade to the previous solution proposed in 
 . the comments of the same answer. Uses tolower_oraz_2_ch() 
 . as its character version which is a macro instead of a 
 . function to help with performance.
*/

#define tolower_oraz_2_ch(ch) \
    (ch < 'A' || ch > 'Z' ? ch : ch | 0x60)

char * tolower_oraz_2 (char * str) { 
    
    char * p;

    for (p = str; *p; ++p) {

        // if (*p < 'A') continue;
        // if (*p > 'Z') continue;
        
        // *p = *p | 0x60;

        *p = tolower_oraz_2_ch(*p);
        
    }
    
    return p;

}

/*
 . tolower_openbsd_ch()
 . 
 . Parameters
 . 
 .     car * str - The string to convert
 . 
 . Emulates the logic of openbsd's tolower(). Uses a look-up 
 . table of characters instead of calculating lower ver
*/

const short _tolower_openbsd_arr[] = {
    EOF,
    0x00,   0x01,   0x02,   0x03,   0x04,   0x05,   0x06,   0x07,
    0x08,   0x09,   0x0a,   0x0b,   0x0c,   0x0d,   0x0e,   0x0f,
    0x10,   0x11,   0x12,   0x13,   0x14,   0x15,   0x16,   0x17,
    0x18,   0x19,   0x1a,   0x1b,   0x1c,   0x1d,   0x1e,   0x1f,
    0x20,   0x21,   0x22,   0x23,   0x24,   0x25,   0x26,   0x27,
    0x28,   0x29,   0x2a,   0x2b,   0x2c,   0x2d,   0x2e,   0x2f,
    0x30,   0x31,   0x32,   0x33,   0x34,   0x35,   0x36,   0x37,
    0x38,   0x39,   0x3a,   0x3b,   0x3c,   0x3d,   0x3e,   0x3f,
    0x40,   'a',    'b',    'c',    'd',    'e',    'f',    'g',
    'h',    'i',    'j',    'k',    'l',    'm',    'n',    'o',
    'p',    'q',    'r',    's',    't',    'u',    'v',    'w',
    'x',    'y',    'z',    0x5b,   0x5c,   0x5d,   0x5e,   0x5f,
    0x60,   0x61,   0x62,   0x63,   0x64,   0x65,   0x66,   0x67,
    0x68,   0x69,   0x6a,   0x6b,   0x6c,   0x6d,   0x6e,   0x6f,
    0x70,   0x71,   0x72,   0x73,   0x74,   0x75,   0x76,   0x77,
    0x78,   0x79,   0x7a,   0x7b,   0x7c,   0x7d,   0x7e,   0x7f,
    0x80,   0x81,   0x82,   0x83,   0x84,   0x85,   0x86,   0x87,
    0x88,   0x89,   0x8a,   0x8b,   0x8c,   0x8d,   0x8e,   0x8f,
    0x90,   0x91,   0x92,   0x93,   0x94,   0x95,   0x96,   0x97,
    0x98,   0x99,   0x9a,   0x9b,   0x9c,   0x9d,   0x9e,   0x9f,
    0xa0,   0xa1,   0xa2,   0xa3,   0xa4,   0xa5,   0xa6,   0xa7,
    0xa8,   0xa9,   0xaa,   0xab,   0xac,   0xad,   0xae,   0xaf,
    0xb0,   0xb1,   0xb2,   0xb3,   0xb4,   0xb5,   0xb6,   0xb7,
    0xb8,   0xb9,   0xba,   0xbb,   0xbc,   0xbd,   0xbe,   0xbf,
    0xc0,   0xc1,   0xc2,   0xc3,   0xc4,   0xc5,   0xc6,   0xc7,
    0xc8,   0xc9,   0xca,   0xcb,   0xcc,   0xcd,   0xce,   0xcf,
    0xd0,   0xd1,   0xd2,   0xd3,   0xd4,   0xd5,   0xd6,   0xd7,
    0xd8,   0xd9,   0xda,   0xdb,   0xdc,   0xdd,   0xde,   0xdf,
    0xe0,   0xe1,   0xe2,   0xe3,   0xe4,   0xe5,   0xe6,   0xe7,
    0xe8,   0xe9,   0xea,   0xeb,   0xec,   0xed,   0xee,   0xef,
    0xf0,   0xf1,   0xf2,   0xf3,   0xf4,   0xf5,   0xf6,   0xf7,
    0xf8,   0xf9,   0xfa,   0xfb,   0xfc,   0xfd,   0xfe,   0xff
};

const short * _tolower_openbsd_tbl = _tolower_openbsd_arr;

int tolower_openbsd_ch (int ch) {
  
    return ch > 255 ? ch : (_tolower_openbsd_tbl + 1)[ch];

}

char * tolower_openbsd (char * str) {

    char *p = str;
    
    for ( ; *p; ++p) {

        // *p = tolower_openbsd_ch(*p);

        // Check for character to help performance

        if (*p > 255) continue;

        *p = (_tolower_openbsd_tbl + 1)[*p];

    }

    return p;

}

/*
 . tolower_ctype()
 . 
 . Parameters
 . 
 .     car * str - The string to convert
 . 
 . Uses ctype's tolower() for its core functionality.
*/

char * tolower_ctype (char * str) {
    
    char * p;
    
    for (p = str; *p; ++p) {

        *p = tolower(*p);

    } 
    
    return p;

}

/* -- Main -- */

int main (int argc, char const ** argv) {

    int    tries;
    double start, end, total;

    tries = argc <= 1 ? 1000000 : atoi(argv[1]);

    fun_t funcs [] = { 
        tolower_oraz, 
        tolower_oraz_2, 
        tolower_openbsd, 
        tolower_ctype 
    };

    int funcs_len = sizeof(funcs) / sizeof(*funcs);;

    for (int func = 0; func < funcs_len; ++func) {
        
        printf("Func #%d\n\n", func + 1);

        start = clock();

        test_tolower_func(funcs[func], tries);

        end = clock();

        total = (double) (end - start) / CLOCKS_PER_SEC;
        
        printf("Total time: %f seconds\n\n", total);
        
    }

    return 0;
}