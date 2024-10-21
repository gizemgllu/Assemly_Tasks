#ifdef __cplusplus
#include <cstdio>
#include <cassert>
#else
#include <stdio.h>
#include <assert.h>
#endif

// Grade 7 => A =  Assuming that indexing starts from zero, calculate a total of values at even index positions (1, 3, 5, ...)
int solution_for_grade_7(const int *arr, size_t arr_size) {
    if (arr == nullptr || arr_size == 0) {
        return 0;  // null or empty array
    }

    int result = 0;

    __asm {
        xor EAX, EAX            ; 
        mov ESI, arr            ; 
        xor ECX, ECX            ; 

    Loop7:
        cmp ECX, arr_size       ; 
        jge Exit7               ; 

        test ECX, 1             ; 
        jnz Skip7               ; 

        mov EDX, [ESI + ECX * 4] ; 
        add EAX, EDX            ; 

    Skip7:
        inc ECX                 ; 
        jmp Loop7               ; 

    Exit7:
        mov result, EAX         ; 
    }

    return result;
}

// Grade 9 => B = Find the index of maximum odd value.
int solution_for_grade_9(const int *arr, size_t arr_size) {
    if (arr == nullptr || arr_size == 0) {
        return -1;  // null or empty array
    }

    int max_value = 0x80000000; 
    int max_index = -1;

    __asm {
        mov ESI, arr            ; 
        xor ECX, ECX            ; 
        xor EAX, EAX            ; 
        mov EDX, -1             ; 

    Loop9:
        cmp ECX, arr_size       ; 
        jge Check         ; 

        mov EBX, [ESI + ECX * 4] ; 
        test EBX, 1             ; 
        jz Skip9                ; 

        cmp EBX, EAX            ; 
        cmovg EAX, EBX          ; 
        cmovg EDX, ECX          ; 

    Skip9:
        inc ECX                 ; 
        jmp Loop9               ; 

    Check:
        ; After the loop, check if max_index was updated
        cmp EDX, -1             ; 
        jnz Exit9               ; 

        ; If max_index is still -1, it means no odd values were found
        mov EDX, -1             ; // returns -1 if no odd values found
        
    Exit9:
        mov max_index, EDX      ; 
    }

    return max_index;
}

#include <cstdio>
#include <cassert>

int solution_for_grade_7(int const * arr, size_t arr_size);
int solution_for_grade_9(int const * arr, size_t arr_size);

int main() {
    int test_result;

    
    int test_arr1[] = { 900000, 998, 5022, -300, 4444, 5678, 54366, 70, -80000, 0 };
   
    test_result = solution_for_grade_7(test_arr1, sizeof(test_arr1) / sizeof(test_arr1[0]));
    assert(test_result == 883832);
    printf("Grade 7 result1 is %d\n", test_result);

    // test for side cases
    int test_arr2[] = { -91, -11, 20, -33, 40, -55, 60, -71, 800, 0 };
    test_result = solution_for_grade_7(test_arr2, sizeof(test_arr2) / sizeof(test_arr2[0]));
    assert(test_result == 829);
    printf("Grade 7 result2 is %d\n", test_result);

    test_result = solution_for_grade_9(test_arr2, sizeof(test_arr1) / sizeof(test_arr1[0]));
    assert(test_result == -1); 
    printf("Grade 9 result1 is %d\n", test_result);
    printf("There arent any odd value in the array! ");


    return 0;
}
