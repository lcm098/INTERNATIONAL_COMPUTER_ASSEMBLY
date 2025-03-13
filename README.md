# INTERNATIONAL_COMPUTER_ASSEMBLY

""" A very simple code to print Hello World in IC_Assembly """
""" in IC Assembly, we use Very Special Variables at the place of Registers """

section .text ||

    mov ras, "Hello" // move "Hello" string to ras (vs variable)
    load fptr, ras // load vs-var to function pointer
    call write // call write function to print it
    unload fptr // nice way to unload fptr, every time after load

||