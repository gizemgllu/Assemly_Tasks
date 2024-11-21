#ifdef __cplusplus
#include <cstdio>
#include <cassert>
#else
#include <stdio.h>
#include <assert.h>
#endif

// my variant is A = 2 and B = 0

// Odd Counts
void solution_for_grade_7(const int arr[], size_t arr_rows, size_t arr_cols, int result[])
{
    if (!arr || !result || arr_rows == 0 || arr_cols == 0) {
        fprintf(stderr, "input is invalid!.\n");
        return;
    }

    __asm {
        mov esi, arr            
        mov edi, result         
        mov ecx, arr_rows       

    row_loop:
        test ecx, ecx          
        jz end_rows          

        push ecx               
        xor eax, eax            
        mov edx, arr_cols       

    col_loop:
        test edx, edx           
        jz store_result        

        mov ebx, [esi]         
        test ebx, 1           
        jz next   

        inc eax        

    next:
        add esi, 4         
        dec edx              
        jmp col_loop          

    store_result:
        mov [edi], eax         
        add edi, 4           
        pop ecx              
        mov edx, arr_cols    
        shl edx, 2             
        sub esi, edx            
        dec ecx                 
        jmp row_loop           

    end_rows:
    }
}


// Minimal Positive Value
void solution_for_grade_9(const int arr[], size_t arr_rows, size_t arr_cols, int result[])
{
    if (!arr || !result || arr_rows == 0 || arr_cols == 0) {
        fprintf(stderr, "input is invalid!.\n");
        return;
    }

    __asm {
        mov esi, arr            
        mov edi, result         
        mov ecx, arr_rows       

    row_loop:
        test ecx, ecx           
        jz end_rows            

        push ecx               
        mov edx, arr_cols       
        mov ebx, -1            
        xor eax, eax           
    col_loop:
        test edx, edx          
        jz store_result        

        mov eax, [esi]         
        cmp eax, 1              
        jl next    

        cmp ebx, -1             
        je set_min        
        cmp eax, ebx            
        jge next     

    set_min:
        mov ebx, eax            

    next:
        add esi, 4            
        dec edx               
        jmp col_loop          

    store_result:
        mov [edi], ebx         
        add edi, 4             
        mov edx, arr_cols       
        shl edx, 2             
        sub esi, edx            
        add esi, edx            
        pop ecx                
        dec ecx                
        jmp row_loop           
    end_rows:
    }
}

int main()
{
    const size_t ROWS = 2;
    const size_t COLS = 4;

    const int input[ROWS][COLS] = {
        { 1, -2, 3, 4 },
        { 5, 6, -7, 8 }
    };

    int result_grade_7[ROWS]{};
    int result_grade_9[ROWS]{};

    solution_for_grade_7((const int*)input, ROWS, COLS, result_grade_7);
    solution_for_grade_9((const int*)input, ROWS, COLS, result_grade_9);

    const int expected_grade_7[ROWS] = { 2, 2 };
    const int expected_grade_9[ROWS] = { 1, 5 };

    // Grade 7 
    printf("Grade 7 Results are : \n");
    for (size_t i = 0; i < ROWS; i++) {
        printf("%d ", result_grade_7[i]);
        // assert to check validity
        assert(result_grade_7[i] == expected_grade_7[i]); 
    }
     puts("");

    // Grade 9 
    printf("Grade 9 Results are :\n");
    for (size_t i = 0; i < ROWS; i++) {
        printf("%d ", result_grade_9[i]);
        assert(result_grade_9[i] == expected_grade_9[i]); 
    }
   ;

    return 0;
}
