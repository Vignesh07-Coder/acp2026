#!/usr/bin/env bash

# Define run function to capture output and status
run() {
    output=$(eval "$1" 2>&1)
    status=$?
}

# Helper to compile before tests
setup() {
    gcc -o demo3 demo3.c
}

# 1. Zero Rectangles (Logic Edge Case)
test1() {
    run bash -c "echo 0 | ./demo3"
    if [ "$status" -eq 0 ]; then
        echo "Test 1 passed!"
    fi
}

# 2. Negative Dimensions (Domain Logic)
# Tests if the program accepts negative lengths (should ideally handle as error)
test2() {
    run bash -c "echo -e '1\n-5\n10' | ./demo3"
    # Even if it calculates -50, it shouldn't crash
    if [[ "$output" =~ "-50.00" ]]; then
        echo "Test 2 passed!"
    fi
}

# 3. Floating Point Precision (Rounding/Comparison
# Checks if the largest area logic handles very small differences
test3() {
    run bash -c "echo -e '2\n1.000001\n1.0\n1.000002\n1.0' | ./demo3"
    if [[ "$output" =~ "Rectangle 2" ]]; then
        echo "Test 3 passed!"
    fi
}

# 4. Large Number of Rectangles (Stack Overflow/Memory)
# Tests if the array of structures handles a large 'n' (VLA limits)
test4() {
    # Generating input for 10,000 rectangles
    input_data=$(python3 -c "print('10000'); print('1\n1\n'*10000)")
    run bash -c "echo '$input_data' | ./demo3"
    if [ "$status" -eq 0 ]; then
        echo "Test 4 passed!"
    fi
}

# 5. Non-Numeric Input (Input Validation)
# Tests if the program enters an infinite loop or crashes on 'abc'
test5() {
    run bash -c "echo 'abc' | ./demo3"
    # The program should exit or fail safely, not hang
    if [ "$status" -eq 0 ]; then
        echo "Test 5 passed!"
    fi
}

# 6. Identical Areas (Tie-breaking)
# Ensures the logic returns the first occurrence or handles ties without error
test6() {
    run bash -c "echo -e '3\n10\n2\n5\n4\n2\n10' | ./demo3"
    # Area 20 occurs twice. Program should pick one consistently.
    if [[ "$output" =~ "Rectangle 1" ]] || [[ "$output" =~ "Rectangle 2" ]]; then
        echo "Test 6 passed!"
    fi
}

teardown() {
    rm -f demo3
}

# Run setup
setup

# Run tests
test1
# test2
# test3
# test4
# test5
# test6

# Run teardown
teardown
