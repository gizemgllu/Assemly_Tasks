#ifdef __cplusplus
#include <cstdio>
#include <cstring>
#include <cassert>
#else
#include <stdio.h>
#include <string.h>
#include <assert.h>
#endif

// Variant A(2) 
int solution_for_grade_6(const char* input)
{
    if (!input) {
        return 0;  // If input is NULL
    }

    int result = 0;

    __asm
    {
        xor eax, eax       
        xor ecx, ecx       
        mov esi, input     

    loop_start_A:
        lodsb              
        test al, al        
        jz loop_end_A      

        cmp al, '0'        
        jl loop_start_A    
        cmp al, '9'        
        jg loop_start_A    

        sub al, '0'        
        add ecx, eax       

        jmp loop_start_A   

    loop_end_A:
        mov result, ecx    
    }

    return result;
}


// Variant B(0)
void solution_for_grade_9(const char* input, char* output)
{
    
    if (!input || !output) {
        return;  // If either input or output is NULL
    }

    __asm
    {
        mov esi, input     
        mov edi, output    
        mov al, 0          

        mov ebx, 0         

    loop_start_B:
        lodsb              
        test al, al        
        jz loop_end_B      

        cmp al, ' '       
        jne copy_char      

        // Handle multiple spaces
        cmp ebx, 1         
        je loop_start_B    

     
        mov al, '_'        
        stosb             
        mov ebx, 1         
        jmp loop_start_B   

    copy_char:
        stosb              
        mov ebx, 0         
        jmp loop_start_B   

    loop_end_B:
        stosb              
    }
}


int main()
{
    
    int n_result = 0;
    
    // No numerals
    n_result = solution_for_grade_6(".,!?:;-");
    assert(0 == n_result); // Expect 0, no numerals
    
    // input with numerals
    n_result = solution_for_grade_6("4A 78 B");
    assert(19 == n_result); // Expect 4 + 7 + 8 = 19

    n_result = solution_for_grade_6("   3 5  ");
    assert(8 == n_result); // Expect 3 + 5 = 8

    // Empty string
    n_result = solution_for_grade_6("");
    assert(0 == n_result); // Expect 0 for empty string
    
    // Only numerals
    n_result = solution_for_grade_6("12345");
    assert(15 == n_result); 
    
    //  input with spaces
    char s_result[256] = ""; 
    
    // No spaces to replace
    solution_for_grade_9("Hello,World!", s_result);
    assert(!strcmp("Hello,World!", s_result)); 

    solution_for_grade_9("A.   BC,   D!", s_result);
    assert(!strcmp("A._BC,_D!", s_result));  
    // Empty string
    solution_for_grade_9("", s_result);
    assert(!strcmp("", s_result)); 
    
    // Only spaces
    solution_for_grade_9("     ", s_result);
    assert(!strcmp("_", s_result)); 

    printf("All tests are successful!!\n");
    return 0;
}
