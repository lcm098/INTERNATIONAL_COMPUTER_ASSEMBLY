# INTERNATIONAL_COMPUTER_ASSEMBLY

""" A very simple code to print Hello World in IC_Assembly """
""" in IC Assembly, we use Very Special Variables at the place of Registers """

section .text ||

    mov ras, "Hello"  // move "Hello" string to ras (vs variable)
    load fptr, @[ras] // load vs-var as (array group) to function pointer
    call write        // call write function to print it
    unload fptr       // nice way to unload fptr, every time after load

    link arr, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    load fptr, @[arr]
    call write
    unload fptr

    link dict, {"ram":1, "shyam":2, "mohan":3}
    load fptr, @[dict]
    call write
    unload fptr

    link list, ["anoop", 1, false, nil]
    load fptr, @[list]
    call write
    unload fptr

    load fptr, @[age, gender] 
    call read                  //call stander read for input  

    // introduction ecx (which is result resolver variable)

    mov ecx_res, fptr   // move fptr value to ecx_res variable
    unload fptr         // unload the previous persistence of read function

    cmp [(age >= 21) & (gender == 'm')], true
    [
        link name
        load fptr, @["Hello ", name, " You Can Drive!"]
        call write
        unload fptr
    ]
    else is false
    [
        load fptr, @["Hello ", name, " You Can Not Drive"]
        call write
        unload fptr
    ]

||

section .data ||
    
    da arr 10
    dd dict 3
    dl list 4
    
    dr name "danishk"
    dr age 3
    dr gender 1

||