# Test Document
Welcome to the test document. This section provides an overview of the document.

 The rod cutting program determines the optimal way to cut a rod for maximum value while respecting piece constraints. It reads rod pieces with length, value, and max usage limits, 0 means unlimited, validates user input, and computes the best cuts. LRU and FIFO caching store results, including usage counts, to optimize efficiency and avoid redundant calculations.


## To run the program:
    # 1. run make
    # 2. To test policy LRU run: ./policyLRU input.txt
    # 3. To test policy FIFO run: ./policyFIFO input.txt

## Test Cases for Rod Cutting Program
 # Valid Inputs
        5
        1 @ 1 = 2
        2 @ 2 = 4
        Remainder: 0
        Value: 6

        25
        2 @ 2 = 4
        3 @ 7 = 30
        Remainder: 0
        Value: 34

        3
        1 @ 1 = 2
        1 @ 2 = 2
        Remainder: 0
        Value: 4   

        100000
        1 @ 1 = 2
        2 @ 2 = 4
        14285 @ 7 = 142850
        Remainder: 0
        Value: 142856

# Invalid Inputs (Alphabetic Characters)
        a
        Error: Invalid input. Please enter a positive integer.

# Invalid Inputs (Negative Numbers & Special Characters)        
        -10
        Error: Invalid input. Please enter a positive integer.
        $$
        Error: Invalid input. Please enter a positive integer.

# Edge Cases (Empty and Large Values)
        100001
        Error: Rod length is too large.

        (empty)
        Error: Input cannot be empty.

        0
        Error: Rod length must be a positive integer.
