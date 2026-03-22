#!/usr/bin/env bats

# Helper to compile before tests
setup() {
    gcc -o demo3 demo3.c
}

# 1. Zero Rectangles (Logic Edge Case)
@test "Handle zero rectangles gracefully" {
    run bash -c "echo 0 | ./demo3"
    [ "$status" -eq 0 ]
}

# 2. Negative Dimensions (Domain Logic)
# Tests if the program accepts negative lengths (should ideally handle as error)
@test "Input with negative dimensions" {
    run bash -c "echo -e '1\n-5\n10' | ./demo3"
    # Even if it calculates -50, it shouldn't crash
    [[ "$output" =~ "-50.00" ]]
}

# 3. Floating Point Precision (Rounding/Comparison
# Checks if the largest area logic handles very small differences
@test "Comparison of very close floating point areas" {
    run bash -c "echo -e '2\n1.000001\n1.0\n1.000002\n1.0' | ./demo3"
    [[ "$output" =~ "Rectangle 2" ]]
}

# 4. Large Number of Rectangles (Stack Overflow/Memory)
# Tests if the array of structures handles a large 'n' (VLA limits)
@test "Large input size for n" {
    # Generating input for 10,000 rectangles
    input_data=$(python3 -c "print('10000'); print('1\n1\n'*10000)")
    run bash -c "echo '$input_data' | ./demo3"
    [ "$status" -eq 0 ]
}

# 5. Non-Numeric Input (Input Validation)
# Tests if the program enters an infinite loop or crashes on 'abc'
@test "Non-numeric input for count" {
    run bash -c "echo 'abc' | ./demo3"
    # The program should exit or fail safely, not hang
    [ "$status" -eq 0 ] 
}

# 6. Identical Areas (Tie-breaking)
# Ensures the logic returns the first occurrence or handles ties without error
@test "Multiple rectangles with identical largest area" {
    run bash -c "echo -e '3\n10\n2\n5\n4\n2\n10' | ./demo3"
    # Area 20 occurs twice. Program should pick one consistently.
    [[ "$output" =~ "Rectangle 1" ]] || [[ "$output" =~ "Rectangle 2" ]]
}

teardown() {
    rm -f demo3
}
