    #ifdef __cplusplus
    #include <cstdio>
    #include <cassert>
    #else
    #include <stdio.h>
    #include <assert.h>
    #endif

    //variant 0 => E = –2XY + 3(Z + X)
    short solution_for_grade_7(short x, short y, short z)
    {
        
        short result;
        __asm
        {
            
            mov ax, x        
            imul ax, y      
            imul ax, -2      

            mov bx, z        
            add bx, x      
            imul bx, 3       

            add ax, bx       

            mov [result], ax 
        }
        return result;
    }
    
    short solution_for_grade_9(short x, short y, short z)
    {
       
        short result; // to calculate => E / (3Y - 2Z)
        short e = solution_for_grade_7(x, y, z); 
        short denominator;

        __asm
        {
            mov ax, y        
            imul ax, 3       

            mov bx, z        
            imul bx, 2       

            sub ax, bx      
            mov [denominator], ax 
        }

        // to handle zero exception
        if (denominator == 0) {
            printf("Can't divide by 0!\n");
            return 0;  
        }

        __asm
        {
            mov ax, e          
            cwd                
            mov bx, denominator 
            idiv bx            

            mov [result], ax   
        }

        return result;
    }
    

    int main()
    {

        short first = 420;  
        short second = -50; 
        short third = 122;  

        short f = 50;  
        short s = 10; 
        short t = 20;  
    
        short result7 = solution_for_grade_7(first, second, third);
        short result9 = solution_for_grade_9(first, second, third);

        short result71 = solution_for_grade_7(f, s, t);
        short result91 = solution_for_grade_9(f, s, t);

    
        printf("solution_for_grade_7(%d, %d, %d) = %d\n", first, second, third, result7);
        printf("solution_for_grade_9(%d, %d, %d) = %d\n", first, second, third, result9);

        printf("------- with some other variable ---------");
        
        printf("solution_for_grade_71(%d, %d, %d) = %d\n", f, s, t, result71);
        printf("solution_for_grade_91(%d, %d, %d) = %d\n", f, s, t, result91);

        // manual calculatoin to check
        short expected_result7 = -2 * (first * second) + 3 * (third + first);
        assert(result7 == expected_result7);

        short denominator = 3 * second - 2 * third;
        if (denominator != 0) {
            short expected_result9 = expected_result7 / denominator;
            assert(result9 == expected_result9); 
        } else {
            printf("Can't divide by 0!! \n");
        }

        return 0;

    }
