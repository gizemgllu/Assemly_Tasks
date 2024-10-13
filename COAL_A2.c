#ifdef __cplusplus
#include <cstdio>
#include <cassert>
#else
#include <stdio.h>
#include <assert.h>
#endif

// Variant 0 => E = –2fs + 3(t + f)
int solution_for_grade_5(int x, int y, int z)
{
    int result;
    __asm
    {
        mov eax, x                
        imul eax, y               
        imul eax, -2              

        mov ebx, z               
        add ebx, x              
        imul ebx, 3             

        add eax, ebx              

        mov result, eax           
    }
    return result;
}

// Variant 2 => D = X – (Y – 1)3/ Z
int solution_for_grade_7(int x, int y, int z)
{
    int result;
    __asm
    {
        mov eax, y                
        dec eax                   
        imul eax, eax             
        imul eax, y               

        mov ecx, z                
        test ecx, ecx            
        jz division_by_zero       

      
        cdq                      
        idiv ecx                 

        mov ebx, x               
        sub ebx, eax              

        mov result, ebx           
        jmp end_grade_7          

    division_by_zero:
        mov result, -1            

    end_grade_7:
    }
    return result;
}


// D is bigger than 0, so multiply 
int solution_for_grade_9(int x, int y, int z)
{
    int result;
    __asm
    {
        // calculation of E
        mov eax, y                
        dec eax                 
        imul eax, eax             
        imul eax, y              

        mov ebx, x                
        sub ebx, eax              

        mov ecx, z              
        test ecx, ecx             
        jz division_by_zero       

        cdq                      
        idiv ecx                 
        mov ebx, eax              

        // calculation of D
        mov eax, x              
        imul eax, y               
        imul eax, -2           

        mov ecx, z               
        add ecx, x               
        imul ecx, 3              

        add eax, ecx            
        mov ecx, eax           

       
        cmp ebx, 0                
        jg multiply               
        jl divide               

        // If D == 0
        jmp return_negative   

    multiply:
        imul eax, ebx            
        jmp store_result

    divide:
        test ebx, ebx             
        jz return_negative     
        cdq                       
        idiv ebx                 
        jmp store_result

    return_negative:
        mov eax, -1               

    division_by_zero:
        mov eax, -1               

    store_result:
        mov result, eax          
    }
    return result;
}


int main()
{
    // values in the template code
    int f = 320000;
    int s = -250000;
    int t = 122000;
    int r = 0;

    r = solution_for_grade_5(f, s, t);
    printf("solution_for_grade_5(%d, %d, %d) = %d\n", f, s, t, r);
    int expected_result5 = -2 * (f * s) + 3 * (t + f);
    printf("Expected result for grade 5 = %d\n", expected_result5);

    assert(r == expected_result5);

    r = solution_for_grade_7(f, s, t);
    printf("solution_for_grade_7(%d, %d, %d) = %d\n", f, s, t, r);
    assert(r != 0);

    int expected_d7;
    if (t == 0) {
        expected_d7 = -1;  
    } else {
        expected_d7 = f - ((s - 1) * (s - 1) * (s - 1)) / t;
    }
    printf("Expected result for grade 7 = %d\n", expected_d7);

    r = solution_for_grade_9(f, s, t);
    printf("solution_for_grade_9(%d, %d, %d) = %d\n", f, s, t, r);
    assert(r > -1);

    printf("------------------------\n");


    // with different input values as you asked in the templete code. With smaller values it is working more correctly
    int small_f = 2000;  
    int small_s = -1500; 
    int small_t = 1000;  
    int small_r = 0;

    small_r = solution_for_grade_5(small_f, small_s, small_t);
    printf("solution_for_grade_5(%d, %d, %d) = %d\n", small_f, small_s, small_t, small_r);
    int expected_result5_small = -2 * (small_f * small_s) + 3 * (small_t + small_f);
    printf("Expected result for grade 5 (small values) = %d\n", expected_result5_small);

    assert(small_r == expected_result5_small);

 
    small_r = solution_for_grade_7(small_f, small_s, small_t);
    printf("solution_for_grade_7(%d, %d, %d) = %d\n", small_f, small_s, small_t, small_r);

    int expected_d7_small;
    if (small_t == 0) {
        expected_d7_small = -1;  
    } else {
        expected_d7_small = small_f - ((small_s - 1) * (small_s - 1) * (small_s - 1)) / small_t;
    }
    printf("Expected result for grade 7 (small values) = %d\n", expected_d7_small);

    small_r = solution_for_grade_9(small_f, small_s, small_t);
    printf("solution_for_grade_9(%d, %d, %d) = %d\n", small_f, small_s, small_t, small_r);

    return 0;
}